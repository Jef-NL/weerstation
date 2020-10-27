/**
 ******************************************************************************
 * @file           : standBy.c
 * @brief          : Standby functions STM32
 ******************************************************************************
 * This file is used to activate the Standby mode and reset the Standby flags.
 *
 *
 ******************************************************************************
 */

#include "standBy.h"

/** \addtogroup PowerControl
 * Power related functions to control the power usage of the STM.
 *  @{
 */

/**
 * @brief  Function resetting the StandBy flags
 *
 * Reset the StandBy and WakeUp flag.
 * @param  argument: Not used
 * @retval None
 */
void resetStandBy() {
	// Check if flag haven't been reset
	if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET) {
		// Reset flags
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	}
}

/**
 * @brief  Function activating the StandBy mode
 *
 * Start the StandBy mode using the Hal Library.
 * @param  argument: Not used
 * @retval None
 */
void startStandBy() {
	// Enter standby mode
	HAL_PWR_EnterSTANDBYMode();
}
/** @}*/
