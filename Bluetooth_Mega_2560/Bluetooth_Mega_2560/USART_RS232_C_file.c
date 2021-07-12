/*
 * USART_RS232_C_file.c
 *
 */ 

#include "USART_RS232_H_file.h"					


// USART 0 

void USART0_Init(unsigned long BAUDRATE)
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	UBRR0L = BAUD_PRESCALE_0;
	UBRR0H = (BAUD_PRESCALE_0 >> 8);
}

char USART0_RxChar()
{
	while (!(UCSR0A & (1 << RXC0)));
	return(UDR0);
}

void USART0_TxChar(char data)
{
	
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void USART0_SendString(char *str)
{
	int i=0;
	while (str[i]!=0)
	{
		USART0_TxChar(str[i]);
		i++;
	}
}

// USART 1 

void USART1_Init(unsigned long BAUDRATE)			
{ 
	UCSR1B |= (1 << RXEN1) | (1 << TXEN1);		
	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);	
	UBRR1L = BAUD_PRESCALE_1;
	UBRR1H = (BAUD_PRESCALE_1 >> 8);				
}

char USART1_RxChar()								
{
	while (!(UCSR1A & (1 << RXC1)));			
	return(UDR1);								
}

void USART1_TxChar(char data)					
{
	
	while (!(UCSR1A & (1<<UDRE1)));				
	UDR1 = data;								
}

void USART1_SendString(char *str)				
{
	int i=0;									
	while (str[i]!=0)
	{
		USART1_TxChar(str[i]);					
		i++;
	}
}


// USART 2

void USART2_Init(unsigned long BAUDRATE)
{
	UCSR2B |= (1<<RXCIE0) | (1 << RXEN2) | (1 << TXEN2);
	UCSR2C |= (1 << UCSZ20) | (1 << UCSZ21);
	UBRR2L = BAUD_PRESCALE_2;
	UBRR2H = (BAUD_PRESCALE_2 >> 8);
}

char USART2_RxChar()
{
	while (!(UCSR2A & (1 << RXC2)));
	return(UDR2);
}

void USART2_TxChar(char data)
{
	
	while (!(UCSR2A & (1<<UDRE2)));
	UDR2 = data;
}

void USART2_SendString(char *str)
{
	int i=0;
	while (str[i]!=0)
	{
		USART2_TxChar(str[i]);
		i++;
	}
}


// USART 3

void USART3_Init(unsigned long BAUDRATE)
{
	UCSR3B |= (1 << RXEN3) | (1 << TXEN3);
	UCSR3C |= (1 << UCSZ30) | (1 << UCSZ31);
	UBRR3L = BAUD_PRESCALE_3;
	UBRR3H = (BAUD_PRESCALE_3 >> 8);
}

char USART3_RxChar()
{
	while (!(UCSR3A & (1 << RXC3)));
	return(UDR3);
}

void USART3_TxChar(char data)
{
	
	while (!(UCSR3A & (1<<UDRE3)));
	UDR3 = data;
}

void USART3_SendString(char *str)
{
	int i=0;
	while (str[i]!=0)
	{
		USART3_TxChar(str[i]);
		i++;
	}
}




