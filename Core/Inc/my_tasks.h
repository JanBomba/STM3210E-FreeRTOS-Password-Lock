/**@file my_tasks.h  
*/
#include "main.h"
#include "cmsis_os.h"
#include "lcd.h"
#include "stdio.h"
#include "display_command.h"

#define AccessTime 3000

void StartTask02(void const * argument);
void StartTask03(void const * argument);
void StartTask04(void const * argument);
void StartTask05(void const * argument);
