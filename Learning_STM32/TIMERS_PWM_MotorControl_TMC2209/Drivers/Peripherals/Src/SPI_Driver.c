/*
 * SPI_Driver.c
 *
 *  Created on: Dec 15, 2024
 *      Author: singh
 */

#ifndef PERIPHERALS_SRC_SPI_DRIVER_C_
#define PERIPHERALS_SRC_SPI_DRIVER_C_

#include <stdint.h>
#include "STM32F411xx.h"
#include "SPI_Driver.h"

/*SPI Clock Control API*/
void SPI_PCLK_Control(SPI_RegDef_t *pSPIx, uint8_t EN_DI){
    if(EN_DI == CLK_EN){
		if(pSPIx == SPI1){
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2){
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3){
			SPI3_PCLK_EN();
		}
		else if(pSPIx == SPI4){
			SPI4_PCLK_EN();
		}
		else if(pSPIx == SPI5){
			SPI5_PCLK_EN();
		}
		else{
		}
	}
	else if(EN_DI == CLK_DI){
		if(pSPIx == SPI1){
			SPI1_PCLK_DI();
		}
		else if(pSPIx == SPI2){
			SPI2_PCLK_DI();
		}
		else if(pSPIx == SPI3){
			SPI3_PCLK_DI();
		}
		else if(pSPIx == SPI4){
			SPI4_PCLK_DI();
		}
		else if(pSPIx == SPI5){
			SPI5_PCLK_DI();
		}
		else{
		}
	}
}

/*SPI Initialize & Deinitialize APIs*/
void SPI_Init(SPIx_Handle_t *pSPIHandle){
    //Configure the SPI CR1 Register
	uint32_t tempreg = 0;

	//Initialize SPI Peripheral clock
	SPI_PCLK_Control(pSPIHandle->pSPIx, CLK_EN);

	//Configure SPI Peripheral
	//1. Configure SPI Device Mode
	tempreg |= pSPIHandle->SPIx_Config.SPI_DEVICE_MODE << SPI_CR1_MSTR_BIT;

	//2. Configure the SPI Bus configuration
	if(pSPIHandle->SPIx_Config.SPI_BUS_CONFIG == SPI_BUS_CONFIG_FULL_DUPLEX){
		//BIDI Mode should be cleared - 2-line Unidirectional data mode selected
		tempreg &= ~(1<<SPI_CR1_BIDI_MODE_BIT);
	} 
	else if(pSPIHandle->SPIx_Config.SPI_BUS_CONFIG == SPI_BUS_CONFIG_HALF_DUPLEX){
		//BIDI Mode should be Set - 1-line bidirectional mode selected
		tempreg |= (1<<SPI_CR1_BIDI_MODE_BIT);
	}
	else if(pSPIHandle->SPIx_Config.SPI_BUS_CONFIG == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
		//BIDI Mode should be cleared - 2-line unidirectional mode selected
		tempreg &= ~(1<<SPI_CR1_BIDI_MODE_BIT);
		//RXONLY Bit also needs to be Set 
		tempreg |= (1<<SPI_CR1_RX_ONLY_BIT);
	}
	else{
		//Error!
	}

	//3. Configure the SPI Clock Speed
	if(pSPIHandle->SPIx_Config.SPI_DEVICE_MODE == SPI_DEVICE_MODE_MASTER){
		//IF configured in master mode, then only set the baud rate
		tempreg |= (pSPIHandle->SPIx_Config.SPI_SCLK_SPEED << SPI_CR1_BR_BIT);
	}

	//4. Configure the SPI Data frame format
	if(pSPIHandle->SPIx_Config.SPI_DFF == SPI_DFF_16BIT){
		//Set DFF to 16bits
		tempreg |= (1 << SPI_CR1_DFF_BIT);
	}
	else{
		//Set DFF to 8 bits (default)
		tempreg &= ~(1 << SPI_CR1_DFF_BIT);	
	}

	//5. Configure CPOL & CPHA
	if(pSPIHandle->SPIx_Config.SPI_CPOL == SPI_CPOL_HIGH){
		//Set: CPOL idle state as HIGH
		tempreg |= (1 << SPI_CR1_CPOL_BIT);	//Set CPOL
	}
	else{
		//Clear: CPOL idle state as LOW
		tempreg &= ~(1 << SPI_CR1_CPOL_BIT);	//Set CPOL
	}
	
	if(pSPIHandle->SPIx_Config.SPI_CPHA == SPI_CPHA_HIGH){
		//Set: CPHA idle state as HIGH
		tempreg |= (1 << SPI_CR1_CPHA_BIT);	//Set CPHA
	}
	else{
		//Clear: CPHA idle state as LOW
		tempreg &= ~(1 << SPI_CR1_CPHA_BIT);	//Set CPHA
	}

	//Configure SPI SSM
	if(pSPIHandle->SPIx_Config.SPI_SSM == SPI_SSM_ENABLED){
		//Set SSM bit == 1
		tempreg |= (1 << SPI_CR1_SSM_BIT);
		//Set SSI bit == 1 , so NSS pin is pulled high
	}
	else{
		tempreg &= ~(1 << SPI_CR1_SSM_BIT);
	}

	//Initialize the SPI Peripheral with all configured settings
	pSPIHandle->pSPIx->SPI_CR1 |= tempreg;
}


