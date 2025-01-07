/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "STM32F411xx.h"
#include "GPIO_Driver.h"
#include "GPTimer_Driver.h"
#include "SPI_Driver.h"
#include "SYSTICK_Driver.h"
#include "NVIC.h"


#define SYSTEM_FREQUENCY	16000000
#define TIMER_FREQUENCY		1000

#define BUFFER_SIZE		12


//Test function
// void GPIO_Init(GPIOx_Handle_t *pGPIOxHandle);

/*
 * Exercise - Test the SPI_SendData API to send the string "hello world" and use the below configuration
 * 1. SPI2 in Master mode
 * 2. SCLK - max possible
 * 3. DFF = 0 & DFF = 1
*/

/*
 * Pinouts documented for SPI2 Peripheral being used
 * MOSI -> PB15 - CN10 : 26
 * MISO -> PB14 - CN10 : 28
 * SCK --> PB13 - CN10 : 30
 * NSS --> PB12 - CN10 : 16
*/

volatile uint8_t transmit_flag = 0;

//This configures the SPI GPIO Pins
void SPI2_GPIOInit(void);

//This configures the SPI device as master or slave
void SPI2_Init_Master(void);

//This is an application test API for Transmit operations
void SPI_TX_TEST(char *data);

//This is an application test API for Receive operations
void SPI_RX_TEST(char *data);

void BUTTON_GPIO_INIT(void);

//extern void initialise_monitor_handles(void);

typedef struct{
	int a;
	int b;
	int c;
}data_t;


int main(void)
{
	/* functions to run for OpenOCD Debugging */
	//initialise_monitor_handles();

	/*------------------------------------------*/
	//Create a buffer
	//char user_data[BUFFER_SIZE] = "Hello World";		//master mode
	data_t data_list = {15,30,60};

	/* Creating an 12 bit RX buffer */
	//char rx_buffer[BUFFER_SIZE] = {0};  // Initialize with zeros
	data_t data_rx_list = {0};

	printf("SWV printf Debugging Initialized\n");

	//Configure & Initialize SPI2 Peripheral
	SPI2_GPIOInit();

	SPI2_Init_Master();		//for master mode

	TIMx_Delay_ms_Init(TIM2);

	BUTTON_GPIO_INIT(); //Commented when device is in slave mode
	
	/* Loop forever */
	/*Master flag loop code*/
	for(;;){
		while(transmit_flag == 1){
			transmit_flag = 0;
			//memset(&rx_buffer, 0, BUFFER_SIZE);
			//SPI_TX_TEST(user_data);
			SPI_SSOE_Configure(SPI2, ENABLE);
			SPI_Enable(SPI2);

			SPI_FullDuplex_Master(SPI2, (uint8_t *)&data_list, (uint8_t *)&data_rx_list, sizeof(data_t));

			printf("USER Data sent! Through SPI Interface!!\n");
			printf("Data received: %d\n", data_rx_list.a);
			printf("Data received: %d\n", data_rx_list.b);
			printf("Data received: %d\n", data_rx_list.c);

			SPI_Disable_blocking(SPI2);
		}
		TIMx_Delay_ms(TIM2, 100);	//100ms
	}
}



void SPI2_GPIOInit(void){
	//Create a GPIO Handle and perform configure
	GPIOx_Handle_t SPIPins;

	SPIPins.pGPIOx_Base = GPIOB;
	SPIPins.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_ALTERNATE;
	SPIPins.GPIO_PinConfig.GPIOx_PinAltFunMode = GPIO_AFR_AF5;
	SPIPins.GPIO_PinConfig.GPIOx_PinOPType = GPIO_OUTPUT_PUSH_PULL;
	SPIPins.GPIO_PinConfig.GPIOx_PinSpeed = GPIO_SPEED_HIGH;
	SPIPins.GPIO_PinConfig.GPIOx_PinPUPDControl = GPIO_PUPD_PULL_UP;

	//Initialize MOSI Pin
	SPIPins.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_15;
	GPIOx_Init(&SPIPins);

	//Initialize MISO Pin
	SPIPins.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_14;
	GPIOx_Init(&SPIPins);

	//Initialize SCK
	SPIPins.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_13;
	GPIOx_Init(&SPIPins);

	//Initialize NSS
	SPIPins.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_12;

	//SPI Pins configured!
	GPIOx_Init(&SPIPins);
}


