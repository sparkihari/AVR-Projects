/*
 * USART_RS232_C_file.c
 *
 */ 

#include "USART_RS232_H_file.h"					

void USART_Init(unsigned long BAUDRATE)			
{ 
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);		
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);	
	UBRR0L = BAUD_PRESCALE;
	UBRR0H = (BAUD_PRESCALE >> 8);				
}

char USART_RxChar()								
{
	while (!(UCSR0A & (1 << RXC0)));			
	return(UDR0);								
}

void USART_TxChar(char data)					
{
	
	while (!(UCSR0A & (1<<UDRE0)));				
	UDR0 = data;								
}

void USART_SendString(char *str)				
{
	int i=0;									
	while (str[i]!=0)
	{
		USART_TxChar(str[i]);					
		i++;
	}
}

