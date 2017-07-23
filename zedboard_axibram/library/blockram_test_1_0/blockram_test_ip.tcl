# ip

source ../scripts/adi_env.tcl
source $ad_hdl_dir/library/scripts/adi_ip.tcl

adi_ip_create blockram_test_v1_0
adi_ip_files blockram_test_v1_0 [list \
  "hdl/blockram_test_v1_0_S00_AXI.v" \
  "hdl/blockram_test_v1_0.v" \
							 ]

# adi_ip_properties blockram_test_v1_0

# adi_ip_properties_lite blockram_test_v1_0

ipx::package_project -root_dir . \
    -vendor analog.com \
    -library user \
    -taxonomy /Analog_Devices

set_property vendor_display_name {Analog Devices} [ipx::current_core]
set_property company_url {www.analog.com} [ipx::current_core]

set_property supported_families {\
									 virtex7       Production \
									 qvirtex7      Production \
									 kintex7       Production \
									 kintex7l      Production \
									 qkintex7      Production \
									 qkintex7l     Production \
									 artix7        Production \
									 artix7l       Production \
									 aartix7       Production \
									 qartix7       Production \
									 zynq          Production \
									 qzynq         Production \
									 azynq         Production \
									 virtexu       Production \
									 kintexuplus   Production \
									 zynquplus     Production \
									 kintexu       Production \
									 virtex7       Beta \
									 qvirtex7      Beta \
									 kintex7       Beta \
									 kintex7l      Beta \
									 qkintex7      Beta \
									 qkintex7l     Beta \
									 artix7        Beta \
									 artix7l       Beta \
									 aartix7       Beta \
									 qartix7       Beta \
									 zynq          Beta \
									 qzynq         Beta \
									 azynq         Beta \
									 virtexu       Beta \
									 virtexuplus   Beta \
									 kintexuplus   Beta \
									 zynquplus     Beta \
									 kintexu       Beta}\
	[ipx::current_core]

ipx::remove_all_bus_interface [ipx::current_core]
set memory_maps [ipx::get_memory_maps * -of_objects [ipx::current_core]]
foreach map $memory_maps {
    ipx::remove_memory_map [lindex $map 2] [ipx::current_core ]
}

# end of adi_ip_properties_lite

ipx::infer_bus_interface {\
							  s_axi_awid \
							  s_axi_awaddr \
							  s_axi_awlen \
							  s_axi_awsize \
							  s_axi_awburst \
							  s_axi_awlock \
							  s_axi_awcache \
							  s_axi_awprot \
							  s_axi_awqos \
							  s_axi_awregion \
							  s_axi_awuser \
							  s_axi_awvalid \
							  s_axi_awready \
							  s_axi_wdata \
							  s_axi_wstrb \
							  s_axi_wlast \
							  s_axi_wuser \
							  s_axi_wvalid \
							  s_axi_wready \
							  s_axi_bid \
							  s_axi_bresp \
							  s_axi_buser \
							  s_axi_bvalid \
							  s_axi_bready \
							  s_axi_arid \
							  s_axi_araddr \
							  s_axi_arlen \
							  s_axi_arsize \
							  s_axi_arburst \
							  s_axi_arlock \
							  s_axi_arcache \
							  s_axi_arprot \
							  s_axi_arqos \
							  s_axi_arregion \
							  s_axi_aruser \
							  s_axi_arvalid \
							  s_axi_arready \
							  s_axi_rid \
							  s_axi_rdata \
							  s_axi_rresp \
							  s_axi_rlast \
							  s_axi_ruser \
							  s_axi_rvalid \
							  s_axi_rready} \
	xilinx.com:interface:aximm_rtl:1.0 [ipx::current_core]

ipx::infer_bus_interface s_axi_aclk xilinx.com:signal:clock_rtl:1.0 [ipx::current_core]
ipx::infer_bus_interface s_axi_aresetn xilinx.com:signal:reset_rtl:1.0 [ipx::current_core]
ipx::add_memory_map {s_axi} [ipx::current_core]
set_property slave_memory_map_ref {s_axi} [ipx::get_bus_interfaces s_axi -of_objects [ipx::current_core]]

# ipx::add_address_block {axi_lite} [ipx::get_memory_maps s_axi -of_objects [ipx::current_core]]
# set_property range {65536} [ipx::get_address_blocks axi_lite \
	# 								-of_objects [ipx::get_memory_maps s_axi -of_objects [ipx::current_core]]]

ipx::add_address_block {axi} [ipx::get_memory_maps s_axi -of_objects [ipx::current_core]]
set_property range {65536} [ipx::get_address_blocks axi \
								-of_objects [ipx::get_memory_maps s_axi -of_objects [ipx::current_core]]]
ipx::add_bus_parameter ASSOCIATED_BUSIF [ipx::get_bus_interfaces s_axi_aclk \
											 -of_objects [ipx::current_core]]
set_property value s_axi [ipx::get_bus_parameters ASSOCIATED_BUSIF \
							  -of_objects [ipx::get_bus_interfaces s_axi_aclk \
											   -of_objects [ipx::current_core]]]

# end of adi_ip_properties

adi_ip_constraints blockram_test_v1_0 [list \
  "blockram_test_constr.xdc" \
  "$ad_hdl_dir/library/common/ad_axi_ip_constr.xdc" ]

ipx::save_core [ipx::current_core]

