/**
  ******************************************************************************
  * @file           : ESP-Wireless-v1.c
  * @brief          : ESP WiFi and TCP connect functions
  ******************************************************************************
  * This file contains all ESP and TCP related functions for the weather station.
  *
  *
  ******************************************************************************
  */

#include "ESP-Wireless-v1.h"

/** \addtogroup ESP-Wireless
 * ESP / TCP / Uart related functions are grouped in to this module.
 *  @{
 */

// Global variables

/**Buffer for the Uart Received data**/
char receiveBuffer[200];
/**IP address for TCP server**/
char* hostIP = "";
/**Hal Tick Delay variable**/
uint32_t tickdelay = 0;



/**
  * @brief  Function initializing the ESP.
  *
  * Reset the ESP using the Uart connection
  * @param  argument: Not used
  * @retval None
  */
void espInit() {
	consoleSend("Restarting ESP\n");
	// Create command
	const char Data[] = "AT+RST\r\n";

	// Send Uart command
	HAL_UART_Transmit(&huart1, (uint8_t*) Data, sizeof(Data), 100);

	//Startup delay
	HAL_Delay(500);
	consoleSend("Done restarting ESP\n");
}

/**
  * @brief  Function connect to WiFi.
  *
  * Connect to a wireless network using the SSID and the Password
  * @param  ssid: Network SSID name
  * @param  passw: Network Password
  * @retval bool: Connected or not connected
  */
bool espConnect(char *ssid, char *passw) {
	// Variables
	static char sendBuffer[80];
	memcpy(sendBuffer, "", sizeof(sendBuffer));
	clearChar(receiveBuffer, sizeof(receiveBuffer));

	HAL_StatusTypeDef uartRet;

	// Reset ESP
	espInit();

	// Create commands
	snprintf(sendBuffer, sizeof(sendBuffer), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, passw);

	// Update User
	consoleSend("Connecting to WiFi...\n");

	// Reset UART1
	HAL_UART_AbortReceive(&huart1);

	// Send commands
	HAL_UART_Transmit(&huart1, (uint8_t*) sendBuffer, strlen(sendBuffer), 10);

	// Receive answer
	uartRet = HAL_UART_Receive_IT(&huart1, (uint8_t*) receiveBuffer, 200);
	tickdelay = HAL_GetTick() + 5000;
	while ((strstr(receiveBuffer, "OK") == 0 && strstr(receiveBuffer, "ERROR") == 0) && HAL_GetTick() <= tickdelay);		// Hold for read

	// Check answer
	if (uartRet != HAL_ERROR) {
		if (strstr(receiveBuffer, "OK")){
			// Update User
			consoleSend("Connected to WiFi\n");
			return true;
		} else if (strstr(receiveBuffer, "FAIL")){
			// Update User
			consoleSend("Failed to connect\n");
			return false;
		} else if (strstr(receiveBuffer, "ERR")){
			// Update User
			consoleSend("Error connecting to WiFi\n");
			return false;
		}
	}

	return false;
}

/**
  * @brief  Function connect to TCP Server.
  *
  * Connect to the TCP webserver using the IP address of the server and the port
  * @param  address: Webserver IP address
  * @param  port: Webserver port
  * @retval bool: Connected or not connected
  */
bool tcpConnect(char *address, char *port) {
	// Variables
	static char sendBuffer[50];
	memcpy(sendBuffer, "", sizeof(sendBuffer));
	clearChar(receiveBuffer, sizeof(receiveBuffer));
	hostIP = address;

	HAL_StatusTypeDef uartRet;

	// Create commands
	snprintf(sendBuffer, sizeof(sendBuffer), "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", address, port);

	// Update User
	consoleSend("Connecting to TCP server...\n");

	// Reset UART1
	HAL_UART_AbortReceive(&huart1);

	// Send commands
	HAL_UART_Transmit(&huart1, (uint8_t*) sendBuffer, strlen(sendBuffer), 10);

	// Receive answer
	uartRet = HAL_UART_Receive_IT(&huart1, (uint8_t*) receiveBuffer, 200);
	tickdelay = HAL_GetTick() + 5000;
	while ((strstr(receiveBuffer, "OK") == 0 && strstr(receiveBuffer, "ERROR") == 0) && HAL_GetTick() <= tickdelay);		// Hold for read

	// Check answer
	if (uartRet != HAL_ERROR) {
		if (strstr(receiveBuffer, "OK")){
			// Update User
			consoleSend("Connected to TCP Server\n");
			return true;
		} else if (strstr(receiveBuffer, "ALREADY CONN")){
			// Update User
			consoleSend("Already connected to TCP Server\n");
			return true;
		} else if (strstr(receiveBuffer, "ERR")){
			// Update User
			consoleSend("Error connecting to TCP server\n");
			return false;
		} else if (strstr(receiveBuffer, "busy")){
			// Update User
			consoleSend("Error connecting to TCP server Busy...\n");
			return false;
		}
	}

	return false;
}

