/*************************SUMMERY BB*********************************/

BoolBox SpeedFailBB = { 520, 195, 645, 225, &memory1.speedfailoveride, 0, 5,
BLUE, YELLOW, WHITE, BLUE, &arialRoundedMTBold_24ptFontInfo };


/*****************************************************************************
 * MONITOR SUMMARY render
 ****************************************************************************/

void monitor_Summary_Render(Memory *memory, uint8_t sections) {
	char str[20];
	/*********************SECTION 1*************************/
	if ((sections & 0x1)) {

		drawString(80, 80, BLACK, &arialRoundedMTBold_24ptFontInfo, "Speed");
		drawString(650, 80, BLACK, &arialRoundedMTBold_24ptFontInfo, "RPM");

		drawString(80, 120, BLACK, &arialRoundedMTBold_24ptFontInfo,
				"Acceleration");
		drawString(650, 120, BLACK, &arialRoundedMTBold_24ptFontInfo, "RPM/S");

		drawString(80, 160, BLACK, &arialRoundedMTBold_24ptFontInfo,
				"Overspeed");
		drawString(240, 160, BLACK, &arialRoundedMTBold_24ptFontInfo, "Trip");
		drawString(300, 160, BLACK, &arialRoundedMTBold_24ptFontInfo,
				"Setpoint");
		drawString(650, 160, BLACK, &arialRoundedMTBold_24ptFontInfo, "RPM");

		drawString(80, 200, BLACK, &arialRoundedMTBold_24ptFontInfo, "Speed");
		drawString(180, 200, BLACK, &arialRoundedMTBold_24ptFontInfo, "Fail");
		drawString(235, 200, BLACK, &arialRoundedMTBold_24ptFontInfo,
				"Override");
		drawString(365, 200, BLACK, &arialRoundedMTBold_24ptFontInfo, "Status");

		drawString(80, 240, BLACK, &arialRoundedMTBold_24ptFontInfo, "Analog");
		drawString(200, 240, BLACK, &arialRoundedMTBold_24ptFontInfo, "Output");
		drawString(650, 240, BLACK, &arialRoundedMTBold_24ptFontInfo, "mA");

		drawString(80, 280, BLACK, &arialRoundedMTBold_24ptFontInfo, "Date");

		drawString(80, 320, BLACK, &arialRoundedMTBold_24ptFontInfo, "Time");

	}

	/*********************SECTION 2 SPEED*************************/

	if ((sections & 0x2)) {

		GLCD_FILLRECT(520, 75, 645, 105, WHITE);
		sprintf(str, "%07.2f", memory->speed/10.0);
		drawString(520, 80, BLUE, &arialRoundedMTBold_24ptFontInfo, str);

	}
	/*********************SECTION 3 ACELRATION*************************/
	if ((sections & 0x4)) {
		GLCD_FILLRECT(520, 115, 645, 145, WHITE);
		sprintf(str, "%07.2f", memory->accel/10.0);
		drawString(520, 120, BLUE, &arialRoundedMTBold_24ptFontInfo, str);

	}
	/*********************SECTION 4 OVERSPEED*************************/
	if ((sections & 0x8)) {
		float f = memory->overspeedset;
		if (f > 99999)
			f = 99999.9;
		else if (f < -99999)
			f = -99999.9;
		GLCD_FILLRECT(520, 155, 645, 185, WHITE);
		sprintf(str, "%d", memory->overspeedset/10);

		drawString(520, 160, BLUE, &arialRoundedMTBold_24ptFontInfo, str);

	}
	/*********************SECTION 5 SPEEDFAIL*************************/

	if ((sections & 0x10)) {

		if (memory->speedfailoveride == 1) {
			GLCD_FILLRECT(520, 195, 645, 195 + 30, BLUE);
			drawString(520, 200, WHITE, &arialRoundedMTBold_24ptFontInfo,
					"TRUE");
		} else if (memory->speedfailoveride == 0) {
			GLCD_FILLRECT(520, 195, 645, 195 + 30, WHITE);
			drawString(520, 200, BLUE, &arialRoundedMTBold_24ptFontInfo,
					"FALSE");

		} else {
			GLCD_FILLRECT(520, 195, 645, 195 + 30, RED);
			drawString(520, 200, WHITE, &arialRoundedMTBold_24ptFontInfo,
					"ERR");

		}
	}

	/*********************SECTION 6 ANALOG OUTPUT*************************/
	if ((sections & 0x20)) {
		float f;
		//pwm0 = (uint16_t)(40400.0*(sp1/25000.0) + 10500.0);
		f = ((float) (memory->analog1_output)) / 2447.182925;

		GLCD_FILLRECT(520, 235, 645, 235 + 30, WHITE);
		sprintf(str, "%06.3f", f);
		drawString(520, 240, BLUE, &arialRoundedMTBold_24ptFontInfo, str);

	}
	/*********************SECTION 7 DATE*************************/
	if ((sections & 0x40)) {
		GLCD_FILLRECT(520, 275, 645, 275 + 30, WHITE);
		sprintf(str, "%04d/%02d/%02d", memory->year, memory->mounth,
				memory->day);
		drawString(520, 280, BLUE, &arialRoundedMTBold_24ptFontInfo, str);
	}
	/*********************SECTION 8 TIME*************************/

	if ((sections & 0x80)) {
		GLCD_FILLRECT(520, 315, 645, 315 + 30, WHITE);
		sprintf(str, "%02d:%02d:%02d", memory->hour, memory->min, memory->sec);
		drawString(520, 320, BLUE, &arialRoundedMTBold_24ptFontInfo, str);

	}
}


 /*****************************************************************
 * MONITOR SUMMARY LCD STYLE
 ****************************************************************/
 
 
 
void monitor_summary_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(1, 397, 200, 479,BLUE);

	drawString(270,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Monitor Summary");
	
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