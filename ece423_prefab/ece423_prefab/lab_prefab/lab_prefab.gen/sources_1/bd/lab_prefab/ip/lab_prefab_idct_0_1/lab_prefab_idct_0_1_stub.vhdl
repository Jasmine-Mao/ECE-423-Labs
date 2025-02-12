-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
-- Date        : Wed Feb 12 13:57:11 2025
-- Host        : ECE-MCU1 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Users/j54mao/ECE423/ECE-423-Labs/ece423_prefab/ece423_prefab/lab_prefab/lab_prefab.gen/sources_1/bd/lab_prefab/ip/lab_prefab_idct_0_1/lab_prefab_idct_0_1_stub.vhdl
-- Design      : lab_prefab_idct_0_1
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity lab_prefab_idct_0_1 is
  Port ( 
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    DCAC_TVALID : in STD_LOGIC;
    DCAC_TREADY : out STD_LOGIC;
    DCAC_TDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    blockout_TVALID : out STD_LOGIC;
    blockout_TREADY : in STD_LOGIC;
    blockout_TDATA : out STD_LOGIC_VECTOR ( 31 downto 0 )
  );

end lab_prefab_idct_0_1;

architecture stub of lab_prefab_idct_0_1 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "ap_clk,ap_rst_n,DCAC_TVALID,DCAC_TREADY,DCAC_TDATA[31:0],blockout_TVALID,blockout_TREADY,blockout_TDATA[31:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "idct,Vivado 2022.1";
begin
end;
