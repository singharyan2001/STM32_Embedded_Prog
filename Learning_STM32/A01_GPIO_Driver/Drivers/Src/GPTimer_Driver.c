/*
 * GPTimer_Driver.c
 *
 *  Created on: Oct 22, 2024
 *      Author: singh
 */

#include "STM32F411xx.h"
#include "GPTimer_Driver.h"

#define sys_freq_default	16000000
#define tim_freq_1khz_ms	1000		//1ms

//APB1 Bus interface
#define TIM2_EN			(1<<0)		//APB1
#define TIM3_EN			(1<<1)		//APB1
#define TIM4_EN			(1<<2)		//APB1
#define TIM5_EN			(1<<3)		//APB1

//General MACROS
#define TIMx_CEN		(1<<0)
#define TIMx_SR_UIF		(1<<0)

#define TIMx_UIE		 0


//Configuration APIs
void TIMx_ClockEnable(TIM_RegDef_t *TIMx){
	if(TIMx == TIM2){
		//Enable TIM2 clock Access
		RCC->APB1ENR |= TIM2_EN;
	} else if(TIMx == TIM3){
		//Enable TIM3 clock Access
		RCC->APB1ENR |= TIM3_EN;
	} else if(TIMx == TIM4){
		//Enable TIM4 clock Access
		RCC->APB1ENR |= TIM4_EN;
	} else if(TIMx == TIM5){
		//Enable TIM5 clock Access
		RCC->APB1ENR |= TIM5_EN;
	} else{
		//No conditions matched!
	}
}

//void TIMx_ClockDisable(TIM_RegDef_t *TIMx){
//	if(TIMx == TIM2){
//		//Enable TIM2 clock Access
//		RCC->APB1ENR |= TIM2_EN;
//	} else if(TIMx == TIM3){
//		RCC->APB1ENR |= TIM3_EN;
//	} else if(TIMx == TIM4){
//		RCC->APB1ENR |= TIM4_EN;
//	} else if(TIMx == TIM5){
//		RCC->APB1ENR |= TIM5_EN;
//	} else{
//		//No conditions matched!
//	}
//}

void TIMx_SetPrescaler(TIM_RegDef_t *TIMx, uint32_t prescaler){
	TIMx->PSC = prescaler;
}

uint32_t TIMx_ComputePrescaler(TIM_RegDef_t *TIMx, uint32_t sys_freq, uint32_t tim_freq){
	return ((sys_freq/tim_freq) - 1);
}

void TIMx_SetPeriod(TIM_RegDef_t *TIMx, uint32_t period){
	TIMx->ARR = (period-1);
}

void TIMx_ConfigMode(TIM_RegDef_t *TIMx, uint8_t Mode){
	if(Mode == 0){
		TIMx->CR1 |= (TIM_MODE_DOWN_COUNTER << 4);
	} else {
		TIMx->CR1 |= (TIM_MODE_UP_COUNTER << 4);
	}
}

void TIMx_EnableInterrupt(TIM_RegDef_t *TIMx){
	TIMx->DIER |= (1 << TIMx_UIE);
	*NVIC_ISER0 |= (1 << IRQ_NO_TIM2); //for now enable interrupts on timer 2
}

void TIMx_DisableInterrupt(TIM_RegDef_t *TIMx){
	TIMx->DIER &= ~(1 << TIMx_UIE);
	*NVIC_ICER0 |= (1 << IRQ_NO_TIM2);	//for now disable interrupts on timer 2
}


void TIMx_Init(TIM_RegDef_t *TIMx, TIMx_Config_t *TIMx_Config){
	//Enable clock access to Timer Peripheral
	TIMx_ClockEnable(TIMx);

	//Set value to Prescaler Register (PSC)
	TIMx_SetPrescaler(TIMx, TIMx_Config->Prescaler);

	//Set value to Auto Reload register (ARR)
	TIMx_SetPeriod(TIMx, TIMx_Config->delay);

	//Set Counter mode
	TIMx_ConfigMode(TIMx, TIMx_Config->Mode);

	//Enable or Disable Interrupt on Timer peripheral
	if(TIMx_Config->Interrupt == TIM_INT_ENABLE){
		TIMx_EnableInterrupt(TIMx);					//Enables the Timer Interrupt
	} else{
		TIMx_DisableInterrupt(TIMx);				//Disables the Timer Interrupt
	}
}


//General Application APIs
void TIMx_Start(TIM_RegDef_t *TIMx){
	TIMx->CNT = 0;
	TIMx->CR1 |= TIMx_CEN;
}

void TIMx_Stop(TIM_RegDef_t *TIMx){
	TIMx->CNT = 0;
	TIMx->CR1 &= ~(TIMx_CEN);
}

void TIMx_Delay_Blocking_ms(TIM_RegDef_t *TIMx, uint32_t delay_ms){
	//Enable clock access
	TIMx_ClockEnable(TIMx);

	//Set prescaler register
	uint32_t psc_value = TIMx_ComputePrescaler(TIMx, sys_freq_default, tim_freq_1khz_ms);
	TIMx_SetPrescaler(TIMx, psc_value);

	//Set Auto reload register
	TIMx_SetPeriod(TIMx, delay_ms);

	//Clear counter
	TIMx->CNT = 0;

	//Start timer
	TIMx_Start(TIMx);

	//Check for update flag
	while(!(TIMx->SR & TIMx_SR_UIF)){
		//wait till UIF bit is set in TIM SR
	}
	//Clear flag
	TIMx->SR &= ~(1 << 0);

	//Stop timer
	TIMx_Stop(TIMx);
}


//IRQ Handling
void TIMx_IRQHandling(TIM_RegDef_t *TIMx){
	// Clear the update interrupt flag
	if(TIMx->SR & TIMx_SR_UIF){
		TIMx->SR &= ~(1 << 0);
	}
}

