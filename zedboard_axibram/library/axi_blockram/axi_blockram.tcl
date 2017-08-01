# ip

source ../scripts/adi_env.tcl
source $ad_hdl_dir/library/scripts/adi_ip.tcl

adi_ip_create axi_blockram
adi_ip_files axi_blockram [list \
  "$ad_hdl_dir/library/common/up_axi.v" \
  "axi_blockram_constr.xdc" \
  "axi_blockram.v" ]

adi_ip_properties axi_blockram

ipx::remove_bus_interface {clk} [ipx::current_core]
ipx::associate_bus_interfaces -busif s_axi -clock s_axi_aclk [ipx::current_core]

set_property driver_value 0 [ipx::get_ports *clk2* -of_objects [ipx::current_core]]

adi_ip_constraints axi_blockram [list \
  "axi_blockram_constr.xdc" ]

ipx::save_core [ipx::current_core]
