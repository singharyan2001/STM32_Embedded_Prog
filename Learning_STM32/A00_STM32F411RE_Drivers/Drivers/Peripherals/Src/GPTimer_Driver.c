/*
 * GPTimer_Driver.c
 *
 *  Created on: Oct 22, 2024
 *      Author: singh
 */

#include "STM32F411xx.h"
#include "GPTimer_Driver.h"
#include "NVIC.h"
#include "GPIO_Driver.h"


#define sys_freq_default	16000000
#define tim_freq_1khz_ms	1000		//1ms
#define TIMER_FREQUENCY_1MHZ	1000000

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
	//Set ARR Register
	TIMx->ARR = (period-1);
}

void TIMx_ConfigMode(TIM_RegDef_t *TIMx, uint8_t Mode){
	if(Mode == 0){
		TIMx->CR1 |= (TIM_MODE_DOWN_COUNTER << 4);
	} else {
		TIMx->CR1 |= (TIM_MODE_UP_COUNTER << 4);
	}
}

void TIMx_EnableInterrupt(TIM_RegDef_t *TIMx, uint8_t IRQ_no){
	TIMx->DIER |= (1 << TIMx_UIE);
	NVIC_EnableIRQ(IRQ_no);
}

void TIMx_DisableInterrupt(TIM_RegDef_t *TIMx, uint8_t IRQ_no){
	TIMx->DIER &= ~(1 << TIMx_UIE);
	NVIC_DisableIRQ(IRQ_no);
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
		TIMx_EnableInterrupt(TIMx, TIMx_Config->IRQ_No);		//Enables the Timer Interrupt
	} else{
		TIMx_DisableInterrupt(TIMx, TIMx_Config->IRQ_No);		//Disables the Timer Interrupt
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

// One-time configuration for TIM2 to prepare for delays
void TIMx_Delay_ms_Init(TIM_RegDef_t *TIMx) {
    // Enable clock access
    TIMx_ClockEnable(TIMx);

    // Set prescaler register
    TIMx_SetPrescaler(TIMx, 15);

    //Set Auto reload register
    TIMx_SetPeriod(TIMx, 1000);

    // Set Counter Mode (Up counter)
    TIMx_ConfigMode(TIMx, TIM_MODE_UP_COUNTER);
}

// Blocking delay in milliseconds
void TIMx_Delay_ms(TIM_RegDef_t *TIMx, uint32_t delay_ms) {
	//Start timer
	TIMx_Start(TIMx);
    for(volatile uint32_t i = 0; i < delay_ms; i++){
    	//Check for update flag
    	while(!(TIMx->SR & TIMx_SR_UIF)){}
    	//Clear flag
    	TIMx->SR &= ~TIMx_SR_UIF;
    }
    //Stop timer
    TIMx_Stop(TIMx);
}


//IRQ Handling
void TIMx_IRQHandling(TIM_RegDef_t *TIMx){
	// Clear the update interrupt flag
	if(TIMx->SR & TIMx_SR_UIF){
		TIMx->SR &= ~TIMx_SR_UIF;
	}
}

/*
 * PWM Drivers
 */

void TIMx_PWM_Init(TIMx_Config_t *TIMConfig, TIMx_PWMConfig_t *PWMConfig){
	//1. Initialize Timer hardware - Enable Timer clock, prescaler, ARR
	TIMx_ClockEnable(TIMConfig->TIMx);
	uint32_t psc_value = TIMx_ComputePrescaler(TIMConfig->TIMx, TIMConfig->System_frequency, TIMConfig->Timer_frequency);
	TIMx_SetPrescaler(TIMConfig->TIMx, psc_value);
	TIMx_SetPeriod(TIMConfig->TIMx, TIMConfig->delay);

	//2. Configure PWM Mode - Mode, OC Preload enable, initial duty cycle
	TIMx_PWM_SetMode(TIMConfig->TIMx, PWMConfig->PWM_MODE);
	TIMx_PWM_SetOCPreload(TIMConfig->TIMx, PWMConfig->PWM_MODE);
	TIMx_PWM_SetDutyCycle(TIMConfig->TIMx, PWMConfig->PWM_DutyCycle, PWMConfig->PWM_Channel);

	//3. Configure PWM Polarity and Enable Output channel
	TIMx_PWM_SetPolarity(TIMConfig->TIMx, PWMConfig->PWM_Polarity, PWMConfig->PWM_CH_Polarity);
	TIMx_PWM_EnableOutputChannel(TIMConfig->TIMx, PWMConfig->PWM_CH_Enable);

}


void TIMx_PWM_SetAltFunMode(GPIOx_RegDef_t *pGPIOx_Base, uint8_t GPIO_Pin, uint8_t Altfun){
	uint8_t reg_index = GPIO_Pin / 8;
	uint8_t bit_pos = ((GPIO_Pin % 8) * 4);
	pGPIOx_Base->AFR[reg_index] &= ~(0xf << bit_pos);
	pGPIOx_Base->AFR[reg_index] |= (Altfun << bit_pos);
}

void TIMx_PWM_SetMode(TIM_RegDef_t *TIMx, uint8_t pwm_mode){
	//1.Set PWM Mode in Capture/Compare Mode 1 Register - CCMR1
	TIMx->CCMR1 |= (pwm_mode << TIM_CCMR1_OC1M);
}

void TIMx_PWM_SetOCPreload(TIM_RegDef_t *TIMx, uint8_t en){
	//1. Configure the Output Compare Preload - 0CxPE bit in CCMR1
	TIMx->CCMR1 |= (en << TIM_CCMR1_OC1PE);
}

void TIMx_PWM_SetPolarity(TIM_RegDef_t *TIMx, uint8_t polarity, uint8_t channel_polarity){
	//1. Configure PWM Polarity of the PWM Channel
	TIMx->CCER |= (polarity << channel_polarity);
}

void TIMx_PWM_EnableOutputChannel(TIM_RegDef_t *TIMx, uint8_t channel_en){
	TIMx->CCER |= (1 << channel_en);
}

void TIMx_PWM_SetDutyCycle(TIM_RegDef_t *TIMx, uint32_t duty_cycle, uint8_t channel){
	//1. Check if input duty cycle is valid
	if(duty_cycle > 100){
		duty_cycle = 100;
	}
	//2. Calculate CCR value
	uint32_t CCR_Value = (TIMx->ARR+1)*duty_cycle/100;

	//3. Configure duty cycle wrt channel
	switch(channel){
		case 1:
			TIMx->CCR1 = CCR_Value;
			break;
		case 2:
			TIMx->CCR2 = CCR_Value;
			break;
		case 3:
			TIMx->CCR3 = CCR_Value;
			break;
		case 4:
			TIMx->CCR4 = CCR_Value;
			break;
	}

}

void TIMx_PWM_Start(TIM_RegDef_t *TIMx){
	//1. Start PWM Timer
	TIMx->CR1 |= (1<<TIM_CR1_CEN);
}

void TIMx_PWM_Stop(TIM_RegDef_t *TIMx){
	//1. Stop PWM Timer
	TIMx->CR1 &= ~(1<<TIM_CR1_CEN);
}

