#include<p18f46k22.h>
#include"serial.h"

//#include <stdio.h>
unsigned char Y;
extern unsigned char volt_flag;

void serial_display_num(unsigned int  ans0)
{

	unsigned int data;
	 data=ans0;
	 send_charCom2(data/1000+0x30);
	send_charCom2((data%1000)/100+0x30);
	 send_charCom2((data%100)/10+0x30);
	 send_charCom2((data%10)+0x30);
  
}

void serial_display(unsigned int  ans0)
{

	unsigned int data;
	 data=ans0;
	 send_charCom2(data/1000+0x30);
	send_charCom2((data%1000)/100+0x30);
	send_charCom2('.');
	 send_charCom2((data%100)/10+0x30);
	 send_charCom2((data%10)+0x30);
  
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
void serial_display_A(unsigned int  ans0)
{	
	
	unsigned int data;
	 data=ans0;
	 send_charCom2(data/1000+0x30);
	send_charCom2('.');
	send_charCom2((data%1000)/100+0x30);
	 send_charCom2((data%100)/10+0x30);
	 send_charCom2((data%10)+0x30);
  
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


/***** S E R I A L  T R A N S M I S S I O N *****************************************************************/
void send_charCom2(unsigned char x)                                          
{
   TXREG2 = x;
   while(!TXSTA2bits.TRMT);
}

/************************************************************************************************************/
void send_strCom2(const rom unsigned char *ptr)      // send string.
{
   while(*ptr !='\0')
   {
      send_charCom2(*ptr);
      ptr++;
	
   }
}

/***** S E R I A L  T R A N S M I S S I O N *****************************************************************/
void send_char(unsigned char x)         //  send each character at a time.                                             
{
   TXREG = x;
   while(!TXSTA1bits.TRMT);
//    while(!PIR1bits.RC1IF);
}

/************************************************************************************************************/
void send_str(unsigned char *ptr)      // send string.
{
   while(*ptr !='\0')
   {
      send_char(*ptr);
      ptr++;
   }
}

void serRX2(void)
 {
		while(PIR3bits.RC2IF==0);
		Y=RCREG2;
		
}

