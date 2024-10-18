/*`1
 * STM32F411xx.h
 *
 *  Created on: Oct 11, 2024
 *      Author: Aryan Singh
 */

#ifndef INC_STM32F411XX_H_
#define INC_STM32F411XX_H_

#include <stdint.h>

/*
 * IMP MACROS
 */

#define __IO			volatile
#define CLK_EN			1
#define CLK_DI			0
#define HIGH			1
#define LOW				0
#define ENABLE			1
#define DISABLE			0


/********************************************* Processor Specific Details *********************************************/
/*
 * ARM Cortex Mx Processor NVIC Registers
 */
/* NVIC ISERx Register Addresses - Interrupt Set-Enable Register */
#define NVIC_ISER0		((__IO uint32_t*)0xE000E100)
#define NVIC_ISER1		((__IO uint32_t*)0xE000E104)
#define NVIC_ISER2		((__IO uint32_t*)0xE000E108)
#define NVIC_ISER3		((__IO uint32_t*)0xE000E10C)
#define NVIC_ISER4		((__IO uint32_t*)0xE000E110)
#define NVIC_ISER5		((__IO uint32_t*)0xE000E114)
#define NVIC_ISER6		((__IO uint32_t*)0xE000E118)
#define NVIC_ISER7		((__IO uint32_t*)0xE000E11C)

/* NVIC ICERx Register Addresses - Interrupt Clear-Enable Register */
#define NVIC_ICER0		((__IO uint32_t*)0xE000E180)
#define NVIC_ICER1		((__IO uint32_t*)0xE000E184)
#define NVIC_ICER2		((__IO uint32_t*)0xE000E188)
#define NVIC_ICER3		((__IO uint32_t*)0xE000E18C)
#define NVIC_ICER4		((__IO uint32_t*)0xE000E190)
#define NVIC_ICER5		((__IO uint32_t*)0xE000E194)
#define NVIC_ICER6		((__IO uint32_t*)0xE000E198)
#define NVIC_ICER7		((__IO uint32_t*)0xE000E19C)


/* NVIC IPRx Register Addresses - Interrupt Priority Register */
/*
 * Note - In ARM Cortex Mx Processor - there 60 IPR Registers i.e. IPR0 - IPR59
 *		  Each IPRx register is splitted into 4 sections, each of 8 bits.
 *		  Each section is for a IRQ Number to configure its priority
 */
#define NVIC_IPRx_BASE	((__IO uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED	4


/**********************************************************************************************************************/

/********************************************** Peripherals specific Details ******************************************/
/*
 * Base Addresses of Flash, ROM and SRAM Memories
 */

#define FLASH_BASE		0x08000000U		/*!< Base Address of Main Memory i.e. Flash Memory >*/
#define SRAM_BASE		0x20000000U		/*!< Base Address of SRAM >*/
#define ROM_BASE		0x1FFF0000U		/*!< Base Address of System Memory i.e. ROM >*/


/*
 * Base Addresses of Bus Domains - AHBx, APBx
 */
#define PERIPH_BASE		0x40020000U		/*!< Base Address of the Pheripheral Bus Domain>*/
#define AHB1_BASE		PERIPH_BASE		/*!< Base Address of the AHB1 Bus Domain >*/
#define AHB2_BASE		0x50000000U		/*!< Base Address of the AHB2 Bus Domain >*/
#define APB1_BASE		0x40000000U		/*!< Base Address of the APB1 Bus Domain >*/
#define APB2_BASE		0x40010000U		/*!< Base Address of the APB2 Bus Domain >*/


/*
 * Base Addresses of AHB1 Peripherals
 */
#define GPIOA_BASE					(AHB1_BASE)				/*!< Base Address of GPIOA Peripheral >*/
#define GPIOB_BASE					(AHB1_BASE + 0x0400)	/*!< Base Address of GPIOB Peripheral >*/
#define GPIOC_BASE					(AHB1_BASE + 0x0800)	/*!< Base Address of GPIOC Peripheral >*/
#define GPIOD_BASE					(AHB1_BASE + 0x0C00)	/*!< Base Address of GPIOD Peripheral >*/
#define GPIOE_BASE					(AHB1_BASE + 0x1000)	/*!< Base Address of GPIOE Peripheral >*/

#define GPIOH_BASE					(AHB1_BASE + 0x1C00)	/*!< Base Address of GPIOH Peripheral >*/

