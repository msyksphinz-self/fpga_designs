#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "rv32_cpu.hpp"
#include "cpu_hls.h"

uint32_t cpu_hls (XLEN_t mem[MEMORY_SIZE])
{
#pragma HLS INTERFACE m_axi port=mem bundle=mem
  rv32_cpu u_rv32_cpu (mem, 0x1000, 0x1004);
  uint32_t test_counter = 0;

  L0:do {
    test_counter ++;
    u_rv32_cpu.fetch_inst();
    u_rv32_cpu.decode_inst();
    u_rv32_cpu.execute_inst();
  } while (!u_rv32_cpu.is_finish_cpu() && test_counter < 5000);

  return u_rv32_cpu.get_tohost();
}
