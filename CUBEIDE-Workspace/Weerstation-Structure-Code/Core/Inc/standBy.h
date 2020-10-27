/**
  ******************************************************************************
  * @file           : standBy.h
  * @brief          : Standby functions STM32
  ******************************************************************************
  * This file is used to activate the Standby mode and reset the Standby flags.
  *
  *
  ******************************************************************************
  */
#include "stm32f0xx_hal.h"

#ifndef INC_STANDBY_H_
#define INC_STANDBY_H_

void resetStandBy();
void startStandBy();


#endif /* INC_STANDBY_H_ */
