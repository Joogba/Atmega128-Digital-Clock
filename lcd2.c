#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"

#define CLI() cli()
#define SEI() sei()

#define EX_LCD_DATA  (*(volatile unsigned char *)0x8000)
#define EX_LCD_CONTROL  (*(volatile unsigned char *)0x8001)

void port_init(void)
{
 PORTB = 0x00;
 DDRB  = 0x00;
}

void init_devices(void)
{
  CLI();
  port_init();
  MCUCR = 0x80;
  SEI();
}

int main(void)
{
   char i, count=0;
   init_devices();
   _delay_ms(1000);
   lcdInit();
   lcdClear();
   lcd_puts(1, "<NEWTC> KR-M128");
   lcd_puts(2, "LAB 10 ");

   while (1)
   {
     count++;
	 lcd_gotoxy(12,2);
	 lcd_putn3(count);
	 _delay_ms(1000);
   }
   return 0;
}



