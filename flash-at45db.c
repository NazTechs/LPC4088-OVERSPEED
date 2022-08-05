/* Copyright (c) 2010, Ulf Kulau
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * \addtogroup Device Interfaces
 * @{
 *
 * \addtogroup AT45DB_interface
 * @{
 */

/**
 * \file
 *		Atmel Flash EEPROM AT45DB interface implementation
 * \author
 *      Ulf Kulau <kulau@ibr.cs.tu-bs.de>
 */
 

#include "flash-at45db.h"




int8_t at45db_init(void) {
	uint8_t i = 0, id = 0;
	/*setup buffer manager to perform write and read operations*/
	buffer_mgr.active_buffer = 0;
	buffer_mgr.buffer_addr[0] = AT45DB_BUFFER_1;
	buffer_mgr.buffer_addr[1] = AT45DB_BUFFER_2;
	buffer_mgr.buf_to_page_addr[0] = AT45DB_BUF_1_TO_PAGE;
	buffer_mgr.buf_to_page_addr[1] = AT45DB_BUF_2_TO_PAGE;
	
	
	LPC_GPIO2->DIR |= AT45DB_RST; //RESET
	LPC_GPIO2->DIR |= AT45DB_CS; //CS
	
	AT45_RST(0) ;
	AT45_RST(0) ;
	AT45_RST(0) ;
	AT45_RST(0) ;
	
	 _delay_ms(50);
	AT45_RST(1) ;
		 _delay_ms(50);
	AT45_CS(1);
	/*init mspi in mode3, at chip select pin 3 and max baud rate*/
	//SSP0Init();

	while (id != 0x1F) {
		AT45_CS(0);
		src_addr[0] = 0x9F;
		src_addr[1] = 0x00;
		dest_addr[0] = 0;
		dest_addr[1] = 0;
		SSPTrans(0,(uint8_t *)src_addr,(uint8_t *)dest_addr,2);
		//SSPSend(0,(uint8_t *)src_addr,1);
		//SSPReceive(0,(uint8_t *)dest_addr,1);
		id = dest_addr[1];
		AT45_CS(1);
		_delay_ms(10);
		if (i++ > 250) {
			return -1;
		}
	}
	return id;

}

void at45db_erase_chip(void) {
	/*chip erase command consists of 4 byte*/
	uint8_t cmd[4] = { 0xC7, 0x94, 0x80, 0x9A };
	at45db_write_cmd(&cmd[0]);
	AT45_CS(1);
	/*wait until AT45DB161 is ready again*/
	AT45_CS(0);
	at45db_busy_wait();
	AT45_CS(1);
}

void at45db_erase_block(uint16_t addr) {
	/*block erase command consists of 4 byte*/
	uint8_t cmd[4]; //= { AT45DB_BLOCK_ERASE, (uint8_t) (addr >> 3),
			//(uint8_t) (addr << 5), 0x00 };
			cmd[0] = AT45DB_BLOCK_ERASE;
			cmd[1] = (uint8_t) (addr >> 3);
			cmd[2] = (uint8_t) (addr << 5);
			cmd[3] = 0x00;
	at45db_write_cmd(&cmd[0]);
	AT45_CS(1);
	/*wait until AT45DB161 is ready again*/
	AT45_CS(0);
	at45db_busy_wait();
	AT45_CS(1);
}

void at45db_erase_page(uint16_t addr) {
	/*block erase command consists of 4 byte*/
	uint8_t cmd[4] ;//= { AT45DB_PAGE_ERASE, (uint8_t) (addr >> 6),
			//(uint8_t) (addr << 2), 0x00 };
		
			cmd[0] = AT45DB_PAGE_ERASE;
			cmd[1] = (uint8_t) (addr >> 6);
			cmd[2] = (uint8_t) (addr << 2);
			cmd[3] = 0x00;
	at45db_write_cmd(&cmd[0]);
	AT45_CS(1);
	/*wait until AT45DB161 is ready again*/
	AT45_CS(0);
	at45db_busy_wait();
	AT45_CS(1);
}

void at45db_write_buffer(uint16_t addr, uint8_t *buffer, uint16_t bytes) {
	uint16_t i;
	/*block erase command consists of 4 byte*/
	uint8_t cmd[4];// = { buffer_mgr.buffer_addr[buffer_mgr.active_buffer], 0x00,
		//at45db_busy_wait();
			//(uint8_t) (addr >> 8), (uint8_t) (addr) };
	cmd[0] = buffer_mgr.buffer_addr[buffer_mgr.active_buffer];
	cmd[1] = 0x00;
	cmd[2] = (uint8_t) (addr >> 8);
	cmd[3] = (uint8_t) (addr) ;

	at45db_write_cmd(&cmd[0]);
	src_addr[0] = 0;
	for (i = 0; i < bytes; i++) {
		src_addr[0] = *(buffer+i);
		
		SSPSend(0,(uint8_t *)src_addr,1);
	}

	AT45_CS(1);
}

void at45db_buffer_to_page(uint16_t addr) {
	/*write active buffer to page command consists of 4 byte*/
	uint8_t cmd[4] ;//= { buffer_mgr.buf_to_page_addr[buffer_mgr.active_buffer],
	//(uint8_t) (addr >> 6), (uint8_t) (addr << 2), 0x00 };
	/*wait until AT45DB161 is ready again*/
	
	at45db_busy_wait();

	cmd[0] =  buffer_mgr.buf_to_page_addr[buffer_mgr.active_buffer];
	cmd[1] = (uint8_t) (addr >> 6);
	cmd[2] = (uint8_t) (addr << 2);
	cmd[3] = (uint8_t) 0x00 ;
	at45db_write_cmd(&cmd[0]);
	AT45_CS(1);
	/* switch active buffer to allow the other one to be written,
	 * while these buffer is copied to the Flash EEPROM page*/
	buffer_mgr.active_buffer ^= 1;
}

