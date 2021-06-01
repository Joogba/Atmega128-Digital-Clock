#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"







void port_init(void)
{
 PORTA = 0x00;
 DDRA  = 0xff;
 PORTB = 0x00;
 DDRB  = 0x00;
 PORTC = 0x00; //m103 output only
 DDRC  = 0x03;
 PORTD = 0x00;
 DDRD  = 0x00;
 PORTE = 0x00;
 DDRE  = 0x00;
 PORTF = 0x00;
 DDRF  = 0x00;
 PORTG = 0x00;
 DDRG  = 0x03;
}






int main(void)
{
   char i, count=0;
    port_init();
   _delay_ms(1000);
   lcdInit();
  	
    MCUCR = 0x80;
 
   lcdClear();
   lcd_puts(1, "KPU University");
   lcd_puts(2, "2021.04.27 ");

   while (1)
   {
     count++;
	 lcd_gotoxy(12,2);
	 lcd_putn3(count);
	 _delay_ms(1000);
   }
   return 0;
}

