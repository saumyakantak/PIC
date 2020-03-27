#include "p18f46k22.h"
//#include"serial.h"

#define LED1 PORTEbits.RE2 


#pragma code hiprio_int=0x0008
#define KEY_1  0x01              //up        RD4
#define KEY_2  0x02            //crscr       RD5
#define KEY_3  0x04           //menu         RD6
#define KEY_4  0x08           //down         RD7


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
while(1)
		{  LED1=1;
			LED1=0;	
		}
   
}     
 

  //      ADCON0=0x00; //ch1  RA0
  //      ADCON1=0x05; 
  //      ADCON0=0x01;       
      
    //    ADCON0=0x03;

	//	while((ADCON0&0x02)!=0x00);
      //  {
       // }
        // k1=ADRESH;
         //m1=ADRESL;
         //k1=k1<<8;
        // m1=k1|m1;
            
		//adc_val1_mv =m1*4.508;
           
 //ch2//
        
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


void serial(unsigned int x)	
{
TXREG2=x;

while(PIR3bits.TX2IF==0);

}

//-----------------------------------------------------------------------------------------------------------------------
//**********************************************************************************************************************
void voltage_read()
{
//	TRISCbits.TRISC3=1;
//	ANSELCbits.ANSC3=1;
//	ADCON2=0xB8;
//	ADCON0=0x3F;
//	//ADCON1=0xce;
//	ADCON1=0x8E;
//	delayms(1);
//  ADCON0bits.GO=1;
//  while(ADCON0bits.DONE==1);
//  	x= (256*ADRESH) + ADRESL;
//	x=x/2.04;
//	x=x*10;
//	x=x/1.271;   //X=X/1.261//1.212
//	lcd_num_display(x);
}