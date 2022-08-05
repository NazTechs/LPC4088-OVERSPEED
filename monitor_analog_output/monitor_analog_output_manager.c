void AnalogOutputMng(uint8_t key, uint8_t *MenuState, uint8_t *MenuRender) {

				if (key == 65 )
				{
					
					Menu_State = MONITOR_MENU;
					RENDER_REQ(Menu_Render,REDRAW);

				}


				if (key == 17 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = LOG_MENU;

				}

				
				if (key == 68) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = MONITOR_MENU;

				}

				if (key == 18) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = CONFIG_MENU;

				}				
				
				if (key == 19 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = TEST_MENU;

				}

	RENDER_REQ(*MenuRender, REFRESH0);
}