void SPI_Deinit(SPI_RegDef_t *pSPIx){
    //SPI Deinitialize function
	//Set bit for reset and then clear bit to completed deinitialization sequence
	if(pSPIx == SPI1){
		SPI1_REG_RESET();
	}
	else if(pSPIx == SPI2){
		SPI2_REG_RESET();
	}
	else if(pSPIx == SPI2){
		SPI3_REG_RESET();
	}
	else if(pSPIx == SPI2){
		SPI4_REG_RESET();
	}
	else if(pSPIx == SPI2){
		SPI5_REG_RESET();
	}
	else{
		//Error! Out of bounds!
	}
}

/*SPI Send & Receive APIs*/

/*
 * Description:
 * This is a blocking SPI Write/Send data function. 
 * 
 * IP Parameters:
 * @param - SPI_RegDef_t *pSPIx --> This is a pointer to the base address of the peripheral that is of type SPI_RegDef_t
 * @param - uint8_t *pTxBuffer  --> This is a pointer to a buffer/data of type unit8_t
 * @param - uint32_t length 	--> This variable holds the length or size of the buffer.
 * 
 * Return:
 * None
*/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t length){
    //1. Check if length is zero? if true, return transmission complete and if false, continue.
	if(length <= 0) return;  // No data to transmit

	uint32_t len = length;	//Created a local variable to store length data.
	while(len > 0){
		//2. Check if Tx buffer is empty? if false, wait and if true, continue.
		while(!(pSPIx->SPI_SR & (1 << SPI_SR_TXE_BIT))); //This checks if the TXE bit in the SPI_SR register is set. If it's set, it means the transmit buffer is empty and ready to accept new data.

		//3. check if Data frame format is 8 bit or 16 bit, and execute accordingly.
		if(pSPIx->SPI_CR1 & (1 << SPI_CR1_DFF_BIT)){
			//DFF is 16 bits format
			//4. load 16 bits of data into SPI DR Register and increment address by 2 byte and de-increment length by 2.
			/*
			 * The typecaste (uint16_t *)pTxBuffer changes the interpretation of pTxBuffer from a pointer to uint8_t type data to a pointer to uint16_t type data.
			 * The "*" dereferences the pointer, accessing the 16 bit data. i.e. *((uint16_t *)pTxBuffer)
			*/
			pSPIx->SPI_DR = *((uint16_t *)pTxBuffer);		//Write 16 bits of data to SPI TX Buffer
			pTxBuffer += 2;									//Increment address by 2 bytes
			len -= 2;										//De-Increment length by 2
		}
		else{
			//DFF is 8 bits format
			//5. load 8 bit data into SPI DR Register and increment address by 1 byte and de-increment length by 1.
			pSPIx->SPI_DR = *pTxBuffer;		//Write 8 buts of data to SPI TX Buffer
			pTxBuffer++;					//Increment address by 1 byte
			len--;							//De-Increment length by 1
		}
	}
}

