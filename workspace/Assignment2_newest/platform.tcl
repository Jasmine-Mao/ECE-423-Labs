# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\j54mao\ECE423\ECE-423-Labs\workspace\Assignment2_newest\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\j54mao\ECE423\ECE-423-Labs\workspace\Assignment2_newest\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Assignment2_newest}\
-hw {C:\Users\j54mao\ECE423\ECE-423-Labs\ece423_prefab\ece423_prefab\lab_prefab\lab_prefab_wrapper_newest_lab2.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/j54mao/ECE423/ECE-423-Labs/workspace}

platform write
platform generate -domains 
platform active {Assignment2_newest}
domain active {zynq_fsbl}
bsp reload
bsp config enable_multi_partition "true"
bsp config num_logical_vol "10"
bsp write
bsp reload
catch {bsp regenerate}
bsp write
platform generate
domain active {standalone_domain}
domain active {standalone_domain}
domain active {standalone_domain}
domain active {standalone_domain}
domain active {standalone_domain}
bsp reload
domain active {standalone_domain}
bsp removelib -name xilffs
bsp setlib -name xilffs -ver 4.7
bsp write
bsp reload
catch {bsp regenerate}
bsp removelib -name xilffs
bsp write
bsp reload
catch {bsp regenerate}
bsp setlib -name xilffs -ver 4.7
bsp config enable_multi_partition "true"
bsp config num_logical_vol "10"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains 
domain active {standalone_domain}
catch {bsp regenerate}
bsp setlib -name xilffs -ver 4.7
bsp config enable_multi_partition "true"
bsp config num_logical_vol "10"
bsp write
bsp write
platform generate -domains standalone_domain 
platform generate
platform generate
