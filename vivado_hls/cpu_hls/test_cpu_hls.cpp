#include <stdio.h>
#include <stdint.h>
#include "cpu_hls.h"

int main ()
{
  uint32_t image_in[1024];
  uint32_t image_out[1024];
  cpu_hls (image_in, image_out);

#ifdef C_SIMULATION
  // int x;
  // for(x = 0; x < 1024; x++) {
  //   printf ("%08x\n", image_out[x]);
  // }
#endif // C_SIMULATION

  return 0;
}
