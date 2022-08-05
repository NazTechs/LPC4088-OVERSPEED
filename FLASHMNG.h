/*****************************************************************************
 *  Soheil Nazari. _MODBUSMNG__H FUNCTION   +989122939002
 *****************************************************************************
 * FileName:        LCD_FUNC.h
 * Dependencies:    
 * Processor:       LPC4088
 * Compiler:       	
 * Linker:         
 * Company:			TADBIR
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    1/10/2017
 *****************************************************************************/
 
 #ifndef _FLASHMNG__H

 #define _FLASHMNG__H
	

#include "flash-at45db.h"
#include "type.h"
#include <stdlib.h>     /* atoi */
#include <string.h>

#include <LPC407x_8x_177x_8x.h>
#include <math.h>
#include "MEMORY.h"

#define _LCD_DEBUG4
#ifdef _LCD_DEBUG4
									
	#include "SSD1963.h"
	#include "GRAPHIC.h"
	#include "GFONT.h"
	
		#define LCDEBUG4(args...)	{char D_str[50]; GLCD_FILLRECT(0,20,800,40,LIGHTRED);drawString(0,20,CYAN,&arialNarrow_20ptFontInfo,"F_DBG "); \
											sprintf(D_str,args  );drawString(100,20,CYAN,&arialNarrow_20ptFontInfo,D_str);	}
				
#else
		#define	LCDEBUG4(args...) ;
#endif
											
void testPage(uint16_t lenght,uint8_t *buffer);
void readTripLog(uint32_t add,uint8_t *buffer);
void writeTripLog(uint32_t add,uint8_t *buffer);
void writeTriplogLenght(uint32_t lenght);
uint32_t readTriplogLenght(void);

	#endif 
