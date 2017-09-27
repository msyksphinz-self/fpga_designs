// See LICENSE for license details.

#include <assert.h>
#include "matrixmul.h"
#include "matrixmul_two.h"
#include "util.h"
// #include "dataset_mat.h"
#include "dataset_small.h"

void show_result (int64_t *A)
{
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < K; i++) {
      printf ("%03ld ", A[j*K+i]);
    }
    printf ("\n");
  }
  return;
}


void matrixmul_soft (int64_t *A, int64_t *B)
{
  int64_t output_data[N*K];
  uint64_t start_cycle, stop_cycle;

  printf ("Software Start\n");
  start_cycle = read_csr(mcycle);
  for (int n = 0; n < N; n++) {
    for (int k = 0; k < K; k++) {
      output_data[n*K+k] = 0;
      // printf ("Calculating (%d,%d)\n", n, k);
      for (int m = 0; m < M; m++) {
        output_data[n*K+k] += (A[n*M+m] * B[m*K+k]);
        // if ((n == 1) && (k == 0)) {
        //   printf ("A[%d]=%d B[%d]=%d output %d\n", n*M+m, A[n*M+m], m*K+k, B[m*K+k], output_data[n*K+k]);
        // }
      }
    }
  }
  stop_cycle = read_csr(mcycle);
  printf ("Software Finished. %ld-%ld=%ld\n", stop_cycle, start_cycle, stop_cycle-start_cycle);

  show_result(output_data);
}


void matrixmul_hw1 (int64_t *A, int64_t *B)
{
  int64_t output_data[N*K];
  uint64_t start_cycle, stop_cycle;

  printf ("Hardware Start <MatrixMul TwoRequester>\n");
  start_cycle = read_csr(mcycle);
  uint64_t dummy;
  matrixmul_setM (dummy, M);
  matrixmul_setK (dummy, K);
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < K; i++) {
      matrixmul_two (output_data[j*K+i], &(input1_data[j*M]), &(input2_data[i]));
    }
  }
  stop_cycle = read_csr(mcycle);
  printf ("Hardware Finished. %ld-%ld=%ld\n", stop_cycle, start_cycle, stop_cycle-start_cycle);
  show_result(output_data);
}


void matrixmul_hw2 (int64_t *A, int64_t *B)
{
  int64_t output_data[N*K];
  uint64_t start_cycle, stop_cycle;

  printf ("Hardware Start <MatrixMul TwoRequester>\n");
  start_cycle = read_csr(mcycle);
  uint64_t dummy;
  matrixmul_setM (dummy, M);
  matrixmul_setK (dummy, K);
  for (int i = 0; i < K; i++) {
    for (int j = 0; j < N; j++) {
      matrixmul_two (output_data[j*K+i], &(input1_data[j*M]), &(input2_data[i]));
    }
  }
  stop_cycle = read_csr(mcycle);
  printf ("Hardware Finished. %ld-%ld=%ld\n", stop_cycle, start_cycle, stop_cycle-start_cycle);
  show_result(output_data);
}



int main()
{
  // printf ("Hardware Start <MatrixMul>\n");
  // start_cycle = read_csr(mcycle);
  // for (int i = 0; i < 16; i++) {
  //   for (int j = 0; j < 16; j++) {
  //     matrixmul (output_data[j*16+i], &(input1_data[j*16]), &(input2_data[i]));
  //   }
  // }
  // stop_cycle = read_csr(mcycle);
  //
  // for (int j = 0; j < 16; j++) {
  //   for (int i = 0; i < 16; i++) {
  //     printf ("%03ld ", output_data[j*16+i]);
  //   }
  //   printf ("\n");
  // }
  // printf ("Hardware Finished. %ld-%ld=%ld\n", stop_cycle, start_cycle, stop_cycle-start_cycle);

  matrixmul_soft (input1_data, input2_data);
  matrixmul_hw1 (input1_data, input2_data);
  matrixmul_hw2 (input1_data, input2_data);

  return 0;
}
