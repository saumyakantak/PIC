
#include "p18f46k22.h"
#include "delays.h"  //inbuit delay for 1ms
#include "DOT_MARKER.h"
#include"serial.h"
#define _XTAL_FREQ 2000000


unsigned char LH_RESULT=0,RH_RESULT=0; //RR=0;
extern unsigned int LH_FLAG;
extern unsigned int RH_FLAG;
extern unsigned int LH_yellow_flag;
extern unsigned int LH_red_flag;
extern unsigned int RH_yellow_flag;
extern unsigned int RH_red_flag;

unsigned int count77=0;


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
	
			if(SELECT_KEY==1)
			{
				 if(RH_FLAG==6)     //if(LH_FLAG==8)
				  {
					RH_RESULT=0;
					RH_DISOK();
					final_cheak_tube=0;
				  }
				else
				  {
					RH_RESULT=1;
					Delay_ms(5);
					NG_DISPLAY();
				  }
			}

			if(SELECT_KEY==0)
			{	
				 if(LH_FLAG==6)     //if(RH_FLAG==8)
				  {
					LH_RESULT=0;
					LH_DISOK();
					final_cheak_tube=0;
				  }
				  else
					{
					LH_RESULT=1;
					Delay_ms(5);
					NG_DISPLAY();
					//NEWHAR();
					}
			}
}		


void NG_DISPLAY()
{	
			c_wr(0x01);
			Delay_ms(1);
			c_wr(0x80);
			Delay_ms(5);
			if(LH_RESULT==1)
			{
			LH_RESULT=0;
			d_wr('L');d_wr('H');d_wr(' ');
			}
			if(RH_RESULT==1)
			{
			RH_RESULT=0;
			d_wr('R');d_wr('H');d_wr(' ');
			}
			d_wr('P'); d_wr('C'); d_wr('B'); 
			d_wr(' ');d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');d_wr('C'); d_wr('T'); d_wr(' ');
			c_wr(0xC0);
			Delay10KTCYx(5);
			d_wr('S');d_wr('O');d_wr('M');d_wr('E');d_wr(' ');d_wr('P');d_wr('A');d_wr('R');d_wr('A');d_wr('M');d_wr('E');d_wr('T');d_wr('E');d_wr('R');//d_wr('U');d_wr('&');d_wr('D');//d_wr(' ');
			c_wr(0x90);
			Delay10KTCYx(5);
			d_wr('F');d_wr('A');d_wr('I');d_wr('L');d_wr('E');d_wr('D');
		
			if((RH_red_flag==1)||(LH_red_flag==1))
			{
			RED=1;
			YELLOW =0;
			GREEN =0;
			Delay_ms(5);
			}
			if((RH_yellow_flag==1)||(LH_yellow_flag==1))
			{
			YELLOW=1;
			RED =0;
			GREEN =0;
			Delay_ms(5);
			}
			Delay_ms(2); 
			RCSTA=0x90;
			TXSTA=0x20;
			TXSTAbits.TXEN=1;
			TRISCbits.RC6=0;
			SPBRG=23;
			RCSTAbits.SPEN=1;
			
			Delay_ms(2); 
			TXREG='N';
			while(PIR1bits.TXIF==0);
			BUZZER =1;
			RED_NG=1;
			Delay_ms(5);
			BUZZER =0;
			RED_NG=0;
			Delay_ms(5);
			serial_display_mv(count77);
			send_charCom2('J');
			send_charCom2('O');
			send_charCom2('B');
			send_charCom2('N');
			send_charCom2('G');
			serial_display_mv(count77);
			Delay_ms(500);			
}  
	


