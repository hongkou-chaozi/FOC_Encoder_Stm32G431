#include "encoder.h"

void requestEncoderData(void)
{
	uint8_t requstCmd = 0x1A;
	
	HAL_UART_Transmit_DMA(&huart1, &requstCmd, sizeof(requstCmd));
}

uint32_t processEncoderData(uint8_t * rawData)
{
	uint32_t encoderPos = 0;
	uint8_t tmpData[11] = {0};
	HAL_UART_Receive_DMA(&huart1,(uint8_t *)tmpData,sizeof(tmpData));
	

}