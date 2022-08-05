/*****************************************************************************
 *  Soheil Nazari. _MAINMENU__C FUNCTION   +989122939002
 *****************************************************************************
 * FileName:        LCD_FUNC.h
 * Dependencies:    
 * Processor:       LPC4088
 * Compiler:       	
 * Linker:         
 * Company:			TADBIR
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    1/10/2017
 *****************************************************************************/
 
 #include "Memory.h"
 
 
 
 
#include <LPC407x_8x_177x_8x.h>





uint16_t an01AppliedTable[21] = {0};
uint16_t an02AppliedTable[21] = {0};

uint8_t an01UpdateFlag = 1;
uint8_t an02UpdateFlag = 1;



/********************** EEPROM FUNCTION ******************/


void int_EEPROM()

	{

			LPC_EEPROM->PWRDWN = 0;

		  LPC_EEPROM->CLKDIV = 319;//SystemCoreClock/375000 - 1;

		  LPC_EEPROM->WSTATE = (2 | (6 << 8) | ( 4 << 16));

	}



	void write_EEPROM (uint16_t addr , uint8_t *buffer , uint8_t bytes)

	{



										int i ;

										LPC_EEPROM ->CMD = 0x03; // write 8 bit data

										LPC_EEPROM ->ADDR = addr;

										for ( i = 0 ; i < bytes ; i ++)

									{

														LPC_EEPROM ->WDATA = *(buffer + i);

									}



											LPC_EEPROM ->ADDR = addr;

											LPC_EEPROM ->CMD = 0x06;

											for (i = 0 ; i < 1000000 ; i++);





	}



	void read_EEPROM (uint16_t addr , uint8_t *buffer , uint8_t bytes)

	{

										int i ;

										LPC_EEPROM ->ADDR = addr;

										LPC_EEPROM ->CMD = 0x008; // read 8 bit data

                    for (i = 0 ; i < 1000000 ; i++);

										for ( i = 0 ; i < bytes ; i ++)

									{

														*(buffer + i) =LPC_EEPROM ->RDATA ;

									}

	}



/************************RAM MEMORY************************************/



/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

 Memory memory1;

/*---------------------------------------------------------------------------------*/


 void MemoryInit(Memory *memory)
{
	/*******************SUMMERY********************************/
	
	memory->accel =  0.0;
	memory->accel1 = 0.0;
	memory->analog1_output = 27020;
	memory->analog1_slip = 40400;
	memory->analog1_start = 10500;
	memory->day = 1;
	memory->hour = 0;
	memory->min = 0;
	memory->mounth = 1;
	memory->overspeedset = 37000;
	memory->sec = 0;
	memory->speed = 0.0;
	memory->speed1 = 0.0;
	memory->speedfailoveride = 1;
	memory->year = 2018;
	
	
	memory->overaccellset = 1000;
	memory->speedfailsetpoint = 5000;
	
	memory->alarmoverspeedsetpoint = 11000;
	memory->alarmoverspeed = 0;

	memory->state = 0; //NORMAL 0 ALARM 1 TRIP 2
	/************************Trip PAGE1*****************************/
	memory->internalFaultTrip = 0;
	memory->internalFaultTripFirstOut = 0;
	memory->PowerupTrip = 1;
	memory->PowerupTripFirstOut = 1;
	memory->ConfigTrip = 0;
	memory->ConfigTripFirstOut = 0;
	memory->ParameterError = 0;
	memory->ParameterErrorFirstOut = 0;
	memory->OverspeedTrip = 0;
	memory->OverspeedTripFirstOut = 0;
	memory->SpeedProbOpenWire = 4;
	memory->SpeedProbOpenWireFirstOut = 4;
	
	
	/************************Trip PAGE2*****************************/
	
	memory->SpeedLostTrip = 0;
	memory->SpeedLostTripFirstOut = 0;
	memory->OveraccelTrip = 0;
	memory->OveraccelTripFirstOut = 0;
	memory->SpeedFailTrip = 0;
	memory->SpeedFailTripFirstOut = 0;
	memory->SpeedFailTimeoutTrip = 0;
	memory->SpeedFailTimeoutTripFirstOut = 0;
	
	
	/*********************ALRM LATCH PAGE1****************************/
	
	memory->InternalFaultAlarm = 0;
	memory->ConfigurationMismatch =0;
	memory->PowerSupply1Fault =0;
	memory->PowerSupply2Fault =0;
	memory->TmpOverspeedSetpointOn =0;
	memory->ManualSimSpeedTest =0;
	

		
	/*********************ALRM LATCH PAGE2****************************/
	
	memory->AutoSimSpeedTest =0;
	memory->PeriodicOvrspdTest =0;
	memory->SpeedLostAlarm =0;
	memory->SpeedFailAlarm =0;

		
}


