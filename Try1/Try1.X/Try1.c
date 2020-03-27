#include <xc.h>
#include <p18F46k22.h>
#pragma config LVP = OFF
#pragma config PBADEN = OFF

#define led PORTBbits.RB0
int x=0;
void delay (unsigned int ms)
{
	unsigned int i,j;
	for (i = 0;i<ms;++i)
		for (j = 0;j<127;++j);
}
void delayms(unsigned int b)
{
int sp,sj;

for(sp=0;sp<b;sp++)
{
for(sj=0;sj<7;sj++)
{
}
}
}
void send_charCom2(unsigned char x)                                          
{
   TXREG2 = x;
   while(!TXSTA2bits.TRMT);
}
void UART_Init2()
{

        TXSTA2bits.TXEN =1;
		RCSTA2bits.SPEN =1;	
		TRISDbits.TRISD7  = 1; 
        TRISDbits.TRISD6  = 0; 
       	TXSTA2 = 0b00100000;
		RCSTA2 = 0b10010000;
		BAUDCON2 = 0b00000000;
		SPBRG2=25;	
}
void voltage_read()
{
	TRISCbits.TRISC3=1;
	ANSELCbits.ANSC3=1;
	ADCON2=0xB8;
	ADCON0=0x3F;
	//ADCON1=0xce;
	ADCON1=0x8E;
	delayms(1);
  ADCON0bits.GO=1;
  while(ADCON0bits.DONE==1);
  	x= (256*ADRESH) + ADRESL;
//	x=x/2.04;
//	x=x*10;
//	x=x/1.271;   //X=X/1.261//1.212
//	lcd_num_display(x);
}
void serial_display_mv(unsigned int  ans0)
{

	unsigned int data;
	 data=ans0;
	send_charCom2('0');
	 send_charCom2(data/1000+0x30);
	send_charCom2((data%1000)/100+0x30);
	 send_charCom2((data%100)/10+0x30);
	 send_charCom2((data%10)+0x30);
  
}
void main(void) 
{
    TRISC=0b10010000;        // (rs rw E...RC0,RC1,RC2)( ANALOG CHANNELS RC3 TO RC7( RC3 AS A VOLT ADC)
TRISB=0b00001111;     	// (data PORTD RB4 TO RB7) (SWITCH RB0 TO RB4)
TRISD=0b10111111;       //  ANALOG INPUTS(RD0...RD7)
TRISA=0x11001101; //analog i/p
TRISE=0x07;  //led
ANSELB=0x00;  //SWITCH
ANSELA=0x01;   //ANALOG I/P  (RA0,RA1,RA5)
ANSELD=0X1F;  //ANALOG I/P  (RD0...RD7)
ANSELC=0x00;   //ANALOG I/P (RC3....RC7)
ANSELE=0x03;
ADCON2=0xB8;
TRISEbits.RE2=1;
RCSTA=0x90;
TXSTA=0x20;
TXSTAbits.TXEN=1;
TRISCbits.RC6=0;
SPBRG=23;
RCSTAbits.SPEN=1;
ANSELCbits.ANSC7=0;
PIR3bits.RC2IF==0;
UART_Init2();
	led = 0;
	while (1)
	{
        led=0;
		delay(1000);
        voltage_read();
        serial_display_mv(x);
		led=1;
		delay(1000);
	}
    return;
}



