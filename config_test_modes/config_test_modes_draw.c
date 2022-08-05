	void config_test_modes_draw(uint8_t *MenuRender)
			{
				
					if( RENDER_CHK(Menu_Render,REDRAW) )
					{
						config_test_modes_lcd();
						config_test_modes_items();
						config_test_modes_Reneder(0xFF);
						RENDER_END(Menu_Render,REDRAW);
					
					}
		
					if( RENDER_CHK(Menu_Render,REFRESH0) )
					{
												

						config_test_modes_Reneder(0xFF);
						RENDER_END(Menu_Render,REFRESH0);
					
					}						
					
			}
									

							