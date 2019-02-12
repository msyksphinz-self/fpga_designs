#include <math.h>
#include <stdint.h>

#include "rv32_cpu.hpp"
#include "cpu_hls.h"

void cpu_hls (const uint32_t inst_mem[1024], uint32_t data_mem[1024])
{
  int y, x;

  uint32_t addr = 0;
  uint32_t inst;
  inst_rv32_t dec_inst;

  rv32_cpu u_rv32_cpu (data_mem);

  do {
    inst = inst_mem[addr];
    dec_inst = u_rv32_cpu.decode_inst(inst);

    uint32_t reg_data;

    uint8_t rs1 = u_rv32_cpu.get_rs1_addr (inst);
    uint8_t rs2 = u_rv32_cpu.get_rs2_addr (inst);
    uint8_t rd  = u_rv32_cpu.get_rd_addr  (inst);

    switch (dec_inst) {
      case LW  : {
        uint32_t addr = rs1 + ((inst >> 20) & 0xfff);
        reg_data = u_rv32_cpu.mem_access(LOAD, rs1, addr, data_mem);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case ADD : {
        reg_data = u_rv32_cpu.read_reg(rs1) + u_rv32_cpu.read_reg(rs2);
        u_rv32_cpu.write_reg(rd, reg_data);
        break;
      }
      case SW  : {
        uint32_t addr = rs1 + ((inst >> 25) + ((inst >> 7) &0x1f));
        reg_data = u_rv32_cpu.read_reg(rs1);
        u_rv32_cpu.mem_access(STORE, rs2, addr, data_mem);
        break;
      }
      default  : break;
    }
  } while (dec_inst == WFI);

  return;
}
