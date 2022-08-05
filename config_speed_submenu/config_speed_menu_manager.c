
uint8_t config_speed_item;
void Config_speed_Mng(uint8_t key, uint8_t *MenuState, uint8_t *MenuRender) 
{




				
											
				if (key == 65)
				{
					Menu_State = CONFIG_MENU;
					RENDER_REQ(Menu_Render,REDRAW);
					config_speed_item = 0;

				}
				if (key == 50 && config_speed_item<=3)
				{
					
					config_speed_item =config_speed_item  +1;
					RENDER_REQ(Menu_Render,REFRESH0);

				}

				if (key == 17 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = LOG_MENU;
					config_speed_item = 0;
					config_item = 0 ;

				}

				
				if (key == 68 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = MONITOR_MENU;
					config_speed_item = 0;
					config_item = 0 ;

				}

				if (key == 18) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = CONFIG_MENU;
					config_speed_item = 0;

				}				
				
				if (key == 19 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = TEST_MENU;
					config_speed_item = 0;
					config_item = 0 ;

				}
				
				if (key == 52 && config_speed_item>=1)
				{
					
					config_speed_item =config_speed_item  -1;
					RENDER_REQ(Menu_Render,REFRESH0);

				}		
				if (key == 51)
				{
						switch(config_speed_item){
							case 0 :
							{
								Menu_State = CONFIG_SPEED_INPUT;
								RENDER_REQ(Menu_Render,REDRAW);
								
							break;	
						}
							case 1 :
							{
								Menu_State = CONFIG_SPEED_ACCELERATION;
								RENDER_REQ(Menu_Render,REDRAW);
							break;
							}
							
							
							case 2 :
							{
								Menu_State = CONFIG_SPEED_START_LOGIC;
								RENDER_REQ(Menu_Render,REDRAW);
							break;
							}
							
						
						}					
					}
			}