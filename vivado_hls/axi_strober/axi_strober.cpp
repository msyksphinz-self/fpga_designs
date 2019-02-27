#include <stdint.h>

void axi_strober (uint32_t *memory)
{
  for (int i = 0; i < 128; i++) {
    memory[i] = i;
  }

  // uint16_t *memory16 = (uint16_t *)memory;
  // for (int i = 0; i < 100; i++) {
  //   memory16[i] = i;
  // }

  // uint64_t *memory64 = (uint64_t *)memory;
  // for (int i = 0; i < 20; i+=8) {
  //   memory[i + 0] = (i <<  0);
  //   memory[i + 1] = (i <<  8);
  //   memory[i + 2] = (i << 16);
  //   memory[i + 3] = (i << 24);
  //   memory[i + 4] = 0;
  //   memory[i + 5] = 0;
  //   memory[i + 6] = 0;
  //   memory[i + 7] = 0;
  // }

  return;
}
