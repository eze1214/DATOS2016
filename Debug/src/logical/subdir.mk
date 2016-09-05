################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/logical/Fecha.cpp \
../src/logical/Registro.cpp \
../src/logical/Vendedores.cpp \
../src/logical/Ventas.cpp 

OBJS += \
./src/logical/Fecha.o \
./src/logical/Registro.o \
./src/logical/Vendedores.o \
./src/logical/Ventas.o 

CPP_DEPS += \
./src/logical/Fecha.d \
./src/logical/Registro.d \
./src/logical/Vendedores.d \
./src/logical/Ventas.d 


# Each subdirectory must supply rules for building sources it contributes
src/logical/%.o: ../src/logical/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


