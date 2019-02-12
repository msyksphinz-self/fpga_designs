#include <stdint.h>

typedef enum {
  LW = 0,
  SW,
  ADD,
  NOP,
  WFI
} inst_rv32_t;

typedef enum {
  LOAD = 0,
  STORE = 1
} memtype_t;

class rv32_cpu {
  typedef uint32_t XLEN_t   ;
  typedef uint8_t  RegAddr_t;
  typedef uint32_t INST_t   ;

  XLEN_t m_reg32[32];

  uint32_t *m_data_mem;

public:
  rv32_cpu (uint32_t *data_mem);

  XLEN_t mem_access (memtype_t op, uint32_t data, uint32_t addr, uint32_t *data_mem);

  inst_rv32_t decode_inst (INST_t inst);

  RegAddr_t get_rs1_addr (INST_t inst) {
    return ((inst >> 15) & 0x1f);
  }
  RegAddr_t get_rs2_addr (INST_t inst) {
    return ((inst >> 20) & 0x1f);
  }
  RegAddr_t get_rd_addr (INST_t inst) {
    return ((inst >> 7) & 0x1f);
  }

  XLEN_t read_reg(RegAddr_t addr) {
    return m_reg32[addr];
  }

  void write_reg(RegAddr_t addr, XLEN_t data) {
    m_reg32[addr] = data;
  }
};
