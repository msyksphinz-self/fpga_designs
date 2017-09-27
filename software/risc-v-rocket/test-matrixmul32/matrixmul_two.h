// See LICENSE for license details.

#ifndef SRC_MAIN_C_MATRIXMUL_TWO_H
#define SRC_MAIN_C_MATRIXMUL_TWO_H

#include "rocc.h"

#define XCUSTOM_MATRIXMUL_TWO 0

#define k_MTRXMUL_SETM   (0)
#define k_MTRXMUL_SETK   (1)
#define k_MTRXMUL_DOCALC (2)

#define matrixmul_setM(y, len)											\
  ROCC_INSTRUCTION(XCUSTOM_MATRIXMUL_TWO, y, len, 0, k_MTRXMUL_SETM);
#define matrixmul_setK(y, len)											\
  ROCC_INSTRUCTION(XCUSTOM_MATRIXMUL_TWO, y, len, 0, k_MTRXMUL_SETK);
#define matrixmul_two(y, mem_addr0, mem_addr1)                            \
  ROCC_INSTRUCTION(XCUSTOM_MATRIXMUL_TWO, y, mem_addr0, mem_addr1, k_MTRXMUL_DOCALC);

#endif  // SRC_MAIN_C_MATRIXMUL_TWO_H
