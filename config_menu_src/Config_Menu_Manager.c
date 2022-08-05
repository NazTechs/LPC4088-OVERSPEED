
/************************************************************************
 * Configuration Manager items
 ************************************************************************/


void ConfigMng(uint8_t key, uint8_t *MenuState, uint8_t *MenuRender) 
{






				if (key == 17 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = LOG_MENU;
					config_item = 0;

				}

				
				if (key == 68 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = MONITOR_MENU;
					config_item = 0;


				}
				
				
				if (key == 19) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = TEST_MENU;
					config_item = 0;
				}
				
											
				if (key == 65)
				{
					Menu_State = MENU_HOME;
					RENDER_REQ(Menu_Render,REDRAW);
					config_item = 0;
				}
				if (key == 50 && config_item<=8)
				{
					
					config_item =config_item  +1;
					RENDER_REQ(Menu_Render,REFRESH0);

				}
				
				if (key == 52 && config_item>=1)
				{
					
					config_item =config_item  -1;
					RENDER_REQ(Menu_Render,REFRESH0);

				}		
				if (key == 51)
				{
						switch(config_item){
							case 0 :
							{
								Menu_State = CONFIG_SPEED;
								RENDER_REQ(Menu_Render,REDRAW)
								
							break;	
						}
							case 1 :
							{
								Menu_State = CONFIG_TRIP_LATCH;
								RENDER_REQ(Menu_Render,REDRAW);
							break;
							}
							
							
							case 2 :
							{
								Menu_State = GONFIG_ANALOG_OUTPUT;
								RENDER_REQ(Menu_Render,REDRAW);
							break;
							}
							
							
							case 3 :
							{
								Menu_State = CONFIG_TEST_MODES;
								RENDER_REQ(Menu_Render,REDRAW);
							break;
							}
							
							case 4 :
							{
								Menu_State = CONFIG_PERIODIC_OVERSPEED_TEST;
								RENDER_REQ(Menu_Render,REDRAW);
							break;
							}

							
							
							case 5 :
							{
								Menu_State = CONFIG_MODBUS;
								RENDER_REQ(Menu_Render,REDRAW);
							break;
							}
						
						}					
					}
			}





