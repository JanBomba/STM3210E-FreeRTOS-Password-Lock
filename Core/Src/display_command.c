#include "display_command.h"

#define Title "<<<ZAMEK SZYFROWY>>>"

#define PIN_correct1 "    PIN POPRAWNY    "
#define PIN_correct2 "                    "
#define PIN_correct3 "               /    "
#define PIN_correct4 "              /     "
#define PIN_correct5 "             /      "
#define PIN_correct6 "         \\  /       "
#define PIN_correct7 "          \\/        "
	
#define PIN_wrong1 "   PIN NIEPOPRAWNY  "
#define PIN_wrong2 "                    "
#define PIN_wrong3 "       \\    /       "
#define PIN_wrong4 "        \\  /        "
#define PIN_wrong5 "         \\/         "
#define PIN_wrong6 "         /\\         "
#define PIN_wrong7 "        /  \\        "
#define PIN_wrong8 "       /    \\       "

#define pin_disp "PIN: "

#define serwis_disp "Podaj PIN serwisowy"

void Def_LCD () {
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(Green);
	LCD_DisplayStringLine(Line0, (uint8_t*)Title);
	LCD_DisplayStringLine(Line5, (uint8_t*)pin_disp);
}

void PIN_LCD () {
	LCD_ClearLine(Line5);
	LCD_DisplayStringLine(Line5, (uint8_t*)pin_disp);
}

void Correct_LCD (){
	LCD_Clear(Green);
	LCD_SetBackColor(Green);
	LCD_SetTextColor(White);
	LCD_DisplayStringLine(Line1, (uint8_t*)PIN_correct1);
	LCD_DisplayStringLine(Line2, (uint8_t*)PIN_correct2);
	LCD_DisplayStringLine(Line3, (uint8_t*)PIN_correct3);
	LCD_DisplayStringLine(Line4, (uint8_t*)PIN_correct4);
	LCD_DisplayStringLine(Line5, (uint8_t*)PIN_correct5);
	LCD_DisplayStringLine(Line6, (uint8_t*)PIN_correct6);
	LCD_DisplayStringLine(Line7, (uint8_t*)PIN_correct7);
}

void Incorrect_LCD (){
	LCD_Clear(Red);
	LCD_SetBackColor(Red);
	LCD_SetTextColor(White);
	LCD_DisplayStringLine(Line1, (uint8_t*)PIN_wrong1);
	LCD_DisplayStringLine(Line2, (uint8_t*)PIN_wrong2);
	LCD_DisplayStringLine(Line3, (uint8_t*)PIN_wrong3);
	LCD_DisplayStringLine(Line4, (uint8_t*)PIN_wrong4);
	LCD_DisplayStringLine(Line5, (uint8_t*)PIN_wrong5);
	LCD_DisplayStringLine(Line6, (uint8_t*)PIN_wrong6);
	LCD_DisplayStringLine(Line7, (uint8_t*)PIN_wrong7);
	LCD_DisplayStringLine(Line8, (uint8_t*)PIN_wrong8);
}

void Serwis_Def_LCD () {
	LCD_Clear(Yellow);
	LCD_SetBackColor(Red);
	LCD_SetTextColor(White);
	LCD_DisplayStringLine(Line0, (uint8_t*)serwis_disp);
}
