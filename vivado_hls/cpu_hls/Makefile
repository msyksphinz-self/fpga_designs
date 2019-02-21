export HLS_TARGET = cpu_hls
export HLS_SOLUTION = normal

HLS_SRC =
HLS_SRC += cpu_hls.cpp
HLS_SRC += rv32_cpu.cpp
HLS_SRC += rv32_csr.cpp

export HLS_SRC

TEST_PATTERNS = $(wildcard ./riscv-tests/isa/rv32ui-p-*.hex)
RUN_PATTERNS = $(addsuffix _run,$(notdir $(basename $(TEST_PATTERNS))))

regression: | $(RUN_PATTERNS)

%_run:
	make -f ../common/csim.mk HLS_SOLUTION=$(subst _run,,$@) TEST_PATTERN=$(subst _run,.hex,$@) > /dev/null

include ./../common/common.mk
