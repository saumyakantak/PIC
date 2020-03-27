
#include "p18f46k22.h"
//#include "delays.h"  //inbuit delay for 1ms
#include "DOT_MARKER.h"
#include"serial.h"
#define _XTAL_FREQ 2000000

void buzzer(unsigned char serial_power );

void tmr_delay( unsigned long int sec_mul)
{
  unsigned long int i,j;
  for(j=0;j<sec_mul;j++)
{
	for(i=0;i<45;i++)
	{
	T0CON=0x01;
	TMR0H=0xB1;
	TMR0L=0xE0;
	T0CONbits.TMR0ON=1;
	while(INTCONbits.TMR0IF==0);
	T0CONbits.TMR0ON=0;
	INTCONbits.TMR0IF=0;
	}
}
}  


  

void TSTOVR ()
{
	
	 if(final_cheak_tube==8)
	  {
		serial_display(count);
		send_charCom2('J');
		send_charCom2('O');
		send_charCom2('B');
		send_charCom2('O');
		send_charCom2('K');
		serial_display(count);
		  DISOK();
		final_cheak_tube=0;
	  }
	  
	  else
		{
			serial_display(count);
			send_charCom2('J');
			send_charCom2('O');
			send_charCom2('B');
			send_charCom2('N');
			send_charCom2('G');
			serial_display(count);
			final_cheak_tube=0;
			c_wr(0x01);
			Delay1KTCYx(5);
			c_wr(0x80);
			Delay1KTCYx(5); 	
			d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
			d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
			c_wr(0xC0);
			Delay10KTCYx(5);
			d_wr('S');d_wr('O');d_wr('M');d_wr('E');d_wr(' ');d_wr('P');d_wr('A');d_wr('R');d_wr('A');d_wr('M');d_wr('E');d_wr('T');d_wr('E');d_wr('R');//d_wr('U');d_wr('&');d_wr('D');//d_wr(' ');
			c_wr(0x90);
			Delay10KTCYx(5);
			d_wr('F');d_wr('A');d_wr('I');d_wr('L');d_wr('E');d_wr('D');//d_wr('A');d_wr('R');d_wr('G');d_wr('E');d_wr('T');d_wr(':');d_wr(':');d_wr('U');d_wr('&');d_wr('S');//d_wr('S');
		
			RED=1;

			RCSTA=0x90;
			
			TXSTA=0x20;
			TXSTAbits.TXEN=1;
			TRISCbits.RC6=0;
			SPBRG=23;
			RCSTAbits.SPEN=1;
			//HIGH_BEAM_ON=1;
			Delay_ms(2); 
			TXREG='K';
			while(PIR1bits.TXIF==0);

			NEWHAR();
		}  
	

	     
	  
}

void DISOK()
{
	GREEN=1;
	
	c_wr(0x01);
	Delay1KTCYx(5);
	c_wr(0x80);
	Delay1KTCYx(5); 	
	d_wr('F'); d_wr('I'); d_wr('N'); d_wr('A'); d_wr('L');d_wr(' ');	d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
	    d_wr(' '); d_wr('O'); d_wr('K'); 
	c_wr(0xC0);
	Delay10KTCYx(5);
	d_wr('A');d_wr('L');d_wr('L');d_wr(' ');d_wr('P');d_wr('A');d_wr('R');d_wr('A');d_wr('M');d_wr('E');d_wr('T');d_wr('E');d_wr('R');//d_wr('U');d_wr('&');d_wr('D');//d_wr(' ');
	c_wr(0x90);
	Delay10KTCYx(5);
	d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('E');d_wr('D');//d_wr('A');d_wr('R');d_wr('G');d_wr('E');d_wr('T');d_wr(':');d_wr(':');d_wr('U');d_wr('&');d_wr('S');//d_wr('S');
	c_wr(0xD0);
	
	Delay10KTCYx(5);
	d_wr('*');d_wr('C');d_wr('O');d_wr('N');d_wr('G');d_wr('R');d_wr('A');d_wr('T');d_wr('U');d_wr('L');d_wr('A');d_wr('T');d_wr('I');d_wr('O');d_wr('N');d_wr('*');
	
		RCSTA=0x90;
		TXSTA=0x20;
		TXSTAbits.TXEN=1;
		TRISCbits.RC6=0;
		SPBRG=23;
		RCSTAbits.SPEN=1;
		Delay_ms(2); 
		TXREG='L';
		while(PIR1bits.TXIF==0);

		Delay_ms(2); 
		TXREG='M';
		while(PIR1bits.TXIF==0);

	tmr_delay(1);
	counter();
//	serial_display(count);
	tmr_delay(2);
	NEWHAR();
}


void NEWHAR ()
{
c_wr(0x01);
Delay1KTCYx(5);
c_wr (0x80);
Delay1KTCYx(5);
delay(3);
d_wr(' '); d_wr(' '); d_wr('F'); d_wr('O'); d_wr('R'); d_wr(' '); d_wr('T'); 
d_wr('E'); d_wr('S'); d_wr('T'); d_wr('I'); d_wr('N');  d_wr('G');  d_wr(' '); d_wr(' ');d_wr(' '); 
delay(3);
c_wr (0xC0);
Delay1KTCYx(5);
d_wr('C'); d_wr('O'); d_wr('N'); d_wr('N');	d_wr('E'); d_wr('C'); d_wr('T'); d_wr(' '); 
d_wr('L'); d_wr('E'); d_wr('D'); d_wr(' '); d_wr('T');  d_wr('U');  d_wr('B'); d_wr('E');  	
c_wr(0x90);
Delay1KTCYx(5);
d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*');	d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*'); 
d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*');  d_wr('*');  d_wr('*'); d_wr('*');     
	//	lcd_num_display(count);
c_wr(0xD0);
    d_wr('M'); d_wr('E'); d_wr('N');d_wr('U'); d_wr('='); d_wr('>'); d_wr('P'); d_wr('R');d_wr('E');  d_wr('S');d_wr('S');d_wr('"');d_wr('E');d_wr('"');
}
   
   
unsigned int counter()  
{
	
	 count = count++;  
	 EEpromWrite(&count,MAX_VAL_LOCATION_25,2);
	 if (count >= min_range25 )
	 {
		 EEpromClear(&count,MAX_VAL_LOCATION_25,2);
		 count=0; 
		 
	 }
}

void buzzer(unsigned char serial_power )
{
RCSTA=0x90;
	
TXSTA=0x20;
	TXSTAbits.TXEN=1;
	  TRISCbits.RC6=0;
	SPBRG=23;
	RCSTAbits.SPEN=1;
Delay_ms(2); 
TXREG=serial_power;
while(PIR1bits.TXIF==0);

}
