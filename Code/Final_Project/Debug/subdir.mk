################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../Operations.c \
../TIMER_PBcfg.c \
../Timers.c \
../UART.c \
../gpio.c \
../keypad.c \
../lcd.c \
../main.c \
../seven_seg.c 

OBJS += \
./Buzzer.o \
./Operations.o \
./TIMER_PBcfg.o \
./Timers.o \
./UART.o \
./gpio.o \
./keypad.o \
./lcd.o \
./main.o \
./seven_seg.o 

C_DEPS += \
./Buzzer.d \
./Operations.d \
./TIMER_PBcfg.d \
./Timers.d \
./UART.d \
./gpio.d \
./keypad.d \
./lcd.d \
./main.d \
./seven_seg.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


