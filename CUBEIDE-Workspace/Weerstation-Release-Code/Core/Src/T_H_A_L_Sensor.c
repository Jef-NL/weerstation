/**
 ******************************************************************************
 * @file           : T_H_A_L_Sensor.c
 * @brief          : calculate and read the sensor data
 ******************************************************************************
 * This file contains all ESP and TCP related functions for the weather station.
 *
 *
 ******************************************************************************
 */
#include "T_H_A_L_Sensor.h"

/** \addtogroup Sensors
 * Read the sensors.
 *  @{
 */

/**
 * @brief Read the bmp280 and calculate the air pressure
 *
 * Read the registers of the bmp280 and calculate the temperature
 * and after that it will use that value to calculate the pressure.
 * @param  argument: Not used
 * @retval double: Pressure value
 */
double Read_Pressure_Sensor() {
	uint16_t dig_value_T1 = Read_Sensor_16_unsigned(0x88, (0x76 << 1));
	int16_t dig_value_T2 = Read_Sensor_16_signed(0x8A, (0x76 << 1));
	int16_t dig_value_T3 = -1000;//Read_Sensor_16_signed(0x8D, (0x76 << 1));
	uint16_t dig_value_P1 = Read_Sensor_16_unsigned(0x8E, (0x76 << 1));
	int16_t dig_value_P2 = Read_Sensor_16_signed(0x90, (0x76 << 1));
	int16_t dig_value_P3 = Read_Sensor_16_signed(0x92, (0x76 << 1));
	int16_t dig_value_P4 = Read_Sensor_16_signed(0x94, (0x76 << 1));
	int16_t dig_value_P5 = -1* Read_Sensor_16_signed(0x96, (0x76 << 1));
	int16_t dig_value_P6 = Read_Sensor_16_signed(0x98, (0x76 << 1));
	int16_t dig_value_P7 = Read_Sensor_16_signed(0x9A, (0x76 << 1));
	int16_t dig_value_P8 = Read_Sensor_16_signed(0x9C, (0x76 << 1));
	int16_t dig_value_P9 = Read_Sensor_16_signed(0x9E, (0x76 << 1));
	int value1 = Read_Sensor_20(0xF7, (0x76 << 1));
	int value2 = Read_Sensor_20(0xFA, (0x76 << 1));

	double var1 = (((double)value1 / 16384.0) - ((double)dig_value_T1 / 1024.0)) * (double)dig_value_T2;
	double var2 = (((double)value1 / 131072.0) - ((double)dig_value_T1 / 8192.0))
			* ((value1 / 131072.0) - ((double)dig_value_T1 / 8192.0)) * dig_value_T3;
	//double T= (var1+var2)/5120.0;
	double var3 = var1 + var2;

	var1 = (var3 / 2.0) - 64000.0;
	var2 = var1 * var1 * (double)dig_value_P6 / 32768.0;
	var2 = var2 + var1 * (double)dig_value_P5 * 2.0;
	var2 = (var2 / 4.0) + ((double)dig_value_P4 * 65536.0);
	var1 = ((double)dig_value_P3 * var1 * var1 / 524288.0 + (double)dig_value_P2 * var1)
			/ 524288.0;
	var1 = (1.0 + var1 / 32768) * (double)dig_value_P1;
	double P = 1048576 - (double)value2;
	P = (P - (var2 / 4096)) * 6250 / var1;
	var1 = dig_value_P9 * P * P / 2147483648.0;
	var2 = P * (double)dig_value_P8 / 32768;
	P = P + (var1 + var2 + (double)dig_value_P7) / 16;




	return P;
}

/**
 * @brief Read the  SI7021 and calculate the temperature
 *
 * Read the sensor via i2c and calculate the temperature.
 * @param  argument: Not used
 * @retval double: Temperature value
 */
double Tem_Sensor() {
	double T =
			((175.72 * ((Read_Sensor_16_signed(0xF3, (0x40 << 1)))) / (65536))
					- 46.85);
	return T;
}
/**
 * @brief Read the  SI7021 and calculate the humidity.
 *
 * Read the sensor via i2c and calculate the humidity.
 * @param  argument: Not used
 * @retval double: humidity value
 */
double Hum_Sensor() {
	double H = (((125 * (Read_Sensor_16_unsigned(0xF5, (0x40 << 1)))) / 65536)
			- 6);
	return H;
}
/**
 * @brief Read the LDR and calculate the humidity.
 *
 * Read the LDR via the ADC and calculate the light intensity.
 * @param  argument: Not used
 * @retval double: humidity value
 */
double LUX_Sensor() {
	uint16_t analogValue;
	double returnValue = 0.0;
	double voltage = 0.0;

	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
	analogValue = HAL_ADC_GetValue(&hadc);

	voltage = 3.3 - (((double) analogValue / 4095) * 3.3);

	returnValue = (250.0 / voltage) - 50.0;
	return returnValue;
}
/** @}*/
