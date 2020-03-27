#include "p18f46k22.h"
#include "config.h"
#include "delays.h"  //inbuit delay for 1ms
#include "param.h"
#include "datatypes.h"
#include "keypad.h"
#define _XTAL_FREQ 2000000
#define RED  PORTCbits.RC0  //ch14
#define  YELLOW   PORTCbits.RC1//RC6// ch15
#define GREEN   PORTCbits.RC2 //RC7  // ch16
#define BUZZER  PORTCbits.RC3
#define SELECT_KEY PORTDbits.RD5 

extern unsigned char SW2;
extern  signed int count;
extern  signed int count2;
extern unsigned int min_range25;
extern unsigned int final_cheak_tube;


unsigned int counter();
UBYTE EEpromErase(UBYTE *data,UWORD addr, UWORD len);
void tmr_delay( unsigned long int sec_mul);
void NEWHAR ();
void CHKST ();
void initi_Timer0();
void TSTOVR ();
void NG_DISPLAY();
void LH_DISOK();
void RH_DISOK();
void serial_display(unsigned int  ans0);
