#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu_hls.h"

int main (int argc, char *argv[])
{
  uint32_t memory[MEMORY_SIZE];

  FILE *fp;
  if ((fp = fopen (argv[1], "r")) == NULL) {
    perror (argv[1]);
    exit (1);
  }

  int idx = 0;
  while (fscanf(fp, "%08x", &memory[idx]) != EOF) {
    // fprintf (stdout, "memory[%d] <= %08x\n", idx, memory[idx]);
    idx ++;
  }

  uint32_t result = cpu_hls (memory);

  fprintf (stdout, "Result = %d\n", result);
  fprintf (stderr, "Pattern %s = %d\n", argv[1], result);

  return result != 1;
}
