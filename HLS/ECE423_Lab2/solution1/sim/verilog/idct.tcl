
log_wave -r /
set designtopgroup [add_wave_group "Design Top Signals"]
set coutputgroup [add_wave_group "C Outputs" -into $designtopgroup]
set return_group [add_wave_group return(axis) -into $coutputgroup]
add_wave /apatb_idct_top/AESL_inst_idct/blockout_TREADY -into $return_group -color #ffff00 -radix hex
add_wave /apatb_idct_top/AESL_inst_idct/blockout_TVALID -into $return_group -color #ffff00 -radix hex
add_wave /apatb_idct_top/AESL_inst_idct/blockout_TDATA -into $return_group -radix hex
set cinputgroup [add_wave_group "C Inputs" -into $designtopgroup]
set return_group [add_wave_group return(axis) -into $cinputgroup]
add_wave /apatb_idct_top/AESL_inst_idct/DCAC_TREADY -into $return_group -color #ffff00 -radix hex
add_wave /apatb_idct_top/AESL_inst_idct/DCAC_TVALID -into $return_group -color #ffff00 -radix hex
add_wave /apatb_idct_top/AESL_inst_idct/DCAC_TDATA -into $return_group -radix hex
set resetgroup [add_wave_group "Reset" -into $designtopgroup]
add_wave /apatb_idct_top/AESL_inst_idct/ap_rst_n -into $resetgroup
set clockgroup [add_wave_group "Clock" -into $designtopgroup]
add_wave /apatb_idct_top/AESL_inst_idct/ap_clk -into $clockgroup
set testbenchgroup [add_wave_group "Test Bench Signals"]
set tbinternalsiggroup [add_wave_group "Internal Signals" -into $testbenchgroup]
set tb_simstatus_group [add_wave_group "Simulation Status" -into $tbinternalsiggroup]
set tb_portdepth_group [add_wave_group "Port Depth" -into $tbinternalsiggroup]
add_wave /apatb_idct_top/AUTOTB_TRANSACTION_NUM -into $tb_simstatus_group -radix hex
add_wave /apatb_idct_top/ready_cnt -into $tb_simstatus_group -radix hex
add_wave /apatb_idct_top/done_cnt -into $tb_simstatus_group -radix hex
add_wave /apatb_idct_top/ap_c_n_tvin_trans_num_DCAC -into $tb_simstatus_group -radix hex
add_wave /apatb_idct_top/ap_c_n_tvout_trans_num_blockout -into $tb_simstatus_group -radix hex
add_wave /apatb_idct_top/LENGTH_DCAC -into $tb_portdepth_group -radix hex
add_wave /apatb_idct_top/LENGTH_blockout -into $tb_portdepth_group -radix hex
set tbcoutputgroup [add_wave_group "C Outputs" -into $testbenchgroup]
set tb_return_group [add_wave_group return(axis) -into $tbcoutputgroup]
add_wave /apatb_idct_top/blockout_TREADY -into $tb_return_group -color #ffff00 -radix hex
add_wave /apatb_idct_top/blockout_TVALID -into $tb_return_group -color #ffff00 -radix hex
add_wave /apatb_idct_top/blockout_TDATA -into $tb_return_group -radix hex
set tbcinputgroup [add_wave_group "C Inputs" -into $testbenchgroup]
set tb_return_group [add_wave_group return(axis) -into $tbcinputgroup]
add_wave /apatb_idct_top/DCAC_TREADY -into $tb_return_group -color #ffff00 -radix hex
add_wave /apatb_idct_top/DCAC_TVALID -into $tb_return_group -color #ffff00 -radix hex
add_wave /apatb_idct_top/DCAC_TDATA -into $tb_return_group -radix hex
save_wave_config idct.wcfg
run all

