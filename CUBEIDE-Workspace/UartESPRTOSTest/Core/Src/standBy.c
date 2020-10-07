/*
 * standBy.c
 *
 *  Created on: Oct 3, 2020
 *      Author: quinn
 */

#include "standBy.h"
void resetStandBy(){
	// Check if flag haven't been reset
	if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET){
			// Reset flags
			__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
			__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
		}
}
void startStandBy(){
	// Enter standby mode
	HAL_PWR_EnterSTANDBYMode();
}
void startSleep(){
	// Enter standby mode
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}
