/*
 * uart_Servo.h
 *
 *  Created on: Oct 8, 2026
 *      Author: julie
 */

#ifndef INC_UART_SERVO_H_
#define INC_UART_SERVO_H_

#include <aLLHeader.h>

// les valeurs de position
#define MEDIAN_VALUE         2000  // réference de position pour le servo
#define MID_VAL_ID6          3100

#define MID_ID5_MAX          3700
#define MID_ID5_MIN          380
#define MID_VAL_ID5          1486


#define RX_MAX_BUF           8
#define MAX_SERVO_NUM        6

// limites maximum et minimum autoriser pour le serial servo
#define MAX_PULSE            4000
#define MIN_PULSE            96


void UartServo_Ctrl(uint8_t id, uint16_t value, uint16_t time);
void UartServo_Set_Snyc_Buffer(uint16_t s1, uint16_t s2, uint16_t s3, uint16_t s4, uint16_t s5, uint16_t s6);
void UartServo_Sync_Write(uint16_t sync_time);
void UartServo_Set_Torque(uint8_t enable);
void UartServo_Set_ID(uint8_t id);


void UartServo_Get_Angle(uint8_t id);
void UartServo_Revice(uint8_t Rx_Temp);
uint8_t UartServo_Rx_Parse(void);
void Servo_Test ();

#endif /* INC_UART_SERVO_H_ */
