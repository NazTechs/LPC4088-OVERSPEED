/*************************MONITOR DEDICATED INPUT*********************************/

BoolBox StartInputBB = { 540, 135, 640, 165, &memory1.StartInput, 0, 5, BLUE,
WHITE, WHITE, BLUE, &arialRoundedMTBold_24ptFontInfo };
BoolBox ResetInputBB = { 540, 195, 640, 225, &memory1.ResetInput, 0, 5, BLUE,
WHITE, WHITE, BLUE, &arialRoundedMTBold_24ptFontInfo };
BoolBox SpeedFailOverideInput = { 540, 255, 640, 285,
		&memory1.SpeedFailOverideInput, 0, 5, BLUE, WHITE, WHITE, BLUE,
		&arialRoundedMTBold_24ptFontInfo };
		
		
		
//-------------------------------- MONITOR DEDICATED DISCRETE INPUT RENDER-----------------------------------//

void MonitorDedicatedDiscreteInputsRender(void) {

	/********************************* SECTION 1 ***********************************/


	drawString(100, 140, BLACK, &arialRoundedMTBold_20ptFontInfo,
			"Start Input (or start Button)");
	drawString(100, 200, BLACK, &arialRoundedMTBold_20ptFontInfo,
			"Reset Input");
	drawString(100, 260, BLACK, &arialRoundedMTBold_20ptFontInfo,
			"Speed Fail Override Input");

	/********************************* SECTION 2 - START INPUT ***********************************/

	DrawBB(&StartInputBB);

	/********************************* SECTION 3 - RESET INPUT ***********************************/

	DrawBB(&ResetInputBB);
	/********************************* SECTION 4 - SPEED FAIL OVERRIDE INPUT ***********************************/
	DrawBB(&SpeedFailOverideInput);

}

 /*****************************************************************
 * MONITOR DEDICATED LCD STYLE
 ****************************************************************/

void monitor_dedicated_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(1, 397, 200, 479,BLUE);

	drawString(140, 35, BLACK, &arialRoundedMTBold_24ptFontInfo,"Monitor Dedicated Discrete Inputs");	
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