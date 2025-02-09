// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
// Date        : Sun Feb  9 13:36:03 2025
// Host        : ECE-MCU21 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ lab_prefab_idct_0_0_stub.v
// Design      : lab_prefab_idct_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "idct,Vivado 2022.1" *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix(ap_clk, ap_rst_n, DCAC_TVALID, DCAC_TREADY, 
  DCAC_TDATA, blockout_TVALID, blockout_TREADY, blockout_TDATA)
/* synthesis syn_black_box black_box_pad_pin="ap_clk,ap_rst_n,DCAC_TVALID,DCAC_TREADY,DCAC_TDATA[15:0],blockout_TVALID,blockout_TREADY,blockout_TDATA[7:0]" */;
  input ap_clk;
  input ap_rst_n;
  input DCAC_TVALID;
  output DCAC_TREADY;
  input [15:0]DCAC_TDATA;
  output blockout_TVALID;
  input blockout_TREADY;
  output [7:0]blockout_TDATA;
endmodule
