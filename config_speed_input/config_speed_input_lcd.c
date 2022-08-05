/*----------------------------------------------------------------------------------
------------------------------------------------------------------------------------
------------------------------------------------------------------------------------

							CONFIG SPEED INPUT

------------------------------------------------------------------------------------
------------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/



/*****************************************************************************
 * Config speed input items
 ****************************************************************************/

void config_speed_input_items(void) 

{

			
		drawString(90,110,BLACK,&arialRoundedMTBold_20ptFontInfo,"Probe Type");
	   
	
		drawString(90,155,BLACK,&arialRoundedMTBold_20ptFontInfo,"Nr of Gear Teeth");	
	    
	
		drawString(90,200,BLACK,&arialRoundedMTBold_20ptFontInfo,"Gear Ratio");
	   

		drawString(90,245,BLACK,&arialRoundedMTBold_20ptFontInfo,"Overspeed Trip");
		
		drawString(650,245,BLACK,&arialRoundedMTBold_20ptFontInfo,"RPM");
		
	
		drawString(90,290,BLACK,&arialRoundedMTBold_20ptFontInfo,"Sudden Speed Loss");
	    						
						
	    drawString(250,370,BLACK,&arialRoundedMTBold_16ptFontInfo,"Press ENTER to Edit Value");
}


/*****************************************************************************
 * Config speed Input
 ****************************************************************************/
 
void config_speed_input_Reneder(uint8_t config_speed_input_sec)
{

/********************************* SECTION 1 - PROBE TYPE ******************************/	
	if (config_speed_input_sec & 0x01)
        drawString(580,110,BLUE,&arialRoundedMTBold_24ptFontInfo,"PASSIVE");	

/********************************* SECTION 2 NUMBER OF GEAR TEETH ****************************/	
	if (config_speed_input_sec & 0x02)
		drawString(580,155,BLUE,&arialRoundedMTBold_24ptFontInfo,"20");

/********************************* SECTION 3 GEAR RATIO ***********************************/	
	if (config_speed_input_sec & 0x04)
		drawString(580,200,BLUE,&arialRoundedMTBold_24ptFontInfo,"5");	

/********************************* SECTION 4 OVERSPEED TRIP ***********************************/	
	if (config_speed_input_sec & 0x08)
		drawString(580,245,BLUE,&arialRoundedMTBold_20ptFontInfo,"1000");

/********************************* SECTION 5 SUDDEN SPEED LOSS *******************************/	
	if (config_speed_input_sec & 0x10)
        drawString(580,290,BLUE,&arialRoundedMTBold_24ptFontInfo,"TRIP");
			
}


/*****************************************************************************
 * Config Speed Input LCD
 ****************************************************************************/
void config_speed_input_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(394, 398, 586, 479,BLUE);

    drawString(290,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Speed Input");
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