/************************************************************************
 * Configuration Speed menu items
 ************************************************************************/
 
 char config_speedMenuItems[25][40] = {"Speed Input","Acceleration","Input Logic"};
uint8_t config_speedMenuShifts[25] = {137,130,140};
ListBox config_speedMenuList = {180,100,610,380, 3 ,3,0,0,WHITE,BLACK,BLUE,WHITE,&arialRoundedMTBold_24ptFontInfo,55};

/****************************************************************
 * 			CONFIGURATION SPEED MENU
 ****************************************************************/

void config_speedMenuReneder(uint8_t *s_item)
{

		config_speedMenuList.s_item = *s_item;
		DrawList(&config_speedMenuList,config_speedMenuItems,config_speedMenuShifts);
		*s_item = config_speedMenuList.s_item;

}

/****************************************************************
 * CONFIGURATION SPEED MENU LCD STYLE
 ****************************************************************/

void config_speed_menu_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(394, 398, 586, 479, BLUE);

	drawString(300, 35, BLACK, &arialRoundedMTBold_26ptFontInfo,
			"Speed Menu");

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