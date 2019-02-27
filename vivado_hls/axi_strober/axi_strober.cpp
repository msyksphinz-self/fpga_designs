#include <math.h>
#include <stdint.h>

void axi_strober (uint8_t *master_mem)
{
#pragma HLS INTERFACE m_axi port=master_mem bundle=mem
  for (int i = 0; i < 100; i++) {
    master_mem[i] = i;
  }

  // uint16_t *master_mem16 = (uint16_t *)master_mem;
  // for (int i = 0; i < 100; i++) {
  //   master_mem16[i] = i;
  // }

  uint64_t *master_mem64 = (uint64_t *)master_mem;
  for (int i = 0; i < 20; i++) {
    master_mem64[i] = (i << 24) | (i << 16) | (i << 8) | (i << 0);
  }

  return;
}
