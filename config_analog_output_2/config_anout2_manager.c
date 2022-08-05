


 uint16_t  an2TableItems[]        = {
  1,2,3,4,5,6,7,
  0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,
  0x2000,0x3000,0x4000,0x5000,0x6000,0x7000,0x8000
};
uint8_t   an2EditAbleItem[]      = {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
uint32_t  an2Serial;
tableCtrlData an2Table = {3,8,0,0,0,0,an2TableItems,an2EditAbleItem,&an2Serial};


void configAnout2Mng(uint8_t key, uint8_t *MenuState, uint8_t *MenuRender) {
    if (an2Open == 0)
    {
      int i;
        uint8_t calbReturn;
        an2Open = 1;
        calbReturn = getCalbAn(an2TableItems,&an2Serial,AN2_ADD_PAGE);
        if (calbReturn == 1){
          intCalbAn(AN2_ADD_PAGE);
          for (i =0 ; i< 1000000;i++);
          getCalbAn(an2TableItems,&an2Serial,AN2_ADD_PAGE);
        }

        RENDER_REQ(*MenuRender,REFRESH0);
    }
    if (key == 65)
  				{
  					*MenuState = GONFIG_ANALOG_OUTPUT;
  					RENDER_REQ(*MenuRender,REDRAW);
  					analog_item = 0;
            an2Table.tableEditMode = 0;
            an2Table.tableSelItem  = 0;
  				}


    switch(an2Table.tableEditMode)
      	{
      			case 0 : //normal mode
              if (key == 68 ) {
                RENDER_REQ(*MenuRender, REDRAW);
                *MenuState = CONFIG_ANALOG_OUTPUT_2;
                an2Table.tableEditMode = 1;
                log_item = 0;
                RENDER_REQ(*MenuRender, REFRESH0);}
                if (key == 19 ) {
                      RENDER_REQ(*MenuRender, REDRAW);
                      *MenuState = GONFIG_ANALOG_OUTPUT;
                      analog_item = 0 ;
                      an2Table.tableEditMode = 0;
                      an2Table.tableSelItem  = 0;
                      }
      			break;
            case 1 : //Sel mode
            {
              if (key == 50){
                if((an2Table.tableSelItem + 1) < ((an2Table.rowNum - 1) * an2Table.columnNum))
                {
                  an2Table.tableSelItem++;
                  RENDER_REQ(*MenuRender, REFRESH0);
                }
              }
              if (key == 52){
                if(an2Table.tableSelItem >0)
                {
                  an2Table.tableSelItem--;
                  RENDER_REQ(*MenuRender, REFRESH0);
                }
              }
              if (key == 33){
                if(an2Table.tableSelItem + (an2Table.rowNum - 1) + 1  <=
                  ((an2Table.rowNum - 1) * an2Table.columnNum))
                {
                  an2Table.tableSelItem = an2Table.tableSelItem + (an2Table.rowNum - 1);
                  RENDER_REQ(*MenuRender, REFRESH0);
                }
              }
              if (key == 49){
                if(an2Table.tableSelItem - (an2Table.rowNum - 1) >=0)
                {
                  an2Table.tableSelItem = an2Table.tableSelItem - (an2Table.rowNum - 1);
                  RENDER_REQ(*MenuRender, REFRESH0);
                }
              }
              if(key == 51){
                if (an2Table.editAbleItem[an2Table.tableSelItem])
                  {
                    an2Table.tableEditMode = 2;
                    RENDER_REQ(*MenuRender, REFRESH0);
                  }
              }
              if (key == 19 ) {
                    RENDER_REQ(*MenuRender, REFRESH0);
                    an2Table.tableEditMode = 0;
                    an2Table.tableSelItem  = 0;
                    an2Table.tableEditMode = 0;
                    }
                if (key == 17 ) {
                    int i;
                    setCalbAn(an2TableItems,AN2_ADD_PAGE);
                    for (i = 0 ; i < 100000;i++);
                    getCalbAn(an2TableItems,&an2Serial,AN2_ADD_PAGE);
                    an02UpdateFlag = 1;
                    RENDER_REQ(*MenuRender, REFRESH0);
                  }
            }

            break;
      			case 2 : //Edit mode
                  if (key == 52){
                    if (65535 > ((uint32_t)an2TableItems[an2Table.tableSelItem]) + ((uint32_t)pow(10,an2Table.editModeValueSelected)))
                      an2TableItems[an2Table.tableSelItem] = an2TableItems[an2Table.tableSelItem] + pow(10,an2Table.editModeValueSelected);
                    else
                      an2TableItems[an2Table.tableSelItem] = 65535;
                    RENDER_REQ(*MenuRender, REFRESH0);
                    }
                  if (key == 50){
                      an2TableItems[an2Table.tableSelItem] =
                      an2TableItems[an2Table.tableSelItem] - pow(10,an2Table.editModeValueSelected);
                      RENDER_REQ(*MenuRender, REFRESH0);
                    }
                  if (key == 33){
                    if (an2Table.editModeValueSelected == 0)
                        an2Table.editModeValueSelected = 0;
                    else
                        an2Table.editModeValueSelected--;
                    RENDER_REQ(*MenuRender, REFRESH0);
                      }
                  if (key == 49){
                    if (an2Table.editModeValueSelected == 5)
                          an2Table.editModeValueSelected = 5;
                    else
                        an2Table.editModeValueSelected++;
                    RENDER_REQ(*MenuRender, REFRESH0);
                      }
                  if(key == 51){
                          an2Table.tableEditMode = 1;
                          RENDER_REQ(*MenuRender, REFRESH0);
                    }
                  if (key == 19 ) {
                          RENDER_REQ(*MenuRender, REFRESH0);
                          an2Table.tableEditMode = 0;
                          an2Table.tableSelItem  = 0;
                          an2Table.tableEditMode = 0;
                          }
      			break;

      }
}
