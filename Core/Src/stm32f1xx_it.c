/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
#include "FreeRTOS.h"
#include "task.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "stdio.h"
#include "cmsis_os.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t znak;
uint8_t n;
extern osSemaphoreId znak_licznikHandle;
extern osMessageQId PIN_znakHandle;
extern osSemaphoreId EnterHandle;
extern osSemaphoreId SERWISHandle;
extern osSemaphoreId alarmHandle;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim6;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
#endif /* INCLUDE_xTaskGetSchedulerState */
  xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  }
#endif /* INCLUDE_xTaskGetSchedulerState */
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM6 global interrupt.
  */
void TIM6_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_IRQn 0 */
	BaseType_t xHigherPriorityTaskWoken;
  /* USER CODE END TIM6_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_IRQn 1 */
	HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(w2_GPIO_Port, w2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(w3_GPIO_Port, w3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(w4_GPIO_Port, w4_Pin, GPIO_PIN_RESET);
	if((n<2) &&(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin) || !HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin) || !HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin) || !HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)))
	{
		n++;
		if(n==2)
		{
			for(uint8_t i=0; i<4; i++) {
			switch(i) {
				case 0:
				HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(w2_GPIO_Port, w2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w3_GPIO_Port, w3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w4_GPIO_Port, w4_Pin, GPIO_PIN_SET);
				if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) {
					//znak=10; ENTER
					n++;
					xSemaphoreGiveFromISR(EnterHandle, &xHigherPriorityTaskWoken);
			}
				if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)){
					n++;
				}
				if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)){
					znak=0;
					xSemaphoreGiveFromISR( znak_licznikHandle, &xHigherPriorityTaskWoken);
					n++;
								xQueueSendToFrontFromISR( PIN_znakHandle, &znak, NULL);
				}
				if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)){
					//SERWIS
					xSemaphoreGiveFromISR( SERWISHandle, &xHigherPriorityTaskWoken);
					n++;
				}
				break;
				case 1:
				HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w2_GPIO_Port, w2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(w3_GPIO_Port, w3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w4_GPIO_Port, w4_Pin, GPIO_PIN_SET);
				if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)){
					n++;
				}
				if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)){
					znak=3;
					xSemaphoreGiveFromISR( znak_licznikHandle, &xHigherPriorityTaskWoken);
					n++;
								xQueueSendToFrontFromISR( PIN_znakHandle, &znak, NULL);
				}
				if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)){
					znak=2;
					xSemaphoreGiveFromISR( znak_licznikHandle, &xHigherPriorityTaskWoken);
					n++;
								xQueueSendToFrontFromISR( PIN_znakHandle, &znak, NULL);
				}
				if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)){
					znak=1;
					xSemaphoreGiveFromISR( znak_licznikHandle, &xHigherPriorityTaskWoken);
					n++;
								xQueueSendToFrontFromISR( PIN_znakHandle, &znak, NULL);

				}
				break;
				case 2:
				HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w2_GPIO_Port, w2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w3_GPIO_Port, w3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(w4_GPIO_Port, w4_Pin, GPIO_PIN_SET);
				if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)){
					n++;
				}
				if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)){
					znak=6;
					xSemaphoreGiveFromISR( znak_licznikHandle, &xHigherPriorityTaskWoken);
					n++;
								xQueueSendToFrontFromISR( PIN_znakHandle, &znak, NULL);
				}
				if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)){
					znak=5;
					xSemaphoreGiveFromISR( znak_licznikHandle, &xHigherPriorityTaskWoken);
					n++;
								xQueueSendToFrontFromISR( PIN_znakHandle, &znak, NULL);
				}
				if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)){
					znak=4;
					xSemaphoreGiveFromISR( znak_licznikHandle, &xHigherPriorityTaskWoken);
					n++;
								xQueueSendToFrontFromISR( PIN_znakHandle, &znak, NULL);
				}
				break;
				case 3:
				HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w2_GPIO_Port, w2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w3_GPIO_Port, w3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w4_GPIO_Port, w4_Pin, GPIO_PIN_RESET);
				if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)){
					n++;
				}
				if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)){
					znak=9;
					xSemaphoreGiveFromISR( znak_licznikHandle, &xHigherPriorityTaskWoken);
					n++;
								xQueueSendToFrontFromISR( PIN_znakHandle, &znak, NULL);
				}
				if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)){
					znak=8;
					xSemaphoreGiveFromISR( znak_licznikHandle, &xHigherPriorityTaskWoken);
					n++;
								xQueueSendToFrontFromISR( PIN_znakHandle, &znak, NULL);
				}
				if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)){
					znak=7;
					xSemaphoreGiveFromISR( znak_licznikHandle, &xHigherPriorityTaskWoken);
					n++;
								xQueueSendToFrontFromISR( PIN_znakHandle, &znak, NULL);
				}
				break;
			}

		}
	}
}
	else if( HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin) && HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin) && HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin) && HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin))
	switch(n){
		case 1:
			n=0;
		break;
		case 3:
			n++;
		break;
		case 4:
			n=0;
		break;
	}
  /* USER CODE END TIM6_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
