/*
 * T_H_A_L_Sensor.h
 *
 *  Created on: Oct 3, 2020
 *      Author: quinn
 */

#ifndef INC_T_H_A_L_SENSOR_H_
#define INC_T_H_A_L_SENSOR_H_

//includes
#include "I2c.h"
#include "main.h"


double Read_Pressure_Sensor();
double Tem_Sensor();
double Hum_Sensor();
double LUX_Sensor();
#endif /* INC_T_H_A_L_SENSOR_H_ */
