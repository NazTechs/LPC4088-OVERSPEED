void config_trip_latch_Draw(uint8_t *MenuRender)

 {
	if (RENDER_CHK(*MenuRender, REDRAW)) 
	{
		 config_trip_latch_lcd();
		 config_trip_latch_items();
		 config_trip_latch_Reneder(0xFF);
		RENDER_END(*MenuRender, REDRAW);	
	}
	
	if( RENDER_CHK(Menu_Render,REFRESH0) )
	{											
	 config_trip_latch_Reneder(0xFF);
	RENDER_END(Menu_Render,REFRESH0);				
	}
}
