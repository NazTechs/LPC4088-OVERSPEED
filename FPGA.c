/*****************************************************************************
 *  Soheil Nazari. GENERAL FUNCTION   +989122939002
 *****************************************************************************
 * FileName:        FPGA.c
 * Dependencies:    
 * Processor:       LPC1768
 * Compiler:       	
 * Linker:         
 * Company:			ELLTECHS
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    14/09/2016
 *****************************************************************************/

#include "fpga.h"


#define  _LCD_DEBUG_FPGA
#ifdef _LCD_DEBUG_FPGA
		#include "MAINMENU.h"
		
		#define LCDEBUG_F(args...)	{char D_str[50]; GLCD_FILLRECT(0,21,800,40,YELLOW);drawString(0,20,BLACK,&arialNarrow_20ptFontInfo,"DEBUG_F="); \
											sprintf(D_str,args  );drawString(120,20,BLACK,&arialNarrow_20ptFontInfo,D_str);	}
				
#else
		#define	LCDEBUG_F(args...) ;
#endif
											

#define FPGA_DATA_DIR(x)  { \
														if (x) { \
															 LPC_GPIO0->DIR |= 0x30; \
															 LPC_GPIO1->DIR |= (0x5c44); } \
														else { \
																LPC_GPIO0->DIR &= ~0x30; \
														  	LPC_GPIO1->DIR &= ~(0x5c44); } \
															}
#define FPGA_DATA(x)			{ \
														 LPC_GPIO0->CLR =  0x30;	  \
														 LPC_GPIO1->CLR = (0x5c44); \
														 LPC_GPIO0->SET = (x & 0x3) << 4; \
														 LPC_GPIO1->SET = (x & 0x4)  ; \
														 LPC_GPIO1->SET = (x & 0x8) << 3; \
														 LPC_GPIO1->SET = (x & 0x70) << 6; \
														 LPC_GPIO1->SET = (x & 0x80) << 7; \
													}

#define FPGA_nRST(x) ((x) ? (LPC_GPIO1 -> SET = (1 << 15) ) : (LPC_GPIO1 -> CLR = (1 << 15)))
#define FPGA_DIR(x)  ((x) ? (LPC_GPIO3 -> SET = (1 << 19) ) : (LPC_GPIO3 -> CLR = (1 << 19)))
#define FPGA_CYC(x)  ((x) ? (LPC_GPIO3 -> SET = (1 << 20) ) : (LPC_GPIO3 -> CLR = (1 << 20)))
#define FPGA_ALE(x)  ((x) ? (LPC_GPIO3 -> SET = (1 << 21) ) : (LPC_GPIO3 -> CLR = (1 << 21)))
#define FPGA_STB(x)  ((x) ? (LPC_GPIO4 -> SET = (1 << 14) ) : (LPC_GPIO4 -> CLR = (1 << 14)))		
#define FPGA_WE(x)   ((x) ? (LPC_GPIO4 -> SET = (1 << 15) ) : (LPC_GPIO4 -> CLR = (1 << 15)))	

uint16_t parDefect = 0;	
uint32_t reCounter = 0;	
uint32_t reCounterTRM = 0;														
uint32_t totalMatch = 0;											
void Fpga_init() {

	/*
	 P0[4]  >>>  D0
	 P0[5]  >>>  D1
	 P1[2]  >>>  D2
	 P1[6]  >>>  D3
	 P1[10] >>>  D4
	 P1[11] >>>  D5
	 p1[12] >>>  D6
	 p1[14] >>>  D7

	 p1[15] >>>  nRst
	 p3[19] >>>  m_dir
	 p3[20] >>>  m_cyc
	 p3[21] >>>  m_ale
	 p4[14] >>>  m_stb
	 p4[15] >>>  m_we
	 p4[24] >>>  m_ack
	
	 p4[30] >>> m_parity
	 */

	FPGA_DATA_DIR(1);
	LPC_GPIO1->DIR |= (0x1 << 15);
	LPC_GPIO3->DIR |= (0x1 << 19);
	LPC_GPIO3->DIR |= (0x1 << 20);
	LPC_GPIO3->DIR |= (0x1 << 21);
	LPC_GPIO4->DIR |= (0x1 << 14);
	LPC_GPIO4->DIR |= (0x1 << 15);
	LPC_GPIO4->DIR &= ~(0x1 << 24);
	LPC_GPIO4->DIR &= ~(0x1 << 30);
	{
		int i;
		FPGA_nRST(0);
		for (i = 0; i < 1000; i++)
			;
		FPGA_nRST(1);
		for (i = 0; i < 1000; i++)
			;
	}

}

