/*
 * MPU_I2C.h
 *
 *  Created on: Oct 8, 2026
 *      Author: julie
 */

#ifndef INC_MPU_I2C_H_
#define INC_MPU_I2C_H_

#include "aLLHeader.h"


// SCL PB13, SDA PB15
#define MPU_SDA_IN()                     \
    {                                    \
        GPIOB->CRH &= 0X0FFFFFFF;        \
        GPIOB->CRH |= (uint32_t)8 << 28; \
    }
#define MPU_SDA_OUT()                    \
    {                                    \
        GPIOB->CRH &= 0X0FFFFFFF;        \
        GPIOB->CRH |= (uint32_t)3 << 28; \
    }

#define MPU_IIC_SCL(a) HAL_GPIO_WritePin(MPU_SCL_GPIO_Port, MPU_SCL_Pin, a)
#define MPU_IIC_SDA(a) HAL_GPIO_WritePin(MPU_SDA_GPIO_Port, MPU_SDA_Pin, a)
#define READ_SDA HAL_GPIO_ReadPin(MPU_SDA_GPIO_Port, MPU_SDA_Pin)


void MPU_IIC_Delay(void);
void MPU_IIC_Init(void);
void MPU_IIC_Start(void);
void MPU_IIC_Stop(void);
void MPU_IIC_Send_Byte(uint8_t txd);
uint8_t MPU_IIC_Read_Byte(unsigned char ack);
uint8_t MPU_IIC_Wait_Ack(void);
void MPU_IIC_Ack(void);
void MPU_IIC_NAck(void);


#endif /* INC_MPU_I2C_H_ */
