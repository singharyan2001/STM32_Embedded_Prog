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
#include "SYSTICK_Driver.h"
#include "GPTimer_Driver.h"

#define SYSTEM_FREQUENCY	16000000
#define TIMER_FREQUENCY		1000	//1KHz - 1000Hz

void TIM2_PWM_Init(uint32_t frequency);
void TIM2_SetDutyCycle(uint32_t duty_cycle);

//void TIM_PWM_Init(TIM_RegDef_t *TIMx, uint32_t frequency);
//void TIM_SetDutyCycle(TIM_RegDef_t *TIMx, uint32_t duty_cycle);


//void LED_YGRB_Test(void);
//void PORTC_LED_Test(void);
void ONBOARD_LED_Test(void);
void ONBOARD_LED_Toggle(void);

//void are_ButtonPressed_Test(void);

void delay(uint32_t value);

//GPIOx_Handle_t LED_Y;
//GPIOx_Handle_t LED_G;
//GPIOx_Handle_t LED_R;
//GPIOx_Handle_t LED_B;
GPIOx_Handle_t ONBOARD_LED;

//GPIOx_Handle_t PushButton_Handle;
//GPIOx_Handle_t EndstopLSW_Handle;


int main(void)
{
	//Clear the Newly created structures
//	memset(&LED_Y, 0, sizeof(LED_Y));
//	memset(&LED_G, 0, sizeof(LED_G));
//	memset(&LED_R, 0, sizeof(LED_R));
//	memset(&LED_B, 0, sizeof(LED_B));
//	memset(&ONBOARD_LED, 0, sizeof(ONBOARD_LED));
//	memset(&PushButton_Handle, 0, sizeof(PushButton_Handle));
//	memset(&EndstopLSW_Handle, 0, sizeof(EndstopLSW_Handle));

	//Configuring Up all Handlers
	//Output Configurations
	//GPIO Pin - PC8
//	LED_Y.pGPIOx_Base = GPIOC;
//	LED_Y.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_8;
//	LED_Y.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_OUTPUT;
//	LED_Y.GPIO_PinConfig.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL;
//	LED_Y.GPIO_PinConfig.GPIOx_PinSpeed = GPIO_SPEED_LOW;

	//GPIO Pin - PD2
//	LED_G.pGPIOx_Base = GPIOD;
//	LED_G.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_2;
//	LED_G.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_OUTPUT;
//	LED_G.GPIO_PinConfig.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL;
//	LED_G.GPIO_PinConfig.GPIOx_PinSpeed = GPIO_SPEED_LOW;

	//GPIO Pin - PB8
//	LED_R.pGPIOx_Base = GPIOB;
//	LED_R.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_8;
//	LED_R.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_OUTPUT;
//	LED_R.GPIO_PinConfig.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL;
//	LED_R.GPIO_PinConfig.GPIOx_PinSpeed = GPIO_SPEED_LOW;

	//GPIO Pin - PC6
//	LED_B.pGPIOx_Base = GPIOC;
//	LED_B.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_6;
//	LED_B.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_OUTPUT;
//	LED_B.GPIO_PinConfig.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL;
//	LED_B.GPIO_PinConfig.GPIOx_PinSpeed = GPIO_SPEED_LOW;

	// GPIO Pin - PA5
	ONBOARD_LED.pGPIOx_Base = GPIOA;
	ONBOARD_LED.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_5;
	ONBOARD_LED.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_OUTPUT;
	ONBOARD_LED.GPIO_PinConfig.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL;
	ONBOARD_LED.GPIO_PinConfig.GPIOx_PinSpeed = GPIO_SPEED_LOW;

	//Input Configurations
//	PushButton_Handle.pGPIOx_Base = GPIOC;
	//PushButton_Handle.GPIO_PinConfig = PushButton_Config;
//	PushButton_Handle.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_13;
//	PushButton_Handle.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_INT_FALLING;
//	PushButton_Handle.GPIO_PinConfig.GPIOx_PinPUPDControl = GPIO_PUPD_PULL_UP;
//
//	EndstopLSW_Handle.pGPIOx_Base = GPIOA;
//	EndstopLSW_Handle.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_12;
//	EndstopLSW_Handle.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_INPUT;
//	EndstopLSW_Handle.GPIO_PinConfig.GPIOx_PinPUPDControl = GPIO_PUPD_PULL_DOWN;

	//Setup timer 2
	TIMx_Config_t TIM2_Config;
	memset(&TIM2_Config, 0, sizeof(TIM2_Config));

	TIM2_Config.System_frequency = SYSTEM_FREQUENCY;
	TIM2_Config.Timer_frequency = TIMER_FREQUENCY;
	TIM2_Config.Prescaler = TIMx_ComputePrescaler(TIM2, SYSTEM_FREQUENCY, TIMER_FREQUENCY);
	TIM2_Config.Mode = TIM_MODE_UP_COUNTER;
	TIM2_Config.Interrupt = TIM_INT_ENABLE;
	TIM2_Config.IRQ_No = IRQ_NO_TIM2;
	TIM2_Config.delay = 250;

	//TIMx_Init(TIM2, &TIM2_Config);

	//Provide Clock Access to the GPIO Peripherals
	GPIOx_PClkControl(GPIOA, CLK_EN);
//	GPIOx_PClkControl(GPIOB, CLK_EN);
//	GPIOx_PClkControl(GPIOC, CLK_EN);
//	GPIOx_PClkControl(GPIOD, CLK_EN);

	//Initialize all Configurations
//	GPIOx_Init(&LED_Y);
//	GPIOx_Init(&LED_G);
//	GPIOx_Init(&LED_R);
//	GPIOx_Init(&LED_R);
//	GPIOx_Init(&LED_B);
	GPIOx_Init(&ONBOARD_LED);

//	GPIOx_Init(&PushButton_Handle);
//	GPIOx_Init(&EndstopLSW_Handle);

	//IRQ Configurations
//	GPIO_IRQ_INT_Config(IRQ_NO_EXTI15_10, ENABLE);
//	GPIO_IRQ_Priority_Config(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI_15);	//Priority no - 15

	//TIMx_Start(TIM2);
	//TIMx_Delay_ms_Init(TIM2);

	TIM2_PWM_Init(1000);	//1khz

	for (volatile int i = 0; i < 1000000; i++); // Simple delay

	while(1){
		//ONBOARD_LED_Test();

		TIM2_SetDutyCycle(750);
		for (volatile int i = 0; i < 1000000; i++); // Simple delay
		TIM2_SetDutyCycle(250);
		for (volatile int i = 0; i < 1000000; i++); // Simple delay
		TIM2_SetDutyCycle(50);
		for (volatile int i = 0; i < 1000000; i++); // Simple delay
	}
}

