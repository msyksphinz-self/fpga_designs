set project_directory   [file dirname [info script]]
set hw_name             "system_top_hw_platform_0"
set project_name adv7511_zed

open_project [file join $project_directory $project_name]

set project_directory [file dirname [info script]]
set sdk_workspace  [file join $project_directory $project_name.sdk]

if { [file exists [file join $sdk_workspace $hw_name]] == 0 } {
    file mkdir [file join $sdk_workspace $hw_name]
}
set design_top_name [get_property "top" [current_fileset]]
file copy -force [file join $project_directory $project_name.runs "impl_1" $design_top_name.sysdef] [file join $sdk_workspace $hw_name $design_top_name.hdf]

close_project


