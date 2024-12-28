/*
 *
 *
 */

#include <stdint.h>
#include "STM32F411xx.h"
#include "GPIO_Driver.h"
#include "GPTimer_Driver.h"
#include "DHT22.h"
#include <stdio.h>

//Timing Configuration API
uint32_t DHT22_SetTiming(void){
    //API
    return DHT22_SUCCESS;
}

//Initialization API
uint32_t DHT22_Init(GPIOx_RegDef_t *GPIO, uint8_t GPIO_Pin_no){
    //API
	//1. Enable clock access to GPIO & Timer Peripheral
	GPIOx_PClkControl(GPIO, CLK_EN);
    //TIMx_ClockEnable(TIM5);
    //2. Configure GPIO pin - as Output Mode
    //Set Mode
    GPIO_SetMode(GPIO, GPIO_Pin_no, GPIO_MODE_OUTPUT);

    //Set Output type & speed
    GPIO_SetOutputType(GPIO, GPIO_Pin_no, GPIO_OUTPUT_PUSH_PULL);
    GPIO_SetOutputSpeed(GPIO, GPIO_Pin_no, GPIO_SPEED_HIGH);

    //3. Configure Timer - Will use TIM5
    TIMx_Delay_ms_Init(TIM5);

    GPIO_SetPin(GPIO, GPIO_Pin_no);

    return DHT22_SUCCESS;
}

//Data Read API
uint32_t DHT22_Read(GPIOx_RegDef_t *GPIO, uint8_t GPIO_Pin_no, float *temp, float *humidity){
    //API
    /*Initialization Phase*/
	uint8_t data[5] = {0}; //To store the 5 bytes read from the sensor
	uint8_t timeout;
    //START SIGNAL
    //1. MCU sends Start Signal
    GPIO_ResetPin(GPIO, GPIO_Pin_no);

    //2. MCU Sleeps for 1ms-18ms
    TIMx_Delay_ms(TIM5, 20);

    //3. MCU Pulls pin High
    GPIO_SetPin(GPIO, GPIO_Pin_no);

    //4. MCU Sleeps for 20-40us
    TIMx_Single_Delay_us(TIM5, 40);

    //5. MCU configures pin to INPUT Mode
    GPIO_SetMode(GPIO, GPIO_Pin_no, GPIO_MODE_INPUT);
    
    //MCU waits for DHT22 Response signal
    //1. Wait for pin to go LOW (response signal)
    timeout = 100;									//100us timeout
    while(GPIO_ReadFromInputPin(GPIO, GPIO_Pin_no) == 1 && --timeout);	//Wait for pin to go LOW
    if(!timeout){
    	return DHT22_ERR_TIMEOUT;
    }

    //2. Wait for pin to go HIGH (response signal)
    timeout = 100;									//100us timeout
    while(GPIO_ReadFromInputPin(GPIO, GPIO_Pin_no) == 0 && --timeout);	//Wait for pin to go HIGH
    if(!timeout){
    	return DHT22_ERR_TIMEOUT;
    }

    //3. Wait for pin to go LOW (indication of Start bit)
    timeout = 100;									//100us timeout
    while(GPIO_ReadFromInputPin(GPIO, GPIO_Pin_no) == 1 && --timeout);	//Wait for pin to go LOW
    if(!timeout){
    	return DHT22_ERR_TIMEOUT;
    }

    /*Data Transmission Phase*/
    //1. Handle the 5 bytes of incomming data from DHT22 Sensor
    //Iterate over each byte, and within each byte, iterate over each bit, check 50us signal, then measure pulse width
    //and then decode the bit through pulse width
    for(volatile uint8_t byteIndex = 0; byteIndex < 5; byteIndex++){
    	for(volatile uint8_t bitIndex = 0; bitIndex < 8; bitIndex++){
    		//Wait for start signal of the bit
    		timeout = 100;
    		while(GPIO_ReadFromInputPin(GPIO, GPIO_Pin_no) == 0 && --timeout);	//Wait for pin to go HIGH, current start bit signal is being transmitted.
    		if(!timeout){
    			return DHT22_ERR_TIMEOUT;
    		}

    		//Measure high pulse width signal
    		TIMx_Start(TIM5);
    		uint32_t start = TIM5->CNT;
    		timeout = 100;
    		while(GPIO_ReadFromInputPin(GPIO, GPIO_Pin_no) == 1 && timeout);
    		if(!timeout){
    			return DHT22_ERR_TIMEOUT;
    		}

    		TIM5->CR1 &= ~(TIMx_CEN);	//Stop timer
    		uint8_t pulseWidth = (TIM5->CNT) - start; //measure current time
    		TIM5->CNT = 0;	//Clear CNT

    		//Decode bit
    		if(pulseWidth > 50){
    			//High pulse > 50us is a '1'
    			data[byteIndex] |= (1<<(7-bitIndex));
    		}
    	}
    }

    /*Checksum Validation Phase*/
    //1. Compute checksum
//    uint8_t checksum = data[0] + data[1] + data[2] + data[3];
//    if(checksum != data[4]){
//    	return DHT22_ERR_CHECKSUM;
//    }
//    printf("Checksum value: %d", checksum);

    /*Convert Data to Temp & Humidity*/
    *humidity = (((data[0] << 8) | data[1]) * 0.1)/100; //Convert to %RH
    *temp = ((((data[2] & 0x7F) << 8) | data[3]) * 0.1)/100; //Convert to *C

    //condition to check negative temperature
    printf("Read successfully through DHT22 sensor\n");
    printf("Temperature: %.2f *c\n", *temp);
    printf("Humidity: %.2f RH\n", *humidity);

    /*Back to normal state*/
//    TIMx_Delay_ms(TIM5, 1000);
    GPIO_SetMode(GPIO, GPIO_Pin_no, GPIO_MODE_OUTPUT);
    GPIO_SetPin(GPIO, GPIO_Pin_no);
    return DHT22_SUCCESS;
}


//Diagnostic API
uint32_t DHT22_GetStatus(void){
    //API
    return DHT22_SUCCESS;
}
