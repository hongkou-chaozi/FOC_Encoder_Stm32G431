#ifndef __ENCODER
#define __ENCODER

#include "main.h"
#include "usart.h"

uint8_t rawEncoderData[11];

uint32_t encoderRequest(uint8_t * rawData);

//	uint32_t encoderPos = 0;
//	HAL_UART_Receive_DMA(&huart1,(uint8_t *)tempData,sizeof(tempData));




#endif

