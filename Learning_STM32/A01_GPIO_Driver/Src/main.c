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


#include <string.h>
#include <stdint.h>
#include "STM32F411xx.h"
#include "GPIO_Driver.h"
//#include "YGRB_LED_Test.h"
//#include "Button_Test.h"
#include "SYSTICK_Driver.h"


void LED_YGRB_Test(void);
void PORTC_LED_Test(void);
void ONBOARD_LED_Test(void);
void ONBOARD_LED_Toggle(void);

void are_ButtonPressed_Test(void);

void delay(uint32_t value);

GPIOx_Handle_t LED_Y;
GPIOx_Handle_t LED_G;
GPIOx_Handle_t LED_R;
GPIOx_Handle_t LED_B;
GPIOx_Handle_t ONBOARD_LED;

GPIOx_Handle_t PushButton_Handle;
GPIOx_Handle_t EndstopLSW_Handle;


int main(void)
{
	//Clear the Newly created structures
	memset(&LED_Y, 0, sizeof(LED_Y));
	memset(&LED_G, 0, sizeof(LED_G));
	memset(&LED_R, 0, sizeof(LED_R));
	memset(&LED_B, 0, sizeof(LED_B));
	memset(&ONBOARD_LED, 0, sizeof(ONBOARD_LED));
	memset(&PushButton_Handle, 0, sizeof(PushButton_Handle));
	memset(&EndstopLSW_Handle, 0, sizeof(EndstopLSW_Handle));

	//Configuring Up all Handlers
	//Output Configurations
	//GPIO Pin - PC8
	LED_Y.pGPIOx_Base = GPIOC;
	LED_Y.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_8;
	LED_Y.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_OUTPUT;
	LED_Y.GPIO_PinConfig.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL;
	LED_Y.GPIO_PinConfig.GPIOx_PinSpeed = GPIO_SPEED_LOW;

	//GPIO Pin - PD2
	LED_G.pGPIOx_Base = GPIOD;
	LED_G.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_2;
	LED_G.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_OUTPUT;
	LED_G.GPIO_PinConfig.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL;
	LED_G.GPIO_PinConfig.GPIOx_PinSpeed = GPIO_SPEED_LOW;

	//GPIO Pin - PB8
	LED_R.pGPIOx_Base = GPIOB;
	LED_R.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_8;
	LED_R.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_OUTPUT;
	LED_R.GPIO_PinConfig.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL;
	LED_R.GPIO_PinConfig.GPIOx_PinSpeed = GPIO_SPEED_LOW;

	//GPIO Pin - PC6
	LED_B.pGPIOx_Base = GPIOC;
	LED_B.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_6;
	LED_B.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_OUTPUT;
	LED_B.GPIO_PinConfig.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL;
	LED_B.GPIO_PinConfig.GPIOx_PinSpeed = GPIO_SPEED_LOW;

	// GPIO Pin - PA5
	ONBOARD_LED.pGPIOx_Base = GPIOA;
	ONBOARD_LED.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_5;
	ONBOARD_LED.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_OUTPUT;
	ONBOARD_LED.GPIO_PinConfig.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL;
	ONBOARD_LED.GPIO_PinConfig.GPIOx_PinSpeed = GPIO_SPEED_LOW;

	//Input Configurations
	PushButton_Handle.pGPIOx_Base = GPIOC;
	//PushButton_Handle.GPIO_PinConfig = PushButton_Config;
	PushButton_Handle.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_13;
	PushButton_Handle.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_INT_FALLING;
	PushButton_Handle.GPIO_PinConfig.GPIOx_PinPUPDControl = GPIO_PUPD_PULL_UP;

	EndstopLSW_Handle.pGPIOx_Base = GPIOA;
	EndstopLSW_Handle.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_12;
	EndstopLSW_Handle.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_INPUT;
	EndstopLSW_Handle.GPIO_PinConfig.GPIOx_PinPUPDControl = GPIO_PUPD_PULL_DOWN;


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

	//IRQ Configurations
	GPIO_IRQ_INT_Config(IRQ_NO_EXTI15_10, ENABLE);
	GPIO_IRQ_Priority_Config(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI_15);	//Priority no - 15

	while(1){
		//are_ButtonPressed_Test();
		LED_YGRB_Test();
		SysTick_DelayMs(250);
	}
}

void EXTI0_IRQHandler(void){
	/* EXTI0 ISR Implementation */
	//Handle the Interrupt - Handler API
	GPIO_IRQHandling(GPIO_PIN_0);
}


void EXTI15_10_IRQHandler(){
	delay(500000);
	GPIO_IRQHandling(GPIO_PIN_13);				//Clear the Interrupt that was generated by the Button
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);
	delay(500000);						//2 second delay
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);
	//GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_5, HIGH);
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
	SysTick_DelayMs(250);
}


void LED_YGRB_Test(void){
	GPIO_WriteToOutputPin(LED_Y.pGPIOx_Base, LED_Y.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
	GPIO_WriteToOutputPin(LED_G.pGPIOx_Base, LED_G.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
	GPIO_WriteToOutputPin(LED_R.pGPIOx_Base, LED_R.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
	GPIO_WriteToOutputPin(LED_B.pGPIOx_Base, LED_B.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
	SysTick_DelayMs(250);
	GPIO_WriteToOutputPin(LED_Y.pGPIOx_Base, LED_Y.GPIO_PinConfig.GPIOx_PinNumber, LOW);
	GPIO_WriteToOutputPin(LED_G.pGPIOx_Base, LED_G.GPIO_PinConfig.GPIOx_PinNumber, LOW);
	GPIO_WriteToOutputPin(LED_R.pGPIOx_Base, LED_R.GPIO_PinConfig.GPIOx_PinNumber, LOW);
	GPIO_WriteToOutputPin(LED_B.pGPIOx_Base, LED_B.GPIO_PinConfig.GPIOx_PinNumber, LOW);
	SysTick_DelayMs(250);
}

void PORTC_LED_Test(void){
	GPIO_WriteToOutputPort(GPIOC, 0xffff);
	SysTick_DelayMs(750);
	GPIO_WriteToOutputPort(GPIOC, 0x0000);
	SysTick_DelayMs(750);
}

void ONBOARD_LED_Test(void){
	GPIO_WriteToOutputPin(GPIOA, ONBOARD_LED.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
	SysTick_DelayMs(750);
	GPIO_WriteToOutputPin(GPIOA, ONBOARD_LED.GPIO_PinConfig.GPIOx_PinNumber, LOW);
}

void ONBOARD_LED_Toggle(void){
	GPIO_ToggleOutputPin(GPIOA, ONBOARD_LED.GPIO_PinConfig.GPIOx_PinNumber);
}

