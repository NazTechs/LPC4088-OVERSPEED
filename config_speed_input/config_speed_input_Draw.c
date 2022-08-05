/*----------------------------------------------------------------------------------
------------------------------------------------------------------------------------
------------------------------------------------------------------------------------

							CONFIG SPEED INPUT

------------------------------------------------------------------------------------
------------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
						
			
void config_speed_input_Draw(uint8_t *MenuRender)

 {
	if (RENDER_CHK(*MenuRender, REDRAW)) 
	{
		config_speed_input_lcd();
		config_speed_input_items();
		config_speed_input_Reneder(0xFF);
		RENDER_END(*MenuRender, REDRAW);	
	}
	
	if( RENDER_CHK(Menu_Render,REFRESH0) )
	{											
	config_speed_input_Reneder(0xFF);
	RENDER_END(Menu_Render,REFRESH0);				
	}
}