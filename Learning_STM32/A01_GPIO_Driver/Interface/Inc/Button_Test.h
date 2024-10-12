/*
 * PushButton_test.h
 *
 *  Created on: Oct 12, 2024
 *      Author: Aryan singh
 */

#ifndef INC_BUTTON_TEST_H_
#define INC_BUTTON_TEST_H_

#include "STM32F411xx.h"
#include "GPIO_Driver.h"

/*
 * Target Board - STM32F411RE
 * Using the Push Button provided on the Dev board
 * Using Endstop limit switch (externally), to try out read APIs and Interrupts APIs
 */

GPIOx_Handle_t PushButton_Handle;
GPIOx_Handle_t EndstopLSW_Handle;


//Push Button Configuration - B1 - User Button - PC13
GPIOx_PinConfig_t PushButton_Config = {
		.GPIOx_PinNumber = GPIO_PIN_NUMBER_13,
		.GPIOx_PinMode = GPIO_MODE_INPUT,
		.GPIOx_PinPUPDControl = GPIO_PUPD_PULL_UP
};

//Endstop Limit Switch Configuration - PA12
GPIOx_PinConfig_t Endstop_LimitSwitch_Config = {
		.GPIOx_PinNumber = GPIO_PIN_NUMBER_12,
		.GPIOx_PinMode = GPIO_MODE_INPUT,
		.GPIOx_PinPUPDControl = GPIO_PUPD_PULL_DOWN
};





#endif /* INC_BUTTON_TEST_H_ */
