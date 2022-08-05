void AnalogOutputDraw(uint8_t *MenuRender) {

	if (RENDER_CHK(*MenuRender, REDRAW)) {
		monitor_analog_output_lcd();
		MonitorAnalogOutputRender(0xFF);
		RENDER_END(*MenuRender, REDRAW);
	}
	if (RENDER_CHK(*MenuRender, REFRESH0)) {
			uint8_t sections = 0;
			if (prv_memory.analog1_output != memory1.analog1_output)
				sections = 0x2;
			if (prv_memory.speed != memory1.speed)
				sections |= 0x4;
			MonitorAnalogOutputRender(sections);
			prv_memory = memory1;
			RENDER_END(*MenuRender, REFRESH0);
	}

}

