################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../prueba\ Manejador\ Archivo/ManejadorArchivos.cpp 

OBJS += \
./prueba\ Manejador\ Archivo/ManejadorArchivos.o 

CPP_DEPS += \
./prueba\ Manejador\ Archivo/ManejadorArchivos.d 


# Each subdirectory must supply rules for building sources it contributes
prueba\ Manejador\ Archivo/ManejadorArchivos.o: ../prueba\ Manejador\ Archivo/ManejadorArchivos.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"prueba Manejador Archivo/ManejadorArchivos.d" -MT"prueba\ Manejador\ Archivo/ManejadorArchivos.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


