//Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2017.3 (lin64) Build 2018833 Wed Oct  4 19:58:07 MDT 2017
//Date        : Sat Nov 25 18:23:31 2017
//Host        : nsh-VirtualBox running 64-bit Ubuntu 16.04.3 LTS
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (diff_clock_rtl_0_clk_n,
    diff_clock_rtl_0_clk_p,
    generateout0,
    gpio_rtl_0_tri_io,
    pwm0,
    reset_rtl_0);
  input diff_clock_rtl_0_clk_n;
  input diff_clock_rtl_0_clk_p;
  output generateout0;
  inout [15:0]gpio_rtl_0_tri_io;
  output pwm0;
  input reset_rtl_0;

  wire diff_clock_rtl_0_clk_n;
  wire diff_clock_rtl_0_clk_p;
  wire generateout0;
  wire [0:0]gpio_rtl_0_tri_i_0;
  wire [1:1]gpio_rtl_0_tri_i_1;
  wire [10:10]gpio_rtl_0_tri_i_10;
  wire [11:11]gpio_rtl_0_tri_i_11;
  wire [12:12]gpio_rtl_0_tri_i_12;
  wire [13:13]gpio_rtl_0_tri_i_13;
  wire [14:14]gpio_rtl_0_tri_i_14;
  wire [15:15]gpio_rtl_0_tri_i_15;
  wire [2:2]gpio_rtl_0_tri_i_2;
  wire [3:3]gpio_rtl_0_tri_i_3;
  wire [4:4]gpio_rtl_0_tri_i_4;
  wire [5:5]gpio_rtl_0_tri_i_5;
  wire [6:6]gpio_rtl_0_tri_i_6;
  wire [7:7]gpio_rtl_0_tri_i_7;
  wire [8:8]gpio_rtl_0_tri_i_8;
  wire [9:9]gpio_rtl_0_tri_i_9;
  wire [0:0]gpio_rtl_0_tri_io_0;
  wire [1:1]gpio_rtl_0_tri_io_1;
  wire [10:10]gpio_rtl_0_tri_io_10;
  wire [11:11]gpio_rtl_0_tri_io_11;
  wire [12:12]gpio_rtl_0_tri_io_12;
  wire [13:13]gpio_rtl_0_tri_io_13;
  wire [14:14]gpio_rtl_0_tri_io_14;
  wire [15:15]gpio_rtl_0_tri_io_15;
  wire [2:2]gpio_rtl_0_tri_io_2;
  wire [3:3]gpio_rtl_0_tri_io_3;
  wire [4:4]gpio_rtl_0_tri_io_4;
  wire [5:5]gpio_rtl_0_tri_io_5;
  wire [6:6]gpio_rtl_0_tri_io_6;
  wire [7:7]gpio_rtl_0_tri_io_7;
  wire [8:8]gpio_rtl_0_tri_io_8;
  wire [9:9]gpio_rtl_0_tri_io_9;
  wire [0:0]gpio_rtl_0_tri_o_0;
  wire [1:1]gpio_rtl_0_tri_o_1;
  wire [10:10]gpio_rtl_0_tri_o_10;
  wire [11:11]gpio_rtl_0_tri_o_11;
  wire [12:12]gpio_rtl_0_tri_o_12;
  wire [13:13]gpio_rtl_0_tri_o_13;
  wire [14:14]gpio_rtl_0_tri_o_14;
  wire [15:15]gpio_rtl_0_tri_o_15;
  wire [2:2]gpio_rtl_0_tri_o_2;
  wire [3:3]gpio_rtl_0_tri_o_3;
  wire [4:4]gpio_rtl_0_tri_o_4;
  wire [5:5]gpio_rtl_0_tri_o_5;
  wire [6:6]gpio_rtl_0_tri_o_6;
  wire [7:7]gpio_rtl_0_tri_o_7;
  wire [8:8]gpio_rtl_0_tri_o_8;
  wire [9:9]gpio_rtl_0_tri_o_9;
  wire [0:0]gpio_rtl_0_tri_t_0;
  wire [1:1]gpio_rtl_0_tri_t_1;
  wire [10:10]gpio_rtl_0_tri_t_10;
  wire [11:11]gpio_rtl_0_tri_t_11;
  wire [12:12]gpio_rtl_0_tri_t_12;
  wire [13:13]gpio_rtl_0_tri_t_13;
  wire [14:14]gpio_rtl_0_tri_t_14;
  wire [15:15]gpio_rtl_0_tri_t_15;
  wire [2:2]gpio_rtl_0_tri_t_2;
  wire [3:3]gpio_rtl_0_tri_t_3;
  wire [4:4]gpio_rtl_0_tri_t_4;
  wire [5:5]gpio_rtl_0_tri_t_5;
  wire [6:6]gpio_rtl_0_tri_t_6;
  wire [7:7]gpio_rtl_0_tri_t_7;
  wire [8:8]gpio_rtl_0_tri_t_8;
  wire [9:9]gpio_rtl_0_tri_t_9;
  wire pwm0;
  wire reset_rtl_0;

  design_1 design_1_i
       (.diff_clock_rtl_0_clk_n(diff_clock_rtl_0_clk_n),
        .diff_clock_rtl_0_clk_p(diff_clock_rtl_0_clk_p),
        .generateout0(generateout0),
        .gpio_rtl_0_tri_i({gpio_rtl_0_tri_i_15,gpio_rtl_0_tri_i_14,gpio_rtl_0_tri_i_13,gpio_rtl_0_tri_i_12,gpio_rtl_0_tri_i_11,gpio_rtl_0_tri_i_10,gpio_rtl_0_tri_i_9,gpio_rtl_0_tri_i_8,gpio_rtl_0_tri_i_7,gpio_rtl_0_tri_i_6,gpio_rtl_0_tri_i_5,gpio_rtl_0_tri_i_4,gpio_rtl_0_tri_i_3,gpio_rtl_0_tri_i_2,gpio_rtl_0_tri_i_1,gpio_rtl_0_tri_i_0}),
        .gpio_rtl_0_tri_o({gpio_rtl_0_tri_o_15,gpio_rtl_0_tri_o_14,gpio_rtl_0_tri_o_13,gpio_rtl_0_tri_o_12,gpio_rtl_0_tri_o_11,gpio_rtl_0_tri_o_10,gpio_rtl_0_tri_o_9,gpio_rtl_0_tri_o_8,gpio_rtl_0_tri_o_7,gpio_rtl_0_tri_o_6,gpio_rtl_0_tri_o_5,gpio_rtl_0_tri_o_4,gpio_rtl_0_tri_o_3,gpio_rtl_0_tri_o_2,gpio_rtl_0_tri_o_1,gpio_rtl_0_tri_o_0}),
        .gpio_rtl_0_tri_t({gpio_rtl_0_tri_t_15,gpio_rtl_0_tri_t_14,gpio_rtl_0_tri_t_13,gpio_rtl_0_tri_t_12,gpio_rtl_0_tri_t_11,gpio_rtl_0_tri_t_10,gpio_rtl_0_tri_t_9,gpio_rtl_0_tri_t_8,gpio_rtl_0_tri_t_7,gpio_rtl_0_tri_t_6,gpio_rtl_0_tri_t_5,gpio_rtl_0_tri_t_4,gpio_rtl_0_tri_t_3,gpio_rtl_0_tri_t_2,gpio_rtl_0_tri_t_1,gpio_rtl_0_tri_t_0}),
        .pwm0(pwm0),
        .reset_rtl_0(reset_rtl_0));
  IOBUF gpio_rtl_0_tri_iobuf_0
       (.I(gpio_rtl_0_tri_o_0),
        .IO(gpio_rtl_0_tri_io[0]),
        .O(gpio_rtl_0_tri_i_0),
        .T(gpio_rtl_0_tri_t_0));
  IOBUF gpio_rtl_0_tri_iobuf_1
       (.I(gpio_rtl_0_tri_o_1),
        .IO(gpio_rtl_0_tri_io[1]),
        .O(gpio_rtl_0_tri_i_1),
        .T(gpio_rtl_0_tri_t_1));
  IOBUF gpio_rtl_0_tri_iobuf_10
       (.I(gpio_rtl_0_tri_o_10),
        .IO(gpio_rtl_0_tri_io[10]),
        .O(gpio_rtl_0_tri_i_10),
        .T(gpio_rtl_0_tri_t_10));
  IOBUF gpio_rtl_0_tri_iobuf_11
       (.I(gpio_rtl_0_tri_o_11),
        .IO(gpio_rtl_0_tri_io[11]),
        .O(gpio_rtl_0_tri_i_11),
        .T(gpio_rtl_0_tri_t_11));
  IOBUF gpio_rtl_0_tri_iobuf_12
       (.I(gpio_rtl_0_tri_o_12),
        .IO(gpio_rtl_0_tri_io[12]),
        .O(gpio_rtl_0_tri_i_12),
        .T(gpio_rtl_0_tri_t_12));
  IOBUF gpio_rtl_0_tri_iobuf_13
       (.I(gpio_rtl_0_tri_o_13),
        .IO(gpio_rtl_0_tri_io[13]),
        .O(gpio_rtl_0_tri_i_13),
        .T(gpio_rtl_0_tri_t_13));
  IOBUF gpio_rtl_0_tri_iobuf_14
       (.I(gpio_rtl_0_tri_o_14),
        .IO(gpio_rtl_0_tri_io[14]),
        .O(gpio_rtl_0_tri_i_14),
        .T(gpio_rtl_0_tri_t_14));
  IOBUF gpio_rtl_0_tri_iobuf_15
       (.I(gpio_rtl_0_tri_o_15),
        .IO(gpio_rtl_0_tri_io[15]),
        .O(gpio_rtl_0_tri_i_15),
        .T(gpio_rtl_0_tri_t_15));
  IOBUF gpio_rtl_0_tri_iobuf_2
       (.I(gpio_rtl_0_tri_o_2),
        .IO(gpio_rtl_0_tri_io[2]),
        .O(gpio_rtl_0_tri_i_2),
        .T(gpio_rtl_0_tri_t_2));
  IOBUF gpio_rtl_0_tri_iobuf_3
       (.I(gpio_rtl_0_tri_o_3),
        .IO(gpio_rtl_0_tri_io[3]),
        .O(gpio_rtl_0_tri_i_3),
        .T(gpio_rtl_0_tri_t_3));
  IOBUF gpio_rtl_0_tri_iobuf_4
       (.I(gpio_rtl_0_tri_o_4),
        .IO(gpio_rtl_0_tri_io[4]),
        .O(gpio_rtl_0_tri_i_4),
        .T(gpio_rtl_0_tri_t_4));
  IOBUF gpio_rtl_0_tri_iobuf_5
       (.I(gpio_rtl_0_tri_o_5),
        .IO(gpio_rtl_0_tri_io[5]),
        .O(gpio_rtl_0_tri_i_5),
        .T(gpio_rtl_0_tri_t_5));
  IOBUF gpio_rtl_0_tri_iobuf_6
       (.I(gpio_rtl_0_tri_o_6),
        .IO(gpio_rtl_0_tri_io[6]),
        .O(gpio_rtl_0_tri_i_6),
        .T(gpio_rtl_0_tri_t_6));
  IOBUF gpio_rtl_0_tri_iobuf_7
       (.I(gpio_rtl_0_tri_o_7),
        .IO(gpio_rtl_0_tri_io[7]),
        .O(gpio_rtl_0_tri_i_7),
        .T(gpio_rtl_0_tri_t_7));
  IOBUF gpio_rtl_0_tri_iobuf_8
       (.I(gpio_rtl_0_tri_o_8),
        .IO(gpio_rtl_0_tri_io[8]),
        .O(gpio_rtl_0_tri_i_8),
        .T(gpio_rtl_0_tri_t_8));
  IOBUF gpio_rtl_0_tri_iobuf_9
       (.I(gpio_rtl_0_tri_o_9),
        .IO(gpio_rtl_0_tri_io[9]),
        .O(gpio_rtl_0_tri_i_9),
        .T(gpio_rtl_0_tri_t_9));
endmodule
