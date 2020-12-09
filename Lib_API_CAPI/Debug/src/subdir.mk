################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AIN.c \
../src/BUS.c \
../src/GPIO.c \
../src/PORT.c \
../src/RTC.c \
../src/TIMER.c \
../src/UART.c 

OBJS += \
./src/AIN.o \
./src/BUS.o \
./src/GPIO.o \
./src/PORT.o \
./src/RTC.o \
./src/TIMER.o \
./src/UART.o 

C_DEPS += \
./src/AIN.d \
./src/BUS.d \
./src/GPIO.d \
./src/PORT.d \
./src/RTC.d \
./src/TIMER.d \
./src/UART.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


