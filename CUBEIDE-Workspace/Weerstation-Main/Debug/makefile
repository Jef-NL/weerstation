################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Weerstation-Main.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Weerstation-Main.list \

OBJCOPY_BIN += \
Weerstation-Main.bin \


# All Target
all: Weerstation-Main.elf secondary-outputs

# Tool invocations
Weerstation-Main.elf: $(OBJS) $(USER_OBJS) C:\Users\jefba\OneDrive\ -\ Avans\ Hogeschool\GitHub\WeerstationP5L2\CUBEIDE-Workspace\Weerstation-Main\STM32F030R8TX_FLASH.ld
	arm-none-eabi-gcc -o "Weerstation-Main.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\jefba\OneDrive - Avans Hogeschool\GitHub\WeerstationP5L2\CUBEIDE-Workspace\Weerstation-Main\STM32F030R8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Weerstation-Main.map" -Wl,--gc-sections -static -u _printf_float --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Weerstation-Main.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Weerstation-Main.list"
	@echo 'Finished building: $@'
	@echo ' '

Weerstation-Main.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Weerstation-Main.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
