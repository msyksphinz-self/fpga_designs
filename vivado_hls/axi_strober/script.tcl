open_project $env(HLS_TARGET)
set_top $env(HLS_TARGET)
add_files $env(HLS_SRC)
add_files -tb test_$env(HLS_TARGET).cpp
open_solution $env(HLS_SOLUTION)

create_clock -period 10 -name default
source "./directives.tcl"
csim_design

puts "Set VU440 as parts"
set_part {xcvu440-flgb2377-3-e}

csynth_design
cosim_design
export_design -format ip_catalog
