################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor\ drivers/src/debug_frmwrk.c \
../vendor\ drivers/src/lpc17xx_adc.c \
../vendor\ drivers/src/lpc17xx_can.c \
../vendor\ drivers/src/lpc17xx_clkpwr.c \
../vendor\ drivers/src/lpc17xx_dac.c \
../vendor\ drivers/src/lpc17xx_emac.c \
../vendor\ drivers/src/lpc17xx_exti.c \
../vendor\ drivers/src/lpc17xx_gpio.c \
../vendor\ drivers/src/lpc17xx_i2c.c \
../vendor\ drivers/src/lpc17xx_i2s.c \
../vendor\ drivers/src/lpc17xx_libcfg_default.c \
../vendor\ drivers/src/lpc17xx_mcpwm.c \
../vendor\ drivers/src/lpc17xx_nvic.c \
../vendor\ drivers/src/lpc17xx_pinsel.c \
../vendor\ drivers/src/lpc17xx_pwm.c \
../vendor\ drivers/src/lpc17xx_qei.c \
../vendor\ drivers/src/lpc17xx_rit.c \
../vendor\ drivers/src/lpc17xx_rtc.c \
../vendor\ drivers/src/lpc17xx_spi.c \
../vendor\ drivers/src/lpc17xx_ssp.c \
../vendor\ drivers/src/lpc17xx_systick.c \
../vendor\ drivers/src/lpc17xx_timer.c \
../vendor\ drivers/src/lpc17xx_uart.c \
../vendor\ drivers/src/lpc17xx_wdt.c 

OBJS += \
./vendor\ drivers/src/debug_frmwrk.o \
./vendor\ drivers/src/lpc17xx_adc.o \
./vendor\ drivers/src/lpc17xx_can.o \
./vendor\ drivers/src/lpc17xx_clkpwr.o \
./vendor\ drivers/src/lpc17xx_dac.o \
./vendor\ drivers/src/lpc17xx_emac.o \
./vendor\ drivers/src/lpc17xx_exti.o \
./vendor\ drivers/src/lpc17xx_gpio.o \
./vendor\ drivers/src/lpc17xx_i2c.o \
./vendor\ drivers/src/lpc17xx_i2s.o \
./vendor\ drivers/src/lpc17xx_libcfg_default.o \
./vendor\ drivers/src/lpc17xx_mcpwm.o \
./vendor\ drivers/src/lpc17xx_nvic.o \
./vendor\ drivers/src/lpc17xx_pinsel.o \
./vendor\ drivers/src/lpc17xx_pwm.o \
./vendor\ drivers/src/lpc17xx_qei.o \
./vendor\ drivers/src/lpc17xx_rit.o \
./vendor\ drivers/src/lpc17xx_rtc.o \
./vendor\ drivers/src/lpc17xx_spi.o \
./vendor\ drivers/src/lpc17xx_ssp.o \
./vendor\ drivers/src/lpc17xx_systick.o \
./vendor\ drivers/src/lpc17xx_timer.o \
./vendor\ drivers/src/lpc17xx_uart.o \
./vendor\ drivers/src/lpc17xx_wdt.o 

C_DEPS += \
./vendor\ drivers/src/debug_frmwrk.d \
./vendor\ drivers/src/lpc17xx_adc.d \
./vendor\ drivers/src/lpc17xx_can.d \
./vendor\ drivers/src/lpc17xx_clkpwr.d \
./vendor\ drivers/src/lpc17xx_dac.d \
./vendor\ drivers/src/lpc17xx_emac.d \
./vendor\ drivers/src/lpc17xx_exti.d \
./vendor\ drivers/src/lpc17xx_gpio.d \
./vendor\ drivers/src/lpc17xx_i2c.d \
./vendor\ drivers/src/lpc17xx_i2s.d \
./vendor\ drivers/src/lpc17xx_libcfg_default.d \
./vendor\ drivers/src/lpc17xx_mcpwm.d \
./vendor\ drivers/src/lpc17xx_nvic.d \
./vendor\ drivers/src/lpc17xx_pinsel.d \
./vendor\ drivers/src/lpc17xx_pwm.d \
./vendor\ drivers/src/lpc17xx_qei.d \
./vendor\ drivers/src/lpc17xx_rit.d \
./vendor\ drivers/src/lpc17xx_rtc.d \
./vendor\ drivers/src/lpc17xx_spi.d \
./vendor\ drivers/src/lpc17xx_ssp.d \
./vendor\ drivers/src/lpc17xx_systick.d \
./vendor\ drivers/src/lpc17xx_timer.d \
./vendor\ drivers/src/lpc17xx_uart.d \
./vendor\ drivers/src/lpc17xx_wdt.d 


