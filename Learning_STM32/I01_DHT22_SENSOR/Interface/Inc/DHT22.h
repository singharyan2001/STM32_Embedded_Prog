/*
 * DHT22.h
 *
 *  Created on: Dec 1, 2024
 *      Author: singh
 */

#ifndef INC_DHT22_H_
#define INC_DHT22_H_

#include <stdint.h>
#include "GPIO_Driver.h"

#define DEFAULT_SYS_FREQUENCY   16000000
#define TIMER_FREQUENCY_1MHZ    1000000

/*
 * Enums for DHT22 Sensor
*/
typedef enum{
    DHT22_SUCCESS,
    DHT22_ERR_TIMEOUT = -1,
    DHT22_ERR_CHECKSUM = -2,
    DHT22_ERR_INIT = -3
}DHT22_Error_e;

/*
 * Structures for DHT22 Sensor
*/
typedef struct{
    float Temperature;
    float Humidity;
}DHT22_DS_t;


/*
 * Functions for DHT22 Sensor
 */

//Timing Configuration API
uint32_t DHT22_SetTiming(void);

//Initialization API
uint32_t DHT22_Init(GPIOx_RegDef_t *GPIO, uint8_t GPIO_Pin_no);

//Data Read API
uint32_t DHT22_Read(GPIOx_RegDef_t *GPIO, uint8_t GPIO_Pin_no, float *temp, float *humidity);

//Diagnostic API
uint32_t DHT22_GetStatus(void);

//Non-Blocking APIs - Async or Interrupt based APIs

//Power Management API

//Calibration API



#endif /* INC_DHT22_H_ */
