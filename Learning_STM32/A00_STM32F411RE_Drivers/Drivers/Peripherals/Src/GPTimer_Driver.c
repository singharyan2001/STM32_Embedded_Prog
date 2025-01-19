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


#define SYSTEM_FREQUENCY_DEFAULT	16000000	//default interal RC oscillator
#define TIMER_FREQUENCY_10KHZ		1000		//To achieve 1ms timebase
#define TIMER_FREQUENCY_1MHZ		1000000		//To achieve 1us timebase


//APB1 Bus interface
#define TIM2_EN			(1<<0)
#define TIM3_EN			(1<<1)
#define TIM4_EN			(1<<2)
#define TIM5_EN			(1<<3)

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
	TIMx_SetPrescaler(TIMx, TIMx_Config->prescaler);

	//Set value to Auto Reload register (ARR)
	TIMx_SetPeriod(TIMx, TIMx_Config->desired_delay);

	//Set Counter mode
	TIMx_ConfigMode(TIMx, TIMx_Config->timer_mode);

	//Enable or Disable Interrupt on Timer peripheral
	if(TIMx_Config->interrupt == TIM_INT_ENABLE){
		TIMx_EnableInterrupt(TIMx, TIMx_Config->irq_no);		//Enables the Timer Interrupt
	} else{
		TIMx_DisableInterrupt(TIMx, TIMx_Config->irq_no);		//Disables the Timer Interrupt
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
	uint32_t psc_value = TIMx_ComputePrescaler(TIMConfig->TIMx, TIMConfig->system_frequency, TIMConfig->timer_frequency);
	TIMx_SetPrescaler(TIMConfig->TIMx, psc_value);
	TIMx_SetPeriod(TIMConfig->TIMx, TIMConfig->desired_delay);

	//2. Configure PWM Mode - Mode, OC Preload enable, initial duty cycle
	TIMx_PWM_SetMode(TIMConfig->TIMx, PWMConfig->pwm_channel, PWMConfig->pwm_mode);
	TIMx_PWM_SetOCPreload(TIMConfig->TIMx, PWMConfig->pwm_channel, PWMConfig->pwm_output_compare_preload_enable);
	TIMx_PWM_SetDutyCycle(TIMConfig->TIMx, PWMConfig->pwm_duty_cycle, PWMConfig->pwm_channel);

	//3. Configure PWM Polarity and Enable Output channel
	TIMx_PWM_SetChannelPolarity(TIMConfig->TIMx, PWMConfig->pwm_channel, PWMConfig->pwm_channel_polarity);
	TIMx_PWM_EnableOutputChannel(TIMConfig->TIMx, PWMConfig->pwm_channel, PWMConfig->pwm_channel_enable);
}


void TIMx_PWM_SetAltFunMode(GPIOx_RegDef_t *pGPIOx_Base, uint8_t GPIO_Pin, uint8_t Altfun){
	uint8_t reg_index = GPIO_Pin / 8;
	uint8_t bit_pos = ((GPIO_Pin % 8) * 4);
	pGPIOx_Base->AFR[reg_index] &= ~(0xf << bit_pos);
	pGPIOx_Base->AFR[reg_index] |= (Altfun << bit_pos);
}

void TIMx_PWM_SetMode(TIM_RegDef_t *TIMx, uint8_t pwm_mode, uint8_t pwm_channel){
	//1.Set PWM Mode in Capture/Compare Mode 1 Register - CCMR1
	if(pwm_channel == PWM_CHANNEL_1){
		TIMx->CCMR1 |= (pwm_mode << TIM_CCMR1_OC1M);
	}
	else if(pwm_channel == PWM_CHANNEL_2){
		TIMx->CCMR1 |= (pwm_mode << TIM_CCMR1_OC2M);
	}
	else if(pwm_channel == PWM_CHANNEL_3){
		TIMx->CCMR1 |= (pwm_mode << TIM_CCMR1_OC3M);
	}
	else if(pwm_channel == PWM_CHANNEL_4){
		TIMx->CCMR1 |= (pwm_mode << TIM_CCMR1_OC4M);
	}
	else{
		//no match found
	}
}

void TIMx_PWM_SetOCPreload(TIM_RegDef_t *TIMx, uint8_t pwm_channel, uint8_t en){
	//1. Configure the Output Compare Preload - 0CxPE bit in CCMR1
	if(pwm_channel == PWM_CHANNEL_1){
		TIMx->CCMR1 |= (en << TIM_CCMR1_OC1PE);
	}
	else if(pwm_channel == PWM_CHANNEL_2){
		TIMx->CCMR1 |= (en << TIM_CCMR1_OC2PE);
	}
	else if(pwm_channel == PWM_CHANNEL_3){
		TIMx->CCMR1 |= (en << TIM_CCMR1_OC2PE);
	}
	else if(pwm_channel == PWM_CHANNEL_4){
		TIMx->CCMR1 |= (en << TIM_CCMR1_OC2PE);
	}
	else{
		//no match found
	}
}

void TIMx_PWM_SetChannelPolarity(TIM_RegDef_t *TIMx, uint8_t pwm_channel, uint8_t channel_polarity){
	//1. Configure PWM Polarity of the PWM Channel
	if(pwm_channel == PWM_CHANNEL_1){
		TIMx->CCER |= (channel_polarity << TIM_CCER_CC1P);
	}
	else if(pwm_channel == PWM_CHANNEL_2){
		TIMx->CCER |= (channel_polarity << TIM_CCER_CC2P);
	}
	else if(pwm_channel == PWM_CHANNEL_3){
		TIMx->CCER |= (channel_polarity << TIM_CCER_CC3P);
	}
	else if(pwm_channel == PWM_CHANNEL_4){
		TIMx->CCER |= (channel_polarity << TIM_CCER_CC4P);
	}
	else{
		//no match found
	}
}

void TIMx_PWM_EnableOutputChannel(TIM_RegDef_t *TIMx, uint8_t pwm_channel, uint8_t channel_en){
	if(pwm_channel == PWM_CHANNEL_1){
		TIMx->CCER |= (channel_en << TIM_CCER_CC1E);
	}
	else if(pwm_channel == PWM_CHANNEL_2){
		TIMx->CCER |= (channel_en << TIM_CCER_CC2E);
	}
	else if(pwm_channel == PWM_CHANNEL_3){
		TIMx->CCER |= (channel_en << TIM_CCER_CC3E);
	}
	else if(pwm_channel == PWM_CHANNEL_4){
		TIMx->CCER |= (channel_en << TIM_CCER_CC4E);
	}
	else{
		//no match found
	}
}

void TIMx_PWM_SetDutyCycle(TIM_RegDef_t *TIMx, uint32_t duty_cycle, uint8_t pwm_channel){
	//1. Check if input duty cycle is valid
	if(duty_cycle > 100){
		duty_cycle = 100;
	}
	//2. Calculate CCR value
	uint32_t CCR_Value = (TIMx->ARR+1)*duty_cycle/100;

	//3. Configure duty cycle wrt channel
	switch(pwm_channel){
		case PWM_CHANNEL_1:
			TIMx->CCR1 = CCR_Value;
			break;
		case PWM_CHANNEL_2:
			TIMx->CCR2 = CCR_Value;
			break;
		case PWM_CHANNEL_3:
			TIMx->CCR3 = CCR_Value;
			break;
		case PWM_CHANNEL_4:
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

