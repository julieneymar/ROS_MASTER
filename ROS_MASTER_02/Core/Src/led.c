/*
 * led.c
 *
 *  Created on: Apr 9, 2026
 *      Author: julie
 */

#include "led.h"
#include <stdio.h>


void Led(){
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	HAL_Delay(20000);
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
	HAL_Delay(20000);
}


