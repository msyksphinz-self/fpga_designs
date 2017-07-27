set project_name adv7511_zed

source ../../scripts/adi_env.tcl
source $ad_hdl_dir/projects/scripts/adi_project.tcl
source $ad_hdl_dir/projects/scripts/adi_board.tcl

adi_project_create adv7511_zed
adi_project_files adv7511_zed [list \
  "system_top.v" \
  "$ad_hdl_dir/projects/common/zed/zed_system_constr.xdc" \
  "$ad_hdl_dir/library/xilinx/common/ad_iobuf.v"]

# Run Project
adi_project_run adv7511_zed

# Add IPs
update_compile_order -fileset sources_1
open_bd_design {./adv7511_zed.srcs/sources_1/bd/system/system.bd}
update_ip_catalog -rebuild
startgroup
create_bd_cell -type ip -vlnv analog.com:user:blockram_test_v1_0:1.0 blockram_test_0
endgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 \
	-config {Master "/sys_ps7/M_AXI_GP0" intc_ip "Auto" Clk_xbar "Auto" Clk_master "Auto" Clk_slave "Auto" }  \
	[get_bd_intf_pins blockram_test_0/S_AXI]
regenerate_bd_layout

# reset_run synth_1
# reset_run system_xbar_0_synth_1
# launch_runs impl_1 -to_step write_bitstream -jobs 2
# wait_on_run impl_1
# save_bd_design

# Run Project
adi_project_run adv7511_zed

