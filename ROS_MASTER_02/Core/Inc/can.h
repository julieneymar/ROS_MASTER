/*
 * can.h
 *
 *  Created on: Apr 16, 2026
 *      Author: julie
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_

#include <aLLHeader.h>
extern CAN_HandleTypeDef hcan;

void Can_Init(void);

void Can_Test_Send();


#endif /* INC_CAN_H_ */
