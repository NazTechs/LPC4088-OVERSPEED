/****************************************************************************
 *   SOHEIL NAZARI                       $
 *   Project: KEYBOARD CONTROL SOURCE
 *
 *   Description:
 *   KEYBOARD CONTROL 16 MATRIX
 *
 ****************************************************************************
****************************************************************************/


	#include "type.h"
	#include "KEYBOARD.h"
	
	uint8_t prv_key;
	void KEY_Init()
	{
		
		//ROW
		LPC_IOCON->P0_25    |= 0x2 << 3; 
		LPC_IOCON->P3_7     |= 0x2 << 3; 
		LPC_IOCON->P3_6     |= 0x2 << 3; 
		LPC_IOCON->P0_23    |= 0x2 << 3; 
		
		//COL
		LPC_IOCON->P3_4     |= 0x2 << 3; 
		LPC_IOCON->P3_5     |= 0x2 << 3; 
		LPC_IOCON->P0_24    |= 0x2 << 3; 
		LPC_IOCON->P0_26    |= 0x2 << 3; 
		
		KEY_ROW_POR_1->CLR  =  (1 << KEY_ROW_POS_1); 
		KEY_ROW_POR_2->CLR  =  (1 << KEY_ROW_POS_2); 
		KEY_ROW_POR_3->CLR  =  (1 << KEY_ROW_POS_3); 
		KEY_ROW_POR_4->CLR  =  (1 << KEY_ROW_POS_4);
		
		
		KEY_COL_POR_1->CLR  =  (1 << KEY_COL_POS_1); 
		KEY_COL_POR_2->CLR  =  (1 << KEY_COL_POS_2); 
		KEY_COL_POR_3->CLR  =  (1 << KEY_COL_POS_3); 
		KEY_COL_POR_4->CLR  =  (1 << KEY_COL_POS_4); 

	}


	uint8_t SCAN_KEY()
	{
		uint32_t val   = 0;
		uint8_t  col_s = 0;
		uint8_t  row_s = 0;
		uint8_t key;
		////////////////////////////////////////////
		
		KEY_ROW_POR_1->DIR |=  (1 << KEY_ROW_POS_1); 
		KEY_ROW_POR_2->DIR |=  (1 << KEY_ROW_POS_2); 
		KEY_ROW_POR_3->DIR |=  (1 << KEY_ROW_POS_3); 
		KEY_ROW_POR_4->DIR |=  (1 << KEY_ROW_POS_4);
		
		KEY_COL_POR_1->DIR &= ~(1 << KEY_COL_POS_1);
		KEY_COL_POR_2->DIR &= ~(1 << KEY_COL_POS_2);
		KEY_COL_POR_3->DIR &= ~(1 << KEY_COL_POS_3);
		KEY_COL_POR_4->DIR &= ~(1 << KEY_COL_POS_4);
		
		////////////////////////////////////////////
		
		{ int i; for(i=0;i<50;i++);}
		

		
		
		val = KEY_COL_POR_1->PIN;
		val = (val >> KEY_COL_POS_1) & 0x0001;
		if (val == 0)
			col_s = 1;
		
				val = KEY_COL_POR_2->PIN;
		val = (val >> KEY_COL_POS_2) & 0x0001;
		if (val == 0)
			col_s = 2;
		
				val = KEY_COL_POR_3->PIN;
		val = (val >> KEY_COL_POS_3) & 0x0001;
		if (val == 0)
			col_s = 3;
		
		val = KEY_COL_POR_4->PIN;
		val = (val >> KEY_COL_POS_4) & 0x0001;
		if (val == 0)
			col_s = 4;
		
		
		////////////////////////////////////////////
		
		KEY_ROW_POR_1->DIR &= ~(1 << KEY_ROW_POS_1); 
		KEY_ROW_POR_2->DIR &= ~(1 << KEY_ROW_POS_2); 
		KEY_ROW_POR_3->DIR &= ~(1 << KEY_ROW_POS_3); 
		KEY_ROW_POR_4->DIR &= ~(1 << KEY_ROW_POS_4);
		
		KEY_COL_POR_1->DIR |=  (1 << KEY_COL_POS_1);
		KEY_COL_POR_2->DIR |=  (1 << KEY_COL_POS_2);
		KEY_COL_POR_3->DIR |=  (1 << KEY_COL_POS_3);
		KEY_COL_POR_4->DIR |=  (1 << KEY_COL_POS_4);
		
		////////////////////////////////////////////	



		

			
		{ int i; for(i=0;i<50;i++);}
		
		val = KEY_ROW_POR_1->PIN;
		val = (val >> KEY_ROW_POS_1) & 0x0001;
		if (val == 0)
			row_s = 1;
		
		val = KEY_ROW_POR_2->PIN;
		val = (val >> KEY_ROW_POS_2) & 0x0001;
		if (val == 0)
			row_s = 2;
		
		val = KEY_ROW_POR_3->PIN;
		val = (val >> KEY_ROW_POS_3) & 0x0001;
		if (val == 0)
			row_s = 3;
		
		val = KEY_ROW_POR_4->PIN;
		val = (val >> KEY_ROW_POS_4) & 0x0001;
		if (val == 0)
			row_s = 4;
		key = row_s << 4 | col_s;
		if (prv_key != key)
		{
			prv_key = key;
			return (row_s << 4 | col_s);
		}
		else
		{
			return 0;
		}
		
	}


