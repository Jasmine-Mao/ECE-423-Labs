# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\j54mao\ECE423\ECE-423-Labs\workspace\ece423_lab1_system\_ide\scripts\systemdebugger_ece423_lab1_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\j54mao\ECE423\ECE-423-Labs\workspace\ece423_lab1_system\_ide\scripts\systemdebugger_ece423_lab1_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Xilinx PYNQ-Z1 003017AC82EDA" && level==0 && jtag_device_ctx=="jsn-Xilinx PYNQ-Z1-003017AC82EDA-23727093-0"}
fpga -file C:/Users/j54mao/ECE423/ECE-423-Labs/workspace/ece423_lab1/_ide/bitstream/lab_prefab_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/j54mao/ECE423/ECE-423-Labs/workspace/lab_prefab_wrapper/export/lab_prefab_wrapper/hw/lab_prefab_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/j54mao/ECE423/ECE-423-Labs/workspace/ece423_lab1/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/j54mao/ECE423/ECE-423-Labs/workspace/ece423_lab1/Debug/ece423_lab1.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
