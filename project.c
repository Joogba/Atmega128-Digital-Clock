#include "init.h"

#define EX_LCD_DATA (*(volatile unsigned char *)0x8000)
#define EX_LCD_CONTROL (*(volatile unsigned char *)0x8001)

#define PASSWORD_LEN 4

int main(void)
{
	static char i, k;
	char pw[PASSWORD_LEN];
	char key_data, key_old;
	int login_flag = 0;	 // 1 : 로그인 성공
	int pw_auth = 1; // 하나라도 다르면 0으로 
	int login_count = 0; // 로그인 자리수
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

	for (int i = 0; i < PASSWORD_LEN; i++)
	{
	}

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
			
			key_old = key_data continue;
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
		}

		// 기능별 출력

		// 시계기능 =-=-=-=
		keydata = PINB & 0xff;
		if (keydata != key_old)
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
			

		
		
		_delay_ms(1000);
	}
}
