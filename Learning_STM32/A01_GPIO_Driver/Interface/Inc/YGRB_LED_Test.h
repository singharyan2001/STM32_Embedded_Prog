/*
 * YGRB_LED_Test.h
 *
 *  Created on: Oct 12, 2024
 *      Author: Aryan singh
 */

#ifndef INC_YGRB_LED_TEST_H_
#define INC_YGRB_LED_TEST_H_

#include "STM32F411xx.h"
#include "GPIO_Driver.h"


GPIOx_Handle_t ONBOARD_LED;
GPIOx_Handle_t LED_Y;
GPIOx_Handle_t LED_G;
GPIOx_Handle_t LED_R;
GPIOx_Handle_t LED_B;

// GPIO Pin - PA5
GPIOx_PinConfig_t ONBOARD_LED_Config = {
		.GPIOx_PinNumber = GPIO_PIN_NUMBER_5,
		.GPIOx_PinMode = GPIO_MODE_OUTPUT,
		.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL,
		.GPIOx_PinSpeed = GPIO_SPEED_LOW
};


// GPIO Pin - PC8
GPIOx_PinConfig_t Yellow_led = {
		.GPIOx_PinNumber = GPIO_PIN_NUMBER_8,
		.GPIOx_PinMode = GPIO_MODE_OUTPUT,
		.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL,
		.GPIOx_PinSpeed = GPIO_SPEED_LOW
};

//GPIO Pin - PD2
GPIOx_PinConfig_t Green_led = {
		.GPIOx_PinNumber = GPIO_PIN_NUMBER_2,
		.GPIOx_PinMode = GPIO_MODE_OUTPUT,
		.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL,
		.GPIOx_PinSpeed = GPIO_SPEED_LOW
};

//GPIO Pin - PB8
GPIOx_PinConfig_t Red_led = {
		.GPIOx_PinNumber = GPIO_PIN_NUMBER_8,
		.GPIOx_PinMode = GPIO_MODE_OUTPUT,
		.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL,
		.GPIOx_PinSpeed = GPIO_SPEED_LOW
};

//GPIO Pin - PC6
GPIOx_PinConfig_t Blue_led = {
		.GPIOx_PinNumber = GPIO_PIN_NUMBER_6,
		.GPIOx_PinMode = GPIO_MODE_OUTPUT,
		.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL,
		.GPIOx_PinSpeed = GPIO_SPEED_LOW
};



#endif /* INC_YGRB_LED_TEST_H_ */
