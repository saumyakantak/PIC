#include "p18f46k22.h"
//#include "delays.h"
#include "config.h"
#include "keypad.h"
#include "param.h"
#include "datatypes.h"
#include "DOT_MARKER.h "
#include"serial.h"
#include "lcd.h"


void MANUL_CHK()
{						unsigned int count1=0,SW_P=0;			
						Delay_ms(2); 
						RCSTA=0x90;	
						TXSTA=0x20;
						TXSTAbits.TXEN=1;
						TRISCbits.RC6=0;
						SPBRG=23;
						RCSTAbits.SPEN=1;
						Delay_ms(2); 
						TXREG=7;
						while(PIR1bits.TXIF==0);	 
						c_wr(0x01);
						Delay_ms(2);
						c_wr(0x80); 
						Delay_ms(50);	
						d_wr('M'); d_wr('A'); d_wr('N');d_wr('U'); d_wr('A'); d_wr('L'); d_wr('L'); d_wr('Y'); d_wr(' ');
						d_wr('C'); d_wr('H'); d_wr('E');d_wr('C'); d_wr('K'); d_wr(' ');
						c_wr(0xC0);
						d_wr('T');d_wr('U');d_wr('B');d_wr('E');d_wr(' ');d_wr('S');d_wr('W');d_wr('I');d_wr('T');d_wr('C');d_wr('H');d_wr(' ');d_wr(' ');d_wr(' ');
						c_wr(0x90); 
						d_wr('P');d_wr('R');d_wr('E');d_wr('S');d_wr('S');d_wr(' ');d_wr('L');d_wr('E');d_wr('D');d_wr(' ');d_wr('S');d_wr('W');      //d_wr('E');d_wr('S');//d_wr(' ');
						c_wr(0xD0);
						d_wr('T'); d_wr('E');d_wr('S');d_wr('T');d_wr(' ');d_wr('T');d_wr('I');d_wr('M');d_wr('E');d_wr(':');
						for(count1=1;count1<5;count1++)
						{
						c_wr(0xDA);
						lcd_num_display(count1);
						 Delay_ms(2500);
						}
}
void m24()
{
unsigned int count1=0,SW_P=0;			
Delay_ms(2); 
RCSTA=0x90;	
TXSTA=0x20;
TXSTAbits.TXEN=1;
TRISCbits.RC6=0;
SPBRG=23;
RCSTAbits.SPEN=1;
Delay_ms(2); 
TXREG=8;
while(PIR1bits.TXIF==0);	 
c_wr(0x01);
Delay_ms(2);
c_wr(0x80); 
Delay_ms(50);	
d_wr('M'); d_wr('A'); d_wr('N');d_wr('U'); d_wr('A'); d_wr('L'); d_wr('L'); d_wr('Y'); d_wr(' ');
d_wr('C'); d_wr('H'); d_wr('E');d_wr('C'); d_wr('K'); d_wr(' ');
c_wr(0xC0);
d_wr('T');d_wr('U');d_wr('B');d_wr('E');d_wr(' ');d_wr('S');d_wr('W');d_wr('I');d_wr('T');d_wr('C');d_wr('H');d_wr(' ');d_wr(' ');d_wr(' ');
c_wr(0x90); 
d_wr('P');d_wr('R');d_wr('E');d_wr('S');d_wr('S');d_wr(' ');d_wr('L');d_wr('E');d_wr('D');d_wr(' ');d_wr('S');d_wr('W');      //d_wr('E');d_wr('S');//d_wr(' ');
c_wr(0xD0);
d_wr('T'); d_wr('E');d_wr('S');d_wr('T');d_wr(' ');d_wr('T');d_wr('I');d_wr('M');d_wr('E');d_wr(':');
for(count1=1;count1<5;count1++)
{
c_wr(0xDA);
lcd_num_display(count1);
Delay_ms(2500);
}
}