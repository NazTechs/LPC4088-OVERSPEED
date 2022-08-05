void config_speed_Menu_Draw(uint8_t *MenuRender) 
{

				
					if( RENDER_CHK(Menu_Render,REDRAW) )
					{
						
						config_speed_menu_lcd();
						config_speedMenuReneder(&config_speed_item);
						RENDER_END(Menu_Render,REDRAW);
					
					}
		
					if( RENDER_CHK(Menu_Render,REFRESH0) )
						
					{
						config_speedMenuReneder(&config_speed_item);
						RENDER_END(Menu_Render,REFRESH0);
					
					}						
					
}