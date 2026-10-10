/*
 * encoder.h
 *
 *  Created on: Oct 8, 2026
 *      Author: julie
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_
#include "aLLHeader.h"

#define ENCODER_CIRCLE           (1320)

void Encoder_Init(void);
void Encoder_Update_Count(void);
int Encoder_Get_Count_Now(uint8_t Motor_id);
void Encoder_Get_ALL(int* Encoder_all);


#endif /* INC_ENCODER_H_ */
