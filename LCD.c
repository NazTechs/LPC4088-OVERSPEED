/*****************************************************************************
 *  Soheil Nazari. LCD SSD1963 FUNCTION   +989122939002
 *****************************************************************************
 * FileName:        LCD_FUNC.h
 * Dependencies:    
 * Processor:       LPC4088
 * Compiler:       	
 * Linker:         
 * Company:			TADBIR
 *
 * Author               @Date \95-11-18       Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    1/10/2017
 *****************************************************************************/

#include "LCD.h"

/**********************LOCAL Structure************************************
 *
 *************************************************************************/

typedef struct {
	int posx;
	int posy;
	int posx2;
	int posy2;

	uint8_t win_size;
	uint8_t total_item;
	uint8_t win_s;
	uint8_t s_item;

	uint16_t f_color;
	uint16_t b_color;
	uint16_t fs_color;
	uint16_t bs_color;

	const FONT_INFO *font;
	uint16_t distance;

} ListBox;

typedef struct {
	int posx;
	int posy;
	int posx2;
	int posy2;

	uint8_t *value;
	uint8_t offsetx;
	uint8_t offsety;

	uint16_t fs_color;
	uint16_t fb_color;
	uint16_t ts_color;
	uint16_t tb_color;

	const FONT_INFO *font;

} BoolBox;

typedef struct {
	int posx;
	int posy;
	int posx2;
	int posy2;

	uint8_t selected;
	uint8_t input;

	uint32_t value;

	uint32_t max;
	uint32_t min;

	uint8_t cursor;
	uint8_t lenght;
	uint8_t dist;

	uint16_t fs_color;
	uint16_t fb_color;
	uint16_t ts_color;
	uint16_t tb_color;

	const FONT_INFO *font;

} NumBox;

void increase(NumBox *number) {
	uint32_t p = (uint32_t) pow(10, number->cursor);
	if (number->value + p <= number->max)
		number->value = number->value + p;
}

void decrease(NumBox *number) {
	uint32_t p = (uint32_t) pow(10, number->cursor);
	if (number->value - p >= number->min)
		number->value = number->value - p;
}

void next(NumBox *number) {

	if (number->cursor < number->lenght)
		number->cursor++;

}

void prv(NumBox *number) {

	if (number->cursor > 0)
		number->cursor--;

}

/**********************LOCAL FUNCTION************************************
 *
 *************************************************************************/

void DrawList(ListBox *List, char items[25][40], uint8_t shifts[25]) {
	uint8_t i;
	uint16_t swin_y1, swin_y2;
	if (List->s_item > List->total_item - 1)
		List->s_item = List->total_item - 1;
	else {
		GLCD_FILLRECT(List->posx, List->posy, List->posx2, List->posy2,
				List->f_color);
		// DETECT windows
		if (List->s_item < List->win_s) {
			List->win_s = List->s_item;
		} else if (List->s_item >= List->win_s + List->win_size) {
			List->win_s = List->s_item - List->win_size + 1;
		}
		// DRAW WINDOW

		for (i = 0; i < List->win_size; i++) {
			drawString(List->posx + shifts[List->win_s + i],
					List->posy + i * List->distance + 10, List->b_color,
					List->font, items[List->win_s + i]);
		}
		swin_y1 = List->posy + List->distance * (List->s_item - List->win_s)
				- 10;
		swin_y2 = List->posy + List->distance * (List->s_item - List->win_s + 1)
				- 10;
		if (swin_y1 < List->posy)
			swin_y1 = List->posy;
		if (swin_y2 > List->posy2)
			swin_y2 = List->posy2;
		GLCD_FILLRECT(List->posx, swin_y1, List->posx2, swin_y2,
				List->fs_color);
		drawString(List->posx + shifts[List->s_item],
				List->posy + List->distance * (List->s_item - List->win_s) + 10,
				List->bs_color, List->font, items[List->s_item]);

	}
}

void DrawBB(BoolBox *BB) {
	if (*BB->value == 1) {
		GLCD_FILLRECT(BB->posx, BB->posy, BB->posx2, BB->posy2, BB->tb_color);
		drawString(BB->posx + BB->offsetx, BB->posy + BB->offsety, BB->ts_color,
				BB->font, "TRUE");
	} else if (*BB->value == 0) {
		GLCD_FILLRECT(BB->posx, BB->posy, BB->posx2, BB->posy2, BB->fb_color);
		drawString(BB->posx + BB->offsetx, BB->posy + BB->offsety, BB->fs_color,
				BB->font, "FALSE");

	} else if (*BB->value == 3) {
		GLCD_FILLRECT(BB->posx, BB->posy, BB->posx2, BB->posy2, RED);
		drawString(BB->posx + BB->offsetx, BB->posy + BB->offsety, BB->ts_color,
				BB->font, "ERR");

	} else if (*BB->value == 4) {
		GLCD_FILLRECT(BB->posx, BB->posy, BB->posx2, BB->posy2, GRAY1);
		drawString(BB->posx + BB->offsetx, BB->posy + BB->offsety, BB->ts_color,
				BB->font, "NA");

	}

}
/**********************Global FUNCTION************************************
 *
 *************************************************************************/
