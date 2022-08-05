	void config_analog_output_draw(uint8_t *MenuRender)
			{

					if( RENDER_CHK(Menu_Render,REDRAW) )
					{
						config_analog_output_lcd();
						config_analog_output_items();
						config_analog_output_Reneder(&analog_item);
						RENDER_END(Menu_Render,REDRAW);

					}

					if( RENDER_CHK(Menu_Render,REFRESH0) )
					{


						config_analog_output_Reneder(&analog_item);
						RENDER_END(Menu_Render,REFRESH0);

					}



			}
