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
  uint32_t m_reg32[32];

  uint32_t *m_data_mem;

public:
  rv32_cpu (uint32_t *data_mem);

  uint32_t mem_access (memtype_t op, uint32_t data, uint32_t addr, uint32_t *data_mem);

  inst_rv32_t decode_inst (uint32_t inst);

  uint8_t get_rs1_addr (uint32_t inst) {
    return ((inst >> 15) & 0x1f);
  }
  uint8_t get_rs2_addr (uint32_t inst) {
    return ((inst >> 20) & 0x1f);
  }
  uint8_t get_rd_addr (uint32_t inst) {
    return ((inst >> 7) & 0x1f);
  }

  uint32_t read_reg(uint8_t addr) {
    return m_reg32[addr];
  }

  void write_reg(uint8_t addr, uint32_t data) {
    m_reg32[addr] = data;
  }
};
