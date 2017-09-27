// See LICENSE for license details.

#ifndef SRC_MAIN_C_MATRIXMUL_H
#define SRC_MAIN_C_MATRIXMUL_H

#include "rocc.h"

#define XCUSTOM_MATRIXMUL 2

#define matrixmul(y, mem_addr0, mem_addr1)                            \
  ROCC_INSTRUCTION(XCUSTOM_MATRIXMUL, y, mem_addr0, mem_addr1, 0);

#endif  // SRC_MAIN_C_MATRIXMUL_H
