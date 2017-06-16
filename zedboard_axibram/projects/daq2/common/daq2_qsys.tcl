
# ad9144-xcvr

add_instance avl_ad9144_xcvr avl_adxcvr 1.0
set_instance_parameter_value avl_ad9144_xcvr {ID} {0}
set_instance_parameter_value avl_ad9144_xcvr {TX_OR_RX_N} {1}
set_instance_parameter_value avl_ad9144_xcvr {PCS_CONFIG} {JESD_PCS_CFG2}
set_instance_parameter_value avl_ad9144_xcvr {LANE_RATE} {10000.0}
set_instance_parameter_value avl_ad9144_xcvr {PLLCLK_FREQUENCY} {5000.0}
set_instance_parameter_value avl_ad9144_xcvr {REFCLK_FREQUENCY} {500.0}
set_instance_parameter_value avl_ad9144_xcvr {CORECLK_FREQUENCY} {250.0}
set_instance_parameter_value avl_ad9144_xcvr {NUM_OF_LANES} {4}
set_instance_parameter_value avl_ad9144_xcvr {NUM_OF_CONVS} {2}
set_instance_parameter_value avl_ad9144_xcvr {FRM_BCNT} {1}
set_instance_parameter_value avl_ad9144_xcvr {FRM_SCNT} {1}
set_instance_parameter_value avl_ad9144_xcvr {MF_FCNT} {32}
set_instance_parameter_value avl_ad9144_xcvr {HD} {1}

add_connection sys_clk.clk avl_ad9144_xcvr.sys_clk
add_connection sys_clk.clk_reset avl_ad9144_xcvr.sys_resetn
add_interface tx_ref_clk clock sink
set_interface_property tx_ref_clk EXPORT_OF avl_ad9144_xcvr.ref_clk
add_interface tx_data_0 conduit end
set_interface_property tx_data_0 EXPORT_OF avl_ad9144_xcvr.tx_data_0
add_interface tx_data_1 conduit end
set_interface_property tx_data_1 EXPORT_OF avl_ad9144_xcvr.tx_data_1
add_interface tx_data_2 conduit end
set_interface_property tx_data_2 EXPORT_OF avl_ad9144_xcvr.tx_data_2
add_interface tx_data_3 conduit end
set_interface_property tx_data_3 EXPORT_OF avl_ad9144_xcvr.tx_data_3
add_interface tx_sysref conduit end
set_interface_property tx_sysref EXPORT_OF avl_ad9144_xcvr.sysref
add_interface tx_sync conduit end
set_interface_property tx_sync EXPORT_OF avl_ad9144_xcvr.sync
add_connection avl_ad9144_xcvr.tx_phy_s_0 avl_ad9144_xcvr.tx_ip_s_0
add_connection avl_ad9144_xcvr.tx_phy_s_1 avl_ad9144_xcvr.tx_ip_s_3
add_connection avl_ad9144_xcvr.tx_phy_s_2 avl_ad9144_xcvr.tx_ip_s_1
add_connection avl_ad9144_xcvr.tx_phy_s_3 avl_ad9144_xcvr.tx_ip_s_2
add_connection avl_ad9144_xcvr.tx_ip_d_0 avl_ad9144_xcvr.tx_phy_d_0
add_connection avl_ad9144_xcvr.tx_ip_d_3 avl_ad9144_xcvr.tx_phy_d_1
add_connection avl_ad9144_xcvr.tx_ip_d_1 avl_ad9144_xcvr.tx_phy_d_2
add_connection avl_ad9144_xcvr.tx_ip_d_2 avl_ad9144_xcvr.tx_phy_d_3

# ad9144-xcvr

add_instance axi_ad9144_xcvr axi_adxcvr 1.0
set_instance_parameter_value axi_ad9144_xcvr {ID} {0}
set_instance_parameter_value axi_ad9144_xcvr {TX_OR_RX_N} {1}
set_instance_parameter_value axi_ad9144_xcvr {NUM_OF_LANES} {4}

add_connection sys_clk.clk axi_ad9144_xcvr.s_axi_clock
add_connection sys_clk.clk_reset axi_ad9144_xcvr.s_axi_reset
add_connection axi_ad9144_xcvr.if_up_rst avl_ad9144_xcvr.rst
add_connection avl_ad9144_xcvr.ready axi_ad9144_xcvr.ready
add_connection axi_ad9144_xcvr.core_pll_locked avl_ad9144_xcvr.core_pll_locked

# ad9144-core

add_instance axi_ad9144_core axi_ad9144 1.0
set_instance_parameter_value axi_ad9144_core {QUAD_OR_DUAL_N} {0}

