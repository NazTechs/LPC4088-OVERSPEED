/*
**********************************************************************************************************
* GRAPHIC FUNCTION FOR SSD1963
*
*
*
**********************************************************************************************************
*/


#ifndef _graphic_ssd1963

	#define _graphic_ssd1963


#include "type.h"
#include "GFONT.h"
#include "SSD1963.h"


void PutPixel_C(uint16_t x,uint16_t y,uint32_t color);

void DrawLine(int x1, int y1, int x2, int y2, int color);

void GLCD_Rectangle(uint16_t x,uint16_t y, uint16_t b, uint16_t a);

void GLCD_FILLRECT(uint16_t x,uint16_t y, uint16_t b, uint16_t a,uint16_t color);

void GLCD_Circle(uint16_t cx, uint16_t cy ,uint16_t radius);

void drawCirclePoints(int cx, int cy, int x, int y, uint16_t color);

void drawCircle (uint16_t xCenter, uint16_t yCenter, uint16_t radius, uint16_t color);

void drawCharBitmap(const uint16_t xPixel, const uint16_t yPixel, uint16_t color, const uint8_t *glyph, uint16_t glyphHeightPages, uint16_t glyphWidthBits);

void drawString(uint16_t x, uint16_t y, uint16_t color, const FONT_INFO *fontInfo, char *str);

void GLCD_Bmp (unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint16_t *bmp);

void GLCD_SBmp (unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint16_t *bmp);

void GLCD_RECT_LINE (uint16_t x1,uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);

void drawPolarLine (uint16_t x, uint16_t y , uint16_t Radius, uint16_t Angle , uint8_t Widht , uint16_t color);

void creatbutton(int x, int y,int width,int hight, char *text,int textpose);

void GLCD_DOT_LINE (uint16_t x1,uint16_t y1, uint16_t x2, uint16_t y2,uint16_t Dot_Lenght,uint16_t Ratio,uint16_t color);
	
#endif
