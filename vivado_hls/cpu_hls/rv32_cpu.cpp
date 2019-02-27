#include "stdio.h"

#include "cpu_hls.h"
#include "rv32_cpu.hpp"

rv32_cpu::rv32_cpu(uint8_t *data_mem, Addr_t tohost_addr, Addr_t fromhost_addr)
    : m_data_mem(data_mem), m_tohost_addr(tohost_addr), m_fromhost_addr(fromhost_addr)
{
#pragma HLS INTERFACE m_axi port=data_mem bundle=mem
  m_update_pc = false;
  m_finish_cpu = false;

  m_reg32[0] = 0;
  m_pc = 0;

#ifndef __SYNTHESIS__
  if ((m_cpu_log = fopen("cpu.log", "w")) == NULL) {
    perror ("cpu.log");
  }
#endif // __SYNTHESIS__
}

void rv32_cpu::fetch_inst ()
{
  uint32_t *data_mem32 = (uint32_t *)m_data_mem;
  m_inst = data_mem32[m_pc >> 2];
}


void rv32_cpu::decode_inst ()
{
  switch(m_inst & 0x7f) {
    case 0x0f : {
      switch ((m_inst >> 12) & 0x07) {
        case 0b000 : m_dec_inst = FENCE;   break;
        case 0b001 : m_dec_inst = FENCE_I; break;
        default    : m_dec_inst = NOP;     break;
      }
      break;
    }
    case 0x33 : {
      switch ((m_inst >> 12) & 0x07) {
        case 0b000 : {
          if      (((m_inst >> 25) & 0x7f) == 0b0000000) { m_dec_inst = ADD; }
          else if (((m_inst >> 25) & 0x7f) == 0b0100000) { m_dec_inst = SUB; }
          else                                           { m_dec_inst = NOP; }
          break;
        }
        case 0b001 : m_dec_inst = SLL;  break;
        case 0b010 : m_dec_inst = SLT;  break;
        case 0b011 : m_dec_inst = SLTU; break;
        case 0b100 : m_dec_inst = XOR;  break;
        case 0b101 : {
          if      (((m_inst >> 25) & 0x7f) == 0b0000000) { m_dec_inst = SRL; }
          else if (((m_inst >> 25) & 0x7f) == 0b0100000) { m_dec_inst = SRA; }
          else                                       { m_dec_inst = NOP; }
          break;
        }
        case 0b110 : m_dec_inst = OR;  break;
        case 0b111 : m_dec_inst = AND; break;
        default    : m_dec_inst = NOP; break;
      }
      break;
    }
    case 0x03 :
      switch ((m_inst >> 12) & 0x07) {
        case 0b000 : m_dec_inst = LB; break;
        case 0b001 : m_dec_inst = LH; break;
        case 0b010 : m_dec_inst = LW; break;
        case 0b100 : m_dec_inst = LBU; break;
        case 0b101 : m_dec_inst = LHU; break;
        default    : m_dec_inst = NOP; break;
      }
      break;
    case 0x23 : m_dec_inst = SW;    break;
    case 0x37 : m_dec_inst = LUI;   break;
    case 0x17 : m_dec_inst = AUIPC; break;
    case 0x63 : {
      switch ((m_inst >> 12) & 0x07) {
        case 0b000 : m_dec_inst = BEQ;  break;
        case 0b001 : m_dec_inst = BNE;  break;
        case 0b100 : m_dec_inst = BLT;  break;
        case 0b101 : m_dec_inst = BGE;  break;
        case 0b110 : m_dec_inst = BLTU; break;
        case 0b111 : m_dec_inst = BGEU; break;
        default    : m_dec_inst = NOP;  break;
      }
      break;
    }
    case 0x13 : {
      switch ((m_inst >> 12) & 0x07) {
        case 0b000 : m_dec_inst = ADDI;  break;
        case 0b010 : m_dec_inst = SLTI;  break;
        case 0b011 : m_dec_inst = SLTIU; break;
        case 0b100 : m_dec_inst = XORI;  break;
        case 0b110 : m_dec_inst = ORI;   break;
        case 0b111 : m_dec_inst = ANDI;  break;
        case 0b001 : m_dec_inst = SLLI;  break;
        case 0b101 : {
          if      (((m_inst >> 25) & 0x7f) == 0b0000000) { m_dec_inst = SRLI; }
          else if (((m_inst >> 25) & 0x7f) == 0b0100000) { m_dec_inst = SRAI; }
          else                                           { m_dec_inst = NOP; }
          break;
        }
        default    : m_dec_inst = NOP;   break;
      }
      break;
    }
    case 0x6f : m_dec_inst = JAL;  break;
    case 0x67 : m_dec_inst = JALR; break;
    case 0x73 :
      switch ((m_inst >> 12) & 0x07) {
        case 0x000 : {
          if (((m_inst >> 20) & 0xfff) == 0x000) {
            m_dec_inst = ECALL;
          } else if (((m_inst >> 20) & 0xfff) == 0x001) {
            m_dec_inst = EBREAK;
          } else if (((m_inst >> 20) & 0xfff) == 0x002) {
            m_dec_inst = URET;
          } else if (((m_inst >> 20) & 0xfff) == 0x102) {
            m_dec_inst = SRET;
          } else if (((m_inst >> 20) & 0xfff) == 0x302) {
            m_dec_inst = MRET;
          } else {
            m_dec_inst = NOP;
          }
          break;
        }
        case 0b001 : m_dec_inst = CSRRW  ; break;
        case 0b010 : m_dec_inst = CSRRS  ; break;
        case 0b011 : m_dec_inst = CSRRC  ; break;
        case 0b101 : m_dec_inst = CSRRWI ; break;
        case 0b110 : m_dec_inst = CSRRSI ; break;
        case 0b111 : m_dec_inst = CSRRCI ; break;
        default    : m_dec_inst = NOP    ; break;
      }
      break;
    default   : m_dec_inst = WFI; break;
  }
}


