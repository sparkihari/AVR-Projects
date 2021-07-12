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
#define BAUD_PRESCALE_0 (((F_CPU / (BAUDRATE * 16UL))) - 1)	
#define BAUD_PRESCALE_1 (((F_CPU / (BAUDRATE * 16UL))) - 1)
#define BAUD_PRESCALE_2 (((F_CPU / (BAUDRATE * 16UL))) - 1)
#define BAUD_PRESCALE_3 (((F_CPU / (BAUDRATE * 16UL))) - 1)

void USART0_Init(unsigned long);
char USART0_RxChar();
void USART0_TxChar(char);
void USART0_SendString(char*);


void USART1_Init(unsigned long);
char USART1_RxChar();
void USART1_TxChar(char);
void USART1_SendString(char*);	

void USART2_Init(unsigned long);
char USART2_RxChar();
void USART2_TxChar(char);
void USART2_SendString(char*);		


void USART3_Init(unsigned long);
char USART3_RxChar();
void USART3_TxChar(char);
void USART3_SendString(char*);
#endif									