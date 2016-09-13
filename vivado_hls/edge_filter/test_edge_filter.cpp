#include <stdio.h>
#include <stdint.h>
#include "./edge_filter.h"

int main ()
{
  uint32_t image_in[128][128];
  uint32_t image_out[128][128];
  edge_filter (image_in, image_out);

#ifdef C_SIMULATION
  int y, x;
  for(y = 0; y < 128; y++) {
    for (x = 0; x < 128; x++) {
      printf ("%d ", image_out[y][x]);
    }
    printf ("\n");
  }
#endif // C_SIMULATION

  return 0;
}

