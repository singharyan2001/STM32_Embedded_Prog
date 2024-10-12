/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <Button_Test.h>
#include <stdint.h>
#include "STM32F411xx.h"
#include "GPIO_Driver.h"
#include "YGRB_LED_Test.h"
#include "Button_Test.h"

void LED_YGRB_Test(void);
void PORTC_LED_Test(void);
void ONBOARD_LED_Test(void);
void ONBOARD_LED_Toggle(void);

void are_ButtonPressed_Test(void);

void delay(uint32_t value);


int main(void)
{
	//Configuring Up all Handlers
	//Output Configurations
	LED_Y.pGPIOx_Base = GPIOC;
	LED_Y.GPIO_PinConfig = Yellow_led;

	LED_G.pGPIOx_Base = GPIOD;
	LED_G.GPIO_PinConfig = Green_led;

	LED_R.pGPIOx_Base = GPIOB;
	LED_R.GPIO_PinConfig = Red_led;

	LED_B.pGPIOx_Base = GPIOC;
	LED_B.GPIO_PinConfig = Blue_led;

	ONBOARD_LED.pGPIOx_Base = GPIOA;
	ONBOARD_LED.GPIO_PinConfig = ONBOARD_LED_Config;

	//Input Configurations
	PushButton_Handle.pGPIOx_Base = GPIOC;
	PushButton_Handle.GPIO_PinConfig = PushButton_Config;

	EndstopLSW_Handle.pGPIOx_Base = GPIOA;
	EndstopLSW_Handle.GPIO_PinConfig = Endstop_LimitSwitch_Config;

	//Provide Clock Access to the GPIO Peripherals
	GPIOx_PClkControl(GPIOA, CLK_EN);
	GPIOx_PClkControl(GPIOB, CLK_EN);
	GPIOx_PClkControl(GPIOC, CLK_EN);
	GPIOx_PClkControl(GPIOD, CLK_EN);

	//Initialize all Configurations
	GPIOx_Init(&LED_Y);
	GPIOx_Init(&LED_G);
	GPIOx_Init(&LED_R);
	GPIOx_Init(&LED_R);
	GPIOx_Init(&LED_B);
	GPIOx_Init(&ONBOARD_LED);

	GPIOx_Init(&PushButton_Handle);
	GPIOx_Init(&EndstopLSW_Handle);

	while(1){
		are_ButtonPressed_Test();
	}
}



void delay(uint32_t value){
	for(int i=0; i < value; i++){};
}


void are_ButtonPressed_Test(void){
	if(GPIO_ReadFromInputPin(GPIOC, PushButton_Handle.GPIO_PinConfig.GPIOx_PinNumber) == LOW){
		LED_YGRB_Test();
	}
	else if(GPIO_ReadFromInputPin(GPIOA, EndstopLSW_Handle.GPIO_PinConfig.GPIOx_PinNumber) == HIGH){
		PORTC_LED_Test();
		//ONBOARD_LED_Test();
	}
	else{
		ONBOARD_LED_Toggle();
	}
	delay(500000);
}


void LED_YGRB_Test(void){
	GPIO_WriteToOutputPin(LED_Y.pGPIOx_Base, LED_Y.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
	GPIO_WriteToOutputPin(LED_G.pGPIOx_Base, LED_G.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
	GPIO_WriteToOutputPin(LED_R.pGPIOx_Base, LED_R.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
	GPIO_WriteToOutputPin(LED_B.pGPIOx_Base, LED_B.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
	delay(500000);
	GPIO_WriteToOutputPin(LED_Y.pGPIOx_Base, LED_Y.GPIO_PinConfig.GPIOx_PinNumber, LOW);
	GPIO_WriteToOutputPin(LED_G.pGPIOx_Base, LED_G.GPIO_PinConfig.GPIOx_PinNumber, LOW);
	GPIO_WriteToOutputPin(LED_R.pGPIOx_Base, LED_R.GPIO_PinConfig.GPIOx_PinNumber, LOW);
	GPIO_WriteToOutputPin(LED_B.pGPIOx_Base, LED_B.GPIO_PinConfig.GPIOx_PinNumber, LOW);
	delay(500000);
}

void PORTC_LED_Test(void){
	GPIO_WriteToOutputPort(GPIOC, 0xffff);
	delay(500000);
	GPIO_WriteToOutputPort(GPIOC, 0x0000);
	delay(500000);
}

void ONBOARD_LED_Test(void){
	GPIO_WriteToOutputPin(GPIOA, ONBOARD_LED.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
	for(int i=0; i < 500000; i++){};
	GPIO_WriteToOutputPin(GPIOA, ONBOARD_LED.GPIO_PinConfig.GPIOx_PinNumber, LOW);
}

void ONBOARD_LED_Toggle(void){
	GPIO_ToggleOutputPin(GPIOA, ONBOARD_LED.GPIO_PinConfig.GPIOx_PinNumber);
}

