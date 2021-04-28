/*
 * Project: BNO055_328P
 * Created: 23/04/2021 5:12:25 PM
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
#include "string.h"

#include "i2c_master.h"					// Include I2C Master header file
#include "USART_RS232_H_file.h"			// Include USART header file 
#include "bno055.h"						// Include BNO055 Master header file 

#define BUF_LEN			20


uint8_t id;
uint8_t raw[6]= { 0, 0, 0, 0, 0, 0 }, calib = 0;

int16_t raw_x = 0, raw_y = 0, raw_z = 0;

char buffer[BUF_LEN], float_[BUF_LEN];

static void BNO055_Init(void)
{
	uint8_t id;
	USART_SendString("\n\r BNO055 Initialization");

	i2c_start(BNO055_WRITE);
	i2c_write(BNO055_CHIP_ID_ADDR);
	i2c_stop();

	i2c_start(BNO055_READ);
	id = i2c_read_nack();
	i2c_stop();

	if (id == BNO055_CHIP_ID)
	{

		i2c_start(BNO055_WRITE);
		i2c_write(BNO055_PAGE_ID_ADDR);
		i2c_write(0x00);
		i2c_stop();
		USART_SendString(".....");

		i2c_start(BNO055_WRITE);
		i2c_write(BNO055_OPR_MODE_ADDR);
		i2c_write(BNO055_OPERATION_MODE_CONFIG);
		i2c_stop();
		USART_SendString(".....");
		_delay_ms(1);

		i2c_start(BNO055_WRITE);
		i2c_write(BNO055_PWR_MODE_ADDR);
		i2c_write(BNO055_POWER_MODE_NORMAL);
		i2c_stop();
		USART_SendString(".....");
		_delay_ms(1);

		i2c_start(BNO055_WRITE);
		i2c_write(BNO055_OPR_MODE_ADDR);
		i2c_write(BNO055_OPERATION_MODE_NDOF);
		i2c_stop();
		USART_SendString(".....");
		_delay_ms(1);
		
		USART_SendString(".....Completed\n\r\n\r");

	}
	else
	{
		USART_SendString(".....Failed\n\r");

	}
}

static void Read_value(void)
{
	i2c_start(BNO055_WRITE);
	i2c_write(BNO055_EULER_H_LSB_ADDR);
	i2c_stop();

	i2c_start(BNO055_READ);

	raw[0] = i2c_read_ack();
	raw[1]=  i2c_read_ack();

	raw[2] = i2c_read_ack();
	raw[3] = i2c_read_ack();

	raw[4] = i2c_read_ack();
	raw[5] = i2c_read_nack();

	i2c_stop();
	
	raw_z =(((int16_t)raw[1] << 8) | raw[0])/16 ;       // Turn the MSB and LSB into a signed 16-bit value
	raw_y =(((int16_t)raw[3] << 8) | raw[2])/16 ;
	raw_x =(((int16_t)raw[5] << 8) | raw[4])/16 ;

}


static void Print_Angle()
{
	
	dtostrf( raw_x, 3, 2, float_ );
	snprintf(buffer,BUF_LEN,"\n\r X-axis: %s\t ",float_);
	USART_SendString(buffer);
	
	dtostrf( raw_y, 3, 2, float_ );
	snprintf(buffer,BUF_LEN,"Y-axis: %s\t ",float_);
	USART_SendString(buffer);

	dtostrf( raw_z, 3, 2, float_ );
	snprintf(buffer,BUF_LEN,"Z-axis: %s\t ",float_);
	USART_SendString(buffer);
	
}

int main(void)
{
	i2c_init();								// Initialize I2C	-> 400 kHZ
	USART_Init(9600);						// Initialize UART	-> 9600 Buadrate
	USART_SendString("\n\r BNO055 IMU Test \n\r");
	
	BNO055_Init();							// Initialize BNO055-> Internal Clock Source

    while (1) 
    {
		Read_value();
		Print_Angle();
		_delay_ms(10);
    }
}