void SPI2_Init(void){
	//Configure and Initialize SPI2 peripheral
	SPIx_Handle_t SPI2_Handle;

	SPI2_Handle.pSPIx = SPI2;
	SPI2_Handle.SPIx_Config.SPI_DEVICE_MODE = SPI_DEVICE_MODE_MASTER;
	SPI2_Handle.SPIx_Config.SPI_BUS_CONFIG = SPI_BUS_CONFIG_FULL_DUPLEX;
	SPI2_Handle.SPIx_Config.SPI_SCLK_SPEED = SPI_BAUDRATE_DIV8;
	SPI2_Handle.SPIx_Config.SPI_DFF = SPI_DFF_8BIT;

	//Configure to Mode 0
	SPI2_Handle.SPIx_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2_Handle.SPIx_Config.SPI_CPHA = SPI_CPHA_LOW;

	//Enable Software Slave management for NSS
	//SPI2_Handle.SPIx_Config.SPI_SSM = SPI_SSM_ENABLED;
	//if Hardware slave management is enabled
	SPI2_Handle.SPIx_Config.SPI_SSM = SPI_SSM_DISABLED;

	//Initialize SPI2 Peripheral
	SPI_Init(&SPI2_Handle);
}

void SPI2_Init_Master(void){
	//Configure and Initialize SPI2 peripheral
	SPIx_Handle_t SPI2_Handle;
	memset(&SPI2_Handle, 0, sizeof(SPIx_Handle_t));	//clear the handle before performing the operations on it.

	SPI2_Handle.pSPIx = SPI2;
	SPI2_Handle.SPIx_Config.SPI_DEVICE_MODE = SPI_DEVICE_MODE_MASTER;
	SPI2_Handle.SPIx_Config.SPI_BUS_CONFIG = SPI_BUS_CONFIG_FULL_DUPLEX;
	SPI2_Handle.SPIx_Config.SPI_SCLK_SPEED = SPI_BAUDRATE_DIV8;
	SPI2_Handle.SPIx_Config.SPI_DFF = SPI_DFF_8BIT;

	//Configure to Mode 0
	SPI2_Handle.SPIx_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2_Handle.SPIx_Config.SPI_CPHA = SPI_CPHA_LOW;

	//Enable Software Slave management for NSS
	// SPI2_Handle.SPIx_Config.SPI_SSM = SPI_SSM_ENABLED;
	SPI2_Handle.SPIx_Config.SPI_SSM = SPI_SSM_DISABLED;		//Hardware Slave management enabled
	
	//Initialize SPI2 Peripheral
	SPI_Init(&SPI2_Handle);
}

void SPI2_Init_Slave(void){
	//Configure and Initialize SPI2 peripheral
	SPIx_Handle_t SPI2_Handle;
	memset(&SPI2_Handle, 0, sizeof(SPIx_Handle_t));	//clear the handle before performing the operations on it.

	SPI2_Handle.pSPIx = SPI2;
	SPI2_Handle.SPIx_Config.SPI_DEVICE_MODE = SPI_DEVICE_MODE_SLAVE;
	SPI2_Handle.SPIx_Config.SPI_BUS_CONFIG = SPI_BUS_CONFIG_FULL_DUPLEX;
	//SPI2_Handle.SPIx_Config.SPI_SCLK_SPEED = SPI_BAUDRATE_DIV8;
	SPI2_Handle.SPIx_Config.SPI_DFF = SPI_DFF_8BIT;

	//Configure to Mode 0
	SPI2_Handle.SPIx_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2_Handle.SPIx_Config.SPI_CPHA = SPI_CPHA_LOW;

	//Enable Software Slave management for NSS
	// SPI2_Handle.SPIx_Config.SPI_SSM = SPI_SSM_ENABLED;
	SPI2_Handle.SPIx_Config.SPI_SSM = SPI_SSM_DISABLED;		//Hardware Slave management enabled
	
	//Initialize SPI2 Peripheral
	SPI_Init(&SPI2_Handle);
}


