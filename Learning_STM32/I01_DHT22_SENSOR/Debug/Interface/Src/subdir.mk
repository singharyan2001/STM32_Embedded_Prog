################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Interface/Src/DHT22.c 

OBJS += \
./Interface/Src/DHT22.o 

C_DEPS += \
./Interface/Src/DHT22.d 


# Each subdirectory must supply rules for building sources it contributes
Interface/Src/%.o Interface/Src/%.su Interface/Src/%.cyclo: ../Interface/Src/%.c Interface/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -c -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/I01_DHT22_SENSOR/Drivers/Processor/Inc" -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/I01_DHT22_SENSOR/Interface/Inc" -I../Inc -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/I01_DHT22_SENSOR/Drivers/Device/Inc" -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/I01_DHT22_SENSOR/Drivers/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Interface-2f-Src

clean-Interface-2f-Src:
	-$(RM) ./Interface/Src/DHT22.cyclo ./Interface/Src/DHT22.d ./Interface/Src/DHT22.o ./Interface/Src/DHT22.su

.PHONY: clean-Interface-2f-Src

