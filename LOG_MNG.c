/*---------------------------------------------------------------------------------*/

void LogMenuMng(uint8_t key, uint8_t *MenuState, uint8_t *MenuRender) {

	if (key == 17) {
		RENDER_REQ(*MenuRender, REDRAW);
		RENDER_REQ(*MenuRender, REFRESH0);
		*MenuState = LOG_MENU;

	}

	if (key == 68) {
		RENDER_REQ(*MenuRender, REDRAW);
		RENDER_REQ(*MenuRender, REFRESH0);
		*MenuState = MONITOR_MENU;

	}
	if (key == 65) {
		RENDER_REQ(*MenuRender, REDRAW);
		RENDER_REQ(*MenuRender, REFRESH0);
		*MenuState = MENU_HOME;
	}
	if (key == 50) {
		LogMenuCurrent = LogMenuCurrent + 1;
		RENDER_REQ(*MenuRender, REFRESH0);
	}
	if (key == 52 && LogMenuCurrent > 0) {

		LogMenuCurrent = LogMenuCurrent - 1;
		RENDER_REQ(*MenuRender, REFRESH0);
	}
}
