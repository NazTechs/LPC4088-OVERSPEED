/*****************************************************************************
 *  Soheil Nazari. GENERAL RTC FUNCTION   +989122939002
 *****************************************************************************
 * FileName:        RTC.h
 * Dependencies:    
 * Processor:       LPC1768
 * Compiler:       	
 * Linker:         
 * Company:			ELLTECHS
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    14/09/2016
 *****************************************************************************/
 
 #ifndef _RTC_H

	#define _RTC_H
 
 #include "type.h"


 
 
 

uint8_t rtc_init(void);
uint8_t rtcDateUpdate(uint8_t day,uint8_t month,uint16_t year);
uint8_t rtcTimeUpdate(uint8_t sec,uint8_t min,uint16_t hour);

uint8_t rtcGetDate(uint8_t *day,uint8_t *month,uint16_t *year);
uint8_t rtcGetTime(uint8_t *sec,uint8_t *min,uint8_t *hour);
#endif
