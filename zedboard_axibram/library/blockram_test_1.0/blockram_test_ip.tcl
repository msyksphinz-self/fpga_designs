# ip

source ../scripts/adi_env.tcl
source $ad_hdl_dir/library/scripts/adi_ip.tcl

adi_ip_create blockram_test_v1_0
adi_ip_files blockram_test_v1_0 [list \
  "hdl/blockram_test_v1_0_S00_AXI.v" \
  "hdl/blockram_test_v1_0.v" \
							 ]

adi_ip_properties blockram_test_v1_0

adi_ip_constraints blockram_test_v1_0 [list \
  "blockram_test_constr.xdc" \
  "$ad_hdl_dir/library/common/ad_axi_ip_constr.xdc" ]

ipx::save_core [ipx::current_core]

