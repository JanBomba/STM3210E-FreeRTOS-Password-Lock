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
#define dBounceTime  10
#define DisplayWidth 20
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DAC_HandleTypeDef hdac;

TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

SRAM_HandleTypeDef hsram3;

osThreadId defaultTaskHandle;
osThreadId wyswietlanieHandle;
osThreadId zarzadcaHandle;
osThreadId peryferiaHandle;
osThreadId serwisHandle;
osMessageQId PIN_znakHandle;
osSemaphoreId znak_licznikHandle;
osSemaphoreId PIN_completedHandle;
osSemaphoreId EnterHandle;
osSemaphoreId SERWISHandle;
osSemaphoreId PIN_tooShortHandle;
osSemaphoreId alarmHandle;
osSemaphoreId PIN_correctHandle;
/* USER CODE BEGIN PV */
osMessageQId PINHandle;
volatile uint8_t znak=0;
volatile uint8_t symbol=99;
volatile uint8_t klawisz_0=0;
volatile uint8_t klawisz_1=0;
volatile uint8_t klawisz_2=0;
volatile uint8_t klawisz_3=0;
volatile uint8_t klawisz_4=0;
volatile uint8_t klawisz_5=0;
volatile uint8_t klawisz_6=0;
volatile uint8_t klawisz_7=0;
volatile uint8_t klawisz_8=0;
volatile uint8_t klawisz_9=0;
volatile uint8_t klawisz_A=0;
volatile uint8_t klawisz_B=0;
volatile uint8_t klawisz_C=0;
volatile uint8_t klawisz_D=0;
volatile uint8_t klawisz_K=0;
volatile uint8_t klawisz_G=0;
volatile uint8_t n=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DAC_Init(void);
static void MX_FSMC_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
void StartTask04(void const * argument);
void StartTask05(void const * argument);

/* USER CODE BEGIN PFP */
void Def_LCD (void);
void Def_LCD () {
	uint8_t pin_disp [20] = "PIN: ";
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(Green);
	LCD_DisplayStringLine(Line5, pin_disp);
}

void Correct_LCD (void);
void Correct_LCD (){
	uint8_t PIN_correct1[20] = "    PIN POPRAWNY    ";
	uint8_t PIN_correct2[20] = "                    ";
	uint8_t PIN_correct3[20] = "               /    ";
	uint8_t PIN_correct4[20] = "              /     ";
	uint8_t PIN_correct5[20] = "             /      ";
	uint8_t PIN_correct6[20] = "         \\  /       ";
	uint8_t PIN_correct7[20] = "          \\/        ";
	
	LCD_Clear(Green);
	LCD_SetBackColor(Green);
	LCD_SetTextColor(White);
	LCD_DisplayStringLine(Line1, PIN_correct1);
	LCD_DisplayStringLine(Line2, PIN_correct2);
	LCD_DisplayStringLine(Line3, PIN_correct3);
	LCD_DisplayStringLine(Line4, PIN_correct4);
	LCD_DisplayStringLine(Line5, PIN_correct5);
	LCD_DisplayStringLine(Line6, PIN_correct6);
	LCD_DisplayStringLine(Line7, PIN_correct7);
}

void Incorrect_LCD (void);
void Incorrect_LCD (){
	uint8_t PIN_wrong1[20] = "   PIN NIEPOPRAWNY  ";
	uint8_t PIN_wrong2[20] = "                    ";
	uint8_t PIN_wrong3[20] = "       \\    /       ";
	uint8_t PIN_wrong4[20] = "        \\  /        ";
	uint8_t PIN_wrong5[20] = "         \\/         ";
	uint8_t PIN_wrong6[20] = "         /\\         ";
	uint8_t PIN_wrong7[20] = "        /  \\        ";
	uint8_t PIN_wrong8[20] = "       /    \\       ";
	
	LCD_Clear(Red);
	LCD_SetBackColor(Red);
	LCD_SetTextColor(White);
	LCD_DisplayStringLine(Line1, PIN_wrong1);
	LCD_DisplayStringLine(Line2, PIN_wrong2);
	LCD_DisplayStringLine(Line3, PIN_wrong3);
	LCD_DisplayStringLine(Line4, PIN_wrong4);
	LCD_DisplayStringLine(Line5, PIN_wrong5);
	LCD_DisplayStringLine(Line6, PIN_wrong6);
	LCD_DisplayStringLine(Line7, PIN_wrong7);
	LCD_DisplayStringLine(Line8, PIN_wrong8);
}