add_connection avl_ad9144_xcvr.core_clk axi_ad9144_core.if_tx_clk
add_connection axi_ad9144_core.if_tx_data avl_ad9144_xcvr.ip_data
add_connection sys_clk.clk_reset axi_ad9144_core.s_axi_reset
add_connection sys_clk.clk axi_ad9144_core.s_axi_clock

# ad9144-unpack

add_instance util_ad9144_upack util_upack 1.0
set_instance_parameter_value util_ad9144_upack {CHANNEL_DATA_WIDTH} {64}
set_instance_parameter_value util_ad9144_upack {NUM_OF_CHANNELS} {2}

add_connection avl_ad9144_xcvr.core_clk util_ad9144_upack.if_dac_clk
add_connection axi_ad9144_core.dac_ch_0 util_ad9144_upack.dac_ch_0
add_connection axi_ad9144_core.dac_ch_1 util_ad9144_upack.dac_ch_1

# ad9144-dma

add_instance axi_ad9144_dma axi_dmac 1.0
set_instance_parameter_value axi_ad9144_dma {DMA_DATA_WIDTH_SRC} {128}
set_instance_parameter_value axi_ad9144_dma {DMA_DATA_WIDTH_DEST} {128}
set_instance_parameter_value axi_ad9144_dma {DMA_2D_TRANSFER} {0}
set_instance_parameter_value axi_ad9144_dma {DMA_TYPE_DEST} {2}
set_instance_parameter_value axi_ad9144_dma {DMA_TYPE_SRC} {0}

add_connection avl_ad9144_xcvr.core_clk axi_ad9144_dma.if_fifo_rd_clk
add_connection util_ad9144_upack.if_dac_valid axi_ad9144_dma.if_fifo_rd_en
add_connection util_ad9144_upack.if_dac_data axi_ad9144_dma.if_fifo_rd_dout
add_connection axi_ad9144_dma.if_fifo_rd_underflow axi_ad9144_core.if_dac_dunf
add_connection sys_clk.clk_reset axi_ad9144_dma.s_axi_reset
add_connection sys_clk.clk axi_ad9144_dma.s_axi_clock
add_connection sys_ddr3_cntrl.emif_usr_reset_n axi_ad9144_dma.m_src_axi_reset
add_connection sys_ddr3_cntrl.emif_usr_clk axi_ad9144_dma.m_src_axi_clock

# ad9680-xcvr

add_instance avl_ad9680_xcvr avl_adxcvr 1.0
set_instance_parameter_value avl_ad9680_xcvr {ID} {1}
set_instance_parameter_value avl_ad9680_xcvr {TX_OR_RX_N} {0}
set_instance_parameter_value avl_ad9680_xcvr {PCS_CONFIG} {JESD_PCS_CFG2}
set_instance_parameter_value avl_ad9680_xcvr {LANE_RATE} {10000.0}
set_instance_parameter_value avl_ad9680_xcvr {PLLCLK_FREQUENCY} {5000.0}
set_instance_parameter_value avl_ad9680_xcvr {REFCLK_FREQUENCY} {500.0}
set_instance_parameter_value avl_ad9680_xcvr {CORECLK_FREQUENCY} {250.0}
set_instance_parameter_value avl_ad9680_xcvr {NUM_OF_LANES} {4}
set_instance_parameter_value avl_ad9680_xcvr {NUM_OF_CONVS} {2}
set_instance_parameter_value avl_ad9680_xcvr {FRM_BCNT} {1}
set_instance_parameter_value avl_ad9680_xcvr {FRM_SCNT} {1}
set_instance_parameter_value avl_ad9680_xcvr {MF_FCNT} {32}
set_instance_parameter_value avl_ad9680_xcvr {HD} {1}

add_connection sys_clk.clk avl_ad9680_xcvr.sys_clk
add_connection sys_clk.clk_reset avl_ad9680_xcvr.sys_resetn
add_interface rx_ref_clk clock sink
set_interface_property rx_ref_clk EXPORT_OF avl_ad9680_xcvr.ref_clk
add_interface rx_data_0 conduit end
set_interface_property rx_data_0 EXPORT_OF avl_ad9680_xcvr.rx_data_0
add_interface rx_data_1 conduit end
set_interface_property rx_data_1 EXPORT_OF avl_ad9680_xcvr.rx_data_1
add_interface rx_data_2 conduit end
set_interface_property rx_data_2 EXPORT_OF avl_ad9680_xcvr.rx_data_2
add_interface rx_data_3 conduit end
set_interface_property rx_data_3 EXPORT_OF avl_ad9680_xcvr.rx_data_3
add_interface rx_sysref conduit end
set_interface_property rx_sysref EXPORT_OF avl_ad9680_xcvr.sysref
add_interface rx_sync conduit end
set_interface_property rx_sync EXPORT_OF avl_ad9680_xcvr.sync

