#include <stm32f10x.h>


volatile unsigned long Timer1;

void SysTickDelay(unsigned long dly_ms)
{
	Timer1=dly_ms;
	while(Timer1--);
}


void setup(void);
void loop(void);

int main()
{
		
	
  //SysTick_Config(SystemCoreClock/2);
	setup();
		while(1)
				loop();
//		return 1;
}






void loop()
{
	Pant(0xf800);
	SysTickDelay(5000000);
	Pant(0x07e0);
	SysTickDelay(5000000);
	Pant(0x001f);
	SysTickDelay(5000000);
	Pant(0xffff);
	SysTickDelay(5000000);
	Pant(0x0000);
	SysTickDelay(5000000);
}

void setup(void)
{
	GPIO_Configuration();
	FSMC_LCD_Init();
	LCD_Init();
}
