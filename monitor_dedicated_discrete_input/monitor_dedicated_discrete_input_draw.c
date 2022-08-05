void DedicatedInputDraw(uint8_t *MenuRender) {

	if (RENDER_CHK(*MenuRender, REDRAW)) {
		monitor_dedicated_lcd();
		MonitorDedicatedDiscreteInputsRender();
		RENDER_END(*MenuRender, REDRAW);
	}

}