uint8_t CheckAck() {
	uint32_t val = 0;
	uint8_t data = 0;
	LPC_GPIO4->MASK = ~(1 << 24);
	val = LPC_GPIO4->PIN;
	data = val >> (24);
	LPC_GPIO4->MASK = 0x00000000;
	return (data);
}
uint8_t CheckPar() {
	uint32_t val = 0;
	uint8_t data = 0;
	LPC_GPIO4->MASK = ~(1 << 30);
	val = LPC_GPIO4->PIN;
	data = val >> (30);
	LPC_GPIO4->MASK = 0x00000000;
	return (data);
}

void Fpga_write_add(uint8_t data, uint8_t add) {
	FPGA_DIR(1);
	FPGA_STB(0);
	FPGA_CYC(0);
	FPGA_WE(1);
	FPGA_DATA(add);
	FPGA_ALE(1);
	{
		int i = 0;
		for (i = 0; i < 10; i++)
			;
	}
	FPGA_ALE(0);
	FPGA_DATA(data);
	FPGA_STB(1);
	FPGA_CYC(1);
	while (CheckAck() == 0)
		;
	FPGA_STB(0);
	FPGA_CYC(0);
	FPGA_WE(0);

}

uint8_t Fpga_read_bus() {
	uint32_t val = 0;
	uint8_t data = 0;

	FPGA_DATA_DIR(0);

	LPC_GPIO0->MASK = ~(0x30);
	val = LPC_GPIO0->PIN;
	data = val >> 4;
	LPC_GPIO0->MASK = 0x00000000;

	LPC_GPIO1->MASK = ~(1 << 2);
	val = LPC_GPIO1->PIN;
	data |= val;

	LPC_GPIO1->MASK = ~(1 << 6);
	val = LPC_GPIO1->PIN;
	data |= val >> (6 - 3);

	LPC_GPIO1->MASK = ~(7 << 10);
	val = LPC_GPIO1->PIN;
	data |= val >> (10 - 4);

	LPC_GPIO1->MASK = ~(1 << 14);
	val = LPC_GPIO1->PIN;
	data |= val >> (14 - 7);

	LPC_GPIO1->MASK = 0x00000000;
	FPGA_DATA_DIR(1);

	return (data);
}

uint8_t Fpga_read_add(uint8_t add) {
	uint8_t data = 0;
	uint8_t par;
	FPGA_DIR(1);
	FPGA_STB(0);
	FPGA_CYC(0);
	FPGA_WE(0);
	FPGA_DATA(add);
	FPGA_ALE(1);
	{
		int i = 0;
		for (i = 0; i < 10; i++)
			;
	}
	FPGA_ALE(0);
	FPGA_DIR(0);
	FPGA_STB(1);
	FPGA_CYC(1);
	while (CheckAck() == 0)
		;
			{
		int i = 0;
		for (i = 0; i < 10; i++)
			;
	}
	data = Fpga_read_bus();

	par=CheckPar();

	FPGA_STB(0);
/*	if (par == data%2)
		*ecc = 0;
	else 
		*ecc = 1;
	*/
	/*if (par != ((data>>7 && 0x1) + (data>>6 && 0x1) + (data>>5 && 0x1) + (data>>4 && 0x1) + (data>>3 && 0x1) + (data>>2 && 0x1) + (data && 0x1))%2)
		parDefect++;
	reCounter++;
	LCDEBUG_F("data = %02X Par = %01d PD = %04d  RC = %08d",data,par,parDefect,reCounter); */
	return (data);

}

