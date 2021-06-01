#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"

#define EX_LCD_DATA (*(volatile unsigned char *)0x8000)
#define EX_LCD_CONTROL (*(volatile unsigned char *)0x8001)

int main(void)
{
	int j;
	