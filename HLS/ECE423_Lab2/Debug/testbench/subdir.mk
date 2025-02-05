################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/j54mao/ECE423/ECE-423-Labs/Testbenches/idct_tb_1.cpp 

OBJS += \
./testbench/idct_tb_1.o 

CPP_DEPS += \
./testbench/idct_tb_1.d 


# Each subdirectory must supply rules for building sources it contributes
testbench/idct_tb_1.o: C:/Users/j54mao/ECE423/ECE-423-Labs/Testbenches/idct_tb_1.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -IC:/Software/Xilinx/Vitis_HLS/2022.1/win64/tools/systemc/include -IC:/Software/Xilinx/Vitis_HLS/2022.1/win64/tools/auto_cc/include -IC:/Software/Xilinx/Vitis_HLS/2022.1/include/ap_sysc -IC:/Software/Xilinx/Vitis_HLS/2022.1/include/etc -IC:/Users/j54mao/ECE423/ECE-423-Labs/HLS -IC:/Software/Xilinx/Vitis_HLS/2022.1/include -O0 -g3 -Wall -Wno-unknown-pragmas -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"testbench/idct_tb_1.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


