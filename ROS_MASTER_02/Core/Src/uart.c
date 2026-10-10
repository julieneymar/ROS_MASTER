/*
 * uart.c
 *
 *  Created on: Apr 15, 2026
 *      Author: julie
 */


#include "uart.h"
extern UART_HandleTypeDef huart1;

uint8_t RxTemp = 0;


/*
 * initialisation
 */
void USART1_Init(){
	HAL_UART_Receive_IT(&huart1, (uint8_t *)RxTemp, 1);
}

/*
 * transfert d'un octet
 */

void USART1_Send_U8(uint8_t ch){
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF );
}


void USART_Send_ArrayU8(uint8_t *BufferPtr, uint16_t Length){

	#if ENABLE_UART_DMA
		 HAL_UART_Transmit_DMA(&huart1, BufferPtr, Length);
	#else
		while (Length--)
		{
			USART1_Send_U8(*BufferPtr);
			BufferPtr++;
		}
	#endif
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	UNUSED(huart);

	USART1_Send_U8(RxTemp);

	HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxTemp, 1);
}

/*
 * Redéfini la fonction printf pour utiliser le port série 1 afin d'envoyer des données.
 */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{

    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
