
`include "dump_file_agent.svh"
`include "csv_file_dump.svh"
`include "sample_agent.svh"
`include "sample_manager.svh"
`include "nodf_module_interface.svh"
`include "nodf_module_monitor.svh"
`include "df_process_interface.svh"
`include "df_process_monitor.svh"
`timescale 1ns/1ps

// top module for dataflow related monitors
module dataflow_monitor(
input logic clock,
input logic reset,
input logic finish
);


logic region_0_idle;
assign region_0_idle = 1'b0;


    df_process_intf process_intf_1(clock,reset);
    assign process_intf_1.ap_start = AESL_inst_idct.Block_entry687_proc1_U0.ap_start;
    assign process_intf_1.ap_ready = AESL_inst_idct.Block_entry687_proc1_U0.ap_ready;
    assign process_intf_1.ap_done = AESL_inst_idct.Block_entry687_proc1_U0.ap_done;
    assign process_intf_1.ap_continue = AESL_inst_idct.Block_entry687_proc1_U0.ap_continue;
    assign process_intf_1.real_start = AESL_inst_idct.Block_entry687_proc1_U0.ap_start;
    assign process_intf_1.pin_stall = 1'b0;
    assign process_intf_1.pout_stall = 1'b0;
    assign process_intf_1.cin_stall = 1'b0;
    assign process_intf_1.cout_stall = 1'b0;
    assign process_intf_1.region_idle = region_0_idle;
    assign process_intf_1.finish = finish;
    csv_file_dump pstall_csv_dumper_1;
    csv_file_dump pstatus_csv_dumper_1;
    df_process_monitor process_monitor_1;

    nodf_module_intf module_intf_1(clock,reset);
    assign module_intf_1.ap_start = 1'b0;
    assign module_intf_1.ap_ready = 1'b0;
    assign module_intf_1.ap_done = 1'b0;
    assign module_intf_1.ap_continue = 1'b0;
    assign module_intf_1.finish = finish;
    csv_file_dump mstatus_csv_dumper_1;
    nodf_module_monitor module_monitor_1;


    sample_manager sample_manager_inst;

initial begin
    sample_manager_inst = new;


    pstall_csv_dumper_1 = new("./stalling1.csv");
    pstatus_csv_dumper_1 = new("./status1.csv");
    process_monitor_1 = new(pstall_csv_dumper_1,process_intf_1,pstatus_csv_dumper_1);

    mstatus_csv_dumper_1 = new("./module_status1.csv");
    module_monitor_1 = new(module_intf_1,mstatus_csv_dumper_1);





    sample_manager_inst.add_one_monitor(process_monitor_1);
    sample_manager_inst.add_one_monitor(module_monitor_1);
    
    fork
        sample_manager_inst.start_monitor();
        last_transaction_done;
    join
    disable fork;

    sample_manager_inst.start_dump();
end

    task last_transaction_done();
        wait(reset == 0);
        while(1) begin
            if (finish == 1'b1) begin
                @(negedge clock);
                break;
            end
            else
                @(posedge clock);
        end
    endtask


endmodule
