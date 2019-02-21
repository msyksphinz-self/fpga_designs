open_project $env(HLS_TARGET)
set_top $env(HLS_TARGET)
add_files $env(HLS_SRC)
add_files -tb test_$env(HLS_TARGET).cpp
add_files -tb test.hex
open_solution $env(HLS_SOLUTION)

create_clock -period 10 -name default
source "./directives.tcl"
csim_design -argv test.hex

set fpga_parts [list_part zynq]
set zynq [lsearch $fpga_parts xc7z020clg484-1]

if { $zynq == -1 } {
    puts "Set VU440 as parts"
    set_part {xcvu440-flgb2377-3-e}
} else {
    puts "Set XC7Z as parts"
    set_part {xc7z020clg484-1}
}

csynth_design
cosim_design
export_design -format ip_catalog
