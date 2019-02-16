#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "rv32_cpu.hpp"
#include "cpu_hls.h"

XLEN_t cpu_hls (uint32_t mem[8192])
{
  rv32_cpu u_rv32_cpu (mem, 0x1000, 0x1004);

  do {
    u_rv32_cpu.fetch_inst();
    u_rv32_cpu.decode_inst();
    u_rv32_cpu.execute_inst();
  } while (!u_rv32_cpu.is_finish_cpu());

  return u_rv32_cpu.get_tohost();
}
