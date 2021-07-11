/*
 * PWM_Test_328P.c
 *
 * Created: 04-Jul-21 10:49:52 PM
 * Author : Hari
 */ 

#define F_CPU 16000000UL				/* Define CPU clock Frequency 16MHz */

#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include delay header file */

int i = 0;


static void PWM_Init(void)
{
	DDRB |= (1<<1) | (1<<2) | (1<<3);
	DDRD |= (1<<3) | (1<<5) | (1<<6);


	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11);
	ICR1	= 1250;               							// (16 MHz / 256) / 50 Hz = 1250 (Top value)

	TCCR0A |= (1<<COM0A1) | (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);
	
	TCCR2A |= (1<<COM2A1) | (1<<COM2B1) | (1<<WGM21) | (1<<WGM20);


	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS12);			// 50 Hz

	TCCR0B |= (1<<CS02);									// 244 Hz
	
	TCCR2B |= (1<<CS22) | (1<<CS21);						// 244 Hz

	
	OCR0A = 0;
	OCR0B = 0;
	
	OCR1A = 0;
	OCR1B = 0;
	
	OCR2A = 0;
	OCR2B = 0;
	
}
int main(void)
{
	PWM_Init();
	
    
    while (1) 
    {
		for (i=0; i<250; i++)
		{
				OCR0A = i;
				OCR0B = i;
						
				OCR1A = i * 5;
				OCR1B = i * 5;
						
				OCR2A = i;
				OCR2B = i;
				
				_delay_ms(100);
		}
		
    }
}

