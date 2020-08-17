################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/img_prep.cpp \
../src/img_work.cpp \
../src/main.cpp \
../src/recognition.cpp \
../src/tests.cpp 

OBJS += \
./src/img_prep.o \
./src/img_work.o \
./src/main.o \
./src/recognition.o \
./src/tests.o 

CPP_DEPS += \
./src/img_prep.d \
./src/img_work.d \
./src/main.d \
./src/recognition.d \
./src/tests.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv4 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


