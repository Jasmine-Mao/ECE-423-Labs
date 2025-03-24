# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\j54mao\ece423\ECE-423-Labs\workspace\Assignment_2\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\j54mao\ece423\ECE-423-Labs\workspace\Assignment_2\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Assignment_2}\
-hw {C:\Users\j54mao\ece423\ECE-423-Labs\ece423_prefab\ece423_prefab\lab_prefab\lab_prefab_wrapper_lab2.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/j54mao/ece423/ECE-423-Labs/workspace}

platform write
platform generate -domains 
platform active {Assignment_2}
platform generate
bsp reload
bsp setlib -name xilffs -ver 4.7
bsp config enable_multi_partition "true"
bsp config enable_multi_partition "true"
bsp config num_logical_vol "10"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
platform generate -domains standalone_domain,zynq_fsbl 
platform generate
platform clean
