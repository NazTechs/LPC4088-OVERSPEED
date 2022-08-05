/*****************************************************************************
 *  Soheil Nazari. SSD1963 LCD controller driver  +989122939002
 *****************************************************************************
 * FileName:        SSD1963.h
 * Dependencies:    plib.h, SSD1963_CMD.h, TimeDelay.h, TFT.h, & system.h
 * Processor:       LPC1768
 * Compiler:       	
 * Linker:         
 * Company:			TURBINE MACHINE
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    17/06/2011
 *****************************************************************************/
#define __LPC1788
#ifndef _SSD1963_H
#define _SSD1963_H

 #include "type.h"
 	#include <LPC407x_8x_177x_8x.h>
#include "SSD1963_CMD.h"		//include the command table for SSD1963
//#include "TimeDelay.h"
#include "TFT.h"				//configuration for individual TFT panels

#ifdef __LPC1788
	 //#define BUS_WIDTH	16
	 #define BUS_WIDTH 16
#endif

extern uint16_t _color;
extern uint32_t SystemCoreClock;


/*
*****************************************************************************
* IO port definitions for Microchip LPC17xx series.
*****************************************************************************
*/

#ifdef __LPC1788


// data bus
#define SSD1963_DATA_DIR		LPC_GPIO2->DIR //PORT 2
#define SSD1963_DATA_PIN		LPC_GPIO2->PIN
#define SSD1963_DATA_SET		LPC_GPIO2->SET
#define SSD1963_DATA_CLR		LPC_GPIO2->CLR

#define SSD1963_D0			0    //OFFSET PORT

// control bus


#define SSD1963_CTRL_DIR		LPC_GPIO1->DIR
#define SSD1963_CTRL_SET		LPC_GPIO1->SET
#define SSD1963_CTRL_CLR		LPC_GPIO1->CLR

#define SSD1963_RS			(1 << 6 )
#define SSD1963_WR			(1 << 19 )
#define SSD1963_RD		  (1 << 20)

#define SSD1963_CS			(1 << 20)
#define SSD1963_FCS			(1 << 21)
#define SSD1963_RST		  (1 << 20)

#endif
/*--------------- Graphic LCD interface hardware definitions -----------------*/

#define CLCD_RS_OUT  LPC_GPIO4->DIR  |= SSD1963_RS
#define CLCD_WR_OUT  LPC_GPIO4->DIR  |= SSD1963_WR
#define CLCD_RD_OUT  LPC_GPIO4->DIR  |= SSD1963_RD
#define CLCD_CS_OUT  LPC_GPIO2->DIR  |= SSD1963_CS
#define CLCD_RST_OUT LPC_GPIO1->DIR  |= SSD1963_RST

#if (BUS_WIDTH == 16)


 //SSD1963_DATA_DIR |=  (0xFFFF ) 
#define CLCD_DATA_OUT { LPC_GPIO1->DIR |=  (0xFF << 22 );  \
												LPC_GPIO2->DIR |=  (0xFF );}

#define CLCD_DATA_IN  { LPC_GPIO1->DIR  &= ~  (0xFF << 22 );  \
												LPC_GPIO2->DIR  &= ~  (0xFF );}

					

#elif (BUS_WIDTH == 8)

#define CLCD_DATA_OUT SSD1963_DATA_DIR |= ( 0xFF << SSD1963_D0 )
#define CLCD_DATA_IN  SSD1963_DATA_DIR &= (~0xFF << SSD1963_D0 )



#else
	#pragma diag_error "BUS_WIDTH is not set"
#endif

/*-----------------------------DATA PORT-----------------------------------*/

/* SET DATA 
                                                 */
																								 
#if (BUS_WIDTH == 16)

#define DATA(x)				{ 	 \
															LPC_GPIO1->CLR = (0xFF << 22 ); \
															LPC_GPIO2->CLR = (0xFF ); \
															LPC_GPIO1->SET = (( (x  & 0xFF00 )>> 8 ) << 22 ); \
															LPC_GPIO2->SET = (x & 0xFF ); \
													}
																												
														
// 													(SSD1963_DATA_CLR = ( 0x0000FFFF <<  SSD1963_D0)); \
// 														for(i=0;i<3;i++); \
// 													(SSD1963_DATA_SET = (  x    <<  SSD1963_D0 )); \
// 											}

#elif (BUS_WIDTH == 8)

#define DATA(x)				{ 	(SSD1963_DATA_CLR |= ( 0xFF <<  SSD1963_D0)); \
													(SSD1963_DATA_SET |= (x     <<  SSD1963_D0 )); \
											}

#else
	#pragma diag_error "BUS_WIDTH is not set"
#endif


