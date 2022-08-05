


void configAnout2Draw(uint8_t *MenuRender) {
	if (RENDER_CHK(Menu_Render, REDRAW)) {
		configAnout2RenderLcd();
		configAnout2Render(&an2Table);
		RENDER_END(Menu_Render, REDRAW);
	}

	if (RENDER_CHK(Menu_Render, REFRESH0)) {
		configAnout2Render(&an2Table);
    //configAnout2RenderLcd();
		RENDER_END(Menu_Render, REFRESH0);
	}

}
