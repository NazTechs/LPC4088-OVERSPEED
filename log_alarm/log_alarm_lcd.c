/*----------------------------------------------------------------------------------
------------------------------------------------------------------------------------
------------------------------------------------------------------------------------

							LOG ALARM

------------------------------------------------------------------------------------
------------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/



/*****************************************************************************
 * Log alarm items
 ****************************************************************************/

void log_alarm_items(void)
{

	drawString(320,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Alarm Log");
	
	drawString(150,80,BLACK,&arialRoundedMTBold_16ptFontInfo,"Event ID");
	drawString(450,80,BLACK,&arialRoundedMTBold_16ptFontInfo,"Time Stamp");	
	drawString(710,80,BLUE,&arialRoundedMTBold_16ptFontInfo,"Test");
	GLCD_FILLRECT(9,100,790,101,BLACK);	
		
	GLCD_FILLRECT(2,350,790,352,BLACK);                               
	drawString(300,360,BLACK,&webdings_26ptFontInfo,"3");
	drawString(330,364,BLACK,&arialNarrow_20ptFontInfo,"PAGE   of");
	drawString(466,360,BLACK,&webdings_26ptFontInfo,"4");
}


/*****************************************************************************
 * Log alarm render
 ****************************************************************************/
 
void log_alarm_Reneder(uint16_t log_alarm_sec)
{

/********************************* SECTION 1 - AUTO SIM SPEED TEST ******************************/	

	if (log_alarm_sec & 0x0001)
           drawString(30,115,BLACK,&arialRoundedMTBold_20ptFontInfo,"Auto Sim. Speed Test");	

/********************************* SECTION 2 PERIODIC OVERSPEDD TEST ****************************/	
	if (log_alarm_sec & 0x0002)
			drawString(30,115+40,BLACK,&arialRoundedMTBold_20ptFontInfo,"Periodic Ovrspd Test");

/********************************* SECTION 3 SPEED LOST ALARM ***********************************/	
	if (log_alarm_sec & 0x0004)
			drawString(30,115 + 80,BLACK,&arialRoundedMTBold_20ptFontInfo,"Speed Lost Alarm");

/********************************* SECTION 4 SPEED FAIL ALARM ***********************************/	
	if (log_alarm_sec & 0x0008)
			drawString(30,115 + 120,BLACK,&arialRoundedMTBold_20ptFontInfo,"Speed Fail Alarm");

/********************************* SECTION 5 INTERNAL FAULT ALARM *******************************/	
	if (log_alarm_sec & 0x0010)
			drawString(30,115 + 160,BLACK,&arialRoundedMTBold_20ptFontInfo,"Internal Fault Alarm");

/********************************* SECTION 6 CONFIGURATION MISMATCH *****************************/
	if (log_alarm_sec & 0x0020)
			drawString(30,115 + 200,BLACK,&arialRoundedMTBold_20ptFontInfo,"Configuration Mismatch");
			
/********************************* SECTION 7 POWER SUPPLY 1 FAULT ********************************/	
	if (log_alarm_sec & 0x0040)
			drawString(30,115 + 240,BLACK,&arialRoundedMTBold_20ptFontInfo,"Power Supply 1 Fault");

/********************************* SECTION 8 POWER SUPPLY 2 FAULT ********************************/	
	if (log_alarm_sec & 0x0080)
			drawString(30,115,BLACK,&arialRoundedMTBold_20ptFontInfo,"Power Supply 2 Fault");

/********************************* SECTION 9 TMP OVERSPEED SETPOINT ON ***************************/	
	if (log_alarm_sec & 0x0100)
			drawString(30,115,BLACK,&arialRoundedMTBold_20ptFontInfo,"Tmp Overspd Setpoint On");

/********************************* SECTION 10 MANUAL SIM SPEED TEST ******************************/	
	if (log_alarm_sec & 0x0200)
			drawString(30,115,BLACK,&arialRoundedMTBold_20ptFontInfo,"Manual Sim.Speed Test");

/********************************* SECTION 11 DATE ***********************************************/	
	if (log_alarm_sec & 0x0400)
			drawString(380,115,BLACK,&arialRoundedMTBold_20ptFontInfo,"2010-01-24");	

/********************************* SECTION 12 TIME ***********************************************/	
	if (log_alarm_sec & 0x0800)
			drawString(540,115,BLACK,&arialRoundedMTBold_20ptFontInfo,"12:13:53");		
			
/********************************* SECTION 13 - TEST TIK *****************************************/	
	if (log_alarm_sec & 0x1000)
			drawString(720,115,BLACK,&webdings_26ptFontInfo,"<");
		
/********************************* SECTION 14 - PAGE NUMBER **************************************/	
	if (log_alarm_sec & 0x2000)
			drawString(397,364,BLACK,&arialNarrow_20ptFontInfo,"1");

/********************************* SECTION 15 - TOTAL PAGES **************************************/	
	if (log_alarm_sec & 0x4000)
			drawString(441,364,BLACK,&arialNarrow_20ptFontInfo,"2");
}


/*****************************************************************************
 * Log alarm LCD
 ****************************************************************************/
void log_alarm_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(204, 398, 390, 479,BLUE);

    drawString(320,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Alarm Log");
	GLCD_FILLRECT(1, 71, 790, 73, BLACK);
	GLCD_FILLRECT(1, 395, 790, 397, BLACK);
	GLCD_FILLRECT(201, 395, 203, 479, BLACK);
	GLCD_FILLRECT(391, 395, 393, 479, BLACK);
	GLCD_FILLRECT(587, 395, 589, 479, BLACK);

	drawString(9, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Monitor Menu");

	drawString(231, 427, WHITE, &arialRoundedMTBold_24ptFontInfo, "Log Menu");

	drawString(406, 427, BLACK, &arialRoundedMTBold_24ptFontInfo,
			"Config Menu");

	drawString(608, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Test Menu");
}
