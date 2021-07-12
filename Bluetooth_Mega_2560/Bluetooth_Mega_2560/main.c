/*
 * Bluetooth_Mega_2560.c
 *
 * Created: 12-Jul-21 8:48:52 PM
 * Author : Hari
 */ 

#ifndef  F_CPU
	#define F_CPU 16000000UL
#endif

#include <avr/io.h>						
#include <util/delay.h>					
#include <inttypes.h>					
#include <stdlib.h>						
#include <stdio.h>						
#include <avr/interrupt.h>
#include <stdbool.h>


#include "string.h"
#include "USART_RS232_H_file.h"			/* Include USART header file */

ISR (USART2_RX_vect)
{
	USART0_TxChar(USART2_RxChar());
}
int main(void)
{
	USART0_Init(9600);
	USART2_Init(9600);
	
	USART0_SendString("\n\r BLE_Test \n\r");

	sei(); 
    
	while (1) 
    {
    }
}

