############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project ECE423_Lab2
set_top idct
add_files ../../../Downloads/import_files/import_files/2D_idct.cc
add_files ../../../Downloads/import_files/import_files/dct_math.h
add_files ../../../Downloads/import_files/import_files/mjpeg423_types.h
add_files ../../../Downloads/import_files/import_files/tables.c
add_files ../../../Downloads/import_files/import_files/util.c
add_files ../../../Downloads/import_files/import_files/util.h
add_files -tb ../../../Downloads/idct_2d_tb_1.txt
add_files -tb ../../../Downloads/idct_2d_tb_2.txt
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg400-1}
create_clock -period 10 -name default
set_clock_uncertainty 1.25
#source "./ECE423_Lab2/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
