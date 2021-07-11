/*
 * Timer_Delay_328P.c
 *
 * Created: 04-Jul-21 10:22:55 PM
 * Author : Hari
 */ 

#define F_CPU 16000000UL				/* Define CPU clock Frequency 16MHz */

#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include delay header file */
#include <avr/interrupt.h>

#define LED_SET				(PORTB |= (1<<5))
#define LED_CLEAR			(PORTB &= ~(1<<5))
#define LED_TOGGLE			(PORTB ^= (1<<5))

int i = 0;

static void Timer_Initailize(void)
{
	cli();
	
	TCCR2A |= (1<<WGM21);
	
	TCNT2 = 0;
	
	OCR2A = 124;							// 16 us * 124  = ~ 2 ms
	
	TIMSK2 |= (1<<OCIE2A);
	
	TCCR2B |= (1 << CS22)|(1 << CS21);		// 16 MHz / 256 = 62.5 kHz (1 tick = 16 us)
	
	sei();
}

ISR(TIMER2_COMPA_vect)						// Timer Interrupt
{
	if (i >= 99)							
	{
		i=0;
		LED_TOGGLE;							// Toggle the pin for every 200 ms
	}
	
	else
	{
		i++;
	}
		
}

int main(void)
{
	DDRB |= (1<<5);			// LED on D13 pin
    
	LED_CLEAR;
	
	Timer_Initailize();
	
    while (1) 
    {
    }
}