# ad9680-xcvr

add_instance axi_ad9680_xcvr axi_adxcvr 1.0
set_instance_parameter_value axi_ad9680_xcvr {ID} {1}
set_instance_parameter_value axi_ad9680_xcvr {TX_OR_RX_N} {0}
set_instance_parameter_value axi_ad9680_xcvr {NUM_OF_LANES} {4}

add_connection sys_clk.clk axi_ad9680_xcvr.s_axi_clock
add_connection sys_clk.clk_reset axi_ad9680_xcvr.s_axi_reset
add_connection axi_ad9680_xcvr.if_up_rst avl_ad9680_xcvr.rst
add_connection avl_ad9680_xcvr.ready axi_ad9680_xcvr.ready
add_connection axi_ad9680_xcvr.core_pll_locked avl_ad9680_xcvr.core_pll_locked

# ad9680

add_instance axi_ad9680_core axi_ad9680 1.0

add_connection avl_ad9680_xcvr.core_clk axi_ad9680_core.if_rx_clk
add_connection avl_ad9680_xcvr.ip_sof axi_ad9680_core.if_rx_sof
add_connection avl_ad9680_xcvr.ip_data axi_ad9680_core.if_rx_data
add_connection sys_clk.clk_reset axi_ad9680_core.s_axi_reset
add_connection sys_clk.clk axi_ad9680_core.s_axi_clock

# ad9680-pack

add_instance util_ad9680_cpack util_cpack 1.0
set_instance_parameter_value util_ad9680_cpack {CHANNEL_DATA_WIDTH} {64}
set_instance_parameter_value util_ad9680_cpack {NUM_OF_CHANNELS} {2}

add_connection sys_clk.clk_reset util_ad9680_cpack.if_adc_rst
add_connection sys_ddr3_cntrl.emif_usr_reset_n util_ad9680_cpack.if_adc_rst
add_connection avl_ad9680_xcvr.core_clk util_ad9680_cpack.if_adc_clk
add_connection axi_ad9680_core.adc_ch_0 util_ad9680_cpack.adc_ch_0
add_connection axi_ad9680_core.adc_ch_1 util_ad9680_cpack.adc_ch_1

# ad9680-fifo

add_instance ad9680_adcfifo util_adcfifo 1.0
set_instance_parameter_value ad9680_adcfifo {ADC_DATA_WIDTH} {128}
set_instance_parameter_value ad9680_adcfifo {DMA_DATA_WIDTH} {128}
set_instance_parameter_value ad9680_adcfifo {DMA_ADDRESS_WIDTH} {16}

add_connection sys_clk.clk_reset ad9680_adcfifo.if_adc_rst
add_connection sys_ddr3_cntrl.emif_usr_reset_n ad9680_adcfifo.if_adc_rst
add_connection avl_ad9680_xcvr.core_clk ad9680_adcfifo.if_adc_clk
add_connection util_ad9680_cpack.if_adc_valid ad9680_adcfifo.if_adc_wr
add_connection util_ad9680_cpack.if_adc_data ad9680_adcfifo.if_adc_wdata
add_connection sys_ddr3_cntrl.emif_usr_clk ad9680_adcfifo.if_dma_clk

# ad9680-dma

add_instance axi_ad9680_dma axi_dmac 1.0
set_instance_parameter_value axi_ad9680_dma {DMA_DATA_WIDTH_SRC} {128}
set_instance_parameter_value axi_ad9680_dma {DMA_DATA_WIDTH_DEST} {128}
set_instance_parameter_value axi_ad9680_dma {DMA_LENGTH_WIDTH} {24}
set_instance_parameter_value axi_ad9680_dma {DMA_2D_TRANSFER} {0}
set_instance_parameter_value axi_ad9680_dma {SYNC_TRANSFER_START} {1}
set_instance_parameter_value axi_ad9680_dma {CYCLIC} {0}
set_instance_parameter_value axi_ad9680_dma {DMA_TYPE_DEST} {0}
set_instance_parameter_value axi_ad9680_dma {DMA_TYPE_SRC} {1}

