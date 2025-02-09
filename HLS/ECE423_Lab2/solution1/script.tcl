############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project ECE423_Lab2
set_top idct
add_files ../import_files/import_files/util.h
add_files ../import_files/import_files/util.c
add_files ../import_files/import_files/tables.c
add_files ../import_files/import_files/mjpeg423_types.h
add_files ../import_files/import_files/dct_math.h
add_files ../import_files/import_files/2D_idct.h
add_files ../import_files/import_files/2D_idct.cpp
add_files -tb ../Testbenches/idct_tb_1.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 10 -name default
config_export -format ip_catalog -output C:/Users/hmcculla/ECE423/ECE-423-Labs/IDCT_Accel_IP_Block -rtl verilog
set_clock_uncertainty 1.25
source "./ECE423_Lab2/solution1/directives.tcl"
csim_design -clean -setup
csynth_design
cosim_design -wave_debug -trace_level all
export_design -rtl verilog -format ip_catalog -output C:/Users/hmcculla/ECE423/ECE-423-Labs/IDCT_Accel_IP_Block
