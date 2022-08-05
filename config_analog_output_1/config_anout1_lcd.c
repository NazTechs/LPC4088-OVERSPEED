

uint16_t	textPadY[]          = {50 + 60,85 + 60,120 + 60,155 + 60,190 + 60,225 + 60,260 + 60,50 + 60,85 + 60,120 + 60,155 + 60,190 + 60,225 + 60,260 + 60,50 + 60
                                  ,85 + 60,120 + 60,155 + 60,190 + 60,225 + 60,260 + 60};
uint16_t	textPadX[]          = {60,60,60,60,60,60,60,200,200,200,200,200,200,200,350,350,350,350,350,350,350};

uint16_t  colItemResolve[]		=	{1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3};
uint16_t	rowItemResolve[]		= {1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7};

uint16_t	colPosStartY[]      = {75,75,75,75};
uint16_t	colPosEndY[]        = {350,350,350,350};
uint16_t  colPosX[]			      = {9,151,290,500};

uint16_t  rowPosStartX[]      = {9,9,9,9,9,9,9,9,9};
uint16_t  rowPosEndX[]		    = {500,500,500,500,500,500,500,500,500};
uint16_t	rowPosY[]		   		  = {73,100,135,170,205,240,275,310,350};



char			headerItem[][20]	  = {"Row","RPM x 10","Calb. Digit"};
uint16_t	headerTexextPadX[]	= {50,175,350};
uint16_t	headerTexextPadY[]	= {80,80,80};



