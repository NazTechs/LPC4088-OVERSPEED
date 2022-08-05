/*----------------------------------------------------------------------------------
------------------------------------------------------------------------------------
------------------------------------------------------------------------------------

							CONFIG START lOGIC

------------------------------------------------------------------------------------
------------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
						
			
void config_start_logic_Draw(uint8_t *MenuRender)

 {
	if (RENDER_CHK(*MenuRender, REDRAW)) 
	{
		 config_start_logic_lcd();
		 config_start_logic_items();
		 config_start_logic_Reneder(0xFF);
		RENDER_END(*MenuRender, REDRAW);	
	}
	
	if( RENDER_CHK(Menu_Render,REFRESH0) )
	{											
	 config_start_logic_Reneder(0xFF);
	RENDER_END(Menu_Render,REFRESH0);				
	}
}