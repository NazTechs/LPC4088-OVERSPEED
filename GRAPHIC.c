
#include "GRAPHIC.h"
#include <math.h>		//for fabs() in DrawLine()

/*
**********************************************************************************************************
* Line draw function from Programming The Nintendo Game Boy Advance: The Unofficial Guide
* Copyright (c)2003 by Jonathan S. Harbour -- http://www.jharbour.com
**********************************************************************************************************
*/

	


 	void PutPixel_C(uint16_t x,uint16_t y,uint32_t color)
	{
		int coltem = _color;
		_color=color;
		PutPixel(x, y);
		_color = coltem;
	}

void DrawLine(int x1, int y1, int x2, int y2, int color)
{
	int i, deltax, deltay, numpixels;
	int d, dinc1, dinc2;
	int x, xinc1, xinc2;
	int y, yinc1, yinc2;
	//calculate deltaX and deltaY
	deltax = fabs(x2 - x1);
	deltay = fabs(y2 - y1);

	//initialize
	if(deltax >= deltay)
	{
	//If x is independent variable
	numpixels = deltax + 1;
	d = (2 * deltay) - deltax;
	dinc1 = deltay << 1;
	dinc2 = (deltay - deltax) << 1;
	xinc1 = 1;
	xinc2 = 1;
	yinc1 = 0;
	yinc2 = 1;
	}
	else
	{
	//if y is independent variable
	numpixels = deltay + 1;
	d = (2 * deltax) - deltay;
	dinc1 = deltax << 1;
	dinc2 = (deltax - deltay) << 1;
	xinc1 = 0;
	xinc2 = 1;
	yinc1 = 1;
	yinc2 = 1;
	}

	//move the right direction
	if(x1 > x2)
	{
	xinc1 = -xinc1;
	xinc2 = -xinc2;
	}
	if(y1 > y2)
	{
	yinc1 = -yinc1;
	yinc2 = -yinc2;
	}

	x = x1;
	y = y1;
	//draw the pixels
	_color = color;
	for(i = 1; i < numpixels; i++)
	{
	PutPixel(x, y);
	if(d < 0)
	{
		d = d + dinc1;
		x = x + xinc1;
		y = y + yinc1;
	}
	else
	{
		d = d + dinc2;
		x = x + xinc2;
		y = y + yinc2;
	}
	}
}


void GLCD_Rectangle(uint16_t x,uint16_t y, uint16_t b, uint16_t a)
{
  uint16_t j; // zmienna pomocnicza
  // rysowanie l inii pionowych (boki)
  for (j = 0; j < a; j++) {
		PutPixel_C(x, y + j, _color);
		PutPixel_C(x + b - 1, y + j, _color);
	}
  // rysowanie linii poziomych (podstawy)
  for (j = 0; j < b; j++)	{
		PutPixel_C(x + j, y, _color);
		PutPixel_C(x + j, y + a - 1, _color);
	}
}

void GLCD_FILLRECT(uint16_t x,uint16_t y, uint16_t b, uint16_t a,uint16_t color)
{
	int i,j;
	SetArea(x,y, b, a);
	i = (abs(x-b)+1)*(abs(y-a)+1);
	WriteCommand(CMD_WR_MEMSTART);
	for (j=0; j <= i ;j++)
	WriteColor(color);
	
}
//

void GLCD_Circle(uint16_t cx, uint16_t cy ,uint16_t radius)
{
uint16_t x, y, xchange, ychange, radiusError;
x = radius;
y = 0;
xchange = 1 - 2 * radius;
ychange = 1;
radiusError = 0;
while(x >= y)
  {
  PutPixel_C(cx+x, cy+y, _color); 
  PutPixel_C(cx-x, cy+y, _color); 
  PutPixel_C(cx-x, cy-y, _color);
  PutPixel_C(cx+x, cy-y, _color); 
  PutPixel_C(cx+y, cy+x, _color); 
  PutPixel_C(cx-y, cy+x, _color); 
  PutPixel_C(cx-y, cy-x, _color); 
  PutPixel_C(cx+y, cy-x, _color); 
  y++;
  radiusError += ychange;
  ychange += 2;
  if ( 2*radiusError + xchange > 0 )
    {
    x--;
	radiusError += xchange;
	xchange += 2;
	}
  }
}

