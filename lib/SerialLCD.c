#include <stm32f10x.h>
#include <delay.h>
#include <FSMCDriver.h>
#include <Serialport.h>



void setup(void)
{
	SystemInit();
	FSMC_Init();
	Serial1Begin();	
}

void loop(void)
{

}
