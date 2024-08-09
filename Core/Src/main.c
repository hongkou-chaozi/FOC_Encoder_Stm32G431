/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "comp.h"
#include "dac.h"
#include "dma.h"
#include "fdcan.h"
#include "i2c.h"
#include "opamp.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define PI					3.141592653f
	
#include <stdio.h>
#include <string.h>
//#include "SMO_FOC.h"
#include "decoder0.h"
#include "Decoder_FOC.h"
#include "foc.h"
#include "mc_Lib.h"
#include "PI_tune.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define     BUFFER_SIZE_UART1     50
uint8_t rxBuffer_uart1[BUFFER_SIZE_UART1];

#define     BUFFER_SIZE_UART4     20
uint8_t rxBuffer_uart4[BUFFER_SIZE_UART4];

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
float temp[12];
static uint8_t tempData[52] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x80,0x7F};
uint8_t MotorState = 0;
uint16_t adc1_in1, adc1_in2, adc1_in3, adc1_in4, adc_vbus;
uint16_t IA_Offset,IB_Offset,IC_Offset;
uint8_t ADC_offset = 0;
uint8_t cmd = 0x1A;
uint32_t absPos = 0;
float	memAngle;
float	genTheta;

float Encoder_eleAngle;
float EncoderRPM;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC2_Init();
  MX_COMP1_Init();
  MX_DAC1_Init();
  MX_DAC3_Init();
  MX_FDCAN1_Init();
  MX_I2C3_Init();
  MX_OPAMP1_Init();
  MX_OPAMP2_Init();
  MX_OPAMP3_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
	HAL_OPAMP_Start(&hopamp1);
	HAL_OPAMP_Start(&hopamp2);
	HAL_OPAMP_Start(&hopamp3);
	HAL_ADCEx_Calibration_Start( &hadc1, ADC_SINGLE_ENDED);
	HAL_ADCEx_Calibration_Start( &hadc2, ADC_SINGLE_ENDED);
	__HAL_ADC_CLEAR_FLAG( &hadc1, ADC_FLAG_JEOC);
	__HAL_ADC_CLEAR_FLAG( &hadc1, ADC_FLAG_EOC);
	__HAL_ADC_CLEAR_FLAG( &hadc2, ADC_FLAG_JEOC);
	HAL_ADCEx_InjectedStart_IT(&hadc1);
	HAL_ADCEx_InjectedStart(&hadc2);
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxBuffer_uart1, BUFFER_SIZE_UART1);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart4, rxBuffer_uart4, BUFFER_SIZE_UART4);
	TIM1->ARR = 8000 - 1;
	TIM1->CCR4 = 8000 - 2;
	HAL_TIM_Base_Start( &htim1);
	HAL_TIM_PWM_Start( &htim1, TIM_CHANNEL_4);
	Decoder_FOC_initialize();
	rtU.SpeedRef = 300;
	rtU.Motor_OnOff = 1;
	rtU.v_bus = 24;
	
