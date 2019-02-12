open_project $env(HLS_TARGET)
set_top $env(HLS_TARGET)
add_files $env(HLS_SRC)
add_files -tb test_$env(HLS_TARGET).cpp -cflags "-DC_SIMULATION"
open_solution $env(HLS_SOLUTION)
# set_part {xcvu440-flgb2377-3-e}
set_part {xc7z020clg484-1}
create_clock -period 10 -name default
source "./directives.tcl"
csim_design
csynth_design
# cosim_design
export_design -format ip_catalog
