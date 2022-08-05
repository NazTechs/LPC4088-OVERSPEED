/*****************************************************************************
 *  Soheil Nazari. _MAINMENU__C FUNCTION   +989122939002
 *****************************************************************************
 * @FileName:        LCD_FUNC.h
 * @Dependencies:
 * @Processor:       LPC4088
 * @Compiler:
 * @Linker:
 * @Company:			TADBIR
 *
 * @Author Soheil Nazari             @Date \95-11-18       Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    1/10/2017
 *****************************************************************************/

#include "MAINMENU.h"

uint8_t Menu_State;
uint8_t Menu_Render;
uint8_t MonitorMenuCurrent = 0;
uint8_t LogMenuCurrent = 0;
uint8_t config_item = 0;
float sp_prv = 99999.9;
Memory prv_memory;

#include "monitor_menu/monitor_menu_manager.c"
#include "monitor_summary/monitor_summary_manager.c"
#include "monitor_trip_latch/monitor_trip_latch_manager.c"
#include "monitor_alarm_latch/monitor_alarm_latch_manager.c"
#include "monitor_dedicated_discrete_input/monitor_dedicated_discrete_input_manager.c"
#include "monitor_speed_input/monitor_speed_input_manager.c"
#include "monitor_speed_fail_timer/monitor_speed_fail_timer_manager.c"
#include "monitor_analog_output/monitor_analog_output_manager.c"
#include "monitor_modbus/monitor_modbus_manager.c"
#include "monitor_date_time/monitor_date_time_manager.c"
#include "monitor_system_status/monitor_system_status_manager.c"
#include "monitor_module_information/monitor_module_information_manager.c"





#include "log_menu_src/LOG_MENU_MANAGER.c"
#include "config_menu_src/Config_Menu_Manager.c"
#include "LogOspAcc/log_ovrspd_accel_manager.c"
#include "log_alarm/log_alarm_manager.c"
#include "log_trip/log_trip_manager.c"
#include "log_peakspd_accel/log_peakspd_accel_manager.c"


#include "config_speed_submenu/config_speed_menu_manager.c"
#include "config_speed_input/config_speed_input_manager.c"
#include "config_speed_acceleration/config_speed_accel_manager.c"
#include "config_start_logic/config_start_logic_manager.c"
#include "config_trip_latch/config_trip_latch_manager.c"
#include "config_analog_output/config_analog_output_manager.c"
#include "config_test_modes/config_test_modes_manager.c"
#include "config_periodic_overspeed_test/config_periodic_overspeed_test_manager.c"
#include "config_modbus/config_modbus_manager.c"



#include "config_analog_output_1/config_anout1_manager.c"
#include "config_analog_output_2/config_anout2_manager.c"


#include "test_menu/test_menu_manager.c"
#include "test_tem_overspeed_setpoint/test_tem_overspeed_setpoint_manager.c"
#include "test_manual_simulated_speed/test_manual_simulated_speed_manager.c"
#include "test_periodic_overspeed/test_periodic_overspeed_manager.c"
#include "test_lamp/test_lamp_manager.c"







#include "monitor_menu/monitor_menu_draw.c"
#include "monitor_summary/monitor_summary_draw.c"
#include "monitor_trip_latch/monitor_trip_latch_draw.c"
#include "monitor_alarm_latch/monitor_alarm_latch_draw.c"
#include "monitor_dedicated_discrete_input/monitor_dedicated_discrete_input_draw.c"
#include "monitor_speed_input/monitor_speed_input_draw.c"
#include "monitor_speed_fail_timer/monitor_speed_fail_timer_draw.c"
#include "monitor_analog_output/monitor_analog_output_draw.c"
#include "monitor_modbus/monitor_modbus_draw.c"
#include "monitor_date_time/monitor_date_time_draw.c"
#include "monitor_system_status/monitor_system_status_draw.c"
#include "monitor_module_information/monitor_module_information_draw.c"



#include "log_menu_src/LOG_MENU_DRAW.c"
#include "config_menu_src/Config_Menu_Draw.c"
#include "LogOspAcc/Log_overspd_accel_draw.c"
#include "log_alarm/log_alarm_Draw.c"
#include "log_trip/log_trip_draw.c"
#include "log_peakspd_accel/log_peakspd_accel_draw.c"


#include "config_speed_submenu/config_speed_menu_draw.c"
#include "config_speed_input/config_speed_input_Draw.c"
#include "config_speed_acceleration/config_speed_accel_draw.c"
#include "config_start_logic/config_start_logic_draw.c"
#include "config_trip_latch/config_trip_latch_draw.c"
#include "config_analog_output/config_analog_output_draw.c"
#include "config_test_modes/config_test_modes_draw.c"
#include "config_periodic_overspeed_test/config_periodic_overspeed_test_draw.c"
#include "config_modbus/config_modbus_draw.c"


