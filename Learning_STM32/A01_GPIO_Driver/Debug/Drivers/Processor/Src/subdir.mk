################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Processor/Src/NVIC.c 

OBJS += \
./Drivers/Processor/Src/NVIC.o 

C_DEPS += \
./Drivers/Processor/Src/NVIC.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Processor/Src/%.o Drivers/Processor/Src/%.su Drivers/Processor/Src/%.cyclo: ../Drivers/Processor/Src/%.c Drivers/Processor/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -c -I../Inc -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/A01_GPIO_Driver/Drivers/Device/Inc" -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/A01_GPIO_Driver/Drivers/Peripherals/Inc" -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/A01_GPIO_Driver/Drivers/Processor/Inc" -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/A01_GPIO_Driver/Interface/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Processor-2f-Src

clean-Drivers-2f-Processor-2f-Src:
	-$(RM) ./Drivers/Processor/Src/NVIC.cyclo ./Drivers/Processor/Src/NVIC.d ./Drivers/Processor/Src/NVIC.o ./Drivers/Processor/Src/NVIC.su

.PHONY: clean-Drivers-2f-Processor-2f-Src
