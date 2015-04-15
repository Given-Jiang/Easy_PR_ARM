################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/util/CParser.cpp \
../src/util/deface.cpp \
../src/util/general_test_prepare.cpp \
../src/util/generate_gdts.cpp \
../src/util/learn_prepare.cpp \
../src/util/mc_data_prepare.cpp \
../src/util/util.cpp 

OBJS += \
./src/util/CParser.o \
./src/util/deface.o \
./src/util/general_test_prepare.o \
./src/util/generate_gdts.o \
./src/util/learn_prepare.o \
./src/util/mc_data_prepare.o \
./src/util/util.o 

CPP_DEPS += \
./src/util/CParser.d \
./src/util/deface.d \
./src/util/general_test_prepare.d \
./src/util/generate_gdts.d \
./src/util/learn_prepare.d \
./src/util/mc_data_prepare.d \
./src/util/util.d 


# Each subdirectory must supply rules for building sources it contributes
src/util/%.o: ../src/util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-gnueabihf-g++ -I"E:\SOC_SDK\SOCEDS\embedded\ds-5\include\opencv" -I"E:\SOC_SDK\SOCEDS\embedded\ds-5\include\minigui\include\minigui" -I"E:\SOC_SDK\SOCEDS\embedded\ds-5\include\opencv\opencv" -I"E:\SOC_SDK\SOCEDS\embedded\ds-5\include\opencv\opencv2" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


