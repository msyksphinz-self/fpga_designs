####################################################################################
####################################################################################
## Copyright 2011(c) Analog Devices, Inc.
## Auto-generated, do not modify!
####################################################################################
####################################################################################

M_DEPS += system_top.v
M_DEPS += system_project.tcl
M_DEPS += system_bd.tcl
M_DEPS += ../../scripts/adi_project.tcl
M_DEPS += ../../scripts/adi_env.tcl
M_DEPS += ../../scripts/adi_board.tcl
M_DEPS += ../../common/zed/zed_system_constr.xdc
M_DEPS += ../../common/zed/zed_system_bd.tcl
M_DEPS += ../../../library/xilinx/common/ad_iobuf.v
M_DEPS += ../../../library/axi_clkgen/axi_clkgen.xpr
M_DEPS += ../../../library/axi_hdmi_tx/axi_hdmi_tx.xpr
M_DEPS += ../../../library/axi_i2s_adi/axi_i2s_adi.xpr
M_DEPS += ../../../library/axi_spdif_tx/axi_spdif_tx.xpr
M_DEPS += ../../../library/util_i2c_mixer/util_i2c_mixer.xpr

M_VIVADO := vivado -mode batch -source

M_FLIST := *.cache
M_FLIST += *.data
M_FLIST += *.xpr
M_FLIST += *.log
M_FLIST += *.jou
M_FLIST +=  xgui
M_FLIST += *.runs
M_FLIST += *.srcs
M_FLIST += *.sdk
M_FLIST += *.hw
M_FLIST += *.sim
M_FLIST += .Xil
M_FLIST += *.ip_user_files
M_FLIST += *.str
M_FLIST += *.rpt


.PHONY: all lib fsbl clean_fsbl bootgen hdf zed_project zed_impl clean clean-all
all: lib boot.bin


clean:
	rm -rf $(M_FLIST)


clean-all:clean
	make -C ../../../library/axi_clkgen clean
	make -C ../../../library/axi_hdmi_tx clean
	make -C ../../../library/axi_i2s_adi clean
	make -C ../../../library/axi_spdif_tx clean
	make -C ../../../library/util_i2c_mixer clean


boot.bin: project.sdk/fsbl/Debug/fsbl.elf
	-rm -rf $@
	bootgen -image ./boot.bif -o i $@

project.sdk/fsbl/Debug/fsbl.elf: project.sdk/system_top_hw_platform_0/system.hdf
	xsdk -batch -source ./create_fsbl.tcl

project.sdk/system_top_hw_platform_0/system.hdf: project.xpr
	$(M_VIVADO) create_hdf.tcl > adv7511_zed_hdf.log 2>&1

project.xpr: create_project.tcl implementation.tcl $(M_DEPS)
	$(M_VIVADO) create_project.tcl > create_project.log 2>&1
	$(M_VIVADO) implementation.tcl > implementation.log 2>&1


clean_fsbl:
	rm -rf project.sdk

lib:
	make -C ../../../library/axi_clkgen
	make -C ../../../library/axi_hdmi_tx
	make -C ../../../library/axi_i2s_adi
	make -C ../../../library/axi_spdif_tx
	make -C ../../../library/util_i2c_mixer

####################################################################################
####################################################################################
