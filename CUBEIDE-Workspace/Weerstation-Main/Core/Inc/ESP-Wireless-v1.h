#ifndef ESPWIRELESS_H_
#define ESPWIRELESS_H_

// Includes
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "stm32f0xx_hal.h"
#include "main.h"

// Functions
void espInit();
bool espConnect(char* ssid, char* passw);
bool tcpConnect(char* address, char* port);
bool tcpSend(float temp, float humid, float pressure, float lux, int missedCyl);
void consoleSend(char* message);
void clearChar(char* arr, int leng);

#endif /* ESPWIRELESS_H_ */
