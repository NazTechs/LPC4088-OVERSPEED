/*---------------------------------------------------------------------------------*/
void DataTimeDraw(uint8_t *MenuRender) {

	if (RENDER_CHK(*MenuRender, REDRAW)) {
		monitor_date_time_lcd();
		MonitorDateTimeRender(0xFF);
		RENDER_END(*MenuRender, REDRAW);
	}
	if (RENDER_CHK(*MenuRender, REFRESH0)) {
				uint8_t sections = 0;
				if (prv_memory.day != memory1.day)
					sections = 0x2;
				if (prv_memory.sec != memory1.sec)
					sections |= 0x4;
				MonitorDateTimeRender(sections);
				prv_memory = memory1;
				RENDER_END(*MenuRender, REFRESH0);

}
	}