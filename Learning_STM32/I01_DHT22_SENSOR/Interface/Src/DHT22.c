/*
 *
 *
 */

#include <stdint.h>
#include "STM32F411xx.h"
#include "GPIO_Driver.h"
#include "GPTimer_Driver.h"
#include "DHT22.h"

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
    GPIO_SetOutputSpeed(GPIO, GPIO_Pin_no, GPIO_SPEED_LOW);

    //3. Configure Timer - Will use TIM5
    TIMx_Delay_ms_Init(TIM5);

    GPIO_SetPin(GPIO, GPIO_Pin_no);

    return DHT22_SUCCESS;
}

//Data Read API
uint32_t DHT22_Read(GPIOx_RegDef_t *GPIO, uint8_t GPIO_Pin_no, float *temp, float *humidity){
    //API
    /*Initialization Phase*/
    //START SIGNAL
    //1. MCU sends Start Signal
    GPIO_ResetPin(GPIO, GPIO_Pin_no);

    //2. MCU Sleeps for 1ms-18ms
    TIMx_Delay_ms(TIM5, 20);

    //3. MCU Pulls pin High
    GPIO_SetPin(GPIO, GPIO_Pin_no);

    //4. MCU Sleeps for 20-40us
    TIMx_Single_Delay_us(TIM5, 40);

    GPIO_ResetPin(GPIO, GPIO_Pin_no);
    TIMx_Delay_ms(TIM5, 20);
    GPIO_SetPin(GPIO, GPIO_Pin_no);

    //5. MCU configures pin to INPUT Mode
    GPIO_SetMode(GPIO, GPIO_Pin_no, GPIO_MODE_INPUT);
    
    //MCU waits for DHT22 Response signal
    //1. Wait for pin to go LOW (response signal)

    //2. Wait for pin to go HIGH (response signal)

    //3. Wait for pin to go LOW (incdication of Start bit)

    /*Data Transmission Phase*/
    //1. Handle the 5 bytes of incomming data from DHT22 Sensor


    /*Checksum Validation Phase*/
    //1. Compute checksum

    /*Back to normal state*/
    TIMx_Delay_ms(TIM5, 1000);
    GPIO_SetMode(GPIO, GPIO_Pin_no, GPIO_MODE_OUTPUT);
    GPIO_SetPin(GPIO, GPIO_Pin_no);
    return DHT22_SUCCESS;
}


//Diagnostic API
uint32_t DHT22_GetStatus(void){
    //API
    return DHT22_SUCCESS;
}
