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
		HAL_UART_Transmit(&huart2, (uint8_t*) "I2c error\n",
				sizeof("I2c error\n"), 100);
		//return "ERROR";
	} else {
		uint8_t Data[10];
		Data[0] = sensoradres;
		HAL_I2C_Master_Transmit(&hi2c1, sensAddress, (uint8_t*) &Data[0],
		I2C_MEMADD_SIZE_8BIT, 1000);
		HAL_Delay(200);
		HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t*) &Data[0],
		I2C_MEMADD_SIZE_8BIT, 1000);
		HAL_Delay(200);
		HAL_I2C_Master_Receive(&hi2c1, sensAddress |= 0x01, (uint8_t*) &Data[1],
		I2C_MEMADD_SIZE_8BIT, 1000);
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
		HAL_UART_Transmit(&huart2, (uint8_t*) "I2c error\n",
				sizeof("I2c error\n"), 100);
		//return "ERROR";
	} else {
		uint8_t Data[10];
		Data[0] = sensoradres;
		HAL_I2C_Master_Transmit(&hi2c1, sensAddress, (uint8_t*) &Data[0],
		I2C_MEMADD_SIZE_8BIT, 1000);
		HAL_Delay(200);
		HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t*) &Data[0],
		I2C_MEMADD_SIZE_8BIT, 1000);
		HAL_Delay(200);
		HAL_I2C_Master_Receive(&hi2c1, sensAddress |= 0x01, (uint8_t*) &Data[1],
		I2C_MEMADD_SIZE_8BIT, 1000);
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

		HAL_UART_Transmit(&huart2, (uint8_t*) "I2c error\n",
				sizeof("I2c error ,bmp sensor\n"), 100);
		//return "ERROR";
	} else {
		uint8_t Data[10];
		Data[5] = sensoradres;
		HAL_I2C_Master_Transmit(&hi2c1, sensAddress, (uint8_t*) &Data[5],
		I2C_MEMADD_SIZE_8BIT, 1000);
		HAL_Delay(200);
		HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t*) &Data[0],
		I2C_MEMADD_SIZE_8BIT, 1000);
		HAL_Delay(200);
		HAL_I2C_Master_Receive(&hi2c1, sensAddress |= 0x01, (uint8_t*) &Data[1],
		I2C_MEMADD_SIZE_8BIT, 1000);
		HAL_Delay(100);
		HAL_I2C_Master_Transmit(&hi2c1, sensAddress, (uint8_t*) &Data[5],
		I2C_MEMADD_SIZE_8BIT, 1000);
		HAL_Delay(100);
		HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t*) &Data[3],
		I2C_MEMADD_SIZE_8BIT, 1000);
		Data2 = (((Data[0] << 8) + Data[1]) << 4) + (Data[3] >> 3);

		return Data2;
	}
	return 0;
}
/**
 * @brief Read the external EEPROM, only address 0
 *
 *
 * @param  cycles_counter: the address of the cycles_counter variable.
 * @param  input: The address of the stored struct.
 * @retval double: Pressure value
 */

void readFlash_cycles(int *cycles_counter, SensorData *input) {
	uint8_t Data[10];
	Data[0] = 0x00;
	Data[1] = 0x00;
	HAL_I2C_Master_Transmit(&hi2c1, 0xA1, (uint8_t*) &Data, 2, 1000);
	HAL_Delay(10);
	HAL_I2C_Master_Receive(&hi2c1, 0xA0, (uint8_t*) &Data, 1, 1000);
	HAL_Delay(10);

	char Data3[10];
	*cycles_counter = Data[0];
	itoa(Data[0], Data3, 10);
	HAL_UART_Transmit(&huart2, (uint8_t*) Data3, strlen(Data3), 100);

}
/**
 * @brief Read the external EEPROM, all address if used excepted of address 0.
 *
 *
 * @param  cycles_counter: the address of the cycles_counter variable.
 * @param  input: The address of the stored struct.
 * @retval double: Pressure value
 */
void readFlash_Measure_DATA(int *cycles_counter, SensorData *input) {
	int i=*cycles_counter;
	float g[4];
	uint8_t Data[10];
	HAL_Delay(10);
	for (int j = 0; j < 4; j++) {
		uint16_t address = 0x05 + 0x05 * j + i * 0x20;
		Data[0] = (address >> 8);
		Data[1] = address;
		HAL_I2C_Master_Transmit(&hi2c1, 0xA1, (uint8_t*) &Data, 2, 1000);
		HAL_Delay(10);
		HAL_I2C_Master_Receive(&hi2c1, 0xA0, (uint8_t*) &Data, 4, 1000);
		HAL_Delay(10);
		memcpy(&g[j], Data, sizeof g[j]);
	}
	input[i].T = g[0];
	input[i].H = g[1];
	input[i].A = g[2];
	input[i].L = g[3];

}
/**
 * @brief Write external EEPROM, write the new data and the cycles_counter
 *
 * @param  cycles_counter: the address of the cycles_counter variable.
 * @param  input: The address of the stored struct.
 * @retval double: Pressure value
 */
void writeFlash(int *cycles_counter, SensorData *input) {
	char Data3[10];
	if (HAL_I2C_IsDeviceReady(&hi2c1, 0xA1, 2, 1000) == HAL_ERROR) {
		strcpy(Data3, "ERROR With External EEPROM\n");
		HAL_UART_Transmit(&huart2, (uint8_t*) Data3, strlen(Data3), 100);
		//return "ERROR";
	} else {

		uint8_t Data[10];
		Data[0] = 0x00;
		Data[1] = 0x00;
		Data[2] = *cycles_counter & 0xFF;
		HAL_I2C_Master_Transmit(&hi2c1, 0xA1, (uint8_t*) &Data, 3, 1000);
		itoa(Data[2], Data3, 10);
		HAL_UART_Transmit(&huart2, (uint8_t*) Data3, strlen(Data3), 100);

		int8_t Data2[sizeof(float)];
		int i = *cycles_counter - 1;

		float in[4] = { input[10].T, input[10].H, input[10].A, input[10].L };
		for (int j = 0; j < 5; j++) {
			memcpy(Data2, &in[j], sizeof in[j]);
			uint16_t address = 0x05 + 0x05 * j + i * 0x20;
			Data[0] = (address >> 8);
			Data[1] = address;

			Data[2] = Data2[0];
			Data[3] = Data2[1];
			Data[4] = Data2[2];
			Data[5] = Data2[3];
			HAL_Delay(10);
			HAL_I2C_Master_Transmit(&hi2c1, 0xA1, (uint8_t*) &Data, 6, 1000);
		}
	}
}

/** @}*/