void rv32_cpu::execute_inst()
{
#ifndef __SYNTHESIS__
  fprintf(m_cpu_log, "[%08x] : %08x DASM(%08x)\n", m_pc, m_inst, m_inst);
  fflush(m_cpu_log);
#endif // _SYNTHESIS

  m_rs1 = get_rs1_addr (m_inst);
  m_rs2 = get_rs2_addr (m_inst);
  m_rd  = get_rd_addr  (m_inst);

  m_csr_addr = (m_inst >> 20) & 0x0ffff;

  m_update_pc = false;

  switch (m_dec_inst) {
    case CSRRW  : {
      XLEN_t reg_data = csrrw (m_csr_addr, read_reg(m_rs1));
      write_reg(m_rd, reg_data);
      break;
    }
    case CSRRS  : {
      XLEN_t reg_data = csrrs (m_csr_addr, read_reg(m_rs1));
      write_reg(m_rd, reg_data);
      break;
    }
    case CSRRC  : {
      XLEN_t reg_data = csrrc (m_csr_addr, read_reg(m_rs1));
      write_reg(m_rd, reg_data);
      break;
    }
    case CSRRWI : {
      XLEN_t zimm = (m_inst >> 15) & 0x1f;
      XLEN_t reg_data = csrrw (m_csr_addr, zimm);
      write_reg(m_rd, reg_data);
      break;
    }
    case CSRRSI : {
      XLEN_t zimm = (m_inst >> 15) & 0x1f;
      XLEN_t reg_data = csrrs (m_csr_addr, zimm);
      write_reg(m_rd, reg_data);
      break;
    }
    case CSRRCI : {
      XLEN_t zimm = (m_inst >> 15) & 0x1f;
      XLEN_t reg_data = csrrc (m_csr_addr, zimm);
      write_reg(m_rd, reg_data);
      break;
    }
    case LUI : {
      XLEN_t imm = ExtendSign (ExtractBitField (m_inst, 31, 12), 19);
      imm = SExtXlen(imm << 12);
      write_reg(m_rd, imm);
      break;
    }
    case AUIPC : {
      XLEN_t imm = ExtendSign (ExtractBitField (m_inst, 31, 12), 19);
      imm = SExtXlen(imm << 12) + (m_pc & 0x0fff);
      write_reg(m_rd, imm);
      break;
    }
    case LB  : {
      uint32_t addr = read_reg(m_rs1) + ((m_inst >> 20) & 0xfff);
      XLEN_t reg_data = mem_access(LOAD, read_reg(m_rs1), addr, SIZE_BYTE);
      reg_data = reg_data >> (8 * (addr & 0x03));
      write_reg(m_rd, reg_data);
      break;
    }
    case LH  : {
      uint32_t addr = read_reg(m_rs1) + ((m_inst >> 20) & 0xfff);
      XLEN_t reg_data = mem_access(LOAD, read_reg(m_rs1), addr, SIZE_HWORD);
      reg_data = reg_data >> (8 * (addr & 0x02)) ;
      write_reg(m_rd, reg_data);
      break;
    }
    case LW  : {
      uint32_t addr = read_reg(m_rs1) + ((m_inst >> 20) & 0xfff);
      XLEN_t reg_data = mem_access(LOAD, read_reg(m_rs1), addr, SIZE_WORD);
      write_reg(m_rd, reg_data);
      break;
    }
    case LBU  : {
      uint32_t addr = read_reg(m_rs1) + ((m_inst >> 20) & 0xfff);
      UXLEN_t reg_data = mem_access(LOAD, read_reg(m_rs1), addr, SIZE_BYTE);
      reg_data = reg_data >> (8 * (addr & 0x03));
      write_reg(m_rd, reg_data);
      break;
    }
    case LHU  : {
      uint32_t addr = read_reg(m_rs1) + ((m_inst >> 20) & 0xfff);
      UXLEN_t reg_data = mem_access(LOAD, read_reg(m_rs1), addr, SIZE_HWORD);
      reg_data = reg_data >> (8 * (addr & 0x02)) ;
      write_reg(m_rd, reg_data);
      break;
    }
    case ADDI : {
      XLEN_t reg_data = read_reg(m_rs1) + ExtractIField (m_inst);
      write_reg(m_rd, reg_data);
      break;
    }
    case SLTI : {
      XLEN_t reg_data = read_reg(m_rs1) < ExtractIField (m_inst);
      write_reg(m_rd, reg_data);
      break;
    }
    case SLTIU : {
      XLEN_t reg_data = (uint32_t)read_reg(m_rs1) < ExtractIField (m_inst);
      write_reg(m_rd, reg_data);
      break;
    }
    case XORI : {
      XLEN_t reg_data = read_reg(m_rs1) ^ ExtractIField (m_inst);
      write_reg(m_rd, reg_data);
      break;
    }
    case ORI : {
      XLEN_t reg_data = read_reg(m_rs1) | ExtractIField (m_inst);
      write_reg(m_rd, reg_data);
      break;
    }
    case ANDI : {
      XLEN_t reg_data = read_reg(m_rs1) & ExtractIField (m_inst);
      write_reg(m_rd, reg_data);
      break;
    }
    case SLLI : {
      XLEN_t reg_data = read_reg(m_rs1) << ExtractSHAMTField (m_inst);
      write_reg(m_rd, reg_data);
      break;
    }
    case SRLI : {
      XLEN_t reg_data = (UXLEN_t)read_reg(m_rs1) >> ExtractSHAMTField (m_inst);
      write_reg(m_rd, reg_data);
      break;
    }
    case SRAI : {
      XLEN_t reg_data = (XLEN_t)read_reg(m_rs1) >> ExtractSHAMTField (m_inst);
      write_reg(m_rd, reg_data);
      break;
    }

    case ADD : {
      XLEN_t reg_data = read_reg(m_rs1) + read_reg(m_rs2);
      write_reg(m_rd, reg_data);
      break;
    }
    case SUB : {
      XLEN_t reg_data = read_reg(m_rs1) - read_reg(m_rs2);
      write_reg(m_rd, reg_data);
      break;
    }
    case SLL : {
      XLEN_t reg_data = read_reg(m_rs1) << (uint32_t)read_reg(m_rs2);
      write_reg(m_rd, reg_data);
      break;
    }
    case SLT : {
      XLEN_t reg_data = read_reg(m_rs1) < read_reg(m_rs2);
      write_reg(m_rd, reg_data);
      break;
    }
    case SLTU : {
      XLEN_t reg_data = (uint32_t)read_reg(m_rs1) < (uint32_t)read_reg(m_rs2);
      write_reg(m_rd, reg_data);
      break;
    }
    case XOR : {
      XLEN_t reg_data = read_reg(m_rs1) ^ read_reg(m_rs2);
      write_reg(m_rd, reg_data);
      break;
    }
    case SRL : {
      XLEN_t reg_data = (uint32_t)read_reg(m_rs1) >> (uint32_t)read_reg(m_rs2);
      write_reg(m_rd, reg_data);
      break;
    }
    case SRA : {
      XLEN_t reg_data = read_reg(m_rs1) >> (uint32_t)read_reg(m_rs2);
      write_reg(m_rd, reg_data);
      break;
    }
    case OR : {
      XLEN_t reg_data = read_reg(m_rs1) | read_reg(m_rs2);
      write_reg(m_rd, reg_data);
      break;
    }
    case AND : {
      XLEN_t reg_data = read_reg(m_rs1) & read_reg(m_rs2);
      write_reg(m_rd, reg_data);
      break;
    }
    case SW  : {
      Addr_t addr = read_reg(m_rs1) + ExtractSField(m_inst);
      mem_access(STORE, read_reg(m_rs2), addr, SIZE_WORD);
      break;
    }
    case JAL : {
      Addr_t addr = ExtractUJField(m_inst);
      m_pc = m_pc + addr;
      write_reg(m_rd, addr + 4);
      m_update_pc = true;
      break;
    }
    case BEQ  :
    case BNE  :
    case BLT  :
    case BGE  :
    case BLTU :
    case BGEU : {
      XLEN_t rs1_data = read_reg(m_rs1);
      XLEN_t rs2_data = read_reg(m_rs2);
      Addr_t addr = ExtractSBField(m_inst);
      bool jump_en;
      switch (m_dec_inst) {
        case BEQ  : jump_en = (rs1_data == rs2_data); break;
        case BNE  : jump_en = (rs1_data != rs2_data); break;
        case BLT  : jump_en = (rs1_data <  rs2_data); break;
        case BGE  : jump_en = (rs1_data >= rs2_data); break;
        case BLTU : jump_en = ((uint32_t)rs1_data >= (uint32_t)rs2_data); break;
        case BGEU : jump_en = ((uint32_t)rs1_data >= (uint32_t)rs2_data); break;
      }
      if (jump_en) {
        m_pc = m_pc + addr;
        m_update_pc = true;
#ifndef __SYNTHESIS__
        fprintf(m_cpu_log, "Jump Enabled PC = %08x\n", m_pc);
        fflush(m_cpu_log);
#endif // __SYNTHESIS__
      }
      break;
    }
    case JALR : {
      Addr_t addr = ExtractIField (m_inst);
      m_pc = addr;
      write_reg(m_rd, addr + 4);
      m_update_pc = true;
      break;
    }
    case FENCE   : { break; }
    case FENCE_I : { break; }
    case ECALL : {
      XLEN_t mtvec = csrrs (CsrAddr_mtvec, 0); // MTVEC

      csrrw (CsrAddr_mepc, m_pc);                           // MEPC
      csrrw (CsrAddr_mcause, EcallFromMMode); // MCAUSE
      csrrw (CsrAddr_mtval, 0);                             // MTVAL

      m_pc = mtvec;
      m_update_pc = true;
      break;
    }
    case EBREAK : { break; }
    case URET : {
#ifndef __SYNTHESIS__
      fprintf(m_cpu_log, "Error: [%08x] : %08x URET is not supported\n", m_pc, m_inst);
#endif // __SYNTHESIS__
    }
    case SRET : {
#ifndef __SYNTHESIS__
      fprintf(m_cpu_log, "Error: [%08x] : %08x SRET is not supported\n", m_pc, m_inst);
#endif // __SYNTHESIS__
    }
    case MRET : {
      XLEN_t mepc = csrrs (CsrAddr_mepc, 0); // MEPC
      m_pc = mepc;
      m_update_pc = true;
      break;
    }
    default  : {
#ifndef __SYNTHESIS__
      fprintf(m_cpu_log, "Error: [%08x] : %08x Instruction Decode Error\n", m_pc, m_inst);
#endif // __SYNTHESIS__
      break;
    }
  }
  if (m_update_pc == false) {
    m_pc += 4;
  }
}


