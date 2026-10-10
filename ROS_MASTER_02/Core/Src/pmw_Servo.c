/*
 * pmw_Servo.c
 *
 *  Created on: Apr 17, 2026
 *      Author: julie
 */

#include "pmw_Servo.h"
extern TIM_HandleTypeDef htim7;

uint16_t g_pwm_pulse = 0;

uint8_t g_pwm_angle[MAX_PWM_SERVO] = {90, 90, 90, 90};   // angle actuelle de chaque servo
uint16_t g_angle_num[MAX_PWM_SERVO] = {149, 149, 149, 149}; // Durée d'inpulsion de chaque servo pour 90', 50 pour 0',148 pour 180'


/*
 * Conversion de l'angle en nombre d'impulsion, angle = [0, 180]
 */
static uint16_t PwmServo_Angle_To_Pulse(uint8_t angle)
{
	uint16_t pulse = (angle * 11 + 500) / 10;
	return pulse;
}

/*
 * Fonctionnement pas à pas de chaque servo controle avec le pwm
 */
void PwmServo_Handle(void)
{
    g_pwm_pulse++;  // Incrémente le compteur en us ou ticks (0 → 2000)

    // Compare chaque servomoteur
    #ifdef USE_SERVO_J1
    if (g_pwm_pulse <= g_angle_num[0])  // Si compteur ≤ impulsion requise
        SERVO_1_HIGH();                  // Sortie HIGH
    else
        SERVO_1_LOW();                   // Sortie LOW
    #endif

	#ifdef USE_SERVO_J2
		if (g_pwm_pulse <= g_angle_num[1])
			SERVO_2_HIGH();
		else
			SERVO_2_LOW();
	#endif

	#ifdef USE_SERVO_J3
		if (g_pwm_pulse <= g_angle_num[2])
			SERVO_3_HIGH();
		else
			SERVO_3_LOW();
	#endif

	#ifdef USE_SERVO_J4
		if (g_pwm_pulse <= g_angle_num[3])
			SERVO_4_HIGH();
		else
			SERVO_4_LOW();
	#endif

    //Réinitialisation du cycle
    if (g_pwm_pulse >= 2000)  // Période totale = 2000 × 10 µs = 20 ms
        g_pwm_pulse = 0;
}


/*
 * initialise les servos à 90'
 */
void PwmServo_Init (){
	for (int i = 0; i < MAX_PWM_SERVO; i++){
		g_pwm_angle[i] = 90;
		g_angle_num[i] = PwmServo_Angle_To_Pulse(g_pwm_angle[i]);
		printf("servo initialisé\n");
	}
}

/*
 * controle individuelle des servos
 */
void PwmServo_Set_Angle(uint8_t index, uint8_t angle)
{
    if (index >= MAX_PWM_SERVO) return;                     // Vérifie index valide
    if (angle > 180) return;                                // Vérifie angle valide
    g_pwm_angle[index] = angle;                             // Sauvegarde l'angle
    g_angle_num[index] = PwmServo_Angle_To_Pulse(angle);    // Convertit
}

/*
 * Controle global des servos
 */

void PwmServo_Set_Angle_All(uint8_t angle_s1, uint8_t angle_s2, uint8_t angle_s3, uint8_t angle_s4)
{
	if (angle_s1 <= 180)
	{
		g_pwm_angle[0] = angle_s1;
		g_angle_num[0] = PwmServo_Angle_To_Pulse(angle_s1);
	}

	if (angle_s2 <= 180)
	{
		g_pwm_angle[1] = angle_s2;
		g_angle_num[1] = PwmServo_Angle_To_Pulse(angle_s2);
	}

	if (angle_s3 <= 180)
	{
		g_pwm_angle[2] = angle_s3;
		g_angle_num[2] = PwmServo_Angle_To_Pulse(angle_s3);
	}

	if (angle_s4 <= 180)
	{
		g_pwm_angle[3] = angle_s4;
		g_angle_num[3] = PwmServo_Angle_To_Pulse(angle_s4);
	}
}

/*
 * boucle du débordement du timer
 * La fonction PwmServo_Handle() doit être appelée dans l'interruption du minuteur pour simuler le signal PWM de sortie et
 *  contrôler le servo en fonction de la valeur d'angle du servo définie ci-dessus.
 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == htim7.Instance)
	{
		PwmServo_Handle();
	}
}


static uint8_t key_state = 0;

void Servo(void)
{
    if (Key1_State(KEY_MODE_ONE_TIME))
    {
        if (key_state)
        {
            key_state = 0;
            printf("Position 0°\n");
            PwmServo_Set_Angle_All(0, 0, 0, 0);  // 50 ticks
        }
        else
        {
            key_state = 1;
            printf("Position 180°\n");
            PwmServo_Set_Angle_All(180, 180, 180, 180);  // 250 ticks
        }
    }
}
