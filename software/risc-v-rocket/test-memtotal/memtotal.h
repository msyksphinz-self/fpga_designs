// See LICENSE for license details.

#ifndef SRC_MAIN_C_MEMTOTAL_H
#define SRC_MAIN_C_MEMTOTAL_H

#define XCUSTOM_CHAR 2

#define memtotal(y, mem_addr, size)                          \
  ROCC_INSTRUCTION(XCUSTOM_CHAR, y, mem_addr, size, 0);

#endif  // SRC_MAIN_C_MEMTOTAL_H