void Serwis_Def_LCD (void);
void Serwis_Def_LCD () {
	uint8_t serwis_disp[20] = "Podaj PIN serwisowy";
	
	LCD_Clear(Yellow);
	LCD_SetBackColor(Red);
	LCD_SetTextColor(White);
	LCD_DisplayStringLine(Line0, serwis_disp);
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
  MX_TIM6_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
	STM3210E_LCD_Init();
	LCD_SetBackColor(Black);
	LCD_SetTextColor(Green);
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start(&htim6);
//	HAL_TIM_Base_Start_IT(&htim7);
//	HAL_TIM_Base_Start(&htim7);
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of znak_licznik */
  osSemaphoreDef(znak_licznik);
  znak_licznikHandle = osSemaphoreCreate(osSemaphore(znak_licznik), 1);

  /* definition and creation of PIN_completed */
  osSemaphoreDef(PIN_completed);
  PIN_completedHandle = osSemaphoreCreate(osSemaphore(PIN_completed), 1);

  /* definition and creation of Enter */
  osSemaphoreDef(Enter);
  EnterHandle = osSemaphoreCreate(osSemaphore(Enter), 1);

  /* definition and creation of SERWIS */
  osSemaphoreDef(SERWIS);
  SERWISHandle = osSemaphoreCreate(osSemaphore(SERWIS), 1);

  /* definition and creation of PIN_tooShort */
  osSemaphoreDef(PIN_tooShort);
  PIN_tooShortHandle = osSemaphoreCreate(osSemaphore(PIN_tooShort), 1);

  /* definition and creation of alarm */
  osSemaphoreDef(alarm);
  alarmHandle = osSemaphoreCreate(osSemaphore(alarm), 1);

  /* definition and creation of PIN_correct */
  osSemaphoreDef(PIN_correct);
  PIN_correctHandle = osSemaphoreCreate(osSemaphore(PIN_correct), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of PIN_znak */
  osMessageQDef(PIN_znak, 1, uint8_t);
  PIN_znakHandle = osMessageCreate(osMessageQ(PIN_znak), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
	xSemaphoreTake(EnterHandle, NULL);
	xSemaphoreTake(PIN_tooShortHandle, NULL);
	xSemaphoreTake(alarmHandle, NULL);
	xSemaphoreTake( SERWISHandle, NULL );
	
	osMessageQDef(PIN, 2, 4*sizeof(uint8_t));
	PINHandle = osMessageCreate(osMessageQ(PIN), NULL);
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of wyswietlanie */
  osThreadDef(wyswietlanie, StartTask02, osPriorityHigh, 0, 128);
  wyswietlanieHandle = osThreadCreate(osThread(wyswietlanie), NULL);

  /* definition and creation of zarzadca */
  osThreadDef(zarzadca, StartTask03, osPriorityIdle, 0, 128);
  zarzadcaHandle = osThreadCreate(osThread(zarzadca), NULL);

  /* definition and creation of peryferia */
  osThreadDef(peryferia, StartTask04, osPriorityIdle, 0, 128);
  peryferiaHandle = osThreadCreate(osThread(peryferia), NULL);

  /* definition and creation of serwis */
  osThreadDef(serwis, StartTask05, osPriorityIdle, 0, 128);
  serwisHandle = osThreadCreate(osThread(serwis), NULL);

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
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 9;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 7999;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 0;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 62;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

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
  Timing.AddressSetupTime = 0;
  Timing.AddressHoldTime = 0;
  Timing.DataSetupTime = 2;
  Timing.BusTurnAroundDuration = 0;
  Timing.CLKDivision = 0;
  Timing.DataLatency = 0;
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
	uint8_t i=0;
	uint8_t i_disp[20];
	uint8_t PIN_disp[20];
	uint8_t symbol_disp [20];
	uint8_t PIN[4];
	uint8_t pin_disp [20] = "PIN: ";
	Def_LCD();
//	uint8_t znak_disp [20];
//	uint8_t n_disp [20];
//  /* Infinite loop */
for(;;)
{
	sprintf( (char *)symbol_disp, "znak: %d ", znak);
	LCD_DisplayStringLine(Line1, symbol_disp);
	if( znak_licznikHandle != NULL )
    {
			if( xSemaphoreTake( znak_licznikHandle, NULL ) == pdTRUE )
        {
					//GPIOF->ODR ^= (1<<6);
					if (i==5)	xSemaphoreTake(PIN_completedHandle, NULL);
					if(i!=0 && i<5)	LCD_DisplayChar(Line5, 250-20*i, '*');
					xQueueReceive(PIN_znakHandle, &PIN[i-1], NULL);
					i++;
					sprintf( (char *)i_disp, "i: %d ", i);
					LCD_DisplayStringLine(Line2, i_disp);
					}
				}
		if( EnterHandle != NULL )
							{
								if( xSemaphoreTake( EnterHandle, NULL ) == pdTRUE )
									{
										if(i>=5) {
										LCD_ClearLine(Line5);
										LCD_DisplayStringLine(Line5, pin_disp);
										sprintf( (char*)PIN_disp,"PIN: %d %d %d %d", PIN[0], PIN[1], PIN[2], PIN[3]);
										LCD_DisplayStringLine(Line3, PIN_disp);
										xSemaphoreGive(PIN_completedHandle);
										xQueueSend(PINHandle, PIN, NULL);
										i=1;
										xSemaphoreGive(PIN_tooShortHandle);
											}
										else {
										LCD_ClearLine(Line5);
										LCD_DisplayStringLine(Line5, pin_disp);
										xSemaphoreTake(PIN_tooShortHandle, NULL);
										i=1;
										}
									}
								}
    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the zarzadca thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
	uint8_t PIN_mem[4] = {0, 1, 2, 3};
	uint8_t PIN_read[4];
	uint8_t PIN_correct1[20] = "    PIN POPRAWNY    ";
	uint8_t PIN_correct2[20] = "                    ";
	uint8_t PIN_correct3[20] = "               /    ";
	uint8_t PIN_correct4[20] = "              /     ";
	uint8_t PIN_correct5[20] = "             /      ";
	uint8_t PIN_correct6[20] = "         \\  /       ";
	uint8_t PIN_correct7[20] = "          \\/        ";
	uint8_t correct=0;
	uint8_t kolejka_disp[20];
	uint8_t PIN_wrong1[20] = "   PIN NIEPOPRAWNY  ";
	uint8_t PIN_wrong2[20] = "                    ";
	uint8_t PIN_wrong3[20] = "       \\    /       ";
	uint8_t PIN_wrong4[20] = "        \\  /        ";
	uint8_t PIN_wrong5[20] = "         \\/         ";
	uint8_t PIN_wrong6[20] = "         /\\         ";
	uint8_t PIN_wrong7[20] = "        /  \\        ";
	uint8_t PIN_wrong8[20] = "       /    \\       ";
	uint8_t alarm_cnt=0;
	uint8_t alarm_cnt_disp[20];
	uint8_t alarm_disp[20] = "    ALARM!!!!!!     ";
	uint8_t alarm_disp_cnt =0;
  /* Infinite loop */
  for(;;)
  {
		if( alarmHandle != NULL )
						{
							if( xSemaphoreTake( alarmHandle, NULL ) == pdTRUE ){
								vTaskSuspend(wyswietlanieHandle);
								if(!(alarm_disp_cnt&1)){
									LCD_Clear(Black);
									LCD_SetBackColor(Black);
									LCD_SetTextColor(Red);
									LCD_DisplayStringLine(Line5, alarm_disp);
								}
								else {
									LCD_Clear(Red);
									LCD_SetBackColor(Red);
									LCD_SetTextColor(White);
									LCD_DisplayStringLine(Line5, alarm_disp);
								}
								alarm_disp_cnt++;
								xSemaphoreGive(alarmHandle);
								vTaskDelay(100);
							}
							else if( PIN_tooShortHandle != NULL )
							{
								if( xSemaphoreTake( PIN_tooShortHandle, NULL ) == pdTRUE ){
									xQueueReceive(PINHandle, PIN_read, 0);
									sprintf( (char *) kolejka_disp, "kolejka: %d %d %d %d", PIN_read[0], PIN_read[1], PIN_read[2], PIN_read[3]);
									LCD_DisplayStringLine(Line9, kolejka_disp);
									for(uint8_t i=0; i<4; i++)
										if(PIN_mem[i] == PIN_read[i]) correct++;
									if(correct == 4){
										LCD_Clear(Green);
										LCD_SetBackColor(Green);
										LCD_SetTextColor(White);
										LCD_DisplayStringLine(Line1, PIN_correct1);
										LCD_DisplayStringLine(Line2, PIN_correct2);
										LCD_DisplayStringLine(Line3, PIN_correct3);
										LCD_DisplayStringLine(Line4, PIN_correct4);
										LCD_DisplayStringLine(Line5, PIN_correct5);
										LCD_DisplayStringLine(Line6, PIN_correct6);
										LCD_DisplayStringLine(Line7, PIN_correct7);
										correct=0;
										alarm_cnt=0;
										HAL_Delay(3000);
										Def_LCD();
								}
									else{
										LCD_Clear(Red);
										LCD_SetBackColor(Red);
										LCD_SetTextColor(White);
										LCD_DisplayStringLine(Line1, PIN_wrong1);
										LCD_DisplayStringLine(Line2, PIN_wrong2);
										LCD_DisplayStringLine(Line3, PIN_wrong3);
										LCD_DisplayStringLine(Line4, PIN_wrong4);
										LCD_DisplayStringLine(Line5, PIN_wrong5);
										LCD_DisplayStringLine(Line6, PIN_wrong6);
										LCD_DisplayStringLine(Line7, PIN_wrong7);
										LCD_DisplayStringLine(Line8, PIN_wrong8);
										correct=0;
										alarm_cnt++;
										if(alarm_cnt == 3){
											xSemaphoreGive(alarmHandle);
											alarm_cnt=0;
										}else {
										sprintf(( char*) alarm_cnt_disp, "Pozostalo prob: %d", 3-alarm_cnt);
										LCD_DisplayStringLine(Line9, alarm_cnt_disp);
										}
										HAL_Delay(3000);
										Def_LCD();
									}
							}
							}	
						}		
						
    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the pamiec thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void const * argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  for(;;)
  {
		
    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the peryferia thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void const * argument)
{
  /* USER CODE BEGIN StartTask05 */
//	uint8_t serwis_disp[20] = "Podaj PIN serwisowy";
	uint8_t queue_disp[20];
	uint8_t PIN_read[4];
	uint8_t PIN_serv[4] = {7, 8, 9, 0};
	uint8_t correct;
	uint8_t i;
  /* Infinite loop */
  for(;;)
  {
		if( SERWISHandle != NULL)
									{
										if( xSemaphoreTake( SERWISHandle, NULL ) == pdTRUE ){
											xSemaphoreGive(SERWISHandle);
											if(!i){
													vTaskSuspend(zarzadcaHandle);
													Serwis_Def_LCD();
													vTaskResume(wyswietlanieHandle);
													i++;
											}
											if( PIN_tooShortHandle != NULL )
											{
												if( xSemaphoreTake( PIN_tooShortHandle, NULL ) == pdTRUE ){
													xQueueReceive(PINHandle, PIN_read, 0);
													sprintf( (char *) queue_disp, "kolejka: %d %d %d %d", PIN_read[0], PIN_read[1], PIN_read[2], PIN_read[3]);
													LCD_DisplayStringLine(Line9, queue_disp);
													for(uint8_t i=0; i<4; i++)
														if(PIN_serv[i] == PIN_read[i]) correct++;
													if(correct == 4){
														Correct_LCD();
														correct=0;
														i=0;
														HAL_Delay(3000);
														Def_LCD();
														xSemaphoreTake(alarmHandle, NULL);
														xSemaphoreTake( SERWISHandle, NULL );
														vTaskResume(zarzadcaHandle);
											}	else {
														Incorrect_LCD();
														correct=0;
														HAL_Delay(5000);
														Serwis_Def_LCD();
												}
										}
									}
								}
							}
    osDelay(1);
  }
  /* USER CODE END StartTask05 */
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
