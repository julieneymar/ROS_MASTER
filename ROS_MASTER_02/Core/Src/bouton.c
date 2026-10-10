/*
 * bouton.c
 *
 *  Created on: Apr 9, 2026
 *      Author: julie
 */


#include "bouton.h"


static uint8_t Key1_is_Press(void){

	if(!HAL_GPIO_ReadPin(BOUTTON_1_GPIO_Port, BOUTTON_1_Pin)){
		return KEY_PRESS;
	}
	return KEY_RELEASE;
}

uint8_t Key1_State(uint8_t mode)
{
	static uint16_t key1_state = 0;

	if (Key1_is_Press() == KEY_PRESS)
	{
		if (key1_state < (mode + 1) * 2)
		{
			key1_state++;
		}
	}
	else
	{
		key1_state = 0;
	}
	if (key1_state == 2)
	{
		return KEY_PRESS;
	}
	return KEY_RELEASE;
}