/*
 * Description:
 * This is a blocking SPI Read/Receive data function. 
 * 
 * IP Parameters:
 * @param - SPI_RegDef_t *pSPIx --> This is a pointer to the base address of the peripheral that is of type SPI_RegDef_t
 * @param - uint8_t *pTxBuffer  --> This is a pointer to a buffer/data of type unit8_t
 * @param - uint32_t length 	--> This variable holds the length or size of the buffer.
 * 
 * Return:
 * None
*/
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t length){
    //1. Check if length is zero? if true, return transmission complete and if false, continue.
	if(length == 0) return;  // No data to Receive

	// Validate length for 16-bit mode
    if ((pSPIx->SPI_CR1 & (1 << SPI_CR1_DFF_BIT)) && (length % 2 != 0)) {
        // Invalid length for 16-bit mode
        return;
    }

	if ((pSPIx->SPI_CR1 & (1 << SPI_CR1_DFF_BIT)) && ((uint32_t)pRxBuffer % 2 != 0)) {
    	// Misaligned buffer for 16-bit mode
    	return;
	}

	uint32_t len = length;	//Created a local variable to store length data.
	while(len > 0){
		//2. Check if Rx buffer is not empty? if false, wait and if true, continue.
		// Wait until RXNE flag is set
		while( !(pSPIx->SPI_SR & (1 << SPI_SR_RXNE_BIT)));

		//3. check if Data frame format is 8 bit or 16 bit, and execute accordingly.
		if(pSPIx->SPI_CR1 & (1 << SPI_CR1_DFF_BIT)){
			//DFF is 16 bits format
			//4. Read 16 bits of data of SPI DR Register and store into pRxBuffer which is typecasted to uint16_t* and increment address by 2 byte and de-increment length by 2.
			/*
			 * The typecaste (uint16_t *)pTxBuffer changes the interpretation of pTxBuffer from a pointer to uint8_t type data to a pointer to uint16_t type data.
			 * The "*" dereferences the pointer, accessing the 16 bit data. i.e. *((uint16_t *)pTxBuffer)
			*/
			*((uint16_t *)pRxBuffer) = pSPIx->SPI_DR;		//Read and store 16 bits of data from SPI DR and stores it into *pRxBuffer
			pRxBuffer += 2;									//Increment address by 2 bytes
			len -= 2;										//De-Increment length by 2
		}
		else{
			//DFF is 8 bits format
			//5. Read 8 bit data from SPI DR Register and store into pRxBuffer and increment address by 1 byte and de-increment length by 1.
			*pRxBuffer = pSPIx->SPI_DR;					//Read 8 bits of data from SPI DR and stores it into *pRxBuffer
			pRxBuffer++;								//Increment address by 1 byte
			len--;										//De-Increment length by 1
		}
	}
}

/*SPI Interrupt APIs*/
void SPI_IRQ_INT_Config(uint8_t IRQNumber, uint8_t EN_DI){
    //
}

void SPI_IRQ_Priority_Config(uint8_t IRQNumber, uint32_t IRQPriority){
    //
}

void SPI_IRQHandling(SPIx_Handle_t *pSPIHandle){
    //
}

/*SPI Low Level APIs - Configuration & Control*/

/*
 * SPI Enable API
 *
 * 
*/
void SPI_Enable(SPI_RegDef_t *pSPIx){
	//Enable the SPE Bit in SPI_CR1 Register
	pSPIx->SPI_CR1 |= (1 << SPI_CR1_SPE_BIT);
}


