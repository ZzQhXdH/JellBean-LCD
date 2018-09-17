#ifndef		__LCD_H
#define		__LCD_H

#ifdef		__cplusplus
 extern "C" {
#endif
	 
#include "stm32f4xx.h"

#define LCD_WIDTH				480
#define LCD_HEIGHT				320
#define LCD_PIXELS				(LCD_WIDTH * LCD_HEIGHT)
	 
	 
void vLcdInit(void);
	 
void vLcdClear(uint16_t color);
	 
void vLcdDrawRect(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height, uint16_t color);
	 
uint16_t xLcdGetPixel(uint16_t x0, uint16_t y0);
	 
void vLcdDrawPixel(uint16_t x0, uint16_t y0, uint16_t color);
	 
void vLcdDrawRectColor(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height, const uint16_t *pColor);
	 
#ifdef		__cplusplus
 }
#endif

#endif
