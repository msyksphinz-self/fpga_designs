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
  CsrAddr_cycle          = 0xc00,
  CsrAddr_instret        = 0xc02,
  CsrAddr_hpmcounter3    = 0xc03,
  CsrAddr_hpmcounter4    = 0xc04,
  CsrAddr_hpmcounter5    = 0xc05,
  CsrAddr_hpmcounter6    = 0xc06,
  CsrAddr_hpmcounter7    = 0xc07,
  CsrAddr_hpmcounter8    = 0xc08,
  CsrAddr_hpmcounter9    = 0xc09,
  CsrAddr_hpmcounter10   = 0xc0a,
  CsrAddr_hpmcounter11   = 0xc0b,
  CsrAddr_hpmcounter12   = 0xc0c,
  CsrAddr_hpmcounter13   = 0xc0d,
  CsrAddr_hpmcounter14   = 0xc0e,
  CsrAddr_hpmcounter15   = 0xc0f,
  CsrAddr_hpmcounter16   = 0xc10,
  CsrAddr_hpmcounter17   = 0xc11,
  CsrAddr_hpmcounter18   = 0xc12,
  CsrAddr_hpmcounter19   = 0xc13,
  CsrAddr_hpmcounter20   = 0xc14,
  CsrAddr_hpmcounter21   = 0xc15,
  CsrAddr_hpmcounter22   = 0xc16,
  CsrAddr_hpmcounter23   = 0xc17,
  CsrAddr_hpmcounter24   = 0xc18,
  CsrAddr_hpmcounter25   = 0xc19,
  CsrAddr_hpmcounter26   = 0xc1a,
  CsrAddr_hpmcounter27   = 0xc1b,
  CsrAddr_hpmcounter28   = 0xc1c,
  CsrAddr_hpmcounter29   = 0xc1d,
  CsrAddr_hpmcounter30   = 0xc1e,
  CsrAddr_hpmcounter31   = 0xc1f,
  CsrAddr_mstatus        = 0x300,
  CsrAddr_misa           = 0x301,
  CsrAddr_medeleg        = 0x302,
  CsrAddr_mideleg        = 0x303,
  CsrAddr_mie            = 0x304,
  CsrAddr_mtvec          = 0x305,
  CsrAddr_mscratch       = 0x340,
  CsrAddr_mcounteren     = 0x306,
  CsrAddr_mepc           = 0x341,
  CsrAddr_mcause         = 0x342,
  CsrAddr_mtval          = 0x343,
  CsrAddr_mip            = 0x344,
  CsrAddr_tselect        = 0x7a0,
  CsrAddr_tdata1         = 0x7a1,
  CsrAddr_tdata2         = 0x7a2,
  CsrAddr_tdata3         = 0x7a3,
  CsrAddr_dcsr           = 0x7b0,
  CsrAddr_dpc            = 0x7b1,
  CsrAddr_dscratch       = 0x7b2,
  CsrAddr_mcycle         = 0xb00,
  CsrAddr_minstret       = 0xb02,
  CsrAddr_mhpmcounter3   = 0xb03,
  CsrAddr_mhpmcounter4   = 0xb04,
  CsrAddr_mhpmcounter5   = 0xb05,
  CsrAddr_mhpmcounter6   = 0xb06,
  CsrAddr_mhpmcounter7   = 0xb07,
  CsrAddr_mhpmcounter8   = 0xb08,
  CsrAddr_mhpmcounter9   = 0xb09,
  CsrAddr_mhpmcounter10  = 0xb0a,
  CsrAddr_mhpmcounter11  = 0xb0b,
  CsrAddr_mhpmcounter12  = 0xb0c,
  CsrAddr_mhpmcounter13  = 0xb0d,
  CsrAddr_mhpmcounter14  = 0xb0e,
  CsrAddr_mhpmcounter15  = 0xb0f,
  CsrAddr_mhpmcounter16  = 0xb10,
  CsrAddr_mhpmcounter17  = 0xb11,
  CsrAddr_mhpmcounter18  = 0xb12,
  CsrAddr_mhpmcounter19  = 0xb13,
  CsrAddr_mhpmcounter20  = 0xb14,
  CsrAddr_mhpmcounter21  = 0xb15,
  CsrAddr_mhpmcounter22  = 0xb16,
  CsrAddr_mhpmcounter23  = 0xb17,
  CsrAddr_mhpmcounter24  = 0xb18,
  CsrAddr_mhpmcounter25  = 0xb19,
  CsrAddr_mhpmcounter26  = 0xb1a,
  CsrAddr_mhpmcounter27  = 0xb1b,
  CsrAddr_mhpmcounter28  = 0xb1c,
  CsrAddr_mhpmcounter29  = 0xb1d,
  CsrAddr_mhpmcounter30  = 0xb1e,
  CsrAddr_mhpmcounter31  = 0xb1f,
  CsrAddr_mucounteren    = 0x320,
  CsrAddr_mhpmevent3     = 0x323,
  CsrAddr_mhpmevent4     = 0x324,
  CsrAddr_mhpmevent5     = 0x325,
  CsrAddr_mhpmevent6     = 0x326,
  CsrAddr_mhpmevent7     = 0x327,
  CsrAddr_mhpmevent8     = 0x328,
  CsrAddr_mhpmevent9     = 0x329,
  CsrAddr_mhpmevent10    = 0x32a,
  CsrAddr_mhpmevent11    = 0x32b,
  CsrAddr_mhpmevent12    = 0x32c,
  CsrAddr_mhpmevent13    = 0x32d,
  CsrAddr_mhpmevent14    = 0x32e,
  CsrAddr_mhpmevent15    = 0x32f,
  CsrAddr_mhpmevent16    = 0x330,
  CsrAddr_mhpmevent17    = 0x331,
  CsrAddr_mhpmevent18    = 0x332,
  CsrAddr_mhpmevent19    = 0x333,
  CsrAddr_mhpmevent20    = 0x334,
  CsrAddr_mhpmevent21    = 0x335,
  CsrAddr_mhpmevent22    = 0x336,
  CsrAddr_mhpmevent23    = 0x337,
  CsrAddr_mhpmevent24    = 0x338,
  CsrAddr_mhpmevent25    = 0x339,
  CsrAddr_mhpmevent26    = 0x33a,
  CsrAddr_mhpmevent27    = 0x33b,
  CsrAddr_mhpmevent28    = 0x33c,
  CsrAddr_mhpmevent29    = 0x33d,
  CsrAddr_mhpmevent30    = 0x33e,
  CsrAddr_mhpmevent31    = 0x33f,
  CsrAddr_mvendorid      = 0xf11,
  CsrAddr_marchid        = 0xf12,
  CsrAddr_mimpid         = 0xf13,
  CsrAddr_mhartid        = 0xf14,
  CsrAddr_cycleh         = 0xc80,
  CsrAddr_instreth       = 0xc82,
  CsrAddr_hpmcounter3h   = 0xc83,
  CsrAddr_hpmcounter4h   = 0xc84,
  CsrAddr_hpmcounter5h   = 0xc85,
  CsrAddr_hpmcounter6h   = 0xc86,
  CsrAddr_hpmcounter7h   = 0xc87,
  CsrAddr_hpmcounter8h   = 0xc88,
  CsrAddr_hpmcounter9h   = 0xc89,
  CsrAddr_hpmcounter10h  = 0xc8a,
  CsrAddr_hpmcounter11h  = 0xc8b,
  CsrAddr_hpmcounter12h  = 0xc8c,
  CsrAddr_hpmcounter13h  = 0xc8d,
  CsrAddr_hpmcounter14h  = 0xc8e,
  CsrAddr_hpmcounter15h  = 0xc8f,
  CsrAddr_hpmcounter16h  = 0xc90,
  CsrAddr_hpmcounter17h  = 0xc91,
  CsrAddr_hpmcounter18h  = 0xc92,
  CsrAddr_hpmcounter19h  = 0xc93,
  CsrAddr_hpmcounter20h  = 0xc94,
  CsrAddr_hpmcounter21h  = 0xc95,
  CsrAddr_hpmcounter22h  = 0xc96,
  CsrAddr_hpmcounter23h  = 0xc97,
  CsrAddr_hpmcounter24h  = 0xc98,
  CsrAddr_hpmcounter25h  = 0xc99,
  CsrAddr_hpmcounter26h  = 0xc9a,
  CsrAddr_hpmcounter27h  = 0xc9b,
  CsrAddr_hpmcounter28h  = 0xc9c,
  CsrAddr_hpmcounter29h  = 0xc9d,
  CsrAddr_hpmcounter30h  = 0xc9e,
  CsrAddr_hpmcounter31h  = 0xc9f,
  CsrAddr_mcycleh        = 0xb80,
  CsrAddr_minstreth      = 0xb82,
  CsrAddr_mhpmcounter3h  = 0xb83,
  CsrAddr_mhpmcounter4h  = 0xb84,
  CsrAddr_mhpmcounter5h  = 0xb85,
  CsrAddr_mhpmcounter6h  = 0xb86,
  CsrAddr_mhpmcounter7h  = 0xb87,
  CsrAddr_mhpmcounter8h  = 0xb88,
  CsrAddr_mhpmcounter9h  = 0xb89,
  CsrAddr_mhpmcounter10h = 0xb8a,
  CsrAddr_mhpmcounter11h = 0xb8b,
  CsrAddr_mhpmcounter12h = 0xb8c,
  CsrAddr_mhpmcounter13h = 0xb8d,
  CsrAddr_mhpmcounter14h = 0xb8e,
  CsrAddr_mhpmcounter15h = 0xb8f,
  CsrAddr_mhpmcounter16h = 0xb90,
  CsrAddr_mhpmcounter17h = 0xb91,
  CsrAddr_mhpmcounter18h = 0xb92,
  CsrAddr_mhpmcounter19h = 0xb93,
  CsrAddr_mhpmcounter20h = 0xb94,
  CsrAddr_mhpmcounter21h = 0xb95,
  CsrAddr_mhpmcounter22h = 0xb96,
  CsrAddr_mhpmcounter23h = 0xb97,
  CsrAddr_mhpmcounter24h = 0xb98,
  CsrAddr_mhpmcounter25h = 0xb99,
  CsrAddr_mhpmcounter26h = 0xb9a,
  CsrAddr_mhpmcounter27h = 0xb9b,
  CsrAddr_mhpmcounter28h = 0xb9c,
  CsrAddr_mhpmcounter29h = 0xb9d,
  CsrAddr_mhpmcounter30h = 0xb9e,
  CsrAddr_mhpmcounter31h = 0xb9f
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