#include "monitor_menu/monitor_menu_lcd.c"
#include "monitor_summary/monitor_summary_lcd.c"
#include "monitor_trip_latch/monitor_trip_latch_lcd.c"
#include "monitor_alarm_latch/monitor_alarm_latch_lcd.c"
#include "monitor_dedicated_discrete_input/monitor_dedicated_discrete_input_lcd.c"
#include "monitor_speed_input/monitor_speed_input_lcd.c"
#include "monitor_speed_fail_timer/monitor_speed_fail_timer_lcd.c"
#include "monitor_analog_output/monitor_analog_output_lcd.c"
#include "monitor_modbus/monitor_modbus_lcd.c"
#include "monitor_date_time/monitor_date_time_lcd.c"
#include "monitor_system_status/monitor_system_status_lcd.c"
#include "monitor_module_information/monitor_module_information_lcd.c"

#include "config_menu_src/Config_Menu_LCD.c"
#include "log_menu_src/LOG_MENU_LCD.c"
#include "LogOspAcc/log_ovrspd_accel_lcd.c"
#include "log_alarm/log_alarm_lcd.c"
#include "log_trip/log_trip_lcd.c"
#include "log_peakspd_accel/log_peakspd_accel_LCD.c"
#include "config_speed_submenu/config_speed_menu_lcd.c"
#include "config_speed_input/config_speed_input_lcd.c"
#include "config_speed_acceleration/config_speed_accel_lcd.c"
#include "config_start_logic/config_start_logic_lcd.c"
#include "config_trip_latch/config_trip_latch_lcd.c"
#include "config_analog_output/config_analog_output_lcd.c"
#include "config_test_modes/config_test_modes_lcd.c"
#include "config_periodic_overspeed_test/config_periodic_overspeed_test_lcd.c"
#include "config_modbus/config_modbus_lcd.c"



#include "config_analog_output_1/config_anout1_lcd.c"
#include "config_analog_output_2/config_anout2_lcd.c"


#include "test_menu/test_menu_lcd.c"
#include "test_tem_overspeed_setpoint/test_tem_overspeed_setpoint_lcd.c"
#include "test_manual_simulated_speed/test_manual_simulated_speed_lcd.c"
#include "test_periodic_overspeed/test_periodic_overspeed_lcd.c"
#include "test_lamp/test_lamp_lcd.c"


void intro() {
	ClearDevice_F(0xFFFF);
	GLCD_RECT_LINE(6, 7, 792, 468, BLACK);
	GLCD_RECT_LINE(7, 8, 791, 467, BLACK);
	GLCD_RECT_LINE(8, 9, 790, 466, BLACK);
	GLCD_RECT_LINE(9, 10, 789, 465, BLACK);
	drawCharBitmap(235, 25, RGB565CONVERT(0, 113, 118), tADBIRGARAN_4Bitmaps,
			tADBIRGARAN_4WidthPages, tADBIRGARAN_4HeightPixels);
	drawString(40, 395, BLACK, &arial_24ptFontInfo, "L o a d i n g  .  .  .");
	GLCD_RECT_LINE(30, 425, 770, 455, BLACK);
	{
		int i, j;
		for (i = 32; i <= 769; i=i+28) { //low speed modifi
			GLCD_FILLRECT(31, 426, i, 454, RGB565CONVERT(177, 210, 67));
			//	for (j = 0 ; j <= 200000 ; j++);
		}
	}
}

/**************************************************************
 * @name Main LCD
 * @param uint8_t sections
 * @return void
 *
 * @Author MOJ
 * @REV 01
 * @Date 1/23/2017
 *************************************************************/