/*-----------------------------CONTROL PORT-----------------------------------*/

/* Pin RS setting to 0 or 1                                                   */
#define CLCD_RS(x)     ((x) ? (LPC_GPIO4->SET = SSD1963_RS) : (LPC_GPIO4->CLR = SSD1963_RS));
/* Pin WR setting to 0 or 1                                                   */
#define CLCD_WR(x)     ((x) ? (LPC_GPIO4->SET = SSD1963_WR) : (LPC_GPIO4->CLR = SSD1963_WR));
/* Pin RD setting to 0 or 1                                                   */
#define CLCD_RD(x)     ((x) ? (LPC_GPIO4->SET = SSD1963_RD) : (LPC_GPIO4->CLR = SSD1963_RD));
/* Pin CS setting to 0 or 1                                                   */
#define CLCD_CS(x)     ((x) ? (LPC_GPIO2->SET = SSD1963_CS) : (LPC_GPIO2->CLR = SSD1963_CS));
/* Pin RST setting to 0 or 1                                                   */
#define CLCD_RST(x)     ((x) ? (LPC_GPIO1->SET = SSD1963_RST) : (LPC_GPIO1->CLR = SSD1963_RST));

/*********************************************************************
* Macros:  WriteCommand(cmd)
*
* PreCondition:
*
* Input: cmd - controller command
*
* Output: none
*
* Side Effects: none
*
* Overview: writes command
*
* Note: Since Microchip's PMP
module is used, the syntax PMDIN = cmd
*		is used. For other MCUs, this could be PORTx=cmd that PORTx
*		is the data bus from your MCU.
********************************************************************/
#define WriteCommand(cmd) { /*		int del;*/ \
															CLCD_CS(0); \
															/*	for(del=0;del<2;del++); */\
															CLCD_RS(0); \
															/*	for(del=0;del<2;del++); */\
															CLCD_RD(1); \
															/*	for(del=0;del<2;del++); */\
															DATA(cmd); \
															/*	for(del=0;del<2;del++); */\
															CLCD_WR(0); \
															/*	for(del=0;del<2;del++); */\
														/*	CLCD_WR(1); */\
															CLCD_CS(1); \
															/*	for(del=0;del<2;del++); */\
															/*	for(del=0;del<2;del++); */\
														LPC_GPIO1->CLR = (0xFF << 22 ); \
															LPC_GPIO2->CLR = (0xFF ); \
																												};

//BYTE _gpioStatus = 0;



/*********************************************************************
* Function:  void  WriteData(WORD data)
*
* PreCondition:
*
* Input:  value - value to be written in WORD format
*
* Output: none
*
* Side Effects: none
*
* Overview:
*
* Note: Since Microchip's PMP module is used, the syntax PMDIN = data
*		is used. For other MCUs, this could be PORTx=data that PORTx
*		is the data bus from your MCU.
********************************************************************/
#define WriteData(DAT)	{		/*		int del;*/\
															DATA(DAT); \
															/*	for(del=0;del<2;del++); */\
															CLCD_CS(0); \
															/*		for(del=0;del<2;del++); */\
															CLCD_RS(1); \
															/*		for(del=0;del<2;del++); */\
															CLCD_RD(1); \
															/*		for(del=0;del<2;del++); */\
															CLCD_WR(0); \
															/*		for(del=0;del<2;del++); */\
														  /*	CLCD_WR(1);  */\
															CLCD_CS(1); \
															/*		for(del=0;del<2;del++); */\
															LPC_GPIO1->CLR = (0xFF << 22 ); \
															LPC_GPIO2->CLR = (0xFF ); \
														};

/*********************************************************************
* Function:  void  WriteData(WORD data)
*
* PreCondition:
*
* Input:  value - value to be written in WORD format
*
* Output: none
*
* Side Effects: none
*
* Overview:
*
* Note: Since Microchip's PMP module is used, the syntax PMDIN = data
*		is used. For other MCUs, this could be PORTx=data that PORTx
*		is the data bus from your MCU.
********************************************************************/
#if (BUS_WIDTH == 8)
#define WriteColor(COLOR)	{			\
															DATA((uint8_t)(COLOR>>14)); \
															CLCD_CS(0); \
															CLCD_RS(1); \
															CLCD_RD(1); \
															CLCD_WR(0); \
															CLCD_WR(1);  \
															DATA((uint8_t)(COLOR>>6)); \
															CLCD_CS(0); \
															CLCD_RS(1); \
															CLCD_RD(1); \
															CLCD_WR(0); \
															CLCD_WR(1);  \
															DATA((uint8_t)(COLOR<<2)); \
															CLCD_CS(0); \
															CLCD_RS(1); \
															CLCD_RD(1); \
															CLCD_WR(0); \
															CLCD_WR(1);  \
														};
