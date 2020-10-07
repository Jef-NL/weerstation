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

/** \addtogroup I2c
 * All I2c functions to read the sensors
 *  @{
 */

#include "I2c.h"
#include "main.h"
/**
  * @brief Read the i2c bus
  *
  * first it check if there is a connection, after that it will read a unsigned 16 bit integer.
  * This will be done in two i2c read cycles.
  * @param  sensoradres: address van slave-address
  * @param  sensAddress: address van register-address
  * @retval uint16_t: data
  */
uint16_t Read_Sensor_16_unsigned(uint8_t sensoradres, uint16_t sensAddress) {
	uint16_t Data2;
	if (HAL_I2C_IsDeviceReady(&hi2c1, sensAddress, 2, 1000) == HAL_ERROR) {
		HAL_UART_Transmit(&huart2, (uint8_t*) "I2c error\n", sizeof("I2c error\n"), 100);
		//return "ERROR";
	} else {
		uint8_t Data[10];
		Data[0] = sensoradres;
		HAL_I2C_Master_Transmit(&hi2c1, sensAddress, (uint8_t*) &Data[0],
		I2C_MEMADD_SIZE_8BIT, 1000);

		Data[0] = 0x00;
		Data[1] = 0x00;
		while (Data[0] == 0x00) {
			// Read Temp form I2C Address for Temp
			HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t*) &Data[0],
			I2C_MEMADD_SIZE_8BIT, 1000);
		}
		while (Data[1] == 0x00) {
			// Read Temp form I2C Address for Temp
			HAL_I2C_Master_Receive(&hi2c1, sensAddress |= 0x01,
					(uint8_t*) &Data[1], I2C_MEMADD_SIZE_8BIT, 1000);
		}

		Data2 = (Data[1] << 8) + Data[0];

		return Data2;
	}

	return 0;
}
/**
  * @brief Read the i2c bus
  *
  * first it check if there is a connection, after that it will read a signed 16 bit integer.
  * This will be done in two i2c read cycles.
  * @param  sensoradres: address van slave-address
  * @param  sensAddress: address van register-address
  * @retval int16_t: data
  */
int16_t Read_Sensor_16_signed(uint8_t sensoradres, uint16_t sensAddress) {
	int16_t Data2;
	if (HAL_I2C_IsDeviceReady(&hi2c1, sensAddress, 2, 1000) == HAL_ERROR) {
		HAL_UART_Transmit(&huart2, (uint8_t*) "I2c error\n", sizeof("I2c error\n"), 100);
		//return "ERROR";
	} else {
		uint8_t Data[10];
		Data[0] = sensoradres;
		HAL_I2C_Master_Transmit(&hi2c1, sensAddress, (uint8_t*) &Data[0],
				I2C_MEMADD_SIZE_8BIT, 1000);

		Data[0] = 0x00;
		Data[1] = 0x00;
		while (Data[0] == 0x00) {
			// Read Temp form I2C Address for Temp
			HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t*) &Data[0],
					I2C_MEMADD_SIZE_8BIT, 1000);
		}
		while (Data[1] == 0x00) {
			// Read Temp form I2C Address for Temp
			HAL_I2C_Master_Receive(&hi2c1, sensAddress |= 0x01,
					(uint8_t*) &Data[1], I2C_MEMADD_SIZE_8BIT, 1000);
		}

		Data2 = (Data[1] << 8) + (Data[0]);

		return Data2;
	}

	return 0;
}
/**
  * @brief Read the i2c bus
  *
  * first it check if there is a connection, after that it will read a signed 20 bit integer.
  * This will be done in two i2c read cycles.
  * @param  sensoradres: address van slave-address
  * @param  sensAddress: address van register-address
  * @retval double: Pressure value
  */
int Read_Sensor_20(uint8_t sensoradres, uint16_t sensAddress) {
	int Data2;
	if (HAL_I2C_IsDeviceReady(&hi2c1, sensAddress, 2, 1000) == HAL_ERROR) {

		HAL_UART_Transmit(&huart2, (uint8_t*) "I2c error\n",sizeof("I2c error\n"), 100);
		//return "ERROR";
	} else {
		uint8_t Data[10];
		Data[5] = sensoradres;
		HAL_I2C_Master_Transmit(&hi2c1, sensAddress, (uint8_t*) &Data[5],
				I2C_MEMADD_SIZE_8BIT, 1000);

		Data[0] = 0x00;
		Data[1] = 0x00;
		Data[2] = 0x00;
		while (Data[0] == 0x00) {
			// Read Temp form I2C Address for Temp
			HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t*) &Data[0],
					I2C_MEMADD_SIZE_8BIT, 1000);
		}
		while (Data[1] == 0x00) {
			// Read Temp form I2C Address for Temp
			HAL_I2C_Master_Receive(&hi2c1, sensAddress |= 0x01,
					(uint8_t*) &Data[1], I2C_MEMADD_SIZE_8BIT, 1000);
		}
		Data[5] = sensoradres;
		HAL_I2C_Master_Transmit(&hi2c1, sensAddress, (uint8_t*) &Data[5],
				I2C_MEMADD_SIZE_8BIT, 1000);
		while (Data[3] == 0x00) {
			// Read Temp form I2C Address for Temp
			HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t*) &Data[3],
					I2C_MEMADD_SIZE_8BIT, 1000);
		}

		Data2 = (((Data[0] << 8) + Data[1]) << 4) + (Data[3] >> 3);

		return Data2;
	}
	return 0;
}
/** @}*/