void TIM2_IRQHandler(){
	//ISR Starts here
	TIMx_IRQHandling(TIM2);
	//Do something
	ONBOARD_LED_Toggle();
	//ISR Ends here
}


//void EXTI15_10_IRQHandler(){
//	delay(500000);
//	GPIO_IRQHandling(GPIO_PIN_13);				//Clear the Interrupt that was generated by the Button
//	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);
//	delay(500000);						//2 second delay
//	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);
//	//GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_5, HIGH);
//}


void delay(uint32_t value){
	for(int i=0; i < value; i++){};
}


//void are_ButtonPressed_Test(void){
//	if(GPIO_ReadFromInputPin(GPIOC, PushButton_Handle.GPIO_PinConfig.GPIOx_PinNumber) == LOW){
//		LED_YGRB_Test();
//	}
//	else if(GPIO_ReadFromInputPin(GPIOA, EndstopLSW_Handle.GPIO_PinConfig.GPIOx_PinNumber) == HIGH){
//		PORTC_LED_Test();
//		//ONBOARD_LED_Test();
//	}
//	else{
//		ONBOARD_LED_Toggle();
//	}
//	SysTick_DelayMs(250);
//}
//
//
//void LED_YGRB_Test(void){
//	GPIO_WriteToOutputPin(LED_Y.pGPIOx_Base, LED_Y.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
//	GPIO_WriteToOutputPin(LED_G.pGPIOx_Base, LED_G.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
//	GPIO_WriteToOutputPin(LED_R.pGPIOx_Base, LED_R.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
//	GPIO_WriteToOutputPin(LED_B.pGPIOx_Base, LED_B.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
//	SysTick_DelayMs(250);
//	GPIO_WriteToOutputPin(LED_Y.pGPIOx_Base, LED_Y.GPIO_PinConfig.GPIOx_PinNumber, LOW);
//	GPIO_WriteToOutputPin(LED_G.pGPIOx_Base, LED_G.GPIO_PinConfig.GPIOx_PinNumber, LOW);
//	GPIO_WriteToOutputPin(LED_R.pGPIOx_Base, LED_R.GPIO_PinConfig.GPIOx_PinNumber, LOW);
//	GPIO_WriteToOutputPin(LED_B.pGPIOx_Base, LED_B.GPIO_PinConfig.GPIOx_PinNumber, LOW);
//	SysTick_DelayMs(250);
//}
//
//void PORTC_LED_Test(void){
//	GPIO_WriteToOutputPort(GPIOC, 0xffff);
//	SysTick_DelayMs(750);
//	GPIO_WriteToOutputPort(GPIOC, 0x0000);
//	SysTick_DelayMs(750);
//}

