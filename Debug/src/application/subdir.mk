################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/application/Alta.cpp \
../src/application/ArmadorComandos.cpp \
../src/application/Baja.cpp \
../src/application/BusqIndexada.cpp \
../src/application/BusqSecuencial.cpp \
../src/application/Informe.cpp \
../src/application/Modificacion.cpp 

OBJS += \
./src/application/Alta.o \
./src/application/ArmadorComandos.o \
./src/application/Baja.o \
./src/application/BusqIndexada.o \
./src/application/BusqSecuencial.o \
./src/application/Informe.o \
./src/application/Modificacion.o 

CPP_DEPS += \
./src/application/Alta.d \
./src/application/ArmadorComandos.d \
./src/application/Baja.d \
./src/application/BusqIndexada.d \
./src/application/BusqSecuencial.d \
./src/application/Informe.d \
./src/application/Modificacion.d 


# Each subdirectory must supply rules for building sources it contributes
src/application/%.o: ../src/application/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


