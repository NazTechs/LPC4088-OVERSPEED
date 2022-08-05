/*----------------------------------------------------------------------------------
------------------------------------------------------------------------------------
------------------------------------------------------------------------------------

							CONFIG START LOGIC

------------------------------------------------------------------------------------
------------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/



/*****************************************************************************
 * Config start logic items
 ****************************************************************************/

void config_start_logic_items(void) 

{

		drawString(90,110,BLACK,&arialRoundedMTBold_20ptFontInfo,"Speed Fail Setpoint");
			    drawString(670,110,BLACK,&arialRoundedMTBold_24ptFontInfo,"RPM");

	    
	
	    drawString(90,155,BLACK,&arialRoundedMTBold_20ptFontInfo,"Speed Fail Trip");
	    
			
		drawString(90,200,BLACK,&arialRoundedMTBold_20ptFontInfo,"Speed Fail Alarm");
	   

        drawString(90,245,BLACK,&arialRoundedMTBold_20ptFontInfo,"Speed Fail Timeout");
	
	    drawString(90,290,BLACK,&arialRoundedMTBold_20ptFontInfo,"Speed Fail Timeout");
		drawString(670,290,BLACK,&arialRoundedMTBold_20ptFontInfo,"hh:mm:ss");

       

	    drawString(250,370,BLACK,&arialRoundedMTBold_16ptFontInfo,"Press ENTER to Edit Value");
}


/*****************************************************************************
 * Config Start Logic Reneder
 ****************************************************************************/
 
void config_start_logic_Reneder(uint8_t config_start_logic_sec)
{

/********************************* SECTION 1 - SPEED FAIL SETPOINT ******************************/	
	if (config_start_logic_sec & 0x01)
	    drawString(540,110,BLUE,&arialRoundedMTBold_24ptFontInfo,"100");
       

/********************************* SECTION 2 - SPEED FAIL TRIP ****************************/
	if (config_start_logic_sec & 0x02)	
        drawString(540,155,BLUE,&arialRoundedMTBold_24ptFontInfo,"Not Used"); 
		

/********************************* SECTION 3 SPEED FAIL ALARM***********************************/	
	if (config_start_logic_sec & 0x04)
        drawString(540,200,BLUE,&arialRoundedMTBold_24ptFontInfo,"Not Used");
		

/********************************* SECTION 4 SPEED FAIL TIMEOUT TRIP ***********************************/
	if (config_start_logic_sec & 0x08)	
        drawString(540,245,BLUE,&arialRoundedMTBold_24ptFontInfo,"Not Used"); 
		

/********************************* SECTION 5  SPEED FAIL TIMEOUT TIME *******************************/	
	if (config_start_logic_sec & 0x10)
        drawString(540,290,BLUE,&arialRoundedMTBold_24ptFontInfo,"00:00:30");
			
}


/*****************************************************************************
 * Config Start Logic LCD
 ****************************************************************************/
void config_start_logic_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(394, 398, 586, 479, BLUE);

    drawString(230,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Configure Start Logic");
	GLCD_FILLRECT(1, 71, 790, 73, BLACK);
	GLCD_FILLRECT(1, 395, 790, 397, BLACK);
	GLCD_FILLRECT(201, 395, 203, 479, BLACK);
	GLCD_FILLRECT(391, 395, 393, 479, BLACK);
	GLCD_FILLRECT(587, 395, 589, 479, BLACK);

	drawString(9, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Monitor Menu");

	drawString(231, 427,BLACK , &arialRoundedMTBold_24ptFontInfo, "Log Menu");

	drawString(406, 427, WHITE, &arialRoundedMTBold_24ptFontInfo,
			"Config Menu");

	drawString(608, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Test Menu");
}