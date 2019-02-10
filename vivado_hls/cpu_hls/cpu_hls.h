#ifndef __CPU_HLS__
#define __CPU_HLS__

void cpu_hls (const uint32_t inst_mem[1024], uint32_t data_mem[1024]);

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

class rv32 {
  uint32_t reg32[32];

public:
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
    return reg32[addr];
  }

  void write_reg(uint8_t addr, uint32_t data) {
    reg32[addr] = data;
  }
};


#endif // __CPU_HLS__
