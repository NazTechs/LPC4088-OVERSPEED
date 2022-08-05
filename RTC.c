/*****************************************************************************
 *  Soheil Nazari. RTC FUNCTION   +989122939002
 *****************************************************************************
 * FileName:        FPGA.c
 * Dependencies:    
 * Processor:       LPC4088
 * Compiler:       	
 * Linker:         
 * Company:			ELLTECHS
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    14/09/2016
 *****************************************************************************/
 
 
  #include "rtc.h"
#include <LPC407x_8x_177x_8x.h>
 
/************RTC INIT******************
 *
 * @name RTC INIT
 *
 **************************************/

uint8_t rtc_init()
{
	if (LPC_RTC ->GPREG0 == 150)
	{
		
		LPC_RTC ->GPREG1 = LPC_RTC ->GPREG1 +1;
		
			return (1);
	}
	else
	{
	
	LPC_RTC ->CCR &= !(1 << 0);

	LPC_RTC ->CCR   |=  (1 << 1);
	LPC_RTC ->CCR   &= !(1 << 1);
	
	LPC_RTC ->CCR   |=  (1 << 0);
		
	LPC_RTC ->GPREG0 = 150;
	LPC_RTC ->GPREG1 = 0;
	LPC_RTC ->GPREG2 = 0;
		
	LPC_RTC ->SEC   = 50;
	LPC_RTC ->MIN   = 43;
	LPC_RTC ->HOUR  = 17;
	LPC_RTC ->MONTH = 1;
	LPC_RTC ->YEAR  = 2017;
	LPC_RTC ->DOM  = 18;
	return (0);
	}

}

uint8_t rtcDateUpdate(uint8_t day,uint8_t month,uint16_t year)
{

	LPC_RTC ->MONTH = month;
	LPC_RTC ->YEAR  = year;
	LPC_RTC ->DOM  = day;
	return 0;
}

uint8_t rtcTimeUpdate(uint8_t sec,uint8_t min,uint16_t hour)
{

		LPC_RTC ->SEC   = sec;
		LPC_RTC ->MIN   = min;
		LPC_RTC ->HOUR  = hour;
		return 0;
}
uint8_t rtcGetDate(uint8_t *day,uint8_t *month,uint16_t *year)
{
	*day = LPC_RTC ->DOM;
	*month = LPC_RTC ->MONTH;
	*year = LPC_RTC ->YEAR;
	return 0;
}
uint8_t rtcGetTime(uint8_t *sec,uint8_t *min,uint8_t *hour)
{
	*sec = LPC_RTC ->SEC;
	*min = LPC_RTC ->MIN ;
	*hour = LPC_RTC ->HOUR;
	return 0;
}
