/*****************************************************************************
 * CONFIG MODBUS items
 ****************************************************************************/

void config_modbus_items(void) 

{

		drawString(100,110,BLACK,&arialRoundedMTBold_20ptFontInfo,"Mode");
		
	    drawString(100,155,BLACK,&arialRoundedMTBold_20ptFontInfo,"Baud Rate");
	    
	    drawString(700,155,BLACK,&arialRoundedMTBold_20ptFontInfo,"bits/s"); 
			
		drawString(100,200,BLACK,&arialRoundedMTBold_20ptFontInfo,"Communication Parity");
	     
        drawString(100,245,BLACK,&arialRoundedMTBold_20ptFontInfo,"Slave Address");
	     	
	    drawString(100,290,BLACK,&arialRoundedMTBold_20ptFontInfo,"Enable Write Commands");
	   	
	  
	    drawString(250,370,BLACK,&arialRoundedMTBold_16ptFontInfo,"Press ENTER to Edit Value");
}

/*****************************************************************************
 * CONFIG MODBUS render
 ****************************************************************************/
 
void config_modbus_Reneder(uint8_t config_modbus_sec)
{
	
	/****************************** SECTION 1 - Mode **************************/	
	if (config_modbus_sec & 0x01)
	drawString(560,110,BLUE,&arialRoundedMTBold_24ptFontInfo,"RS232");
	
	/***************************** SECTION 2 - Baud Rate **********************/	
	if (config_modbus_sec & 0x02)
	drawString(560,155,BLUE,&arialRoundedMTBold_24ptFontInfo,"19200");
			
	/***************************** SECTION 3 - Communication Parity ***********/	
	if (config_modbus_sec & 0x04)		
	drawString(560,200,BLUE,&arialRoundedMTBold_24ptFontInfo,"NO Parity"); 
	    
	/***************************** SECTION 4 - Slave Address ******************/	
	if (config_modbus_sec & 0x08)		
	drawString(560,245,BLUE,&arialRoundedMTBold_24ptFontInfo,"2"); 
    
	/***************************** SECTION 5 - Enable Write Commands **********/	
	if (config_modbus_sec & 0x10)		
	drawString(560,290,BLUE,&arialRoundedMTBold_24ptFontInfo,"NO");
	
}

/*****************************************************************************
 * CONFIG MODBUS LCD
 ****************************************************************************/
void config_modbus_lcd(void) {

	ClearDevice_F(0xFFFF);

	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(394, 398, 586, 479,BLUE);

	drawString(250,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"Configure Modbus");
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