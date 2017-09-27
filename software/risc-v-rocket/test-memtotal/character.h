// See LICENSE for license details.

#ifndef SRC_MAIN_C_CHARACTER_H
#define SRC_MAIN_C_CHARACTER_H

#define XCUSTOM_CHAR 2

#define countChar(y, mem_addr)                          \
  ROCC_INSTRUCTION(XCUSTOM_CHAR, y, mem_addr, 0, 0);

#endif  // SRC_MAIN_C_CHARACTER_H
