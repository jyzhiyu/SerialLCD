#include <stm32f10x.h>
#include <delay.h>

/*******************************************
通用硬件操作函数
*******************************************/
#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ADDR
#define Bank1_LCD_C    ((uint32_t)0x60000000)    //disp Reg ADDR

//写寄存器地址函数
void Write_Command(unsigned int index)
{
    *(__IO uint16_t *) (Bank1_LCD_C)= index;
}

//写寄存器数据函数
void Write_Command_Data(unsigned int index,unsigned int val)
{    
    *(__IO uint16_t *) (Bank1_LCD_C)= index;    
    *(__IO uint16_t *) (Bank1_LCD_D)= val;
}

//写16位数据函数
void  Write_Data(unsigned int val)
{   
    *(__IO uint16_t *) (Bank1_LCD_D)= val;     
}

void LCD_Init()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);
  Delayms(4);					   
  GPIO_SetBits(GPIOD, GPIO_Pin_2 );		 	 
	Delayms(10);
	
	Write_Command_Data(0x0000,0x0001);
	Write_Command_Data(0x0003,0xA8A4);
	Write_Command_Data(0x000C,0x0000);
	Write_Command_Data(0x000D,0x080C);
	Write_Command_Data(0x000E,0x2B00);
	Write_Command_Data(0x001E,0x00B7);
	Write_Command_Data(0x0001,0x2B3F);
	Write_Command_Data(0x0002,0x0600);
	Write_Command_Data(0x0010,0x0000);
	Write_Command_Data(0x0011,0x6070);
	Write_Command_Data(0x0005,0x0000);
	Write_Command_Data(0x0006,0x0000);
	Write_Command_Data(0x0016,0xEF1C);
	Write_Command_Data(0x0017,0x0003);
	Write_Command_Data(0x0007,0x0233);
	Write_Command_Data(0x000B,0x0000);
	Write_Command_Data(0x000F,0x0000);
	Write_Command_Data(0x0041,0x0000);
	Write_Command_Data(0x0042,0x0000);
	Write_Command_Data(0x0048,0x0000);
	Write_Command_Data(0x0049,0x013F);
	Write_Command_Data(0x004A,0x0000);
	Write_Command_Data(0x004B,0x0000);
	Write_Command_Data(0x0044,0xEF00);
	Write_Command_Data(0x0045,0x0000);
	Write_Command_Data(0x0046,0x013F);
	Write_Command_Data(0x0030,0x0707);
	Write_Command_Data(0x0031,0x0204);
	Write_Command_Data(0x0032,0x0204);
	Write_Command_Data(0x0033,0x0502);
	Write_Command_Data(0x0034,0x0507);
	Write_Command_Data(0x0035,0x0204);
	Write_Command_Data(0x0036,0x0204);
	Write_Command_Data(0x0037,0x0502);
	Write_Command_Data(0x003A,0x0302);
	Write_Command_Data(0x003B,0x0302);
	Write_Command_Data(0x0023,0x0000);
	Write_Command_Data(0x0024,0x0000);
	Write_Command_Data(0x0025,0x8000);
	Write_Command_Data(0x004f,0x0000);
	Write_Command_Data(0x004e,0x0000);
	Write_Command(0x0022);
}

void SetXY(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1)
{
	Write_Command_Data(0x0044,(x1<<8)+x0);
	Write_Command_Data(0x0045,y0);
	Write_Command_Data(0x0046,y1);
	Write_Command_Data(0x004e,x0);
	Write_Command_Data(0x004f,y0);
	Write_Command (0x0022);//LCD_WriteCMD(GRAMWR);
}
void FillScreen(unsigned int color)
{
	int i,j;
	SetXY(0,0,239,319);

    for(i=0;i<320;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
         Write_Data(color);
	    }

	  }		
}

void SetFrontColor(unsigned int color)
{

}

unsigned int GetFrontColor(void)
{

}

void SetBackColor(unsigned int color)
{

}

unsigned int GetBackColor(void)
{

}

void DrawPoint(unsigned int x,unsigned int y)
{
}

void DrawLine(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
{
}

void DrawRectangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
{
}
void DrawCricle(unsigned int x0, unsigned int y0, unsigned int raudis)
{
}
void FRoundRectangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
{
}
void FillRectangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
{
}
void FillCricle(unsigned int x0, unsigned int y0, unsigned int raudis)
{
}
void FillRoundRectangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
{
}

void PrintString(unsigned int x,unsigned int y,char * dat)
{
}
void SetFont(unsigned char FontIndex)
{
}

unsigned char GetFont(void)
{
}
unsigned char GetFontXSize(void)
{
}
unsigned char GetFontYSize(void)
{
}
void DrewBitmap(unsigned char BitmapIndex)
{
}