#include "config_analog_output_1/config_anout1_draw.c"
#include "config_analog_output_2/config_anout2_draw.c"



#include "test_menu/test_menu_draw.c"
#include "test_tem_overspeed_setpoint/test_tem_overspeed_setpoint_draw.c"
#include "test_manual_simulated_speed/test_manual_simulated_speed_draw.c"
#include "test_periodic_overspeed/test_periodic_overspeed_draw.c"
#include "test_lamp/test_lamp_draw.c"


/*---------------------------------------------------------------------------------*/

void MenuInit() {
	ResetDevice();
	ClearDevice_F(0XFFFF);
	{
		int i, j;
		for (j = 0; j < 255; j++) {
			SetBacklight(j);
			for (i = 0; i <= 20000; i++)
				;
		}
	}
	if ((LPC_WDT->MOD>>2) & 0x1 == 0)
		intro();
	Menu_State = 0;
	Menu_Render = 0;
}


/***********************************************************************************
 *@name HomeMng
 *@param key *MenuState *MenuRender
 *
 **********************************************************************************/
void HomeMng(uint8_t key, uint8_t *MenuState, uint8_t *MenuRender) {
	uint8_t r = 1;
	if (key == 68) {
		RENDER_REQ(*MenuRender, REDRAW);
		*MenuState = MONITOR_MENU;
		r = 0;
	}
	if (key == 17) {
		RENDER_REQ(*MenuRender, REDRAW);

		*MenuState = LOG_MENU;
		r = 0;
	}
	if (key == 18) {
		Menu_State = CONFIG_MENU;
		RENDER_REQ(Menu_Render, REDRAW);
		r = 0;
	}
		if (key == 19) {
		Menu_State = TEST_MENU;
		RENDER_REQ(Menu_Render, REDRAW);
		r = 0;
	}

	/** @TEMPCOD **/ /*
	if (key == 35) {
		uint8_t buffer[512];
		testPage(256,buffer);
		LcdDebugMemory(buffer, 100);
		
		r = 0;
	} */
	/** @RESETKEY \TEMP **/
	if (key == 36) {

		memory1.internalFaultTrip = 0;
		memory1.internalFaultTripFirstOut = 0;
		memory1.PowerupTrip = 0;
		memory1.PowerupTripFirstOut = 0;
		memory1.ConfigTrip = 0;
		memory1.ConfigTripFirstOut = 0;
		memory1.ParameterError = 0;
		memory1.ParameterErrorFirstOut = 0;
		memory1.OverspeedTrip = 0;
		memory1.OverspeedTripFirstOut = 0;
		//memory1.SpeedProbOpenWire = 0;
		//memory1.SpeedProbOpenWireFirstOut = 0;

		memory1.SpeedLostTrip = 0;
		memory1.SpeedLostTripFirstOut = 0;
		memory1.OveraccelTrip = 0;
		memory1.OveraccelTripFirstOut = 0;
		memory1.SpeedFailTrip = 0;
		memory1.SpeedFailTripFirstOut = 0;
		memory1.SpeedFailTimeoutTrip = 0;
		memory1.SpeedFailTimeoutTripFirstOut = 0;
		r = 0;
	}
	if (r)
		RENDER_REQ(*MenuRender, REFRESH0);

}




/*---------------------------------------------------------------------------------*/
float lastShow;
void HomeDraw(uint8_t *MenuRender) {

	if (RENDER_CHK(*MenuRender, REDRAW)) {

		Home();
		//prv_memory.speed = 0000.0;
		SpeedDraw(memory1.speed,99999.9, 0x5);
		
		RENDER_END(*MenuRender, REDRAW);
	}
	if (RENDER_CHK(*MenuRender, REFRESH0)) {
		uint8_t sections = 0;
		if (prv_memory.state != memory1.state)
			sections |= 0x1;
		if (prv_memory.speed != memory1.speed)
			sections |= 0x2;
		if(memory1.speed/prv_memory.speed < 0.999 || memory1.speed/prv_memory.speed > 1.001 || memory1.speed/lastShow < 0.995 || memory1.speed/lastShow > 1.005 ||1 )
		{
			SpeedDraw(memory1.speed, lastShow, 0x02 | sections);
			lastShow = memory1.speed;
		}
		prv_memory.speed = memory1.speed;
		prv_memory.state = memory1.state;
	


		RENDER_END(*MenuRender, REFRESH0);

	}

}




