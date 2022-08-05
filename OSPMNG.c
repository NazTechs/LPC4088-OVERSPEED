/*****************************************************************************
 *  Soheil Nazari. _OSPMNG__C    +989122939002
 *****************************************************************************
 * @FileName:        OSPMNG.h
 * @Dependencies:
 * @Processor:       LPC4088
 * @Compiler:
 * @Linker:
 * @Company:			TADBIR
 *
 * @Author Soheil Nazari              Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SOHEIL NAZARI	    1/18/2017
 *****************************************************************************/

#include "OSPMNG.h"
#include "timer.h"
#include <math.h>
float prv_speed[2];
uint8_t acc_state = 0;
float speed[1000];
uint16_t speed_counter = 0;

uint8_t osp_init() {
	Fpga_init();
	//SPEED SET
	Fpga_speed_init(0x40, 2300, 1700, 12, 8); // CHANNEL 1 SET
	Fpga_speed_init(0x50, 2300, 1700, 120, 1); // CHANNEL 2 SET

	//Accel int
	LPC_SC->PCONP |= (1 << 23);
	LPC_TIM3->TCR = 0x02; /* reset timer */
	LPC_TIM3->PR = 0x00; /* set prescaler to zero */
	LPC_TIM3->TCR = 0x01; /* start timer */

	return 0;

}

uint8_t analog1Update()
{
	
	uint16_t pwm0=20140.0;
	int i;
	uint16_t rpmUpperPos = 0;
	int32_t deltaRpm = 0;
	int32_t deltaDigit = 0;
	float slip;

	if (an01UpdateFlag == 1)
	{
		uint32_t dummySerial;
		an01UpdateFlag = 0;
		getCalbAn(an01AppliedTable,&dummySerial,AN1_ADD_PAGE);
	}
	/**
	*	@SearchForRPM
	*
	**/


		for(i = 8; i <= 13; i++)
			if (an01AppliedTable[i] > memory1.speed){
						rpmUpperPos = i;
						break;
					}
		if (rpmUpperPos == 0)
			return 1;

		deltaRpm = an01AppliedTable[rpmUpperPos] - an01AppliedTable[rpmUpperPos - 1];
		deltaDigit = an01AppliedTable[rpmUpperPos + 7] - an01AppliedTable[rpmUpperPos - 1 + 7];
		if (deltaRpm == 0)
		{
			Fpga_write_add((an01AppliedTable[rpmUpperPos - 1 + 7]) & 0xFF , 0x11);//10140
			Fpga_write_add(an01AppliedTable[rpmUpperPos - 1 + 7] >> 8 , 0x12);
			Fpga_write_add(0x03 , 0x13);
			Fpga_write_add(0x00 , 0x13);
			return 0;
		}
		slip = ((float)deltaDigit)/((float)deltaRpm);
		pwm0 = (uint16_t)(slip * ( memory1.speed - ((float)an01AppliedTable[rpmUpperPos - 1])) + an01AppliedTable[rpmUpperPos - 1 + 7]);
			Fpga_write_add((pwm0) & 0xFF , 0x11);//10140
			Fpga_write_add(pwm0 >> 8 , 0x12);
			Fpga_write_add(0x03 , 0x13);
			Fpga_write_add(0x00 , 0x13);



	memory1.analog1_output = pwm0;

  return 0;
}

uint8_t analog2Update()
{
	uint16_t pwm1=20140.0;
	int i;
	uint16_t rpmUpperPos = 0;
	int32_t deltaRpm = 0;
	int32_t deltaDigit = 0;
	float slip;

	if (an02UpdateFlag == 1)
	{
		uint32_t dummySerial;
		an02UpdateFlag = 0;
		getCalbAn(an02AppliedTable,&dummySerial,AN2_ADD_PAGE);
	}
	/**
	*	@SearchForRPM
	*
	**/


		for(i = 8; i <= 13; i++)
			if (an02AppliedTable[i] > memory1.speed){
						rpmUpperPos = i;
						break;
					}
		if (rpmUpperPos == 0)
			return 1;

		deltaRpm = an02AppliedTable[rpmUpperPos] - an02AppliedTable[rpmUpperPos - 1];
		deltaDigit = an02AppliedTable[rpmUpperPos + 7] - an02AppliedTable[rpmUpperPos - 1 + 7];
		if (deltaRpm == 0)
		{
			Fpga_write_add((an02AppliedTable[rpmUpperPos - 1 + 7]) & 0xFF , 0x31);//10140
			Fpga_write_add(an02AppliedTable[rpmUpperPos - 1 + 7] >> 8 , 0x32);
			Fpga_write_add(0x03 , 0x33);
			Fpga_write_add(0x00 , 0x33);
			return 0;
		}
		slip = ((float)deltaDigit)/((float)deltaRpm);
		pwm1 = (uint16_t)(slip * ( memory1.speed - ((float)an02AppliedTable[rpmUpperPos - 1])) + an02AppliedTable[rpmUpperPos - 1 + 7]);
			Fpga_write_add((pwm1) & 0xFF , 0x31);//10140
			Fpga_write_add(pwm1 >> 8 , 0x32);
			Fpga_write_add(0x03 , 0x33);
			Fpga_write_add(0x00 , 0x33);


  return 0;
}