XLEN_t rv32_cpu::mem_access (memtype_t op, uint32_t data, uint32_t addr, AccSize_t size)
{
  switch (op) {
    case STORE : {
      if (addr == m_tohost_addr) {
        m_finish_cpu = true;
        m_tohost = data;
      } else if (addr == m_fromhost_addr) {
        m_finish_cpu = true;
        m_fromhost = data;
      } else {
        switch(size) {
          case SIZE_BYTE  : {
            m_data_mem[addr] = data;
            break;
          }
          case SIZE_HWORD : {
            uint16_t *data_mem16 = (uint16_t *)m_data_mem;
            data_mem16[addr >> 1] = data & 0x0ffff;
            break;
          }
          case SIZE_WORD : {
            uint32_t *data_mem32 = (uint32_t *)m_data_mem;
            data_mem32[addr >> 2] = data;
            break;
          }
          default : {
#ifndef __SYNTHESIS__
            fprintf(m_cpu_log, "Info: Invalid Memory Access Size\n", addr, data);
            fflush(m_cpu_log);
#endif // __SYNTHESIS__
            break;
          }
        }
      }
      break;
    }
    case LOAD  : {
      if (addr == m_tohost_addr) {
        return m_tohost;
      } else if (addr == m_fromhost_addr) {
        return m_fromhost;
      } else {
        switch(size) {
          case SIZE_BYTE  : {
            return m_data_mem[addr];
          }
          case SIZE_HWORD : {
            uint16_t *data_mem16 = (uint16_t *)m_data_mem;
            return data_mem16[addr >> 1];
          }
          case SIZE_WORD : {
            uint32_t *data_mem32 = (uint32_t *)m_data_mem;
            return data_mem32[addr >> 2];
          }
          default : {
#ifndef __SYNTHESIS__
            fprintf(m_cpu_log, "Info: Invalid Memory Access Size\n", addr, data);
            fflush(m_cpu_log);
#endif // __SYNTHESIS__
            break;
          }
        }
      }
      break;
    }
  }
  return 0;
}