/*---------------------------------------------------------------------------------*/

void MenuMng(uint8_t key, uint8_t *MenuState, uint8_t *MenuRender) {
	switch (*MenuState) {
	case 0: {
		*MenuState = MENU_HOME;
		RENDER_REQ(*MenuRender, REDRAW);

	}
		break;
	case MENU_HOME:
		HomeMng(key, MenuState, MenuRender);
		break;

	case MONITOR_MENU:
		monitorMng(key, MenuState, MenuRender);
		break;
	case MONITOR_SUMMARY:
		SummeryMenuMng(key, MenuState, MenuRender);
		break;
	case MONITOR_TRIP1:
		TripMenu1Mng(key, MenuState, MenuRender);
		break;
	case MONITOR_TRIP2:
		TripMenu2Mng(key, MenuState, MenuRender);
		break;

	case MONITOR_ALARM1:
		AlarmMenu1Mng(key, MenuState, MenuRender);
		break;
	case MONITOR_ALARM2:
		AlarmMenu2Mng(key, MenuState, MenuRender);
		break;
	case MONITOR_DEDICATED_INPUT:
		DedicatetInputMng(key, MenuState, MenuRender);
		break;
	case MONITOR_SPEED_INPUT:
		SpeedInputMng(key, MenuState, MenuRender);
		break;
	case MONITOR_SPEED_FAIL_TIMER:
		SpeedFailTimerMng(key, MenuState, MenuRender);
		break;

	case MONITOR_ANALOG_OUTPUT:
		AnalogOutputMng(key, MenuState, MenuRender);
		break;
	case MONITOR_MODBUS:
		ModbusMng(key, MenuState, MenuRender);
		break;
case MONITOR_DATE_TIME:
		DataTimeMng(key, MenuState, MenuRender);
		break;
	case MONITOR_SYSTEM_STATUS:
		SystemStatusMng(key, MenuState, MenuRender);
		break;
	case MONITOR_MODULE_INFORMATION:
		ModuleInformationMng(key, MenuState, MenuRender);
		break;
		

		/***********************LOG******************************/

	case LOG_MENU:
		logMng(key, MenuState, MenuRender);
		break;
	case LOG_OVRSPD_ACCEL:
		Log_Ovrspd_Accel_manager(key, MenuState, MenuRender);
		break;
	case LOG_ALARM:
		log_alarm_manager(key, MenuState, MenuRender);
		break;
	case LOG_TRIP:
		Log_Trip_manager(key, MenuState, MenuRender);
		break;
		case LOG_PEAK_SPD_ACCEL:
		Log_peakspd_Accel_manager(key, MenuState, MenuRender);
		break;
		/***********************CONF******************************/
	case CONFIG_MENU:
		ConfigMng(key, MenuState, MenuRender);
		break;
		case CONFIG_SPEED:
		Config_speed_Mng(key, MenuState, MenuRender);
		break;
		case CONFIG_SPEED_INPUT:
		config_speed_input_manager(key, MenuState, MenuRender);
		break;
		case CONFIG_SPEED_ACCELERATION:
		config_speed_accel_manager(key, MenuState, MenuRender);
		break;
		case CONFIG_SPEED_START_LOGIC:
		config_start_logic_manager(key, MenuState, MenuRender);
		break;
		case CONFIG_TRIP_LATCH:
		config_trip_latch_manager(key, MenuState, MenuRender);
		break;
		case GONFIG_ANALOG_OUTPUT:
		config_analog_output_manager(key, MenuState, MenuRender);
		break;
		case CONFIG_ANALOG_OUTPUT_1:
			configAnout1Mng(key, MenuState, MenuRender);
		break;
		case CONFIG_ANALOG_OUTPUT_2:
			configAnout2Mng(key, MenuState, MenuRender);
		break;
		case CONFIG_TEST_MODES:
		config_test_modes_manager(key, MenuState, MenuRender);
		break;
		case CONFIG_PERIODIC_OVERSPEED_TEST:
		config_periodic_overspeed_test_manager(key, MenuState, MenuRender);
		break;
		case CONFIG_MODBUS:
		config_modbus_manager(key, MenuState, MenuRender);
		break;
				/***********************TEST******************************/
		case TEST_MENU:
		test_menu_manager(key, MenuState, MenuRender);
		break;
		case TEST_TEMPORARY_OVER_SPEED_SETPOINT:
		test_tem_overspeed_setpoint_manager(key, MenuState, MenuRender);
		break;
		case TEST_MANUAL_SIMULATED_SPEED:
		test_manual_simulated_Speed_manager(key, MenuState, MenuRender);
		break;
		case TEST_PERIODIC_OVERSPEED_TEST:
		test_periodic_overspeed_manager(key, MenuState, MenuRender);
		break;
		case TEST_LAMP:
		test_lamp_manager(key, MenuState, MenuRender);
		break;
	}
	return;
}

