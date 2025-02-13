# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\hmcculla\ECE423\ECE-423-Labs\workspace\Assignment2_debugging\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\hmcculla\ECE423\ECE-423-Labs\workspace\Assignment2_debugging\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Assignment2_debugging}\
-hw {C:\Users\hmcculla\ECE423\ECE-423-Labs\Assignment2_debugging\lab_prefab_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/hmcculla/ECE423/ECE-423-Labs/workspace}

platform write
platform generate -domains 
platform active {Assignment2_debugging}
platform generate
bsp reload
bsp setlib -name xilffs -ver 4.7
bsp config enable_exfat "false"
bsp config enable_multi_partition "true"
bsp config fs_interface "1"
bsp config num_logical_vol "10"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
domain active {zynq_fsbl}
bsp reload
bsp reload
platform generate -domains 
platform generate
platform generate
platform active {Assignment2_debugging}
bsp reload
domain active {standalone_domain}
bsp reload
domain active {zynq_fsbl}
bsp reload
domain active {standalone_domain}
bsp reload
domain active {zynq_fsbl}
bsp reload
platform generate -domains 
platform generate
