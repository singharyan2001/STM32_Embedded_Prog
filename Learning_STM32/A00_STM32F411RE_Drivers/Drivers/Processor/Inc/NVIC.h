/*
 * NVIC.h
 *
 *  Created on: Nov 1, 2024
 *      Author: singh
 */

#ifndef PROCESSOR_INC_NVIC_H_
#define PROCESSOR_INC_NVIC_H_

#include <stdint.h>

//Enable/Disable Interrupt APIs
void NVIC_EnableIRQ(uint8_t IRQ_no);
void NVIC_DisableIRQ(uint8_t IRQ_no);

//Set/Clear Interrupt Priority APIs
void NVIC_SetPriority(uint8_t IRQ_no, uint32_t Priority);

//Pending Interrupt APIs
void NVIC_SetPendingIRQ(uint8_t IRQ_no);
void NVIC_ClearPendingIRQ(uint8_t IRQ_no);

//Check API for any Active Interrupt
uint32_t NVIC_GetPendingIRQ(uint8_t IRQ_no);

//Priority Grouping API
//void NVIC_SetPriorityGrouping(uint32_t priority_group);


#endif /* PROCESSOR_INC_NVIC_H_ */
