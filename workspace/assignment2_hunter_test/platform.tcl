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
platform generate
platform generate
platform clean
platform generate
domain create -name {standalone_ps7_cortexa9_1} -display-name {standalone_ps7_cortexa9_1} -os {standalone} -proc {ps7_cortexa9_1} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {assignment2_hunter_test}
domain active {zynq_fsbl}
domain active {standalone_domain}
domain active {standalone_ps7_cortexa9_1}
platform generate -quick
domain active {zynq_fsbl}
bsp reload
bsp reload
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns"
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DDR"
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DDR"
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_ps7_cortexa9_1}
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DDR -DUSE_ AMP=1"
bsp write
bsp reload
catch {bsp regenerate}
catch {platform remove Assignment2_newest}
catch {platform remove Assignment2_debugging}
catch {platform remove Assignment_2}
platform clean
platform clean
platform clean
platform clean