void configAnout1RenderLcd()
{
    ClearDevice_F(WHITE);

    GLCD_FILLRECT(2,350,790,352,BLACK);
  	drawString(300,360,BLACK,&webdings_26ptFontInfo,"3");
  	drawString(330,364,BLACK,&arialNarrow_20ptFontInfo,"PAGE  1 of 1");
  	drawString(466,360,BLACK,&webdings_26ptFontInfo,"4");



  	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
  	GLCD_FILLRECT(780, 1, 799, 479, BLACK);
  	GLCD_FILLRECT(2, 16, 779, 70, GRAY1);

  	GLCD_FILLRECT(204, 398, 390, 479,GRAY3);

    drawString(320,35,BLACK,&arialRoundedMTBold_24ptFontInfo,"AN 1 Config");
  	GLCD_FILLRECT(1, 71, 790, 73, BLACK);
  	GLCD_FILLRECT(1, 395, 790, 397, BLACK);
  	GLCD_FILLRECT(201, 395, 203, 479, BLACK);
  	GLCD_FILLRECT(391, 395, 393, 479, BLACK);
  	GLCD_FILLRECT(587, 395, 589, 479, BLACK);

  	drawString(9+42, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "EDIT");

  	drawString(231+32, 427, GRAY1, &arialRoundedMTBold_24ptFontInfo, "Save");

  	//drawString(406, 427, BLACK, &arialRoundedMTBold_24ptFontInfo,"Config Menu");

  	drawString(608+42, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Back");

};

void configAnout1Render(tableCtrlData *anTable)
{
        /**
      *	@drawHeader
      *
      **/
      uint16_t i;
      char str[50];

      GLCD_FILLRECT(colPosX[0],rowPosY[0],colPosX[3],rowPosY[8],YELLOW);

      for ( i = 0 ; i < anTable->columnNum ; i++)
      drawString(headerTexextPadX[i],headerTexextPadY[i],BLACK,&arialRoundedMTBold_16ptFontInfo,headerItem[i]);
      /**
      *	@drawRow
      *
      **/
      for ( i = 0 ; i < anTable->rowNum + 1 ; i++){
        GLCD_FILLRECT(rowPosStartX[i],rowPosY[i],rowPosEndX[i],rowPosY[i] + 1,BLACK);
      }
      /**
      *	@drawCol
      *
      **/
      for ( i = 0 ; i < anTable->columnNum + 1 ; i++){
        GLCD_FILLRECT(colPosX[i], colPosStartY[i] ,colPosX[i] + 1,colPosEndY[i],BLACK);
      }
      /**
      *	@drawItems
      *
      **/
      for (i = 0 ; i < (anTable->columnNum) * (anTable->rowNum - 1 ); i++)
      {
          sprintf(str,"%d",anTable->tableItems[i]);
          drawString(textPadX[i],textPadY[i],BLACK,&arialRoundedMTBold_16ptFontInfo,str);
      }

      /**
      *@drawSerial
      *
      **/
      {
          GLCD_FILLRECT(520, 75 ,750 ,105,WHITE);
          sprintf(str,"Calb. Serial: %05d",*(anTable->serialId));
          drawString(520,80,BLUE,&arialRoundedMTBold_16ptFontInfo,str);
      }

      switch(anTable->tableEditMode)
      {
        case 0:
        {
          GLCD_FILLRECT(1, 397, 200, 479,WHITE);
          drawString(9+42, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "EDIT");
        }
        break;
        case 1:
        {
          GLCD_FILLRECT(1, 397, 200, 479,BLUE);
          drawString(9+42, 427, WHITE, &arialRoundedMTBold_24ptFontInfo, "EDIT");
          /**
          *   Table Item DrawList
          **/
          {
              uint16_t colResolve;
              uint16_t rowResolve;
              GLCD_FILLRECT(colPosX[colItemResolve[anTable->tableSelItem] - 1] - 1,
              rowPosY[rowItemResolve[anTable->tableSelItem] ] ,
              colPosX[colItemResolve[anTable->tableSelItem]]-1,
              rowPosY[rowItemResolve[anTable->tableSelItem] + 1] - 1
              ,RGB565CONVERT(160,  160,    160));

              sprintf(str,"%d",anTable->tableItems[anTable->tableSelItem]);
              drawString(textPadX[anTable->tableSelItem],textPadY[anTable->tableSelItem],
                WHITE,&arialRoundedMTBold_16ptFontInfo,str);

            }
            /**       **/
              GLCD_FILLRECT(204, 398, 390, 479,WHITE);
              drawString(231+32, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Save");
          break;
        }
        case 2:
          {
            GLCD_FILLRECT(1, 397, 200, 479,BLUE);
            drawString(9+42, 427, WHITE, &arialRoundedMTBold_24ptFontInfo, "EDIT");
            /**
            *   Table Item DrawList
            **/
            {
                uint16_t colResolve;
                uint16_t rowResolve;
                GLCD_FILLRECT(colPosX[colItemResolve[anTable->tableSelItem] - 1] - 1,
      					rowPosY[rowItemResolve[anTable->tableSelItem] ] ,
      					colPosX[colItemResolve[anTable->tableSelItem]]-1,
      				  rowPosY[rowItemResolve[anTable->tableSelItem] + 1] - 1
      					,BLUE);

      					sprintf(str,"%d",anTable->tableItems[anTable->tableSelItem]);
      					drawString(textPadX[anTable->tableSelItem],textPadY[anTable->tableSelItem],
                  WHITE,&arialRoundedMTBold_16ptFontInfo,str);

              }
            /**
      			*		UnderLine Pos Calc.
      			**/

      			{
      				  uint8_t   underLinePos = 0;
      					uint8_t   valueLenght = 0;
      					uint16_t  result =  anTable->tableItems[anTable->tableSelItem];
      					while (result != 0)
      						{
      							 result = result / 10;
      							 if (result > 0)
      								  valueLenght++;
      						}
      					underLinePos = valueLenght - anTable->editModeValueSelected;
      					drawString(textPadX[anTable->tableSelItem] + 10 * underLinePos,textPadY[anTable->tableSelItem] +  3,WHITE,&arialRoundedMTBold_16ptFontInfo,"_");
      			}

            /**       **/
              GLCD_FILLRECT(204, 398, 390, 479,GRAY3);
              drawString(231+32, 427, GRAY1, &arialRoundedMTBold_24ptFontInfo, "Save");
            break;
          }
      }

}
