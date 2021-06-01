#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "lcd.h"

#define CLI() cli()
#define SEI() sei()

#define EX_LCD_DATA  (*(volatile unsigned char *)0x8000)
#define EX_LCD_CONTROL  (*(volatile unsigned char *)0x8001)




volatile long T1HIGHCNT, T1LOWCNT, TCNT;
unsigned int freq;


unsigned char keydata, key_old;

void port_init(void)
{
	 PORTA = 0x00;
	 DDRA  = 0xff;
	 PORTB = 0x00;
	 DDRB  = 0x00;
	 PORTC = 0x00; //m103 output only
	 DDRC  = 0x00;
	 PORTD = 0x00;
	 DDRD  = 0x00;
	 PORTE = 0x00;
	 DDRE  = 0x00;
	 PORTF = 0x00;
	 DDRF  = 0x00;
	 PORTG = 0x00;
	 DDRG  = 0x1f;  // buzzle --> PORTG4
}

//TIMER1 initialize - prescale:8

void timer1_init(void)
{
	 TCCR1B = 0x00; //stop
	 TCNT1H = 0x00; //setup
	 TCNT1L = 0x00;
	 TCCR1A = 0x00;
	 TCCR1B = 0x02; //Normal mode, prescale = 8 start Timer
}


void init_devices(void)
{
	 //stop errant interrupts until set up
	 CLI(); //disable all interrupts
	 port_init();
	 lcdInit();
	 lcdClear();
	 timer1_init();
	 MCUCR = 0x80;
	 TIMSK = 0x04; //timer1 interrupt sources
	 SEI(); //re-enable interrupts
	 
}



ISR(TIMER1_OVF_vect)
{	
	TCNT1 = TCNT;
	PORTG = PORTG ^ 0x10;
}

void sound(int freq)
{	//T1HIGHCNT = (0xFFFF-floor(1000000/freq))/0x100;
	//T1LOWCNT = 0xFF00 - (0xFFFF-floor(1000000/freq) );
	TCNT = (0xFFFF-floor(1000000/(freq/2)));
	 lcd_gotoxy(5,2);
	 lcd_putn3(TCNT);
	 lcd_gotoxy(11,2);
	 lcd_putn3(freq);
}



int main( void ) 
{
	
	 MCUCR = 0x80;
	 port_init();
	 init_devices();
	lcdClear();
	_delay_ms(500);
	
	 lcd_puts(1,"buzzle test");	
	 _delay_ms(500);
	 
	 int old_note = 0;
	
	while(1) 
	 {
		keydata = PINB & 0xff;
		lcd_putn1(keydata);	
		
			switch(keydata)
			{
			case 0x01:
				sound(523);
				//lcd_puts(2,"DO");	
				break;
			case 0x02:
				sound(587);
				//lcd_puts(2,"RE");	
				break;
			case 0x04:
				sound(659);
				//lcd_puts(2,"MI");
				break;				
			case 0x08:
				sound(699);
				//lcd_puts(2,"PA");
				break;
			case 0x10:
				sound(784);
				//lcd_puts(2,"SOL");
				//_delay_ms(400);
				break;
			case 0x20:
				sound(880);
				//lcd_puts(2,"RA");
				//_delay_ms(400);
				break;
			case 0x40:
				sound(988);
				//lcd_puts(2,"SI");
				//_delay_ms(400);
				break;
			case 0x80:
				sound(523*2);
				//lcd_puts(2,"DO");
				//_delay_ms(400);
				break;
			case 0x00:
				sound(0);
				//_delay_ms(400);
				break;
			default:
				sound(0);
				//_delay_ms(400);
				
				break;
			}
		
			
		
	 
	 }
	return 0;
}