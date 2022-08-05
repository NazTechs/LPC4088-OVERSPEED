/*****************************************************************************
 * CONFIG SPEED ACCELERATION items
 ****************************************************************************/

void config_speed_accel_items(void) 

{

		
	drawString(90,140,BLACK,&arialRoundedMTBold_24ptFontInfo,"Enable Acceleration Trip");


	drawString(90,200,BLACK,&arialRoundedMTBold_24ptFontInfo,"Accel. Trip Enable Speed");	
	drawString(700,200,BLACK,&arialRoundedMTBold_20ptFontInfo,"RPM");
		
	drawString(90,260,BLACK,&arialRoundedMTBold_24ptFontInfo,"Acceleration Trip");
	drawString(700,260,BLACK,&arialRoundedMTBold_20ptFontInfo,"RPM/s");
		

	drawString(250,370,BLACK,&arialRoundedMTBold_16ptFontInfo,"Press ENTER to Edit Value");
}

/*****************************************************************************
 * CONFIG SPEED ACCELERATION render
 ****************************************************************************/
 
void config_speed_accel_Reneder(uint8_t config_speed_accel_sec)
{
	
	/****************************** SECTION 1 - Enable Acceleration Trip **************************/	
	if (config_speed_accel_sec & 0x01)
	drawString(580,140,BLUE,&arialRoundedMTBold_24ptFontInfo,"YES");
	
	/***************************** SECTION 2 - Accel. Trip Enable Speed ***************************/	
	if (config_speed_accel_sec & 0x02)
	drawString(580,200,BLUE,&arialRoundedMTBold_24ptFontInfo,"250");
			
	/********************************* SECTION 3 - Acceleration Trip ******************************/	
	if (config_speed_accel_sec & 0x04)		
	drawString(580,260,BLUE,&arialRoundedMTBold_24ptFontInfo,"5");


	
	
}

/*****************************************************************************
 * CONFIG SPEED ACCELERATION LCD
 ****************************************************************************/
void config_speed_accel_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(394, 398, 586, 479,BLUE);

	drawString(230,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Configure Acceleration");
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