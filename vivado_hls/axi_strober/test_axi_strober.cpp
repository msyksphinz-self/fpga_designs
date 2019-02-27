#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "axi_strober.h"

int main ()
{
  uint8_t memory[512];
  memset (memory, 0, 512);

  axi_strober (memory);

  int y, x;
  for (x = 0; x < 512; x++) {
    printf ("%02x ", memory[x]);
    if ((x % 16) == 15) {
      printf ("\n");
    }
  }

  return 0;
}
