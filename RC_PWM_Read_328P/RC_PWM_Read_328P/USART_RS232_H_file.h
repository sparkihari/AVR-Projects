/*
 * USART_RS232_H_file.h
 *
 */ 


#ifndef USART_RS232_H_FILE_H_				
#define USART_RS232_H_FILE_H_

#ifndef  F_CPU
	#define F_CPU 16000000UL
#endif


#include <avr/io.h>											
#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)	


void USART_Init(unsigned long);			
char USART_RxChar();					
void USART_TxChar(char);				
void USART_SendString(char*);			

#endif									