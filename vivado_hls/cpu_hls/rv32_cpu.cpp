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
    case 0x73 :
      switch ((inst >> 12) & 0x07) {
        case 0b001 : return CSRRW  ;
        case 0b010 : return CSRRS  ;
        case 0b011 : return CSRRC  ;
        case 0b101 : return CSRRWI ;
        case 0b110 : return CSRRSI ;
        case 0b111 : return CSRRCI ;
        default    : return NOP    ;
      }
    default   : return WFI;
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
