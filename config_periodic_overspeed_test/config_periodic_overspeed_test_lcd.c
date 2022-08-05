/*****************************************************************************
 * CONFIG PERIODIC OVERSPEED items
 ****************************************************************************/

void config_periodic_overspeed_test_items(void) 

{

		
	
		drawString(60,140,BLACK,&arialRoundedMTBold_24ptFontInfo,"Periodic Test Enable");
	    
	
	    drawString(60,200,BLACK,&arialRoundedMTBold_24ptFontInfo,"Test Interval");
	     
	    
		drawString(60,260,BLACK,&arialRoundedMTBold_24ptFontInfo,"Operator can Disable Test");	
	    
		drawString(600,200,BLACK,&arialRoundedMTBold_24ptFontInfo,"Day(s)");

		
	    drawString(250,370,BLACK,&arialRoundedMTBold_16ptFontInfo,"Press ENTER to Edit Value");
}

/*****************************************************************************
 * CONFIG PERIODIC OVERSPEED render
 ****************************************************************************/
 
void config_periodic_overspeed_test_Reneder(uint8_t config_periodic_overspeed_test_sec)
{
	
	/****************************** SECTION 1 - Periodic Test Enable **************************/	
	if (config_periodic_overspeed_test_sec & 0x01)
	drawString(520,140,BLUE,&arialRoundedMTBold_24ptFontInfo,"YES");
	
	/***************************** SECTION 2 - Test Interval **********************/	
	if (config_periodic_overspeed_test_sec & 0x02)
	drawString(520,200,BLUE,&arialRoundedMTBold_24ptFontInfo,"7");
			
	/***************************** SECTION 3 - Operator can Disable Test ***********/	
	if (config_periodic_overspeed_test_sec & 0x04)		
	drawString(520,260,BLUE,&arialRoundedMTBold_24ptFontInfo,"YES");
	    
	
	
}

/*****************************************************************************
 * CONFIG PERIODIC OVERSPEED LCD
 ****************************************************************************/
void config_periodic_overspeed_test_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(394, 398, 586, 479,BLUE);

	drawString(130,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Configure Periodic Overspeed Test");
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