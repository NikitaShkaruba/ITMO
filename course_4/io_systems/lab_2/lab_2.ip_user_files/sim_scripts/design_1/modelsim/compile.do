vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xil_defaultlib
vlib modelsim_lib/msim/xpm
vlib modelsim_lib/msim/microblaze_v10_0_4
vlib modelsim_lib/msim/lib_cdc_v1_0_2
vlib modelsim_lib/msim/proc_sys_reset_v5_0_12
vlib modelsim_lib/msim/axi_lite_ipif_v3_0_4
vlib modelsim_lib/msim/lib_pkg_v1_0_2
vlib modelsim_lib/msim/axi_timer_v2_0_16
vlib modelsim_lib/msim/interrupt_control_v3_1_4
vlib modelsim_lib/msim/axi_gpio_v2_0_16
vlib modelsim_lib/msim/generic_baseblocks_v2_1_0
vlib modelsim_lib/msim/axi_infrastructure_v1_1_0
vlib modelsim_lib/msim/axi_register_slice_v2_1_14
vlib modelsim_lib/msim/fifo_generator_v13_2_0
vlib modelsim_lib/msim/axi_data_fifo_v2_1_13
vlib modelsim_lib/msim/axi_crossbar_v2_1_15
vlib modelsim_lib/msim/lmb_v10_v3_0_9
vlib modelsim_lib/msim/lmb_bram_if_cntlr_v4_0_13
vlib modelsim_lib/msim/blk_mem_gen_v8_4_0

vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib
vmap xpm modelsim_lib/msim/xpm
vmap microblaze_v10_0_4 modelsim_lib/msim/microblaze_v10_0_4
vmap lib_cdc_v1_0_2 modelsim_lib/msim/lib_cdc_v1_0_2
vmap proc_sys_reset_v5_0_12 modelsim_lib/msim/proc_sys_reset_v5_0_12
vmap axi_lite_ipif_v3_0_4 modelsim_lib/msim/axi_lite_ipif_v3_0_4
vmap lib_pkg_v1_0_2 modelsim_lib/msim/lib_pkg_v1_0_2
vmap axi_timer_v2_0_16 modelsim_lib/msim/axi_timer_v2_0_16
vmap interrupt_control_v3_1_4 modelsim_lib/msim/interrupt_control_v3_1_4
vmap axi_gpio_v2_0_16 modelsim_lib/msim/axi_gpio_v2_0_16
vmap generic_baseblocks_v2_1_0 modelsim_lib/msim/generic_baseblocks_v2_1_0
vmap axi_infrastructure_v1_1_0 modelsim_lib/msim/axi_infrastructure_v1_1_0
vmap axi_register_slice_v2_1_14 modelsim_lib/msim/axi_register_slice_v2_1_14
vmap fifo_generator_v13_2_0 modelsim_lib/msim/fifo_generator_v13_2_0
vmap axi_data_fifo_v2_1_13 modelsim_lib/msim/axi_data_fifo_v2_1_13
vmap axi_crossbar_v2_1_15 modelsim_lib/msim/axi_crossbar_v2_1_15
vmap lmb_v10_v3_0_9 modelsim_lib/msim/lmb_v10_v3_0_9
vmap lmb_bram_if_cntlr_v4_0_13 modelsim_lib/msim/lmb_bram_if_cntlr_v4_0_13
vmap blk_mem_gen_v8_4_0 modelsim_lib/msim/blk_mem_gen_v8_4_0

vlog -work xil_defaultlib -64 -incr -sv "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"/home/nsh/programs/Vivado/2017.3/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"/home/nsh/programs/Vivado/2017.3/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -64 -93 \
"/home/nsh/programs/Vivado/2017.3/data/ip/xpm/xpm_VCOMP.vhd" \

vcom -work microblaze_v10_0_4 -64 -93 \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5eb2/hdl/microblaze_v10_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/design_1/ip/design_1_microblaze_0_0/sim/design_1_microblaze_0_0.vhd" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"../../../bd/design_1/ip/design_1_clk_wiz_1_0/design_1_clk_wiz_1_0_clk_wiz.v" \
"../../../bd/design_1/ip/design_1_clk_wiz_1_0/design_1_clk_wiz_1_0.v" \

vcom -work lib_cdc_v1_0_2 -64 -93 \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work proc_sys_reset_v5_0_12 -64 -93 \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/f86a/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/design_1/ip/design_1_rst_clk_wiz_1_100M_0/sim/design_1_rst_clk_wiz_1_100M_0.vhd" \

vcom -work axi_lite_ipif_v3_0_4 -64 -93 \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/cced/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work lib_pkg_v1_0_2 -64 -93 \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \

vcom -work axi_timer_v2_0_16 -64 -93 \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/f3cd/hdl/axi_timer_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/design_1/ip/design_1_axi_timer_0_0/sim/design_1_axi_timer_0_0.vhd" \

vcom -work interrupt_control_v3_1_4 -64 -93 \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/8e66/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_16 -64 -93 \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/e9c1/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/design_1/ip/design_1_axi_gpio_0_0/sim/design_1_axi_gpio_0_0.vhd" \

vlog -work generic_baseblocks_v2_1_0 -64 -incr "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_infrastructure_v1_1_0 -64 -incr "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_14 -64 -incr "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/a259/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_2_0 -64 -incr "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/0798/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_0 -64 -93 \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/0798/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_0 -64 -incr "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/0798/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work axi_data_fifo_v2_1_13 -64 -incr "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/74ae/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_15 -64 -incr "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/a1b8/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"../../../bd/design_1/ip/design_1_xbar_0/sim/design_1_xbar_0.v" \

vcom -work lmb_v10_v3_0_9 -64 -93 \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/78eb/hdl/lmb_v10_v3_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/design_1/ip/design_1_dlmb_v10_0/sim/design_1_dlmb_v10_0.vhd" \
"../../../bd/design_1/ip/design_1_ilmb_v10_0/sim/design_1_ilmb_v10_0.vhd" \

vcom -work lmb_bram_if_cntlr_v4_0_13 -64 -93 \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/0739/hdl/lmb_bram_if_cntlr_v4_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/design_1/ip/design_1_dlmb_bram_if_cntlr_0/sim/design_1_dlmb_bram_if_cntlr_0.vhd" \
"../../../bd/design_1/ip/design_1_ilmb_bram_if_cntlr_0/sim/design_1_ilmb_bram_if_cntlr_0.vhd" \

vlog -work blk_mem_gen_v8_4_0 -64 -incr "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/e50b/simulation/blk_mem_gen_v8_4.v" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/5123" "+incdir+../../../../lab_2.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" \
"../../../bd/design_1/ip/design_1_lmb_bram_0/sim/design_1_lmb_bram_0.v" \
"../../../bd/design_1/sim/design_1.v" \

vlog -work xil_defaultlib \
"glbl.v"