#define CRC_BASE					(AHB1_BASE + 0x3000)	/*!< Base Address of CRC Peripheral >*/

#define RCC_BASE					(AHB1_BASE + 0x3800)	/*!< Base Address of RCC Peripheral >*/
#define FLASH_INTERFACE_REGISTER	(AHB1_BASE + 0x3C00)	/*!< Base Address of Flash Interface Register Peripheral >*/

#define DMA_BASE					(AHB1_BASE + 0x6000)	/*!< DMA Peripheral Base Address >*/
#define DMA1_BASE					(DMA_BASE)				/*!< DMA 1 Peripheral Base Address >*/
#define DMA2_BASE					(DMA_BASE + 0x0400)		/*!< DMA 2 Peripheral Base Address>*/


/*
 * Base Addresses of AHB2 Peripherals
 */
#define USB_OTG_FS_BASE				(AHB2_BASE)				/*!< USB OTG FS Peripheral Base Address >*/


/*
 * Base Addresses of APB1 Peripherals
 */
#define TIM2_BASE					(APB1_BASE)				/*!< TIMER 2 Peripheral Base Address >*/
#define TIM3_BASE					(APB1_BASE + 0x0400)	/*!< TIMER 3 Peripheral Base Address >*/
#define TIM4_BASE					(APB1_BASE + 0x0800)	/*!< TIMER 4 Peripheral Base Address >*/
#define TIM5_BASE					(APB1_BASE + 0x0C00)	/*!< TIMER 5 Peripheral Base Address >*/

#define RTC_BKP_BASE				(APB1_BASE + 0x2800)	/*!< RTC Peripheral Base Address >*/
#define WWDG_BASE					(APB1_BASE + 0x2C00)	/*!< Window Watchdog Timer Peripheral Base Address >*/
#define IWDG_BASE					(APB1_BASE + 0x3000)	/*!< Independent Watchdog Timer Peripheral Base Address >*/
#define I2S2_EXT_BASE				(APB1_BASE + 0x3400)	/*!< I2S 2 EXT Peripheral Base Address >*/
#define SPI2_BASE					(APB1_BASE + 0x3800)	/*!< SPI 2 Peripheral Base Address >*/
#define SPI3_BASE					(APB1_BASE + 0x3C00)	/*!< SPI 3 Peripheral Base Address >*/
#define I2S2_BASE					(SPI2_BASE)				/*!< I2S 2 Peripheral Base Address >*/
#define I2S3_BASE					(SPI3_BASE)				/*!< I2S 3 Peripheral Base Address >*/
#define I2S3_EXT_BASE				(APB1_BASE + 0x4000)	/*!< I2S3 Ext Peripheral Base Address >*/
#define USART2_BASE					(APB1_BASE + 0x4400)	/*!< USART 2 Peripheral Base Address >*/

#define I2C1_BASE					(APB1_BASE + 0x5400)	/*!< I2C 1 Peripheral Base Address >*/
#define I2C2_BASE					(APB1_BASE + 0x5800)	/*!< I2C 2 Peripheral Base Address >*/
#define I2C3_BASE					(APB1_BASE + 0x5C00)	/*!< I2C 3 Peripheral Base Address >*/

#define PWR_BASE					(APB1_BASE + 0x7000)	/*!< POWER Peripheral Base Address >*/

/*
 * Base Addresses of APB2 Peripherals
 */
#define TIM1_BASE					(APB2_BASE + 0x0000)	/*!< TIMER 1 Peripheral Base Address >*/
#define USART1_BASE					(APB2_BASE + 0x1000)	/*!< USART 1 Peripheral Base Address >*/
#define USART6_BASE					(APB2_BASE + 0x1400)	/*!< USART 6 Peripheral Base Address >*/

#define ADC1_BASE					(APB2_BASE + 0x2000)	/*!< ADC 1 Peripheral Base Address >*/