/*---------------------------------------------------------------------------------*/

void MenuDraw(uint8_t *MenuState, uint8_t *MenuRender) {
	switch (*MenuState) {
	case MENU_HOME:

		HomeDraw(MenuRender);
		break;

	case MONITOR_MENU:
		monitorMenuDraw(MenuRender);
	
		break;
	case MONITOR_SUMMARY:
		monitorSummeryDraw(MenuRender);
		break;
 	case MONITOR_TRIP1:
		TripMenu1Draw(MenuRender);
		break;
	case MONITOR_TRIP2:
		TripMenu2Draw(MenuRender);
		break;

	case MONITOR_ALARM1:
		AlarmMenu1Draw(MenuRender);
		break;

	case MONITOR_ALARM2:
		AlarmMenu2Draw(MenuRender);
		break;
	case MONITOR_DEDICATED_INPUT:
		DedicatedInputDraw(MenuRender);
		break;
	case MONITOR_SPEED_INPUT:
		SpeedInputDraw(MenuRender);
		break;

	case MONITOR_SPEED_FAIL_TIMER:
		SpeedFailTimerDraw(MenuRender);
		break;
		

	case MONITOR_ANALOG_OUTPUT:
		AnalogOutputDraw(MenuRender);
		break;

	case MONITOR_MODBUS:
		ModbusDraw(MenuRender);
		break;

	case MONITOR_DATE_TIME:
		DataTimeDraw(MenuRender);
		break;

	case MONITOR_SYSTEM_STATUS:
		SystemStatusDraw(MenuRender);
		break;

	case MONITOR_MODULE_INFORMATION:
		ModuleInformationDraw(MenuRender);
		break; 

		/********************LOG MENU******************************/
	case LOG_MENU:
		logMenuDraw(MenuRender);
		break;
	case LOG_OVRSPD_ACCEL:
		log_ovrspd_accel_Draw(MenuRender);
		break;
	case LOG_ALARM:
		log_alarm_Draw(MenuRender);
		break;
	case LOG_TRIP:
		log_trip_Draw(MenuRender);
		break;
		case LOG_PEAK_SPD_ACCEL:
		log_peakspd_accel_Draw(MenuRender);
		break;


		/***********************CONFIGMENU******************************/
	case CONFIG_MENU:
		configMenuDraw(MenuRender);
		break;
		case CONFIG_SPEED:
		config_speed_Menu_Draw(MenuRender);
		break;
		case CONFIG_SPEED_INPUT:
		config_speed_input_Draw(MenuRender);
		break;
		case CONFIG_SPEED_ACCELERATION:
		config_speed_acceleration_draw(MenuRender);
		break;
		case CONFIG_SPEED_START_LOGIC:
		config_start_logic_Draw(MenuRender);
		break;
		case CONFIG_TRIP_LATCH:
		config_trip_latch_Draw(MenuRender);
		break;
		case GONFIG_ANALOG_OUTPUT:
		config_analog_output_draw(MenuRender);
		break;
		
		
		case CONFIG_ANALOG_OUTPUT_1:
			configAnout1Draw(MenuRender);
		break;
		
		case CONFIG_ANALOG_OUTPUT_2:
			configAnout2Draw(MenuRender);
		break;

		
		
		case CONFIG_TEST_MODES:
		config_test_modes_draw(MenuRender);
		break;
		case CONFIG_PERIODIC_OVERSPEED_TEST:
		config_periodic_overspeed_test_draw(MenuRender);
		break;
		case CONFIG_MODBUS:
		config_modbus_draw(MenuRender);
		break;
				/***********************TESTMENU******************************/
		case TEST_MENU:
		testMenuDraw(MenuRender);
		case TEST_TEMPORARY_OVER_SPEED_SETPOINT:
		test_tem_overspeed_setpoint_draw(MenuRender);
		break;
		case TEST_MANUAL_SIMULATED_SPEED:
		test_manual_simulated_speed_draw(MenuRender);
		break;
		case TEST_PERIODIC_OVERSPEED_TEST:
		test_periodic_overspeed_draw(MenuRender);
		break;
		case TEST_LAMP:
		test_lamp_draw(MenuRender);
		break;
	}
}

