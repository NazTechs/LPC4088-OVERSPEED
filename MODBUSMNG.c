/*****************************************************************************
 *  Soheil Nazari. _MODBUS__C FUNCTION   +989122939002
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

#include "MODBUSMNG.h"


extern uint8_t UART1Buffer[BUFSIZE];
extern uint32_t UART1Count;
extern uint8_t UART1LINE;

uint8_t errCounter = 0;

uint8_t modbusAdd = 0;

/**********************LRC GENERATE STRING******************/
uint8_t LRC_CALC_STRING(uint8_t size, char *buf) {
	uint8_t databyte[10] = { 0 };
	uint8_t i;
	uint8_t LRC_TMP = 0;
	char tmpstr[3];
	tmpstr[2] = '\0';
	if (*buf != ':')
		return 0;
	for (i = 0; i < (size - 1) / 2; i++) {
		tmpstr[0] = *(buf + 2 * i + 1);
		tmpstr[1] = *(buf + 2 * i + 2);
		databyte[i] = (uint8_t) strtol(tmpstr, NULL, 16);

	}
	for (i = 0; i < (size - 1) / 2; i++) {
		//LRC_TMP ^= databyte[i];
		LRC_TMP = LRC_TMP + databyte[i];
	}
	LRC_TMP = ~LRC_TMP + 1;
	//LRC_TMP ^= 0xFF;
	//LRC_TMP++;

	return (LRC_TMP);

}
void initModbus(uint32_t buadRate, uint8_t add) {
	UART1_Init(buadRate);
	modbusAdd = add;
	LPC_GPIO3->DIR |= (1 << 18);
	LPC_GPIO3->CLR = (1 << 18);
}
int anaModbus(void) {
	uint8_t lenght;
	uint8_t crc;
	uint8_t scrc;
	uint8_t packetAdd = 0;
	uint8_t comm = 0;
	uint8_t writeRead = 0;
	char tmpstr[3];
	tmpstr[2] = '\0';
	if (UART1Buffer[0] != ':') {
		LCDEBUG3("ERROR %d", errCounter++);
		return -2;
	}
	lenght = strlen(UART1Buffer);
	if (lenght > 7) {
		tmpstr[0] = UART1Buffer[lenght - 4];
		tmpstr[1] = UART1Buffer[lenght - 3];
		scrc = strtol(tmpstr, NULL, 16);
		crc = LRC_CALC_STRING(lenght - 4, UART1Buffer);
		if (crc != scrc)
			return -3;
	}
	tmpstr[0] = UART1Buffer[1];
	tmpstr[1] = UART1Buffer[2];
	packetAdd = strtol(tmpstr, NULL, 16);
	if (packetAdd != modbusAdd)
		return -4;
	tmpstr[0] = UART1Buffer[3];
	tmpstr[1] = UART1Buffer[4];
	comm = strtol(tmpstr, NULL, 16);
	//LCDEBUG3("E=%d L=%d c=%02X S=%02X A=%02X C=%02X S=%s" , errCounter,lenght,crc,scrc,packetAdd,comm,UART1Buffer);
	switch (comm) {
	case 03:
		writeRead = 1;
		return 1;
		break;
	case 04:
		writeRead = 0;
		return 0;
		break;
	default:
		return -5;
		break;
	}
	return -1;
}
;

int readModbus() {

	uint8_t buff[10];
	uint8_t size;
	uint16_t readadd = 0;

//	uint32_t tmpdata32 = 0;
//	int32_t  tmpsdata32 = 0;

	uint8_t tmpdata8 = 0;
	int8_t  tmpsdata8 = 0;

	uint16_t tmpdata16 = 0;
	int16_t  tmpsdata16 = 0;
	char tmpstr[5];
	tmpstr[4] = '\0';
	tmpstr[0] = UART1Buffer[5];
	tmpstr[1] = UART1Buffer[6];
	tmpstr[2] = UART1Buffer[7];
	tmpstr[3] = UART1Buffer[8];
	readadd = strtol(tmpstr, NULL, 16);
	
	readadd = 1;
	
	switch (readadd) {
	case 0x0001:
		size = 2;
	if (memory1.speed < 1000.0)
		tmpdata16 = lroundl(memory1.speed/10.0);
	else
		tmpdata16 = floorf(memory1.speed/10.0);
		buff[0] = (tmpdata16 & 0x0000FF00) >> 8;
		buff[1] = (tmpdata16 & 0x000000FF);
		break;
	case 0x0002 :
		size = 2;
		tmpsdata16 = memory1.accel;
		buff[0] = (tmpsdata16 & 0x0000FF00) >> 8;
		buff[1] = (tmpsdata16 & 0x000000FF);
		break;
	case 0x0005 :
			size = 1;
			tmpdata8 = 0x02;//memory1.state;
			buff[0] = tmpdata8;
	case 0x0006 :
		size = 2;
		tmpsdata16 = memory1.overspeedset;
		buff[0] = (tmpsdata16 & 0x0000FF00) >> 8;
		buff[1] = (tmpsdata16 & 0x000000FF);
		break;
	case 0x000A :
		size = 2;
		tmpsdata16 = memory1.analog1_output;
		buff[0] = (tmpsdata16 & 0x0000FF00) >> 8;
		buff[1] = (tmpsdata16 & 0x000000FF);
		break;
	default:
		size = 0;
		break;
	}
	if (size > 0) {
		char m_str[20];
		char t_str[20];
		int i;
		uint8_t LRC_TMP = 0;
		m_str[0] = '\0';
		for (i = 0; i < size; i++) {
			sprintf(m_str, "%s%02X", m_str, buff[i]);
		}
		sprintf(t_str, ":%02X04%02X%s", modbusAdd, size, m_str);
		LRC_TMP = LRC_CALC_STRING(strlen(t_str), &t_str[0]);
		sprintf(m_str, "%s%02X\r\n", t_str, LRC_TMP);
		LCDEBUG3("%s len = %d", m_str, strlen(t_str));
		LPC_GPIO3->SET = (1 << 18);
		UART1_PrintString(m_str);
		while ((LPC_UART1->LSR & 0x40) == 0)
			;
		LPC_GPIO3->CLR = (1 << 18);
	}
return 0;
}
void chkModbus(void) {

	if (UART1LINE == 1) {

		int8_t analyse = -10;
		analyse = anaModbus();
		if (analyse == 0)
			readModbus();

		LCDEBUG3("%s    LENGHT %d", UART1Buffer , strlen(UART1Buffer));
		//LCDEBUG3("d = %05d R= %05d",memory1.speed/10.0,roundf(memory1.speed/10.0));
		UART1LINE = 0;

	}
	else{
		
		//	readModbus();
    //LCDEBUG3("%c    LENGHT %d", UART1_Getchar() , strlen(UART1Buffer));		
			LCDEBUG3("NO LINE");
		
	
	}
}