#define	SDIO_BASE					(APB2_BASE + 0x2C00)	/*!< SDIO Peripheral Base Address >*/
#define SPI1_BASE					(APB2_BASE + 0x3000)	/*!< SPI 1 Peripheral Base Address >*/
#define SPI4_BASE					(APB2_BASE + 0x3400)	/*!< SPI 4 Peripheral Base Address >*/
#define I2S1_BASE					(SPI1_BASE)				/*!< I2S 1 Peripheral Base Address >*/
#define I2S4_BASE					(SPI4_BASE)				/*!< I2S 4 Peripheral Base Address >*/
#define	SYSCFG_BASE					(APB2_BASE + 0x3800)	/*!< SYSCFG Peripheral Base Address >*/
#define EXTI_BASE					(APB2_BASE + 0x3C00)	/*!< EXTI Controller Peripheral Base Address >*/
#define TIM9_BASE					(APB2_BASE + 0x4000)	/*!< TIMER 9 Peripheral Base Address >*/
#define TIM10_BASE					(APB2_BASE + 0x4400)	/*!< TIMER 10 Peripheral Base Address >*/
#define TIM11_BASE					(APB2_BASE + 0x4800)	/*!< TIMER 11 Peripheral Base Address >*/
#define SPI5_BASE					(APB2_BASE + 0x5000)	/*!< SPI 5 Peripheral Base Address >*/
#define I2S5_BASE					(SPI5_BASE)				/*!< I2S5 Peripheral Base Address >*/

/*
 * IRQ Number Definitions
 */

#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40


/*
 * IRQ Priority Number
 */
#define NVIC_IRQ_PRI_0		0
#define NVIC_IRQ_PRI_1		1
#define NVIC_IRQ_PRI_2		2
#define NVIC_IRQ_PRI_3		3
#define NVIC_IRQ_PRI_4		4
#define NVIC_IRQ_PRI_5		5
#define NVIC_IRQ_PRI_6		6
#define NVIC_IRQ_PRI_7		7
#define NVIC_IRQ_PRI_8		8
#define NVIC_IRQ_PRI_9		9
#define NVIC_IRQ_PRI_10		10
#define NVIC_IRQ_PRI_11		11
#define NVIC_IRQ_PRI_12		12
#define NVIC_IRQ_PRI_13		13
#define NVIC_IRQ_PRI_14		14
#define NVIC_IRQ_PRI_15		15

/******************************************************************************************************************************/
/*
 * Peripheral Registers - Structures Definitions
 */
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/*
 * Peripheral register definition structure for RCC
 */
typedef struct{
	__IO uint32_t CR;				/*>! RCC clock control register										ADDRESS OFFSET:0x00 		*/
	__IO uint32_t PLLCFGR;			/*>! RCC PLL configuration register									ADDRESS OFFSET:0x04 		*/
	__IO uint32_t CFGR;				/*>! RCC clock configuration register 								ADDRESS OFFSET:0x08 		*/
	__IO uint32_t CIR;				/*>! RCC clock interrupt register									ADDRESS OFFSET:0x0C 		*/
	__IO uint32_t AHB1RSTR;			/*>! RCC AHB1 peripheral reset register 							ADDRESS OFFSET:0x10 		*/
	__IO uint32_t AHB2RSTR;			/*>! RCC AHB2 peripheral reset register								ADDRESS OFFSET:0x14 		*/
	__IO uint32_t RESERVED_0[2];	/*>! RESERVED														ADDRESS OFFSET:0x18 & 0x1C 	*/
	__IO uint32_t APB1RSTR;			/*>! RCC APB1 peripheral reset register								ADDRESS OFFSET:0x20 		*/
	__IO uint32_t APB2RSTR;			/*>! RCC APB2 peripheral reset register 							ADDRESS OFFSET:0x24 		*/
	__IO uint32_t RESERVED_1[2];	/*>! RESERVED														ADDRESS OFFSET:0x28 & 0x2C 	*/
	__IO uint32_t AHB1ENR;			/*>! RCC AHB1 peripheral clock enable register						ADDRESS OFFSET:0x30 		*/
	__IO uint32_t AHB2ENR;			/*>! RCC AHB2 peripheral clock enable register 						ADDRESS OFFSET:0x34 		*/
	__IO uint32_t RESERVED_2[2];	/*>! RESERVED														ADDRESS OFFSET:0x38 & 0x3C	*/
	__IO uint32_t APB1ENR;			/*>! RCC APB1 peripheral clock enable register 						ADDRESS OFFSET:0x40 		*/
	__IO uint32_t APB2ENR;			/*>! RCC APB2 peripheral clock enable register						ADDRESS OFFSET:0x44 		*/
	__IO uint32_t RESERVED_3[2];	/*>! RESERVED														ADDRESS OFFSET:0x48 & 0x4C	*/
	__IO uint32_t AHB1LPENR;		/*>! RCC AHB1 peripheral clock enable in low power mode register	ADDRESS OFFSET:0x50 		*/
	__IO uint32_t AHB2LPENR;		/*>! RCC AHB2 peripheral clock enable in low power mode register	ADDRESS OFFSET:0x54 		*/
	__IO uint32_t RESERVED_4[2];	/*>! RESERVED														ADDRESS OFFSET:0x58 & 0x5C	*/
	__IO uint32_t APB1LPENR;		/*>! RCC APB1 peripheral clock enable in low power mode register	ADDRESS OFFSET:0x60 		*/
	__IO uint32_t APB2LPENR;		/*>! RCC APB2 peripheral clock enable in low power mode register	ADDRESS OFFSET:0x64 		*/
	__IO uint32_t RESERVED_5[2];	/*>! RESERVED														ADDRESS OFFSET:0x68 & 0x6C	*/
	__IO uint32_t BDCR;				/*>! RCC Backup domain control register								ADDRESS OFFSET:0x70 		*/
	__IO uint32_t CSR;				/*>! RCC clock control & status register 							ADDRESS OFFSET:0x74 		*/
	__IO uint32_t RESERVED_6[2];	/*>! RESERVED														ADDRESS OFFSET:0x78 & 0x7C	*/
	__IO uint32_t SSCGR;			/*>! RCC spread spectrum clock generation register 					ADDRESS OFFSET:0x80 		*/
	__IO uint32_t PLLI2SCFGR;		/*>! RCC PLLI2S configuration register 								ADDRESS OFFSET:0x84 		*/
	__IO uint32_t RESERVED_7;		/*>! RESERVED														ADDRESS OFFSET:0x88 		*/
	__IO uint32_t DCKCFGR;			/*>! RCC Dedicated Clocks Configuration Register					ADDRESS OFFSET:0x8C 		*/
}RCC_RegDef_t;

