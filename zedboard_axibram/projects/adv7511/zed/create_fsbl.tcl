#!/usr/bin/tclsh

set app_name            "fsbl"
set app_type            {Zynq FSBL}
set bsp_name            "fsbl_bsp"
set hw_name             "system_top_hw_platform_0"
set hwspec_file         "system_top.hdf"
set proc_name           "ps7_cortexa9_0"
set project_directory   [file dirname [info script]]
set sdk_workspace       [file join $project_directory "project.sdk"]

if {[info commands sdk::setws] ne ""} {
	sdk setws         $sdk_workspace
} else {
	sdk set_workspace $sdk_workspace
}

if {[info commands sdk::createhw] ne ""} {
	sdk createhw          -name $hw_name -hwspec [file join $sdk_workspace $hw_name $hwspec_file]
} else {
	sdk create_hw_project -name $hw_name -hwspec [file join $sdk_workspace $hw_name $hwspec_file]
}

hsi::open_hw_design  [file join $sdk_workspace $hw_name $hwspec_file]
hsi::create_sw_design $bsp_name -proc $proc_name -os standalone
hsi::add_library xilffs
hsi::generate_bsp -sw $bsp_name -dir [file join $sdk_workspace $bsp_name] -compile
hsi::close_sw_design  $bsp_name

if {[info commands sdk::createapp] ne ""} {
	sdk createapp          -name $app_name -hwproject $hw_name -proc $proc_name -os standalone -lang C -app $app_type -bsp $bsp_name
} else {
	sdk create_app_project -name $app_name -hwproject $hw_name -proc $proc_name -os standalone -lang C -app $app_type -bsp $bsp_name
}

if {[info commands sdk::projects] ne ""} {
	sdk projects -build
} else {
	sdk build_project $app_name
}

exit
