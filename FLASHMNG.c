/*****************************************************************************
 *  Soheil Nazari. _FLASH__C FUNCTION   +989122939002
 *****************************************************************************
 * @FileName:        LCD_FUNC.h
 * @Dependencies:
 * @Processor:       LPC4088
 * @Compiler:
 * @Linker:
 * @Company:			TADBIR
 *
 * @Author Soheil Nazari              Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    1/10/2017
 *****************************************************************************/

#include "FLASHMNG.h"

/**************************************************************
 *	@MemoryMap
 *	@formatCheck \Page WORD [64..68]
 *	@triploglenght \Page0 WORD [128..131]
 *	@tripPages \Page64 .. 1024
 *
 *************************************************************/
#define TRIPLOGLENGHTPAGE 0
#define TRIPLOGLENGHTADD  128

void testPage(uint16_t lenght,uint8_t *buffer)
{
	//	uint8_t buffer[512];
		int i, j, k;
		k = rand() & 0xFF;
		for (i = 0; i < lenght; i++)
			*(buffer + i) = (uint8_t)(i + k);

		at45db_write_buffer(0, buffer, lenght);
		//at45db_erase_page(0);
		at45db_buffer_to_page(0);

		for (i = 0; i < lenght; i++)
			buffer[i] = 0;

		at45db_read_page_buffered(0, 0, buffer, lenght);
		
}

uint32_t readTriplogLenght(void)
{
	uint8_t buffer[4];
	at45db_read_page_buffered(TRIPLOGLENGHTPAGE, TRIPLOGLENGHTADD, buffer, 4);
	return ((buffer[0] << 24) | (buffer[1] << 16)| (buffer[2] << 8) | buffer[3]);
}
