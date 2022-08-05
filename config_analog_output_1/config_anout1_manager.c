


 uint16_t  an1TableItems[]        = {
  1,2,3,4,5,6,7,
  0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,
  0x2000,0x3000,0x4000,0x5000,0x6000,0x7000,0x8000
};
uint8_t   an1EditAbleItem[]      = {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
uint32_t  an1Serial;
tableCtrlData an1Table = {3,8,0,0,0,0,an1TableItems,an1EditAbleItem,&an1Serial};


void configAnout1Mng(uint8_t key, uint8_t *MenuState, uint8_t *MenuRender) {
    if (an1Open == 0)
    {
      int i;
        uint8_t calbReturn;
        an1Open = 1;
        calbReturn = getCalbAn(an1TableItems,&an1Serial,AN1_ADD_PAGE);
        if (calbReturn == 1){
          intCalbAn(AN1_ADD_PAGE);
          for (i =0 ; i< 1000000;i++);
          getCalbAn(an1TableItems,&an1Serial,AN1_ADD_PAGE);
        }

        RENDER_REQ(*MenuRender,REFRESH0);
    }
    if (key == 65)
  				{
  					*MenuState = GONFIG_ANALOG_OUTPUT;
  					RENDER_REQ(*MenuRender,REDRAW);
  					analog_item = 0;
            an1Table.tableEditMode = 0;
            an1Table.tableSelItem  = 0;
  				}


    switch(an1Table.tableEditMode)
      	{
      			case 0 : //normal mode
              if (key == 68 ) {
                RENDER_REQ(*MenuRender, REDRAW);
                *MenuState = CONFIG_ANALOG_OUTPUT_1;
                an1Table.tableEditMode = 1;
                log_item = 0;
                RENDER_REQ(*MenuRender, REFRESH0);}
                if (key == 19 ) {
                      RENDER_REQ(*MenuRender, REDRAW);
                      *MenuState = GONFIG_ANALOG_OUTPUT;
                      analog_item = 0 ;
                      an1Table.tableEditMode = 0;
                      an1Table.tableSelItem  = 0;
                      }
      			break;
            case 1 : //Sel mode
            {
              if (key == 50){
                if((an1Table.tableSelItem + 1) < ((an1Table.rowNum - 1) * an1Table.columnNum))
                {
                  an1Table.tableSelItem++;
                  RENDER_REQ(*MenuRender, REFRESH0);
                }
              }
              if (key == 52){
                if(an1Table.tableSelItem >0)
                {
                  an1Table.tableSelItem--;
                  RENDER_REQ(*MenuRender, REFRESH0);
                }
              }
              if (key == 33){
                if(an1Table.tableSelItem + (an1Table.rowNum - 1) + 1  <=
                  ((an1Table.rowNum - 1) * an1Table.columnNum))
                {
                  an1Table.tableSelItem = an1Table.tableSelItem + (an1Table.rowNum - 1);
                  RENDER_REQ(*MenuRender, REFRESH0);
                }
              }
              if (key == 49){
                if(an1Table.tableSelItem - (an1Table.rowNum - 1) >=0)
                {
                  an1Table.tableSelItem = an1Table.tableSelItem - (an1Table.rowNum - 1);
                  RENDER_REQ(*MenuRender, REFRESH0);
                }
              }
              if(key == 51){
                if (an1Table.editAbleItem[an1Table.tableSelItem])
                  {
                    an1Table.tableEditMode = 2;
                    RENDER_REQ(*MenuRender, REFRESH0);
                  }
              }
              if (key == 19 ) {
                    RENDER_REQ(*MenuRender, REFRESH0);
                    an1Table.tableEditMode = 0;
                    an1Table.tableSelItem  = 0;
                    an1Table.tableEditMode = 0;
                    }
                if (key == 17 ) {
                    int i;
                    setCalbAn(an1TableItems,AN1_ADD_PAGE);
                    for (i = 0 ; i < 100000;i++);
                    getCalbAn(an1TableItems,&an1Serial,AN1_ADD_PAGE);
                    an01UpdateFlag = 1;
                    RENDER_REQ(*MenuRender, REFRESH0);
                  }
            }

            break;
      			case 2 : //Edit mode
                  if (key == 52){
                    if (65535 > ((uint32_t)an1TableItems[an1Table.tableSelItem]) + ((uint32_t)pow(10,an1Table.editModeValueSelected)))
                      an1TableItems[an1Table.tableSelItem] = an1TableItems[an1Table.tableSelItem] + pow(10,an1Table.editModeValueSelected);
                    else
                      an1TableItems[an1Table.tableSelItem] = 65535;
                    RENDER_REQ(*MenuRender, REFRESH0);
                    }
                  if (key == 50){
                      an1TableItems[an1Table.tableSelItem] =
                      an1TableItems[an1Table.tableSelItem] - pow(10,an1Table.editModeValueSelected);
                      RENDER_REQ(*MenuRender, REFRESH0);
                    }
                  if (key == 33){
                    if (an1Table.editModeValueSelected == 0)
                        an1Table.editModeValueSelected = 0;
                    else
                        an1Table.editModeValueSelected--;
                    RENDER_REQ(*MenuRender, REFRESH0);
                      }
                  if (key == 49){
                    if (an1Table.editModeValueSelected == 5)
                          an1Table.editModeValueSelected = 5;
                    else
                        an1Table.editModeValueSelected++;
                    RENDER_REQ(*MenuRender, REFRESH0);
                      }
                  if(key == 51){
                          an1Table.tableEditMode = 1;
                          RENDER_REQ(*MenuRender, REFRESH0);
                    }
                  if (key == 19 ) {
                          RENDER_REQ(*MenuRender, REFRESH0);
                          an1Table.tableEditMode = 0;
                          an1Table.tableSelItem  = 0;
                          an1Table.tableEditMode = 0;
                          }
      			break;

      }
}
