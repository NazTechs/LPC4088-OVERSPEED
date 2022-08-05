//-------------------------------------- MONITOR ANALOGE OUTPUT ----------------------------------------//

void MonitorAnalogOutputRender(uint8_t sections) {
	char str[10];
	/********************************* SECTION 1 ***********************************/
	if ((sections & 0x1)) {

		drawString(100, 160, BLACK, &arialRoundedMTBold_28ptFontInfo, "Speed");
		drawString(540, 160, BLACK, &arialRoundedMTBold_28ptFontInfo, "RPM");

		drawString(100, 240, BLACK, &arialRoundedMTBold_28ptFontInfo,
				"Analog Output");
		drawString(540, 240, BLACK, &arialRoundedMTBold_28ptFontInfo, "mA");
	}

	/********************************* SECTION 2 - SPEED ***********************************/
	if ((sections & 0x2)) {
		GLCD_FILLRECT(360, 150, 510, 190, WHITE);
		sprintf(str, "%07.1f", memory1.speed);
		drawString(360, 160, BLUE, &arialRoundedMTBold_28ptFontInfo, str);
	}
	/********************************* SECTION 3 - ANALOG OUTPUT ***********************************/
	if ((sections & 0x4)) {
		float f;
		f = ((float) (memory1.analog1_output)) / 2447.182925;
		sprintf(str, "%06.3f", f);
		GLCD_FILLRECT(360, 230, 510, 270, WHITE);
		drawString(360, 240, BLUE, &arialRoundedMTBold_28ptFontInfo, str);
	}
}

/*****************************************************************
 * MONITOR ANALOG OUTPUT LCD STYLE
 ****************************************************************/
 
 
 
void monitor_analog_output_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(1, 397, 200, 479,BLUE);

 drawString(220, 35, BLACK, &arialRoundedMTBold_24ptFontInfo,"Monitor Analog Output");	
	GLCD_FILLRECT(1, 71, 790, 73, BLACK);
	GLCD_FILLRECT(1, 395, 790, 397, BLACK);
	GLCD_FILLRECT(201, 395, 203, 479, BLACK);
	GLCD_FILLRECT(391, 395, 393, 479, BLACK);
	GLCD_FILLRECT(587, 395, 589, 479, BLACK);

	drawString(9, 427, WHITE, &arialRoundedMTBold_24ptFontInfo, "Monitor Menu");

	drawString(231, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Log Menu");

	drawString(406, 427, BLACK, &arialRoundedMTBold_24ptFontInfo,
			"Config Menu");

	drawString(608, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Test Menu");
 
 
 }