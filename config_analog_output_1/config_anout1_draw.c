


void configAnout1Draw(uint8_t *MenuRender) {
	if (RENDER_CHK(Menu_Render, REDRAW)) {
		configAnout1RenderLcd();
		configAnout1Render(&an1Table);
		RENDER_END(Menu_Render, REDRAW);
	}

	if (RENDER_CHK(Menu_Render, REFRESH0)) {
		configAnout1Render(&an1Table);
    //configAnout1RenderLcd();
		RENDER_END(Menu_Render, REFRESH0);
	}

}
