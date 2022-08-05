/************************************************************************
 * AnalogOutput menu items
 ************************************************************************/

char analogMenuItems[25][40] = {"Analog Output 1","Analog Output 2"};
uint8_t analogMenuShifts[25] = {50,50};
ListBox analogMenuList = {180,100,610,380, 5 ,2,0,0,WHITE,BLACK,BLUE,
		WHITE,&arialRoundedMTBold_24ptFontInfo,55};




/*****************************************************************************
 * CONFIG ANALOG OUTPUT items
 ****************************************************************************/

void config_analog_output_items(void)

{



	/*drawString(120,180,BLACK,&arialRoundedMTBold_24ptFontInfo,"Speed @ 4mA");
    drawString(650,180,BLACK,&arialRoundedMTBold_20ptFontInfo,"RPM");

	drawString(120,240,BLACK,&arialRoundedMTBold_24ptFontInfo,"Speed @ 20mA");
    drawString(650,240,BLACK,&arialRoundedMTBold_20ptFontInfo,"RPM");	*/

	//drawString(250,370,BLACK,&arialRoundedMTBold_16ptFontInfo,"Press ENTER to Edit Value");
}

/*****************************************************************************
 * CONFIG ANALOG OUTPUT render
 ****************************************************************************/

void config_analog_output_Reneder(uint8_t *s_item)
{
analogMenuList.s_item = *s_item;;
DrawList(&analogMenuList,analogMenuItems,analogMenuShifts);
*s_item = analogMenuList.s_item;


	/****************************** SECTION 1 - Speed @ 4mA ***********************/
	/*if (config_analog_output_sec & 0x01)
	drawString(500,180,BLUE,&arialRoundedMTBold_24ptFontInfo,"0");*/

	/*****************************  SECTION 2 - Speed @ 20mA ***********************/
	/*if (config_analog_output_sec & 0x02)
	drawString(500,240,BLUE,&arialRoundedMTBold_24ptFontInfo,"5000");*/


}

/*****************************************************************************
 * CONFIG ANALOG OUTPUT LCD
 ****************************************************************************/
void config_analog_output_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(394, 398, 586, 479,BLUE);

	drawString(210,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Configure Analog Output");
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
