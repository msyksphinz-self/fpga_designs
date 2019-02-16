#include "rv32_csr.hpp"

XLEN_t rv32_csr::csrrw (Addr_t addr, XLEN_t data)
{
  switch(addr) {
    case CsrAddr_mcycle    : return m_mcycle    .csrrw(data);
    case CsrAddr_minstret  : return m_minstret  .csrrw(data);
    case CsrAddr_mimpid    : return m_mimpid    .csrrw(data);
    case CsrAddr_marchid   : return m_marchid   .csrrw(data);
    case CsrAddr_mvendorid : return m_mvendorid .csrrw(data);
    case CsrAddr_misa      : return m_misa      .csrrw(data);
    case CsrAddr_mstatus   : return m_mstatus   .csrrw(data);
    case CsrAddr_mtvec     : return m_mtvec     .csrrw(data);
    case CsrAddr_mip       : return m_mip       .csrrw(data);
    case CsrAddr_mie       : return m_mie       .csrrw(data);
    case CsrAddr_mscratch  : return m_mscratch  .csrrw(data);
    case CsrAddr_mepc      : return m_mepc      .csrrw(data);
    case CsrAddr_mtval     : return m_mtval     .csrrw(data);
    case CsrAddr_mcause    : return m_mcause    .csrrw(data);
    case CsrAddr_mhartid   : return m_mhartid   .csrrw(data);
    case CsrAddr_dcsr      : return m_dcsr      .csrrw(data);
    case CsrAddr_dpc       : return m_dpc       .csrrw(data);
    case CsrAddr_dscratch  : return m_dscratch  .csrrw(data);
    case CsrAddr_medeleg   : return m_medeleg   .csrrw(data);
    default                : return 0x0;
  }
}


XLEN_t rv32_csr::csrrs (Addr_t addr, XLEN_t data)
{
  switch(addr) {
    case CsrAddr_mcycle    : return m_mcycle    .csrrs(data);
    case CsrAddr_minstret  : return m_minstret  .csrrs(data);
    case CsrAddr_mimpid    : return m_mimpid    .csrrs(data);
    case CsrAddr_marchid   : return m_marchid   .csrrs(data);
    case CsrAddr_mvendorid : return m_mvendorid .csrrs(data);
    case CsrAddr_misa      : return m_misa      .csrrs(data);
    case CsrAddr_mstatus   : return m_mstatus   .csrrs(data);
    case CsrAddr_mtvec     : return m_mtvec     .csrrs(data);
    case CsrAddr_mip       : return m_mip       .csrrs(data);
    case CsrAddr_mie       : return m_mie       .csrrs(data);
    case CsrAddr_mscratch  : return m_mscratch  .csrrs(data);
    case CsrAddr_mepc      : return m_mepc      .csrrs(data);
    case CsrAddr_mtval     : return m_mtval     .csrrs(data);
    case CsrAddr_mcause    : return m_mcause    .csrrs(data);
    case CsrAddr_mhartid   : return m_mhartid   .csrrs(data);
    case CsrAddr_dcsr      : return m_dcsr      .csrrs(data);
    case CsrAddr_dpc       : return m_dpc       .csrrs(data);
    case CsrAddr_dscratch  : return m_dscratch  .csrrs(data);
    case CsrAddr_medeleg   : return m_medeleg   .csrrs(data);
    default                : return 0x0;
  }
}


XLEN_t rv32_csr::csrrc (Addr_t addr, XLEN_t data)
{
  switch(addr) {
    case CsrAddr_mcycle    : return m_mcycle    .csrrc(data);
    case CsrAddr_minstret  : return m_minstret  .csrrc(data);
    case CsrAddr_mimpid    : return m_mimpid    .csrrc(data);
    case CsrAddr_marchid   : return m_marchid   .csrrc(data);
    case CsrAddr_mvendorid : return m_mvendorid .csrrc(data);
    case CsrAddr_misa      : return m_misa      .csrrc(data);
    case CsrAddr_mstatus   : return m_mstatus   .csrrc(data);
    case CsrAddr_mtvec     : return m_mtvec     .csrrc(data);
    case CsrAddr_mip       : return m_mip       .csrrc(data);
    case CsrAddr_mie       : return m_mie       .csrrc(data);
    case CsrAddr_mscratch  : return m_mscratch  .csrrc(data);
    case CsrAddr_mepc      : return m_mepc      .csrrc(data);
    case CsrAddr_mtval     : return m_mtval     .csrrc(data);
    case CsrAddr_mcause    : return m_mcause    .csrrc(data);
    case CsrAddr_mhartid   : return m_mhartid   .csrrc(data);
    case CsrAddr_dcsr      : return m_dcsr      .csrrc(data);
    case CsrAddr_dpc       : return m_dpc       .csrrc(data);
    case CsrAddr_dscratch  : return m_dscratch  .csrrc(data);
    case CsrAddr_medeleg   : return m_medeleg   .csrrc(data);
    default                : return 0x0;
  }
}
