/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "timers.h"
#include "lcd.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define dBounceTime 10
#define DisplayWidth 20
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DAC_HandleTypeDef hdac;

SRAM_HandleTypeDef hsram3;

osThreadId defaultTaskHandle;
osThreadId klawiatura_deboHandle;
osThreadId wyswietlaczHandle;
osMessageQId znakHandle;
osMessageQId symbolHandle;
osMessageQId nHandle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DAC_Init(void);
static void MX_FSMC_Init(void);
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);

/* USER CODE BEGIN PFP */
static void klawiatura_debo(void);
static void klawiatura_debo()
{
uint8_t znak; // czy na pewno moze byc jak go wykorzystujemy jako cyfra 0
uint8_t symbol;
uint8_t klawisz_0;
uint8_t klawisz_1;
uint8_t klawisz_2;
uint8_t klawisz_3;
uint8_t klawisz_4;
uint8_t klawisz_5;
uint8_t klawisz_6;
uint8_t klawisz_7;
uint8_t klawisz_8;
uint8_t klawisz_9;
uint8_t klawisz_UP;
uint8_t klawisz_DOWN;
uint8_t klawisz_ENTER;
uint8_t klawisz_SERWIS;
uint8_t n;

//klawiatura
		if(n==4) n=1;
		for(int i=1;i<5;i++)
	{
		switch (i)
		{
case 1: 	//wiersz 1 R1(W1)
				HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_RESET);
				
			////////////////////////////   0   ////////////////////////////
			switch (klawisz_0)
			{
				case 0: if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_0++; GPIOF->ODR =(klawisz_0<<6); break;
				case 1: if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_0++; else klawisz_0=0;GPIOF->ODR =(klawisz_0<<6) ;break;
				case 2: znak=0; n++; klawisz_0++; GPIOF->ODR =(klawisz_0<<6);
				case 3: if(HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_0++; GPIOF->ODR =(klawisz_0<<6); break;
				case 4: if(HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_0=0; else klawisz_0=3; GPIOF->ODR =(klawisz_0<<6); break;
			}
			////////////////////////////   SERWIS   ////////////////////////////
			switch (klawisz_SERWIS)
			{
				case 0: if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_SERWIS++; break;
				case 1: if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_SERWIS++; else klawisz_SERWIS=0; break;
				case 2: symbol=1; klawisz_SERWIS++;
				case 3: if(HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_SERWIS++; break;
				case 4: if(HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_SERWIS=0; else klawisz_SERWIS=3; break;
			}
				HAL_GPIO_WritePin(w1_GPIO_Port, w1_Pin, GPIO_PIN_SET);
			break;
case 2:		//wiersz 2 R2(W2)
				HAL_GPIO_WritePin(w2_GPIO_Port, w2_Pin, GPIO_PIN_RESET);
			////////////////////////////   1   ////////////////////////////
			switch (klawisz_1)
			{
				case 0: if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_1++; break;
				case 1: if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_1++; else klawisz_1=0; break;
				case 2: znak=1; n++; klawisz_1++;
				case 3: if(HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_1++; break;
				case 4: if(HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_1=0; else klawisz_1=3; break;
			}
			////////////////////////////   2   ////////////////////////////
			switch (klawisz_2)
			{
				case 0: if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_2++; break;
				case 1: if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_2++; else klawisz_2=0; break;
				case 2: znak=2; n++; klawisz_2++;
				case 3: if(HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_2++; break;
				case 4: if(HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_2=0; else klawisz_2=3; break;
			}
			////////////////////////////   3   ////////////////////////////
			switch (klawisz_3)
			{
				case 0: if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_3++; break;
				case 1: if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_3++; else klawisz_3=0; break;
				case 2: znak=3; n++; klawisz_3++;
				case 3: if(HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_3++; break;
				case 4: if(HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_3=0; else klawisz_3=3; break;
			}
			////////////////////////////   ENTER   ////////////////////////////
			switch (klawisz_ENTER)
			{
				case 0: if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_ENTER++; break;
				case 1: if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_ENTER++; else klawisz_ENTER=0; break;
				case 2: symbol=2; klawisz_ENTER++;
				case 3: if(HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_ENTER++; break;
				case 4: if(HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_ENTER=0; else klawisz_ENTER=3; break;
			}
				HAL_GPIO_WritePin(w2_GPIO_Port, w2_Pin, GPIO_PIN_SET);
			break;
case 3:		//wiersz 3 R3(W3)
				HAL_GPIO_WritePin(w3_GPIO_Port, w3_Pin, GPIO_PIN_RESET);
			////////////////////////////   4   ////////////////////////////
			switch (klawisz_4)
			{
				case 0: if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_4++; break;
				case 1: if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_4++; else klawisz_4=0; break;
				case 2: znak=4; n++; klawisz_4++;
				case 3: if(HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_4++; break;
				case 4: if(HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_4=0; else klawisz_4=3; break;
			}
			////////////////////////////   5   ////////////////////////////
			switch (klawisz_5)
			{
				case 0: if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_5++; break;
				case 1: if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_5++; else klawisz_5=0; break;
				case 2: znak=5; n++; klawisz_5++;
				case 3: if(HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_5++; break;
				case 4: if(HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_5=0; else klawisz_5=3; break;
			}
			////////////////////////////   6   ////////////////////////////
			switch (klawisz_6)
			{
				case 0: if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_6++; break;
				case 1: if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_6++; else klawisz_6=0; break;
				case 2: znak=6; n++; klawisz_6++;
				case 3: if(HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_6++; break;
				case 4: if(HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_6=0; else klawisz_6=3; break;
			}
			////////////////////////////   DOWN   ////////////////////////////
			switch (klawisz_DOWN)
			{
				case 0: if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_DOWN++; break;
				case 1: if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_DOWN++; else klawisz_DOWN=0; break;
				case 2: symbol=3; klawisz_DOWN++;
				case 3: if(HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_DOWN++; break;
				case 4: if(HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_DOWN=0; else klawisz_DOWN=3; break;
			}
				HAL_GPIO_WritePin(w3_GPIO_Port, w3_Pin, GPIO_PIN_SET);
			break;
case 4:		//wiersz 4 R4(W4)
				HAL_GPIO_WritePin(w4_GPIO_Port, w4_Pin, GPIO_PIN_RESET);
			////////////////////////////   7   ////////////////////////////
			switch (klawisz_7)
			{
				case 0: if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_7++; break;
				case 1: if(!HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_7++; else klawisz_7=0; break;
				case 2: symbol=7; klawisz_7++;
				case 3: if(HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_7++; break;
				case 4: if(HAL_GPIO_ReadPin(k4_GPIO_Port, k4_Pin)) klawisz_7=0; else klawisz_7=3; break;
			}
			////////////////////////////   8   ////////////////////////////
			switch (klawisz_8)
			{
				case 0: if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_8++; break;
				case 1: if(!HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_8++; else klawisz_8=0; break;
				case 2: znak=8; n++; klawisz_8++;
				case 3: if(HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_8++; break;
				case 4: if(HAL_GPIO_ReadPin(k3_GPIO_Port, k3_Pin)) klawisz_8=0; else klawisz_8=3; break;
			}
			////////////////////////////   9   ////////////////////////////
			switch (klawisz_9)
			{
				case 0: if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_9++; break;
				case 1: if(!HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_9++; else klawisz_9=0; break;
				case 2: znak=9; klawisz_9++;
				case 3: if(HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_9++; break;
				case 4: if(HAL_GPIO_ReadPin(k2_GPIO_Port, k2_Pin)) klawisz_9=0; else klawisz_9=3; break;
			}
			////////////////////////////   UP   ////////////////////////////
			switch (klawisz_UP)
			{
				case 0: if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_UP++; break;
				case 1: if(!HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_UP++; else klawisz_UP=0; break;
				case 2: symbol=4; klawisz_UP++;
				case 3: if(HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_UP++; break;
				case 4: if(HAL_GPIO_ReadPin(k1_GPIO_Port, k1_Pin)) klawisz_UP=0; else klawisz_UP=3; break;
			}
				HAL_GPIO_WritePin(w4_GPIO_Port, w4_Pin, GPIO_PIN_SET);
			break;
		}
	}
	xQueueSend(znakHandle,&znak,0);
	xQueueSend(symbolHandle,&symbol,0);
	xQueueSend(nHandle,&n,0);

	
	uint8_t n_display [DisplayWidth];
	uint8_t symbol_display [DisplayWidth];
	uint8_t znak_display [DisplayWidth];
		
		LCD_SetBackColor(Black);
		LCD_SetTextColor(Green);
				
		snprintf((char *)n_display, DisplayWidth, "   %d   ", n);
		LCD_DisplayStringLine(Line2, n_display);
		
		snprintf((char *)symbol_display, DisplayWidth, "   %d   ", symbol);
		LCD_DisplayStringLine(Line4, symbol_display);
		
		snprintf((char *)znak_display, DisplayWidth, "   %d   ", znak);
		LCD_DisplayStringLine(Line6, znak_display);
		
		vTaskDelay(dBounceTime/portTICK_PERIOD_MS);
	}
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
  MX_DAC_Init();
  MX_FSMC_Init();
  /* USER CODE BEGIN 2 */
STM3210E_LCD_Init();
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
	
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of znak */
  osMessageQDef(znak, 1, uint8_t);
  znakHandle = osMessageCreate(osMessageQ(znak), NULL);

  /* definition and creation of symbol */
  osMessageQDef(symbol, 1, uint8_t);
  symbolHandle = osMessageCreate(osMessageQ(symbol), NULL);

  /* definition and creation of n */
  osMessageQDef(n, 1, uint8_t);
  nHandle = osMessageCreate(osMessageQ(n), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of klawiatura_debo */
  osThreadDef(klawiatura_debo, StartTask02, osPriorityHigh, 0, 128);
  klawiatura_deboHandle = osThreadCreate(osThread(klawiatura_debo), NULL);

  /* definition and creation of wyswietlacz */
  osThreadDef(wyswietlacz, StartTask03, osPriorityHigh, 0, 128);
  wyswietlaczHandle = osThreadCreate(osThread(wyswietlacz), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */

  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, w1_Pin|w2_Pin|w3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, w4_Pin|LED1_Pin|LED2_Pin|LED3_Pin
                          |LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : w1_Pin w2_Pin w3_Pin */
  GPIO_InitStruct.Pin = w1_Pin|w2_Pin|w3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : k1_Pin k2_Pin */
  GPIO_InitStruct.Pin = k1_Pin|k2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : k3_Pin k4_Pin */
  GPIO_InitStruct.Pin = k3_Pin|k4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : w4_Pin */
  GPIO_InitStruct.Pin = w4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(w4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin LED4_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : Relay_Pin */
  GPIO_InitStruct.Pin = Relay_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Relay_GPIO_Port, &GPIO_InitStruct);

}

/* FSMC initialization function */
static void MX_FSMC_Init(void)
{

  /* USER CODE BEGIN FSMC_Init 0 */

  /* USER CODE END FSMC_Init 0 */

  FSMC_NORSRAM_TimingTypeDef Timing = {0};

  /* USER CODE BEGIN FSMC_Init 1 */

  /* USER CODE END FSMC_Init 1 */

  /** Perform the SRAM3 memory initialization sequence
  */
  hsram3.Instance = FSMC_NORSRAM_DEVICE;
  hsram3.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram3.Init */
  hsram3.Init.NSBank = FSMC_NORSRAM_BANK4;
  hsram3.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram3.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram3.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram3.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram3.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram3.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram3.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram3.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram3.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram3.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  hsram3.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram3.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 15;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 255;
  Timing.BusTurnAroundDuration = 15;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram3, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Disconnect NADV
  */

  __HAL_AFIO_FSMCNADV_DISCONNECTED();

  /* USER CODE BEGIN FSMC_Init 2 */

  /* USER CODE END FSMC_Init 2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the klawiatura_debo thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
		klawiatura_debo();
    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the wyswietlacz thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
//	uint8_t n_display [DisplayWidth];
//	uint8_t symbol_display [DisplayWidth];
//	uint8_t znak_display [DisplayWidth];
//	
//	uint8_t n_queue;
//	uint8_t symbol_queue;
//	uint8_t znak_queue;
//  /* Infinite loop */
  for(;;)
  {
//		
//	xQueueReceive(nHandle,&n_queue,0);
//	xQueueReceive(znakHandle,&znak_queue,0);	
//	xQueueReceive(symbolHandle,&symbol_queue,0);	
//		
//		LCD_SetBackColor(Black);
//		LCD_SetTextColor(Green);
//				
//		snprintf((char *)n_display, DisplayWidth, "   %d   ", n_queue);
//		LCD_DisplayStringLine(Line2, n_display);
//		
//		snprintf((char *)symbol_display, DisplayWidth, "   %d   ", symbol_queue);
//		LCD_DisplayStringLine(Line4, symbol_display);
//		
//		snprintf((char *)znak_display, DisplayWidth, "   %d   ", znak_queue);
//		LCD_DisplayStringLine(Line6, znak_display);
//		
    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

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
