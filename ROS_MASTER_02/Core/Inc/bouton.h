/*
 * bouton.h
 *
 *  Created on: Apr 9, 2026
 *      Author: julie
 */

#ifndef INC_BOUTON_H_
#define INC_BOUTON_H_
#include <aLLHeader.h>

#define KEY_PRESS  1
#define KEY_RELEASE 0

#define KEY_MODE_ONE_TIME  1
#define  KEY_MODE_ALWAYS  0

uint8_t Key1_State(uint8_t mode);

#endif /* INC_BOUTON_H_ */
