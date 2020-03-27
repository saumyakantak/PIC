#include "p18f46k22.h"
#include "config.h"
//#include "delays.h"  //inbuit delay for 1ms
#include "param.h"
#include "datatypes.h"
#include "keypad.h"
#define _XTAL_FREQ 2000000
#define RED  PORTCbits.RC0  //ch14
#define  YELLOW   PORTAbits.RA4//RC6// ch15
#define GREEN   PORTCbits.RC2 //RC7  // ch16

extern unsigned char SW2;
extern unsigned char HARREJ;
extern  signed int count;
extern  signed int count2;
extern unsigned int min_range25;
extern unsigned int final_cheak_tube;


extern unsigned int red_flag;
extern unsigned int yellow_flag;



unsigned int counter();
UBYTE EEpromErase(UBYTE *data,UWORD addr, UWORD len);
void tmr_delay( unsigned long int sec_mul);
void NEWHAR ();
void CHKST ();
void initi_Timer0();
void TSTOVR ();
void DISOK();
void serial_display(unsigned int  ans0);
