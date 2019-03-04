#pragma once

#include <stdint.h>

#include "rv32_basic.hpp"
#include "rv32_csr.hpp"

typedef enum {
  CSRRW , CSRRS , CSRRC ,
  CSRRWI, CSRRSI, CSRRCI,
  LUI, AUIPC,
  ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI,
  ADD, SUB, SLL ,SLT, SLTU, XOR, SRL, SRA, OR, AND,
  LB, LH, LW, LBU, LHU, SW, SH, SB,
  JAL, JALR,
  BEQ, BNE, BLT, BGE, BLTU, BGEU,
  FENCE, FENCE_I,
  ECALL, EBREAK,
  MRET, SRET, URET,
  NOP,
  WFI
} inst_rv32_t;


typedef enum {
  InstAddrMisalign  =  0,
  InstAccessFault   =  1,
  IllegalInst       =  2,
  Breakpoint        =  3,
  LoadAddrMisalign  =  4,
  LoadAccessFault   =  5,
  StoreAddrMisalign =  6,
  StoreAccessFault  =  7,
  EcallFromUMode    =  8,
  EcallFromSMode    =  9,
  EcallFromHMode    = 10,
  EcallFromMMode    = 11,
  InstPageFault     = 12,
  LoadPageFault     = 13,
  StorePageFault    = 15
} ExceptCode_t;


typedef enum {
  LOAD = 0,
  STORE = 1
} memtype_t;


typedef enum {
  SIZE_BYTE  = 0,
  SIZE_HWORD = 1,
  SIZE_WORD  = 2,
  SIZE_DWORD = 3
} AccSize_t;


class rv32_cpu {
  Addr_t m_pc;

  Inst_t m_inst;
  inst_rv32_t m_dec_inst;

  XLEN_t m_reg32[32];
  rv32_csr m_rv32_csr;
  uint8_t *m_data_mem;
  Addr_t m_tohost_addr;
  Addr_t m_fromhost_addr;
  XLEN_t m_tohost;
  XLEN_t m_fromhost;

  RegAddr_t m_rs1;
  RegAddr_t m_rs2;
  RegAddr_t m_rd ;
  uint16_t  m_csr_addr;

  bool m_update_pc;
  bool m_finish_cpu;

#ifndef __SYNTHESIS__
  FILE *m_cpu_log;
#endif // __SYNTHESIS__

  XLEN_t mem_access (memtype_t op, uint32_t data, uint32_t addr, AccSize_t size);

  RegAddr_t get_rs1_addr (Inst_t inst) {
    return ((inst >> 15) & 0x1f);
  }
  RegAddr_t get_rs2_addr (Inst_t inst) {
    return ((inst >> 20) & 0x1f);
  }
  RegAddr_t get_rd_addr (Inst_t inst) {
    return ((inst >> 7) & 0x1f);
  }

  XLEN_t read_reg(RegAddr_t addr) {
    return m_reg32[addr];
  }

  void write_reg(RegAddr_t addr, XLEN_t data) {
    if (addr != 0) {
      m_reg32[addr] = data;
#ifndef __SYNTHESIS__
      fprintf(m_cpu_log, "x%02d <= %08x\n", addr, data);
#endif // _SYNTHESIS
    }
  }

  XLEN_t csrrw (uint16_t addr, XLEN_t data) {
    return m_rv32_csr.csrrw (addr, data);
  }
  XLEN_t csrrs (uint16_t addr, XLEN_t data) {
    return m_rv32_csr.csrrs (addr, data);
  }
  XLEN_t csrrc (uint16_t addr, XLEN_t data) {
    return m_rv32_csr.csrrc (addr, data);
  }

  // Utilitity for decoder
  XLEN_t ExtendSign (uint32_t data, uint32_t msb);
  XLEN_t ExtractBitField (Inst_t hex, uint32_t left, uint32_t right);
  XLEN_t ExtractUJField (Inst_t hex);
  XLEN_t ExtractIField (Inst_t hex);
  XLEN_t ExtractSBField (Inst_t hex);
  XLEN_t ExtractSField (Inst_t hex);
  XLEN_t ExtractSHAMTField (Inst_t hex);

  inline XLEN_t  SExtXlen (Inst_t hex) { return hex; }
  inline UXLEN_t UExtXlen (Inst_t hex) { return hex; }

public:
  rv32_cpu (uint8_t *data_mem, Addr_t tohost_addr, Addr_t fromhost_addr);

  void fetch_inst  ();
  void decode_inst ();
  void execute_inst();

  XLEN_t get_tohost   () { return m_tohost; }
  XLEN_t get_fromhost () { return m_fromhost; }

  Addr_t GetPC () { return m_pc; }

  bool is_finish_cpu() { return m_finish_cpu || (m_dec_inst == WFI); }
};
