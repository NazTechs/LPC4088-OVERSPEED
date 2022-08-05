/*****************************************************************************
 *  Soheil Nazari. _MEMORY__H FUNCTION   +989122939002
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

#ifndef _MEMORY__H

#define _MEMORY__H

#include "type.h"

/**************************************************************************
*	@localAddress
**************************************************************************/
#define AN1_ADD_PAGE 10
#define AN1_ADD0 (AN1_ADD_PAGE<<6)

#define AN2_ADD_PAGE 11
#define AN2_ADD0 (AN1_ADD_PAGE<<6)
/**********************LOCAL Structure************************************
 *
 *************************************************************************/

typedef struct {
	float speed;
	float accel;
	float speed1;
	float accel1;

	uint8_t state;

	uint16_t overspeedset;
	uint16_t overaccellset;

	uint16_t speedfailsetpoint;
	
	uint8_t speedfailoveride;
	
	uint16_t alarmoverspeedsetpoint;
	uint8_t alarmoverspeed;

	/*******************************************************/
	uint16_t analog1_output;
	uint16_t analog1_slip;
	uint16_t analog1_start;

	/*******************************************************/

	uint8_t day;
	uint8_t mounth;
	uint16_t year;

	uint8_t hour;
	uint8_t min;
	uint8_t sec;

	/**********************TRIPDATA*************************/

	uint8_t internalFaultTrip;
	uint8_t internalFaultTripFirstOut;

	uint8_t PowerupTrip;
	uint8_t PowerupTripFirstOut;

	uint8_t ConfigTrip;
	uint8_t ConfigTripFirstOut;

	uint8_t ParameterError;
	uint8_t ParameterErrorFirstOut;

	uint8_t OverspeedTrip;
	uint8_t OverspeedTripFirstOut;

	uint8_t SpeedProbOpenWire;
	uint8_t SpeedProbOpenWireFirstOut;

	uint8_t SpeedLostTrip;
	uint8_t SpeedLostTripFirstOut;

	uint8_t OveraccelTrip;
	uint8_t OveraccelTripFirstOut;

	uint8_t SpeedFailTrip;
	uint8_t SpeedFailTripFirstOut;

	uint8_t SpeedFailTimeoutTrip;
	uint8_t SpeedFailTimeoutTripFirstOut;

	/*********************ALRM LATCH PAGE1****************************/

	uint8_t InternalFaultAlarm;
	uint8_t ConfigurationMismatch;
	uint8_t PowerSupply1Fault;
	uint8_t PowerSupply2Fault;
	uint8_t TmpOverspeedSetpointOn;
	uint8_t ManualSimSpeedTest;

	/*********************ALRM LATCH PAGE1****************************/
	uint8_t AutoSimSpeedTest;
	uint8_t PeriodicOvrspdTest;
	uint8_t SpeedLostAlarm;
	uint8_t SpeedFailAlarm;

	/********************************MonitorDedicatedDiscreteInputsRender*******************/
	uint8_t StartInput;
	uint8_t ResetInput;
	uint8_t SpeedFailOverideInput;

} Memory;

/**********************LOCAL Variable************************************
 *
 *************************************************************************/
typedef struct {
  uint8_t		columnNum;
  uint8_t   rowNum;
  uint8_t   tableEditMode;
  uint8_t		tableSelItem;
  uint8_t   editMode;
  uint8_t   editModeValueSelected;
	uint16_t	*tableItems;
	uint8_t		*editAbleItem;
	uint32_t	*serialId;
}tableCtrlData;

extern Memory memory1;

void MemoryInit(Memory *memory);


void int_EEPROM();
void write_EEPROM (uint16_t addr , uint8_t *buffer , uint8_t bytes);
void read_EEPROM  (uint16_t addr , uint8_t *buffer , uint8_t bytes);

/**
*
*
**/

extern uint16_t an01AppliedTable[21];
extern uint16_t an02AppliedTable[21];

extern uint8_t an01UpdateFlag;
extern uint8_t an02UpdateFlag;

uint8_t getCalbAn(uint16_t *anTable,uint32_t *anSerial ,uint8_t anPage);
uint8_t setCalbAn(uint16_t *anTable,uint8_t anPage);
void intCalbAn(uint8_t anPage);


#endif
