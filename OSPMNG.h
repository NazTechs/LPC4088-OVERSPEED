/*****************************************************************************
 *  Soheil Nazari. _OSPMNG__h    +989122939002
 *****************************************************************************
 * @FileName:        OSPMNG.h
 * @Dependencies:
 * @Processor:       LPC4088
 * @Compiler:
 * @Linker:
 * @Company:			TADBIR
 *
 * @Author Soheil Nazari              Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    1/18/2017
 *****************************************************************************/


 #ifndef _OSPMNG__H

 #define _OSPMNG__H

 #include "fpga.h"
#include  "type.h"
#include "Memory.h"

//#define _LCD_DEBUG2
#ifdef _LCD_DEBUG2
									
	#include "SSD1963.h"
	#include "GRAPHIC.h"
	#include "GFONT.h"
	
		#define LCDEBUG2(args...)	{char D_str[50]; GLCD_FILLRECT(0,20,800,40,YELLOW);drawString(0,20,BLACK,&arialNarrow_20ptFontInfo,"OSP_DBG="); \
											sprintf(D_str,args  );drawString(200,20,BLACK,&arialNarrow_20ptFontInfo,D_str);	}
				
#else
		#define	LCDEBUG2(args...) ;
#endif

extern Memory memory1;


uint8_t osp_init(void);
uint8_t ospUpdate(void);


#endif
