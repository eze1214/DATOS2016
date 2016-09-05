################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/shared/ParserDatos.cpp \
../src/shared/Utilidades.cpp 

OBJS += \
./src/shared/ParserDatos.o \
./src/shared/Utilidades.o 

CPP_DEPS += \
./src/shared/ParserDatos.d \
./src/shared/Utilidades.d 


# Each subdirectory must supply rules for building sources it contributes
src/shared/%.o: ../src/shared/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


