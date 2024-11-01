/*
 * SYSTICK_Driver.c
 *
 *  Created on: Oct 20, 2024
 *      Author: singh
 */

#include "STM32F411xx.h"
#include "SYSTICK_Driver.h"

#define SYSTICK_LOAD_1MS	16000

void SysTick_DelayMs(uint32_t N){
	//1. Program Reload Value
	SYSTICK->RVR = SYSTICK_LOAD_1MS;

	//2. Clear Current Value Register
	SYSTICK->CVR = 0;

	//3. Program Control and Status register - Enable CNT, Select CLKSRC, Enable INT (Optional), Check Count flag
	//Select Clock Source - Processor clock source
	SYSTICK->CSR |= STCSR_PCLKSRC;
	//Enable the Systick Counter
	SYSTICK->CSR |= STCSR_ENABLE;

	//Clear the delay
	for(int i=0; i<N; i++){
		//WAIT until Count flag is set TO 1
		while(!(SYSTICK->CSR & STCSR_COUNTFLAG)){};
	}

	//After we achieve our delay, we disable the counter, set the count flag to zero
	SYSTICK->CSR = 0;
}