void MAIN_LCD(uint8_t sections) {

	ClearDevice_F(0xFFFF);
	GLCD_FILLRECT(1, 16, 779, 70, GRAY1);
	GLCD_FILLRECT(1, 71, 790, 73, BLACK);
	GLCD_FILLRECT(1, 1, 799, 15, BLACK);
	GLCD_FILLRECT(780, 1, 799, 479, BLACK);


	GLCD_FILLRECT(1, 395, 790, 397, BLACK);

	drawString(9, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Monitor Menu");

	GLCD_FILLRECT(201, 395, 203, 479, BLACK);
	drawString(231, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Log Menu");

	GLCD_FILLRECT(391, 395, 393, 479, BLACK);
	drawString(406, 427, BLACK, &arialRoundedMTBold_24ptFontInfo,
			"Config Menu");

	GLCD_FILLRECT(587, 395, 589, 479, BLACK);
	drawString(608, 427, BLACK, &arialRoundedMTBold_24ptFontInfo, "Test Menu");


}

void Home(void) {
	MAIN_LCD(0);
	
	drawString(355, 30, BLACK, &arialRoundedMTBold_26ptFontInfo, "HOME");
	drawString(280, 105, BLACK, &arialRoundedMTBold_26ptFontInfo, "SPEED     RPM");

}
void SpeedDraw(float sp, float prv_sp, uint8_t sections) {

	int j, j2;
	char str[2] = { 0, 0 };
	char number[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	if ((sections & 0x1)) {
		if (memory1.state == 2) {
			GLCD_FILLRECT(1, 330, 779, 395, RED);
			drawString(195, 332, YELLOW, &arialRoundedMTBold_48ptFontInfo,
					"MODULE  TRIP");
		}
		if (memory1.state == 1)
		{
			GLCD_FILLRECT(1, 330, 779, 395, YELLOW);
			drawString(195, 332, BLACK, &arialRoundedMTBold_48ptFontInfo,
					"MODULE  ALARM");
		}
		if (memory1.state == 0) {
			GLCD_FILLRECT(1, 300, 779, 395, WHITE);
		}
	}
	if ((sections & 0x2)) {
		j = sp * 10;
		j2 = prv_sp * 10;
		if ((j / 100000) % 10 != (j2 / 100000) % 10) {
			str[0] = number[(j / 100000) % 10];
			GLCD_FILLRECT(189, 190, 189 + 1 * 75, 270, WHITE);
			drawString(189 + 0 * 75, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
		}

		if ((j / 10000) % 10 != (j2 / 10000) % 10) {
			str[0] = number[(j / 10000) % 10];
			GLCD_FILLRECT(189 + 1 * 75, 190, 189 + 2 * 75, 270, WHITE);
			drawString(189 + 1 * 75, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
		}

		if ((j / 1000) % 10 != (j2 / 1000) % 10) {
			str[0] = number[(j / 1000) % 10];
			GLCD_FILLRECT(189 + 2 * 75, 190, 189 + 3 * 75, 270, WHITE);
			drawString(189 + 2 * 75, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
		}

		if ((j / 100) % 10 != (j2 / 100) % 10) {
			str[0] = number[(j / 100) % 10];
			GLCD_FILLRECT(189 + 3 * 75, 190, 189 + 4 * 75-10, 270, WHITE);
			drawString(189 + 3 * 75, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
		}

		if ((j / 10) % 10 != (j2 / 10) % 10) {
			GLCD_FILLRECT(189 + 4 * 75, 190, 189 + 5 * 75, 270, WHITE);
			str[0] = number[(j / 10) % 10];
			drawString(189 + 4 * 75-5, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, "." );
			drawString(189 + 4 * 75 + 15, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
		}
//			drawString(189 + 4 * 75 + 55, 190, BLACK,
//					&arialRoundedMTBold_72ptFontInfo, ".");
//		}
//		if (j % 10 != j2 % 10) {
//			GLCD_FILLRECT(189 + 5 * 75, 190,189 + 6 * 75, 270, WHITE);
//			str[0] = number[j % 10];
//			drawString(189 + 5 * 75, 190, BLACK,
//					&arialRoundedMTBold_72ptFontInfo, str);
//		}
	}
	if ((sections & 0x4))
		{
		j = sp * 10;
		j2 = prv_sp * 10;
		
			str[0] = number[(j / 100000) % 10];
			GLCD_FILLRECT(189, 190, 189 + 1 * 75, 270, WHITE);
			drawString(189 + 0 * 75, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
		

		
			str[0] = number[(j / 10000) % 10];
			GLCD_FILLRECT(189 + 1 * 75, 190, 189 + 2 * 75, 270, WHITE);
			drawString(189 + 1 * 75, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
		

		
			str[0] = number[(j / 1000) % 10];
			GLCD_FILLRECT(189 + 2 * 75, 190, 189 + 3 * 75, 270, WHITE);
			drawString(189 + 2 * 75, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
		

		
			str[0] = number[(j / 100) % 10];
			GLCD_FILLRECT(189 + 3 * 75, 190, 189 + 4 * 75, 270, WHITE);
			drawString(189 + 3 * 75, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
		

		
			GLCD_FILLRECT(189 + 4 * 75, 190, 189 + 5 * 75, 270, WHITE);
			str[0] = number[(j / 10) % 10];
			drawString(189 + 4 * 75, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
					
						 {
			str[0] = number[(j / 100) % 10];
			GLCD_FILLRECT(189 + 3 * 75, 190, 189 + 4 * 75-10, 270, WHITE);
			drawString(189 + 3 * 75, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
		}

		 {
			GLCD_FILLRECT(189 + 4 * 75, 190, 189 + 5 * 75, 270, WHITE);
			str[0] = number[(j / 10) % 10];
			drawString(189 + 4 * 75-5, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, "." );
			drawString(189 + 4 * 75 + 15, 190, BLACK,
					&arialRoundedMTBold_72ptFontInfo, str);
		}
				}
}

/********************************************************************
 * @name Buffer Writer
 *
 ********************************************************************/

void LcdDebugMemory(uint8_t *buffer, uint16_t bytes) {

	int i;
	char str[10];
	ClearDevice_F(LIGHTRED);
	for (i = 0; i < bytes; i++) {
		sprintf(str, "%03d ", *(buffer + i));
		drawString(10 + (i % 8) * 80, 10 + (i / 8) * 40, BLACK,
				&arialRoundedMTBold_24ptFontInfo, str);
	}

}

