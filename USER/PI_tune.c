#include "PI_tune.h"



void PI_tune(cur_PI_type * curLoop, spd_PI_type * spdLoop)
{
	uint8_t newBuffer[BUFFER_SIZE_UART1 - 1];
	
	int caseValue = 0xFF;
	
	if(rxBuffer_uart1[0] == '!')
	{
			caseValue = 0;
	}
	
	if(rxBuffer_uart1[0] == '@')
	{
			caseValue = 1;
	}
	
	if(rxBuffer_uart1[0] == '#')
	{
			caseValue = 2;
	}
	
	if(rxBuffer_uart1[0] == '$')
	{
			caseValue = 3;
	}
	
	uint8_t str[10];
	memcpy(newBuffer, &rxBuffer_uart1[1], BUFFER_SIZE_UART1 - 1);
	for (int i = 0; i < 9; i++) 
	{
      str[i] = newBuffer[i];
  }
	
	float tmp = 0;
	sscanf(str, "%f", &tmp);
	
	if(caseValue == 0)
	{
		spdLoop->Kp_spd = tmp;
	}
	
	else if(caseValue == 1)
	{
		spdLoop->Ki_spd = tmp;
	}
		
	else if(caseValue == 2)
	{
		curLoop->Kp_cur = tmp;
	}
		
	else if(caseValue == 3)
	{
		curLoop->Ki_cur = tmp;
	}

}
