// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
// Date        : Wed Feb 12 16:34:53 2025
// Host        : ECE-MCU21 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/hmcculla/ECE423/ECE-423-Labs/ece423_prefab/ece423_prefab/lab_prefab/lab_prefab.gen/sources_1/bd/lab_prefab/ip/lab_prefab_idct_0_2/lab_prefab_idct_0_2_stub.v
// Design      : lab_prefab_idct_0_2
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "idct,Vivado 2022.1" *)
module lab_prefab_idct_0_2(DCAC_TVALID, DCAC_TREADY, DCAC_TDATA, 
  blockout_TVALID, blockout_TREADY, blockout_TDATA, ap_clk, ap_rst_n)
/* synthesis syn_black_box black_box_pad_pin="DCAC_TVALID,DCAC_TREADY,DCAC_TDATA[31:0],blockout_TVALID,blockout_TREADY,blockout_TDATA[31:0],ap_clk,ap_rst_n" */;
  input DCAC_TVALID;
  output DCAC_TREADY;
  input [31:0]DCAC_TDATA;
  output blockout_TVALID;
  input blockout_TREADY;
  output [31:0]blockout_TDATA;
  input ap_clk;
  input ap_rst_n;
endmodule
