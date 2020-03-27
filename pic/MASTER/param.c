#include "p18f46k22.h"
#include "param.h"
#include "keypad.h" 
#include "datatypes.h"

 BYTE EEpromGet(UWORD addr) 
 { 
 	volatile BYTE eepTemp; 
 	UWORDbytes temp;
 	temp.data=addr;
 	EEADRH = temp.high;
 	EEADR = temp.low; 
 	EECON1bits.EEPGD = 0; 
 	EECON1bits.CFGS = 0; 
 	EECON1bits.RD = 1; 
 	eepTemp = EEDATA; 
 	return eepTemp; 
 } 
 

 void EEpromPut(UWORD addr, BYTE data) 
 { 
 	UWORDbytes temp;
 	temp.data=addr;		 //could use cast instead
 	EEADRH = temp.high;
 	EEADR = temp.low; 
 	EEDATA = data; 
 	EECON1bits.EEPGD = 0; 
 	EECON1bits.CFGS = 0; 
 	EECON1bits.WREN = 1; 
 
INTCONbits.GIE=0; 
 	_asm
 	MOVLW 0x55
 	MOVWF EECON2,0
 	MOVLW 0xAA
 	MOVWF EECON2,0
 	_endasm
 	EECON1bits.WR=1;
 	while (EECON1bits.WR == 1);
 INTCONbits.GIE=1; 
 
 	EECON1bits.WREN = 0; 
 } 
 

 UBYTE EEpromWrite(UBYTE *data,UWORD addr, UWORD len)
 {
 	UWORD i;
 
 	for(i=0; i<len; i++)
 	{
 		EEpromPut(addr++,data[i]);
 	}
 	return i;
 }

 UBYTE EEpromRead(UBYTE *data,UWORD addr, UWORD len)
 {
 	UWORD i;
 
 	//printf("eeprom read %uhd\n\r",len);
 	for(i=0; i<len; i++)
 	{
 		data[i]=EEpromGet(addr++);
 	
 	}
 	return i;
 }
 
 UBYTE EEpromClear(UBYTE *data,UWORD addr, UWORD len)
{ 
 unsigned int  i; 
 		for(i=0; i<len; i++)
 
 	{
	 EEpromPut(addr++,0);

  	}
 	return i;	
}



 

