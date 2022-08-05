/*****************************************************************************
 *  Soheil Nazari. LCD ILI9325 FUNCTION   +989122939002
 *****************************************************************************
 * FileName:        LCD_FUNC.h
 * Dependencies:    
 * Processor:       LPC1768
 * Compiler:       	
 * Linker:         
 * Company:			ELLTECHS
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    10/19/2016
 *****************************************************************************/

#include "type.h"
#include "SSD1963.h"
#include "GRAPHIC.h"
#include "GFONT.h"


/**********************GDLOBAL DEFINE********************************
*
*********************************************************************/ 

#define NOMENU 0
#define HOME_MENU 1
#define MONITOR_MENU 2
#define MONITOR_MENU 2



/**********************GDLOBAL VARIBLE********************************
*
*********************************************************************/ 
extern _Bool Refreshed;
extern uint8_t MenuState;





void LCD_INTRO();



void DrawFrame();


void DrawHome();
void DrawConf();
void DrawTime();