void SPI_TX_TEST(char *data){
	//Configure SSI Bit
	//SPI_SSI_Configure(SPI2, ENABLE);
	//or
	/*
	 * If Hardware slave mangement is enabled, then making SSOE bit 1 will make NSS Output Enable.
	 * The NSS Pin is automatically managed by the hardware i.e. when SPE = 1, NSS will be pulled to low.
	 * and NSS Pin will be high when SPE = 0
	*/
	SPI_SSOE_Configure(SPI2, ENABLE);

	//Enable the SPI2 Peripheral
	SPI_Enable(SPI2);

	//Test SPI Send data API
	SPI_SendData(SPI2, (uint8_t *)data, BUFFER_SIZE);

	//After transmission, we close or disable the SPI Peripheral
	//Disable the SPI2 Peripheral
	SPI_Disable_blocking(SPI2);
}

void SPI_RX_TEST(char *data){
	SPI_ReceiveData(SPI2, (uint8_t *)data, BUFFER_SIZE);
	printf("RX Buffer is: %s\n", data);
	memset(&data, 0, sizeof(BUFFER_SIZE));
}


void BUTTON_GPIO_INIT(void){
	//Create handle
	GPIOx_Handle_t GPIOHandle;
	memset(&GPIOHandle, 0, sizeof(GPIOHandle));	//Clear
	GPIOHandle.pGPIOx_Base = GPIOA;
	GPIOHandle.GPIO_PinConfig.GPIOx_PinNumber = GPIO_PIN_0;
	GPIOHandle.GPIO_PinConfig.GPIOx_PinMode = GPIO_MODE_INT_FALLING; //GPIO_MODE_INPUT;
	GPIOHandle.GPIO_PinConfig.GPIOx_PinPUPDControl = GPIO_PUPD_PULL_UP;
	//Initialize
	GPIOx_Init(&GPIOHandle);
	GPIO_SetPullUpDown(GPIOA, GPIO_PIN_0, GPIO_PUPD_PULL_UP);

	//IRQ Configurations
	GPIO_IRQ_INT_Config(IRQ_NO_EXTI0, ENABLE);
	GPIO_IRQ_Priority_Config(IRQ_NO_EXTI0, NVIC_IRQ_PRI_15);	//Priority no - 15
}

void EXTI0_IRQHandler(){
	//Handle debouncing
	//for(int i=0; i < 50000; i++);

	//Clear the Interrupt
	GPIO_IRQHandling(GPIO_PIN_0);

	//Raise Flag
	transmit_flag = 1;
}


//Test function to test new APIs created
// void GPIO_Init(GPIOx_Handle_t *pGPIOxHandle){
// 	//Test
// 	uint8_t pin = pGPIOxHandle->GPIO_PinConfig.GPIOx_PinNumber;
// 	uint8_t mode = pGPIOxHandle->GPIO_PinConfig.GPIOx_PinMode;
// 	uint8_t speed = pGPIOxHandle->GPIO_PinConfig.GPIOx_PinSpeed;
// 	uint8_t OPType = pGPIOxHandle->GPIO_PinConfig.GPIOx_PinOPType;
// 	uint8_t PUPDConfig = pGPIOxHandle->GPIO_PinConfig.GPIOx_PinPUPDControl;
// 	// uint8_t Altfun_Mode = pGPIOxHandle->GPIO_PinConfig.GPIOx_PinAltFunMode;

// 	//Enable Clock access for the peripheral
// //	GPIOx_PClkControl(GPIOA, CLK_EN);

// 	//1. Set GPIO pin mode
// 	GPIO_SetMode(pGPIOxHandle->pGPIOx_Base, pin, mode);

// 	//2. Set GPIO pin output type
// 	GPIO_SetOutputType(pGPIOxHandle->pGPIOx_Base, pin, OPType);

// 	//3. Set GPIO pin output speed
// 	GPIO_SetOutputSpeed(pGPIOxHandle->pGPIOx_Base, pin, speed);

// 	//4. Set GPIO pin pull up/down config
// 	GPIO_SetPullUpDown(pGPIOxHandle->pGPIOx_Base, pin, PUPDConfig);
// }