################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/core/chars_identify.cpp \
../src/core/chars_recognise.cpp \
../src/core/chars_segment.cpp \
../src/core/core_func.cpp \
../src/core/features.cpp \
../src/core/plate.cpp \
../src/core/plate_detect.cpp \
../src/core/plate_judge.cpp \
../src/core/plate_locate.cpp \
../src/core/plate_recognize.cpp 

OBJS += \
./src/core/chars_identify.o \
./src/core/chars_recognise.o \
./src/core/chars_segment.o \
./src/core/core_func.o \
./src/core/features.o \
./src/core/plate.o \
./src/core/plate_detect.o \
./src/core/plate_judge.o \
./src/core/plate_locate.o \
./src/core/plate_recognize.o 

CPP_DEPS += \
./src/core/chars_identify.d \
./src/core/chars_recognise.d \
./src/core/chars_segment.d \
./src/core/core_func.d \
./src/core/features.d \
./src/core/plate.d \
./src/core/plate_detect.d \
./src/core/plate_judge.d \
./src/core/plate_locate.d \
./src/core/plate_recognize.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/%.o: ../src/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-gnueabihf-g++ -I"E:\SOC_SDK\SOCEDS\embedded\ds-5\include\opencv" -I"E:\SOC_SDK\SOCEDS\embedded\ds-5\include\minigui\include\minigui" -I"E:\SOC_SDK\SOCEDS\embedded\ds-5\include\opencv\opencv" -I"E:\SOC_SDK\SOCEDS\embedded\ds-5\include\opencv\opencv2" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