XLEN_t rv32_cpu::ExtendSign (uint32_t data, uint32_t msb)
{

  int const mask = 1ULL << msb; // mask can be pre-computed if b is fixed

  data = data & ((1ULL << (msb + 1)) - 1);  // (Skip this if bits in x above position b are already zero.)
  return (data ^ mask) - mask;
}


XLEN_t rv32_cpu::ExtractBitField (Inst_t hex, uint32_t left, uint32_t right)
{
  uint32_t mask = (static_cast<uint32_t>(1) << (left - right + 1)) - 1;
  return (hex >> right) & mask;
}


XLEN_t rv32_cpu::ExtractUJField (Inst_t hex)
{
  uint32_t i24_21 = ExtractBitField (hex, 24, 21) & 0x0fUL;
  uint32_t i30_25 = ExtractBitField (hex, 30, 25) & 0x03fUL;
  uint32_t i20_20 = ExtractBitField (hex, 20, 20) & 0x01UL;
  uint32_t i19_12 = ExtractBitField (hex, 19, 12) & 0x0ffUL;
  uint32_t i31_31 = ExtractBitField (hex, 31, 31) & 0x01UL;

  uint32_t u_res = (i31_31 << 20) |
           (i19_12 << 12) |
           (i20_20 << 11) |
           (i30_25 <<  5) |
           (i24_21 <<  1);
  return ExtendSign (u_res, 20);
}


