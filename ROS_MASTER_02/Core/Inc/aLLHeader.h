/*
 * ALLHeader.h
 *
 *  Created on: Apr 9, 2026
 *      Author: julie
 */

#ifndef INC_ALLHEADER_H_
#define INC_ALLHEADER_H_

#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "led.h"
#include "buzzer.h"
#include "tache.h"
#include "bouton.h"
#include "cmsis_os.h"
#include "can.h"
#include "uart_Servo.h"
#include "rgb.h"
#include "mpu_I2C.h"
#include "mpu9250.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"


#endif /* INC_ALLHEADER_H_ */
