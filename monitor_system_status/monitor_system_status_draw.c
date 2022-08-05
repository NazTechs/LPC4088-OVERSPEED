void SystemStatusDraw(uint8_t *MenuRender) {

	if (RENDER_CHK(*MenuRender, REDRAW)) {
		monitor_system_status_lcd();
		MonitorSystemStatusRender();
		RENDER_END(*MenuRender, REDRAW);
	}

}