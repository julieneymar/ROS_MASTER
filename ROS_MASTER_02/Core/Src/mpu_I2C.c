/*
 * MPU_I2C.c
 *
 *  Created on: Oct 8, 2026
 *      Author: julie
 */
#include <mpu_I2C.h>


// Microsecond delay
static void Delay_For_Pin(uint8_t nCount)
{
    uint8_t i = 0;
    for(; nCount != 0; nCount--)
    {
        for (i = 0; i < 10; i++);
    }
}

#define delay_us  Delay_For_Pin

// Initialize the IIC
void MPU_IIC_Init(void)
{
	delay_us(1);
}


// Generates the IIC initiation signal
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();
	MPU_IIC_SDA(1);
	MPU_IIC_SCL(1);
	delay_us(4);
 	MPU_IIC_SDA(0);
	delay_us(4);
	MPU_IIC_SCL(0);
}

// Generates an IIC stop signal
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();
	MPU_IIC_SCL(0);
	MPU_IIC_SDA(0);
 	delay_us(4);
	MPU_IIC_SCL(1);
	MPU_IIC_SDA(1);
	delay_us(4);
}


// Wait for the answer signal to arrive.
// Return value: 1, receive and reply failed 0, receive and reply succeeded
uint8_t MPU_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	MPU_SDA_IN();
	MPU_IIC_SDA(1);delay_us(1);
	MPU_IIC_SCL(1);delay_us(1);
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	MPU_IIC_SCL(0);
	return 0;
}

// Generate AN ACK reply
void MPU_IIC_Ack(void)
{
	MPU_IIC_SCL(0);
	MPU_SDA_OUT();
	MPU_IIC_SDA(0);
	delay_us(2);
	MPU_IIC_SCL(1);
	delay_us(2);
	MPU_IIC_SCL(0);
}
// No ACK response is generated
void MPU_IIC_NAck(void)
{
	MPU_IIC_SCL(0);
	MPU_SDA_OUT();
	MPU_IIC_SDA(1);
	delay_us(2);
	MPU_IIC_SCL(1);
	delay_us(2);
	MPU_IIC_SCL(0);
}

// The IIC sends a byte that returns whether the slave machine answered, 1, yes, 0, no
void MPU_IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
	MPU_SDA_OUT();
    MPU_IIC_SCL(0);
    for(t=0;t<8;t++)
    {
        MPU_IIC_SDA((txd&0x80)>>7);
        txd<<=1;
		delay_us(2);
		MPU_IIC_SCL(1);
		delay_us(2);
		MPU_IIC_SCL(0);
		delay_us(2);
    }
}
// Read 1 byte, ack=1, send ACK, ack=0, send nACK
uint8_t MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();
    for(i=0;i<8;i++ )
	{
        MPU_IIC_SCL(0);
        delay_us(2);
		MPU_IIC_SCL(1);
        receive<<=1;
        if(READ_SDA)receive++;
		delay_us(1);
    }
    if (!ack)
        MPU_IIC_NAck();
    else
        MPU_IIC_Ack();
    return receive;
}
