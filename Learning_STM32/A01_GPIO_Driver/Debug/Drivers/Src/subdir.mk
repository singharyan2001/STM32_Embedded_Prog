################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/GPIO_Driver.c \
../Drivers/Src/GPTimer_Driver.c \
../Drivers/Src/SYSTICK_Driver.c 

OBJS += \
./Drivers/Src/GPIO_Driver.o \
./Drivers/Src/GPTimer_Driver.o \
./Drivers/Src/SYSTICK_Driver.o 

C_DEPS += \
./Drivers/Src/GPIO_Driver.d \
./Drivers/Src/GPTimer_Driver.d \
./Drivers/Src/SYSTICK_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -c -I../Inc -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/A01_GPIO_Driver/Drivers/Inc" -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/A01_GPIO_Driver/Interface/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/GPIO_Driver.cyclo ./Drivers/Src/GPIO_Driver.d ./Drivers/Src/GPIO_Driver.o ./Drivers/Src/GPIO_Driver.su ./Drivers/Src/GPTimer_Driver.cyclo ./Drivers/Src/GPTimer_Driver.d ./Drivers/Src/GPTimer_Driver.o ./Drivers/Src/GPTimer_Driver.su ./Drivers/Src/SYSTICK_Driver.cyclo ./Drivers/Src/SYSTICK_Driver.d ./Drivers/Src/SYSTICK_Driver.o ./Drivers/Src/SYSTICK_Driver.su

.PHONY: clean-Drivers-2f-Src

