M_DEPS += ../common/ad_axi_ip_constr.xdc
M_DEPS += ../common/ad_csc_1.v
M_DEPS += ../common/ad_csc_1_add.v
M_DEPS += ../common/ad_csc_1_mul.v
M_DEPS += ../common/ad_csc_RGB2CrYCb.v
M_DEPS += ../common/ad_mem.v
M_DEPS += ../common/ad_rst.v
M_DEPS += ../common/ad_ss_444to422.v
M_DEPS += ../common/up_axi.v
M_DEPS += ../common/up_clock_mon.v
M_DEPS += ../common/up_hdmi_tx.v
M_DEPS += ../common/up_xfer_cntrl.v
M_DEPS += ../common/up_xfer_status.v
M_DEPS += ../scripts/adi_env.tcl
M_DEPS += ../scripts/adi_ip.tcl

M_DEPS += ./hdl/blockram_test_v1_0_S00_AXI.v
M_DEPS += ./hdl/blockram_test_v1_0.v

M_VIVADO := vivado -mode batch -source

M_FLIST := *.cache
M_FLIST += *.data
M_FLIST += *.xpr
M_FLIST += *.log
M_FLIST += component.xml
M_FLIST += *.jou
M_FLIST +=  xgui
M_FLIST += *.ip_user_files
M_FLIST += *.srcs
M_FLIST += *.hw
M_FLIST += *.sim
M_FLIST += .Xil


.PHONY: all clean clean-all
all: blockram_test.xpr


clean:clean-all


clean-all:
	rm -rf $(M_FLIST)


blockram_test.xpr: $(M_DEPS)
	-rm -rf $(M_FLIST)
	$(M_VIVADO) blockram_test_ip.tcl  >> blockram_test_ip.log 2>&1
