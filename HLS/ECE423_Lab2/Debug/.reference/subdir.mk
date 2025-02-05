################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
C:/Users/j54mao/ECE423/ECE-423-Labs/import_files/import_files/2D_idct.cc 

CC_DEPS += \
./.reference/2D_idct.d 

OBJS += \
./.reference/2D_idct.o 


# Each subdirectory must supply rules for building sources it contributes
.reference/2D_idct.o: C:/Users/j54mao/ECE423/ECE-423-Labs/import_files/import_files/2D_idct.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -IC:/Software/Xilinx/Vitis_HLS/2022.1/win64/tools/systemc/include -IC:/Software/Xilinx/Vitis_HLS/2022.1/win64/tools/auto_cc/include -IC:/Software/Xilinx/Vitis_HLS/2022.1/include/ap_sysc -IC:/Software/Xilinx/Vitis_HLS/2022.1/include/etc -IC:/Users/j54mao/ECE423/ECE-423-Labs/HLS -IC:/Software/Xilinx/Vitis_HLS/2022.1/include -IC:/Users/hmcculla/ECE432/ECE-423-Labs/HLS -IC:/Users/j54mao/ece423/ECE-423-Labs/HLS -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


