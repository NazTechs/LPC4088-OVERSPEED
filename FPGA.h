/*****************************************************************************
 *  Soheil Nazari. GENERAL FPGA FUNCTION   +989122939002
 *****************************************************************************
 * FileName:        FPGA.h
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
 
 #ifndef _FPGA_H

	#define _FPGA_H
 
 #include "type.h"
 #include <LPC407x_8x_177x_8x.h>	

 
 
 

void Fpga_init(void);
void  Fpga_speed_init(uint8_t add,uint16_t hiLimit , uint16_t loLimit ,uint8_t nPulse , uint8_t CnvSpeed); 													
float Fpga_readSp (uint8_t add,uint8_t nPulse);				
float Fpga_readSpTRM (uint8_t add,uint8_t nPulse);	
void Fpga_write_add(uint8_t data, uint8_t add); 
uint8_t Fpga_Trip(uint8_t state);

/************************************************
 * @NAME
 * @PARAM
 * @RETURN
 *
 * @DISC
 *
 * @AUTHOR
 * @REV
 * @DATE
 ***********************************************/
uint8_t Fpga_set_pwm(uint16_t pwm_set,uint8_t add);

uint8_t Fpga_read_add(uint8_t add);

#endif
