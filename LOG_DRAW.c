
void LogMenuDraw(uint8_t *MenuRender) {

	if (RENDER_CHK(*MenuRender, REDRAW)) {

		LogMenuReneder(&LogMenuCurrent, 0);
		RENDER_END(*MenuRender, REDRAW);

	}
	if (RENDER_CHK(*MenuRender, REFRESH0)) {

		LogMenuReneder(&LogMenuCurrent, 1);
		RENDER_END(*MenuRender, REFRESH0);
	}

}
