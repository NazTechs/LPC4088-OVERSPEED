//--------------------------------------- MONITOR DATE & TIME ------------------------------------------//

void MonitorDateTimeRender(uint8_t sections) {
	char str[20];
	if ((sections & 0x1)) {
	/********************************* SECTION 1 ***********************************/

;

	drawString(180, 150, BLACK, &arialRoundedMTBold_28ptFontInfo, "Date");
	drawString(180, 220, BLACK, &arialRoundedMTBold_28ptFontInfo, "Time");
	}

	/********************************* SECTION 2 - DATE ***********************************/
	if ((sections & 0x2)) {
		char month[12][4] =  {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
	GLCD_FILLRECT(450, 140, 690, 180, WHITE);
	sprintf(str,"%02d %s %04d",memory1.day,month[memory1.mounth],memory1.year);
	drawString(460, 150, BLUE, &arialRoundedMTBold_28ptFontInfo, str);
	}

	/********************************* SECTION 3 - TIME ***********************************/
	if ((sections & 0x4)) {
	GLCD_FILLRECT(450, 210, 620, 250, WHITE);
	sprintf(str, "%02d:%02d:%02d", memory1.hour, memory1.min, memory1.sec);
	drawString(460, 220, BLUE, &arialRoundedMTBold_28ptFontInfo, str);
	}

}

/*****************************************************************
 * MONITOR DATE & TIME LCD STYLE
 ****************************************************************/
 
 
 
void monitor_date_time_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(1, 397, 200, 479,BLUE);

	GLCD_FILLRECT(1, 71, 790, 73, BLACK);
	GLCD_FILLRECT(1, 395, 790, 397, BLACK);
	GLCD_FILLRECT(201, 395, 203, 479, BLACK);
	GLCD_FILLRECT(391, 395, 393, 479, BLACK);
	GLCD_FILLRECT(587, 395, 589, 479, BLACK);

	
	drawString(220, 35, BLACK, &arialRoundedMTBold_24ptFontInfo,"Monitor/Set Date & Time");	

	drawString(9, 427, WHITE, &arialRoundedMTBold_24ptFontInfo, "Monitor Menu");

	drawString(231, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Log Menu");

	drawString(406, 427, BLACK, &arialRoundedMTBold_24ptFontInfo,
			"Config Menu");

	drawString(608, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Test Menu");
 
 
 }