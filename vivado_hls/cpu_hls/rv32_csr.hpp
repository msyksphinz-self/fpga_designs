#pragma once

#include "rv32_basic.hpp"

class rv32_csr_base {
 private:
  XLEN_t m_csr;
 public:
  rv32_csr_base (XLEN_t imm)
      : m_csr(imm) {}
  rv32_csr_base ()
      : m_csr(0) {}

  XLEN_t csrrw (XLEN_t imm) {
    XLEN_t ret_val = m_csr;
    m_csr = imm;
    return ret_val;
  }

  XLEN_t csrrs (XLEN_t imm) {
    XLEN_t ret_val = m_csr;
    m_csr = m_csr | imm;
    return ret_val;
  }

  XLEN_t csrrc (XLEN_t imm) {
    XLEN_t ret_val = m_csr;
    m_csr = m_csr & ~imm;
    return ret_val;
  }

};


typedef enum {
  cycle          = 0xc00,
  instret        = 0xc02,
  hpmcounter3    = 0xc03,
  hpmcounter4    = 0xc04,
  hpmcounter5    = 0xc05,
  hpmcounter6    = 0xc06,
  hpmcounter7    = 0xc07,
  hpmcounter8    = 0xc08,
  hpmcounter9    = 0xc09,
  hpmcounter10   = 0xc0a,
  hpmcounter11   = 0xc0b,
  hpmcounter12   = 0xc0c,
  hpmcounter13   = 0xc0d,
  hpmcounter14   = 0xc0e,
  hpmcounter15   = 0xc0f,
  hpmcounter16   = 0xc10,
  hpmcounter17   = 0xc11,
  hpmcounter18   = 0xc12,
  hpmcounter19   = 0xc13,
  hpmcounter20   = 0xc14,
  hpmcounter21   = 0xc15,
  hpmcounter22   = 0xc16,
  hpmcounter23   = 0xc17,
  hpmcounter24   = 0xc18,
  hpmcounter25   = 0xc19,
  hpmcounter26   = 0xc1a,
  hpmcounter27   = 0xc1b,
  hpmcounter28   = 0xc1c,
  hpmcounter29   = 0xc1d,
  hpmcounter30   = 0xc1e,
  hpmcounter31   = 0xc1f,
  mstatus        = 0x300,
  misa           = 0x301,
  medeleg        = 0x302,
  mideleg        = 0x303,
  mie            = 0x304,
  mtvec          = 0x305,
  mscratch       = 0x340,
  mcounteren     = 0x306,
  mepc           = 0x341,
  mcause         = 0x342,
  mtval          = 0x343,
  mip            = 0x344,
  tselect        = 0x7a0,
  tdata1         = 0x7a1,
  tdata2         = 0x7a2,
  tdata3         = 0x7a3,
  dcsr           = 0x7b0,
  dpc            = 0x7b1,
  dscratch       = 0x7b2,
  mcycle         = 0xb00,
  minstret       = 0xb02,
  mhpmcounter3   = 0xb03,
  mhpmcounter4   = 0xb04,
  mhpmcounter5   = 0xb05,
  mhpmcounter6   = 0xb06,
  mhpmcounter7   = 0xb07,
  mhpmcounter8   = 0xb08,
  mhpmcounter9   = 0xb09,
  mhpmcounter10  = 0xb0a,
  mhpmcounter11  = 0xb0b,
  mhpmcounter12  = 0xb0c,
  mhpmcounter13  = 0xb0d,
  mhpmcounter14  = 0xb0e,
  mhpmcounter15  = 0xb0f,
  mhpmcounter16  = 0xb10,
  mhpmcounter17  = 0xb11,
  mhpmcounter18  = 0xb12,
  mhpmcounter19  = 0xb13,
  mhpmcounter20  = 0xb14,
  mhpmcounter21  = 0xb15,
  mhpmcounter22  = 0xb16,
  mhpmcounter23  = 0xb17,
  mhpmcounter24  = 0xb18,
  mhpmcounter25  = 0xb19,
  mhpmcounter26  = 0xb1a,
  mhpmcounter27  = 0xb1b,
  mhpmcounter28  = 0xb1c,
  mhpmcounter29  = 0xb1d,
  mhpmcounter30  = 0xb1e,
  mhpmcounter31  = 0xb1f,
  mucounteren    = 0x320,
  mhpmevent3     = 0x323,
  mhpmevent4     = 0x324,
  mhpmevent5     = 0x325,
  mhpmevent6     = 0x326,
  mhpmevent7     = 0x327,
  mhpmevent8     = 0x328,
  mhpmevent9     = 0x329,
  mhpmevent10    = 0x32a,
  mhpmevent11    = 0x32b,
  mhpmevent12    = 0x32c,
  mhpmevent13    = 0x32d,
  mhpmevent14    = 0x32e,
  mhpmevent15    = 0x32f,
  mhpmevent16    = 0x330,
  mhpmevent17    = 0x331,
  mhpmevent18    = 0x332,
  mhpmevent19    = 0x333,
  mhpmevent20    = 0x334,
  mhpmevent21    = 0x335,
  mhpmevent22    = 0x336,
  mhpmevent23    = 0x337,
  mhpmevent24    = 0x338,
  mhpmevent25    = 0x339,
  mhpmevent26    = 0x33a,
  mhpmevent27    = 0x33b,
  mhpmevent28    = 0x33c,
  mhpmevent29    = 0x33d,
  mhpmevent30    = 0x33e,
  mhpmevent31    = 0x33f,
  mvendorid      = 0xf11,
  marchid        = 0xf12,
  mimpid         = 0xf13,
  mhartid        = 0xf14,
  cycleh         = 0xc80,
  instreth       = 0xc82,
  hpmcounter3h   = 0xc83,
  hpmcounter4h   = 0xc84,
  hpmcounter5h   = 0xc85,
  hpmcounter6h   = 0xc86,
  hpmcounter7h   = 0xc87,
  hpmcounter8h   = 0xc88,
  hpmcounter9h   = 0xc89,
  hpmcounter10h  = 0xc8a,
  hpmcounter11h  = 0xc8b,
  hpmcounter12h  = 0xc8c,
  hpmcounter13h  = 0xc8d,
  hpmcounter14h  = 0xc8e,
  hpmcounter15h  = 0xc8f,
  hpmcounter16h  = 0xc90,
  hpmcounter17h  = 0xc91,
  hpmcounter18h  = 0xc92,
  hpmcounter19h  = 0xc93,
  hpmcounter20h  = 0xc94,
  hpmcounter21h  = 0xc95,
  hpmcounter22h  = 0xc96,
  hpmcounter23h  = 0xc97,
  hpmcounter24h  = 0xc98,
  hpmcounter25h  = 0xc99,
  hpmcounter26h  = 0xc9a,
  hpmcounter27h  = 0xc9b,
  hpmcounter28h  = 0xc9c,
  hpmcounter29h  = 0xc9d,
  hpmcounter30h  = 0xc9e,
  hpmcounter31h  = 0xc9f,
  mcycleh        = 0xb80,
  minstreth      = 0xb82,
  mhpmcounter3h  = 0xb83,
  mhpmcounter4h  = 0xb84,
  mhpmcounter5h  = 0xb85,
  mhpmcounter6h  = 0xb86,
  mhpmcounter7h  = 0xb87,
  mhpmcounter8h  = 0xb88,
  mhpmcounter9h  = 0xb89,
  mhpmcounter10h = 0xb8a,
  mhpmcounter11h = 0xb8b,
  mhpmcounter12h = 0xb8c,
  mhpmcounter13h = 0xb8d,
  mhpmcounter14h = 0xb8e,
  mhpmcounter15h = 0xb8f,
  mhpmcounter16h = 0xb90,
  mhpmcounter17h = 0xb91,
  mhpmcounter18h = 0xb92,
  mhpmcounter19h = 0xb93,
  mhpmcounter20h = 0xb94,
  mhpmcounter21h = 0xb95,
  mhpmcounter22h = 0xb96,
  mhpmcounter23h = 0xb97,
  mhpmcounter24h = 0xb98,
  mhpmcounter25h = 0xb99,
  mhpmcounter26h = 0xb9a,
  mhpmcounter27h = 0xb9b,
  mhpmcounter28h = 0xb9c,
  mhpmcounter29h = 0xb9d,
  mhpmcounter30h = 0xb9e,
  mhpmcounter31h = 0xb9f
} CsrAddr;

class rv32_csr {
 private :

  rv32_csr_base m_mcycle      ;
  rv32_csr_base m_minstret    ;
  rv32_csr_base m_mimpid      ;
  rv32_csr_base m_marchid     ;
  rv32_csr_base m_mvendorid   ;
  rv32_csr_base m_misa        ;
  rv32_csr_base m_mstatus     ;
  rv32_csr_base m_mtvec       ;
  rv32_csr_base m_mip         ;
  rv32_csr_base m_mie         ;
  rv32_csr_base m_mscratch    ;
  rv32_csr_base m_mepc        ;
  rv32_csr_base m_mtval       ;
  rv32_csr_base m_mcause      ;
  rv32_csr_base m_mhartid     ;
  rv32_csr_base m_dcsr        ;
  rv32_csr_base m_dpc         ;
  rv32_csr_base m_dscratch    ;
  rv32_csr_base m_medeleg     ;

 public:
  XLEN_t csrrw (Addr_t addr, XLEN_t data);
  XLEN_t csrrs (Addr_t addr, XLEN_t data);
  XLEN_t csrrc (Addr_t addr, XLEN_t data);
};
