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
 
 #ifndef _MODBUSMNG__H

 #define _MODBUSMNG__H
	

#include "UART_LPC4088.h"
#include "type.h"
#include <stdlib.h>     /* atoi */
#include <string.h>

#include <LPC407x_8x_177x_8x.h>
#include <math.h>
#include "MEMORY.h"

//#define _LCD_DEBUG3
#ifdef _LCD_DEBUG3
									
	#include "SSD1963.h"
	#include "GRAPHIC.h"
	#include "GFONT.h"
	
		#define LCDEBUG3(args...)	{char D_str[50]; GLCD_FILLRECT(0,60,800,80,YELLOW);drawString(0,60,BLACK,&arialNarrow_20ptFontInfo,"M_DBG "); \
											sprintf(D_str,args  );drawString(100,60,BLACK,&arialNarrow_20ptFontInfo,D_str);	}
				
#else
		#define	LCDEBUG3(args...) ;
#endif
											
void initModbus(uint32_t buadRate,uint8_t add);
void chkModbus();

	#endif 
