#ifndef __PI_TUNE
#define __PI_TUNE

#include "Decoder_FOC.h"
#include "stdint.h"
#include "string.h"
#include  <stdio.h>

#define     BUFFER_SIZE_UART1     50
extern cur_PI_type cur_PI;
extern spd_PI_type spd_PI;
extern uint8_t rxBuffer_uart1[BUFFER_SIZE_UART1];

void PI_tune(cur_PI_type * curLoop, spd_PI_type * spdLoop);



#endif 
