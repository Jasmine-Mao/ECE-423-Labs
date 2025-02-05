################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../0/2022.1/workspace2/.metadata/.plugins/org.eclipse.cdt.make.core/specs.cpp 

C_SRCS += \
../0/2022.1/workspace2/.metadata/.plugins/org.eclipse.cdt.make.core/specs.c 

OBJS += \
./0/2022.1/workspace2/.metadata/.plugins/org.eclipse.cdt.make.core/specs.o 

CPP_DEPS += \
./0/2022.1/workspace2/.metadata/.plugins/org.eclipse.cdt.make.core/specs.d 

C_DEPS += \
./0/2022.1/workspace2/.metadata/.plugins/org.eclipse.cdt.make.core/specs.d 


# Each subdirectory must supply rules for building sources it contributes
0/2022.1/workspace2/.metadata/.plugins/org.eclipse.cdt.make.core/%.o: ../0/2022.1/workspace2/.metadata/.plugins/org.eclipse.cdt.make.core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DAESL_TB -D__llvm__ -D__llvm__ -IC:/Software/Xilinx/Vitis_HLS/2022.1/win64/tools/systemc/include -IC:/Software/Xilinx/Vitis_HLS/2022.1/win64/tools/auto_cc/include -IC:/Software/Xilinx/Vitis_HLS/2022.1/include/ap_sysc -IC:/Software/Xilinx/Vitis_HLS/2022.1/include/etc -IC:/Users/j54mao/ECE423/ECE-423-Labs/HLS -IC:/Software/Xilinx/Vitis_HLS/2022.1/include -IC:/Users/hmcculla/ECE432/ECE-423-Labs/HLS -IC:/Users/j54mao/ece423/ECE-423-Labs/HLS -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0/2022.1/workspace2/.metadata/.plugins/org.eclipse.cdt.make.core/%.o: ../0/2022.1/workspace2/.metadata/.plugins/org.eclipse.cdt.make.core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -IC:/Software/Xilinx/Vitis_HLS/2022.1/win64/tools/systemc/include -IC:/Software/Xilinx/Vitis_HLS/2022.1/win64/tools/auto_cc/include -IC:/Software/Xilinx/Vitis_HLS/2022.1/include/ap_sysc -IC:/Software/Xilinx/Vitis_HLS/2022.1/include/etc -IC:/Users/j54mao/ECE423/ECE-423-Labs/HLS -IC:/Software/Xilinx/Vitis_HLS/2022.1/include -IC:/Users/hmcculla/ECE432/ECE-423-Labs/HLS -IC:/Users/j54mao/ece423/ECE-423-Labs/HLS -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


