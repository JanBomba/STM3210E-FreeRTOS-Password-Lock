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
	LCD_DisplayStringLine(Line0, Title);
	LCD_DisplayStringLine(Line5, pin_disp);
}

void PIN_LCD () {
	LCD_ClearLine(Line5);
	LCD_DisplayStringLine(Line5, pin_disp);
}

void Correct_LCD (){
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

void Incorrect_LCD (){
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

void Serwis_Def_LCD () {
	LCD_Clear(Yellow);
	LCD_SetBackColor(Red);
	LCD_SetTextColor(White);
	LCD_DisplayStringLine(Line0, serwis_disp);
}
