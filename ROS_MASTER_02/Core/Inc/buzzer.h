/*
 * buzzer.h
 *
 *  Created on: Apr 9, 2026
 *      Author: julie
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include <aLLHeader.h>

#define BEEP_STATE_OFF       0
#define BEEP_STATE_ON_ALWAYS 1
#define BEEP_STATE_ON_DELAY  2

#define BUZZER_ON HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
#define BUZZER_OFF HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
#define BUZZER_TOGGLE HAL_GPIO_TogglePin (BUZZER_GPIO_Port, BUZZER_Pin);

#endif /* INC_BUZZER_H_ */
