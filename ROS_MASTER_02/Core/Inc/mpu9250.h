/*
 * mpu9250.h
 *
 *  Created on: Oct 8, 2026
 *      Author: julie
 */

#ifndef INC_MPU9250_H_
#define INC_MPU9250_H_

#include "aLLHeader.h"

#include <stdio.h>
#include <stdint.h>

#define MPU9250_ADDR            0X68    //adresse du MPU9250 sur le bus I²C lorsque la broche AD0 est à l’état bas.
#define MPU6500_ID1				0X71  	//valeur attendue dans le registre d’identification du MPU9250.
#define MPU6500_ID2				0X73  	//valeur alternative acceptée

#define AK8963_ADDR				0X0C	//adresse I²C du magnétomètre.
#define AK8963_ID				0X48	//identifiant attendu du magnétomètre AK8963


#define MAG_WIA					0x00	//AK8963
#define MAG_CNTL1          	  	0X0A
#define MAG_CNTL2            	0X0B

#define MAG_XOUT_L				0X03
#define MAG_XOUT_H				0X04
#define MAG_YOUT_L				0X05
#define MAG_YOUT_H				0X06
#define MAG_ZOUT_L				0X07
#define MAG_ZOUT_H				0X08

//MPU6500
#define MPU_SELF_TESTX_REG		0X0D	//X
#define MPU_SELF_TESTY_REG		0X0E	//Y
#define MPU_SELF_TESTZ_REG		0X0F	//Z
#define MPU_SELF_TESTA_REG		0X10	//A
#define MPU_SAMPLE_RATE_REG		0X19	//Diviseur de fréquence d’échantillonnage
#define MPU_CFG_REG				0X1A	//Configuration du filtre passe-bas numérique
#define MPU_GYRO_CFG_REG		0X1B	//Choix de la plage de mesure du gyroscope
#define MPU_ACCEL_CFG_REG		0X1C	//Choix de la plage de mesure de l’accéléromètre
#define MPU_ACCEL_CFG_2_REG     0x1D
#define MPU_MOTION_DET_REG		0X1F
#define MPU_FIFO_EN_REG			0X23
#define MPU_I2CMST_CTRL_REG		0X24
#define MPU_I2CSLV0_ADDR_REG	0X25
#define MPU_I2CSLV0_REG			0X26
#define MPU_I2CSLV0_CTRL_REG	0X27
#define MPU_I2CSLV1_ADDR_REG	0X28
#define MPU_I2CSLV1_REG			0X29
#define MPU_I2CSLV1_CTRL_REG	0X2A
#define MPU_I2CSLV2_ADDR_REG	0X2B
#define MPU_I2CSLV2_REG			0X2C
#define MPU_I2CSLV2_CTRL_REG	0X2D
#define MPU_I2CSLV3_ADDR_REG	0X2E
#define MPU_I2CSLV3_REG			0X2F
#define MPU_I2CSLV3_CTRL_REG	0X30
#define MPU_I2CSLV4_ADDR_REG	0X31
#define MPU_I2CSLV4_REG			0X32
#define MPU_I2CSLV4_DO_REG		0X33
#define MPU_I2CSLV4_CTRL_REG	0X34
#define MPU_I2CSLV4_DI_REG		0X35


#define MPU_INTBP_CFG_REG		0X37
#define MPU_INT_EN_REG			0X38	//Activation des interruptions
#define MPU_INT_STA_REG			0X3A

#define MPU_ACCEL_XOUTH_REG		0X3B	//Octet de poids fort de l’accélération X
#define MPU_ACCEL_XOUTL_REG		0X3C
#define MPU_ACCEL_YOUTH_REG		0X3D
#define MPU_ACCEL_YOUTL_REG		0X3E
#define MPU_ACCEL_ZOUTH_REG		0X3F
#define MPU_ACCEL_ZOUTL_REG		0X40

#define MPU_TEMP_OUTH_REG		0X41
#define MPU_TEMP_OUTL_REG		0X42

#define MPU_GYRO_XOUTH_REG		0X43	//Octet de poids fort de la vitesse de rotation X
#define MPU_GYRO_XOUTL_REG		0X44
#define MPU_GYRO_YOUTH_REG		0X45
#define MPU_GYRO_YOUTL_REG		0X46
#define MPU_GYRO_ZOUTH_REG		0X47
#define MPU_GYRO_ZOUTL_REG		0X48

#define MPU_EXT_SENS_DATA_00_REG 0x49

#define MPU_I2CSLV0_DO_REG		0X63	//IIC
#define MPU_I2CSLV1_DO_REG		0X64	//IIC
#define MPU_I2CSLV2_DO_REG		0X65	//IIC
#define MPU_I2CSLV3_DO_REG		0X66

#define MPU_I2CMST_DELAY_REG	0X67
#define MPU_SIGPATH_RST_REG		0X68
#define MPU_MDETECT_CTRL_REG	0X69
#define MPU_USER_CTRL_REG		0X6A
#define MPU_PWR_MGMT1_REG		0X6B	//Gestion de l’alimentation et réveil
#define MPU_PWR_MGMT2_REG		0X6C	//Activation des axes et capteurs
#define MPU_FIFO_CNTH_REG		0X72	//FIFO
#define MPU_FIFO_CNTL_REG		0X73	//FIFO
#define MPU_FIFO_RW_REG			0X74	//FIFO
#define MPU_DEVICE_ID_REG		0X75	//Identifiant du composant



uint8_t MPU9250_Init(void);
uint8_t MPU_Write_Byte(uint8_t devaddr,uint8_t reg,uint8_t data);
uint8_t MPU_Read_Byte(uint8_t devaddr,uint8_t reg);
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr);
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr);
uint8_t MPU_Set_Rate(uint16_t rate);
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf);
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf);

uint8_t MPU_Get_Gyroscope(int16_t *gx, int16_t *gy, int16_t *gz);
uint8_t MPU_Get_Accelerometer(int16_t *ax, int16_t *ay, int16_t *az);
uint8_t MPU_Get_Magnetometer(int16_t *mx, int16_t *my, int16_t *mz);

void MPU9250_Read_Data_Handle(void);
void MPU_Delay_ms(uint16_t time);


#endif /* INC_MPU9250_H_ */
