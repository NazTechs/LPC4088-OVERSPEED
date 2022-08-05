/*****************************************************************************
 * CONFIG TRIP LATCH items
 ****************************************************************************/

void config_trip_latch_items(void) 

{
	drawString(80,220,BLACK,&arialRoundedMTBold_24ptFontInfo,"Trip Configuration");
	drawString(250,370,BLACK,&arialRoundedMTBold_16ptFontInfo,"Press ENTER to Edit Value");

}
	
/*****************************************************************************
 * CONFIG TRIP LATCH render
 ****************************************************************************/
	
	void config_trip_latch_Reneder(uint16_t config_trip_latch_sec)
{
	config_trip_latch_sec =1;
	/********************************* SECTION 1 - ENERGIZE TO TRIP ******************************/	

	if (config_trip_latch_sec & 0x01)
           drawString(400,220,BLUE,&arialRoundedMTBold_24ptFontInfo,"ENERGIZE TO TRIP");	

/********************************* SECTION 2 DE-ENERGIZE TO TRIP ****************************/	
	if (config_trip_latch_sec & 0x02)
			drawString(400,220,BLUE,&arialRoundedMTBold_24ptFontInfo,"DE-ENERGIZE TO TRIP");
	
}



/*****************************************************************************
 * Config TRIP LATCH LCD
 ****************************************************************************/
void config_trip_latch_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(394, 398, 586, 479, BLUE);

    drawString(230,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Configure Trip Latch");
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