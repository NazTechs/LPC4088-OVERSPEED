/*****************************************************************************
 * TEST TEMPORARY OVERSPEED SETPOINT
 ****************************************************************************/

void test_tem_overspeed_setpoint_items(void) 

{

    drawString(140,85,BLACK,&arialRoundedMTBold_20ptFontInfo,"Temporary Overspeed  Trip Setpoint");
	drawString(410,130,BLACK,&arialRoundedMTBold_28ptFontInfo,"RPM");
	drawString(80,200,BLACK,&arialRoundedMTBold_20ptFontInfo,"Actual Speed");
	drawString(660,200,BLACK,&arialRoundedMTBold_20ptFontInfo,"RPM");
	drawString(80,250,BLACK,&arialRoundedMTBold_20ptFontInfo,"Overspeed  Trip Setpoint");
	drawString(660,250,BLACK,&arialRoundedMTBold_20ptFontInfo,"RPM");
	drawString(160,360,BLACK,&arialRoundedMTBold_20ptFontInfo,"Test Time Remaining");
	
}

/*****************************************************************************
 * TEST TEMPORARY OVERSPEED SETPOINT RENDER
 ****************************************************************************/
 
void test_tem_overspeed_setpoint_Reneder(uint8_t test_tem_overspeed_setpoint_sec)
{
	
	/***************************** SECTION 1 - Temporary Overspeed  Trip Setpoint  **************************/	
	if (test_tem_overspeed_setpoint_sec & 0x01)
    drawString(310,130,BLACK,&arialRoundedMTBold_28ptFontInfo,"2000 ");
	
	/***************************** SECTION 2 - Actual Speed **********************/	
	if (test_tem_overspeed_setpoint_sec & 0x02)
	drawString(560,200,BLACK,&arialRoundedMTBold_24ptFontInfo,"1600");
			
	/***************************** SECTION 3 - Overspeed  Trip Setpoint  ***********/	
	if (test_tem_overspeed_setpoint_sec& 0x04)		
	drawString(560,250,BLACK,&arialRoundedMTBold_24ptFontInfo,"3500 ");
	    
	/***************************** SECTION 4 - Test Time Remaining ******************/	
	if (test_tem_overspeed_setpoint_sec& 0x08)		
	drawString(530,360,BLACK,&arialRoundedMTBold_24ptFontInfo,"00:00:25"); 
    /***************************** SECTION 4 - Temporary Overspeed Trip Setpoint Active ******************/	
	if (test_tem_overspeed_setpoint_sec& 0x10)		
	GLCD_FILLRECT(1, 345, 788, 394,YELLOW);
	drawString(120,360,BLACK,&arialRoundedMTBold_20ptFontInfo,"Temporary Overspeed Trip Setpoint Active");
    
}

/*****************************************************************************
 * TEST TEMPORARY OVERSPEED SETPOINT LCD
 ****************************************************************************/
void test_tem_overspeed_setpoint_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(590, 397, 779, 479,BLUE);

	drawString(140,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Temporary Overspeed Setpoint Test");
	GLCD_FILLRECT(1, 71, 790, 73, BLACK);
	GLCD_FILLRECT(1, 395, 790, 397, BLACK);
	GLCD_FILLRECT(201, 395, 203, 479, BLACK);
	GLCD_FILLRECT(391, 395, 393, 479, BLACK);
	GLCD_FILLRECT(587, 395, 589, 479, BLACK);



	drawString(608, 427, WHITE, &arialRoundedMTBold_24ptFontInfo, "END TEST");
}