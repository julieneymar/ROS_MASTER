/*
 * encoder.c
 *
 *  Created on: Oct 8, 2026
 *      Author: julie
 */


#include "encoder.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;



int g_Encoder_M1_Now = 0;
int g_Encoder_M2_Now = 0;
int g_Encoder_M3_Now = 0;
int g_Encoder_M4_Now = 0;

/**
 * @Brief: To read the encoder count, call every 10 milliseconds
 * @Note:
 * @Parm: Motor id :MOTOR_ID_M1, MOTOR_ID_M2, MOTOR_ID_M3, MOTOR_ID_M4
 * @Retval: Returns encoder count data
 */
static int16_t Encoder_Read_CNT(uint8_t Motor_id)
{
	int16_t Encoder_TIM = 0;
	switch(Motor_id)
	{
	case MOTOR_ID_M1:  Encoder_TIM = (short)TIM2 -> CNT; TIM2 -> CNT = 0; break;
	case MOTOR_ID_M2:  Encoder_TIM = (short)TIM4 -> CNT; TIM4 -> CNT = 0; break;
	case MOTOR_ID_M3:  Encoder_TIM = (short)TIM5 -> CNT; TIM5 -> CNT = 0; break;
	case MOTOR_ID_M4:  Encoder_TIM = (short)TIM3 -> CNT; TIM3 -> CNT = 0; break;
	default:  break;
	}
	return Encoder_TIM;
}


// Lire le comptage d'un seul moteur
int Encoder_Get_Count_Now(uint8_t Motor_id)
{
	if (Motor_id == MOTOR_ID_M1) return g_Encoder_M1_Now;
	if (Motor_id == MOTOR_ID_M2) return g_Encoder_M2_Now;
	if (Motor_id == MOTOR_ID_M3) return g_Encoder_M3_Now;
	if (Motor_id == MOTOR_ID_M4) return g_Encoder_M4_Now;
	return 0;
}

// Lire les quatre moteurs simultanément
void Encoder_Get_ALL(int* Encoder_all)
{
	Encoder_all[0] = g_Encoder_M1_Now;
	Encoder_all[1] = g_Encoder_M2_Now;
	Encoder_all[2] = g_Encoder_M3_Now;
	Encoder_all[3] = g_Encoder_M4_Now;
}

// Update the count value of the encoder. call every 10 milliseconds
void Encoder_Update_Count(void)
{
	// g_Encoder_M1_Now += Encoder_Read_CNT(MOTOR_ID_M1);
	g_Encoder_M1_Now -= Encoder_Read_CNT(MOTOR_ID_M1);

	g_Encoder_M2_Now += Encoder_Read_CNT(MOTOR_ID_M2);
	// g_Encoder_M2_Now -= Encoder_Read_CNT(MOTOR_ID_M2);

	g_Encoder_M3_Now += Encoder_Read_CNT(MOTOR_ID_M3);
	// g_Encoder_M3_Now -= Encoder_Read_CNT(MOTOR_ID_M3);

	// g_Encoder_M4_Now += Encoder_Read_CNT(MOTOR_ID_M4);
	g_Encoder_M4_Now -= Encoder_Read_CNT(MOTOR_ID_M4);
}

// Initializing timer
void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_1 | TIM_CHANNEL_2);
}



int encoder[4] = {0};
int show_encoder = 0;


void Test_encoder(void)
{
	if (Key1_State(KEY_MODE_ONE_TIME))
	{
		static int state = 0;
		state++;
		int speed = 0;
		if (state == 1)
		{
			speed = 2000;
			Motor_Set_Pwm(MOTOR_ID_M1, speed);
			Motor_Set_Pwm(MOTOR_ID_M2, speed);
			Motor_Set_Pwm(MOTOR_ID_M3, speed);
			Motor_Set_Pwm(MOTOR_ID_M4, speed);
		}
		if (state == 2)
		{
			Motor_Stop(0);
		}
		if (state == 3)
		{
			speed = -2000;
			Motor_Set_Pwm(MOTOR_ID_M1, speed);
			Motor_Set_Pwm(MOTOR_ID_M2, speed);
			Motor_Set_Pwm(MOTOR_ID_M3, speed);
			Motor_Set_Pwm(MOTOR_ID_M4, speed);
		}
		if (state == 4)
		{
			state = 0;
			Motor_Stop(1);
		}
	}

	show_encoder++;
	if (show_encoder > 10)
	{
		show_encoder = 0;
		Encoder_Get_ALL(encoder);
		printf("Encoder:%d, %d, %d, %d\n", encoder[0], encoder[1], encoder[2], encoder[3]);
	}

	Encoder_Update_Count();
	LED_ON;
	HAL_Delay(10);
}