/*
 * SPI Disable API
 *
 * 
*/
void SPI_Disable_blocking(SPI_RegDef_t *pSPIx){
	//Disable the SPE Bit in SPI_CR1 Register
	while( pSPIx->SPI_SR & (1 << SPI_SR_BSY_BIT) ){
		/*
		 * The code will block here, until the condition is true/valid.
		 * The condition checks weather the BSY Flag in the status register is raised or not.
		 * If it is raised, the condtion is true/valid, and it will wait here, until the condition becomes false.
		 * If the flag is no longer raised, the condition will no longer be true, and will exit the while loop, and
		 * will procced to execute the SPI Peripheral Disable code.\
		 * BSY Flag raised basically means the SPI TX buffer is currently busy in transmission.
		 */
	}
	pSPIx->SPI_CR1 &= ~(1 << SPI_CR1_SPE_BIT);
}


/*
 * SPI SSI Configure API
 *
 * 
*/
void SPI_SSI_Configure(SPI_RegDef_t *pSPIx, uint8_t EN_DI){
	if(EN_DI == ENABLE){
		pSPIx->SPI_CR1 |= (1 << SPI_CR1_SSI_BIT);
		//We are doing this since this is device is not working in multi master mode.
	}
	else{
		pSPIx->SPI_CR1 &= ~(1 << SPI_CR1_SSI_BIT);
		//We are doing this since this is device is working in multi master mode.
	}
}

/*
 * SPI SSOE Configure API
 *
 * 
*/
void SPI_SSOE_Configure(SPI_RegDef_t *pSPIx, uint8_t EN_DI){
	//
	if(EN_DI == ENABLE){
		pSPIx->SPI_CR2 |= (1 << SPI_CR2_SSOE_BIT);
	}
	else{
		pSPIx->SPI_CR2 &= ~(1 << SPI_CR2_SSOE_BIT);
	}
}


//test function

void SPI_FullDuplex_Master(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint8_t *pRxBuffer, uint32_t length){
    while (length > 0) {
        // Wait for TXE flag (Transmit Buffer Empty)
        while (!(pSPIx->SPI_SR & (1 << SPI_SR_TXE_BIT)));

        // Write data to SPI_DR (Transmit Data Register)
        pSPIx->SPI_DR = *pTxBuffer;

		// Wait for RXNE flag (Receive Buffer Not Empty)
        while( !(pSPIx->SPI_SR & (1 << SPI_SR_RXNE_BIT)));

        // Read data from SPI_DR (Receive Data Register)
        *pRxBuffer = pSPIx->SPI_DR;

        // Increment buffer pointers and decrement length
        pTxBuffer++;
        pRxBuffer++;
        length--;
    }

    // Wait for SPI busy flag (BSY) to clear (ensure last transfer is complete)
    while (pSPIx->SPI_SR & (1 << SPI_SR_BSY_BIT));
}

void SPI_FullDuplex_Slave(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, volatile uint8_t *pRxBuffer, uint32_t length){
    while (length > 0) {
        // Wait for RXNE flag (Receive Buffer Not Empty)
        while( !(pSPIx->SPI_SR & (1 << SPI_SR_RXNE_BIT)));

        // Read data from SPI_DR (Receive Data Register)
        *pRxBuffer = pSPIx->SPI_DR;

        // Wait for TXE flag (Transmit Buffer Empty)
        while (!(pSPIx->SPI_SR & (1 << SPI_SR_TXE_BIT)));

        // Write data to SPI_DR (Transmit Data Register)
        pSPIx->SPI_DR = *pTxBuffer;

        // Increment buffer pointers and decrement length
        pTxBuffer++;
        pRxBuffer++;
        length--;
    }

    // Wait for SPI busy flag (BSY) to clear (ensure last transfer is complete)
    while (pSPIx->SPI_SR & (1 << SPI_SR_BSY_BIT));
}


#endif /* PERIPHERALS_SRC_SPI_DRIVER_C_ */