void ONBOARD_LED_Test(void){
	GPIO_WriteToOutputPin(GPIOA, ONBOARD_LED.GPIO_PinConfig.GPIOx_PinNumber, HIGH);
	//SysTick_DelayMs(750);
	TIMx_Delay_ms(TIM2, 250);
	//TIMx_Delay_Blocking_ms(TIM2, 1000);
	GPIO_WriteToOutputPin(GPIOA, ONBOARD_LED.GPIO_PinConfig.GPIOx_PinNumber, LOW);
	TIMx_Delay_ms(TIM2, 250);
}

void ONBOARD_LED_Toggle(void){
	GPIO_ToggleOutputPin(GPIOA, ONBOARD_LED.GPIO_PinConfig.GPIOx_PinNumber);
}

//void TIM_PWM_Init(TIM_RegDef_t *TIMx, uint32_t frequency){
//	//1.Enable Timer X and GPIO X Clock
//	TIMx_ClockEnable(TIMx);
//	RCC->AHB1ENR |= (1<<0); //enable clock access to GPIOA Peripheral
//	GPIOx_PClkControl(GPIOA, CLK_EN);
//
//	//2. Set GPIO Pin to Alternate Function Mode (PA5)
//	GPIOA->MODER |= (1<<5);
//	GPIOA->OTYPER &= ~(1<<5);
//
//	//3. Configure TIMER x for PWM
//
//	//4. Set PWM Mode on TIMER X Channel n
//
//	//5. Set Initial duty cycle to 50%
//
//	//6. Enable Timer X Counter
//}

void TIM2_PWM_Init(uint32_t frequency) {
    // 1. Enable Timer 2 and GPIOA Clocks
    RCC->APB1ENR |= (1<<0); // Enable TIM2 Clock
    RCC->AHB1ENR |= (1<<0); // Enable GPIOA Clock

    // 2. Set PA5 to Alternate Function Mode
    GPIOA->MODER &= ~(0x3 << (5 * 2));   // Clear MODER5[1:0] bits for PA5
    GPIOA->MODER |= (0x2 << (5 * 2));    // Set MODER5 to Alternate Function mode
    GPIOA->AFR[0] |= (0x1 << (5 * 4));   // Set AFRL5 to AF1 (TIM2 CH1 on PA5)

    // 3. Configure Timer 2 for PWM
    uint32_t psc_value = (SYSTEM_FREQUENCY / (frequency)) - 1;
    TIM2->PSC = psc_value;              // Set prescaler for 1 kHz PWM frequency
    TIM2->ARR = 999;                    // Set Auto-Reload Register for 1 ms period, therefore 1000ticks - 1000ms i.e. 1 second (1000 ticks at 1 MHz)

    // 4. Set PWM Mode 1 on TIM2 CH1
    TIM2->CCMR1 |= (0x6 << 4);  // PWM Mode 1 on Channel 1
    TIM2->CCMR1 |= (1<<3);         			     // Enable preload on CCR1
    TIM2->CCER |= 0x0001;                 // Enable output on TIM2 CH1

    // 5. Set initial duty cycle to 50%
    TIM2->CCR1 = 500;  // 50% Duty Cycle

    // 6. Enable Timer 2 Counter
    TIM2->CR1 |= (1<<0);
}

void TIM2_SetDutyCycle(uint32_t duty_cycle) {
    // Ensure duty cycle does not exceed ARR
    if (duty_cycle > TIM2->ARR) duty_cycle = TIM2->ARR;
    TIM2->CCR1 = duty_cycle;
}


//void TIM_SetDutyCycle(TIM_RegDef_t *TIMx, uint32_t duty_cycle){
//	//1. Check: Ensure Duty cycle does not exceed Auto-reload register value
//
//	//2. Set new duty cycle
//}

