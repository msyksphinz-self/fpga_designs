#include "stdio.h"

#include "rv32_cpu.hpp"


rv32_cpu::rv32_cpu(uint32_t *data_mem)
    : m_data_mem(data_mem)
{}

inst_rv32_t rv32_cpu::decode_inst (uint32_t inst)
{
  switch(inst & 0x3f) {
    case 0x33 : return ADD;
    case 0x03 : return LW;
    case 0x23 : return SW;
    case 0xff : return NOP;   //
    default   : return NOP;
  }
}


uint32_t rv32_cpu::mem_access (memtype_t op, uint32_t data, uint32_t addr, uint32_t *data_mem)
{
  switch (op) {
    case STORE : data_mem[addr] = data; break;
    case LOAD  : return data_mem[addr]; break;
  }
  return 0;
}
