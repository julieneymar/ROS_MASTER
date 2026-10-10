/*
 * led.h
 *
 *  Created on: Apr 9, 2026
 *      Author: julie
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include <aLLHeader.h>

void Led();

#define LED_ON 	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
#define LED_OFF 	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
#define LED_TOGGLE HAL_GPIO_TogglePin (LED_GPIO_Port, LED_Pin);




#endif /* INC_LED_H_ */
