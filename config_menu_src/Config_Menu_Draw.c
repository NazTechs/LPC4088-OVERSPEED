	



void configMenuDraw(uint8_t *MenuRender) 
{

				
					if( RENDER_CHK(Menu_Render,REDRAW) )
					{
						
						CONFIG_MENU_LCD();
						configurationMenuReneder(&config_item);
						RENDER_END(Menu_Render,REDRAW);
					
					}
		
					if( RENDER_CHK(Menu_Render,REFRESH0) )
						
					{
						configurationMenuReneder(&config_item);
						RENDER_END(Menu_Render,REFRESH0);
					
					}						
					
			}