add_connection sys_ddr3_cntrl.emif_usr_clk axi_ad9680_dma.if_s_axis_aclk
add_connection ad9680_adcfifo.if_dma_wr axi_ad9680_dma.if_s_axis_valid
add_connection ad9680_adcfifo.if_dma_wdata axi_ad9680_dma.if_s_axis_data
add_connection ad9680_adcfifo.if_dma_wready axi_ad9680_dma.if_s_axis_ready
add_connection ad9680_adcfifo.if_dma_xfer_req axi_ad9680_dma.if_s_axis_xfer_req
add_connection ad9680_adcfifo.if_adc_wovf axi_ad9680_core.if_adc_dovf
add_connection sys_clk.clk_reset axi_ad9680_dma.s_axi_reset
add_connection sys_clk.clk axi_ad9680_dma.s_axi_clock
add_connection sys_ddr3_cntrl.emif_usr_reset_n axi_ad9680_dma.m_dest_axi_reset
add_connection sys_ddr3_cntrl.emif_usr_clk axi_ad9680_dma.m_dest_axi_clock

# reconfig sharing

add_instance avl_adxcfg_0 avl_adxcfg 1.0
add_connection sys_clk.clk avl_adxcfg_0.rcfg_clk
add_connection sys_clk.clk_reset avl_adxcfg_0.rcfg_reset_n
add_connection avl_adxcfg_0.rcfg_m0 avl_ad9144_xcvr.phy_reconfig_0
add_connection avl_adxcfg_0.rcfg_m1 avl_ad9680_xcvr.phy_reconfig_0

add_instance avl_adxcfg_1 avl_adxcfg 1.0
add_connection sys_clk.clk avl_adxcfg_1.rcfg_clk
add_connection sys_clk.clk_reset avl_adxcfg_1.rcfg_reset_n
add_connection avl_adxcfg_1.rcfg_m0 avl_ad9144_xcvr.phy_reconfig_1
add_connection avl_adxcfg_1.rcfg_m1 avl_ad9680_xcvr.phy_reconfig_1

add_instance avl_adxcfg_2 avl_adxcfg 1.0
add_connection sys_clk.clk avl_adxcfg_2.rcfg_clk
add_connection sys_clk.clk_reset avl_adxcfg_2.rcfg_reset_n
add_connection avl_adxcfg_2.rcfg_m0 avl_ad9144_xcvr.phy_reconfig_2
add_connection avl_adxcfg_2.rcfg_m1 avl_ad9680_xcvr.phy_reconfig_2

add_instance avl_adxcfg_3 avl_adxcfg 1.0
add_connection sys_clk.clk avl_adxcfg_3.rcfg_clk
add_connection sys_clk.clk_reset avl_adxcfg_3.rcfg_reset_n
add_connection avl_adxcfg_3.rcfg_m0 avl_ad9144_xcvr.phy_reconfig_3
add_connection avl_adxcfg_3.rcfg_m1 avl_ad9680_xcvr.phy_reconfig_3

# addresses

ad_cpu_interconnect 0x10404000 avl_adxcfg_0.rcfg_s0
ad_cpu_interconnect 0x10504000 avl_adxcfg_0.rcfg_s1
ad_cpu_interconnect 0x10405000 avl_adxcfg_1.rcfg_s0
ad_cpu_interconnect 0x10505000 avl_adxcfg_1.rcfg_s1
ad_cpu_interconnect 0x10406000 avl_adxcfg_2.rcfg_s0
ad_cpu_interconnect 0x10506000 avl_adxcfg_2.rcfg_s1
ad_cpu_interconnect 0x10407000 avl_adxcfg_3.rcfg_s0
ad_cpu_interconnect 0x10507000 avl_adxcfg_3.rcfg_s1
ad_cpu_interconnect 0x10400000 avl_ad9144_xcvr.core_pll_reconfig
ad_cpu_interconnect 0x10402000 avl_ad9144_xcvr.lane_pll_reconfig
ad_cpu_interconnect 0x10401000 avl_ad9144_xcvr.ip_reconfig
ad_cpu_interconnect 0x1040c000 axi_ad9144_dma.s_axi
ad_cpu_interconnect 0x10410000 axi_ad9144_xcvr.s_axi
ad_cpu_interconnect 0x10420000 axi_ad9144_core.s_axi
ad_cpu_interconnect 0x10500000 avl_ad9680_xcvr.core_pll_reconfig
ad_cpu_interconnect 0x10501000 avl_ad9680_xcvr.ip_reconfig
ad_cpu_interconnect 0x1050c000 axi_ad9680_dma.s_axi
ad_cpu_interconnect 0x10510000 axi_ad9680_xcvr.s_axi
ad_cpu_interconnect 0x10520000 axi_ad9680_core.s_axi

# dma interconnects

ad_dma_interconnect axi_ad9144_dma.m_src_axi
ad_dma_interconnect axi_ad9680_dma.m_dest_axi

# interrupts

ad_cpu_interrupt 10 axi_ad9680_dma.interrupt_sender
ad_cpu_interrupt 11 axi_ad9144_dma.interrupt_sender
