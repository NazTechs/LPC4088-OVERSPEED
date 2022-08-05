/************************************************************************
 * Configuration menu items
 ************************************************************************/

char configurationMenuItems[25][40] = { "Speed", "Trip Latch", "Analog Output",
		"Test Modes", "Periodic Overspeed Test", "Modbus" };
uint8_t configurationMenuShifts[25] = { 170, 140, 115, 134, 39, 166 };
ListBox configurationMenuList = { 180, 100, 610, 380, 5, 6, 0, 0, WHITE, BLACK,
		BLUE, WHITE, &arialRoundedMTBold_24ptFontInfo, 55 };

/****************************************************************
 * CONFIGURATION MENU
 ****************************************************************/

void configurationMenuReneder(uint8_t *s_item) {

	configurationMenuList.s_item = *s_item;
	DrawList(&configurationMenuList, configurationMenuItems,
			configurationMenuShifts);
	*s_item = configurationMenuList.s_item;

}

/****************************************************************
 * CONFIGURATION MENU LCD STYLE
 ****************************************************************/

void CONFIG_MENU_LCD(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(394, 398, 586, 479, BLUE);

	drawString(240, 30, BLACK, &arialRoundedMTBold_26ptFontInfo,
			"Configuration Menu");

	GLCD_FILLRECT(1, 71, 790, 73, BLACK);
	GLCD_FILLRECT(1, 395, 790, 397, BLACK);
	GLCD_FILLRECT(201, 395, 203, 479, BLACK);
	GLCD_FILLRECT(391, 395, 393, 479, BLACK);
	GLCD_FILLRECT(587, 395, 589, 479, BLACK);

	drawString(9, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Monitor Menu");

	drawString(231, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Log Menu");

	drawString(406, 427, WHITE, &arialRoundedMTBold_24ptFontInfo,
			"Config Menu");

	drawString(608, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Test Menu");

}
