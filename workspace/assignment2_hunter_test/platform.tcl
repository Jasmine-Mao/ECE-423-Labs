# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\hmcculla\ECE423\ECE-423-Labs\workspace\assignment2_hunter_test\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\hmcculla\ECE423\ECE-423-Labs\workspace\assignment2_hunter_test\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {assignment2_hunter_test}\
-hw {C:\Users\hmcculla\ECE423\ECE-423-Labs\ece423_prefab\ece423_prefab\lab_prefab\lab_prefab_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/hmcculla/ECE423/ECE-423-Labs/workspace}

platform write
platform generate -domains 
platform active {assignment2_hunter_test}
domain active {zynq_fsbl}
bsp reload
domain active {standalone_domain}
bsp reload
domain active {zynq_fsbl}
bsp config enable_multi_partition "true"
bsp config num_logical_vol "10"
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp reload
domain active {zynq_fsbl}
bsp reload
domain active {standalone_domain}
bsp setlib -name xilffs -ver 4.7
bsp write
bsp reload
catch {bsp regenerate}
bsp config enable_multi_partition "true"
bsp config num_logical_vol "10"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
