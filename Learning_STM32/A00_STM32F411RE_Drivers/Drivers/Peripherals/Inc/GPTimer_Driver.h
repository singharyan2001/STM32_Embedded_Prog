/*
 * GPTimer_Driver.h
 *
 *  Created on: Oct 22, 2024
 *      Author: singh
 */

#ifndef INC_GPTIMER_DRIVER_H_
#define INC_GPTIMER_DRIVER_H_

#include "STM32F411xx.h"
#include <stdint.h>
#include "GPIO_Driver.h"

/*
 * Register specific macros
 */

//Timer Control Register 1 - CR1

#define TIM_CR1_CEN					0
#define TIM_CR1_UDIS				1
#define TIM_CR1_URS					2
#define TIM_CR1_OPM					3
#define TIM_CR1_DIR					4
#define TIM_CR1_CMS					5
#define TIM_CR1_ARPE				7
#define TIM_CR1_CKD					8

//Timer Status Register
#define TIM_SR_UIF					0

//Timer Capture/Compare Mode Register - CCMR 1&2
//OUTPUT CAPTURE
//TIMER CCMR1 Register
#define TIM_CCMR1_CC1S				0
#define TIM_CCMR1_OC1FE				2
#define TIM_CCMR1_OC1PE				3
#define TIM_CCMR1_OC1M				4
#define TIM_CCMR1_OC1CE				7
#define TIM_CCMR1_CC2S				8
#define TIM_CCMR1_OC2FE				10
#define TIM_CCMR1_OC2PE				11
#define TIM_CCMR1_OC2M				12
#define TIM_CCMR1_OC2CE				15

//TIMER CCMR2 Register
#define TIM_CCMR2_CC3S				0
#define TIM_CCMR2_OC3FE				2
#define TIM_CCMR1_OC3PE				3
#define TIM_CCMR1_OC3M				4
#define TIM_CCMR1_OC3CE				7
#define TIM_CCMR1_CC4S				8
#define TIM_CCMR1_OC4FE				10
#define TIM_CCMR1_OC4PE				11
#define TIM_CCMR1_OC4M				12
#define TIM_CCMR1_OC4CE				15

//INPUT CAPTURE


//Timer Capture/Compare Enable Register - CCER
#define TIM_CCER_CC1E				0
#define TIM_CCER_CC1P				1
#define TIM_CCER_CC1NP				3
#define TIM_CCER_CC2E				4
#define TIM_CCER_CC2P				5
#define TIM_CCER_CC2NP				7
#define TIM_CCER_CC3E				8
#define TIM_CCER_CC3P				9
#define TIM_CCER_CC3NP				11
#define TIM_CCER_CC4E				8
#define TIM_CCER_CC4P				9
#define TIM_CCER_CC4NP				11

/*
 * General Macros
 */
#define TIM_MODE_UP_COUNTER			1
#define TIM_MODE_DOWN_COUNTER		0

#define TIM_INT_ENABLE				1
#define TIM_INT_DISABLE				0


#define TIM_PWM_MODE1				6
#define TIM_PWM_MODE2				7

#define TIM_OC1PE_DISABLE			0
#define TIM_OC1PE_ENABLE			1

//#define TIM_PWM_OC1_ACTIVE_HIGH		0
//#define TIM_PWM_OC1_ACTIVE_LOW		1

#define PWM_CHANNEL_1				1
#define PWM_CHANNEL_2				2
#define PWM_CHANNEL_3				3
#define PWM_CHANNEL_4				4

#define PWM_POLARITY_ACTIVE_HIGH	0
#define PWM_POLARITY_ACTIVE_LOW		1

/*
 * Data structure for Timer Peripheral
 */
typedef struct {
	TIM_RegDef_t *TIMx;
	uint32_t system_frequency;		// System frequency, default 16MHz
	uint32_t timer_frequency;	  	// TIMER frequency ? 1Hz, 1KHz, 1MHz
    uint32_t prescaler;				// Timer prescaler value
    uint32_t desired_delay;         // Auto-reload value
    uint8_t timer_mode;         			// Timer mode (e.g., up-counter, down-counter)
    uint8_t interrupt;    			// Enable/Disable interrupt
    uint8_t irq_no;					// Timer peripheral - irq number
}TIMx_Config_t;


typedef struct{
	uint8_t pwm_mode;
	uint8_t pwm_channel;
	uint8_t pwm_output_compare_preload_enable;
	uint8_t pwm_polarity;
	uint8_t pwm_channel_polarity;
	uint8_t pwm_channel_enable;
	uint32_t pwm_duty_cycle;
}TIMx_PWMConfig_t;


/*
 * TIMx Peripheral APIs --> TIM2 to TIM5 APIs
 */
//Configuration APIs
void TIMx_ClockEnable(TIM_RegDef_t *TIMx);
//void TIMx_ClockDisable(TIM_RegDef_t *TIMx);
uint32_t TIMx_ComputePrescaler(TIM_RegDef_t *TIMx, uint32_t sys_freq, uint32_t tim_freq);
void TIMx_SetPrescaler(TIM_RegDef_t *TIMx, uint32_t prescaler);
void TIMx_SetPeriod(TIM_RegDef_t *TIMx, uint32_t period);
void TIMx_ConfigMode(TIM_RegDef_t *TIMx, uint8_t Mode);

//Initialization API
void TIMx_Init(TIM_RegDef_t *TIMx, TIMx_Config_t *TIMx_Config);
void TIMx_Delay_ms_Init(TIM_RegDef_t *TIMx);

//General application APIs
void TIMx_Start(TIM_RegDef_t *TIMx);
void TIMx_Stop(TIM_RegDef_t *TIMx);

void TIMx_Delay_ms(TIM_RegDef_t *TIMx, uint32_t delay_ms);
//TIMx_Delay_Blocking_1ms

//Interrupt Handling APIs
void TIMx_EnableInterrupt(TIM_RegDef_t *TIMx, uint8_t IRQ_no);
void TIMx_DisableInterrupt(TIM_RegDef_t *TIMx, uint8_t IRQ_no);
void TIMx_IRQHandling(TIM_RegDef_t *TIMx);

//PWM Drivers
void TIMx_PWM_Init(TIMx_Config_t *TIMConfig, TIMx_PWMConfig_t *PWMConfig);

void TIMx_PWM_SetAltFunMode(GPIOx_RegDef_t *pGPIOx_Base, uint8_t GPIO_Pin, uint8_t Altfun);

void TIMx_PWM_SetMode(TIM_RegDef_t *TIMx, uint8_t pwm_mode, uint8_t pwm_channel);
void TIMx_PWM_SetOCPreload(TIM_RegDef_t *TIMx, uint8_t pwm_channel, uint8_t en);

void TIMx_PWM_SetChannelPolarity(TIM_RegDef_t *TIMx, uint8_t pwm_channel, uint8_t channel_polarity);
void TIMx_PWM_EnableOutputChannel(TIM_RegDef_t *TIMx, uint8_t pwm_channel, uint8_t channel_en);

void TIMx_PWM_SetDutyCycle(TIM_RegDef_t *TIMx, uint32_t duty_cycle, uint8_t pwm_channel);

void TIMx_PWM_Start(TIM_RegDef_t *TIMx);
void TIMx_PWM_Stop(TIM_RegDef_t *TIMx);


#endif /* INC_GPTIMER_DRIVER_H_ */
