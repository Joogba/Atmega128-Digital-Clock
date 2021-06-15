#include "init.h"

#define EX_LCD_DATA (*(volatile unsigned char *)0x8000)
#define EX_LCD_CONTROL (*(volatile unsigned char *)0x8001)

#define PASSWORD_LEN 4

#define BUTTON1 0x01
#define BUTTON2 0x02
#define BUTTON3 0x04
#define BUTTON4 0x08
#define BUTTON5 0x10
#define BUTTON6 0x20
#define BUTTON7 0x40
#define BUTTON8 0x80

#define SECOND 	0
#define MINUTE 	1
#define HOUR 	2
#define DAY 	3
#define MONTH 	4
#define YEAR 	5

int main(void)
{
	static char i, k;
	char pw[PASSWORD_LEN];
	char key_data, key_old;
	int login_flag = 0;	 // 1 : 로그인 성공
	int pw_auth = 1; // 하나라도 다르면 0으로 
	int login_count = 0; // 로그인 자리수

	// variables=-=-=-=-=-=-=-=-=

	// global

	// login

	// clock

	// dual clock
	unsigned char time1_Arr[6] = { 0,};
	unsigned char time2_Arr[6] = { 0,};

	// alarm

	//stop watch

	// timer/counter

	
	
	init_ds1307();	
	init_devices();
	lcdInit();
	_delay_ms(500);
	lcd_puts(1, "Login");
	lcd_puts(2, "PassWord : ");

	// 비밀번호 3456
	eeprom_write_byte(0x0000, '3');
	eeprom_write_byte(0x0001, '4');
	eeprom_write_byte(0x0002, '5');
	eeprom_write_byte(0x0003, '6');

	// seoul time
	writebyte(0x04,0x50);  //second
 	writebyte(0x05,0x59);  //min
 	writebyte(0x06,0x15);  //hour
	writebyte(0x07,0x11);  //day
	writebyte(0x08,0x05);  //month
	writebyte(0x09,0x21);  //year

	// seoul time
	writebyte(0x0A,0x50);  //second
 	writebyte(0x0B,0x59);  //min
 	writebyte(0x0C,0x02);  //hour
	writebyte(0x0D,0x11);  //day
	writebyte(0x0E,0x05);  //month
	writebyte(0x0F,0x21);  //year


	while (1)
	{
		
		if (login_flag == 0)  // 로그인 
		{

			key_data = PINB & 0xff;
			if (key_data != key_old)
			{
				switch (key_data)
				{
				case 0x01:
					pw[login_count] = '0';
					break;
				case 0x02:
					pw[login_count] = '1';
					break;
				case 0x04:
					pw[login_count] = '2';
					break;
				case 0x08:
					pw[login_count] = '3';
					break;
				case 0x10:
					pw[login_count] = '4';
					break;
				case 0x20:
					pw[login_count] = '5';
					break;
				case 0x40:
					pw[login_count] = '6';
					break;
				case 0x80:
					pw[login_count] = '7';
					break;
				}
				login_count++;
			}
			
			
			if (login_count >= 4 && login_flag == 0)
			{
				for(int i = 0 ; i < PASSWORD_LEN ; i++)
				{
					if(pw[i] != (char)eeprom_read_byte(i))
						pw_auth =0;
				}

				if(pw_auth == 1) // 로그인성공
				{
					login_count = 0;
					login_flag = 1;
					
				}
			}
			else
				continue;

			key_old = key_data;
		}

		lcd_puts(2, "Welcome!!");
		_delay_ms(500);

		// 기능별 출력

		// 시계기능 =-=-=-=
		keydata = PINB & 0xff;
		if (keydata != key_old)
		{
			switch (key_data)
				{
				case BUTTON1: 
				// change time 	button1 : switch digit, button2 :up number
					
					break;
				case BUTTON2: 
				// switch timeline Korea, Usa
					
					break;
				case BUTTON3: 
				// Alarm  		button1 : switch digit, button2 :up number
					
					break;
				case BUTTON4:
				// Stop Watch		button1 : start button2 : recode
					break;
				case BUTTON5:
					
					break;
				case BUTTON6:
					
					break;
				case BUTTON7:
					
					break;
				case BUTTON8:
					
					break;
				}
			

		
		
		
	}
}
