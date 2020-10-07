/*
 * FlashMemory.c
 *
 *  Created on: Oct 5, 2020
 *      Author: quinn
 */

#include "FlashMemory.h"

void Flash_WriteData(uint32_t addr,uint16_t *data,uint16_t Size)
{
         //1, unlock FLASH
  HAL_FLASH_Unlock();

         //2, erase FLASH
         // Initialize FLASH_EraseInitTypeDef
    FLASH_EraseInitTypeDef f;
    f.TypeErase = FLASH_TYPEERASE_PAGES;
    f.PageAddress = addr;
    f.NbPages = 1;
         // Set PageError
    uint32_t PageError = 0;
         //call the erase function
    HAL_FLASHEx_Erase(&f, &PageError);

         //3, burn to FLASH
	  uint32_t TempBuf = 0;
	  for(uint32_t i = 0;i< Size ;i++)
	 {
		 TempBuf = ~(*(data+i));
		 TempBuf <<= 16;
		  TempBuf += *(data+i); //Reverse check
		 HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD , addr + i * 4, TempBuf);
	 }

         //4, lock FLASH
  HAL_FLASH_Lock();
}

 // FLASH read data test, successfully returned 1
uint8_t Flash_ReadData(uint32_t addr,uint16_t *data,uint16_t Size)
{
  uint32_t temp;
	uint8_t result = 1;
  for(uint32_t i = 0;i< Size ;i++)
	{
			temp = *(__IO uint32_t*)(addr + i * 4);
		  if((uint16_t)temp == (uint16_t)(~(temp>>16)))
			{
				*(data+i) = (uint16_t)temp;
			}
			else
			{
				result = 0;
			}
	}
  return result;
}

