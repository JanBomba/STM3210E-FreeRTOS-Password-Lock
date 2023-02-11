#include "my_tasks.h"

#define alarm_disp "    ALARM!!!!!!     "

extern osThreadId defaultTaskHandle;
extern osThreadId wyswietlanieHandle;
extern osThreadId zarzadcaHandle;
extern osThreadId peryferiaHandle;
extern osThreadId serwisHandle;
extern osMessageQId PIN_znakHandle;
extern osSemaphoreId znak_licznikHandle;
extern osSemaphoreId EnterHandle;
extern osSemaphoreId SERWISHandle;
extern osSemaphoreId PIN_tooShortHandle;
extern osSemaphoreId alarmHandle;
extern osSemaphoreId PIN_correctHandle;
extern osMessageQId PINHandle;

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the klawiatura_debo thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */

/**
*<pre>
*void Start Task02();
*</pre>
*
*\brief Zadanie wyswietlacz
*
*Odpowiedzialne za:
*wyswietlanie gwiazdek na wyswietlaczu w momencie wpisywania pojedynczej cyfry PINU
*odbiera dane z przerwania, magazynuje w buforze i wysyla do zarzadcy
*podlicza ilosc wpisanych cyfr
*sprawdza dlugosc hasla
*/
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
	uint8_t i=0;
	uint8_t PIN[4];
	Def_LCD();
//  /* Infinite loop */
for(;;)
{
	if( znak_licznikHandle != NULL )
    {
			if( xSemaphoreTake( znak_licznikHandle, NULL ) == pdTRUE )
        {
					if(i!=0 && i<5)	LCD_DisplayChar(Line5, 250-20*i, '*');
					xQueueReceive(PIN_znakHandle, &PIN[i-1], NULL);
					i++;
					}
				}
		if( EnterHandle != NULL )
							{
								if( xSemaphoreTake( EnterHandle, NULL ) == pdTRUE )
									{
										if(i>=5) {
										PIN_LCD();
										xQueueSend(PINHandle, PIN, NULL);
										i=1;
										xSemaphoreGive(PIN_tooShortHandle);
											}
										else {

										PIN_LCD();
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
/**
*<pre>
*void Start Task03();
*</pre>
*
*\brief Zadanie zarzadca
*
*/
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
	uint8_t PIN_mem[4] = {0, 1, 2, 3};
	uint8_t PIN_read[4];
	uint8_t correct=0;
	uint8_t alarm_cnt=0;
	uint8_t alarm_cnt_disp[20];
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
									LCD_DisplayStringLine(Line5, (uint8_t*)alarm_disp);
								}
								else {
									LCD_Clear(Red);
									LCD_SetBackColor(Red);
									LCD_SetTextColor(White);
									LCD_DisplayStringLine(Line5, (uint8_t*)alarm_disp);
								}
								alarm_disp_cnt++;
								xSemaphoreGive(alarmHandle);
								vTaskDelay(100);
							}
							else if( PIN_tooShortHandle != NULL )
							{
								if( xSemaphoreTake( PIN_tooShortHandle, NULL ) == pdTRUE ){
									xQueueReceive(PINHandle, PIN_read, 0);
									for(uint8_t i=0; i<4; i++)
										if(PIN_mem[i] == PIN_read[i]) correct++;
									if(correct == 4){
										vTaskSuspend(wyswietlanieHandle);
										Correct_LCD();
										xSemaphoreGive(PIN_correctHandle);
										correct=0;
										alarm_cnt=0;
										vTaskDelay(AccessTime/portTICK_PERIOD_MS);
										vTaskResume(wyswietlanieHandle);
										Def_LCD();
								}
									else{
										vTaskSuspend(wyswietlanieHandle);
										Incorrect_LCD();
										correct=0;
										alarm_cnt++;
										if(alarm_cnt == 3){
											xSemaphoreGive(alarmHandle);
											alarm_cnt=0;
										}else {
										sprintf(( char*) alarm_cnt_disp, "Pozostalo prob: %d", 3-alarm_cnt);
										LCD_DisplayStringLine(Line9, alarm_cnt_disp);
										}
										vTaskDelay(AccessTime/portTICK_PERIOD_MS);
										vTaskResume(wyswietlanieHandle);
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
* @brief Function implementing the peryferia thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
/**
*<pre>
*void Start Task04();
*</pre>
*
*\brief Zadanie peryferia
*
*/
void StartTask04(void const * argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */

	for(;;)
  {
		if( alarmHandle != NULL )
						{
							if( xSemaphoreTake( alarmHandle, NULL ) == pdTRUE ){
								Buzzer_GPIO_Port->ODR |= (1<<5);
								xSemaphoreGive(alarmHandle);
							}
							else
								Buzzer_GPIO_Port->ODR &= ~(1<<5);
						}
		if( PIN_correctHandle != NULL )
						{
							if( xSemaphoreTake( PIN_correctHandle, NULL ) == pdTRUE ){
								Relay_GPIO_Port->ODR &= ~(1<<4);
								vTaskDelay(AccessTime/portTICK_PERIOD_MS);
								Relay_GPIO_Port->ODR |= (1<<4);
							}
						}
    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the serwis thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
/**
*<pre>
*void Start Task05();
*</pre>
*
*\brief Zadanie serwis
*
*/

void StartTask05(void const * argument)
{
  /* USER CODE BEGIN StartTask05 */
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
													PIN_LCD();
													vTaskResume(wyswietlanieHandle);
													i++;
											}
											if( PIN_tooShortHandle != NULL )
											{
												if( xSemaphoreTake( PIN_tooShortHandle, NULL ) == pdTRUE ){
													xQueueReceive(PINHandle, PIN_read, 0);
													for(uint8_t i=0; i<4; i++)
														if(PIN_serv[i] == PIN_read[i]) correct++;
													if(correct == 4){
														vTaskSuspend(wyswietlanieHandle);
														Correct_LCD();
														correct=0;
														i=0;
														vTaskDelay(AccessTime/portTICK_PERIOD_MS);
														vTaskResume(wyswietlanieHandle);
														Def_LCD();
														xSemaphoreTake(alarmHandle, NULL);
														xSemaphoreTake( SERWISHandle, NULL );
														vTaskResume(zarzadcaHandle);
											}	else {
														vTaskSuspend(wyswietlanieHandle);
														Incorrect_LCD();
														correct=0;
														vTaskDelay(AccessTime/portTICK_PERIOD_MS);
														vTaskResume(wyswietlanieHandle);
														Serwis_Def_LCD();
														PIN_LCD();
												}
										}
									}
								}
							}
    osDelay(1);
  }
  /* USER CODE END StartTask05 */
}
