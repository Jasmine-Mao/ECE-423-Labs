# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\j54mao\ECE423\ECE-423-Labs\workspace\Assignment3_platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\j54mao\ECE423\ECE-423-Labs\workspace\Assignment3_platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Assignment3_platform}\
-hw {C:\Users\j54mao\ECE423\ECE-423-Labs\workspace\assignment2_hunter_test\hw\lab_prefab_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/j54mao/ECE423/ECE-423-Labs/workspace}

platform write
platform generate -domains 
platform active {Assignment3_platform}
domain create -name {standalone_ps7_cortexa9_1} -display-name {standalone_ps7_cortexa9_1} -os {standalone} -proc {ps7_cortexa9_1} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {Assignment3_platform}
domain active {zynq_fsbl}
domain active {standalone_domain}
domain active {standalone_ps7_cortexa9_1}
platform generate -quick
domain active {zynq_fsbl}
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DRR"
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DRR"
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_ps7_cortexa9_1}
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DRR -DUSE_AMP=1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
domain active {standalone_domain}
domain active {standalone_domain}
domain active {standalone_domain}
domain active {standalone_domain}
domain active {zynq_fsbl}
bsp reload
domain active {standalone_domain}
domain active {standalone_domain}
domain active {standalone_domain}
bsp config enable_multi_partition "true"
bsp config num_logical_vol "10"
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
domain active {standalone_domain}
domain active {standalone_ps7_cortexa9_1}
domain active {standalone_ps7_cortexa9_1}
domain active {standalone_ps7_cortexa9_1}
platform generate -domains 
domain active {standalone_ps7_cortexa9_1}
bsp setlib -name xilffs -ver 4.7
bsp config enable_multi_partition "true"
bsp config num_logical_vol "10"
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp setlib -name xilffs -ver 4.7
bsp config enable_multi_partition "true"
bsp config num_logical_vol "10"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain,standalone_ps7_cortexa9_1 
platform clean
platform generate
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform active {Assignment3_platform}
domain active {standalone_ps7_cortexa9_1}
domain active {zynq_fsbl}
bsp reload
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DRR"
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DRR"
bsp reload
domain active {standalone_domain}
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DRR"
bsp reload
domain active {standalone_ps7_cortexa9_1}
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DRR -DUSE_AMP=1"
bsp reload
platform generate -domains 
platform generate
platform active {Assignment3_platform}
platform generate -domains 
domain active {standalone_domain}
bsp reload
domain active {zynq_fsbl}
bsp reload
bsp reload
domain active {standalone_domain}
bsp reload
domain active {standalone_ps7_cortexa9_1}
bsp reload
domain active {standalone_domain}
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DRR"
bsp reload
domain active {standalone_ps7_cortexa9_1}
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DSHAREABLE_DRR -DUSE_AMP=1"
bsp reload
platform generate
