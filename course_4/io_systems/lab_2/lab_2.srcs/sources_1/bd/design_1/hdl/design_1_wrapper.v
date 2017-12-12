//Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2017.3 (win64) Build 2018833 Wed Oct  4 19:58:22 MDT 2017
//Date        : Tue Dec 12 14:11:37 2017
//Host        : TS_Comp running 64-bit Service Pack 1  (build 7601)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (capturetrig0,
    clock_rtl,
    generateout0,
    gpio_rtl_tri_o,
    pwm0,
    reset_rtl);
  input capturetrig0;
  input clock_rtl;
  output generateout0;
  output [15:0]gpio_rtl_tri_o;
  output pwm0;
  input reset_rtl;

  wire capturetrig0;
  wire clock_rtl;
  wire generateout0;
  wire [15:0]gpio_rtl_tri_o;
  wire pwm0;
  wire reset_rtl;

  design_1 design_1_i
       (.capturetrig0(capturetrig0),
        .clock_rtl(clock_rtl),
        .generateout0(generateout0),
        .gpio_rtl_tri_o(gpio_rtl_tri_o),
        .pwm0(pwm0),
        .reset_rtl(reset_rtl));
endmodule
