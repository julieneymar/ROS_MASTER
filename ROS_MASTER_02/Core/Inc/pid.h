/*
 * pid.h
 *
 *  Created on: Oct 9, 2026
 *      Author: julie
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include "aLLHeader.h"

#include "stdint.h"

#define PID_DEF_KP      (0.8f)
#define PID_DEF_KI      (0.06f)
#define PID_DEF_KD      (0.5f)

typedef struct _pid_t
{
    float target_val;             // Vitesse demandée
    float pwm_output;        		// Commande calculée par le PID
    float Kp,Ki,Kd;          		// Gain proportionnel, Gain intégral, Gain dérivé
    float err;             			// Erreur actuelle
    float err_last;          		// Erreur conservée d'un calcul précéde

    float err_next;                 // Erreur du calcul précédent dans la formule utilisée
    float integral;          		// Variable prévue pour stocker une intégrale, mais non utilisée dans ce calcul
} motor_pid_t;

typedef struct _motor_data_t
{
    float speed_mm_s[4];        // Input value, encoder calculation speed
    float speed_pwm[4];         // Output value, PID calculates PWM value
    int16_t speed_set[4];       // Speed setting value
} motor_data_t;


void PID_Param_Init(void);
void PID_Calc_Motor(motor_data_t* motor);
void PID_Set_Motor_Target(uint8_t motor_id, float target);
void PID_Clear_Motor(uint8_t motor_id);
void PID_Set_Motor_Parm(uint8_t motor_id, float kp, float ki, float kd);

#endif /* INC_PID_H_ */