void LH_DISOK()
{
	GREEN=1;
	c_wr(0x01);
	Delay1KTCYx(5);
	c_wr(0x80);
	Delay1KTCYx(5); 	
	d_wr('L'); d_wr('H');d_wr(' '); d_wr('S'); d_wr('I'); d_wr('D');d_wr('E');d_wr(' ');
	d_wr('P'); d_wr('C'); d_wr('B');d_wr(' '); d_wr('O'); d_wr('K'); 
	c_wr(0xC0);
	Delay10KTCYx(5);
	d_wr('A');d_wr('L');d_wr('L');d_wr(' ');d_wr('P');d_wr('A');d_wr('R');d_wr('A');d_wr('M');d_wr('E');d_wr('T');d_wr('E');d_wr('R');//d_wr('U');d_wr('&');d_wr('D');//d_wr(' ');
	c_wr(0x90);
	Delay10KTCYx(5);
	d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('E');d_wr('D');//d_wr('A');d_wr('R');d_wr('G');d_wr('E');d_wr('T');d_wr(':');d_wr(':');d_wr('U');d_wr('&');d_wr('S');//d_wr('S');
	Delay_ms(500);
   	BUZZER =1; 
	Delay_ms(1);  
	BUZZER =0;
	Delay_ms(1);
	BUZZER =1;
	Delay_ms(1);
	BUZZER =0;
	Delay_ms(1);	  
	RED =0;
	YELLOW =0;
	GREEN =0;
	Delay_ms(5);
	counter();
	tmr_delay(1);
	serial_display_mv(count77);
	send_charCom2('J');
	send_charCom2('O');
	send_charCom2('B');
	send_charCom2('O');
	send_charCom2('K');
	serial_display_mv(count77);
	Delay_ms(500);
	Channel_Read_LH('B');
	Delay_ms(500);
	//NEWHAR();
}

void RH_DISOK()
{
	GREEN=1;
	
	c_wr(0x01);
	Delay1KTCYx(5);
	c_wr(0x80);
	Delay1KTCYx(5); 	
	d_wr('R'); d_wr('H');d_wr(' '); d_wr('S'); d_wr('I'); d_wr('D');d_wr('E');d_wr(' ');
	d_wr('P'); d_wr('C'); d_wr('B');d_wr(' '); d_wr('O'); d_wr('K'); 
	c_wr(0xC0);
	Delay10KTCYx(5);
	d_wr('A');d_wr('L');d_wr('L');d_wr(' ');d_wr('P');d_wr('A');d_wr('R');d_wr('A');d_wr('M');d_wr('E');d_wr('T');d_wr('E');d_wr('R');//d_wr('U');d_wr('&');d_wr('D');//d_wr(' ');
	c_wr(0x90);
	Delay10KTCYx(5);
	d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('E');d_wr('D');//d_wr('A');d_wr('R');d_wr('G');d_wr('E');d_wr('T');d_wr(':');d_wr(':');d_wr('U');d_wr('&');d_wr('S');//d_wr('S');
	Delay_ms(500);
   	BUZZER =1; 
	Delay_ms(1);  
	BUZZER =0;
	Delay_ms(1);
	BUZZER =1;
	Delay_ms(1);
	BUZZER =0;
	Delay_ms(1);	  
	RED =0;
	YELLOW =0;
	GREEN =0;
	Delay_ms(5);
	counter();
	tmr_delay(1);
	serial_display_mv(count77);
	send_charCom2('J');
	send_charCom2('O');
	send_charCom2('B');
	send_charCom2('O');
	send_charCom2('K');
	serial_display_mv(count77);
	Delay_ms(500);
	Channel_Read_LH('A');
	Delay_ms(500);
	//NEWHAR();
}



void NEWHAR ()
{
c_wr(0x01);
Delay1KTCYx(5);
c_wr (0x80);
Delay1KTCYx(5);
delay(3);
d_wr('C'); d_wr('O'); d_wr('N'); d_wr('N');	d_wr('E'); d_wr('C'); d_wr('T'); d_wr(' '); 
d_wr('L'); d_wr('E'); d_wr('D'); d_wr(' '); d_wr('P');  d_wr('C');  d_wr('B'); d_wr(' ');  
delay(3);
c_wr (0xC0);
Delay1KTCYx(5);
d_wr('P'); d_wr('C'); d_wr('B'); d_wr(' ');	d_wr('C'); d_wr('O'); d_wr('U'); d_wr('N'); 
d_wr('T'); d_wr(' '); d_wr(':'); d_wr(' '); lcd_num_display(count77); 	
c_wr(0x90);
Delay1KTCYx(5);
d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*');	d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*'); 
d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*');  d_wr('*');  d_wr('*'); d_wr('*');     
	//	lcd_num_display(count);
c_wr(0xD0);
    d_wr('M'); d_wr('E'); d_wr('N');d_wr('U');d_wr(' '); d_wr('='); d_wr('>');d_wr(' '); d_wr('P'); d_wr('R');d_wr('E');  d_wr('S');d_wr('S');d_wr('"');d_wr('E');d_wr('"');
}
   
   
unsigned int counter()  
{
	
	 count77 = count77++;  
//	 EEpromWrite(&count77,MAX_VAL_LOCATION_25,2);

	if (count77 >= 9999 )
	{
//EEpromClear(&count77,MAX_VAL_LOCATION_25,2);
	count77=0; 
	}
	
}

