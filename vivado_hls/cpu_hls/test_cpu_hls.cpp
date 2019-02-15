#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu_hls.h"

int main ()
{
  uint32_t memory[8192];

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

  return 0;
}
