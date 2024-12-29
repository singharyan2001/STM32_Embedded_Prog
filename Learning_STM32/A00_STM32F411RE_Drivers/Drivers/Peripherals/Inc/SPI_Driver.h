/*
 * SPI_Driver.h
 *
 *  Created on: Dec 15, 2024
 *      Author: singh
 */

#ifndef PERIPHERALS_INC_SPI_DRIVER_H_
#define PERIPHERALS_INC_SPI_DRIVER_H_

#include "STM32F411xx.h"

/*
 * SPI related general Macros
*/

/*SPI Device Mode Macros*/
#define SPI_DEVICE_MODE_SLAVE       0
#define SPI_DEVICE_MODE_MASTER      1

/*SPI Bus Configuration Macros*/
#define SPI_BUS_CONFIG_FULL_DUPLEX          1
#define SPI_BUS_CONFIG_HALF_DUPLEX          2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY       3

/*SPI Clock Speed Macros*/
#define SPI_BAUDRATE_DIV2           0
#define SPI_BAUDRATE_DIV4           1
#define SPI_BAUDRATE_DIV8           2
#define SPI_BAUDRATE_DIV16          3
#define SPI_BAUDRATE_DIV32          4
#define SPI_BAUDRATE_DIV64          5
#define SPI_BAUDRATE_DIV128         6
#define SPI_BAUDRATE_DIV256         7

/*SPI Data Frame Format Macros*/
#define SPI_DFF_8BIT                0
#define SPI_DFF_16BIT               1

/*SPI CPOL Macros*/
#define SPI_CPOL_LOW                0
#define SPI_CPOL_HIGH               1

/*SPI CPHA Macros*/
#define SPI_CPHA_LOW                0
#define SPI_CPHA_HIGH               1

/*SPI Software Slave Management Macros*/
#define SPI_SSM_DISABLED            0
#define SPI_SSM_ENABLED             1


/*SPI Register bit Macros*/
//SPI CR1 Register
#define SPI_CR1_CPHA_BIT            0
#define SPI_CR1_CPOL_BIT            1
#define SPI_CR1_MSTR_BIT            2
#define SPI_CR1_BR_BIT              3
#define SPI_CR1_SPE_BIT             6
#define SPI_CR1_LSB_FIRST_BIT       7
#define SPI_CR1_SSI_BIT             8
#define SPI_CR1_SSM_BIT             9
#define SPI_CR1_RX_ONLY_BIT         10
#define SPI_CR1_DFF_BIT             11
#define SPI_CR1_CRC_NEXT_BIT        12
#define SPI_CR1_CRC_EN_BIT          13
#define SPI_CR1_BIDI_OE_BIT         14
#define SPI_CR1_BIDI_MODE_BIT       15


//SPI CR2 Register
#define SPI_CR2_RXDMA_EN_BIT        0
#define SPI_CR2_TXDMA_EN_BIT        1
#define SPI_CR2_SSOE_BIT            2
#define SPI_CR2_FRF_BIT             4
#define SPI_CR2_ERRIE_BIT           5
#define SPI_CR2_RXNEIE_BIT          6
#define SPI_CR2_TXEIE_BIT           7


//SPI STATUS Register
#define SPI_SR_RXNE_BIT             0
#define SPI_SR_TXE_BIT              1
#define SPI_SR_CHSIDE_BIT           2
#define SPI_SR_UDR_BIT              3
#define SPI_SR_CRC_ERR_BIT          4
#define SPI_SR_MODF_BIT             5
#define SPI_SR_OVR_BIT              6
#define SPI_SR_BSY_BIT              7
#define SPI_SR_FRE_BIT              8


typedef struct{
    //SPI Configuration structure
    uint8_t SPI_DEVICE_MODE;            /*!< SPI Device Mode - Master or Slave */
    uint8_t SPI_BUS_CONFIG;             /*!< SPI Bus configuration */
    uint8_t SPI_SCLK_SPEED;             /*!< SPI Clock speed */
    uint8_t SPI_DFF;                    /*!< SPI Data frame format */
    uint8_t SPI_CPOL;                   /*!< SPI Clock Polarity */
    uint8_t SPI_CPHA;                   /*!< SPI Clock Phase */
    uint8_t SPI_SSM;                    /*!< SPI Software slave management */
}SPIx_Config_t;


typedef struct{
    //SPI Handle Structure
    SPI_RegDef_t *pSPIx;            /*!< This field holds the base address of the selected SPIx (x:1,2,3,4,5) Peripheral*/
    SPIx_Config_t SPIx_Config;
}SPIx_Handle_t;

/*SPI Clock Control API*/
void SPI_PCLK_Control(SPI_RegDef_t *pSPIx, uint8_t EN_DI);

/*SPI Initialize & Deinitialize APIs*/
void SPI_Init(SPIx_Handle_t *pSPIHandle);
void SPI_Deinit(SPI_RegDef_t *pSPIx);

/*Enable & Disable SPI Peripheral API*/
void SPI_Enable(SPI_RegDef_t *pSPIx);
void SPI_Disable_blocking(SPI_RegDef_t *pSPIx);

/*SPI SSI Configure API*/
void SPI_SSI_Configure(SPI_RegDef_t *pSPIx, uint8_t EN_DI);

/*SPI SSOE Configure API*/
void SPI_SSOE_Configure(SPI_RegDef_t *pSPIx, uint8_t EN_DI);


/*SPI Send & Receive APIs*/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t length);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t length);

/*SPI Interrupt APIs*/
void SPI_IRQ_INT_Config(uint8_t IRQNumber, uint8_t EN_DI);
void SPI_IRQ_Priority_Config(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPIx_Handle_t *pSPIHandle);

/*SPI Low Level APIs - Configuration & Control*/


#endif /* PERIPHERALS_INC_SPI_DRIVER_H_ */