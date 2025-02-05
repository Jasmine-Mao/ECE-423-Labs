set moduleName idct
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type dataflow
set FunctionProtocol ap_ctrl_none
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set C_modelName {idct}
set C_modelType { void 0 }
set C_modelArgList {
	{ DCAC int 16 regular {axi_s 0 volatile  { DCAC Data } }  }
	{ blockout int 8 regular {axi_s 1 volatile  { blockout Data } }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "DCAC", "interface" : "axis", "bitwidth" : 16, "direction" : "READONLY"} , 
 	{ "Name" : "blockout", "interface" : "axis", "bitwidth" : 8, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 8
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst_n sc_in sc_logic 1 reset -1 active_low_sync } 
	{ DCAC_TDATA sc_in sc_lv 16 signal 0 } 
	{ blockout_TDATA sc_out sc_lv 8 signal 1 } 
	{ DCAC_TVALID sc_in sc_logic 1 invld 0 } 
	{ DCAC_TREADY sc_out sc_logic 1 inacc 0 } 
	{ blockout_TVALID sc_out sc_logic 1 outvld 1 } 
	{ blockout_TREADY sc_in sc_logic 1 outacc 1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst_n", "role": "default" }} , 
 	{ "name": "DCAC_TDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":16, "type": "signal", "bundle":{"name": "DCAC", "role": "TDATA" }} , 
 	{ "name": "blockout_TDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "blockout", "role": "TDATA" }} , 
 	{ "name": "DCAC_TVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "invld", "bundle":{"name": "DCAC", "role": "TVALID" }} , 
 	{ "name": "DCAC_TREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "inacc", "bundle":{"name": "DCAC", "role": "TREADY" }} , 
 	{ "name": "blockout_TVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "blockout", "role": "TVALID" }} , 
 	{ "name": "blockout_TREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "outacc", "bundle":{"name": "blockout", "role": "TREADY" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "6", "32"],
		"CDFG" : "idct",
		"Protocol" : "ap_ctrl_none",
		"ControlExist" : "0", "ap_start" : "0", "ap_ready" : "0", "ap_done" : "0", "ap_continue" : "0", "ap_idle" : "0", "real_start" : "0",
		"Pipeline" : "Dataflow", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "1",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "194", "EstimateLatencyMax" : "194",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "1",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"InputProcess" : [
			{"ID" : "3", "Name" : "Loop_VITIS_LOOP_38_1_proc1_U0"}],
		"OutputProcess" : [
			{"ID" : "32", "Name" : "Loop_VITIS_LOOP_130_3_proc2_U0"}],
		"Port" : [
			{"Name" : "DCAC", "Type" : "Axis", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "3", "SubInstance" : "Loop_VITIS_LOOP_38_1_proc1_U0", "Port" : "DCAC"}]},
			{"Name" : "blockout", "Type" : "Axis", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "32", "SubInstance" : "Loop_VITIS_LOOP_130_3_proc2_U0", "Port" : "blockout"}]}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.DCAC_temp_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.workspace_U", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_38_1_proc1_U0", "Parent" : "0", "Child" : ["4", "5"],
		"CDFG" : "Loop_VITIS_LOOP_38_1_proc1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "66", "EstimateLatencyMax" : "66",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "DCAC", "Type" : "Axis", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "DCAC_TDATA_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "DCAC_temp", "Type" : "Memory", "Direction" : "O", "DependentProc" : ["6"], "DependentChan" : "1"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_38_1_DCAC_col_copy", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter1", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter0", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "1"}}]},
	{"ID" : "4", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_38_1_proc1_U0.flow_control_loop_pipe_U", "Parent" : "3"},
	{"ID" : "5", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_38_1_proc1_U0.regslice_both_DCAC_U", "Parent" : "3"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0", "Parent" : "0", "Child" : ["7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"],
		"CDFG" : "Loop_VITIS_LOOP_59_2_proc",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "51", "EstimateLatencyMax" : "51",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "DCAC_temp", "Type" : "Memory", "Direction" : "I", "DependentProc" : ["3"], "DependentChan" : "1"},
			{"Name" : "workspace", "Type" : "Memory", "Direction" : "O", "DependentProc" : ["32"], "DependentChan" : "2"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_59_2", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "10", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage9", "LastStateIter" : "ap_enable_reg_pp0_iter1", "LastStateBlock" : "ap_block_pp0_stage9_subdone", "QuitState" : "ap_ST_fsm_pp0_stage9", "QuitStateIter" : "ap_enable_reg_pp0_iter1", "QuitStateBlock" : "ap_block_pp0_stage9_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "1"}}]},
	{"ID" : "7", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.am_addmul_16s_16s_13ns_31_4_1_U4", "Parent" : "6"},
	{"ID" : "8", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_15s_31s_31_4_1_U5", "Parent" : "6"},
	{"ID" : "9", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_13ns_30ns_30_4_1_U6", "Parent" : "6"},
	{"ID" : "10", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.am_addmul_16s_16s_16s_32_4_1_U7", "Parent" : "6"},
	{"ID" : "11", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.am_addmul_17s_17s_14ns_32_4_1_U8", "Parent" : "6"},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.am_addmul_16s_16s_14s_31_4_1_U9", "Parent" : "6"},
	{"ID" : "13", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_14ns_31s_31_4_1_U10", "Parent" : "6"},
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_17s_15s_32s_32_4_1_U11", "Parent" : "6"},
	{"ID" : "15", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_12ns_31s_31_4_1_U12", "Parent" : "6"},
	{"ID" : "16", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_15ns_32s_32_4_1_U13", "Parent" : "6"},
	{"ID" : "17", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_17s_13s_32s_32_4_1_U14", "Parent" : "6"},
	{"ID" : "18", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.am_addmul_16s_16s_16s_32_4_1_U15", "Parent" : "6"},
	{"ID" : "19", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.am_addmul_17s_17s_14ns_32_4_1_U16", "Parent" : "6"},
	{"ID" : "20", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.am_addmul_16s_16s_14s_31_4_1_U17", "Parent" : "6"},
	{"ID" : "21", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.am_addmul_16s_16s_13ns_31_4_1_U18", "Parent" : "6"},
	{"ID" : "22", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_14ns_31s_31_4_1_U19", "Parent" : "6"},
	{"ID" : "23", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_17s_15s_32s_32_4_1_U20", "Parent" : "6"},
	{"ID" : "24", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_17s_13s_32s_32_4_1_U21", "Parent" : "6"},
	{"ID" : "25", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_15ns_32s_32_4_1_U22", "Parent" : "6"},
	{"ID" : "26", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_15s_31s_31_4_1_U23", "Parent" : "6"},
	{"ID" : "27", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_13ns_30ns_30_4_1_U24", "Parent" : "6"},
	{"ID" : "28", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_12ns_31s_31_4_1_U25", "Parent" : "6"},
	{"ID" : "29", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_15ns_32s_32_4_1_U26", "Parent" : "6"},
	{"ID" : "30", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.mac_muladd_16s_15ns_32s_32_4_1_U27", "Parent" : "6"},
	{"ID" : "31", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_59_2_proc_U0.flow_control_loop_pipe_U", "Parent" : "6"},
	{"ID" : "32", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0", "Parent" : "0", "Child" : ["33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58"],
		"CDFG" : "Loop_VITIS_LOOP_130_3_proc2",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "75", "EstimateLatencyMax" : "75",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "workspace", "Type" : "Memory", "Direction" : "I", "DependentProc" : ["6"], "DependentChan" : "2"},
			{"Name" : "blockout", "Type" : "Axis", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "blockout_TDATA_blk_n", "Type" : "RtlSignal"}]}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_130_3", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "16", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage9", "LastStateIter" : "ap_enable_reg_pp0_iter1", "LastStateBlock" : "ap_block_pp0_stage9_subdone", "QuitState" : "ap_ST_fsm_pp0_stage9", "QuitStateIter" : "ap_enable_reg_pp0_iter1", "QuitStateBlock" : "ap_block_pp0_stage9_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "1"}}]},
	{"ID" : "33", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.am_addmul_21s_21s_16s_32_4_1_U41", "Parent" : "32"},
	{"ID" : "34", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.am_addmul_21s_21s_14s_32_4_1_U42", "Parent" : "32"},
	{"ID" : "35", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.am_addmul_21s_21s_13ns_32_4_1_U43", "Parent" : "32"},
	{"ID" : "36", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.am_addmul_22s_22s_14ns_32_4_1_U44", "Parent" : "32"},
	{"ID" : "37", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_13ns_32s_32_4_1_U45", "Parent" : "32"},
	{"ID" : "38", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_22s_13s_32s_32_4_1_U46", "Parent" : "32"},
	{"ID" : "39", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_14ns_32ns_32_4_1_U47", "Parent" : "32"},
	{"ID" : "40", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_22s_15s_32s_32_4_1_U48", "Parent" : "32"},
	{"ID" : "41", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_15s_32s_32_4_1_U49", "Parent" : "32"},
	{"ID" : "42", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_15ns_32ns_32_4_1_U50", "Parent" : "32"},
	{"ID" : "43", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_12ns_32ns_32_4_1_U51", "Parent" : "32"},
	{"ID" : "44", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_15ns_32ns_32_4_1_U52", "Parent" : "32"},
	{"ID" : "45", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.am_addmul_21s_21s_13ns_32_4_1_U53", "Parent" : "32"},
	{"ID" : "46", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.am_addmul_22s_22s_14ns_32_4_1_U54", "Parent" : "32"},
	{"ID" : "47", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_13ns_32s_32_4_1_U55", "Parent" : "32"},
	{"ID" : "48", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.am_addmul_21s_21s_16s_32_4_1_U56", "Parent" : "32"},
	{"ID" : "49", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.am_addmul_21s_21s_14s_32_4_1_U57", "Parent" : "32"},
	{"ID" : "50", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_22s_13s_32s_32_4_1_U58", "Parent" : "32"},
	{"ID" : "51", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_14ns_32ns_32_4_1_U59", "Parent" : "32"},
	{"ID" : "52", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_22s_15s_32s_32_4_1_U60", "Parent" : "32"},
	{"ID" : "53", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_15s_32s_32_4_1_U61", "Parent" : "32"},
	{"ID" : "54", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_15ns_32ns_32_4_1_U62", "Parent" : "32"},
	{"ID" : "55", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_12ns_32ns_32_4_1_U63", "Parent" : "32"},
	{"ID" : "56", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.mac_muladd_21s_15ns_32ns_32_4_1_U64", "Parent" : "32"},
	{"ID" : "57", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.flow_control_loop_pipe_U", "Parent" : "32"},
	{"ID" : "58", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.Loop_VITIS_LOOP_130_3_proc2_U0.regslice_both_blockout_U", "Parent" : "32"}]}


set ArgLastReadFirstWriteLatency {
	idct {
		DCAC {Type I LastRead 0 FirstWrite -1}
		blockout {Type O LastRead -1 FirstWrite 9}}
	Loop_VITIS_LOOP_38_1_proc1 {
		DCAC {Type I LastRead 0 FirstWrite -1}
		DCAC_temp {Type O LastRead -1 FirstWrite 1}}
	Loop_VITIS_LOOP_59_2_proc {
		DCAC_temp {Type I LastRead 8 FirstWrite -1}
		workspace {Type O LastRead -1 FirstWrite 10}}
	Loop_VITIS_LOOP_130_3_proc2 {
		workspace {Type I LastRead 8 FirstWrite -1}
		blockout {Type O LastRead -1 FirstWrite 9}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "194", "Max" : "194"}
	, {"Name" : "Interval", "Min" : "76", "Max" : "76"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	DCAC { axis {  { DCAC_TDATA in_data 0 16 }  { DCAC_TVALID in_vld 0 1 }  { DCAC_TREADY in_acc 1 1 } } }
	blockout { axis {  { blockout_TDATA out_data 1 8 }  { blockout_TVALID out_vld 1 1 }  { blockout_TREADY out_acc 0 1 } } }
}

set maxi_interface_dict [dict create]

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
