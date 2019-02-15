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
  LW,  SW,
  JAL, JALR,
  BEQ, BNE, BLT, BGE, BLTU, BGEU,
  NOP,
  WFI
} inst_rv32_t;

typedef enum {
  LOAD = 0,
  STORE = 1
} memtype_t;

class rv32_cpu {
  Addr_t m_pc;

  Inst_t m_inst;
  inst_rv32_t m_dec_inst;

  XLEN_t m_reg32[32];
  rv32_csr m_rv32_csr;
  uint32_t *m_data_mem;

  RegAddr_t m_rs1;
  RegAddr_t m_rs2;
  RegAddr_t m_rd ;
  uint16_t  m_csr_addr;

  bool m_update_pc = false;

#ifndef __SYNTHESIS__
  FILE *m_cpu_log;
#endif // __SYNTHESIS__

  XLEN_t mem_access (memtype_t op, uint32_t data, uint32_t addr);

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
  uint32_t ExtendSign (uint32_t data, uint32_t msb);
  uint32_t ExtractBitField (uint32_t hex, uint32_t left, uint32_t right);
  uint32_t ExtractUJField (uint32_t hex);
  uint32_t ExtractIField (uint32_t hex);
  uint32_t ExtractSBField (uint32_t hex);

  inline XLEN_t  SExtXlen (uint32_t  hex) { return (hex << 32) >> 32; }
  inline uint32_t UExtXlen (uint32_t hex) { return (hex << 32) >> 32; }

public:
  rv32_cpu (uint32_t *data_mem);

  void fetch_inst  ();
  void decode_inst ();
  void execute_inst();

  bool is_finish_cpu() { return m_dec_inst == WFI; }
};