XLEN_t rv32_cpu::ExtractIField (Inst_t hex)
{
  uint32_t uimm32 = ExtractBitField (hex, 31, 20);
  return ExtendSign (uimm32, 11);
}


XLEN_t rv32_cpu::ExtractSHAMTField (Inst_t hex)
{
  return ExtractBitField (hex, 24, 20);
}


XLEN_t rv32_cpu::ExtractSBField (Inst_t hex)
{
  uint32_t i07_07 = ExtractBitField (hex,  7,  7) & 0x01UL;
  uint32_t i11_08 = ExtractBitField (hex, 11,  8) & 0x0fUL;
  uint32_t i30_25 = ExtractBitField (hex, 30, 25) & 0x03fUL;
  uint32_t i31_31 = ExtractBitField (hex, 31, 31) & 0x01UL;

  uint32_t u_res = (i31_31 << 12) |
           (i07_07 << 11) |
           (i30_25 <<  5) |
           (i11_08 <<  1);
  return ExtendSign (u_res, 12);
}


XLEN_t rv32_cpu::ExtractSField (Inst_t hex)
{
  XLEN_t i11_07 = ExtractBitField (hex, 11,  7) & 0x01fUL;
  XLEN_t i31_25 = ExtractBitField (hex, 31, 25) & 0x07fUL;

  XLEN_t u_res = (i31_25 << 5) |
           (i11_07 << 0);

  return ExtendSign (u_res, 11);
}
