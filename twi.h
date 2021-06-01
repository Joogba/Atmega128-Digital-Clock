
#define DS1307	0xd0

#define I2C_CLK	100000
#define TWBR_SET	(16000000-(I2C_CLK*16))/(I2C_CLK*8)

#define WMODE 	0x00
#define RMODE	0x01

#define SEC		0x00
#define MIN		0x01
#define HOUR	0x02
#define DAY		0x03
#define DATE	0x04
#define MON		0x05
#define YEAR	0x06
#define CONTROL	0x07

void delay(int n)
{
  volatile int i,j;
  for (i=1;i<n;i++) {
	for (j=1;j<600;j++) ;
  }
}

void I2C_delay(void)
{
	volatile int j;
   	for(j=1;j<10;j++);

}

void I2C_init(void)
{
  DDRD = 0x03;
  PORTD = 0x03;
  TWBR = TWBR_SET;
  TWSR = 0x00;
}

void I2C_start(void)
{
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
}

void I2C_stop(void)
{
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void writebyte(unsigned char address, unsigned char data) 
{
  I2C_start();
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

  while( ((TWCR & 0x80) == 0x00) || (TWSR & 0xF8) != 0x08);
  TWDR = DS1307 | WMODE;
  TWCR = 0x84;

  while( ((TWCR & 0x80) == 0x00) || (TWSR & 0xF8) != 0x18);
  TWDR = address;
  TWCR = 0x84;

  while( ((TWCR & 0x80) == 0x00) || (TWSR & 0xF8) != 0x28);
  TWDR = data;
  TWCR = 0x84;
    
  
  

  while( ((TWCR & 0x80) == 0x00) || (TWSR & 0xF8) != 0x28);
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

  I2C_delay();
}

unsigned char readbyte(unsigned char address) 
{
  unsigned char data = 0;
  I2C_start();
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

  while( ((TWCR & 0x80) == 0x00) || (TWSR & 0xF8) != 0x08);
  TWDR = DS1307 | WMODE;
  TWCR = 0x84;

  while( ((TWCR & 0x80) == 0x00) || (TWSR & 0xF8) != 0x18);
  TWDR = address;
  TWCR = 0x84;

  while( ((TWCR & 0x80) == 0x00) || (TWSR & 0xF8) != 0x28);
  TWCR = 0xA4;

  while( ((TWCR & 0x80) == 0x00) || (TWSR & 0xF8) != 0x10);
  TWDR = DS1307 | RMODE;
  TWCR = 0x84;

  while( ((TWCR & 0x80) == 0x00) || (TWSR & 0xF8) != 0x40);
  TWCR = 0x84;
  while( ((TWCR & 0x80) == 0x00) || (TWSR & 0xF8) != 0x58);
  data = TWDR;
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
  return data;
}

void init_ds1307(void){
	I2C_init();
	I2C_start();

	writebyte(SEC, 1);
	writebyte(MIN, 1);
	writebyte(HOUR, 1);
	writebyte(DAY, 1);
	writebyte(DATE, 1);
	writebyte(MON, 1);
	writebyte(YEAR, 1);
	writebyte(CONTROL, 0x10);
	
	I2C_stop();
}
