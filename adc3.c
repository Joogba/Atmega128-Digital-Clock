#include "lcd.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>


#define CLI() cli()
#define SEI() sei()


#define EX_LCD_DATA  (*(volatile unsigned char *)0x8000)
#define EX_LCD_CONTROL  (*(volatile unsigned char *)0x8001)



void adc_init(void)
{
	ADCSRA = 0x00; // disable adc
	ADMUX = 0x00; // select adc input 0;
	ADCSRA = 0x87; // adc enable, 분주 128 // 10000111
	// adc 를 위한 주파수 = 16mhz / 128 = 125 khz
}

void adc_startConversion(void)
{
	ADCSRA &= 0x07; // 128 분주비 사용 111
	ADMUX = 0x03;
	ADCSRA |= 0xc0; // adc ON 11000000
}

unsigned int adc_readData(void)
{
	
	volatile unsigned int adc_temp;
	while((ADCSRA & 0x10) == 0); // 변환 완료까지 기다림
	adc_temp=(int)ADCL+(int)ADCH*256;
	// ADCSRA = ADCSRA | 0x10
	return adc_temp;
}

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

int main()
{
	unsigned int adc_data, ah0, al0;
	float voltage,tempo;
	init_devices();
	adc_init();
	lcdInit();
	
	_delay_ms(500);
	
	
	lcd_puts(1," adc test");
	lcd_puts(2," adc res.");
	
	while(1)
	{
		adc_startConversion();
		adc_data = adc_readData();
		voltage = (float)(5.*adc_data)/1024.;
		lcd_gotoxy(12,2);
		lcd_putn4(voltage); //48738
		_delay_ms(500);
		
	}
	return 0;
}