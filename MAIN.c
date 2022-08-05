/* * * * * SOHEIL * * * * *
 * * * * * 1395,10,22 * * * * */

#include "type.h"
#include <stdlib.h>     /* atoi */
#include <string.h>

#include <LPC407x_8x_177x_8x.h>
#include <math.h>

#include "SSP_LPC408x.h"

#include "KEYBOARD.h"
#include "MAINMENU.h"

#include "RTC.h"

#include "UART_LPC4088.h"
#include "OSPMNG.h"

#include "MODBUSMNG.h"

#define  _FILE_DEBUG
#ifdef _FILE_DEBUG

#define DEBUG(args...)	{char D_str[50]; ;UART0_PrintString("\r\n#DEBUG_MAIN.c   "); \
											sprintf(D_str,args  );UART0_PrintString(D_str);										  }

#else
#define	DEBUG(args...) ;
#endif

/*
 //-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
 */
/*----------------------------------------------------------------------------
 //
 //  <e> Game Setting
 //      <h> NAZARI Game ENABLE
 //          <o1.0>  Nazari Game Controll Bit
 //                  <i>     Game
 //                  <0=>    Worm
 //                  <1=>    Screeps Game
 //
 //      </h>
 //
 //  </e>
 */

/************************************************************************/

/**********************GLOBAL VARIBLE************************************
 *
 *************************************************************************/

uint32_t data;
uint8_t src_addr[16]; //16 byte Write buffer
uint8_t dest_addr[16]; //16 byte Read buffer

