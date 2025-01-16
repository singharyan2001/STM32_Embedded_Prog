################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Peripherals/Src/GPIO_Driver.c \
../Drivers/Peripherals/Src/GPTimer_Driver.c \
../Drivers/Peripherals/Src/SPI_Driver.c \
../Drivers/Peripherals/Src/SYSTICK_Driver.c 

OBJS += \
./Drivers/Peripherals/Src/GPIO_Driver.o \
./Drivers/Peripherals/Src/GPTimer_Driver.o \
./Drivers/Peripherals/Src/SPI_Driver.o \
./Drivers/Peripherals/Src/SYSTICK_Driver.o 

C_DEPS += \
./Drivers/Peripherals/Src/GPIO_Driver.d \
./Drivers/Peripherals/Src/GPTimer_Driver.d \
./Drivers/Peripherals/Src/SPI_Driver.d \
./Drivers/Peripherals/Src/SYSTICK_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Peripherals/Src/%.o Drivers/Peripherals/Src/%.su Drivers/Peripherals/Src/%.cyclo: ../Drivers/Peripherals/Src/%.c Drivers/Peripherals/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/TIMERS_PWM_MotorControl_TMC2209/Drivers/Device/Inc" -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/TIMERS_PWM_MotorControl_TMC2209/Drivers/Peripherals/Inc" -I"C:/Users/singh/VSCODE/saved_files/EmbeddedSystems/STM32_Embedded/Learning_STM32/TIMERS_PWM_MotorControl_TMC2209/Drivers/Processor/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Peripherals-2f-Src

clean-Drivers-2f-Peripherals-2f-Src:
	-$(RM) ./Drivers/Peripherals/Src/GPIO_Driver.cyclo ./Drivers/Peripherals/Src/GPIO_Driver.d ./Drivers/Peripherals/Src/GPIO_Driver.o ./Drivers/Peripherals/Src/GPIO_Driver.su ./Drivers/Peripherals/Src/GPTimer_Driver.cyclo ./Drivers/Peripherals/Src/GPTimer_Driver.d ./Drivers/Peripherals/Src/GPTimer_Driver.o ./Drivers/Peripherals/Src/GPTimer_Driver.su ./Drivers/Peripherals/Src/SPI_Driver.cyclo ./Drivers/Peripherals/Src/SPI_Driver.d ./Drivers/Peripherals/Src/SPI_Driver.o ./Drivers/Peripherals/Src/SPI_Driver.su ./Drivers/Peripherals/Src/SYSTICK_Driver.cyclo ./Drivers/Peripherals/Src/SYSTICK_Driver.d ./Drivers/Peripherals/Src/SYSTICK_Driver.o ./Drivers/Peripherals/Src/SYSTICK_Driver.su

.PHONY: clean-Drivers-2f-Peripherals-2f-Src