/*
 * This Macros is defines RCC as a RCC Base Memory address which is pinter casted to type RCC_RegDef_t.
 */
#define RCC			((RCC_RegDef_t *)RCC_BASE)

/*
 * Macros to enable clock access to GPIO Peripherals
 */
#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1<<4))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1<<7))

/*
 * Macros to disable clock access to peripheral
 */
#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<4))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<7))

/*
 * Reset Macros for GPIO Peripherals
 */
#define GPIOA_REG_RESET()		do{ (RCC->AHB1RSTR |= (1<<0));  (RCC->AHB1RSTR &= ~(1<<0)); }while(0)	/*!< First set bits then clear bits! >*/
#define GPIOB_REG_RESET()		do{ (RCC->AHB1RSTR |= (1<<1));	(RCC->AHB1RSTR &= ~(1<<1)); }while(0)	/*!< First set bits then clear bits! >*/
#define GPIOC_REG_RESET()		do{ (RCC->AHB1RSTR |= (1<<2));	(RCC->AHB1RSTR &= ~(1<<2)); }while(0)	/*!< First set bits then clear bits! >*/
#define GPIOD_REG_RESET()		do{ (RCC->AHB1RSTR |= (1<<3));	(RCC->AHB1RSTR &= ~(1<<3)); }while(0)	/*!< First set bits then clear bits! >*/
#define GPIOE_REG_RESET()		do{ (RCC->AHB1RSTR |= (1<<4));	(RCC->AHB1RSTR &= ~(1<<4)); }while(0)	/*!< First set bits then clear bits! >*/
#define GPIOH_REG_RESET()		do{ (RCC->AHB1RSTR |= (1<<7));	(RCC->AHB1RSTR &= ~(1<<7)); }while(0)	/*!< First set bits then clear bits! >*/

/*
 * Macros to enable clock access to SYSCFG Peripheral
 */
#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= (1<<14))
#define SYSCFG_PCLK_DI()	(RCC->APB2ENR &= ~(1<<14))


/*---------------------------------------------------------------------------------------------------------------------------------------*/
/*
 * GPIO Peripheral Register structure
 *
 * GPIO_RegDef_t represents the registers of the GPIO Peripheral.
 * These registers are mapped to specific memory locations, and
 * Each field in the structure corresponds to a particular hardware register that controls the GPIO.
 *
 * The structure GPIO_RegDef_t is a blueprint of the memory layout of the GPIO peripheral’s registers.
 *
 */
