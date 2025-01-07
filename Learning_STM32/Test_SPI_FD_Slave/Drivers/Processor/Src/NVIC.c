/*
 * NVIC.c
 *
 *  Created on: Nov 1, 2024
 *      Author: singh
 */

#include "STM32F411xx.h"
#include "NVIC.h"

//Enable/Disable Interrupt APIs
void NVIC_EnableIRQ(uint8_t IRQ_no){
	uint8_t bit_pos = 0;

	//Check IRQ no, then calculate bit position
	if(IRQ_no < 31){
		bit_pos = IRQ_no;
		*NVIC_ISER0 |= (1<<bit_pos);
	} else if((IRQ_no > 31) && (IRQ_no < 66)){
		bit_pos = IRQ_no % 32;
		*NVIC_ISER1 |= (1<<bit_pos);
	} else if((IRQ_no >= 64) && (IRQ_no <= 85)){
		bit_pos = IRQ_no % 32;
		*NVIC_ISER2 |= (1<<bit_pos);
	} else{
		//Invalid!
	}
}

void NVIC_DisableIRQ(uint8_t IRQ_no){
	uint8_t bit_pos = 0;

	//Check IRQ no, then calculate bit position
	if(IRQ_no < 31){
		bit_pos = IRQ_no;
		*NVIC_ICER0 |= (1<<bit_pos);
	} else if((IRQ_no > 31) && (IRQ_no < 66)){
		bit_pos = IRQ_no % 32;
		*NVIC_ICER1 |= (1<<bit_pos);
	} else if((IRQ_no >= 64) && (IRQ_no <= 85)){
		bit_pos = IRQ_no % 32;
		*NVIC_ICER2 |= (1<<bit_pos);
	} else{
		//Invalid!
	}
}

//Set/Clear Interrupt Priority APIs
void NVIC_SetPriority(uint8_t IRQ_no, uint32_t Priority){
	/* To Configure the Priority of the Interrupt*/
	uint8_t bit_pos = 0;
	uint8_t iprx = 0;
	uint8_t iprx_section = 0;

	//1. Find the IPRx register no, only 4 IRQ per IPR register
	iprx = IRQ_no % 4;

	//2. Find the section and bit position, only 4 sections in each IPR register
	iprx_section = IRQ_no % 4;
	bit_pos = (iprx_section * 8) + (8 - NO_PR_BITS_IMPLEMENTED);	//each section of 8 bits, only X bits used

	//3. Configure the Priority
	*(NVIC_IPRx_BASE + (iprx)) |= (Priority << bit_pos);	//Base address + ipr register offset |= value is left shifted by bit_pos
}

