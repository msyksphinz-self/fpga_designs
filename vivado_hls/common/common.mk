HLS_TARGET ?= design
HLS_SOLUTION ?= opt1

all:
	vivado_hls script.tcl

clean:
	rm -rf *.log *~
	rm -rf $(HLS_TARGET)
