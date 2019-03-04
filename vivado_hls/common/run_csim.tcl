open_project $env(HLS_TARGET)
set_top $env(HLS_TARGET)
add_files $env(HLS_SRC)
add_files -tb test_$env(HLS_TARGET).cpp
add_files -tb ./riscv-tests/isa/$env(TEST_PATTERN)
open_solution $env(HLS_SOLUTION)

create_clock -period 10 -name default
source "./directives.tcl"

puts $env(TEST_PATTERN)

csim_design -argv $env(TEST_PATTERN)
