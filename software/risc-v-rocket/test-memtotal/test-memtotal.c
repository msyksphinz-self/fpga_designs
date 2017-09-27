// See LICENSE for license details.

#include <assert.h>
#include "accumulator.h"
#include "translator.h"
#include "character.h"
#include "memtotal.h"
#include "util.h"

int main() {
  uint64_t phy_data_addr;

  uint64_t num_array[1024];
  uint64_t max_count = 1;

  for (int i = 0; i < 1024; i++) {
    num_array[i] = i;
  }

  printf ("Hardware Start\n");

  uint64_t hw_total[11] = {0};
  for (int count = 0; count < 11; count++) {
    uint64_t start_cycle = read_csr(mcycle);
    memtotal (hw_total[count], num_array, max_count-1);
    uint64_t stop_cycle = read_csr(mcycle);

    printf ("[HW: MemTotal %ld] %ld\n", hw_total[count], stop_cycle - start_cycle);
    max_count *= 2;
  }

  max_count = 1;
  for (int count = 0; count < 11; count++) {
    uint64_t total = 0;

    uint64_t start_cycle = read_csr(mcycle);
    for (int j = 0; j < max_count; j++) {
      total += num_array[j];
    }
    uint64_t stop_cycle = read_csr(mcycle);
    printf ("[SW: MemTotal %ld] %ld\n", total, stop_cycle - start_cycle);

    max_count *= 2;
  }

  return 0;
}
