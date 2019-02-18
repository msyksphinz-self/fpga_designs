#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu_hls.h"

int main ()
{
  uint32_t memory[MEMORY_SIZE];

  // #ifndef __SYNTHESIS__
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
  // #endif // __SYNTHESIS__

  uint32_t result = cpu_hls (memory);

  // #ifndef __SYNTHESIS__
  fprintf (stdout, "Result = %d\n", result);
  // #endif // __SYNTHESIS__

  // return !(result == 1);
  return 0;
}
