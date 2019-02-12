#include "rv32_csr.hpp"

XLEN_t rv32_csr::csrrw (Addr_t addr, XLEN_t data)
{
  switch(addr) {
    case mcycle    : return m_mcycle    .csrrw(data);
    case minstret  : return m_minstret  .csrrw(data);
    case mimpid    : return m_mimpid    .csrrw(data);
    case marchid   : return m_marchid   .csrrw(data);
    case mvendorid : return m_mvendorid .csrrw(data);
    case misa      : return m_misa      .csrrw(data);
    case mstatus   : return m_mstatus   .csrrw(data);
    case mtvec     : return m_mtvec     .csrrw(data);
    case mip       : return m_mip       .csrrw(data);
    case mie       : return m_mie       .csrrw(data);
    case mscratch  : return m_mscratch  .csrrw(data);
    case mepc      : return m_mepc      .csrrw(data);
    case mtval     : return m_mtval     .csrrw(data);
    case mcause    : return m_mcause    .csrrw(data);
    case mhartid   : return m_mhartid   .csrrw(data);
    case dcsr      : return m_dcsr      .csrrw(data);
    case dpc       : return m_dpc       .csrrw(data);
    case dscratch  : return m_dscratch  .csrrw(data);
    case medeleg   : return m_medeleg   .csrrw(data);
    default        : return 0x0;
  }
}


XLEN_t rv32_csr::csrrs (Addr_t addr, XLEN_t data)
{
  switch(addr) {
    case mcycle    : return m_mcycle    .csrrs(data);
    case minstret  : return m_minstret  .csrrs(data);
    case mimpid    : return m_mimpid    .csrrs(data);
    case marchid   : return m_marchid   .csrrs(data);
    case mvendorid : return m_mvendorid .csrrs(data);
    case misa      : return m_misa      .csrrs(data);
    case mstatus   : return m_mstatus   .csrrs(data);
    case mtvec     : return m_mtvec     .csrrs(data);
    case mip       : return m_mip       .csrrs(data);
    case mie       : return m_mie       .csrrs(data);
    case mscratch  : return m_mscratch  .csrrs(data);
    case mepc      : return m_mepc      .csrrs(data);
    case mtval     : return m_mtval     .csrrs(data);
    case mcause    : return m_mcause    .csrrs(data);
    case mhartid   : return m_mhartid   .csrrs(data);
    case dcsr      : return m_dcsr      .csrrs(data);
    case dpc       : return m_dpc       .csrrs(data);
    case dscratch  : return m_dscratch  .csrrs(data);
    case medeleg   : return m_medeleg   .csrrs(data);
    default        : return 0x0;
  }
}


XLEN_t rv32_csr::csrrc (Addr_t addr, XLEN_t data)
{
  switch(addr) {
    case mcycle    : return m_mcycle    .csrrc(data);
    case minstret  : return m_minstret  .csrrc(data);
    case mimpid    : return m_mimpid    .csrrc(data);
    case marchid   : return m_marchid   .csrrc(data);
    case mvendorid : return m_mvendorid .csrrc(data);
    case misa      : return m_misa      .csrrc(data);
    case mstatus   : return m_mstatus   .csrrc(data);
    case mtvec     : return m_mtvec     .csrrc(data);
    case mip       : return m_mip       .csrrc(data);
    case mie       : return m_mie       .csrrc(data);
    case mscratch  : return m_mscratch  .csrrc(data);
    case mepc      : return m_mepc      .csrrc(data);
    case mtval     : return m_mtval     .csrrc(data);
    case mcause    : return m_mcause    .csrrc(data);
    case mhartid   : return m_mhartid   .csrrc(data);
    case dcsr      : return m_dcsr      .csrrc(data);
    case dpc       : return m_dpc       .csrrc(data);
    case dscratch  : return m_dscratch  .csrrc(data);
    case medeleg   : return m_medeleg   .csrrc(data);
    default        : return 0x0;
  }
}