int main() {

	/**********************PERSISTANCE VARIBLE********************************
	 *
	 *************************************************************************/

	
	uint8_t pre_key = 1, pre_Menu_State = 254, pre_Menu_Render = 255;
  uint16_t refreshCounter = 0;
	uint16_t LCD_DATA[3];
	uint32_t hnum = 0;
	
		//LPC_WDT->FEED = 0xAA;
	//LPC_WDT->FEED = 0x55;
	
	/**********************INIT******************************************
	 *
	 *********************************************************************/
	MemoryInit(&memory1);
	{
			//LPC_WDT->

			LPC_WDT->MOD = 0x3;
			LPC_WDT->TC = 0x5FFFF;
			LPC_WDT->FEED = 0xAA;
			LPC_WDT->FEED = 0x55;

		}
	
	SystemInit();
		{
			int i;
			  LPC_GPIO1->DIR  |= (1<<21);
		LPC_GPIO1->CLR  = (1<<21);
			
		for(i=0;i<100000;i++);
		}

	KEY_Init();
	UART0_Init(57600);
	DEBUG("world is resurrecting");
		
	initModbus(57600,1);
	rtc_init();
	SSP0Init();
	at45db_init();
	MenuInit();


	
	osp_init();
	int_EEPROM();

	//		while(1)
	//		{
	//			int i;
	//				LCDEBUG("FLASH STATE=%x",at45db_init());
 	//			for (i = 0 ; i < 10000000;i++);
	//		}
		
		
	while (1) {
		uint8_t key = SCAN_KEY();
		
		LPC_WDT->FEED = 0xAA;
		LPC_WDT->FEED = 0x55;
		
		MenuMng(key, &Menu_State, &Menu_Render);
		MenuDraw(&Menu_State, &Menu_Render);
	//	while(1);
/*		refreshCounter++;
		if(refreshCounter > 200)
		{
			CLCD_RST(0);
			DelayMs_SSD(10);
			CLCD_RST(1);
			refreshCounter=0;
		}*/
		

		{
		WriteCommand(0xE3);
		CLCD_DATA_IN;
		ReadData(LCD_DATA[0]);
		ReadData(LCD_DATA[1]);
		ReadData(LCD_DATA[2]);
		CLCD_DATA_OUT;
			if (LCD_DATA[0] != 0x1E)
			{
				int i;
				LPC_GPIO1->SET  = (1<<21);
				for(i=0;i<100000;i++);
				LPC_GPIO1->CLR  = (1<<21);
				for(i=0;i<100000;i++);
				ResetDevice();
				Menu_Render= REDRAW;
				hnum ++;
			}
		}

/*		refreshCounter++;
		if (refreshCounter > 100)
		{
		Menu_Render= REDRAW;
			refreshCounter = 0;
		} */
		chkModbus();
		ospUpdate();

		{

			rtcGetTime(&memory1.sec, &memory1.min, &memory1.hour);
			rtcGetDate(&memory1.day, &memory1.mounth, &memory1.year);
		}

		{

			if (key != pre_key || pre_Menu_State != Menu_State
					|| pre_Menu_Render != Menu_Render) {
				char str[32];
				uint8_t i = 0;
				while (LPC_UART1->LSR & 0x1) {
					str[i] = LPC_UART1->RBR;
					i++;
				}
				str[i] = 0;
				/*LCDEBUG("KEY=%d-MENU=%d,Menu=%dMemory=%f CHAR = %s %c", key,
						Menu_State, Menu_Render, memory1.speed, str, 'a'); */
				pre_key = key;
				pre_Menu_State = Menu_State;
				pre_Menu_Render = Menu_Render;
			}

		}
		
	/*	{
		   	uint8_t  buff1, buff2;
				int16_t buff[1024];
				uint16_t buffcounter = 0;
			  int32_t meanbuff  = 0;
			  uint32_t del;
				for(buffcounter = 0; buffcounter < 1024 ; buffcounter++)
			{
				buff1 = Fpga_read_add(0x4C);
				buff2 = Fpga_read_add(0x4D);
				buff[buffcounter] = (buff2 << 8)| buff1;
				for(del = 0 ; del<10000;del++);
				meanbuff = meanbuff + buff[buffcounter];
		}
			  meanbuff = meanbuff / 1024;
		{char D_str[50]; GLCD_FILLRECT(0,81,200,100,BLUE);
		   sprintf(D_str,"mean = %d ms",meanbuff );
			  drawString(0,80,YELLOW,&arialNarrow_20ptFontInfo,D_str);	}
	}
		*/
//#define siguart
#ifdef siguart

	while(1)
				{int i;
					char D_str[50]; GLCD_FILLRECT(0,81,200,100,BLUE);
		   sprintf(D_str,"tc = %02X ms",UART1_Getchar() );
			  drawString(80,80,YELLOW,&arialNarrow_20ptFontInfo,D_str);
					for(i=0;i<100000;i++);
		LPC_WDT->FEED = 0xAA;
		LPC_WDT->FEED = 0x55;				}

#endif

//#define sigview
#ifdef sigview
									Fpga_write_add((49100) & 0xFF , 0x11);//10140
								  Fpga_write_add(49100 >> 8 , 0x12);
								  Fpga_write_add(0x03 , 0x13);
								  Fpga_write_add(0x00 , 0x13);
			
			Fpga_write_add((49100) & 0xFF , 0x31);
								  Fpga_write_add(49100 >> 8 , 0x32);
								  Fpga_write_add(0x03 , 0x33);
								  Fpga_write_add(0x00 , 0x33);
		while(1)
		{
			int16_t buff[1024];
			int16_t buffh[1024];
			uint16_t buffcounter = 0;
			uint32_t del;
			uint8_t  buff1, buff2, buff3, buff4;
			int32_t meanbuff  = 0;
			int32_t meanbuffh = 0;
			float sTime;
			//for(del = 0 ; del<10000000;del++);
			LPC_TIM0->TC = 0;
			LPC_TIM0->TCR = 1;
			

			
			for(buffcounter = 0; buffcounter < 1024 ; buffcounter++)
			{
				buff1 = Fpga_read_add(0x4C);
			  buff2 = Fpga_read_add(0x4D);
				buff3 = Fpga_read_add(0x5C);
			  buff4 = Fpga_read_add(0x5D);
				for(del = 0 ; del<1;del++);
				buff[buffcounter] = (buff2 << 8)| buff1;
				buffh[buffcounter] = (buff4 << 8)| buff3;
				
				meanbuff = meanbuff + buff[buffcounter];
				meanbuffh = meanbuffh + buffh[buffcounter];
			}
			sTime = ((float)LPC_TIM0->TC) / 60000.0;
			GLCD_FILLRECT(0,100,800,400,BLACK);
			meanbuff = meanbuff / 1024;
			meanbuffh = meanbuffh / 1024;
			for(buffcounter = 2; buffcounter < 800 ; buffcounter++)
			{
				PutPixel_C(buffcounter,175 + (meanbuff-buff[buffcounter])/50,BRIGHTRED);
				PutPixel_C(buffcounter,175 + (meanbuff-buff[buffcounter])/50+1,BRIGHTRED);
				PutPixel_C(buffcounter,175 + (meanbuff-buff[buffcounter])/50-1,BRIGHTRED);
				
				PutPixel_C(buffcounter-1,175 + (meanbuff-buff[buffcounter])/50,BRIGHTRED);
				PutPixel_C(buffcounter-1,175 + (meanbuff-buff[buffcounter])/50+1,BRIGHTRED);
				PutPixel_C(buffcounter-1,175 + (meanbuff-buff[buffcounter])/50-1,BRIGHTRED);
				
				PutPixel_C(buffcounter-2,175 + (meanbuff-buff[buffcounter])/50,BRIGHTRED);
				PutPixel_C(buffcounter-2,175 + (meanbuff-buff[buffcounter])/50+1,BRIGHTRED);
				PutPixel_C(buffcounter-2,175 + (meanbuff-buff[buffcounter])/50-1,BRIGHTRED);
				
				

				PutPixel_C(buffcounter,250+(meanbuffh-buffh[buffcounter])/25,BRIGHTYELLOW);
				PutPixel_C(buffcounter,250+(meanbuffh-buffh[buffcounter])/25+1,BRIGHTYELLOW);
				PutPixel_C(buffcounter,250+(meanbuffh-buffh[buffcounter])/25-1,BRIGHTYELLOW);
				
				PutPixel_C(buffcounter-1,250+(meanbuffh-buffh[buffcounter])/25,BRIGHTYELLOW);
				PutPixel_C(buffcounter-1,250+(meanbuffh-buffh[buffcounter])/25+1,BRIGHTYELLOW);
				PutPixel_C(buffcounter-1,250+(meanbuffh-buffh[buffcounter])/25-1,BRIGHTYELLOW);
				
				PutPixel_C(buffcounter-2,250+(meanbuffh-buffh[buffcounter])/25,BRIGHTYELLOW);
				PutPixel_C(buffcounter-2,250+(meanbuffh-buffh[buffcounter])/25+1,BRIGHTYELLOW);
				PutPixel_C(buffcounter-2,250+(meanbuffh-buffh[buffcounter])/25-1,BRIGHTYELLOW);
				
				}
				LPC_WDT->FEED = 0xAA;
				LPC_WDT->FEED = 0x55;
				

				{
					int16_t f_buffh[1024-32];
					int32_t mean_f_buff  = 0;
					int i,j;
					for(i = 0 ; i < 1024 -32 ; i++){
					f_buffh[i] = 0;
					for(j = 0 ; j < 32 ; j++)
					{
						f_buffh[i] = f_buffh[i] + buffh[i+j] / 32;
						LPC_WDT->FEED = 0xAA;
						LPC_WDT->FEED = 0x55;
					}
					mean_f_buff = mean_f_buff + f_buffh[i];
				}
					mean_f_buff = mean_f_buff / 1024-32;
					for(buffcounter = 2; buffcounter < 800 ; buffcounter++)
			{
				//DrawLine(buffcounter-1,250+ 20 +(mean_f_buff-f_buffh[buffcounter-1])/50,buffcounter,250+ 20 +(mean_f_buff-f_buffh[buffcounter])/50,BRIGHTGREEN);
				PutPixel_C(buffcounter,350 +(mean_f_buff-f_buffh[buffcounter])/25,BRIGHTGREEN);
				PutPixel_C(buffcounter,350 +(mean_f_buff-f_buffh[buffcounter])/25+1,BRIGHTGREEN);
				PutPixel_C(buffcounter,350 +(mean_f_buff-f_buffh[buffcounter])/25-1,BRIGHTGREEN);
								PutPixel_C(buffcounter-1,350 +(mean_f_buff-f_buffh[buffcounter])/25,BRIGHTGREEN);
				PutPixel_C(buffcounter-1,350+(mean_f_buff-f_buffh[buffcounter])/25+1,BRIGHTGREEN);
				PutPixel_C(buffcounter-1,350 +(mean_f_buff-f_buffh[buffcounter])/25-1,BRIGHTGREEN);
								PutPixel_C(buffcounter-2,350 +(mean_f_buff-f_buffh[buffcounter])/25,BRIGHTGREEN);
				PutPixel_C(buffcounter-2,350 +(mean_f_buff-f_buffh[buffcounter])/25+1,BRIGHTGREEN);
				PutPixel_C(buffcounter-2,350 +(mean_f_buff-f_buffh[buffcounter])/25-1,BRIGHTGREEN);
				}
				LPC_WDT->FEED = 0xAA;
				LPC_WDT->FEED = 0x55;
					
			}
				{
					int16_t a_buff[1024-128];
					int16_t a_buff_win[128];
					int32_t mean_a_buff  = 0;
					int i,j;
					for (i=0;i<128;i++)
						a_buff_win[i] =  buff[i];
					for(i=0; i < 1024 - 128 ; i++)
					{
						a_buff[i] = 0;
						for (j = 0 ; j < 128 ; j++)
							{
								a_buff[i] = a_buff[i] + buff[i+j] - a_buff_win[j];
							}
					a_buff[i] =	a_buff[i]/32;
					mean_a_buff =mean_a_buff + a_buff[i];  
				  LPC_WDT->FEED = 0xAA;
				  LPC_WDT->FEED = 0x55;
						}
					mean_a_buff = mean_a_buff/(1024-128);
				for(buffcounter = 0; buffcounter < 800 ; buffcounter++)
			  {
				PutPixel_C(buffcounter,250+ 30 +(mean_a_buff-a_buff[buffcounter])/5,BRIGHTCYAN);
				}
			}
						
				
				
				{char D_str[50]; GLCD_FILLRECT(0,81,200,100,BLUE);
		   sprintf(D_str,"tc = %2.3f ms",sTime );
			  drawString(0,80,YELLOW,&arialNarrow_20ptFontInfo,D_str);	}
		}
		
		#endif /**/
		
	}
}

