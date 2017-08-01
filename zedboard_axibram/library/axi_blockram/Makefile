####################################################################################
####################################################################################
## Copyright 2011(c) Analog Devices, Inc.
## Auto-generated, do not modify!
####################################################################################
####################################################################################

TARGET = axi_blockram

# M_DEPS += ../common/ad_rst.v
# M_DEPS += ../common/up_axi.v
# M_DEPS += ../common/up_clkgen.v
M_DEPS += ../scripts/adi_env.tcl
M_DEPS += ../scripts/adi_ip.tcl
M_DEPS += ../xilinx/common/ad_mmcm_drp.v
M_DEPS += $(TARGET).v
M_DEPS += $(TARGET)_constr.xdc
M_DEPS += $(TARGET).tcl

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
all: $(TARGET).xpr


clean:clean-all


clean-all:
	rm -rf $(M_FLIST)


$(TARGET).xpr: $(M_DEPS)
	-rm -rf $(M_FLIST)
	$(M_VIVADO) $(TARGET).tcl  >> $(TARGET).log 2>&1

####################################################################################
####################################################################################
