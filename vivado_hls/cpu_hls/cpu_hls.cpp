#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "rv32_cpu.hpp"
#include "cpu_hls.h"

void cpu_hls (const uint32_t inst_mem[2048], uint32_t data_mem[2048])
{
  int y, x;

  uint32_t pc = 0;
  uint32_t inst;
  inst_rv32_t dec_inst;

  rv32_cpu u_rv32_cpu (data_mem);

#ifndef __SYNTHESIS__
  FILE *cpu_log;
  if ((cpu_log = fopen("cpu.log", "w")) == NULL) {
    perror ("cpu.log");
  }
#endif

  do {
    inst = inst_mem[pc >> 2];
    dec_inst = u_rv32_cpu.decode_inst(inst);

    uint32_t reg_data;

#ifndef __SYNTHESIS__
    fprintf(cpu_log, "[%08x] : %08x DASM(%08x)\n", pc, inst, inst);
#endif // _SYNTHESIS

    RegAddr_t rs1 = u_rv32_cpu.get_rs1_addr (inst);
    RegAddr_t rs2 = u_rv32_cpu.get_rs2_addr (inst);
    RegAddr_t rd  = u_rv32_cpu.get_rd_addr  (inst);
    uint16_t  csr_addr = (inst >> 16) & 0x0ffff;

    bool update_pc = false;

    switch (dec_inst) {
      case CSRRW  : {
        reg_data = u_rv32_cpu.csrrw (csr_addr, rs1);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case CSRRS  : {
        reg_data = u_rv32_cpu.csrrs (csr_addr, rs1);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case CSRRC  : {
        reg_data = u_rv32_cpu.csrrc (csr_addr, rs1);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case CSRRWI : {
        XLEN_t zimm = (inst >> 15) & 0x1f;
        reg_data = u_rv32_cpu.csrrw (csr_addr, zimm);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case CSRRSI : {
        XLEN_t zimm = (inst >> 15) & 0x1f;
        reg_data = u_rv32_cpu.csrrs (csr_addr, zimm);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case CSRRCI : {
        XLEN_t zimm = (inst >> 15) & 0x1f;
        reg_data = u_rv32_cpu.csrrc (csr_addr, zimm);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case LUI : {
        XLEN_t imm = u_rv32_cpu.ExtendSign (u_rv32_cpu.ExtractBitField (inst, 31, 12), 19);
        imm = u_rv32_cpu.SExtXlen(imm << 12);
        u_rv32_cpu.write_reg(rd, imm);
        break;
      }
      case AUIPC : {
        XLEN_t imm = u_rv32_cpu.ExtendSign (u_rv32_cpu.ExtractBitField (inst, 31, 12), 19);
        imm = u_rv32_cpu.SExtXlen(imm << 12) + pc & 0x0fff;
        u_rv32_cpu.write_reg(rd, imm);
        break;
      }
      case LW  : {
        uint32_t addr = rs1 + ((inst >> 20) & 0xfff);
        reg_data = u_rv32_cpu.mem_access(LOAD, rs1, addr, data_mem);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case ADDI : {
        reg_data = u_rv32_cpu.read_reg(rs1) + u_rv32_cpu.ExtractIField (inst);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case SLTI : {
        reg_data = u_rv32_cpu.read_reg(rs1) < u_rv32_cpu.ExtractIField (inst);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case SLTIU : {
        reg_data = (uint32_t)u_rv32_cpu.read_reg(rs1) < u_rv32_cpu.ExtractIField (inst);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case XORI : {
        reg_data = u_rv32_cpu.read_reg(rs1) ^ u_rv32_cpu.ExtractIField (inst);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case ORI : {
        reg_data = u_rv32_cpu.read_reg(rs1) | u_rv32_cpu.ExtractIField (inst);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case ANDI : {
        reg_data = u_rv32_cpu.read_reg(rs1) & u_rv32_cpu.ExtractIField (inst);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }

      case ADD : {
        reg_data = u_rv32_cpu.read_reg(rs1) + u_rv32_cpu.read_reg(rs2);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case SUB : {
        reg_data = u_rv32_cpu.read_reg(rs1) - u_rv32_cpu.read_reg(rs2);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case SLL : {
        reg_data = u_rv32_cpu.read_reg(rs1) << (uint32_t)u_rv32_cpu.read_reg(rs2);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case SLT : {
        reg_data = u_rv32_cpu.read_reg(rs1) < u_rv32_cpu.read_reg(rs2);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case SLTU : {
        reg_data = (uint32_t)u_rv32_cpu.read_reg(rs1) < (uint32_t)u_rv32_cpu.read_reg(rs2);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case XOR : {
        reg_data = u_rv32_cpu.read_reg(rs1) ^ u_rv32_cpu.read_reg(rs2);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case SRL : {
        reg_data = (uint32_t)u_rv32_cpu.read_reg(rs1) >> (uint32_t)u_rv32_cpu.read_reg(rs2);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case SRA : {
        reg_data = u_rv32_cpu.read_reg(rs1) >> (uint32_t)u_rv32_cpu.read_reg(rs2);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case OR : {
        reg_data = u_rv32_cpu.read_reg(rs1) | u_rv32_cpu.read_reg(rs2);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case AND : {
        reg_data = u_rv32_cpu.read_reg(rs1) & u_rv32_cpu.read_reg(rs2);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case SW  : {
        uint32_t addr = rs1 + ((inst >> 25) + ((inst >> 7) &0x1f));
        reg_data = u_rv32_cpu.read_reg(rs1);
        u_rv32_cpu.mem_access(STORE, rs2, addr, data_mem);
        break;
      }
      case JAL : {
        uint32_t addr = u_rv32_cpu.ExtractUJField(inst);
        pc = addr;
        u_rv32_cpu.write_reg(rd, addr + 4);
        update_pc = true;
        break;
      }
      case BEQ  :
      case BNE  :
      case BLT  :
      case BGE  :
      case BLTU :
      case BGEU : {
        XLEN_t rs1_data = u_rv32_cpu.read_reg(rs1);
        XLEN_t rs2_data = u_rv32_cpu.read_reg(rs2);
        Addr_t addr = u_rv32_cpu.ExtractSBField(inst);
        bool jump_en;
        switch ((inst >> 12) & 0x7) {
          case BEQ  : jump_en = (rs1_data == rs2_data); break;
          case BNE  : jump_en = (rs1_data != rs2_data); break;
          case BLT  : jump_en = (rs1_data <  rs2_data); break;
          case BGE  : jump_en = (rs1_data >= rs2_data); break;
          case BLTU : jump_en = ((uint32_t)rs1_data >= (uint32_t)rs2_data); break;
          case BGEU : jump_en = ((uint32_t)rs1_data >= (uint32_t)rs2_data); break;
        }
        if (jump_en) {
          pc = addr;
          update_pc = true;
        }
        break;
      }
      case JALR : {
        uint32_t addr = u_rv32_cpu.ExtractIField (inst);
        pc = addr;
        u_rv32_cpu.write_reg(rd, addr + 4);
        update_pc = true;
        break;
      }
      default  : {
        break;
      }
    }
    if (update_pc == false) {
      pc += 4;
    }
  } while (dec_inst != WFI);

  return;
}
