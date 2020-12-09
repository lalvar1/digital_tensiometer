################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include FreeRTOS_src/subdir.mk
-include FreeRTOS_portable/MemMang/subdir.mk
-include FreeRTOS_portable/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Prueba.axf

# Tool invocations
Prueba.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\lucho\Documents\LPCXpresso_7.0.2_102\workspaceproyecto\Lib_LCD_Texto\Debug" -L"C:\Users\lucho\Documents\LPCXpresso_7.0.2_102\workspaceproyecto\CMSISv2p00_LPC17xx\Debug" -L"C:\Users\lucho\Documents\LPCXpresso_7.0.2_102\workspaceproyecto\Lib_API_CAPI\Debug" -L"C:\Users\lucho\Documents\LPCXpresso_7.0.2_102\workspaceproyecto\Lib_Contenedores\Debug" -L"C:\Users\lucho\Documents\LPCXpresso_7.0.2_102\workspaceproyecto\Lib_MCU_LPC176x\Debug" -Xlinker -Map="Prueba.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "Prueba_Debug.ld" -o "Prueba.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) Prueba.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Prueba.axf"; # arm-none-eabi-objcopy -O binary "Prueba.axf" "Prueba.bin" ; checksum -p LPC1769 -d "Prueba.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
