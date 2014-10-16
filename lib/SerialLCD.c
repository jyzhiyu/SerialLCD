#include <stm32f10x.h>
#include <delay.h>
#include <FSMCDriver.h>
#include <Serialport.h>

#define DATBUFMAX 64
u8 datbuf[DATBUFMAX] = {0};
u8 datindex = 0;

#define TIMEOVERFLOWMAX 0xFFFFF
u32 TimeOverflow = TIMEOVERFLOWMAX;

void ATProcess(void);

void setup(void)
{
	SystemInit();
	Serial1Begin();		
	Serial1Print("SerialLCD initial....\n");
	FSMC_Init();
	Serial1Print("SerialLCD initial done~~~\n");
	Serial1Print("Hello~~~, welcome to SerialLCD world~~~\n");
	Serial1Print("Send \"AT+help\" to get the help list\n");
}

void InitDatBuf()
{
	u8 i =0;
	for(i = 0; i < DATBUFMAX; i++)
	{
		datbuf[i] = 0;
	}
	datindex = 0;
}

void loop(void)
{
	ATProcess();
}

void ATProcess(void)
{

	char dattemp = 0;
	TimeOverflow = TIMEOVERFLOWMAX;
	if(Serial1Available() > 0)
	{
		dattemp = Serial1Read();
		TimeOverflow = TIMEOVERFLOWMAX;
		if(dattemp != 0x0A)
		{
			datbuf[datindex] = dattemp;
			datindex++;
			if(datindex == DATBUFMAX)
			{
				Serial1Print("[ERROR][RX]:Receive AT command buffer overflow~~~\n");
				InitDatBuf();
				return;
			}
		}
		else
		{
			CMDprocess();
			InitDatBuf();
			return;
		}
				
	}
	TimeOverflow--;
	if(TimeOverflow == 0)
	{
		Serial1Print("[ERROR][RX]:Receive AT command time overflow~~~\n");
		InitDatBuf();
		return;
	}
}

void CMDprocess()
{
	if(	(datbuf[0] == 'A') &&
		(datbuf[1] == 'T') &&
		(datbuf[2] == '+'))
		{
			if((datbuf[3] == 'S') && (datbuf[4] == 'D') && (datbuf[5] == ';'))
				SetDevice();
			
			if((datbuf[3] == 'I') && (datbuf[4] == 'I') && (datbuf[5] == ';'))
				LCDInit();
			
			if((datbuf[3] == 'G') && (datbuf[4] == 'X') && (datbuf[5] == ';'))
				GetDisplayXSize();
			
			if((datbuf[3] == 'G') && (datbuf[4] == 'Y') && (datbuf[5] == ';'))
				GetDisplayYSize();
			
			if((datbuf[3] == 'D') && (datbuf[4] == 'O') && (datbuf[5] == ';'))
				Device_on();
			
			if((datbuf[3] == 'D') && (datbuf[4] == 'F') && (datbuf[5] == ';'))
				Device_on();
			
			if((datbuf[3] == 'S') && (datbuf[4] == 'C') && (datbuf[5] == ';'))
				SetContrast();
			
			if((datbuf[3] == 'S') && (datbuf[4] == 'B') && (datbuf[5] == ';'))
				SetBrightness();
			
			if((datbuf[3] == 'S') && (datbuf[4] == 'P') && (datbuf[5] == ';'))
				SetDisplayPage();
			
			if((datbuf[3] == 'W') && (datbuf[4] == 'P') && (datbuf[5] == ';'))
				WritePage();
			
			
			
		}
}