#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "rv32_cpu.hpp"
#include "cpu_hls.h"

void cpu_hls (const uint32_t inst_mem[8192], uint32_t data_mem[8192])
{
  rv32_cpu u_rv32_cpu (data_mem);

  do {
    u_rv32_cpu.fetch_inst();
    u_rv32_cpu.decode_inst();
    u_rv32_cpu.execute_inst();
  } while (!u_rv32_cpu.is_finish_cpu());

  return;
}