void drawCirclePoints(int cx, int cy, int x, int y, uint16_t color)
{
  if (x == 0)
  {
	  PutPixel_C(cx, cy + y, color);
	  PutPixel_C(cx, cy - y, color);
	  PutPixel_C(cx + y, cy, color);
	  PutPixel_C(cx - y, cy, color);
  }
  else if (x == y)
  {
	  PutPixel_C(cx + x, cy + y, color);
	  PutPixel_C(cx - x, cy + y, color);
	  PutPixel_C(cx + x, cy - y, color);
	  PutPixel_C(cx - x, cy - y, color);
  }
  else if (x < y)
  {
	  PutPixel_C(cx + x, cy + y, color);
	  PutPixel_C(cx - x, cy + y, color);
	  PutPixel_C(cx + x, cy - y, color);
	  PutPixel_C(cx - x, cy - y, color);
	  PutPixel_C(cx + y, cy + x, color);
	  PutPixel_C(cx - y, cy + x, color);
	  PutPixel_C(cx + y, cy - x, color);
	  PutPixel_C(cx - y, cy - x, color);
  }
}
void drawCircle (uint16_t xCenter, uint16_t yCenter, uint16_t radius, uint16_t color)
{
  int x = 0;
  int y = radius;
  int p = (5 - radius*4)/4;

  drawCirclePoints(xCenter, yCenter, x, y, color);
  while (x < y)
  {
    x++;
    if (p < 0)
    {
      p += 2*x+1;
    }
    else
    {
      y--;
      p += 2*(x-y)+1;
    }
    drawCirclePoints(xCenter, yCenter, x, y, color);
  }
}
void drawCharBitmap(const uint16_t xPixel, const uint16_t yPixel, uint16_t color, const uint8_t *glyph, uint16_t glyphHeightPages, uint16_t glyphWidthBits)
{
  uint16_t verticalPage, horizBit, currentY, currentX;
  uint16_t indexIntoGlyph;

  // set initial current y
  currentY = yPixel;
  currentX = xPixel;

  // for each page of the glyph
  for (verticalPage = glyphHeightPages; verticalPage > 0; --verticalPage)
  {
    // for each horizontol bit
    for (horizBit = 0; horizBit < glyphWidthBits; ++horizBit)
    {
      // next byte
      indexIntoGlyph = (glyphHeightPages * horizBit) + verticalPage - 1;

      currentX = xPixel + (horizBit);
      // send the data byte
      if (glyph[indexIntoGlyph] & (0X80)) PutPixel_C(currentX, currentY, color);
      if (glyph[indexIntoGlyph] & (0X40)) PutPixel_C(currentX, currentY - 1, color);
      if (glyph[indexIntoGlyph] & (0X20)) PutPixel_C(currentX, currentY - 2, color);
      if (glyph[indexIntoGlyph] & (0X10)) PutPixel_C(currentX, currentY - 3, color);
      if (glyph[indexIntoGlyph] & (0X08)) PutPixel_C(currentX, currentY - 4, color);
      if (glyph[indexIntoGlyph] & (0X04)) PutPixel_C(currentX, currentY - 5, color);
      if (glyph[indexIntoGlyph] & (0X02)) PutPixel_C(currentX, currentY - 6, color);
      if (glyph[indexIntoGlyph] & (0X01)) PutPixel_C(currentX, currentY - 7, color);
    }
    // next line of pages
    currentY += 8;
  }
}
void drawString(uint16_t x, uint16_t y, uint16_t color, const FONT_INFO *fontInfo, char *str)
{
  uint16_t currentX, charWidth, characterToOutput;
  const FONT_CHAR_INFO *charInfo;
  uint16_t charOffset;

  // set current x, y to that of requested
  currentX = x;

  // while not NULL
  while (*str != '\0')
  {
    // get character to output
    characterToOutput = *str;

    // get char info
    charInfo = fontInfo->charInfo;

    // some fonts have character descriptors, some don't
    if (charInfo != NULL)
    {
      // get correct char offset
      charInfo += (characterToOutput - fontInfo->startChar);

      // get width from char info
      charWidth = charInfo->widthBits;

      // get offset from char info
      charOffset = charInfo->offset;
    }
    else
    {
      // if no char info, char width is always 5
      charWidth = 5;

      // char offset - assume 5 * letter offset
      charOffset = (characterToOutput - fontInfo->startChar) * 5;
    }

    // Send individual characters
    drawCharBitmap(currentX, y + 1, color, &fontInfo->data[charOffset], fontInfo->heightPages, charWidth);

    // next char X
    currentX += charWidth + 1;

    // next char
    str++;
  }
}

