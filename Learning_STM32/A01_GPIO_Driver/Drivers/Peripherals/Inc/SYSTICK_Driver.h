/*
 * SYSTICK_Driver.h
 *
 *  Created on: Oct 20, 2024
 *      Author: singh
 */

#ifndef INC_SYSTICK_DRIVER_H_
#define INC_SYSTICK_DRIVER_H_

#include "STM32F411xx.h"

#define STCSR_ENABLE		(1<<0)
#define STCSR_PCLKSRC		(1<<2)
#define STCSR_COUNTFLAG		(1<<16)

void SysTick_DelayMs(uint32_t N);

#endif /* INC_SYSTICK_DRIVER_H_ */
