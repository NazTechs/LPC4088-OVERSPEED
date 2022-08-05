void monitorSummeryDraw(uint8_t *MenuRender) {
	uint8_t sections = 0x00;
	if (RENDER_CHK(*MenuRender, REDRAW)) {
		monitor_summary_lcd();
		monitor_Summary_Render(&memory1, 0xFF);
		RENDER_END(*MenuRender, REDRAW);
		prv_memory = memory1;
	}
	if (RENDER_CHK(*MenuRender, REFRESH0)) {
		uint8_t sections = 0;
		if (prv_memory.speed != memory1.speed)
			sections = 0x2;
		if (prv_memory.accel != memory1.accel)
			sections |= 0x4;
		if (prv_memory.overspeedset != memory1.overspeedset)
			sections |= 0x8;
		if (prv_memory.speedfailoveride != memory1.speedfailoveride)
			sections |= 0x10;
		if (prv_memory.analog1_output != memory1.analog1_output)
			sections |= 0x20;
		if (prv_memory.day != memory1.day)
			sections |= 0x40;
		if (prv_memory.sec != memory1.sec)
			sections |= 0x80;
		monitor_Summary_Render(&memory1, sections);
		prv_memory = memory1;
		RENDER_END(*MenuRender, REFRESH0);
	}

}