//	SVM_handler.PWMtimerCounts = 8000.0F;
//	FOC_handler.Vbus = 24.0F;
//	DQ_handler.d = 1.0F;
//	DQ_handler.q = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV3;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int fputc(int ch, FILE *f)
{
 while ((USART1->ISR & 0X40) == 0); 
 USART1->TDR = (uint8_t)ch; 
 return ch;
}

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	static uint8_t cnt;
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
	if(hadc == &hadc1)
	{
		if(ADC_offset == 0)
		{
			cnt++;
			adc1_in1 = hadc1.Instance->JDR1;
			adc1_in2 = hadc2.Instance->JDR1;
			adc1_in3 = hadc1.Instance->JDR2;
			IA_Offset += adc1_in1;
			IB_Offset += adc1_in2;
			IC_Offset += adc1_in3;
			if(cnt >= 10)
			{
				ADC_offset = 1;
				IA_Offset = IA_Offset/10;
				IB_Offset = IB_Offset/10;
				IC_Offset = IC_Offset/10;
			}
		}
		else
		{
			
			adc1_in1 = hadc1.Instance->JDR1;
			adc1_in3 = hadc1.Instance->JDR2;
			adc1_in2 = hadc2.Instance->JDR1;
			
			rtU.Ia = (adc1_in1 - IA_Offset)*0.012084f;
			rtU.Ib = (adc1_in2 - IB_Offset)*0.012084f;
			rtU.Ic = (adc1_in3 - IC_Offset)*0.012084f;
			
//			ABC_handler.a = rtU.Ia;
//			ABC_handler.b = rtU.Ib;
//			ABC_handler.c = rtU.Ic;
			
			Decoder_FOC_step();
//			VFStart(&ABC_handler, &DQ_handler, &alphaBeta_handler, 0, &SC_handler);
//			SVPWM_Calc(&ABC_handler, &FOC_handler, &SVM_handler, regCCR);
			
//			
			TIM1->CCR1 = rtY.tABC[0];
			TIM1->CCR2 = rtY.tABC[1];
			TIM1->CCR3 = rtY.tABC[2];
			
//			TIM1->CCR1 = regCCR[1];
//			TIM1->CCR2 = regCCR[0];
//			TIM1->CCR3 = regCCR[2];
			
			
//			SVPWM_Calc(&ABC_handler, &FOC_handler, &SVM_handler, regCCR);

			

			rtDWW.decoder_o.Encoder_offset = 47445;
			rtDWW.decoder_o.Cnt_per_Rev = 131072;
			rtDWW.decoder_o.EncoderCnt = absPos;
			rtDWW.decoder_o.EncoderIdx = 0;
									 
			Decoder_Step(&rtDWW.decoder_o.Cnt_per_Rev, &rtDWW.decoder_o.EncoderCnt, &rtDWW.decoder_o.EncoderIdx,
										&EncoderRPM, &Encoder_eleAngle, &rtDWW.decoder_o.Encoder_offset,
										&rtDWW.decoder_o.Decoder_Step_h);
//						 
			rtU.theta_fbk = Encoder_eleAngle;
			rtU.wn_fbk = EncoderRPM;
			
//			genTheta = 2.0F * PI * thetaGenerate(10);
			
			memAngle = absPos / 131072.0F * 2.0F * PI;
			

	
			
			temp[0] = spd_PI.Kp_spd;
			temp[1] = spd_PI.Ki_spd;
			temp[2] = rtU.wn_fbk;
			temp[3] = rtU.SpeedRef;
			temp[4] = absPos;
			temp[5] = cur_PI.Kp_cur;
			temp[6] = cur_PI.Ki_cur;
			temp[7] = iq_fb;
			temp[8] = id_fb;
			temp[9] = rtU.Ia;
			temp[10] = rtU.Ib;
			temp[11] = rtU.Ic;
			memcpy(tempData, temp, sizeof(temp));
			HAL_UART_Transmit_DMA(&huart1,(uint8_t *)tempData,sizeof(tempData));
			HAL_UART_Transmit(&huart4, &cmd, 1, 10);
		}
	}

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADCEx_InjectedConvCpltCallback must be implemented in the user file.
  */
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
	if(GPIO_Pin == KEY1_Pin)
	{
		MotorState = !MotorState;
		if(MotorState == 0)
		{
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
			HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
			HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
			HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
		}
		else
		{
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
			HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
			HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
			HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
		}
	}
	
	else if(GPIO_Pin == KEY2_Pin)
	{
		rtU.SpeedRef -= 100;
		if(rtU.SpeedRef <= -3000)
		{
			rtU.SpeedRef = -3000;
		}
	}
		
	else if(GPIO_Pin == KEY3_Pin)
	{
		rtU.SpeedRef += 100;
		if(rtU.SpeedRef >= 3000)
		{
			rtU.SpeedRef = 3200;
		}
	}
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_IC_CaptureCallback could be implemented in the user file
   */
}




void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef * huart, uint16_t Size)
{
    if(huart->Instance == USART1)
    {

//       HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxBuffer_uart1, BUFFER_SIZE_UART1); 
//       HAL_UART_Transmit(&huart1, rxBuffer_uart1, sizeof(rxBuffer_uart1), 10);
//       memset(rxBuffer_uart1, 0, BUFFER_SIZE_UART1);
//			
			 HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxBuffer_uart1, BUFFER_SIZE_UART1); 
//     HAL_UART_Transmit(&huart1, rxBuffer_uart1, sizeof(rxBuffer_uart1), 10);
			 HAL_UART_Transmit_DMA(&huart1, rxBuffer_uart1, sizeof(rxBuffer_uart1));
			 PI_tune(&cur_PI, &spd_PI);	
    }
		
		if(huart->Instance == UART4)
    {
       HAL_UARTEx_ReceiveToIdle_DMA(&huart4, rxBuffer_uart4, BUFFER_SIZE_UART4);
			 absPos = (uint32_T)rxBuffer_uart4[3] << 8 | rxBuffer_uart4[2] | (uint32_T)rxBuffer_uart4[4] << 16;
			 if(absPos >= 131072)
			 {
				 absPos = 131072;
			 }
			 if(absPos <= 0)
			 {
				 absPos = 0;
			 }
//       memset(rxBuffer_uart4, 0, BUFFER_SIZE_UART4);							   
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