typedef struct{
	__IO uint32_t MODER;		/*<! GPIO port mode register						ADDRESS OFFSET: 0x00	*/
	__IO uint32_t OTYPER;		/*<! GPIO port output type register					ADDRESS OFFSET: 0x04	*/
	__IO uint32_t OSPEEDR;		/*<! GPIO port output speed register				ADDRESS OFFSET: 0x08	*/
	__IO uint32_t PUPDR;		/*<! GPIO port pull-up/pull-down register 			ADDRESS OFFSET: 0x0C	*/
	__IO uint32_t IDR;			/*<! GPIO port input data register					ADDRESS OFFSET: 0x10	*/
	__IO uint32_t ODR;			/*<! GPIO port output data register 				ADDRESS OFFSET: 0x14	*/
	__IO uint32_t BSSR;			/*<! GPIO port bit set/reset register 				ADDRESS OFFSET: 0x18	*/
	__IO uint32_t LCKR;			/*<! GPIO port configuration lock register 			ADDRESS OFFSET: 0x1C	*/
	__IO uint32_t AFR[2];		/*<! AF[0]: GPIO alternate function low register	ADDRESS OFFSET: 0x20	*/
								/*<! AF[1]: GPIO alternate function high register	ADDRESS OFFSET: 0x24	*/
}GPIOx_RegDef_t;

/*
 * GPIO Peripheral Specific Macros
 * This MACRO defines GPIOX (x=A,B,C,D,E,H) as a pointer to a GPIO_RegDef_t structure that is cast to a the base address of GPIOX
 * GPIOX_BASE is a predefined macro that holds the base memory address of GPIOX Peripheral.
 * ((GPIO_RegDef_t *)GPIOX_BASE) - This casts the base address 'GPIOX_BASE' into a pointer of type GPIO_RegDef_t structure.
 * This allows the code to access the registers of GPIO A directly using structure syntax
 *
 * The macro GPIOA is a pointer to the memory address of GPIO port A, cast to the GPIO_RegDef_t type, allowing the code to access and
 * modify GPIO registers through a simple interface like GPIOA->MODER.
 */
#define GPIOA		((GPIOx_RegDef_t *)GPIOA_BASE)	/*!< GPIOA Peripheral Base Address is Type-casted to a pointer of type GPIO_RegDef_t >*/
#define GPIOB		((GPIOx_RegDef_t *)GPIOB_BASE)
#define GPIOC		((GPIOx_RegDef_t *)GPIOC_BASE)
#define GPIOD		((GPIOx_RegDef_t *)GPIOD_BASE)
#define GPIOE		((GPIOx_RegDef_t *)GPIOE_BASE)
#define GPIOH		((GPIOx_RegDef_t *)GPIOH_BASE)


/*--------------------------------------------------------------------------------------------------------------------------------------*/
/*
 * Peripheral register definition structure for EXTI Controller
 */

typedef struct{
	__IO uint32_t EXTI_IMR;		/*!< EXTI Interrupt Mask Register >*/
	__IO uint32_t EXTI_EMR;		/*!< EXTI Event Mask Register >*/
	__IO uint32_t EXTI_RTSR;	/*!< EXTI Rising Trigger Selection Register >*/
	__IO uint32_t EXTI_FTSR;	/*!< EXTI Falling Trigger Selection Register >*/
	__IO uint32_t EXTI_SWIER;	/*!< EXTI Software Interrupt Event Register >*/
	__IO uint32_t EXTI_PR;		/*!< EXTI Pending Register >*/
}EXTI_RegDef_t;


#define EXTI	((EXTI_RegDef_t *)EXTI_BASE)


/*--------------------------------------------------------------------------------------------------------------------------------------*/
/*
 * Peripheral register definition structure for SYSCFG Peripheral
 */

typedef struct{
	__IO uint32_t MEMRMP;
	__IO uint32_t PMC;
	__IO uint32_t EXTICR[4];
	__IO uint32_t RESERVED2[2];
	__IO uint32_t CMPCR;
}SYSCFG_RegDef_t;

#define SYSCFG	((SYSCFG_RegDef_t *)SYSCFG_BASE)

#define GPIO_BASEADDR_TO_CODE(x)   ((x==GPIOA) ? 0 :\
									(x==GPIOB) ? 1 :\
									(x==GPIOC) ? 2 :\
									(x==GPIOD) ? 3 :\
									(x==GPIOE) ? 4 :\
									(x==GPIOH) ? 7 :0)

/*--------------------------------------------------------------------------------------------------------------------------------------*/
/*
 * Peripheral register definition structure for --- Peripheral
 */




#endif /* INC_STM32F411XX_H_ */