/**********************************************************************
*
*	@antableFormat	32bit Hashcode 1b c1 36 ed
*									32bit Serial Start from 1000
*									48 byte data
*
*
*
*
**********************************************************************/
#define HASH	0x1bc136fc
#define DATASTARTBYTE	8
#define SERIALSTART		4
uint8_t getCalbAn(uint16_t *anTable,uint32_t *anSerial ,uint8_t anPage){

	uint8_t buff[64];
	uint32_t hash;
	uint8_t i,j;
	uint16_t add = ((uint16_t)anPage) << 6;
	read_EEPROM ( add ,buff, 64);
	/* CHECK hash code */
	hash = buff[0] | (buff[1] << 8)  | (buff[2] << 16) | (buff[3] << 24);
	if (hash != HASH)
			return 1; //unint
	for (i = 0 ; i < 22 ; i++){
		j = DATASTARTBYTE + 2*i;
		anTable[i] = buff[j] | (buff[j+1] << 8);
	}
	{
		j = SERIALSTART;
		*anSerial =  buff[j+3] | (buff[j+2] << 8)  | (buff[j+1] << 16) | (buff[j+0] << 24);
	}

	return 0;

}

uint8_t setCalbAn(uint16_t *anTable,uint8_t anPage){
	uint8_t rbuff[64],wbuff[64];
	uint32_t hash = HASH;
	uint8_t i,j;
	uint16_t add = ((uint16_t)anPage) << 6;
	uint32_t anSerial;

	read_EEPROM ( add ,rbuff, 64);


	wbuff[0] =  hash        & 0xFF;
	wbuff[1] = (hash >> 8)  & 0xFF;
	wbuff[2] = (hash >> 16) & 0xFF;
	wbuff[3] = (hash >> 24) & 0xFF;


	j = SERIALSTART;

	anSerial =  rbuff[j+3] | (rbuff[j+2] << 8)  | (rbuff[j+1] << 16) | (rbuff[j+0] << 24);

	anSerial++;

	wbuff[j + 3] =  anSerial        & 0xFF;
	wbuff[j + 2] = (anSerial >> 8)  & 0xFF;
	wbuff[j + 1] = (anSerial >> 16) & 0xFF;
	wbuff[j + 0] = (anSerial >> 24) & 0xFF;

	j = DATASTARTBYTE;
  for (i = 0 ; i < 7 ; i++){
		j = DATASTARTBYTE + 2 * i;

		wbuff[j]    = i;
		wbuff[j+1]  = 0;

		//anTable[j] = wbuff[j] | (wbuff[j+1] << 8);
	}
	for (i = 7 ; i < 22 ; i++){
		j = DATASTARTBYTE + 2 * i;

		wbuff[j]    = anTable[i] & 0XFF;
		wbuff[j+1]  = (anTable[i] >> 8) & 0xFF;

		//anTable[j] = wbuff[j] | (wbuff[j+1] << 8);
	}


	write_EEPROM ( add ,wbuff, 64);


}
void intCalbAn(uint8_t anPage){

	uint8_t buff[64];
	uint32_t hash = HASH;
	uint8_t i,j;
	uint16_t add = ((uint16_t)anPage) << 6;

	buff[0] =  hash        & 0xFF;
	buff[1] = (hash >> 8)  & 0xFF;
	buff[2] = (hash >> 16) & 0xFF;
	buff[3] = (hash >> 24) & 0xFF;

	j = SERIALSTART;

	buff[j] = 0;
	buff[j + 1] = 0x00;
	buff[j + 2] = 0x03;
	buff[j + 3] = 0xe8;

	write_EEPROM ( add ,buff, 64);



};
