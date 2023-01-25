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
extern uint8_t znak;
extern uint8_t symbol;
extern uint8_t klawisz_0;
extern uint8_t klawisz_1;
extern uint8_t klawisz_2;
extern uint8_t klawisz_3;
extern uint8_t klawisz_4;
extern uint8_t klawisz_5;
extern uint8_t klawisz_6;
extern uint8_t klawisz_7;
extern uint8_t klawisz_8;
extern uint8_t klawisz_9;
extern uint8_t klawisz_G;
extern uint8_t klawisz_K;
extern uint8_t klawisz_A;
extern uint8_t klawisz_B;
extern uint8_t klawisz_C;
extern uint8_t klawisz_D;
extern uint8_t n;
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
  /* USER CODE END TIM6_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_IRQn 1 */
	HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_RESET);
	if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) GPIOF->ODR ^= (1<<6);
	HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(w2_GPIO_Port, w2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(w3_GPIO_Port, w3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(w4_GPIO_Port, w4_Pin, GPIO_PIN_RESET);
	if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin) || !HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin) || !HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin) || !HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin))
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
				if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) znak=1;
				if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) znak=2;
				if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) znak=3;
				if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) znak=4;
				break;
				case 1:
				HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w2_GPIO_Port, w2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(w3_GPIO_Port, w3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w4_GPIO_Port, w4_Pin, GPIO_PIN_SET);
				if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) znak=5;
				if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) znak=6;
				if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) znak=7;
				if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) znak=8;
				break;
				case 2:
				HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w2_GPIO_Port, w2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w3_GPIO_Port, w3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(w4_GPIO_Port, w4_Pin, GPIO_PIN_SET);
				if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) znak=9;
				if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) znak=10;
				if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) znak=11;
				if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) znak=12;
				break;
				case 3:
				HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w2_GPIO_Port, w2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w3_GPIO_Port, w3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(w4_GPIO_Port, w4_Pin, GPIO_PIN_RESET);
				if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) znak=13;
				if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) znak=14;
				if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) znak=15;
				if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) znak=16;
				break;
			}

		}
			n=0;
	}
}

  /* USER CODE END TIM6_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
