/****************************************************************************
 *   SOHEIL NAZARI                       $
 *   Project: KEYBOARD CONTROL
 *
 *   Description:
 *   KEYBOARD CONTROL 16 MATRIX
 *
 ****************************************************************************
****************************************************************************/

	#ifndef _KEYBOARD
	#define _KEYBOARD

	#include "type.h"
	#include <LPC407x_8x_177x_8x.h>	
	//Control PIN SELECT

	#define KEY_ROW_POS_1 25
	#define KEY_ROW_POS_2 7
	#define KEY_ROW_POS_3 6
	#define KEY_ROW_POS_4 23
	
	#define KEY_ROW_POR_1 LPC_GPIO0
	#define KEY_ROW_POR_2 LPC_GPIO3
	#define KEY_ROW_POR_3 LPC_GPIO3
	#define KEY_ROW_POR_4 LPC_GPIO0

	
	#define KEY_COL_POS_1 4
	#define KEY_COL_POS_2 5
	#define KEY_COL_POS_3 24
	#define KEY_COL_POS_4 26
	
	#define KEY_COL_POR_1 LPC_GPIO3
	#define KEY_COL_POR_2 LPC_GPIO3
	#define KEY_COL_POR_3 LPC_GPIO0
	#define KEY_COL_POR_4 LPC_GPIO0
	



	//CONTROL PORT



	void KEY_Init(void);
	uint8_t SCAN_KEY();
	#endif