void at45db_read_page_buffered(uint16_t p_addr, uint16_t b_addr,
		uint8_t *buffer, uint16_t bytes) {
	/*wait until AT45DB161 is ready again*/
	at45db_busy_wait();
	at45db_page_to_buf(p_addr);
	at45db_read_buffer(b_addr, buffer, bytes);
}

void at45db_read_page_bypassed(uint16_t p_addr, uint16_t b_addr,
		uint8_t *buffer, uint16_t bytes) {
	uint16_t i;
	/*wait until AT45DB161 is ready again*/
	uint8_t cmd[4]; //= { AT45DB_PAGE_READ, (uint8_t) (p_addr >> 6),
	//(((uint8_t) (p_addr << 2)) & 0xFC) | ((uint8_t) (b_addr >> 8)),
	//(uint8_t) (b_addr) };
	at45db_busy_wait();
	/* read bytes directly from page command consists of 4 cmd bytes and
	 * 4 don't care */

	cmd[0] =  AT45DB_PAGE_READ;
	cmd[1] = (uint8_t) (p_addr >> 6);
	cmd[2] = (((uint8_t) (p_addr << 2)) & 0xFC) | ((uint8_t) ((b_addr >> 8) & 0x3)); //chang to fe for 9 byte address
	cmd[3] = (uint8_t) (b_addr)  ;
			
	at45db_write_cmd(&cmd[0]);
	for (i = 0; i < 4; i++) {
		src_addr[0] = 0;
		SSPSend(0,(uint8_t *)src_addr,1);
	}
	/*now the data bytes can be received*/
	for (i = 0; i < bytes; i++) {
		dest_addr[0] = 0;
		SSPTrans(0,(uint8_t *)src_addr,(uint8_t *)dest_addr,1);
		*(buffer+i) = (dest_addr[0]);
		
		
	}
	AT45_CS(1);
}

void at45db_page_to_buf(uint16_t addr) {

	/*write active buffer to page command consists of 4 byte*/
	uint8_t cmd[4] ;//= { AT45DB_PAGE_TO_BUF, (uint8_t) (addr >> 6),
			//(uint8_t) (addr << 2), 0x00 };
	cmd[0] =  AT45DB_PAGE_TO_BUF;
	cmd[1] = (uint8_t) (addr >> 6);
	cmd[2] = (uint8_t) (addr << 2);
	cmd[3] = (uint8_t) 0x00 ;
	at45db_write_cmd(&cmd[0]);
	AT45_CS(1);
	/* switch active buffer to allow the other one to be written,
	 * while these buffer is copied to the Flash EEPROM page*/
	//buffer_mgr.active_buffer ^= 1;
	at45db_busy_wait();

}

void at45db_read_buffer(uint8_t b_addr, uint8_t *buffer, uint16_t bytes) {
	uint16_t i;
	uint8_t cmd[4] ;//= { AT45DB_READ_BUFFER, 0x00, (uint8_t) (b_addr >> 8),
			//(uint8_t) (b_addr) };
	cmd[0] = AT45DB_READ_BUFFER;
	cmd[1] = 0x00;
	cmd[2] = (uint8_t) (b_addr >> 8);
	cmd[3] = (uint8_t) (b_addr)  ;
	at45db_busy_wait();
	at45db_write_cmd(&cmd[0]);
		src_addr[0] = 0;
		SSPSend(0,(uint8_t *)src_addr,1);
	

	for (i = 0; i < bytes; i++) {
		dest_addr[0] = 0;
		SSPReceive(0,(uint8_t *)dest_addr,1);
		*buffer++ = dest_addr[0];
		
	}
	AT45_CS(1);
}

void at45db_write_cmd(uint8_t *cmd) {
	uint8_t i;
	AT45_CS(0);
	for (i = 0; i < 4; i++) {
		src_addr[0] = *cmd++;
		SSPSend(0,(uint8_t *)src_addr,1);
		
	}
}

void at45db_busy_wait(void) {
	src_addr[0] = AT45DB_STATUS_REG;
	dest_addr[0] = 0;
	dest_addr[1] = 0;
	while ((dest_addr[1] >> 7) != 0x01) {
		dest_addr[0] = 0;	
	  dest_addr[1] = 0;	
		AT45_CS(0);
		SSPTrans(0,(uint8_t *)src_addr,(uint8_t *)dest_addr,3);
			AT45_CS(1);
	}
}

void Page_Program_through_Buffer(uint16_t page,uint8_t *buffer,uint16_t bytes)
{

	
	uint16_t i;
	/*block erase command consists of 4 byte*/
	uint8_t cmd[4];// = { buffer_mgr.buffer_addr[buffer_mgr.active_buffer], 0x00,
		//at45db_busy_wait();
			//(uint8_t) (addr >> 8), (uint8_t) (addr) };
	at45db_busy_wait();
	
	cmd[0] = 0x82;
	cmd[1] = (uint8_t) (page >> 6);
	cmd[2] = (uint8_t) (page << 2);
	cmd[3] = (uint8_t) 0x00 ;

	at45db_write_cmd(&cmd[0]);
	src_addr[0] = 0;
	for (i = 0; i < bytes; i++) {
		src_addr[0] = *(buffer+i);
		
		SSPSend(0,(uint8_t *)src_addr,1);
	}
				AT45_CS(1);
	
}

void _delay_ms(uint16_t delay)
{
	uint32_t i;

	for (i = (SystemCoreClock/1000) * delay; i != 0; i-- );


}
