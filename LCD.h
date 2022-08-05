/*****************************************************************************
 *  Soheil Nazari. LCD SSD1963 FUNCTION   +989122939002
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
 
 #ifndef _LCD__H

	#define _LCD__H
	
	#include "string.h"
	#include "stdint.h"
	#include <math.h>
	#include <stdlib.h>     /* atoi */
	#include <string.h>

	#include "SSD1963.h"
	#include "GRAPHIC.h"
	#include "GFONT.h"
	#include "MEMORY.h"
	
	void intro(void);
	void MAIN_LCD(uint8_t sections);
	void Home(void);
	void SpeedDraw(float sp, float prv_sp,uint8_t sectrions);
	void MonitorMenu(uint8_t *s_item,uint8_t sections);
	void SummeryRender(Memory *memory,uint8_t sections);
	
	void  MonitorTripLatch1Render(uint8_t sections);
	void  MonitorTripLatch2Render(uint8_t sections);
	
	
	void  MonitorAlarmLatch1Render(void);
	void  MonitorAlarmLatch2Render(void);
	
	void  MonitorDedicatedDiscreteInputsRender(void);
	void  SpeedInputRender(uint8_t sections);
	void  MonitorAnalogOutputRender(uint8_t sections);
	
	void  MonitorSpeedFailTimerRender(uint8_t sections);


	//void LogMenuReneder(uint8_t *s_item,uint8_t sections);
	void logMenuReneder(uint8_t *s_item);
	void log_alarm_Reneder(uint16_t log_alarm_sec);
	void log_alarm_items(void);

	void LcdDebugMemory(uint8_t *buffer,uint16_t bytes);

	#endif
 
 
