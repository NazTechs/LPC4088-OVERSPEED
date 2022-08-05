/*****************************************************************************
 * CONFIG TEST MODE items
 ****************************************************************************/

void config_test_modes_items(void) 

{

		
		drawString(30,110,BLACK,&arialRoundedMTBold_20ptFontInfo,"Temporary Overspeed Trip");	
	    
	    drawString(670,110,BLACK,&arialRoundedMTBold_20ptFontInfo,"RPM");
	
        drawString(30,170,BLACK,&arialRoundedMTBold_20ptFontInfo,"Temp. Overspeed Trip Timeout");	
	    
	    drawString(670,170,BLACK,&arialRoundedMTBold_20ptFontInfo,"hh:mm:ss");
       
	    drawString(30,230,BLACK,&arialRoundedMTBold_20ptFontInfo,"Simulated Speed Timeout");	
	    
	    drawString(670,230,BLACK,&arialRoundedMTBold_20ptFontInfo,"hh:mm:ss");
	    
		drawString(30,290,BLACK,&arialRoundedMTBold_20ptFontInfo,"Test Mode Interlock Disable");	
	    	
	    drawString(250,370,BLACK,&arialRoundedMTBold_16ptFontInfo,"Press ENTER to Edit Value");
}

/*****************************************************************************
 * CONFIG TEST MODE render
 ****************************************************************************/
 
void config_test_modes_Reneder(uint8_t config_test_modes_sec)
{
	
	/****************************** SECTION 1 -Temporary Overspeed Trip  **************************/	
	if (config_test_modes_sec & 0x01)
	drawString(520,110,BLUE,&arialRoundedMTBold_24ptFontInfo,"2000");
	
	/***************************** SECTION 2 - Temp. Overspeed Trip Timeout **********************/	
	if (config_test_modes_sec & 0x02)
	drawString(520,170,BLUE,&arialRoundedMTBold_24ptFontInfo,"00:00:30");
			
	/***************************** SECTION 3 - Simulated Speed Timeout ***********/	
	if (config_test_modes_sec & 0x04)		
	 drawString(520,230,BLUE,&arialRoundedMTBold_24ptFontInfo,"00:00:40");
	    
	/***************************** SECTION 4 - Test Mode Interlock Disable ******************/	
	if (config_test_modes_sec & 0x08)		
	drawString(520,290,BLUE,&arialRoundedMTBold_24ptFontInfo,"NO");

	
}

/*****************************************************************************
 * CONFIG TEST MODE LCD
 ****************************************************************************/
void config_test_modes_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(394, 398, 586, 479,BLUE);

	drawString(230,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Configure Test Modes");
	GLCD_FILLRECT(1, 71, 790, 73, BLACK);
	GLCD_FILLRECT(1, 395, 790, 397, BLACK);
	GLCD_FILLRECT(201, 395, 203, 479, BLACK);
	GLCD_FILLRECT(391, 395, 393, 479, BLACK);
	GLCD_FILLRECT(587, 395, 589, 479, BLACK);

	drawString(9, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Monitor Menu");

	drawString(231, 427, BLACK , &arialRoundedMTBold_24ptFontInfo, "Log Menu");

	drawString(406, 427, WHITE, &arialRoundedMTBold_24ptFontInfo,
			"Config Menu");

	drawString(608, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Test Menu");
	
}