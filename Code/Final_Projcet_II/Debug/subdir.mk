################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../DC_Motor.c \
../I2C.c \
../Operations_II.c \
../PWM.c \
../TIMER_II_PBcfg.c \
../Timers.c \
../UART.c \
../external_eeprom.c \
../gpio.c \
../main.c 

OBJS += \
./Buzzer.o \
./DC_Motor.o \
./I2C.o \
./Operations_II.o \
./PWM.o \
./TIMER_II_PBcfg.o \
./Timers.o \
./UART.o \
./external_eeprom.o \
./gpio.o \
./main.o 

C_DEPS += \
./Buzzer.d \
./DC_Motor.d \
./I2C.d \
./Operations_II.d \
./PWM.d \
./TIMER_II_PBcfg.d \
./Timers.d \
./UART.d \
./external_eeprom.d \
./gpio.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


