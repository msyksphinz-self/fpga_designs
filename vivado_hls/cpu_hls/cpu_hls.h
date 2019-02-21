#ifndef __CPU_HLS__
#define __CPU_HLS__

#include "rv32_cpu.hpp"

#define MEMORY_SIZE (65536)

XLEN_t cpu_hls (uint32_t mem[MEMORY_SIZE]);

#endif // __CPU_HLS__