void GLCD_Bmp (unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint16_t *bmp) {
   int    i, j;
  //uint16_t *bitmap_ptr = (uint16_t *)bmp;

  //x = DISP_HOR_RESOLUTION-x-w;
  WriteCommand(CMD_SET_COLUMN);
	WriteData(x>>8);
	WriteData(x);
	WriteData((x+w-1)>>8);
	WriteData(x+w-1);
	WriteCommand(CMD_SET_PAGE);
	WriteData(y>>8);
	WriteData(y);
	WriteData((y+h-1)>>8);
	WriteData(y+h-1);
	
	
  //wr_reg(0x50, y);                      /* Horizontal GRAM Start Address      */
  //wr_reg(0x51, y+h-1);                  /* Horizontal GRAM End   Address (-1) */
  //wr_reg(0x52, x);                      /* Vertical   GRAM Start Address      */
  //wr_reg(0x53, x+w-1);                  /* Vertical   GRAM End   Address (-1) */

  //wr_reg(0x20, y);
  //wr_reg(0x21, x);
 

 //wr_cmd(0x22);
	  bmp += (h*w)-1;
	WriteCommand(CMD_WR_MEMSTART);
	
	
  //wr_dat_start();

  	WriteCommand(CMD_WR_MEM_AUTO);
    for (i = 0; i < (w-1)*h ; i++) {
			
      WriteData(*bmp--);
		//DelayMs(1);
    };
  
  WriteCommand(CMD_NOP);

// 	bmp += h*w-1;
// for (j = 0 ; j < h ; j++)
// 	for (i=0;i < w ; i++)
// 	{
// 	_color = *bmp--;
// 	PutPixel(x + w - i ,y + w -  j);
// 		DelayMs(1);
	
}
void GLCD_SBmp (unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint16_t *bmp)
{
	 int    i, j;
	bmp += h*w-1;
for (j = 0 ; j < h ; j++)
	for (i=0;i < w ; i++)
	{
	_color = *bmp--;
	PutPixel(x + w - i ,y + w -  j);
	}
}

void GLCD_RECT_LINE (uint16_t x1,uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
 DrawLine(x1,y1,x1,y2,color);
 DrawLine(x1,y1,x2,y1,color);
 DrawLine(x2,y1,x2,y2,color);
 DrawLine(x1,y2,x2,y2,color);
}
void drawPolarLine (uint16_t x, uint16_t y , uint16_t Radius, uint16_t Angle , uint8_t Widht, uint16_t color)
{
		uint8_t i;
		uint16_t x2,y2;
	 float radian = (float)Angle / 57.295;
		x2 = Radius* cos(radian) + x;
		y2 = Radius* sin(radian) + y;
	
			for (i =0 ; i<= Widht; i++)
	
	  DrawLine(x+i,y+i,x2+i,y2+i,color);
	
}

#include <string.h>
void creatbutton(int x, int y,int width,int hight, char *text,int textpose)
{
	int len;
GLCD_FILLRECT(x,y,x+width,y+hight,RGB565CONVERT(57,44,44));
GLCD_FILLRECT(x+2,y+2,x+width - 3,y+hight-3,RGB565CONVERT(210,226,139));
len = strlen(text);
drawString(x+width/2	- ((len/2)*15) + textpose,y + hight/2 - 8 , RGB565CONVERT(57,44,44),&arial_24ptFontInfo ,text);
	
	
};

void GLCD_DOT_LINE (uint16_t x1,uint16_t y1, uint16_t x2, uint16_t y2,uint16_t Dot_Lenght,uint16_t Ratio,uint16_t color)
{
	int i, deltax, deltay, numpixels;
	int d, dinc1, dinc2;
	int x, xinc1, xinc2;
	int y, yinc1, yinc2;
	//calculate deltaX and deltaY
	deltax = fabs(x2 - x1);
	deltay = fabs(y2 - y1);

	//initialize
	if(deltax >= deltay)
	{
	//If x is independent variable
	numpixels = deltax + 1;
	d = (2 * deltay) - deltax;
	dinc1 = deltay << 1;
	dinc2 = (deltay - deltax) << 1;
	xinc1 = 1;
	xinc2 = 1;
	yinc1 = 0;
	yinc2 = 1;
	}
	else
	{
	//if y is independent variable
	numpixels = deltay + 1;
	d = (2 * deltax) - deltay;
	dinc1 = deltax << 1;
	dinc2 = (deltax - deltay) << 1;
	xinc1 = 0;
	xinc2 = 1;
	yinc1 = 1;
	yinc2 = 1;
	}

	//move the right direction
	if(x1 > x2)
	{
	xinc1 = -xinc1;
	xinc2 = -xinc2;
	}
	if(y1 > y2)
	{
	yinc1 = -yinc1;
	yinc2 = -yinc2;
	}

	x = x1;
	y = y1;
	//draw the pixels
	_color = color;
	for(i = 1; i < numpixels; i++)
	{
	if( (i/Dot_Lenght)%Ratio ==0)
	{
		PutPixel(x, y);
	}
		if(d < 0)
		{
			d = d + dinc1;
			x = x + xinc1;
			y = y + yinc1;
		}
		else
		{
			d = d + dinc2;
			x = x + xinc2;
			y = y + yinc2;
		}
	
	}
	
}
//

