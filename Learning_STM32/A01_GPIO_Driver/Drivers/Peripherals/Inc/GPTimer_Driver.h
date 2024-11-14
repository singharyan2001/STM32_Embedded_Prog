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

#define TIM_MODE_UP_COUNTER		1
#define TIM_MODE_DOWN_COUNTER	0

#define TIM_INT_ENABLE			1
#define TIM_INT_DISABLE			0


/*
 * Handle structure for Timer Peripheral
 */
typedef struct {
	uint32_t System_frequency;		// System frequency, default 16MHz
	uint32_t Timer_frequency;	  	// TIMER frequency ? 1Hz, 1KHz, 1MHz
    uint32_t Prescaler;				// Timer prescaler value
    uint32_t delay;         		// Auto-reload value
    uint8_t Mode;         			// Timer mode (e.g., up-counter, down-counter)
    uint8_t Interrupt;    			// Enable/Disable interrupt
    uint8_t IRQ_No;
}TIMx_Config_t;


/*
 * TIMx Peripheral APIs
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


//PWM APIs






#endif /* INC_GPTIMER_DRIVER_H_ */
