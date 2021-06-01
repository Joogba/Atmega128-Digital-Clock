#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"
#define EX_LCD_DATA (*(volatile unsigned char *)0x8000)
#define EX_LCD_CONTROL (*(volatile unsigned char *)0x8001)

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
void init_devices(void)
{  //stop errant interrupts until set up
	cli(); //disable all interrupts
	XDIV  = 0x00; //xtal divider
	XMCRA = 0x00; //external memory
	port_init();    // UART 0 √ ±‚»≠
	MCUCR = 0x80;
	EICRA = 0x00; //extended ext ints
	EICRB = 0x00; //extended ext ints
	EIMSK = 0x00;
	TIMSK = 0x00; //timer interrupt sources
	ETIMSK = 0x00; //extended timer interrupt sources
	sei(); //re-enable interrupts
	//all peripherals are now initialized
}

int main(void)
{

	static char i, k;
	init_devices();
	lcdInit();
	_delay_ms(500);
	lcd_puts(1, "Test EEPROM");
	lcd_puts(2, "Read data");
	while (1)
	{
		eeprom_write_byte(0x0000,'C');
		eeprom_write_byte(0x0001,'H');
		eeprom_write_byte(0x0002,'O');
		eeprom_write_byte(0x0003,'I');
		eeprom_write_byte(0x0004,' ');
		for (i=0;i<5;i++) {
			k= eeprom_read_byte(i);
			_delay_ms(1000);
			lcd_gotoxy(12,2);
			lcd_putch(k);
		}
		_delay_ms(1000);
	}
}