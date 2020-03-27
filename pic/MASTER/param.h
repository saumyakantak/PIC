 #ifndef __EEPROM_H
 #define __EEPROM_H
 
 
 #include "datatypes.h"

 
 BYTE EEpromGet(UWORD addr);
 void EEpromPut(UWORD addr, BYTE data);
 UBYTE EEpromRead(UBYTE *data,UWORD addr, UWORD len);
 UBYTE EEpromWrite(UBYTE *data,UWORD addr,UWORD len);
 UBYTE EEpromClear(UBYTE *data,UWORD addr, UWORD len);
 
 #endif //__EEPROM_H
