/*----------------------------------------------------------------------------------
------------------------------------------------------------------------------------
------------------------------------------------------------------------------------

							config speed input

------------------------------------------------------------------------------------
------------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/

void  config_speed_input_manager(uint8_t key, uint8_t *MenuState, uint8_t *MenuRender)
{

				if (key == 65 )
				{
					
					Menu_State = CONFIG_SPEED;
					RENDER_REQ(Menu_Render,REDRAW);

				}


				if (key == 17 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = LOG_MENU;
					config_item = 0 ;
					config_speed_item = 0;

				}

				
				if (key == 68 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = MONITOR_MENU;
					config_item = 0 ;
					config_speed_item = 0;

				}

				if (key == 18) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = CONFIG_MENU;
					config_speed_item = 0;

				}				
				
				if (key == 19 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = TEST_MENU;
					config_item = 0 ;
					config_speed_item = 0;

				}
}