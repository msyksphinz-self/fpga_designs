#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu_hls.h"

int main ()
{
  uint32_t memory[2048];

  FILE *fp;
  if ((fp = fopen ("test.hex", "r")) == NULL) {
    perror ("test.hex");
    exit (1);
  }

  int idx = 0;
  while (fscanf(fp, "%08x", &memory[idx]) != EOF) {
    fprintf (stdout, "memory[%d] <= %08x\n", idx, memory[idx]);
    idx ++;
  }

  cpu_hls (memory, memory);

#ifdef C_SIMULATION
  // int x;
  // for(x = 0; x < 1024; x++) {
  //   printf ("%08x\n", image_out[x]);
  // }
#endif // C_SIMULATION

  return 0;
}
