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
 
 #include "SSD1963.h"

#ifndef _SSD1963_C
#define _SSD1963_C

 
 /******************************** GLOBAL VARIABLE ********************************/
	uint16_t _color = 0x0000;
	//int SystemCoreClock = 72000000;
	


/**************** LOCAL FUNCTION PROTOTYPE (SSD1963 SPECIFIC) ****************/

/*********************************************************************
* Function:  SetArea(start_x,start_y,end_x,end_y)
*
* PreCondition: SetActivePage(page)
*
* Input: start_x, end_x	- start column and end column
*		 start_y,end_y 	- start row and end row position (i.e. page address)
*
* Output: none
*
* Side Effects: none
*
* Overview: defines start/end columns and start/end rows for memory access
*			from host to SSD1963
* Note: none
********************************************************************/


 /*static void SetArea(uint64_t start_x, uint64_t start_y, uint64_t end_x, uint64_t end_y)
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
	
}*/


/*********************************************************************
* Function: Set a GPIO pin to state high(1) or low(0)
*
* PreCondition: Set the GPIO pin an output prior using this function
*
* Arguments: BYTE pin	- 	LCD_RESET
*							LCD_SPENA
*							LCD_SPCLK
*							LCD_SPDAT	defined under GraphicsConfig.h
*							
*			 BOOL state - 	0 for low
*							1 for high
* Return: none
*
* Note:
*********************************************************************/
static void GPIO_WR(uint8_t pin, uint8_t state)
{
	uint8_t _gpioStatus = 0;

	if(state==1)
		_gpioStatus = _gpioStatus|pin;
	else
		_gpioStatus = _gpioStatus&(~pin);

	WriteCommand(CMD_SET_GPIO_VAL);	// Set GPIO value
	WriteData(_gpioStatus);
}


/*********************************************************************
* Function:  void EnterSleepMode (void)
* PreCondition: none
* Input:  none
* Output: none
* Side Effects: none
* Overview: SSD1963 enters sleep mode
* Note: Host must wait 5mS after sending before sending next command
********************************************************************/
void EnterSleepMode (void)
{
	WriteCommand(CMD_ENT_SLEEP);
}

/*********************************************************************
* Function:  void ExitSleepMode (void)
* PreCondition: none
* Input:  none
* Output: none
* Side Effects: none
* Overview: SSD1963 enters sleep mode
* Note:   none
********************************************************************/
void ExitSleepMode (void)
{
	WriteCommand(CMD_EXIT_SLEEP);
}

/*********************************************************************
* Function		: void DisplayOff(void)
* PreCondition	: none
* Input			: none
* Output		: none
* Side Effects	: none
* Overview		: SSD1963 changes the display state to OFF state
* Note			: none
********************************************************************/
void DisplayOff(void)
{
	WriteCommand(CMD_BLANK_DISPLAY);
}

/*********************************************************************
* Function		: void DisplayOn(void)
* PreCondition	: none
* Input			: none
* Output		: none
* Side Effects	: none
* Overview		: SSD1963 changes the display state to ON state
* Note			: none
********************************************************************/
void DisplayOn(void)
{
	WriteCommand(CMD_ON_DISPLAY);
}

/*********************************************************************
* Function		: void EnterDeepSleep(void)
* PreCondition	: none
* Input			: none
* Output		: none
* Side Effects	: none
* Overview		: SSD1963 enters deep sleep state with PLL stopped
* Note			: none
********************************************************************/
void EnterDeepSleep(void)
{
	WriteCommand(CMD_ENT_DEEP_SLEEP);
}

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
void SetBacklight(uint8_t intensity)
{
	WriteCommand(CMD_SET_PWM_CONF);// Set PWM configuration for backlight control
	
	WriteData(0x0E);			// PWMF[7:0] = 2, PWM base freq = PLL/(256*(1+5))/256 = 
								// 300Hz for a PLL freq = 120MHz
  //WriteData(75);	
	WriteData(intensity);		// Set duty cycle, from 0x00 (total pull-down) to 0xFF 
								// (99% pull-up , 255/256)
	WriteData(0x01);			// PWM enabled and controlled by host (mcu)
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	
}

