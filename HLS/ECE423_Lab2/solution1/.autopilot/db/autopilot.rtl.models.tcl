set SynModuleInfo {
  {SRCNAME Loop_VITIS_LOOP_39_1_proc1 MODELNAME Loop_VITIS_LOOP_39_1_proc1 RTLNAME idct_Loop_VITIS_LOOP_39_1_proc1
    SUBMODULES {
      {MODELNAME idct_regslice_both RTLNAME idct_regslice_both BINDTYPE interface TYPE interface_regslice INSTNAME idct_regslice_both_U}
      {MODELNAME idct_flow_control_loop_pipe RTLNAME idct_flow_control_loop_pipe BINDTYPE interface TYPE internal_upc_flow_control INSTNAME idct_flow_control_loop_pipe_U}
    }
  }
  {SRCNAME Block_idct_for.cond.i.exit_proc2 MODELNAME Block_idct_for_cond_i_exit_proc2 RTLNAME idct_Block_idct_for_cond_i_exit_proc2
    SUBMODULES {
      {MODELNAME idct_am_addmul_16s_16s_13ns_31_4_1 RTLNAME idct_am_addmul_16s_16s_13ns_31_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_16s_15s_31s_31_4_1 RTLNAME idct_mac_muladd_16s_15s_31s_31_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_16s_13ns_30ns_30_4_1 RTLNAME idct_mac_muladd_16s_13ns_30ns_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_am_addmul_16s_16s_16s_32_4_1 RTLNAME idct_am_addmul_16s_16s_16s_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_am_addmul_17s_17s_14ns_32_4_1 RTLNAME idct_am_addmul_17s_17s_14ns_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_am_addmul_16s_16s_14s_31_4_1 RTLNAME idct_am_addmul_16s_16s_14s_31_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_16s_12ns_31s_31_4_1 RTLNAME idct_mac_muladd_16s_12ns_31s_31_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_16s_14ns_31s_31_4_1 RTLNAME idct_mac_muladd_16s_14ns_31s_31_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_17s_15s_32s_32_4_1 RTLNAME idct_mac_muladd_17s_15s_32s_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_17s_13s_32s_32_4_1 RTLNAME idct_mac_muladd_17s_13s_32s_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_16s_15ns_32s_32_4_1 RTLNAME idct_mac_muladd_16s_15ns_32s_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_am_addmul_16s_16s_13ns_30_4_1 RTLNAME idct_am_addmul_16s_16s_13ns_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_am_addmul_16s_16s_16s_30_4_1 RTLNAME idct_am_addmul_16s_16s_16s_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_am_addmul_17s_17s_14ns_30_4_1 RTLNAME idct_am_addmul_17s_17s_14ns_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_am_addmul_16s_16s_14s_30_4_1 RTLNAME idct_am_addmul_16s_16s_14s_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_16s_15s_30s_30_4_1 RTLNAME idct_mac_muladd_16s_15s_30s_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_16s_13ns_30s_30_4_1 RTLNAME idct_mac_muladd_16s_13ns_30s_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_17s_15s_30s_30_4_1 RTLNAME idct_mac_muladd_17s_15s_30s_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_17s_13s_30s_30_4_1 RTLNAME idct_mac_muladd_17s_13s_30s_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_am_addmul_21s_21s_16s_32_4_1 RTLNAME idct_am_addmul_21s_21s_16s_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_am_addmul_22s_22s_14ns_32_4_1 RTLNAME idct_am_addmul_22s_22s_14ns_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_am_addmul_21s_21s_14s_32_4_1 RTLNAME idct_am_addmul_21s_21s_14s_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_16s_12ns_30s_30_4_1 RTLNAME idct_mac_muladd_16s_12ns_30s_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_16s_15ns_30ns_30_4_1 RTLNAME idct_mac_muladd_16s_15ns_30ns_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_16s_15ns_30s_30_4_1 RTLNAME idct_mac_muladd_16s_15ns_30s_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_16s_14ns_30ns_30_4_1 RTLNAME idct_mac_muladd_16s_14ns_30ns_30_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_am_addmul_21s_21s_13ns_32_4_1 RTLNAME idct_am_addmul_21s_21s_13ns_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_22s_15s_32s_32_4_1 RTLNAME idct_mac_muladd_22s_15s_32s_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_22s_13s_32s_32_4_1 RTLNAME idct_mac_muladd_22s_13s_32s_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_21s_15s_32s_32_4_1 RTLNAME idct_mac_muladd_21s_15s_32s_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_21s_13ns_32s_32_4_1 RTLNAME idct_mac_muladd_21s_13ns_32s_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_21s_12ns_32ns_32_4_1 RTLNAME idct_mac_muladd_21s_12ns_32ns_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_21s_15ns_32ns_32_4_1 RTLNAME idct_mac_muladd_21s_15ns_32ns_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME idct_mac_muladd_21s_14ns_32ns_32_4_1 RTLNAME idct_mac_muladd_21s_14ns_32ns_32_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME idct MODELNAME idct RTLNAME idct IS_TOP 1
    SUBMODULES {
      {MODELNAME idct_DCAC_temp_RAM_AUTO_1R1W_memcore RTLNAME idct_DCAC_temp_RAM_AUTO_1R1W_memcore BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME idct_DCAC_temp_RAM_AUTO_1R1W RTLNAME idct_DCAC_temp_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2}
    }
  }
}
