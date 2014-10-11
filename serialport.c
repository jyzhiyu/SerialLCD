#include <stm32f10x.h>
#include <stm32f10x_it.h>
#include <misc.h>
#include <serialport.h>

#define SERIAL_BUFFER_SIZE 64

USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
	
	
struct ring_buffer
{
  unsigned char buffer[SERIAL_BUFFER_SIZE];
  volatile unsigned int head;
  volatile unsigned int tail;
};

struct ring_buffer rx_buffer = { { 0 }, 0, 0};
struct ring_buffer tx_buffer = { { 0 }, 0, 0};

void store_char(unsigned char c, struct ring_buffer *buffer)
{
  int i = (unsigned int)(buffer->head + 1) % SERIAL_BUFFER_SIZE;

  // if we should be storing the received character into the location
  // just before the tail (meaning that the head would advance to the
  // current location of the tail), we're about to overflow the buffer
  // and so we don't write the character or advance the head.
  if (i != buffer->tail) {
    buffer->buffer[buffer->head] = c;
    buffer->head = i;
  }
}

void USART1_IRQHandler(void)
{
	char c;
	FlagStatus RXNE,TXE;
	RXNE = USART_GetFlagStatus(USART1,USART_FLAG_RXNE);
	if (RXNE == SET)
	{
		c = USART_ReceiveData(USART1);
		store_char(c, &rx_buffer);
	}
	TXE = USART_GetFlagStatus(USART1,USART_FLAG_TXE);
	if (TXE == SET)
	{
		if (tx_buffer.head == tx_buffer.tail)
		{
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		}
		else
		{
			c = tx_buffer.buffer[tx_buffer.tail];
			tx_buffer.tail = (tx_buffer.tail + 1) % SERIAL_BUFFER_SIZE;
			USART_SendData(USART1,c);
		}
	}		
}


void Serial1Begin(void)
{

	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |  RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1, ENABLE); 
	
	
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
 
       
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
   /* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

unsigned char Serial1Available(void)
{
	return (unsigned int)(SERIAL_BUFFER_SIZE + rx_buffer.head - rx_buffer.tail) % SERIAL_BUFFER_SIZE;
}

char Serial1Read(void)
{
	char c;
	if (rx_buffer.head == rx_buffer.tail)
	{
		return -1;
	}
	else
	{
		c = rx_buffer.buffer[rx_buffer.tail];
		rx_buffer.tail = (unsigned int)(rx_buffer.tail + 1) % SERIAL_BUFFER_SIZE;
		return c;
	}
}

void Serial1Write(char c)
{
	int i = (tx_buffer.head + 1) % SERIAL_BUFFER_SIZE;
	while (i == tx_buffer.tail);
	tx_buffer.buffer[tx_buffer.head] = c;
	tx_buffer.head = i;
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}

void Serial1End(void)
{
	while (tx_buffer.head != tx_buffer.tail);
	USART_Cmd(USART1, DISABLE);
}

