/*
 * uart.h
 *
 *  Created on: Apr 15, 2026
 *      Author: julie
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include <aLLHeader.h>

void USART1_Init();
void USART1_Send_U8(uint8_t ch);
void USART_Send_ArrayU8(uint8_t *BufferPtr, uint16_t Length);

#endif /* INC_UART_H_ */
