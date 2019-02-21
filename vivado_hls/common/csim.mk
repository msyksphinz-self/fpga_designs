.PHONY: all

export HLS_SOLUTION
export TEST_PATTERN

all:
	vivado_hls ../common/run_csim.tcl