# Each subdirectory must supply rules for building sources it contributes
vendor\ drivers/src/debug_frmwrk.o: ../vendor\ drivers/src/debug_frmwrk.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/debug_frmwrk.d" -MT"vendor\ drivers/src/debug_frmwrk.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_adc.o: ../vendor\ drivers/src/lpc17xx_adc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_adc.d" -MT"vendor\ drivers/src/lpc17xx_adc.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_can.o: ../vendor\ drivers/src/lpc17xx_can.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_can.d" -MT"vendor\ drivers/src/lpc17xx_can.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_clkpwr.o: ../vendor\ drivers/src/lpc17xx_clkpwr.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_clkpwr.d" -MT"vendor\ drivers/src/lpc17xx_clkpwr.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_dac.o: ../vendor\ drivers/src/lpc17xx_dac.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_dac.d" -MT"vendor\ drivers/src/lpc17xx_dac.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_emac.o: ../vendor\ drivers/src/lpc17xx_emac.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_emac.d" -MT"vendor\ drivers/src/lpc17xx_emac.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_exti.o: ../vendor\ drivers/src/lpc17xx_exti.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_exti.d" -MT"vendor\ drivers/src/lpc17xx_exti.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_gpio.o: ../vendor\ drivers/src/lpc17xx_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_gpio.d" -MT"vendor\ drivers/src/lpc17xx_gpio.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_i2c.o: ../vendor\ drivers/src/lpc17xx_i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_i2c.d" -MT"vendor\ drivers/src/lpc17xx_i2c.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_i2s.o: ../vendor\ drivers/src/lpc17xx_i2s.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_i2s.d" -MT"vendor\ drivers/src/lpc17xx_i2s.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_libcfg_default.o: ../vendor\ drivers/src/lpc17xx_libcfg_default.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_libcfg_default.d" -MT"vendor\ drivers/src/lpc17xx_libcfg_default.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_mcpwm.o: ../vendor\ drivers/src/lpc17xx_mcpwm.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_mcpwm.d" -MT"vendor\ drivers/src/lpc17xx_mcpwm.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_nvic.o: ../vendor\ drivers/src/lpc17xx_nvic.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_nvic.d" -MT"vendor\ drivers/src/lpc17xx_nvic.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_pinsel.o: ../vendor\ drivers/src/lpc17xx_pinsel.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_pinsel.d" -MT"vendor\ drivers/src/lpc17xx_pinsel.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_pwm.o: ../vendor\ drivers/src/lpc17xx_pwm.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_pwm.d" -MT"vendor\ drivers/src/lpc17xx_pwm.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_qei.o: ../vendor\ drivers/src/lpc17xx_qei.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_qei.d" -MT"vendor\ drivers/src/lpc17xx_qei.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_rit.o: ../vendor\ drivers/src/lpc17xx_rit.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_rit.d" -MT"vendor\ drivers/src/lpc17xx_rit.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_rtc.o: ../vendor\ drivers/src/lpc17xx_rtc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_rtc.d" -MT"vendor\ drivers/src/lpc17xx_rtc.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_spi.o: ../vendor\ drivers/src/lpc17xx_spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_spi.d" -MT"vendor\ drivers/src/lpc17xx_spi.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_ssp.o: ../vendor\ drivers/src/lpc17xx_ssp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_ssp.d" -MT"vendor\ drivers/src/lpc17xx_ssp.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_systick.o: ../vendor\ drivers/src/lpc17xx_systick.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_systick.d" -MT"vendor\ drivers/src/lpc17xx_systick.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_timer.o: ../vendor\ drivers/src/lpc17xx_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_timer.d" -MT"vendor\ drivers/src/lpc17xx_timer.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_uart.o: ../vendor\ drivers/src/lpc17xx_uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_uart.d" -MT"vendor\ drivers/src/lpc17xx_uart.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

vendor\ drivers/src/lpc17xx_wdt.o: ../vendor\ drivers/src/lpc17xx_wdt.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\usuaio\Desktop\WS TD2\CMSISv2p00_LPC17xx\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_Contenedores\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_MCU_LPC176x\vendor drivers\inc" -I"C:\Users\usuaio\Desktop\WS TD2\Lib_API_CAPI\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"vendor drivers/src/lpc17xx_wdt.d" -MT"vendor\ drivers/src/lpc17xx_wdt.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


