open_project ../managed_ip_project/managed_ip_project

set_property target_simulator ModelSim [current_project]
create_ip -name blk_mem_gen \
	-vendor xilinx.com \
	-library ip -version 8.3 \
	-module_name blk_mem_gen_0 \
	-dir ./
set_property -dict [list CONFIG.Interface_Type {AXI4} \
						CONFIG.Write_Width_A {128} \
						CONFIG.Write_Depth_A {4097} \
						CONFIG.Use_AXI_ID {true} \
						CONFIG.Memory_Type {Simple_Dual_Port_RAM} \
						CONFIG.Use_Byte_Write_Enable {true} \
						CONFIG.Byte_Size {8} \
						CONFIG.Assume_Synchronous_Clk {true} \
						CONFIG.Read_Width_A {128} \
						CONFIG.Operating_Mode_A {READ_FIRST} \
						CONFIG.Write_Width_B {128} \
						CONFIG.Read_Width_B {128} \
						CONFIG.Operating_Mode_B {READ_FIRST} \
						CONFIG.Enable_B {Use_ENB_Pin} \
						CONFIG.Register_PortA_Output_of_Memory_Primitives {false} \
						CONFIG.Use_RSTB_Pin {true} \
						CONFIG.Reset_Type {ASYNC} \
						CONFIG.Port_B_Clock {100} \
						CONFIG.Port_B_Enable_Rate {100}] [get_ips blk_mem_gen_0]
generate_target {instantiation_template} [get_files blk_mem_gen_0.xci]
generate_target all [get_files  blk_mem_gen_0.xci]
export_ip_user_files -of_objects [get_files blk_mem_gen_0.xci] -no_script -sync -force -quiet
create_ip_run [get_files -of_objects [get_fileset sources_1] blk_mem_gen_0.xci]
launch_runs -jobs 2 blk_mem_gen_0_synth_1
export_simulation -of_objects [get_files blk_mem_gen_0.xci] \
	-directory ip_user_files/sim_scripts \
	-ip_user_files_dir ip_user_files \
	-ipstatic_source_dir ip_user_files/ipstatic \
	-lib_map_path [list {modelsim=managed_ip_project/managed_ip_project.cache/compile_simlib/modelsim} \
					   {questa=managed_ip_project/managed_ip_project.cache/compile_simlib/questa} \
					   {ies=managed_ip_project/managed_ip_project.cache/compile_simlib/ies} \
					   {vcs=managed_ip_project/managed_ip_project.cache/compile_simlib/vcs} \
					   {riviera=managed_ip_project/managed_ip_project.cache/compile_simlib/riviera}] -use_ip_compiled_libs -force -quiet
generate_target all [get_files  blk_mem_gen_0.xci]
catch { config_ip_cache -export [get_ips -all blk_mem_gen_0] }
export_ip_user_files -of_objects [get_files blk_mem_gen_0.xci] -no_script -sync -force -quiet
reset_run blk_mem_gen_0_synth_1
launch_runs -jobs 2 blk_mem_gen_0_synth_1
export_simulation -of_objects [get_files blk_mem_gen_0.xci] \
	-directory ip_user_files/sim_scripts \
	-ip_user_files_dir ip_user_files \
	-ipstatic_source_dir ip_user_files/ipstatic \
	-lib_map_path [list {modelsim=managed_ip_project/managed_ip_project.cache/compile_simlib/modelsim} \
					   {questa=managed_ip_project/managed_ip_project.cache/compile_simlib/questa} \
					   {ies=managed_ip_project/managed_ip_project.cache/compile_simlib/ies} \
					   {vcs=managed_ip_project/managed_ip_project.cache/compile_simlib/vcs} \
					   {riviera=managed_ip_project/managed_ip_project.cache/compile_simlib/riviera}] \
	-use_ip_compiled_libs -force -quiet
