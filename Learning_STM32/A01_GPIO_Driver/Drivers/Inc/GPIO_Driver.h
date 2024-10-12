/*
 * TARGET Board: STM32F411RE
 * GPIO_Driver.h
 *
 *  Created on: Oct 12, 2024
 *      Author: Aryan singh
 */

#ifndef INC_GPIO_DRIVER_H_
#define INC_GPIO_DRIVER_H_

#include "STM32F411xx.h"

/*
 * GPIO IMP MACROS
 */

/*
 * @GPIO_PIN_NUMBERS
 * GPIO Pin Numbers Macros
 */
#define GPIO_PIN_NUMBER_0		0
#define GPIO_PIN_NUMBER_1		1
#define GPIO_PIN_NUMBER_2		2
#define GPIO_PIN_NUMBER_3		3
#define GPIO_PIN_NUMBER_4		4
#define GPIO_PIN_NUMBER_5		5
#define GPIO_PIN_NUMBER_6		6
#define GPIO_PIN_NUMBER_7		7
#define GPIO_PIN_NUMBER_8		8
#define GPIO_PIN_NUMBER_9		9
#define GPIO_PIN_NUMBER_10		10
#define GPIO_PIN_NUMBER_11		11
#define GPIO_PIN_NUMBER_12		12
#define GPIO_PIN_NUMBER_13		13
#define GPIO_PIN_NUMBER_14		14
#define GPIO_PIN_NUMBER_15		15

/*
 * @GPIO_MODES
 * MODER Register Macros
*/
#define GPIO_MODE_INPUT			0
#define GPIO_MODE_OUTPUT		1
#define GPIO_MODE_ALTERNATE		2
#define GPIO_MODE_ANALOG		3

/*
 * @GPIO_OUTPUT_TYPES
 * OTYPER Register MACROS
*/
#define GPIO_OUTPUT_PUSH_PULL	0
#define GPIO_OUTPUT_OPEN_DRAIN	1

/*
 * @GPIO_SPEED_CONFIGS
 * OSPEEDR Register MACROS
*/
#define GPIO_SPEED_LOW			0
#define GPIO_SPEED_MEDIUM		1
#define GPIO_SPEED_FAST			2
#define GPIO_SPEED_HIGH			3

/*
 * @GPIO_PULL_CONFIGS
 * PUPD Register MACROS
*/
#define GPIO_PUPD_NA			0
#define GPIO_PUPD_PULL_UP		1
#define GPIO_PUPD_PULL_DOWN		2

/*
 * @GPIO_ALTERNATE_CONFIGS
 * AFR L/H Register Macros
*/
#define GPIO_AFR_AF0			0
#define GPIO_AFR_AF1			1
#define GPIO_AFR_AF2			2
#define GPIO_AFR_AF3			3
#define GPIO_AFR_AF4			4
#define GPIO_AFR_AF5			5
#define GPIO_AFR_AF6			6
#define GPIO_AFR_AF7			7
#define GPIO_AFR_AF8			8
#define GPIO_AFR_AF9			9
#define GPIO_AFR_AF10			10
#define GPIO_AFR_AF11			11
#define GPIO_AFR_AF12			12
#define GPIO_AFR_AF13			13
#define GPIO_AFR_AF14			14
#define GPIO_AFR_AF15			15



/*
 * GPIOx Pin Configuration Structure
 */
typedef struct{
	uint8_t GPIOx_PinNumber;		/*!< @GPIO_PIN_NUMBERS >*/
	uint8_t GPIOx_PinMode;			/*!< @GPIO_MODES >*/
	uint8_t GPIOx_PinSpeed;			/*!< @GPIO_SPEED_CONFIGS >*/
	uint8_t GPIOx_PinOPType;		/*!< @GPIO_OUTPUT_TYPES >*/
	uint8_t GPIOx_PinPUPDControl;	/*!< @GPIO_PULL_CONFIGS >*/
	uint8_t GPIOx_PinAltFunMode;	/*!< @GPIO_ALTERNATE_CONFIGS >*/
}GPIOx_PinConfig_t;

/*
 * Handle structure for the GPIOx Peripheral
 */
typedef struct{
	GPIOx_RegDef_t *pGPIOx_Base;		/*!< Pointer to hold the base address of the GPIOx Peripheral >*/
	GPIOx_PinConfig_t GPIO_PinConfig;	/*!< Configuration structure for the GPIOx Pin Settings>*/
}GPIOx_Handle_t;

/*
 * GPIO Peripheral - Peripheral Clock Control API
 */
void GPIOx_PClkControl(GPIOx_RegDef_t *pGPIOx_Base, uint8_t EN_DI);

/*
 * GPIO Peripheral - Initialize and De-Initialize APIs
 */
void GPIOx_Init(GPIOx_Handle_t *pGPIOHandle);
void GPIOx_DeInit(GPIOx_RegDef_t *pGPIOx_Base);

/*
 * GPIO Peripheral - Read/Write, and Toggle APIs
 */
uint8_t GPIO_ReadFromInputPin(GPIOx_RegDef_t *pGPIOx_Base, uint8_t GPIO_Pin);
uint16_t GPIO_ReadFromInputPort(GPIOx_RegDef_t *pGPIOx_Base);

void GPIO_WriteToOutputPin(GPIOx_RegDef_t *pGPIOx_Base, uint8_t GPIO_Pin, uint8_t Value);
void GPIO_WriteToOutputPort(GPIOx_RegDef_t *pGPIOx_Base, uint16_t mask);

void GPIO_ToggleOutputPin(GPIOx_RegDef_t *pGPIOx_Base, uint8_t GPIO_Pin);
void GPIO_ToggleOutputPort(GPIOx_RegDef_t *pGPIOx_Base, uint16_t mask);
/*
 * GPIO Peripheral - IRQ Configuration and Handler APIs
 */
void GPIO_IRQConfig(void);
void GPIO_IRQHandler(void);

#endif /* INC_GPIO_DRIVER_H_ */
