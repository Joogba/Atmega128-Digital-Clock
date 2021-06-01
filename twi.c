#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "twi.h"
#include "lcd.h"

#define CLI() cli()
#define SEI() sei()

void port_init(void)
{ PORTA = 0x00;
  DDRA  = 0xff;
  PORTB = 0x00;
  DDRB  = 0x00;
  PORTC = 0x00; //m103 output only
  DDRC  = 0x0f;
  PORTD = 0x00;
  DDRD  = 0x00;
  PORTE = 0x00;
  DDRE  = 0x00;
  PORTF = 0x00;
  DDRF  = 0x00;
  PORTG = 0x00;
  DDRG  = 0x03;
}



//call this routine to initialize all peripherals
void init_devices(void)
{  //stop errant interrupts until set up
   cli(); //disable all interrupts
   XDIV  = 0x00; //xtal divider
   XMCRA = 0x00; //external memory
   port_init();    // UART 0 ÃÊ±âÈ­
   MCUCR = 0x80;
   EICRA = 0x00; //extended ext ints
   EICRB = 0x00; //extended ext ints
   EIMSK = 0x00;
   TIMSK = 0x00; //timer interrupt sources
   ETIMSK = 0x00; //extended timer interrupt sources
   sei(); //re-enable interrupts
   //all peripherals are now initialized
}


void printf_Lcd(int lin, int can, char *Str) {
   lcdRegWrite(0x38);
   lcd_gotoxy(can, lin);
   putString(Str);
}

int main (void)
{	unsigned char second, min, hour,year,date,month;
	init_devices();
	init_ds1307();	
	_delay_ms(500);
	//lcdClear();
	//lcd_puts(1, "Test DS1307");
	//lcd_puts(2, " Test TWI");
	//lcdClear();
	//_delay_ms(500);
	// lcd_puts(1, "Time Test");
 	writebyte(0x00,0x50);  //second
 	writebyte(0x01,0x59);  //min
 	writebyte(0x02,0x15);  //hour
	writebyte(0x04,0x11);  //day
	writebyte(0x05,0x05);  //month
	writebyte(0x06,0x21);  //year
	
	lcdClear();
	_delay_ms(500);
	//lcd_puts(1, "   H: M: S:   ");
	while(1){
		hour = readbyte(0x02);
		hour= ((hour >> 4 ) & 0x01) *10 + (hour & 0x0f);
		lcd_gotoxy(4,2);
	 	lcd_putn2(hour);
		
		min = readbyte(0x01);
		min= (( min >> 4) & 0x07 ) *10 + (min & 0x0f);
	 	lcd_gotoxy(7,2);
	 	lcd_putn2(min);
		second=readbyte(0x00);
		second = ((second >> 4) & 0x07)*10+ (second & 0x0f);
	 	lcd_gotoxy(10,2);
	 	lcd_putn2(second);
	    //    _delay_ms(100);
			
		date=readbyte(0x04);
		date = ((date >> 4) & 0x03)*10+ (date & 0x0f);
        lcd_gotoxy(6,1);
	 	lcd_putn2(date);
		
		month=readbyte(0x05);
		month = ((month >> 4) & 0x01)*10+ (month & 0x0f);
        lcd_gotoxy(4,1);
	 	lcd_putn2(month);
		
		year=readbyte(0x06);
		year = ((year >> 4) & 0x0f)*10+ (year & 0x0f);
        lcd_gotoxy(1,1);
	 	lcd_putn2(year);
	        _delay_ms(100);	
	}
	return 0;
}


