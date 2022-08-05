/*****************************************************************************
 *  Soheil Nazari. _MAINMENU__H FUNCTION   +989122939002
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
 
 #ifndef _MAINMENU__H

 #define _MAINMENU__H
	
	#include "SSD1963.h"
	#include "GRAPHIC.h"
	#include "GFONT.h"
	#include "type.h"
	#include "Memory.h"
	#include "LCD.h"
    #include "FLASHMNG.h"

	
	
	
#define  _LCD_DEBUG
#ifdef _LCD_DEBUG
									
		#define LCDEBUG(args...)	{char D_str[50]; GLCD_FILLRECT(0,0,800,20,LIGHTCYAN);drawString(0,0,BLACK,&arialNarrow_20ptFontInfo,"DEBUG="); \
											sprintf(D_str,args  );drawString(100,0,BLACK,&arialNarrow_20ptFontInfo,D_str);	}
				
#else
		#define	LCDEBUG(args...) ;
#endif
	
	
	#define REDRAW    0x01
	#define REFRESH0  0x02
	#define REFRESH1  0x04
	#define REFRESH2  0x08
	#define REFRESH3  0x10
	#define REFRESH4  0x20
	#define REFRESH5  0x40
	#define REFRESH6  0x80

	#define RENDER_REQ(x,y) (x) |= (y);
	#define RENDER_END(x,y) (x) &= ~(y);
	#define RENDER_CHK(x,y) (((x) & (y)) != 0)
	
	#define MENU_HOME 1
/***********************MONITOR******************************/

											
											
	#define MONITOR_MENU 2
	#define MONITOR_SUMMARY 3
	#define MONITOR_TRIP1 4
	#define MONITOR_TRIP2 5	
	#define MONITOR_ALARM1 6
	#define MONITOR_ALARM2 7
	#define MONITOR_DEDICATED_INPUT 8
	#define MONITOR_SPEED_INPUT 9
	#define MONITOR_SPEED_FAIL_TIMER 10
	#define MONITOR_ANALOG_OUTPUT 11
	#define MONITOR_MODBUS 12
	#define MONITOR_DATE_TIME 13
	#define MONITOR_SYSTEM_STATUS 14
	#define MONITOR_MODULE_INFORMATION 15


	/***********************LOG******************************/

	#define LOG_MENU 16
	#define LOG_OVRSPD_ACCEL 161
	#define LOG_TRIP 162
	#define LOG_ALARM 163
	#define LOG_PEAK_SPD_ACCEL 164
	#define LOG_RESET 165

	/** @CHANGED \MOJ 01/23/2017 **/
	/***********************CONFIG MENU******************************/

	#define CONFIG_MENU 18
	#define CONFIG_SPEED 21
	#define	CONFIG_TRIP_LATCH 22
	#define GONFIG_ANALOG_OUTPUT 23
	
	
	#define CONFIG_ANALOG_OUTPUT_1 231
	#define CONFIG_ANALOG_OUTPUT_2 232
	
	
	
	#define CONFIG_TEST_MODES 24
	#define CONFIG_PERIODIC_OVERSPEED_TEST 25
	#define CONFIG_PASSWORD_CHANGE 26
	#define CONFIG_SET_DATE_TIME 27
	#define CONFIG_MODBUS 28
	/*************************CONFIG SPEED****************************************/
	#define	CONFIG_SPEED_INPUT 29
	#define CONFIG_SPEED_ACCELERATION 30
	#define	CONFIG_SPEED_START_LOGIC	31

	/** @ENDCHANGED \MOJ 01/23/2017 **/
	

	/******************************TEST MENU********************************/
	#define	TEST_TEMPORARY_OVER_SPEED_SETPOINT 32
	#define TEST_MANUAL_SIMULATED_SPEED 33
	#define TEST_AUTO_SIMULATED_SPEED 34
	#define TEST_PERIODIC_OVERSPEED_TEST 35
	#define TEST_LAMP 36
	#define TEST_MENU 37




	extern Memory memory1;
	
	 
	extern uint8_t Menu_State;
	extern uint8_t Menu_Render;
	
	void MenuInit(void);
	void MenuMng(uint8_t key,uint8_t *MenuState,uint8_t *MenuRender);
	void MenuDraw(uint8_t *MenuState,uint8_t *MenuRender);

	#endif 
