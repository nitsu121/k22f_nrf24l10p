################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/clockMan1.c \
../Generated_Code/dspiCom1.c \
../Generated_Code/gpio1.c \
../Generated_Code/hardware_init.c \
../Generated_Code/osa1.c \
../Generated_Code/pin_init.c \
../Generated_Code/pitTimer1.c 

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/clockMan1.o \
./Generated_Code/dspiCom1.o \
./Generated_Code/gpio1.o \
./Generated_Code/hardware_init.o \
./Generated_Code/osa1.o \
./Generated_Code/pin_init.o \
./Generated_Code/pitTimer1.o 

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/clockMan1.d \
./Generated_Code/dspiCom1.d \
./Generated_Code/gpio1.d \
./Generated_Code/hardware_init.d \
./Generated_Code/osa1.d \
./Generated_Code/pin_init.d \
./Generated_Code/pitTimer1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"FSL_OSA_BM_TIMER_CONFIG=2" -D"CPU_MK22FN512VLH12" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/SDK/platform/hal/inc" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/SDK/platform/hal/src/sim/MK22F51212" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/SDK/platform/system/src/clock/MK22F51212" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/SDK/platform/system/inc" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/SDK/platform/osa/inc" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/SDK/platform/CMSIS/Include" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/SDK/platform/devices" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/SDK/platform/devices/MK22F51212/include" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/SDK/platform/devices/MK22F51212/startup" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/Generated_Code/SDK/platform/devices/MK22F51212/startup" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/Sources" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/Generated_Code" -I"C:/freescale/workspace.kds/K22F-NRF24-Test/SDK/platform/drivers/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


