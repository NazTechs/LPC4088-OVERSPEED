	void config_speed_acceleration_draw(uint8_t *MenuRender)
			{
				
					if( RENDER_CHK(Menu_Render,REDRAW) )
					{
						config_speed_accel_lcd();
						config_speed_accel_items();
						config_speed_accel_Reneder(0xFF);
						RENDER_END(Menu_Render,REDRAW);
					
					}
		
					if( RENDER_CHK(Menu_Render,REFRESH0) )
					{
												

						config_speed_accel_Reneder(0xFF);
						RENDER_END(Menu_Render,REFRESH0);
					
					}						
					
			}
									

							