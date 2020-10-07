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


double Read_Pressure_Sensor( char *naam );
double Tem_Sensor(char *naam);
double Hum_Sensor(char *naam);
double LUX_Sensor();
#endif /* INC_T_H_A_L_SENSOR_H_ */