#elif (BUS_WIDTH==16)
#define 	WriteColor(COLOR){			/* int del; */\
															DATA((uint16_t)COLOR); \
																/*	for(del=0;del<2;del++); */\
															CLCD_CS(0); \
															/*		for(del=0;del<2;del++);*/ \
															CLCD_RS(1); \
															/*		for(del=0;del<2;del++); */\
															CLCD_RD(1); \
															/*		for(del=0;del<2;del++); */\
															CLCD_WR(0); \
														/*			for(del=0;del<2;del++); */\
														/*	CLCD_WR(1); */ \
															CLCD_CS(1); \
															/*		for(del=0;del<2;del++);*/ \
															/*		for(del=0;del<2;del++); */\
															LPC_GPIO1->CLR = (0xFF << 22 ); \
															LPC_GPIO2->CLR = (0xFF ); \
														};

#endif

/*********************************************************************
* Function:  void  ReadData(WORD data)
*
* PreCondition:
*
* Input:  value - value to be written in WORD format
*
* Output: none
*
* Side Effects: none
*
* Overview:
*
* Note: Since Microchip's PMP module is used, the syntax PMDIN = data
*		is used. For other MCUs, this could be PORTx=data that PORTx
*		is the data bus from your MCU.
********************************************************************/
		#define 	ReadData(DATA){	CLCD_CS(0); \
															CLCD_RS(1); \
															CLCD_RD(0); \
															CLCD_WR(1); \
														  DATA = ( LPC_GPIO2->PIN & 0xFF ); \
															CLCD_CS(1); \
														};											
														
/*********************************************************************
* Macros: RGB565CONVERT(red, green, blue)
*
* Overview: Converts true color into 5:6:5 RGB format.
*
* PreCondition: none
*
* Input: Red, Green, Blue components.
*
* Output: 5 bits red, 6 bits green, 5 bits blue color.
*
* Side Effects: none
*
********************************************************************/
#define RGB565CONVERT(red, green, blue) (uint16_t) (((red >> 3) << 11) | ((green >>  2) << 5) | (blue >> 3))

/*********************************************************************
* Overview: Some basic colors definitions.
*********************************************************************/
#define BLACK               RGB565CONVERT(0,    0,      0)
#define BRIGHTBLUE          RGB565CONVERT(0,    0,      255)
#define BRIGHTGREEN         RGB565CONVERT(0,    255,    0)
#define BRIGHTCYAN          RGB565CONVERT(0,    255,    255)
#define BRIGHTRED           RGB565CONVERT(255,  0,      0)
#define BRIGHTMAGENTA       RGB565CONVERT(255,  0,      255)
#define BRIGHTYELLOW        RGB565CONVERT(255,  255,    0)
#define BLUE                RGB565CONVERT(0,    0,      128)
#define GREEN               RGB565CONVERT(0,    128,    0)
#define CYAN                RGB565CONVERT(0,    128,    128)
#define RED                 RGB565CONVERT(128,  0,      0)
#define MAGENTA             RGB565CONVERT(128,  0,      128)
#define BROWN               RGB565CONVERT(255,  128,    0)
#define LIGHTGRAY           RGB565CONVERT(128,  128,    128)
#define DARKGRAY            RGB565CONVERT(64,   64,     64)
#define LIGHTBLUE           RGB565CONVERT(128,  128,    255)
#define LIGHTGREEN          RGB565CONVERT(128,  255,    128)
#define LIGHTCYAN           RGB565CONVERT(128,  255,    255)
#define LIGHTRED            RGB565CONVERT(255,  128,    128)
#define LIGHTMAGENTA        RGB565CONVERT(255,  128,    255)
#define YELLOW              RGB565CONVERT(255,  255,    128)
#define WHITE               RGB565CONVERT(255,  255,    255)
                            
#define GRAY0       	      RGB565CONVERT(224,  224,    224)
#define GRAY1         	    RGB565CONVERT(192,  192,    192)   
#define GRAY2               RGB565CONVERT(160,  160,    160)   
#define GRAY3               RGB565CONVERT(128,  128,    128)
#define GRAY4               RGB565CONVERT(96,   96,     96)
#define GRAY5               RGB565CONVERT(64,   64,     64)
#define GRAY6	              RGB565CONVERT(32,   32,     32)


#define BLUE1                RGB565CONVERT(220,  220,    255)
#define YELLOW1              RGB565CONVERT(255,  255,    230)

