/*
 * standby.h
 *
 *  Created on: Oct 3, 2020
 *      Author: quinn
 */

#ifndef INC_STANDBY_H_
#define INC_STANDBY_H_

// Includes
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "stm32f0xx_hal.h"
#include "main.h"

void resetStandBy();
void startStandBy();
void startSleep();

#endif /* INC_STANDBY_H_ */
