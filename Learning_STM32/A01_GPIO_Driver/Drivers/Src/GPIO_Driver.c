/*
 * TARGET Board: STM32F411RE
 * Peripheral Driver: GPIO_Driver.c
 *
 *  Created on: Oct 12, 2024
 *      Author: Aryan singh
 */

#include "STM32F411xx.h"
#include "GPIO_Driver.h"



/*
 * GPIO Peripheral - GPIO Peripheral Clock Control API Definition
 */
void GPIOx_PClkControl(GPIOx_RegDef_t *pGPIOx_Base, uint8_t EN_DI){
	if(EN_DI == CLK_EN){
		if(pGPIOx_Base == GPIOA){
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx_Base == GPIOB){
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx_Base == GPIOC){
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx_Base == GPIOD){
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx_Base == GPIOE){
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx_Base == GPIOH){
			GPIOH_PCLK_EN();
		}
		else{
		}
	}
	else if(EN_DI == CLK_DI){
		if(pGPIOx_Base == GPIOA){
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx_Base == GPIOB){
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx_Base == GPIOC){
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx_Base == GPIOD){
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx_Base == GPIOE){
			GPIOE_PCLK_DI();
		}
		else if(pGPIOx_Base == GPIOH){
			GPIOH_PCLK_DI();
		}
		else{
		}
	}
}


/*
 * GPIO Peripheral - GPIO Initialization API Definition
 */
void GPIOx_Init(GPIOx_Handle_t *pGPIOHandle){
	//Initialize variables
	uint8_t bit_pos = 0;
	uint8_t reg_index = 0;
	uint8_t temp = 0;

	/*Non Interrupt mode configurations*/
	if(pGPIOHandle->GPIO_PinConfig.GPIOx_PinMode <= GPIO_MODE_ANALOG){
		//1. Set GPIO Pin Mode
		bit_pos = pGPIOHandle->GPIO_PinConfig.GPIOx_PinNumber * 2;
		pGPIOHandle->pGPIOx_Base->MODER &= ~(0x3 << bit_pos);		//Clear the Bits
		pGPIOHandle->pGPIOx_Base->MODER |= (pGPIOHandle->GPIO_PinConfig.GPIOx_PinMode << bit_pos);		//Set Bits
		bit_pos = 0;

		//2. Set GPIO Pin Output Type
		if(pGPIOHandle->GPIO_PinConfig.GPIOx_PinMode == GPIO_MODE_OUTPUT){
			bit_pos = pGPIOHandle->GPIO_PinConfig.GPIOx_PinNumber;
			pGPIOHandle->pGPIOx_Base->OTYPER &= ~(0x1 << bit_pos);	//Clear the Bits
			pGPIOHandle->pGPIOx_Base->OTYPER |= (pGPIOHandle->GPIO_PinConfig.GPIOx_PinOPType << bit_pos);	//Set Bits
			bit_pos = 0;
		}

		//3. Set GPIO Pin Speed
		bit_pos = pGPIOHandle->GPIO_PinConfig.GPIOx_PinNumber * 2;
		pGPIOHandle->pGPIOx_Base->OSPEEDR &= ~(0x3 << bit_pos);	//Clear the Bits
		pGPIOHandle->pGPIOx_Base->OSPEEDR |= (pGPIOHandle->GPIO_PinConfig.GPIOx_PinSpeed << bit_pos);	//Set Bits
		bit_pos = 0;

		//4. Set GPIO Pin Pull Up/Down Register
		bit_pos = pGPIOHandle->GPIO_PinConfig.GPIOx_PinNumber * 2;
		pGPIOHandle->pGPIOx_Base->PUPDR &= ~(0x3 << bit_pos);	//Clear the Bits
		pGPIOHandle->pGPIOx_Base->PUPDR |= (pGPIOHandle->GPIO_PinConfig.GPIOx_PinPUPDControl << bit_pos);	//Set Bits
		bit_pos = 0;

		//5. Set GPIO Pin Alternate Functionality Mode
		if(pGPIOHandle->GPIO_PinConfig.GPIOx_PinMode == GPIO_MODE_ALTERNATE){
			//Configure the Alternate functionality registers
			reg_index = (pGPIOHandle->GPIO_PinConfig.GPIOx_PinNumber % 8);
			temp = (pGPIOHandle->GPIO_PinConfig.GPIOx_PinNumber / 8);
			bit_pos = (temp * 4);
			pGPIOHandle->pGPIOx_Base->AFR[reg_index] &= ~(0xf << bit_pos);	//Clear the Bits
			pGPIOHandle->pGPIOx_Base->AFR[reg_index] |= (pGPIOHandle->GPIO_PinConfig.GPIOx_PinAltFunMode << bit_pos);	//Set Bits
		}
	}
	/*Interrupt Mode Enabled configurations*/
	else{
		//Pin Settings + Interrupt mode enable and configurations
	}
}


/*
 * GPIO Peripheral - GPIO De-Initialization API Definition
 */
void GPIOx_DeInit(GPIOx_RegDef_t *pGPIOx_Base){
	if(pGPIOx_Base == GPIOA){
		GPIOA_REG_RESET();
	}
	else if(pGPIOx_Base == GPIOB){
		GPIOB_REG_RESET();
	}
	else if(pGPIOx_Base == GPIOC){
		GPIOC_REG_RESET();
	}
	else if(pGPIOx_Base == GPIOD){
		GPIOD_REG_RESET();
	}
	else if(pGPIOx_Base == GPIOE){
		GPIOE_REG_RESET();
	}
	else if(pGPIOx_Base == GPIOH){
		GPIOH_REG_RESET();
	}
	else{
	}
}


/*
 * GPIO Peripheral - GPIO Read API Definitions
 */
uint8_t GPIO_ReadFromInputPin(GPIOx_RegDef_t *pGPIOx_Base, uint8_t GPIO_Pin){
	uint8_t data;
	data = (uint8_t)(pGPIOx_Base->IDR >> GPIO_Pin) & 0x00000001;
	return data;
}


uint16_t GPIO_ReadFromInputPort(GPIOx_RegDef_t *pGPIOx_Base){
	uint16_t data;
	data = (uint16_t)(pGPIOx_Base->IDR);
	return data;
}


/*
 * GPIO Peripheral - GPIO Write API Definitions
 */
void GPIO_WriteToOutputPin(GPIOx_RegDef_t *pGPIOx_Base, uint8_t GPIO_Pin, uint8_t Value){
	//We write directly to BSSR without using '|=' since BSSR performs atomic writes
	//Also When passing pin numbers like pin 1 or 12, you need to convert them into bitmasks
	uint32_t pin_mask = (1 << GPIO_Pin);
	if(Value == HIGH){
		pGPIOx_Base->BSSR = pin_mask;			//Set Pin high
	}
	else if(Value == LOW){
		pGPIOx_Base->BSSR = (pin_mask << 16);	//Set Pin low
	}
}


void GPIO_WriteToOutputPort(GPIOx_RegDef_t *pGPIOx_Base, uint16_t mask){
	//To write to multiple pins like a port, we can need to directly write to the ODR Register.
	pGPIOx_Base->ODR = mask;
}


/*
 * GPIO Peripheral - GPIO Toggle API Definition
 */
void GPIO_ToggleOutputPin(GPIOx_RegDef_t *pGPIOx_Base, uint8_t GPIO_Pin){
	pGPIOx_Base->ODR ^= (1 << GPIO_Pin);
}

void GPIO_ToggleOutputPort(GPIOx_RegDef_t *pGPIOx_Base, uint16_t mask){
	pGPIOx_Base->ODR ^= mask;
}


