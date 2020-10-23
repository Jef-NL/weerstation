/*
 * I2c.h
 *
 *  Created on: Oct 3, 2020
 *      Author: quinn
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

// Includes
#include <stdbool.h>
#include <stdio.h>
#include "stm32f0xx_hal.h"
#include "main.h"
#include <string.h>
#include <stdlib.h>

int16_t  Read_Sensor_16_signed( uint8_t sensoradres,  uint16_t sensAddress );
uint16_t Read_Sensor_16_unsigned( uint8_t sensoradres,  uint16_t sensAddress );
int  Read_Sensor_20( uint8_t sensoradres,  uint16_t sensAddress );
void writeFlash(int *cycles_counter, SensorData* input);
void readFlash_cycles(int *cycles_counter, SensorData *input);
void readFlash_Measure_DATA(int *cycles_counter, SensorData *input) ;
#endif /* INC_I2C_H_ */
