/*
 * motion.h
 *
 *  Created on: Oct 9, 2026
 *      Author: julie
 */

#ifndef INC_MOTION_H_
#define INC_MOTION_H_

#include "aLLHeader.h"



#include "stdint.h"

#define ENABLE_REAL_WHEEL    (0)
#define YAW_ADJUST           (1)
#define YAW_NO_ADJUST        (0)

// The displacement of a wheel in one complete turn, Unit: mm
#define MECANUM_MINI_CIRCLE_MM       (204.203f)

// Half of the sum of the chassis motor spacing
#define MECANUM_MINI_APB             (164.555f)


// Stop mode, STOP_FREE: stop freely, STOP_BRAKE: brake
typedef enum _stop_mode {
    STOP_FREE = 0,
    STOP_BRAKE
} stop_mode_t;

// The speed structure of the car
typedef struct _car_data
{
    int16_t Vx;       // déplacement longitudinal, avant ou arriere
    int16_t Vy;      // déplacement latéral, gauche droite
    int16_t Vz;      // rotation autour de l'axe vertical
} car_data_t;


void Motion_Stop(uint8_t brake);
void Motion_Set_Pwm(int16_t Motor_1, int16_t Motor_2, int16_t Motor_3, int16_t Motor_4);
void Motion_Ctrl(int16_t V_x, int16_t V_y, int16_t V_z);

void Motion_Get_Encoder(void);
void Motion_Set_Speed(int16_t speed_m1, int16_t speed_m2, int16_t speed_m3, int16_t speed_m4);

void Motion_Handle(void);

void Motion_Get_Speed(car_data_t* car);
float Motion_Get_Circle_MM(void);
float Motion_Get_APB(void);

#endif /* INC_MOTION_H_ */