/*********************************************************************
* Function:  void ResetDevice()
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: Resets LCD, initializes PMP
*			Initialize low level IO port for mcu,
*			initialize SSD1963 for PCLK,
*			HSYNC, VSYNC etc
*
* Note: Need to set the backlight intensity by SetBacklight(BYTE intensity)
*		in main()
*		MCU specific. 
********************************************************************/
void ResetDevice(void)
{
	//INITAITE:SET DIRECTION
	
	CLCD_RS_OUT;
  CLCD_WR_OUT ;
  CLCD_RD_OUT ;
  CLCD_CS_OUT ;
  CLCD_RST_OUT;
	
	CLCD_DATA_OUT;
	///
	
	
	
  CLCD_RST(0);
	DelayMs_SSD(10);
	CLCD_RST(1);      // release from reset state to sleep state
		DelayMs_SSD(10);
	CLCD_RST(0);
	DelayMs_SSD(10);
	CLCD_RST(1);      // release from reset state to sleep state
  DelayMs_SSD(10);
	//Set MN(multipliers) of PLL, VCO = crystal freq * (N+1)
	//PLL freq = VCO/M with 250MHz < VCO < 800MHz
	//The max PLL freq is around 120MHz. To obtain 120MHz as the PLL freq

	WriteCommand(CMD_SET_PLL_MN);	// Set PLL with OSC = 10MHz (hardware), command is 0xE3
									// Multiplier N = 35, VCO (>250MHz)= OSC*(N+1), VCO = 360MHz
	
	WriteData(0x1E);  // 50 * 12 /2 = 300 MHZ
	WriteData(0x06);				// Divider M = 2, PLL = 360/(M+1) = 120MHz
	WriteData(0x04);				// Validate M and N values
	

	WriteCommand(CMD_PLL_START);	// Start PLL command
	
	WriteData(0x01);				// enable PLL
	

	DelayMs_SSD(15);						// wait stablize
	WriteCommand(CMD_PLL_START);	// Start PLL command again
	
	

		
	
	WriteData(0x03);				// now, use PLL output as system clock	
	DelayMs_SSD(15);
	//once PLL locked (at 120MHz), the data hold time set shortest

  WriteCommand(CMD_SOFT_RESET);	// Soft reset
	DelayMs_SSD(15);
	
	WriteCommand(CMD_SET_PCLK);		//set pixel clock (LSHIFT signal) frequency
	
	
	//Set LSHIFT freq, i.e. the DCLK with PLL freq 120MHz set previously
	//Typical DCLK for TY500TFT800480 is 33MHz
	//30MHz = 120MHz*(LCDC_FPR+1)/2^20
	//LCDC_FPR = 262143 (0x3FFFF)
	WriteCommand(CMD_SET_PCLK);		//set pixel clock (LSHIFT signal) frequency
	WriteData(0x03);
	WriteData(0xff);
	WriteData(0xff);
	/*
	WriteData(0x01);
	WriteData(0x71);
	WriteData(0x51);
	*/
	/*
	WriteData(0x03);
	WriteData(0xff);
	WriteData(0xff);
	/*
	To obtain PCLK = 5.3MHz with PLL Frequency = 120MHz,
5.3MHz = 120MHz * LCDC_FPR / 220
LCDC_FPR = 46312
	
	*/
	
	//Set panel mode, varies from individual manufacturer
	WriteCommand(CMD_SET_PANEL_MODE);
	WriteData(0x24);				// set 24-bit for TY500TFT800480 5" panel, data latch in falling edge for LSHIFT
	WriteData(0x00);				// set Hsync+Vsync mode
	WriteData((DISP_HOR_RESOLUTION-1)>>8); //Set panel size
	WriteData(DISP_HOR_RESOLUTION-1);
	WriteData((DISP_VER_RESOLUTION-1)>>8);
	WriteData(DISP_VER_RESOLUTION-1);
	
	WriteData(0x0);				//RGB sequence
	
  //	WriteData(0x1B);
	
	//Set horizontal period
	
	WriteCommand(CMD_SET_HOR_PERIOD);
	#define HT (DISP_HOR_RESOLUTION+DISP_HOR_PULSE_WIDTH+DISP_HOR_BACK_PORCH+DISP_HOR_FRONT_PORCH)
	
	WriteData((HT-1)>>8);	
	WriteData(HT-1);
	
	#define HPS (DISP_HOR_PULSE_WIDTH+DISP_HOR_BACK_PORCH)
	WriteData((HPS-1)>>8);
	WriteData(HPS-1);
	WriteData(DISP_HOR_PULSE_WIDTH-1);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	
	//Set vertical period
	
	WriteCommand(CMD_SET_VER_PERIOD);
		#define VT (DISP_VER_PULSE_WIDTH+DISP_VER_BACK_PORCH+DISP_VER_FRONT_PORCH+DISP_VER_RESOLUTION)
	
	WriteData((VT-1)>>8);
	WriteData(VT-1);
	#define VSP (DISP_VER_PULSE_WIDTH+DISP_VER_BACK_PORCH)
	WriteData((VSP-1)>>8);
	WriteData(VSP-1);
	WriteData(DISP_VER_PULSE_WIDTH-1);
	WriteData(0x00);
	WriteData(0x00);
	
	
#if (BUS_WIDTH==16)
	
	//Set pixel format, i.e. the bpp
	WriteCommand(CMD_SET_PIXEL_FORMAT);
	
	
	WriteData(0x50);
	//WriteData(0x20); 				// set 8bpp
	
	
	
	//Set pixel data interface
	WriteCommand(CMD_SET_DATA_INTERFACE);
	
	
	
WriteData(0x03);				
	//WriteData(0x03);				// 16-bit(565 format) data for 16bpp PIC32MX only
	//WriteData(0x00);				// 8-bit(565 format) data for 16bpp PIC32MX only
//Set pixel format, i.e. the bpp
//	WriteCommand(CMD_SET_PIXEL_FORMAT);
	
	
//	WriteData(0x28);
	//WriteData(0x28); 				// set 16bpp

#elif (BUS_WIDTH==8)

	//Set pixel format, i.e. the bpp
	WriteCommand(CMD_SET_PIXEL_FORMAT);
	
	
	WriteData(0x28);
	//WriteData(0x50); 				// set 16bpp
	
	
	
	//Set pixel data interface
	WriteCommand(CMD_SET_DATA_INTERFACE);
	
	
	
//WriteData(0x03);				
	//WriteData(0x03);				// 16-bit(565 format) data for 16bpp PIC32MX only
	WriteData(0x00);	
#endif


	
	WriteCommand(CMD_SET_GPIO_CONF);// Set all GPIOs to output, controlled by host
	
	WriteData(0x0f);				// Set GPIO0 as output
	WriteData(0x01);				// GPIO[3:0] used as normal GPIOs
	
	// LL Reset to LCD!!!
	GPIO_WR(LCD_SPENA, 1);
	GPIO_WR(LCD_SPCLK, 1);
	GPIO_WR(LCD_SPDAT,1);
	GPIO_WR(LCD_RESET,1);
	GPIO_WR(LCD_RESET,0);
	DelayMs_SSD(10);
	GPIO_WR(LCD_RESET,1);
	
	WriteCommand(CMD_SET_ADDR_MODE)
	WriteData(0x03);   //rotate 180 degree
	//WriteData(0x00); // NORMAL MODE
	
	WriteCommand(CMD_ON_DISPLAY);	// Turn on display; show the image on display	
	
}
/*********************************************************************
* Function: void PutPixel(SHORT x, SHORT y)
*
* PreCondition: none
*
* Input: x,y - pixel coordinates
*
* Output: none
*
* Side Effects: none
*
* Overview: puts pixel
*
* Note: 
********************************************************************/
void PutPixel(uint16_t x, uint16_t y)
{
	SetArea(x,y,DISP_HOR_RESOLUTION-1,DISP_VER_RESOLUTION-1);
	WriteCommand(CMD_WR_MEMSTART);
	WriteData(_color);
		
	
}
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
void ClearDevice(void)
{
	uint16_t	counter;
	uint16_t 	xcounter, ycounter;

	SetArea(0,0,DISP_HOR_RESOLUTION-1,DISP_VER_RESOLUTION-1);

	WriteCommand(CMD_WR_MEMSTART);

	for(ycounter=0;ycounter<DISP_VER_RESOLUTION;ycounter++)
	{
		for(xcounter=0;xcounter<DISP_HOR_RESOLUTION;xcounter++)
		{		
			#if (BUS_WIDTH==16)
			//PutPixel(xcounter,ycounter);
				WriteColor(_color);
			#elif (BUS_WIDTH==8)
			 WriteColor(_color);
			#endif
		
		}
	}

}
void PostProc(uint8_t contrast,uint8_t brightness,uint8_t saturation,uint8_t ENABLE)
{
	WriteCommand(0xBC);
	WriteData(contrast);
	WriteData(brightness);
	WriteData(saturation);
	WriteData(ENABLE);
}


void DelayMs_SSD(uint16_t delay)
{
	uint32_t i;

	for (i = (SystemCoreClock/1000) * delay; i != 0; i-- );


}

void Delay10us_SSD(uint16_t delay)
{
	uint32_t i;

	for (i = (SystemCoreClock/100000) * delay; i != 0; i-- );

}
/*********************************************************************
* Function: void ClearDevice_FAst(void)
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
void ClearDevice_F(uint16_t COLOR)
{
	uint16_t	counter;
	uint16_t 	xcounter, ycounter;
	CLCD_RD(1);
	CLCD_CS(0);

	SetArea(0,0,DISP_HOR_RESOLUTION-1,DISP_VER_RESOLUTION-1);

	WriteCommand(CMD_WR_MEMSTART);
	CLCD_RS(1);
	CLCD_CS(0);
	DATA(COLOR);
	for(ycounter=0;ycounter<DISP_VER_RESOLUTION;ycounter++)
	{
		for(xcounter=0;xcounter<DISP_HOR_RESOLUTION;xcounter++)
		{
			#if (BUS_WIDTH==16)

			CLCD_WR(0);

			CLCD_WR(1);

			#elif (BUS_WIDTH==8)
			 WriteColor(_color);
			#endif

		}
	}

}
#endif
