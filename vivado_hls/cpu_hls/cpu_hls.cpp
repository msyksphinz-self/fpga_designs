#include <math.h>
#include <stdint.h>
#include "cpu_hls.h"

uint32_t mem_access (memtype_t op, uint32_t data, uint32_t addr, uint32_t *data_mem)
{
  switch (op) {
    case STORE : data_mem[addr] = data; break;
    case LOAD  : return data_mem[addr]; break;
  }
  return 0;
}


void cpu_hls (const uint32_t inst_mem[1024], uint32_t data_mem[1024])
{
  int y, x;

  uint32_t addr = 0;
  uint32_t inst;
  inst_rv32_t dec_inst;

  rv32 u_rv32;

  do {
    inst = inst_mem[addr];
    dec_inst = u_rv32.decode_inst(inst);

    uint32_t reg_data;

    uint8_t rs1 = u_rv32.get_rs1_addr (inst);
    uint8_t rs2 = u_rv32.get_rs2_addr (inst);
    uint8_t rd  = u_rv32.get_rd_addr  (inst);

    switch (dec_inst) {
      case LW  : {
        uint32_t addr = rs1 + ((inst >> 20) & 0xfff);
        reg_data = mem_access(LOAD, rs1, addr, data_mem);
        u_rv32.write_reg(rd, reg_data);
        break;
      }
      case ADD : {
        reg_data = u_rv32.read_reg(rs1) + u_rv32.read_reg(rs2);
        u_rv32.write_reg(rd, reg_data);
        break;
      }
      case SW  : {
        uint32_t addr = rs1 + ((inst >> 25) + ((inst >> 7) &0x1f));
        reg_data = u_rv32.read_reg(rs1);
        mem_access(STORE, rs2, addr, data_mem);
        break;
      }
      default  : break;
    }
  } while (dec_inst == WFI);

  return;
}


inst_rv32_t rv32::decode_inst (uint32_t inst)
{
  switch(inst & 0x3f) {
    case 0x33 : return ADD;
    case 0x03 : return LW;
    case 0x23 : return SW;
    case 0xff : return NOP;   //
    default   : return NOP;
  }
}