/**
  * @brief  Function send sensor data to the TCP server.
  *
  * Send the sensor data measured by the sensors to the Webserver using the TCP connection opened by the tcpConnect() function
  * @param  temp: Temperature value
  * @param  humid: Humidity value
  * @param  pressure: Pressure value
  * @param  lux: Light level
  * @param  missedCyl: Minutes data could not be stored on the database
  * @retval bool: Data send successfully or not successfully
  */
bool tcpSend(float temp, float humid, float pressure, float lux, int missedCyl) {
	// Variables
	static char sendBuffer[20];
	memcpy(sendBuffer, "", sizeof(sendBuffer));
	clearChar(receiveBuffer, sizeof(receiveBuffer));

	HAL_StatusTypeDef uartRet;

	static char dataOut[100];																	// Data for post
	int dataLength = 0;

	const char headerOut[] = "POST /weerstationPost.php HTTP/1.1\r\n";							// Post header
	static char hostOut[30];																	// Host IP for post
	const char contentOut[] = "Content-Type: application/x-www-form-urlencoded\r\n";			// Content Type for post
	static char dataLenOut[30] = "";															// Length of dataOut for post

	// Create commands
	memcpy(dataOut, "", sizeof(dataOut));
	snprintf(dataOut, sizeof(dataOut), "api_key=tPmAT5Ab3j7F9&temp=%0.2f&humid=%0.2f&pressure=%0.2f&lux=%0.2f&date=%d", temp, humid, pressure, lux, missedCyl);	// Set data

	memcpy(hostOut, "", sizeof(hostOut));
	snprintf(hostOut, sizeof(hostOut), "Host: %s\r\n", hostIP);									// Set Host IP

	memcpy(dataLenOut, "", sizeof(dataLenOut));
	snprintf(dataLenOut, sizeof(dataLenOut), "Content-Length: %d\r\n\r\n", strlen(dataOut));	// Get data length

	strcat(dataOut, "\r\n");																	// Add Tale

	dataLength = strlen(headerOut) + strlen(hostOut) + strlen(contentOut) + strlen(dataLenOut) + strlen(dataOut);

	snprintf(sendBuffer, sizeof(sendBuffer), "AT+CIPSEND=%d\r\n", dataLength);

	// Update User
	consoleSend("Sending HTTP Post...\n");

	// Send commands
	HAL_UART_Transmit(&huart1, (uint8_t*) sendBuffer, strlen(sendBuffer), 10);					// Send start command
	HAL_Delay(2);

	HAL_UART_Transmit(&huart1, (uint8_t*) headerOut, strlen(headerOut), 10);
	HAL_Delay(2);
	HAL_UART_Transmit(&huart1, (uint8_t*) hostOut, strlen(hostOut), 10);
	HAL_Delay(2);
	HAL_UART_Transmit(&huart1, (uint8_t*) contentOut, strlen(contentOut), 10);
	HAL_Delay(2);
	HAL_UART_Transmit(&huart1, (uint8_t*) dataLenOut, strlen(dataLenOut), 10);
	HAL_Delay(2);

	// Reset UART1
	HAL_UART_AbortReceive(&huart1);

	// Last Send
	HAL_UART_Transmit(&huart1, (uint8_t*) dataOut, strlen(dataOut), 10);

	// Receive answer
	uartRet = HAL_UART_Receive_IT(&huart1, (uint8_t*) receiveBuffer, 200);
	tickdelay = HAL_GetTick() + 2000;
	while (strstr(receiveBuffer, "200 OK") == 0 && HAL_GetTick() <= tickdelay);		// Hold for read

	// Check answer
	if (uartRet != HAL_ERROR) {
		if (strstr(receiveBuffer, "200 OK")){
			// Update User
			consoleSend("Success\n");
			return true;
		} else {
			// Update User
			consoleSend("Failed\n");
			return false;
		}
	}

	return false;
}

/**
  * @brief  Function send Uart message to the USB
  * @param  message: Message to send to the Uart
  * @retval None
  */
void consoleSend(char* message) {
	HAL_UART_Transmit(&huart2, (uint8_t*) message, strlen(message), 10);
	HAL_Delay(10);
}

/**
  * @brief  Function clear char array
  * @param  arr: char array to be cleared
  * @param  leng: length of the char array
  * @retval None
  */
void clearChar(char* arr, int leng){
	for (int i = 0; i<leng; i++){
		arr[i] = '\0';
	}
}

/** @}*/
