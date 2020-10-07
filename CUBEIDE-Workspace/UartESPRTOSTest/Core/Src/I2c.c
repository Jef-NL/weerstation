/*
 * I2c.c
 *
 *  Created on: Oct 3, 2020
 *      Author: quinn
 */

#include "I2c.h"
#include "main.h"

uint16_t Read_Sensor_16_unsigned( uint8_t sensoradres, char *naam, uint16_t sensAddress ){
	uint16_t Data2;
	  if (HAL_I2C_IsDeviceReady(&hi2c1, sensAddress, 2, 1000) == HAL_ERROR) {
		  strcpy(naam,"neee\n");
		  HAL_UART_Transmit(&huart2, (uint8_t*)naam, strlen(naam), 100);
		  //return "ERROR";
	  	}else{
	  uint8_t Data[10];
	  Data[0] = sensoradres;
	  HAL_I2C_Master_Transmit(&hi2c1, sensAddress ,(uint8_t *)&Data[0], I2C_MEMADD_SIZE_8BIT, 1000);


	  Data[0] = 0x00;
	  Data[1] = 0x00;
	  while( Data[0] == 0x00 ){
	  	  // Read Temp form I2C Address for Temp
	  HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t *)&Data[0], I2C_MEMADD_SIZE_8BIT, 1000);
	  }
	  while( Data[1] == 0x00 ){
	  	  	  // Read Temp form I2C Address for Temp
	  	  HAL_I2C_Master_Receive(&hi2c1, sensAddress|= 0x01, (uint8_t *)&Data[1], I2C_MEMADD_SIZE_8BIT, 1000);
	  	 }

	   Data2 = (Data[1] <<8)+ Data[0];
	   itoa(Data2, naam,10);

	   	  return Data2;
	  }

	  	  return 0;
	  	  }
int16_t Read_Sensor_16_signed( uint8_t sensoradres, char *naam, uint16_t sensAddress ){
	int16_t Data2;
	  if (HAL_I2C_IsDeviceReady(&hi2c1, sensAddress, 2, 1000) == HAL_ERROR) {
		  strcpy(naam,"neee\n");
		  HAL_UART_Transmit(&huart2, (uint8_t*)naam, strlen(naam), 100);
		  //return "ERROR";
	  	}else{
	  uint8_t Data[10];
	  Data[0] = sensoradres;
	  HAL_I2C_Master_Transmit(&hi2c1, sensAddress ,(uint8_t *)&Data[0], I2C_MEMADD_SIZE_8BIT, 1000);


	  Data[0] = 0x00;
	  Data[1] = 0x00;
	  while( Data[0] == 0x00 ){
	  	  // Read Temp form I2C Address for Temp
	  HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t *)&Data[0], I2C_MEMADD_SIZE_8BIT, 1000);
	  }
	  while( Data[1] == 0x00 ){
	  	  	  // Read Temp form I2C Address for Temp
	  	  HAL_I2C_Master_Receive(&hi2c1, sensAddress|= 0x01, (uint8_t *)&Data[1], I2C_MEMADD_SIZE_8BIT, 1000);
	  	 }

	   Data2 = (Data[1] <<8)+( Data[0]);
	  // if ( Data2 > 0x07FF ) {
	      //   Data2 |= 0xF000;
	      //  }
	   itoa(Data2, naam,10);

	   	  return Data2;
	  }

	  	  return 0;
	  	  }
int Read_Sensor_20( uint8_t sensoradres, char *naam, uint16_t sensAddress ){
	int Data2;
	  if (HAL_I2C_IsDeviceReady(&hi2c1, sensAddress, 2, 1000) == HAL_ERROR) {
		  strcpy(naam,"neee\n");
		  HAL_UART_Transmit(&huart2, (uint8_t*)naam, strlen(naam), 100);
		  //return "ERROR";
	  	}else{
	  uint8_t Data[10];
	  Data[5] = sensoradres;
	  HAL_I2C_Master_Transmit(&hi2c1, sensAddress ,(uint8_t *)&Data[5], I2C_MEMADD_SIZE_8BIT, 1000);


	  Data[0] = 0x00;
	  Data[1] = 0x00;
	  Data[2] = 0x00;
	  while( Data[0] == 0x00 ){
	  	  // Read Temp form I2C Address for Temp
	  HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t *)&Data[0], I2C_MEMADD_SIZE_8BIT, 1000);
	  }
	  while( Data[1] == 0x00 ){
	  	  	  // Read Temp form I2C Address for Temp
	  	  HAL_I2C_Master_Receive(&hi2c1, sensAddress|= 0x01, (uint8_t *)&Data[1], I2C_MEMADD_SIZE_8BIT, 1000);
	  	 }
	  Data[5] = sensoradres;
	  HAL_I2C_Master_Transmit(&hi2c1, sensAddress ,(uint8_t *)&Data[5], I2C_MEMADD_SIZE_8BIT, 1000);
	  while( Data[3] == 0x00 ){
	  	  	  	  // Read Temp form I2C Address for Temp
	  	  	  HAL_I2C_Master_Receive(&hi2c1, sensAddress, (uint8_t *)&Data[3], I2C_MEMADD_SIZE_8BIT, 1000);
	  	  	  }

	   Data2 = (((Data[0] <<8)+ Data[1])<< 4)+(Data[3]>>3) ;

	  itoa(Data2, naam,10);
	  return Data2;
	  	}
	  return 0;
}
