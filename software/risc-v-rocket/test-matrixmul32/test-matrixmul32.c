// See LICENSE for license details.

#include <assert.h>
#include "matrixmul.h"
#include "matrixmul_two.h"
#include "util.h"
// #include "dataset_mat.h"
#include "dataset_small.h"

void show_result (int32_t *A)
{
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < K; i++) {
      printf ("%03ld ", A[j*K+i]);
    }
    printf ("\n");
  }
  return;
}


void matrixmul_soft (int32_t *A, int32_t *B)
{
  int32_t output_data[N*K];
  uint32_t start_cycle, stop_cycle;

  printf ("Software Start\n");
  start_cycle = read_csr(mcycle);
  for (int n = 0; n < N; n++) {
    for (int k = 0; k < K; k++) {
      output_data[n*K+k] = 0;
      for (int m = 0; m < M; m++) {
        output_data[n*K+k] += (A[n*M+m] * B[m*K+k]);
      }
    }
  }
  stop_cycle = read_csr(mcycle);
  printf ("Software Finished. %ld-%ld=%ld\n", stop_cycle, start_cycle, stop_cycle-start_cycle);

  show_result(output_data);
}


int main()
{
  matrixmul_soft (input1_data, input2_data);

  return 0;
}
