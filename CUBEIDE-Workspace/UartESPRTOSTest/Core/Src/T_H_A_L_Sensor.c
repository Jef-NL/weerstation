/*
 * T_H_A_L_Sensor.c
 *
 *  Created on: Oct 3, 2020
 *      Author: quinn
 */
#include "T_H_A_L_Sensor.h"

 double Read_Pressure_Sensor( char *naam ){
	char Data[10];
	uint16_t dig_value_T1= Read_Sensor_16_unsigned( 0x88, Data, (0x76 << 1));
	int16_t dig_value_T2= Read_Sensor_16_signed( 0x8A, Data, (0x76 << 1));
	int16_t dig_value_T3= Read_Sensor_16_signed( 0x8C, Data, (0x76 << 1));
	uint16_t dig_value_P1= Read_Sensor_16_unsigned( 0x8E, Data, (0x76 << 1));
	int16_t dig_value_P2= Read_Sensor_16_signed( 0x90, Data, (0x76 << 1));
	int16_t dig_value_P3= Read_Sensor_16_signed( 0x92, Data, (0x76 << 1));
	int16_t dig_value_P4= Read_Sensor_16_signed( 0x94, Data, (0x76 << 1));
	int16_t dig_value_P5= Read_Sensor_16_signed( 0x96, Data, (0x76 << 1));
	int16_t dig_value_P6= Read_Sensor_16_signed( 0x98, Data, (0x76 << 1));
	int16_t dig_value_P7= Read_Sensor_16_signed( 0x9A, Data, (0x76 << 1));
	int16_t dig_value_P8= Read_Sensor_16_signed( 0x9C, Data, (0x76 << 1));
	int16_t dig_value_P9= Read_Sensor_16_signed( 0x9E, Data, (0x76 << 1));
	int value1= Read_Sensor_20( 0xF7, Data, (0x76 << 1));
	int value2= Read_Sensor_20( 0xF, Data, (0x76 << 1));

	double var1= ((value1/16384.0)-(dig_value_T1/1024.0))*dig_value_T2;
	double var2= ((value1/131072.0)-(dig_value_T1/8192.0))*((value1/131072.0)-(dig_value_T1/8192.0)) *-1000 ;
	//double T= (var1+var2)/5120.0;
	double var3= var1+var2;

	 var1= (var3/2.0)-64000.0;
	var2= var1*var1 *dig_value_P6/32768.0;
	 var2= var2+ var1* dig_value_P5*2.0;
	var2 = (var2/4.0)+(dig_value_P4*65536.0);
	 var1= (dig_value_P3* var1*var1/524288.0+dig_value_P2*var1)/524288.0;
	 var1=(1.0+var1/32768)*dig_value_P1;
	 double P = 1048576- value2;
	 P= (P-(var2/4096))*6250/var1;
	 var1= dig_value_P9*P*P/2147483648.0;
	 var2= P*dig_value_P8/32768;
	 P = P+(var1+var2+dig_value_P7)/16;
	itoa(P, naam,10);
	return P;
	}


 double Tem_Sensor(char *naam){
	 double T =((175.72 * ((Read_Sensor_16_signed( 0xF3, naam, (0x40 << 1)))) /(65536)) - 46.85);
 	 itoa(T, naam,10);
 	 return T ;
 }
 double Hum_Sensor(char *naam){
	 double H=(((125* (Read_Sensor_16_unsigned( 0xF5, naam, (0x40 << 1)))) / 65536)- 6);
	 itoa(H, naam,10);
	 return H;
 }
 double LUX_Sensor(){
	 uint16_t analogValue;
	 double returnValue = 0.0;
	 double voltage = 0.0;

	 HAL_ADC_Start(&hadc);
	 HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
	 analogValue = HAL_ADC_GetValue(&hadc);

	 voltage = 3.3- (((double) analogValue / 4095) * 3.3);

	 returnValue = ( 250.0 / voltage ) - 50.0;
	 return returnValue;
 }