/*********************************************************************
* Function:  void ResetDevice()
*
* Overview: Initializes LCD module.
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void ResetDevice(void);





/*********************************************************************
* Function: void PutPixel(uint16_t x, uint16_t y)
*
* Overview: Puts pixel with the given x,y coordinate position.
*
* PreCondition: none
*
* Input: x - x position of the pixel.
*		 y - y position of the pixel.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void PutPixel(uint16_t x, uint16_t y);

/*********************************************************************
* Function: void ClearDevice(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: clears screen with current color 
*
* Note: none
*
********************************************************************/
void ClearDevice(void);

/*********************************************************************
* Function:  SetScrollArea(uint16_t top, uint16_t scroll, uint16_t bottom)
*
* PreCondition: none
*
* Input: top - Top Fixed Area in number of lines from the top
*				of the frame buffer
*		 scroll - Vertical scrolling area in number of lines
*		 bottom - Bottom Fixed Area in number of lines
*
* Output: none
*
* Side Effects: none
*
* Overview:
*
* Note: Reference: section 9.22 Set Scroll Area, SSD1963 datasheet Rev0.20
*
********************************************************************/
void SetScrollArea(uint16_t top, uint16_t scroll, uint16_t bottom);

/*********************************************************************
* Function:  void  SetScrollStart(uint16_t line)
*
* Overview: First, we need to define the scrolling area by SetScrollArea()
*			before using this function. 
*
* PreCondition: SetScrollArea(uint16_t top, uint16_t scroll, uint16_t bottom)
*
* Input: line - Vertical scrolling pointer (in number of lines) as 
*		 the first display line from the Top Fixed Area defined in SetScrollArea()
*
* Output: none
*
* Note: Example -
*
*		uint16_t line=0;
*		SetScrollArea(0,272,272);
*		for(line=0;line<272;line++) {SetScrollStart(line);DelayMs(100);}
*		
*		Code above scrolls the whole page upwards in 100ms interval 
*		with page 2 replacing the first page in scrolling
********************************************************************/
void SetScrollStart(uint16_t line);

/*********************************************************************
* Function:  void EnterSleepMode (void)
* PreCondition: none
* Input:  none
* Output: none
* Side Effects: none
* Overview: SSD1963 enters sleep mode
* Note: Host must wait 5mS after sending before sending next command
********************************************************************/
void EnterSleepMode (void);

/*********************************************************************
* Function:  void ExitSleepMode (void)
* PreCondition: none
* Input:  none
* Output: none
* Side Effects: none
* Overview: SSD1963 exits sleep mode
* Note:   cannot be called sooner than 15ms
********************************************************************/
void ExitSleepMode (void);

/*********************************************************************
* Function		: void DisplayOff(void)
* PreCondition	: none
* Input			: none
* Output		: none
* Side Effects	: none
* Overview		: SSD1963 changes the display state to OFF state
* Note			: none
********************************************************************/
void DisplayOff(void);

/*********************************************************************
* Function		: void DisplayOn(void)
* PreCondition	: none
* Input			: none
* Output		: none
* Side Effects	: none
* Overview		: SSD1963 changes the display state to ON state
* Note			: none
********************************************************************/
void DisplayOn(void);

/*********************************************************************
* Function		: void EnterDeepSleep(void)
* PreCondition	: none
* Input			: none
* Output		: none
* Side Effects	: none
* Overview		: SSD1963 enters deep sleep state with PLL stopped
* Note			: none
********************************************************************/
void EnterDeepSleep(void);

/*********************************************************************
* Function:  void  SetBacklight(BYTE intensity)
*
* Overview: This function makes use of PWM feature of ssd1963 to adjust
*			the backlight intensity. 
*
* PreCondition: Backlight circuit with shutdown pin connected to PWM output of ssd1963.
*
* Input: 	(BYTE) intensity from 
*			0x00 (total backlight shutdown, PWM pin pull-down to VSS)
*			0xff (99% pull-up, 255/256 pull-up to VDD)
*
* Output: none
*
* Note: The base frequency of PWM set to around 300Hz with PLL set to 120MHz.
*		This parameter is hardware dependent
********************************************************************/
void SetBacklight(uint8_t intensity);


void DelayMs_SSD(uint16_t delay);

void Delay10us_SSD(uint16_t delay);

void ClearDevice_F(uint16_t COLOR);

static void SetArea(uint64_t start_x, uint64_t start_y, uint64_t end_x, uint64_t end_y)
{


	WriteCommand(CMD_SET_COLUMN);
	WriteData(start_x>>8);
	WriteData(start_x);
	WriteData(end_x>>8);
	WriteData(end_x);
	WriteCommand(CMD_SET_PAGE);
	WriteData(start_y>>8);
	WriteData(start_y);
	WriteData(end_y>>8);
	WriteData(end_y);

}
#endif // _SSD1963_H
