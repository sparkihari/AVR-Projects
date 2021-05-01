/*
 * RC_PWM_Read_328P
 *
 * Created: 01-May-21 5:53:25 PM
 * Author : Hari_spx
 */ 

#ifndef  F_CPU
	#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "string.h"

#include "USART_RS232_H_file.h"			

#define ROLE		0
#define	PITCH		1
#define	THROTTLE	2
#define	YAW			3
#define FL_MODE		4
#define LED			5

#define BUF_LEN		20


uint8_t last_channel_0, last_channel_1, last_channel_2, last_channel_3,last_channel_4,last_channel_5;
volatile int receiver_input_channel_0, receiver_input_channel_1, receiver_input_channel_2, receiver_input_channel_3,receiver_input_channel_4, receiver_input_channel_5;
unsigned long timer_0, timer_1, timer_2, timer_3, timer_4, timer_5, current_time;

char buffer[BUF_LEN], float_[BUF_LEN];

uint8_t Data[6] = { 93, 93, 0, 93, 63, 63 };
bool Rx_Done = false;


void timer_int(void)
{
	TCCR1B |= (1<<CS12);
	
	TCCR1A |= 0;
	
	sei();

}

ISR(PCINT2_vect){
	
	//Channel 0 =========================================
	if(PIND & (1<<PORTD2)){
		if(last_channel_0 == 0){
			TCNT1 = 0;
			last_channel_0 = 1;
			timer_0 = TCNT1;
		}
	}
	else if(last_channel_0 == 1){
		current_time =  TCNT1;
		last_channel_0 = 0;
		receiver_input_channel_0 = current_time - timer_0;
		
	}
	
	
	
	//Channel 1 =========================================
	if(PIND & (1<<PORTD3)){
		if(last_channel_1 == 0){
			TCNT1 = 0;
			last_channel_1 = 1;
			timer_1 = TCNT1;
		}
	}
	else if(last_channel_1 == 1){
		current_time =  TCNT1;
		last_channel_1 = 0;
		receiver_input_channel_1 = current_time - timer_1;
		
	}
	
	
	//Channel 2 =========================================
	if(PIND & (1<<PORTD4)){
		if(last_channel_2 == 0){
			TCNT1 = 0;
			last_channel_2 = 1;
			timer_2 = TCNT1;
		}
	}
	else if(last_channel_2 == 1){
		current_time =  TCNT1;
		last_channel_2 = 0;
		receiver_input_channel_2 = current_time - timer_2;
		
		

	}
	
	
	//Channel 3 =========================================
	if(PIND & (1<<PORTD5)){
		if(last_channel_3 == 0){
			TCNT1 = 0;
			last_channel_3 = 1;
			timer_3 = TCNT1;
		}
	}
	else if(last_channel_3 == 1){
		current_time =  TCNT1;
		last_channel_3 = 0;
		receiver_input_channel_3 = current_time - timer_3;
		
		
	}
	
	//Channel 4 =========================================
	if(PIND & (1<<PORTD6)){
		if(last_channel_4 == 0){
			TCNT1 = 0;
			last_channel_4 = 1;
			timer_4 = TCNT1;
		}
	}
	else if(last_channel_4 == 1){
		current_time =  TCNT1;
		last_channel_4 = 0;
		receiver_input_channel_4 = current_time - timer_4;
		
		

	}


	//Channel 5 =========================================
	if(PIND & (1<<PORTD7)){
		if(last_channel_5 == 0){
			TCNT1 = 0;
			last_channel_5 = 1;
			timer_5 = TCNT1;
		}
	}
	else if(last_channel_5 == 1){
		current_time =  TCNT1;
		last_channel_5 = 0;
		receiver_input_channel_5 = current_time - timer_5;
		Rx_Done = true;
		
	}

}


int main(void)
{
	USART_Init(9600);
	
	PCICR  |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT18);
	PCMSK2 |= (1 << PCINT19);
	PCMSK2 |= (1 << PCINT20);
	PCMSK2 |= (1 << PCINT21);
	PCMSK2 |= (1 << PCINT22);
	PCMSK2 |= (1 << PCINT23);
	
	timer_int();
	
	while (1)
	{
		if (Rx_Done)
		{
			Rx_Done = false;

			Data[ROLE]		= receiver_input_channel_0;
			Data[PITCH]		= receiver_input_channel_1;
			Data[THROTTLE]	= receiver_input_channel_2;
			Data[YAW]		= receiver_input_channel_3;
			Data[FL_MODE]	= receiver_input_channel_4;
			Data[LED]		= receiver_input_channel_5;
		}
		else
		{
			Data[ROLE]		= 93;
			Data[PITCH]		= 93;
			Data[THROTTLE]	= 0;
			Data[YAW]		= 93;
			Data[FL_MODE]	= 63;
			Data[LED]		= 63;
		}


		dtostrf(Data[ROLE], 3, 0, float_ );
		snprintf(buffer,BUF_LEN,"\n\r %s\t ",float_);
		USART_SendString(buffer);
		
		dtostrf(Data[PITCH], 3, 0, float_ );
		snprintf(buffer,BUF_LEN," %s\t ",float_);
		USART_SendString(buffer);
		
		dtostrf(Data[THROTTLE], 3, 0, float_ );
		snprintf(buffer,BUF_LEN," %s\t ",float_);
		USART_SendString(buffer);
		
		dtostrf(Data[YAW], 3, 0, float_ );
		snprintf(buffer,BUF_LEN," %s\t ",float_);
		USART_SendString(buffer);

		dtostrf(Data[FL_MODE], 3, 0, float_ );
		snprintf(buffer,BUF_LEN," %s\t ",float_);
		USART_SendString(buffer);

		dtostrf(Data[LED], 3, 0, float_ );
		snprintf(buffer,BUF_LEN," %s\t ",float_);
		USART_SendString(buffer);

		memset(float_, 0, BUF_LEN);
		memset(buffer, 0, BUF_LEN);

	}
}