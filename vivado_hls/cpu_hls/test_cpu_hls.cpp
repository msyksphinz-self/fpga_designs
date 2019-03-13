#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu_hls.h"

int main (int argc, char *argv[])
{
  XLEN_t memory[MEMORY_SIZE];

  FILE *fp;
  if ((fp = fopen (argv[1], "r")) == NULL) {
    perror (argv[1]);
    exit (1);
  }

  int idx = 0;
  uint32_t hex_data;
  while (fscanf(fp, "%08x", &hex_data) != EOF) {
    memory[idx] = hex_data;
    idx++;
  }

  uint32_t result = cpu_hls (memory);

  fprintf (stdout, "Result = %d\n", result);
  fprintf (stderr, "Pattern %s = %d\n", argv[1], result);

  return result != 1;
  // return 0;
}
