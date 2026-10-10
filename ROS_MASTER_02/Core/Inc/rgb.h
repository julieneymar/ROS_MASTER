/*
 * rgb.h
 *
 *  Created on: Apr 16, 2026
 *      Author: julie
 */

#ifndef INC_RGB_H_
#define INC_RGB_H_

#include <aLLHeader.h>
// extern SPI_HandleTypeDef hspi3;


#define RGB_CTRL_ALL    0xFF
#define MAX_RGB         14


typedef struct
{
    union
    {
        uint8_t Buff[9];           // Vue 1 : tableau brut de 9 octets
        struct
        {
            uint8_t G[3];          // Vert   (3 octets)
            uint8_t R[3];          // Rouge  (3 octets)
            uint8_t B[3];          // Bleu   (3 octets)
        } RGB;                      // Vue 2 : structure RGB
    } Strip[MAX_RGB];               // Tableau de 14 LEDs
} ws2812_t;

void RGB_Init(void);
void RGB_Update(void);

void RGB_Set_Color(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
void RGB_Set_Color_U32(uint8_t index, uint32_t color);
void RGB_Clear(void);

#endif /* INC_RGB_H_ */
