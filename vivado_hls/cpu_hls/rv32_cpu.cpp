#include "stdio.h"

#include "rv32_cpu.hpp"


rv32_cpu::rv32_cpu(uint32_t *data_mem)
    : m_data_mem(data_mem)
{}

inst_rv32_t rv32_cpu::decode_inst (uint32_t inst)
{
  switch(inst & 0x7f) {
    case 0x33 : {
      switch ((inst >> 12) & 0x07) {
        case 0b000 : {
          if      (((inst >> 25) & 0x7f) == 0b0000000) { return ADD; }
          else if (((inst >> 25) & 0x7f) == 0b0100000) { return SUB; }
          else                                       { return NOP; }
        }
        case 0b001 : return SLL;
        case 0b010 : return SLT;
        case 0b011 : return SLTU;
        case 0b100 : return XOR;
        case 0b101 : {
          if      (((inst >> 25) & 0x7f) == 0b0000000) { return SRL; }
          else if (((inst >> 25) & 0x7f) == 0b0100000) { return SRA; }
          else                                       { return NOP; }
        }
        case 0b110 : return OR;
        case 0b111 : return AND;
        default    : return NOP;
      }
    }
    case 0x03 : return LW;
    case 0x23 : return SW;
    case 0x37 : return LUI;
    case 0x17 : return AUIPC;
    case 0x63 : {
      switch ((inst >> 12) & 0x07) {
        case 0b000 : return BEQ;
        case 0b001 : return BNE;
        case 0b100 : return BLT;
        case 0b101 : return BGE;
        case 0b110 : return BLTU;
        case 0b111 : return BGEU;
        default    : return NOP;
      }
    }
    case 0x13 : {
      switch ((inst >> 12) & 0x07) {
        case 0b000 : return ADDI;
        case 0b010 : return SLTI;
        case 0b011 : return SLTIU;
        case 0b100 : return XORI;
        case 0b110 : return ORI;
        case 0b111 : return ANDI;
        default    : return NOP;
      }
    }
    case 0x6f : return JAL;
    case 0x67 : return JALR;
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


XLEN_t rv32_cpu::mem_access (memtype_t op, uint32_t data, uint32_t addr, uint32_t *data_mem)
{
  switch (op) {
    case STORE : data_mem[addr] = data; break;
    case LOAD  : return data_mem[addr]; break;
  }
  return 0;
}


uint32_t rv32_cpu::ExtendSign (uint32_t data, uint32_t msb)
{

  int const mask = 1ULL << msb; // mask can be pre-computed if b is fixed

  data = data & ((1ULL << (msb + 1)) - 1);  // (Skip this if bits in x above position b are already zero.)
  return (data ^ mask) - mask;
}


uint32_t rv32_cpu::ExtractBitField (uint32_t hex, uint32_t left, uint32_t right)
{
  uint32_t mask = (static_cast<uint32_t>(1) << (left - right + 1)) - 1;
  return (hex >> right) & mask;
}


uint32_t rv32_cpu::ExtractUJField (uint32_t hex)
{
  uint32_t i24_21 = ExtractBitField (hex, 24, 21) & 0x0fUL;
  uint32_t i30_25 = ExtractBitField (hex, 30, 25) & 0x03fUL;
  uint32_t i20_20 = ExtractBitField (hex, 20, 20) & 0x01UL;
  uint32_t i19_12 = ExtractBitField (hex, 19, 12) & 0x0ffUL;
  uint32_t i31_31 = ExtractBitField (hex, 31, 31) & 0x01UL;

  uint32_t u_res = (i31_31 << 20) |
           (i19_12 << 12) |
           (i20_20 << 11) |
           (i30_25 <<  5) |
           (i24_21 <<  1);
  return ExtendSign (u_res, 20);
}


uint32_t rv32_cpu::ExtractIField (uint32_t hex)
{
  uint32_t uimm32 = ExtractBitField (hex, 31, 20);
  return ExtendSign (uimm32, 11);
}


uint32_t rv32_cpu::ExtractSBField (uint32_t hex)
{
  uint32_t i07_07 = ExtractBitField (hex,  7,  7) & 0x01UL;
  uint32_t i11_08 = ExtractBitField (hex, 11,  8) & 0x0fUL;
  uint32_t i30_25 = ExtractBitField (hex, 30, 25) & 0x03fUL;
  uint32_t i31_31 = ExtractBitField (hex, 31, 31) & 0x01UL;

  uint32_t u_res = (i31_31 << 12) |
           (i07_07 << 11) |
           (i30_25 <<  5) |
           (i11_08 <<  1);
  return ExtendSign (u_res, 12);
}
