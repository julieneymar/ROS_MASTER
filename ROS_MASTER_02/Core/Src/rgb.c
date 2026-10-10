/*
 * ggb.c
 *
 *  Created on: Apr 16, 2026
 *      Author: julie
 */


#define TIMING_ONE           0x06
#define TIMING_ZERO          0x04

#include "rgb.h"
#define INTERVAL     50



// Store the color information of the light bar
ws2812_t g_ws2812 = {0};

// transmitter data
static void WS2812_Send_Data(uint8_t *buf, uint16_t buf_size)
{
//	HAL_SPI_Transmit_DMA(&hspi3, buf, buf_size);
}

// index=[0, MAX_RGB-1]，RGB=[0x00000000, 0x00FFFFFF]
// Set single RGB light color value, index=[0, MAX_RGB-1], RGB=[0x00000000, 0x00FFFFFF]
static void WS2812_Set_Color_One(uint8_t index, uint32_t RGB)
{
    if (index >= MAX_RGB) return;
    uint8_t i;
    uint32_t TempR = 0, TempG = 0, TempB = 0;

    for(i = 0; i < 8; i++)
    {
        (RGB & 0x00010000) == 0 ? (TempR |= (TIMING_ZERO<<(i*3))) : (TempR |= (TIMING_ONE<<(i*3)));
        (RGB & 0x00000100) == 0 ? (TempG |= (TIMING_ZERO<<(i*3))) : (TempG |= (TIMING_ONE<<(i*3)));
        (RGB & 0x00000001) == 0 ? (TempB |= (TIMING_ZERO<<(i*3))) : (TempB |= (TIMING_ONE<<(i*3)));
        RGB >>= 1;
    }
    for (i = 0; i < 3; i++)
    {
        g_ws2812.Strip[index].RGB.R[i] = TempR >> (16-8*i);
        g_ws2812.Strip[index].RGB.G[i] = TempG >> (16-8*i);
        g_ws2812.Strip[index].RGB.B[i] = TempB >> (16-8*i);
    }
}


// Initializes the indicator bar
void RGB_Init(void)
{
	RGB_Clear();
	RGB_Update();
}

// Refresh RGB light bar color. This function must be called to update the display after the RGB color is modified by the function call below.
void RGB_Update(void)
{
    WS2812_Send_Data((uint8_t*)&g_ws2812.Strip[0].Buff, 9*MAX_RGB);
}

// Set the color, index=[0, max_RGB-1] controls the corresponding bead color, index=0xFF controls all the bead color.
void RGB_Set_Color(uint8_t index, uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t color = r << 16 | g << 8 | b;
    RGB_Set_Color_U32(index, color);
}

// Set the RGB bar color value, index=[0, max_RGB-1] controls the corresponding bead color, index=255 controls all the bead color.
void RGB_Set_Color_U32(uint8_t index, uint32_t color)
{
    if (index < MAX_RGB)
    {
        WS2812_Set_Color_One(index, color);
        return;
    }
    if (index == RGB_CTRL_ALL)
    {
        for (uint16_t i = 0; i < MAX_RGB; i++)
        {
            WS2812_Set_Color_One(i, color);
        }
    }
}

// Clear color (off)
void RGB_Clear(void)
{
    for (uint8_t i = 0; i < MAX_RGB; i++)
    {
        WS2812_Set_Color_One(i, 0);
    }
}

void Rgb_fonction(){
	printf("hoolla");

	// RED
	RGB_Set_Color(index, 0xff, 0x00, 0x00);
	RGB_Update();

	HAL_Delay(10);
	// GREEN
	RGB_Set_Color(index, 0x00, 0xff, 0x00);
	RGB_Update();

	HAL_Delay(10);

	// BLUE
	RGB_Set_Color(index, 0x00, 0x00, 0xff);
	RGB_Update();

}
