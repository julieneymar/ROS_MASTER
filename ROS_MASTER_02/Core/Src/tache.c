/*
 * tache.c
 *
 *  Created on: Apr 15, 2026
 *      Author: julie
 */


#include "tache.h"

int enable_beep = 0;



void Tache_entity_LED(){
	while(1){

		LED_TOGGLE;
		osDelay(100);
	}
}

void Tache_entity_BUZZER(){
	while(1){
		if( enable_beep ){
			BUZZER_TOGGLE;
			osDelay(100);
		} else {
			BUZZER_OFF;
			osDelay(100);
		}

	}

}

void Tache_entity_BOUTTON(){
	while(1){
		if(Key1_State(1) == KEY_PRESS){
			enable_beep = !enable_beep;

		}
		osDelay(200);
	}

}
