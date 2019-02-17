#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu_hls.h"

int main ()
{
  uint32_t memory[MEMORY_SIZE];

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

  // unsigned long start_time = pmon_start_cycle_counter ();
  uint32_t result = cpu_hls (memory);
  // unsigned long stop_time = pmon_read_cycle_counter();

  fprintf (stdout, "Result = %d\n", result);
  // fprintf (stdout, "start_time = %ld, stop_time = %ld, Time = %d\n",
  //          start_time, stop_time, stop_time - start_time);

  return !(result == 1);
}