uint8_t speedUpdate() {
	
	int i ;
	double avspeed = 0.0;
	const int ACGRATE = 100;
	if (memory1.speed  < 25000)
	speed[speed_counter] = Fpga_readSp(0x40, 2);
	else
	speed[speed_counter] = Fpga_readSp(0x50, 20);
	speed_counter++;
	for ( i = 0 ; i < ACGRATE ; i++)
	{
		avspeed = speed[i] + avspeed;
		
	}
	avspeed = avspeed/(float)ACGRATE;
	if (speed_counter >= ACGRATE )
		speed_counter = 0;
	
	memory1.speed = avspeed; 
	
	//an0
	/*{
		uint16_t pwm0=0,pwm1=0;
		if (avspeed < 15000.0)		
			pwm0 = (uint16_t)((avspeed * 2.535) + 10140.0);
		else
				pwm0 = 49100;
		if (avspeed > 15000.0)
			pwm1 = (uint16_t)((avspeed-15000.0) * 2.26996 + 10140.0);//2.29176
		else 
			pwm1 = 10140;
									Fpga_write_add((pwm0) & 0xFF , 0x11);//10140
								  Fpga_write_add(pwm0 >> 8 , 0x12);
								  Fpga_write_add(0x03 , 0x13);
								  Fpga_write_add(0x00 , 0x13);
	//an1		
			Fpga_write_add((pwm1) & 0xFF , 0x31);
								  Fpga_write_add(pwm1 >> 8 , 0x32);
								  Fpga_write_add(0x03 , 0x33);
								  Fpga_write_add(0x00 , 0x33);
		
	}*/
		//memory1.speed = Fpga_readSp(0x50, 8);

	return 0;

}

uint8_t micreoSpeedUpdate()
{
	
	
}

uint8_t accUpdate() {
	uint32_t time = 0;
	float acce = 0.0; 
	if (acc_state == 0) {
		prv_speed[0] = memory1.speed;
		LPC_TIM3->TC = 0;
		acc_state++;
		return 1;
	}
	
	if (acc_state == 1) {
		if (LPC_TIM3->TC > 5000000)
		{
			prv_speed[1] = memory1.speed;
			time = LPC_TIM3->TC;
			acc_state++;
		}
		else
			return 0;
	/*	if (memory1.speed != prv_speed[0]) {
			prv_speed[1] = memory1.speed;
			acc_state++;
		} else if (LPC_TIM3->TC > 72000000) {
			prv_speed[1] = prv_speed[0];
			time = 1;
			acc_state++;
		} */
	}
	if (acc_state == 2) {
		acc_state = 0;
		acce = (prv_speed[1] - prv_speed[0])
				/ (((float) time * 2.0) / ((float) SystemCoreClock));
		memory1.accel = acce;
		return 0;
	}
	return 0;
}

void chkOsp() {
	if (memory1.speed > memory1.overspeedset) {
		Fpga_Trip(1);
		memory1.OverspeedTrip = 1;
		memory1.state = 2;
	}
	else if(memory1.speed >memory1.alarmoverspeedsetpoint && memory1.state != 2){
		memory1.state = 1;
		memory1.alarmoverspeed = 1;
	}
	if(abs((int)memory1.accel) > memory1.overaccellset){
		Fpga_Trip(1);
		memory1.OveraccelTrip = 1;
		memory1.state = 2;
	}
	if (memory1.PowerupTrip == 1){
		memory1.state = 2;
		Fpga_Trip(1);
	}
	if (memory1.speed < memory1.speedfailsetpoint){
		Fpga_Trip(1);
		memory1.SpeedFailTrip = 1;
		memory1.state = 2;
	}
	if(!(memory1.OverspeedTrip || memory1.OveraccelTrip || memory1.PowerupTrip
			|| memory1.SpeedFailTrip))
	{/**@ALRMNOTSET**/
		memory1.state = 0;
		Fpga_Trip(0);
	}

}
uint32_t configCRC()
{
	
	
	
}

uint8_t ospUpdate() {

	speedUpdate();
	accUpdate();
	chkOsp();
	analog1Update();
	analog2Update();
	{
									uint8_t s[4] = {0};
									s[0] = Fpga_read_add(0x40);
									s[1] = Fpga_read_add(0x41);
									s[2] = Fpga_read_add(0x42);
									s[3] = Fpga_read_add(0x43);
		
			LCDEBUG2("ADD STA_REG = %02x s=%08x ANO=%04x", Fpga_read_add(0x44),((s[0] << 24) + (s[1] << 16) + (s[2] << 8) + s[3]),memory1.analog1_output);
	}
	return 0;
}
