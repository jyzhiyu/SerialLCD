#include <stm32f10x.h>
#include <delay.h>

volatile u32 Systickms;

void Delayms(unsigned long dly_ms)
{
	Systickms=dly_ms;
	while(Systickms);
}

 void TimingDelay_Decrement(void)
 {
   if (Systickms != 0x00)
   {
     Systickms--;
  }
}
 
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

