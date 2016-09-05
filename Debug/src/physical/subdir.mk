################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/physical/ArchBlocks.cpp \
../src/physical/ArchRRLF.cpp \
../src/physical/ArchhRRLV.cpp \
../src/physical/BitMap.cpp \
../src/physical/ByteMap.cpp \
../src/physical/Parser.cpp 

OBJS += \
./src/physical/ArchBlocks.o \
./src/physical/ArchRRLF.o \
./src/physical/ArchhRRLV.o \
./src/physical/BitMap.o \
./src/physical/ByteMap.o \
./src/physical/Parser.o 

CPP_DEPS += \
./src/physical/ArchBlocks.d \
./src/physical/ArchRRLF.d \
./src/physical/ArchhRRLV.d \
./src/physical/BitMap.d \
./src/physical/ByteMap.d \
./src/physical/Parser.d 


# Each subdirectory must supply rules for building sources it contributes
src/physical/%.o: ../src/physical/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