uint8_t Fpga_read_add_TRM(uint8_t add) {
	
	uint8_t data[3] = {0,0,0};
	uint8_t par[3];
	FPGA_DIR(1);
	FPGA_STB(0);
	FPGA_CYC(0);
	FPGA_WE(0);
	FPGA_DATA(add);
	FPGA_ALE(1);
	{
		int i = 0;
		for (i = 0; i < 10; i++)
			;
	}
	FPGA_ALE(0);
	FPGA_DIR(0);
	FPGA_STB(1);
	FPGA_CYC(1);
	while (CheckAck() == 0)

			{int i = 0;for (i = 0; i < 10; i++);}
	data[0] = Fpga_read_bus();
	par[0]=CheckPar();
	{int i = 0;for (i = 0; i < 10; i++);}
	
  data[1] = Fpga_read_bus();
	par[1]=CheckPar();
	{int i = 0;for (i = 0; i < 10; i++);}
	
	data[2] = Fpga_read_bus();	
	par[2]=CheckPar();
	{int i = 0;for (i = 0; i < 10; i++);}

	FPGA_STB(0);
/*	if (par == data%2)
		*ecc = 0;
	else 
		*ecc = 1;
	*/
	if (par[0] != data[0]%2 && par[1] != data[1]%2 && par[2] != data[2]%2)
		parDefect++;
	reCounter++;
	reCounterTRM++;
	{char D_str[50]; GLCD_FILLRECT(0,41,200,60,GREEN); \
		sprintf(D_str,"TRM = %d T=%d D=%d", totalMatch ,reCounterTRM,reCounterTRM-totalMatch );drawString(0,40,YELLOW,&arialNarrow_20ptFontInfo,D_str);	}
	//LCDEBUG_F("PD = %04d  RC = %08d TRM= %08d",data[0],par[0],parDefect,reCounter,totalMatch);
	{int i = 0;for (i = 0; i < 1000; i++);}
	if(data[0] == data[1] && data[0] == data[2])
	{
		totalMatch++;
		return (data[0]);
	}
	else if (data[0] == data[1])
		return (data[0]);
	else if (data[1] == data[2])
		return (data[1]);
	else if (data[0] == data[2])
		return (data[0]);
	else 
		return (data[0]);
	
	
}


float Fpga_readSpTRM(uint8_t add, uint8_t nPulse) {
	uint8_t s[4] = { 0 };
	float sp = 0.0;
	uint8_t add_tmp = add & 0xF0;
	s[0] = Fpga_read_add_TRM(add_tmp);
	s[1] = Fpga_read_add_TRM(add_tmp | 0x01);
	s[2] = Fpga_read_add_TRM(add_tmp | 0x02);
	s[3] = Fpga_read_add_TRM(add_tmp | 0x03);
	if (((s[0] << 24) + (s[1] << 16) + (s[2] << 8) + s[3]) != 0) {
		sp = 60.0
				/ (((float) ((s[0] << 24) + (s[1] << 16) + (s[2] << 8) + s[3]))
						/ 50000000.0 / ((float) nPulse));
		if (sp < 2.0)
			sp = 0.0;
	} else

		sp = 0.0;

	return sp;

}


void Fpga_speed_init(uint8_t add, uint16_t hiLimit, uint16_t loLimit,
		uint8_t nPulse, uint8_t CnvSpeed) {

	uint8_t add_tmp = add & 0xF0;
	Fpga_write_add(0x00, add_tmp | 0x04);  // STATE SET 0
	Fpga_write_add((hiLimit >> 8) & 0xff, add_tmp | 0x05);
	Fpga_write_add((uint8_t) (hiLimit & 0xff), add_tmp | 0x06); // DEF EMAM 2250
	Fpga_write_add((loLimit >> 8) & 0xff, add_tmp | 0x07);
	Fpga_write_add((uint8_t) (loLimit & 0xff), add_tmp | 0x08);	// DEF EMAM 1750
	Fpga_write_add(nPulse, add_tmp | 0x09);  // DEF EMAM 16
	Fpga_write_add(CnvSpeed, add_tmp | 0x0A);  // DEF EMAM 1/8
	Fpga_write_add(0x03, add_tmp | 0x04);

}

float Fpga_readSp(uint8_t add, uint8_t nPulse) {
	uint8_t s[4] = { 0 };
	float sp = 0.0;
	uint8_t add_tmp = add & 0xF0;
	s[0] = Fpga_read_add(add_tmp);
	s[1] = Fpga_read_add(add_tmp | 0x01);
	s[2] = Fpga_read_add(add_tmp | 0x02);
	s[3] = Fpga_read_add(add_tmp | 0x03);
	if (((s[0] << 24) + (s[1] << 16) + (s[2] << 8) + s[3]) != 0) {
		sp = 60.0
				/ (((float) ((s[0] << 24) + (s[1] << 16) + (s[2] << 8) + s[3]-16)) //add +1
						/ 50000000.0 / ((float) nPulse));
		if (sp < 10.0)
			sp = 0.0;
	} else

		sp = 0.0;

	return sp;

}

uint8_t Fpga_Trip(uint8_t state) {
	if (state == 1)
		Fpga_write_add(0x0B, 1);
	else
		Fpga_write_add(0x08, 1);
}

uint8_t Fpga_set_pwm(uint16_t pwm_set,uint8_t add)
{
		Fpga_write_add((pwm_set) & 0xFF ,add | 0x01);
		Fpga_write_add(pwm_set >> 8 ,add | 0x02);
		Fpga_write_add(0x03 ,add | 0x03);
		Fpga_write_add(0x00 ,add | 0x03);
}

