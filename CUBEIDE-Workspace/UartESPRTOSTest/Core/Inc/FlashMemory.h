/*
 * FlahMemory.h
 *
 *  Created on: Oct 5, 2020
 *      Author: quinn
 */

#ifndef INC_FLAHMEMORY_H_
#define INC_FLAHMEMORY_H_

#include "main.h"

void Flash_WriteData(uint32_t addr,uint16_t *data,uint16_t Size);
uint8_t Flash_ReadData(uint32_t addr,uint16_t *data,uint16_t Size);

#endif /* INC_FLAHMEMORY_H_ */
