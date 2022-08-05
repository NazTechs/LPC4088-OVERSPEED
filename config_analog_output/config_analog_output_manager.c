

uint8_t analog_item;
uint8_t an1Open = 0;
uint8_t an2Open = 0;
void  config_analog_output_manager(uint8_t key, uint8_t *MenuState, uint8_t *MenuRender)
{

				if (key == 65 )
				{

					*MenuState = CONFIG_MENU;
					RENDER_REQ(*MenuRender,REDRAW);

				}


				if (key == 17 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = LOG_MENU;
					config_item = 0 ;

				}


				if (key == 68 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = MONITOR_MENU;
					config_item = 0 ;

				}

				if (key == 18) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = CONFIG_MENU;

				}

				if (key == 19 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = TEST_MENU;
					config_item = 0 ;

				}

				if (key == 52 && analog_item >= 1)
				{

					analog_item =analog_item  - 1;
					RENDER_REQ(*MenuRender,REFRESH0);

				}

				if (key == 50 && analog_item <= 2)
				{

					analog_item =analog_item  + 1;
					RENDER_REQ(*MenuRender,REFRESH0);

				}

				if (key == 51) {

					switch (analog_item) {
					case 0: {
						*MenuState = CONFIG_ANALOG_OUTPUT_1;
						RENDER_REQ(*MenuRender, REDRAW);
						an1Open = 0;
						break;

					}
					case 1: {
						*MenuState = CONFIG_ANALOG_OUTPUT_2;
						RENDER_REQ(*MenuRender, REDRAW);
						an2Open = 0;
						break;
					}

				}
			}

}
