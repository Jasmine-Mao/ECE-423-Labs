// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __idct_am_addmul_16s_16s_16s_30_4_1__HH__
#define __idct_am_addmul_16s_16s_16s_30_4_1__HH__
#include "idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11.h"
#include <systemc>

template<
    int ID,
    int NUM_STAGE,
    int din0_WIDTH,
    int din1_WIDTH,
    int din2_WIDTH,
    int dout_WIDTH>
SC_MODULE(idct_am_addmul_16s_16s_16s_30_4_1) {
    sc_core::sc_in_clk clk;
    sc_core::sc_in<sc_dt::sc_logic> reset;
    sc_core::sc_in<sc_dt::sc_logic> ce;
    sc_core::sc_in< sc_dt::sc_lv<din0_WIDTH> >   din0;
    sc_core::sc_in< sc_dt::sc_lv<din1_WIDTH> >   din1;
    sc_core::sc_in< sc_dt::sc_lv<din2_WIDTH> >   din2;
    sc_core::sc_out< sc_dt::sc_lv<dout_WIDTH> >   dout;



    idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11 idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11_U;

    SC_CTOR(idct_am_addmul_16s_16s_16s_30_4_1):  idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11_U ("idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11_U") {
        idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11_U.clk(clk);
        idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11_U.rst(reset);
        idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11_U.ce(ce);
        idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11_U.in0(din0);
        idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11_U.in1(din1);
        idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11_U.in2(din2);
        idct_am_addmul_16s_16s_16s_30_4_1_DSP48_11_U.dout(dout);

    }

};

#endif //
