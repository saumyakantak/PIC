#include "p18f46k22.h"
//#include "delays.h"
#include "config.h"
#include "keypad.h"
#include "param.h"
#include "datatypes.h"
#include "DOT_MARKER.h "
#include"serial.h"
#include "lcd.h"
#include "RESULT.h"
#define START_KEY PORTEbits.RE2 

void chk_isr();
void  int_ISR();
void m24();

#pragma code hiprio_int=0x0008
#define KEY_1  0x01              //up        RD4
#define KEY_2  0x02            //crscr       RD5
#define KEY_3  0x04           //menu         RD6
#define KEY_4  0x08           //down         RD7

unsigned char page_index;
unsigned char HARREJ;
void Page_Max(void);
void Page_Max2(void);
void Page_Min(void);
void Page_1(void);
void cal_lux();

void START();
void voltage_read();
void current_read();
void current_read24V();
void MANUL_CHK();
void v_OKD_DISP();
void v_NGD_DISP();
void v_OKC_DISP();
void v_NGC_DISP();
void rev_pol();
unsigned int  target1();
void v32_ps();
void v12_chk();
void v24_ps();
unsigned int sp,sj,ch;
long unsigned int  adc_avg_mv2;
long unsigned int adc_avg_mv1;
unsigned int adc_avg_mv;
void delayms(unsigned int b);
extern unsigned char volt_flag;
int m,n,o1,p,t1,x1,x11;
unsigned int x,ack=0;
unsigned int r,rep=0;    
volatile int f_array=1;
unsigned int temp;
unsigned int v[5];
unsigned char power_argument=0;
unsigned int final_cheak_tube=0;
unsigned int manual_flag=0;
unsigned int manual_check_flag=0;
unsigned int i; 
unsigned int f,r,g;
unsigned int tube_24_flag=0;
unsigned char SW;  /// SW ASSIGN PORT PIN 
unsigned char line;
extern void timepass(unsigned int );

void lcd_num_display(unsigned int );
unsigned char keypress,keyflag,dummy_rtn,byte_1,byte_2,t=0,k=0,o=0,s=0;
unsigned char Status_buffer[24],low_index,high_index;

unsigned int k1,m1,k2,m2,k3,m3,k4,m4,k5,m5,k6,m6,k7,m7,k8,m8,k9,m9,k10,m10,k11,m11,k12,m12,k13,m13,k14,m14,k15,m15,k16,m16,k17,m17;
unsigned adc_val1,adc_val2,adc_val3,adc_val4,adc_val5,adc_val6,adc_val7,adc_val8,adc_val9,adc_val10,adc_val11,adc_val12,adc_val13,adc_val14,adc_val15,adc_val16;
unsigned int adc_val1_mv,adc_val2_mv,adc_val3_mv,adc_val4_mv,adc_val5_mv,adc_val6_mv,adc_val7_mv,adc_val17A_mv,adc_val8_mv;
unsigned int adc_val9_mv,adc_val10_mv,adc_val11_mv,adc_val12_mv,adc_val13_mv,adc_val14_mv,adc_val15_mv,adc_val16_mv;
unsigned int adc_val17_mv,adc_val18_mv,adc_val19_mv,adc_val20_mv,adc_val21_mv,adc_val22_mv,adc_val23_mv,adc_val24_mv;


unsigned char toggle_mode =0;
unsigned char set_mode =0;
static int digit = 0x00,UP_cntr[4];
unsigned int cnt_digit,cnt_digit2;

void set_min(unsigned int min,unsigned int max,unsigned char ch);
void set_max(unsigned int min,unsigned int max,unsigned char ch);
void set_max_count(unsigned int min,unsigned int max,unsigned char ch);
void set_min_count(unsigned int min,unsigned int max,unsigned char ch);

extern unsigned int max_range1;
extern unsigned int min_range1;
extern unsigned int max_range2;
extern unsigned int min_range2;
extern unsigned int max_range3;
extern unsigned int min_range3;
extern unsigned int max_range4;
extern unsigned int min_range4;
extern unsigned int max_range5;
extern unsigned int min_range5;
extern unsigned int max_range6;
extern unsigned int min_range6;
extern unsigned int max_range7;
extern unsigned int min_range7;
extern unsigned int max_range8;
extern unsigned int min_range8;
extern unsigned int max_range9;
extern unsigned int min_range9;
extern unsigned int max_range10;
extern unsigned int min_range10;
extern unsigned int max_range11;
extern unsigned int min_range11;
extern unsigned int max_range12;
extern unsigned int min_range12;
extern unsigned int max_range13;
extern unsigned int min_range13;
extern unsigned int max_range14;
extern unsigned int min_range14;
extern unsigned int max_range15;
extern unsigned int min_range15;
extern unsigned int max_range16;
extern unsigned int min_range16;
extern unsigned int max_range17;
extern unsigned int min_range17;
extern unsigned int max_range18;
extern unsigned int min_range18;
extern unsigned int max_range19;
extern unsigned int min_range19;
extern unsigned int max_range20;
extern unsigned int min_range20;
extern unsigned int max_range21;
extern unsigned int min_range21;
extern unsigned int max_range22;
extern unsigned int min_range22;
extern unsigned int max_range23;
extern unsigned int min_range23;
extern unsigned int max_range24;
extern unsigned int min_range24;
extern unsigned int max_range25;
extern unsigned int min_range25;
extern unsigned int max_range28;
extern unsigned int min_range28;
extern unsigned char page_index;
extern unsigned int initial_cheak;
unsigned int FCT=0;
unsigned int F_FCT=0;

void movepasscur();
void incridigit();
void decridigit();

void movepasscur_set();
void decridigit_set();
void incridigit_set() ;    
void keypad_calling();
void menu_button();         

void Channel_Read(unsigned char serial_power_on); 
unsigned int range;
unsigned int range_set;


void main(void)
{ 
TRISC=0b10111010;        // (rs rw E...RC0,RC1,RC2)( ANALOG CHANNELS RC3 TO RC7( RC3 AS A VOLT ADC)
TRISB=0b00001111;     	// (data PORTD RB4 TO RB7) (SWITCH RB0 TO RB4)
TRISD=0b10111111;       //  ANALOG INPUTS(RD0...RD7)
TRISA=0x11001101; //analog i/p
TRISE=0x07;  //led
ANSELB=0x00;  //SWITCH
ANSELA=0x01;   //ANALOG I/P  (RA0,RA1,RA5)
ANSELD=0X3F;  //ANALOG I/P  (RD0...RD7)
ANSELC=0xB8;   //ANALOG I/P (RC3....RC7)
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
START_KEY =0; 
RED =0; //LOW_BEAM_F_B =0; HIGH_BEAM_F_B =0;
YELLOW=0;//IND_BEAM_LED =0;
GREEN=0;
tube_24_flag=0;

HARREJ=0;
Delay_ms(200);
init_lcd();
Delay_ms(500);
c_wr(0x01);
Delay_ms(200);
init_lcd();
Delay_ms(500);
c_wr(0x01);
Delay_ms(200);
count=0;
init_lcd();
Delay_ms(500);
c_wr(0x01);
Delay_ms(20);
c_wr(0x80);
delayms(5);
	
d_wr('L'); d_wr('E');d_wr('D'); d_wr(' ');	d_wr('T'); d_wr('U'); d_wr('B');d_wr('E'); d_wr(' '); d_wr('T'); d_wr('E'); d_wr('S'); d_wr('T'); d_wr('E'); d_wr('R');
c_wr(0xC0); 		
d_wr('*'); d_wr('*');d_wr('*'); d_wr('*');	d_wr('*'); d_wr('*'); d_wr('*');d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*'); d_wr('*');d_wr('*');
c_wr(0x90);
d_wr('Y');d_wr('O');d_wr('S');d_wr('H');d_wr('I');d_wr('T');d_wr('A');d_wr(' ');d_wr('T');d_wr('E');d_wr('C');d_wr('H');d_wr('N');d_wr('I');d_wr('-');  
Delay_ms(200);
c_wr(0xD0);
d_wr('C'); d_wr('A');d_wr('L'); d_wr(' ');	d_wr('S'); d_wr('E'); d_wr('R');d_wr('V'); d_wr('I');d_wr('C'); d_wr('E');	d_wr('S'); d_wr(' '); d_wr(' ');
Delay_ms(500);
EEPROM_Load();
   
EEpromRead(&count,MAX_VAL_LOCATION_25,2);
EEpromRead(&min_range25,MIN_VAL_LOCATION_25,2);

EEpromRead(&min_range26,MIN_VAL_LOCATION_26,2);

EEpromRead(&count2,MAX_VAL_LOCATION_28,2);
EEpromRead(&min_range28,MIN_VAL_LOCATION_28,2);

RED =0;
START_KEY=0;
EEPROM_Load(); 
NEWHAR();

			       
  while(1)
			{  
					if(v_sel==1)
					{
						c_wr(0xD13);
							Delay_ms(2);
							d_wr('1');d_wr('2');d_wr('V');
					}
					else if(v_sel==0)
					{
						c_wr(0xD13);
							Delay_ms(2);
							d_wr('2');d_wr('4');d_wr('V');
					}
				
				EEpromRead(&count,MAX_VAL_LOCATION_25,2);			
				YELLOW=0;
				RED=0;
				Delay_ms(500);
				GREEN=0;
				tube_24_flag=0;
				r=0;
				f=0;
				g=0;
				EEPROM_Load();
				GREEN=0;
				while(START_KEY!=0)
				{
					
				 if (((PORTB & 0x04) == 0x04))
					menu_button();	
				}	
					Delay_ms(5);
					EEPROM_Load();	
					SW=0;	
					if(PIR3bits.RC2IF==1)
					{
					if(RCREG2=='Y') 
					{
						RCREG2='N';
						START();
						Delay_ms(500);
						 if(final_cheak_tube==8)
	  					{
							if(v_sel==1)
							{
							MANUL_CHK();
							}
							else
							{
							m24();
							}
							TSTOVR();	
						}
						else{ 
								FCT=6-final_cheak_tube;
								for(F_FCT=1;F_FCT<FCT;F_FCT++)
								{
										send_charCom2('0');
										send_charCom2('0');
										send_charCom2('0');
										send_charCom2('0');
										send_charCom2('0');
										Delay_ms(500);
								}
									serial_display(count);
									send_charCom2('J');
									send_charCom2('O');
									send_charCom2('B');
									send_charCom2('N');
									send_charCom2('G');
									serial_display(count);
									final_cheak_tube=0;
									FCT=0;
									F_FCT=0;
							}
					}  
					}
				GREEN=0;
				EEPROM_Load();
				NEWHAR();
				RCSTA=0x90;
				TXSTA=0x20;
				TXSTAbits.TXEN=1;
				TRISCbits.RC6=0;
				SPBRG=23;
				RCSTAbits.SPEN=1;
				TXREG='*';
				while(PIR1bits.TXIF==0);
				Delay_ms(100);	
		}
   
}     
 
void Page_1(void)                    //  to check which channels are  out of range
{   

	if(max_range1 > min_range1 )
	{

		if(adc_val1_mv < min_range1)
		{                             //displaadc_val1_mv '1' (ch1)
			Status_buffer[0] = 1;            
		}
		else if (adc_val1_mv > max_range1)
		{
			Status_buffer[0] = 2;	                                         //displaadc_val1_mv '1 ' (ch1)
		}
		else
		{
			Status_buffer[0] = 0;
		}
	}
	    else
     	{
	
	    }


	if(max_range2 > min_range2 )                                   // same as above for ch 2
	{

		if(adc_val2_mv < min_range2)
		{
			Status_buffer[1] = 1;
		}
		else if (adc_val2_mv > max_range2)
		{
			Status_buffer[1] = 2;
		}
		else
		{
			Status_buffer[1] = 0;
		}
	}
    	else
	   {

	   }


 
	if(max_range3 > min_range3 )          // same as above for ch 3
	 {

		if(adc_val3_mv < min_range3)
		{
			Status_buffer[2] = 1;
		}
		else if (adc_val3_mv > max_range3)
		{
			Status_buffer[2] = 2;
		}
		else
		{
			Status_buffer[2] = 0;
		}
	}
    	else
	   {
	   }



	if(max_range4 > min_range4 )            // same as above for ch 4
	{

		if(adc_val4_mv < min_range4)
		{
			Status_buffer[3] = 1;
		}
		else if (adc_val4_mv > max_range4)
		{
			Status_buffer[3] = 2;
		}
		else
		{
			Status_buffer[3] = 0;
		}
	}
	   else
	   {

	   }


	d_wr(' ');
	if(max_range5 > min_range5)                 // same as above for ch 5
	{

		if(adc_val5_mv < min_range5)
		{
			Status_buffer[4] = 1;
		}
		else if (adc_val5_mv > max_range5)
		{
			Status_buffer[4] = 2;
		}
		else
		{
			Status_buffer[4] = 0;
		}
	}
	    else
	   {

	   }


	if(max_range6 > min_range6)                       // same as above for ch 6
	{
		if(adc_val6_mv < min_range6)
		{
			Status_buffer[5] = 1;
		}
		else if (adc_val6_mv > max_range6)
		{
			Status_buffer[5] = 2;
		}
		else
		{
			Status_buffer[5] = 0;
		}
	}
    	else
    	{
    	}




	if(max_range7 > min_range7)            // same as above for ch 7
	{
		if(adc_val7_mv < min_range7)
		{
			Status_buffer[6] = 1;
		}
		else if (adc_val7_mv > max_range7)
		{
			Status_buffer[6] = 2;
		}
		else
		{
			Status_buffer[6] = 0;
		}
	}
	   else
    	{

	    }


	if(max_range8 > min_range8)                      // same as above for ch 8
	{
		if(adc_val8_mv < min_range8)
		{
			Status_buffer[7] = 1;
		}
		else if (adc_val8_mv > max_range8)
		{
			Status_buffer[7] = 2;
		}
		else
		{
			Status_buffer[7] = 0;
		}
	}
	   else
    	{
	    }


	if(max_range9 > min_range9)            // same as above for ch 9
	{
		if(adc_val9_mv < min_range9)
		{
			Status_buffer[8] = 1;
		}
		else if (adc_val9_mv > max_range9)
		{
			Status_buffer[8] = 2;
		}
		else
		{
			Status_buffer[8] = 0;
		}
	}
    	else
	   {
	   }


 	
 	
 	
	if(max_range10 > min_range10)           // same as above for ch 10
	{
		if(adc_val10_mv < min_range10)
		{
			Status_buffer[9] = 1;
		}
		else if (adc_val10_mv > max_range10)
		{
			Status_buffer[9] = 2;
		}
		else
		{
			Status_buffer[9] = 0;
		}
	}
	   else
	   {
	   }



	if(max_range11 > min_range11)               // same as above for ch 11
	{
		if(adc_val11_mv < min_range11)
		{
			Status_buffer[10] = 1;
		}
		else if (adc_val11_mv > max_range11)
		{
			Status_buffer[10] = 2;
		}
		else
		{
			Status_buffer[10] = 0;
		}
	}
	   else
	   {
	
	   }

	if(max_range12 > min_range12)            // same as above for ch 12
	{
		if(adc_val12_mv < min_range12)
		{
			Status_buffer[11] = 1;
		}
		else if (adc_val12_mv > max_range12)
		{
			Status_buffer[11] = 2;
		}
		else
		{
			Status_buffer[11] = 0;
		}
	}
	    else
	   {
	   }

	if(max_range13 > min_range13)            // same as above for ch 13
	{
		if(adc_val13_mv < min_range13)
		{ 
			Status_buffer[12] = 1;
		}
		else if (adc_val13_mv > max_range13)
		{
			Status_buffer[12] = 2;
		}
		else
		{
			Status_buffer[12] = 0;
		}
	}
	    else
	    {
	
	    }

	if(max_range14 > min_range14)              // same as above for ch 14
	{
		if(adc_val14_mv < min_range14)
		{
			Status_buffer[13] = 1;
		}
		else if (adc_val14_mv > max_range14)
		{
			Status_buffer[13] = 2;
		}
		else
		{
			Status_buffer[13] = 0;
		}
	}
	   else
	    {
	
     	}

	if(max_range15 > min_range15)               // same as above for ch 15
	{
		if(adc_val15_mv < min_range15)
		{
			Status_buffer[14] = 1;
		}
		else if (adc_val15_mv > max_range15)
		{
			Status_buffer[14] = 2;
		}
		else
		{
			Status_buffer[14] = 0;
		}
	}
	else
	{
		
	}

	if(max_range16 > min_range16)               // same as above for ch 16  
	{
		if(adc_val16_mv < min_range16)
		{
			Status_buffer[15] = 1;
		}
		else if (adc_val16_mv > max_range16)
		{
			Status_buffer[15] = 2;
		}
		else
		{
			Status_buffer[15] = 0;
		}
	}
    	else
	     {
		
	    }

	if(max_range17 > min_range17)            // same as above for ch 7
	{
		if(adc_val17_mv < min_range17)
		{
			Status_buffer[16] = 1;
		}
		else if (adc_val17_mv > max_range17)
		{
			Status_buffer[16] = 2;
		}
		else
		{
			Status_buffer[16] = 0;
		}
	}
	   else
    	{
	
	    }

	if(max_range18 > min_range18)                      // same as above for ch 8
	{
		if(adc_val18_mv < min_range18)
		{
			Status_buffer[17] = 1;
		}
		else if (adc_val18_mv > max_range18)
		{
			Status_buffer[17] = 2;
		}
		else
		{
			Status_buffer[17] = 0;
		}
	}
	   else
    	{
	
	    }


	if(max_range19 > min_range19)            // same as above for ch 9
	{
		if(adc_val19_mv < min_range19)
		{
			Status_buffer[18] = 1;
		}
		else if (adc_val19_mv > max_range19)
		{
			Status_buffer[18] = 2;
		}
		else
		{
			Status_buffer[18] = 0;
		}
	}
    	else
	   {

	   }

 	
	if(max_range20 > min_range20)           // same as above for ch 10
	{
		if(adc_val20_mv < min_range20)
		{
			Status_buffer[19] = 1;
		}
		else if (adc_val20_mv > max_range20)
		{
			Status_buffer[19] = 2;
		}
		else
		{//+
			Status_buffer[19] = 0;
		}
	}
	   else
	   {
	   }

	if(max_range21 > min_range21)               // same as above for ch 11
	{
		if(adc_val21_mv < min_range21)
		{
			Status_buffer[20] = 1;
		}
		else if (adc_val21_mv > max_range21)
		{
			Status_buffer[20] = 2;
		}
		else
		{
			Status_buffer[20] = 0;
		}
	}
	   else
	   {
	
	   }

	if(max_range22 > min_range22)            // same as above for ch 12
	{
		if(adc_val22_mv < min_range22)
		{
			Status_buffer[21] = 1;

		}
		else if (adc_val22_mv > max_range22)
		{
			Status_buffer[21] = 2;
		}
		else
		{
			Status_buffer[21] = 0;
		}
	}
	    else
	   {
		
	   }

	if(max_range23 > min_range23)            // same as above for ch 13
	{
		if(adc_val23_mv < min_range23)
		{
			Status_buffer[22] = 1;

		}
		else if (adc_val23_mv > max_range23)
		{
			Status_buffer[22] = 2; 
		}
		else
		{
			Status_buffer[22] = 0;
		}
	}
	    else
	    {
		 
	    }

	if(max_range24 > min_range24)              // same as above for ch 14
	{
		if(adc_val24_mv < min_range24)
		{

			Status_buffer[23] = 1;

		}
		else if (adc_val24_mv > max_range24)
		{
			Status_buffer[23] = 2;
		}
		else
		{
			Status_buffer[23] = 0;
		}
	}
	   else
	    {
		 
     	}

	   
}

void Page_Max(void)
{

    c_wr(0x80);
	d_wr('C');d_wr('H');d_wr('A');d_wr('N');d_wr('N');d_wr('E');d_wr('L');d_wr(' ');d_wr('R');d_wr('A');d_wr('N');d_wr('G');d_wr('E');d_wr('S');d_wr(':');d_wr(':');
	if(max_range1 > min_range1 )
	{

		if(adc_val1_mv < min_range1)
		{

		c_wr(0xC0);
		d_wr('1');
        d_wr(' ');	
			Status_buffer[0] = 1;

		}
		else if (adc_val1_mv > max_range1)
		{
		c_wr(0xC0);
		d_wr('1');
        d_wr(' ');	
		Status_buffer[0] = 2;
			
		}
		else
		{
			Status_buffer[0] = 0;

		c_wr(0xC0);
		d_wr('-');
        d_wr(' ');	
		}

	}
	else
	{
	c_wr(0xC0);
	d_wr('*');
d_wr(' ');
	}

	if(max_range2 > min_range2 )
	{

		if(adc_val2_mv < min_range2)
		{

			c_wr(0xC2);
		d_wr('2');
        d_wr(' ');
			Status_buffer[1] = 1;

		}
		else if (adc_val2_mv > max_range2)
		{
			Status_buffer[1] = 2;
				c_wr(0xC2);
		d_wr('2');
        d_wr(' ');
		}
		else
		{
			Status_buffer[1] = 0;

	c_wr(0xC2);
d_wr('-');
	d_wr(' ');	
		}
	}
	else
	{
		c_wr(0xC2);
	   	d_wr('*');
		d_wr(' ');
			}


	if(max_range3 > min_range3 )
	{

		if(adc_val3_mv < min_range3)
		{

				c_wr(0xC4);
		d_wr('3');
        d_wr(' ');
			Status_buffer[2] = 1;

		}
		else if (adc_val3_mv > max_range3)
		{
			Status_buffer[2] = 2;
		c_wr(0xC4);
		d_wr('3');
        d_wr(' ');
		}
		else
		{
			Status_buffer[2] = 0;

	c_wr(0xC4);
	d_wr('-');
	d_wr(' ');
		
		}
	}
	else
	{
	c_wr(0xC4);
	   	d_wr('*');
		d_wr(' ');
	}

	if(max_range4 > min_range4 )
	{

		if(adc_val4_mv < min_range4)
		{

			
				c_wr(0xC6);
		d_wr('4');
        d_wr(' ');
			Status_buffer[3] = 1;

		}
		else if (adc_val4_mv > max_range4)
		{
			Status_buffer[3] = 2;
				c_wr(0xC6);
		d_wr('4');
        d_wr(' ');
		}
		else
		{
			Status_buffer[3] = 0;

		c_wr(0xC6);
	d_wr('-');
	d_wr(' ');
	
		}
	}
	else
	{
			c_wr(0xC6);
			d_wr('*');	
		d_wr(' ');
	}

	if(max_range5 > min_range5)
	{

		if(adc_val5_mv < min_range5)
		{

				c_wr(0xC8);
		d_wr('5');
        d_wr(' ');
			Status_buffer[4] = 1;

		}
		else if (adc_val5_mv > max_range5)
		{
			Status_buffer[4] = 2;
		c_wr(0xC8);
		d_wr('5');
        d_wr(' ');
		}
		else
		{
			Status_buffer[4] = 0;

		c_wr(0xC8);
	
d_wr('-');
	d_wr(' ');
		}
	}
	else
	{
			c_wr(0xC8);
				d_wr('*');	
		d_wr(' ');
	}

//	d_wr(' ');
	if(max_range6 > min_range6)
	{
		if(adc_val6_mv < min_range6)
		{

			c_wr(0xCA);
		d_wr('6');
        d_wr(' ');
			Status_buffer[5] = 1;

		}
		else if (adc_val6_mv > max_range6)
		{
			Status_buffer[5] = 2;
					c_wr(0xCA);
		d_wr('6');
        d_wr(' ');
		}
		else
		{
			Status_buffer[5] = 0;

				c_wr(0xCA);
	d_wr('-');
	d_wr(' ');	
		}
	}
	else
	{
			c_wr(0xCA);
		d_wr('*');	
		d_wr(' ');
	}

//d_wr(' ');
	if(max_range7 > min_range7)
	{
		if(adc_val7_mv < min_range7)
		{

		     c_wr(0xCC);
		d_wr('7');
        d_wr(' ');
			Status_buffer[6] = 1;

		}
		else if (adc_val7_mv > max_range7)
		{
			Status_buffer[6] = 2;
		 c_wr(0xCC);
		d_wr('7');
        d_wr(' ');
		}
		else
		{
			Status_buffer[6] = 0;

		 c_wr(0xCC);
		d_wr('-');
        d_wr(' ');
		}
	}
	else
	{
	 		c_wr(0xCC);
			d_wr('*');	
		d_wr(' ');
	}

       //d_wr(' ');
	if(max_range8 > min_range8)
	{
		if(adc_val8_mv < min_range8)
		{

		   c_wr(0xCE);
		d_wr('8');
        d_wr(' ');
			Status_buffer[7] = 1;

		}
		else if (adc_val8_mv > max_range8)
		{
			Status_buffer[7] = 2;
			  c_wr(0xCE);
		d_wr('8');
        d_wr(' ');
		}
		else
		{
			Status_buffer[7] = 0;
	  c_wr(0xCE);
	d_wr('-');
	d_wr(' ');
		}
	}
	else
	{
		  c_wr(0xCE);
	   	d_wr('*');
		d_wr(' ');
	}

		//lcd_gotoxy(2,0);

	if(max_range9 > min_range9)
	{
		if(adc_val9_mv < min_range9)
         {
			c_wr(0x90);
		d_wr('9');
        d_wr(' ');
			Status_buffer[8] = 1;

		}
		else if (adc_val9_mv > max_range9)
		{
			Status_buffer[8] = 2;
				c_wr(0x90);
		d_wr('9');
        d_wr(' ');
		}
		else
		{
			Status_buffer[8] = 0;

		c_wr(0x90);
			d_wr('-');
	d_wr(' ');
		}	
	
	}
	else
	{
		c_wr(0x90);
			d_wr('*');	
		d_wr(' ');
	}

 	
	if(max_range10 > min_range10)           // same as above for ch 10
	{
		if(adc_val10_mv < min_range10)
		{

		c_wr(0x92);
		d_wr('1');
        d_wr('0');
			Status_buffer[9] = 1;

		}
		else if (adc_val10_mv > max_range10)
		{
			Status_buffer[9] = 2;
		c_wr(0x92);
		d_wr('1');
        d_wr('0');
		}
		else
		{//+
			Status_buffer[9] = 0;
			c_wr(0x92);
		d_wr('-');
        d_wr(' ');
		}
	}
	   else
	   {
	    c_wr(0x92);
		d_wr('*');
        d_wr(' ');
	   }


//	d_wr(' ');
	if(max_range11 > min_range11)               // same as above for ch 11
	{
		if(adc_val11_mv < min_range11)
		{

	    c_wr(0x94);
		d_wr('1');
        d_wr('1');
			Status_buffer[10] = 1;

		}
		else if (adc_val11_mv > max_range11)
		{
			Status_buffer[10] = 2;
		 c_wr(0x94);
		d_wr('1');
        d_wr('1');
		}
		else
		{
			Status_buffer[10] = 0;

			 c_wr(0x94);
		d_wr('-');
        d_wr(' ');
		}
	}
	   else
	   {
	 c_wr(0x94);
		d_wr('*');
        d_wr(' ');
	   }

     //d_wr(' ');
	if(max_range12 > min_range12)            // same as above for ch 12
	{
		if(adc_val12_mv < min_range12)
		{

	 c_wr(0x96);
		d_wr('1');
        d_wr('2');
			Status_buffer[11] = 1;

		}
		else if (adc_val12_mv > max_range12)
		{
			Status_buffer[11] = 2;
	   c_wr(0x96);
		d_wr('1');
        d_wr('2');
		}
		else
		{
			Status_buffer[11] = 0;

			 c_wr(0x96);
		d_wr('-');
        d_wr(' ');
		}
	}
	    else
	   {
	c_wr(0x96);
		d_wr('*');
        d_wr(' ');
	   }



	if(max_range13 > min_range13)            // same as above for ch 13
	{
		if(adc_val13_mv < min_range13)
		{

				 c_wr(0x98);
		d_wr('1');
        d_wr('3');
			Status_buffer[12] = 1;

		}
		else if (adc_val13_mv > max_range13)
		{
			Status_buffer[12] = 2;
		c_wr(0x98);
		d_wr('1');
        d_wr('3');
		}
		else
		{
			Status_buffer[12] = 0;
c_wr(0x98);
		d_wr('-');
        d_wr(' ');
		}
	}
	    else
	    {
		c_wr(0x98);
		d_wr('*');
        d_wr(' ');
	    }
	if(max_range14 > min_range14)              // same as above for ch 14
	{
		if(adc_val14_mv < min_range14)
		{

		    c_wr(0x9A);
		d_wr('1');
        d_wr('4');
			Status_buffer[13] = 1;

		}
		else if (adc_val14_mv > max_range14)
		{
			Status_buffer[13] = 2;
		        c_wr(0x9A);
		d_wr('1');
        d_wr('4');
		}
		else
		{
			Status_buffer[13] = 0;

			    c_wr(0x9A);
		d_wr('-');
        d_wr(' ');
		}
	}
	   else
	    {
		 c_wr(0x9A);
		d_wr('*');
        d_wr(' ');
     	}

	if(max_range15 > min_range15)               // same as above for ch 15
	{
		if(adc_val15_mv < min_range15)
		{
			c_wr(0x9C);
		d_wr('1');
        d_wr('5');
			Status_buffer[14] = 1;

		}
		else if (adc_val15_mv > max_range15)
		{
			Status_buffer[14] = 2;
			  		c_wr(0x9C);
		d_wr('1');
        d_wr('5');
		}
		else
		{
			Status_buffer[14] = 0;

		    		c_wr(0x9C);
		d_wr('-');
        d_wr(' ');
		}
	}
	else
	{
			c_wr(0x9C);
		d_wr('*');
        d_wr(' ');
	}


  
	if(max_range16 > min_range16)               // same as above for ch 16  
	{
		if(adc_val16_mv < min_range16)
		{

		     	c_wr(0x9E);
		d_wr('1');
        d_wr('6');
			Status_buffer[15] = 1;

		}
		else if (adc_val16_mv > max_range16)
		{
			Status_buffer[15] = 2;
			  c_wr(0x9E);
		d_wr('1');
        d_wr('6');
		}
		else
		{
			Status_buffer[15] = 0;
c_wr(0x9E);
		d_wr('-');
        d_wr(' ');
		}
	}
    	else
	     {
		  c_wr(0x9E);
		d_wr('*');
        d_wr(' ');
	    }

	if(max_range17 > min_range17)            // same as above for ch 7
	{
		if(adc_val17_mv < min_range17)
		{

			c_wr(0xD0);
		d_wr('1');
        d_wr('7');
			Status_buffer[16] = 1;

		}
		else if (adc_val17_mv > max_range17)
		{
			Status_buffer[16] = 2;
		c_wr(0xD0);
		d_wr('1');
        d_wr('7');
		}
		else
		{
			Status_buffer[16] = 0;
         	c_wr(0xD0);
		d_wr('-');
        d_wr(' ');
		}
	}
	   else
    	{
	c_wr(0xD0);
		d_wr('*');
        d_wr(' ');
	    }


//	d_wr(' ');
	if(max_range18 > min_range18)                      // same as above for ch 8
	{
		if(adc_val18_mv < min_range18)
		{

		c_wr(0xD2);
		d_wr('1');
        d_wr('8');
			Status_buffer[17] = 1;

		}
		else if (adc_val18_mv > max_range18)
		{
			Status_buffer[17] = 2;
		c_wr(0xD2);
		d_wr('1');
        d_wr('8');
		}
		else
		{
			Status_buffer[17] = 0;
		c_wr(0xD2);
		d_wr('-');
        d_wr(' ');
		}
	}
	   else
    	{
		c_wr(0xD2);
		d_wr('*');
        d_wr(' ');
	    }

	if(max_range19 > min_range19)            // same as above for ch 9
	{
		if(adc_val19_mv < min_range19)
		{
	c_wr(0xD4);
		d_wr('1');
        d_wr('9');
			Status_buffer[18] = 1;
		}
		else if (adc_val19_mv > max_range19)
		{
			Status_buffer[18] = 2;
		c_wr(0xD4);
		d_wr('1');
        d_wr('9');
		}
		else
		{
			Status_buffer[18] = 0;

		c_wr(0xD4);
		d_wr('-');
        d_wr(' ');
		}
	}
    	else
	   {
    c_wr(0xD4);
		d_wr('*');
        d_wr(' ');
	   }


 //	d_wr(' ');
 	
 	
 	
	if(max_range20 > min_range20)           // same as above for ch 10
	{
		if(adc_val20_mv < min_range20)
		{

		c_wr(0xD6);
		d_wr('2');
        d_wr('0');
			Status_buffer[19] = 1;

		}
		else if (adc_val20_mv > max_range20)
		{
			Status_buffer[19] = 2;
	c_wr(0xD6);
		d_wr('2');
        d_wr('0');
		}
		else
		{//+
			Status_buffer[19] = 0;

		c_wr(0xD6);
		d_wr('-');
        d_wr(' ');
		}
	}
	   else
	   {
	   c_wr(0xD6);
		d_wr('*');
        d_wr(' ');
	   }


//	d_wr(' ');
	if(max_range21 > min_range21)               // same as above for ch 11
	{
		if(adc_val21_mv < min_range21)
		{

	   c_wr(0xD8);
		d_wr('2');
        d_wr('1');
			Status_buffer[20] = 1;

		}
		else if (adc_val21_mv > max_range21)
		{
			Status_buffer[20] = 2;
			   c_wr(0xD8);
		d_wr('2');
        d_wr('1');
		}
		else
		{
			Status_buffer[20] = 0;

				   c_wr(0xD8);
		d_wr('-');
        d_wr(' ');
		}
	}
	   else
	   {
			   c_wr(0xD8);
		d_wr('*');
        d_wr(' ');
	   }

     //d_wr(' ');
	if(max_range22 > min_range22)            // same as above for ch 12
	{
		if(adc_val22_mv < min_range22)
		{

		   c_wr(0xDA);
		d_wr('2');
        d_wr('2');
			Status_buffer[21] = 1;

		}
		else if (adc_val22_mv > max_range22)
		{
			Status_buffer[21] = 2;
	      c_wr(0xDA);
		d_wr('2');
        d_wr('2');
		}
		else
		{
			Status_buffer[21] = 0;

			    c_wr(0xDA);
		d_wr('-');
        d_wr(' ');
		}
	}
	    else
	   {
	  c_wr(0xDA);
		d_wr('*');
        d_wr(' ');
	   }

	if(max_range23 > min_range23)            // same as above for ch 13
	{
		if(adc_val23_mv < min_range23)
		{

				   c_wr(0xDC);
		d_wr('2');
        d_wr('3');
			Status_buffer[22] = 1;

		}
		else if (adc_val23_mv > max_range23)
		{
			Status_buffer[22] = 2;
		c_wr(0xDC);
		d_wr('2');
        d_wr('3');
		}
		else
		{
			Status_buffer[22] = 0;

	    c_wr(0xDC);
		d_wr('-');
        d_wr(' ');
		}
	}
	    else
	    {
		 c_wr(0xDC);
		d_wr('*');
        d_wr(' ');
	    }

	if(max_range24 > min_range24)              // same as above for ch 14
	{
		if(adc_val24_mv < min_range24)
		{

		    c_wr(0xDE);
		d_wr('2');
        d_wr('4'); 
			Status_buffer[23] = 1;

		}
		else if (adc_val24_mv > max_range24)
		{
			Status_buffer[23] = 2;
		         c_wr(0xDE);
		d_wr('2');
        d_wr('4'); 
		}
		else
		{
			Status_buffer[23] = 0;

		c_wr(0xDE);
		d_wr('-');
        d_wr(' '); 
		}
	}
	   else
	    {
		 c_wr(0xDE);
		d_wr('*');
        d_wr(' '); 
     	}

		
} 





unsigned int  target1()
{
c_wr(0x01);
Delay10KTCYx(5);
c_wr(0x80);
Delay10KTCYx(5);
d_wr('S');d_wr('E');d_wr('T');d_wr('T');d_wr('I');d_wr('N');d_wr('G');d_wr('S');d_wr(':');d_wr(':');//d_wr('C');d_wr('H');
c_wr(0xC0);
Delay10KTCYx(5);
d_wr('T');d_wr('O');d_wr(' ');d_wr('S');d_wr('E');d_wr('T');d_wr(' ');d_wr('V');d_wr('O');d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');
c_wr(0x90);
Delay10KTCYx(5);
d_wr(' ');d_wr('S');d_wr('E');d_wr('L');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');d_wr('C');d_wr('O');d_wr('U');d_wr('N');d_wr('T');d_wr(' ');d_wr(' ');d_wr(' ');
c_wr(0xD0);
Delay10KTCYx(5);
d_wr(' ');d_wr('S');d_wr('E');d_wr('T');d_wr(' ');d_wr('C');d_wr('O');d_wr('U');d_wr('N');d_wr('T');d_wr('=');lcd_num_display(count2);
while (((PORTB & 0x0A) != 0x0A))
{
if (PORTBbits.RB0 == 1) 
{ 
	while(PORTBbits.RB0 == 1)
	{	Delay_ms(2);
	}
	 count2 = count2++;  
	 EEpromWrite(&count2,MAX_VAL_LOCATION_28,2);
	c_wr(0xD0);
	delayms(5);
	d_wr(' ');d_wr('S');d_wr('E');d_wr('T');d_wr(' ');d_wr('C');d_wr('O');d_wr('U');d_wr('N');d_wr('T');d_wr('=');lcd_num_display(count2);
	 if (count2 >= min_range28 )
	 {
		 EEpromClear(&count2,MAX_VAL_LOCATION_28,2);
		 count2=0; 
		 
	 }
}

if (((PORTB & 0x08) == 0x08) )
{   
	
	while(((PORTB & 0x08) == 0x08) )
	{	Delay_ms(2);
	}
	count2 = count2--; 
	 EEpromWrite(&count2,MAX_VAL_LOCATION_28,2);
	 c_wr(0xD0);
	delayms(5);
	d_wr(' ');d_wr('S');d_wr('E');d_wr('T');d_wr(' ');d_wr('C');d_wr('O');d_wr('U');d_wr('N');d_wr('T');d_wr('=');lcd_num_display(count2);
	 if (count2 >= min_range28 )
	 {
		 EEpromClear(&count2,MAX_VAL_LOCATION_28,2);
		 count2=0; 
		 
	 }
}
}
NEWHAR();
}

void cal_lux()
{
c_wr(0x01);
Delay10KTCYx(5);
 c_wr(0x80);
Delay10KTCYx(5);
d_wr(' ');d_wr('A');d_wr('V');d_wr('R');d_wr('A');d_wr('G');d_wr('E');d_wr(' ');d_wr('L');d_wr('U');d_wr('X');d_wr('=');
do { 
	EEPROM_Load();
	if(v_sel==1)
	{
		Channel_Read(1);
		Channel_Read(1);
	}
	if(v_sel==0)
	{
		Channel_Read(3);
		Channel_Read(3);
	}
	c_wr(0x8C);
	Delay10KTCYx(5);
	lcd_num_display(adc_avg_mv2);
	tmr_delay(4);
   }
while (((PORTB & 0x0A) != 0x0A));//while (START_KEY!=1);
//send_charCom2('1');
//	send_charCom2('-');
//	serial_display_num(adc_val1_mv);
//	send_charCom2(' ');
//	send_charCom2('2');
//	send_charCom2('-');
//	serial_display_num(adc_val2_mv);
//	send_charCom2(' ');
//	send_charCom2('3');
//	send_charCom2('-');
//	serial_display_num(adc_val3_mv);
//	send_charCom2(' ');
//	send_charCom2('4');
//	send_charCom2('-');
//	serial_display_num(adc_val4_mv);
//	send_charCom2(' ');
//	send_charCom2('5');
//	send_charCom2('-');
//	serial_display_num(adc_val5_mv);
//	send_charCom2(' ');
//	send_charCom2('6');
//	send_charCom2('-');
//	serial_display_num(adc_val6_mv);
//	send_charCom2(' ');
//	send_charCom2('7');
//	send_charCom2('-');
//	serial_display_num(adc_val7_mv);
//	send_charCom2(' ');
//	send_charCom2('8');
//	send_charCom2('-');
//	serial_display_num(adc_val8_mv);
//	send_charCom2(' ');
//	send_charCom2('9');
//	send_charCom2('-');
//	serial_display_num(adc_val9_mv);
//	send_charCom2(' ');
//	send_charCom2('1');
//	send_charCom2('0');
//	send_charCom2('-');
//	serial_display_num(adc_val10_mv);
//	send_charCom2(' ');
//	send_charCom2('1');
//	send_charCom2('1');
//	send_charCom2('-');
//	serial_display_num(adc_val11_mv);
//	send_charCom2(' ');
//	send_charCom2('1');
//	send_charCom2('2');
//	send_charCom2('-');
//	serial_display_num(adc_val12_mv);
//	send_charCom2(' ');
//	send_charCom2('1');
//	send_charCom2('3');
//	send_charCom2('-');
//	serial_display_num(adc_val13_mv);
//	send_charCom2(' ');
//	send_charCom2('1');
//	send_charCom2('4');
//	send_charCom2('-');
//	serial_display_num(adc_val14_mv);
//	send_charCom2(' ');
//	send_charCom2('1');
//	send_charCom2('5');
//	send_charCom2('-');
//	serial_display_num(adc_val15_mv);
//	send_charCom2(' ');
//	send_charCom2('1');
//	send_charCom2('6');
//	send_charCom2('-');
//	serial_display_num(adc_val16_mv);
//	send_charCom2(' ');
//	send_charCom2('1');
//	send_charCom2('7');
//	send_charCom2('-');
//	serial_display_num(adc_val17_mv);
//	send_charCom2(' ');
//	send_charCom2('1');
//	send_charCom2('8');
//	send_charCom2('-');
//	serial_display_num(adc_val18_mv);
//	send_charCom2(' ');
//	send_charCom2('1');
//	send_charCom2('9');
//	send_charCom2('-');
//	serial_display_num(adc_val19_mv);
//	send_charCom2(' ');
//	send_charCom2('2');
//	send_charCom2('0');
//	send_charCom2('-');
//	serial_display_num(adc_val20_mv);
//	send_charCom2(' ');
//	send_charCom2('2');
//	send_charCom2('1');
//	send_charCom2('-');
//	serial_display_num(adc_val21_mv);
//	send_charCom2(' ');
//	send_charCom2('2');
//	send_charCom2('2');
//	send_charCom2('-');
//	serial_display_num(adc_val22_mv);
//	send_charCom2(' ');
//	send_charCom2('2');
//	send_charCom2('3');
//	send_charCom2('-');
//	serial_display_num(adc_val23_mv);
//	send_charCom2(' ');
//	send_charCom2('2');
//	send_charCom2('4');
//	send_charCom2('-');
//	serial_display_num(adc_val24_mv);
//	send_charCom2(' ');
//
//	send_charCom2(' ');
//	send_charCom2('A');
//	send_charCom2('-');
//	serial_display_num(adc_avg_mv2);
NEWHAR();
YELLOW=0;
RED=0;
GREEN=0;
Delay1KTCYx(1); 
RCSTA=0x90;
TXSTA=0x20;
TXSTAbits.TXEN=1;
TRISCbits.RC6=0;
SPBRG=23;
RCSTAbits.SPEN=1;
Delay1KTCYx(2); 
TXREG='*';
while(PIR1bits.TXIF==0);			    
}


void calibration()
{
c_wr(0x01);
Delay10KTCYx(5);
 c_wr(0x80);
Delay10KTCYx(5);
do { 
	EEPROM_Load();
	if(v_sel==1)
	{
		Channel_Read(1);
	}
	if(v_sel==0)
	{
		Channel_Read(3);
	}
	Page_Max();
	tmr_delay(4);
   }
while (((PORTB & 0x0A) != 0x0A));//while (START_KEY!=1);
NEWHAR();
YELLOW=0;
RED=0;
GREEN=0;
Delay1KTCYx(1); 
RCSTA=0x90;
TXSTA=0x20;
TXSTAbits.TXEN=1;
TRISCbits.RC6=0;
SPBRG=23;
RCSTAbits.SPEN=1;
Delay1KTCYx(2); 
TXREG='*';
while(PIR1bits.TXIF==0);			    
}

void keypad_calling()
{

do{
keypad();
}
while (((PORTB & 0x0A) != 0x0A));//while (START_KEY!=1);
			   NEWHAR();
		    
}
void menu_button()
{
c_wr(0x01);
c_wr(0x80);
Delay_ms(20);
d_wr('C');d_wr('H');d_wr('A');d_wr('N');d_wr('N');d_wr('E');d_wr('L');d_wr(' ');d_wr('S');d_wr('E');d_wr('T');d_wr(':');d_wr(':');d_wr('E');d_wr('&');d_wr('S');//d_wr(':');//d_wr('C');d_wr('H');
c_wr(0xC0);
Delay_ms(2);
d_wr('C');d_wr('A');d_wr('L');d_wr('I');d_wr('B');d_wr('R');d_wr('A');d_wr('T');d_wr('I');d_wr('O');d_wr('N');d_wr(':');d_wr(':');d_wr('U');d_wr('&');d_wr('D');//d_wr(' ');
c_wr(0x90);
Delay_ms(2);
d_wr('T');d_wr('U');d_wr('B');d_wr('E');d_wr(' ');d_wr('T');d_wr('A');d_wr('R');d_wr('G');d_wr('E');d_wr('T');d_wr(':');d_wr(':');d_wr('U');d_wr('&');d_wr('S');//d_wr('S');
c_wr(0xD0);

Delay_ms(2);
   d_wr('T');d_wr('O');d_wr(' ');d_wr('E');d_wr('X');d_wr('I');d_wr('T');d_wr(':');d_wr(':');d_wr('S');d_wr('&');d_wr('D');//d_wr('>');//d_wr('E');d_wr('S');//d_wr(' ');

do{
if (((PORTB & 0x09) == 0x09) )
{
calibration();
}
if (((PORTB & 0x03) == 0x03) )
{
cal_lux();
}
if (((PORTB & 0x06) == 0x06) )
{
keypad_calling();
}
}
while (((PORTB & 0x0A) != 0x0A));//while (START_KEY!=1);
			   NEWHAR();
EEPROM_Load();
YELLOW=0;
RED=0;
GREEN=0;

RCSTA=0x90;
	
TXSTA=0x20;
	TXSTAbits.TXEN=1;
	  TRISCbits.RC6=0;
SPBRG=23;
	RCSTAbits.SPEN=1;
//HIGH_BEAM_ON=1;
Delay_ms(2);

	     TXREG='*';
		 while(PIR1bits.TXIF==0);

}
void Channel_Read(unsigned char serial_power_on) 
  {
Delay_ms(2); 
RCSTA=0x90;
	
TXSTA=0x20;
TXSTAbits.TXEN=1;
TRISCbits.RC6=0;
SPBRG=23;
RCSTAbits.SPEN=1;

Delay_ms(2); 
TXREG=serial_power_on;
while(PIR1bits.TXIF==0);

ack=0;
v[5]='NULL';
f_array=1;
	while(ack<56)	
	{
if(RCSTAbits.OERR)
{
RCSTAbits.CREN=0;
RCSTAbits.CREN=1;
}
	
		while(PIR1bits.RCIF==0);
        	v[f_array]=RCREG;	
        	
		if(f_array==4)
		{
		 f_array=1;
		   for(i=1;i<5;i++)
	      	{
		      	if(i==1)
		      	m=v[i]*1000;
		      		if(i==2)
		      	n=v[i]*100;
		      		if(i==3)
		      	o1=v[i]*10;
		      		if(i==4)
		      	p=v[i]*1;
		     }	
if(ack==3)
{
adc_val11_mv=m+n+o1+p;
} 
if(ack==7)
{
adc_val12_mv=m+n+o1+p;
}
if(ack==11)
{
adc_val13_mv=m+n+o1+p;
}
if(ack==15)
{
adc_val14_mv=m+n+o1+p;
}      	   	
if(ack==19)
{
adc_val15_mv=m+n+o1+p;	      
}		      	 
if(ack==23)
{
adc_val16_mv=m+n+o1+p;
}
if(ack==27)
{
adc_val17_mv=m+n+o1+p;
}

if(ack==31)
{
adc_val18_mv=m+n+o1+p;
}
if(ack==35)
{
adc_val19_mv=m+n+o1+p;
}
if(ack==39)
{
adc_val20_mv=m+n+o1+p;
}
if(ack==43)
{
adc_val21_mv=m+n+o1+p;
}
if(ack==47)
{
adc_val22_mv=m+n+o1+p;
}
if(ack==51)
{
 adc_val23_mv=m+n+o1+p;
}
if(ack==55)
{
 adc_val24_mv=m+n+o1+p;
}
		  
		    
		}
		else
     	f_array++;

 c_wr(0x80);
     	ack++;  	
     }ack=0;
	    

	#if 1
	if(toggle_mode == 0)
		{
    #if 0

      lcd_gotoxy(0,0); 
      
			
   #endif

   #if 1
   //ch1
        ADCON0=0x00; //ch1  RA0
        ADCON1=0x05; 
        ADCON0=0x01;       
      
        ADCON0=0x03;

		while((ADCON0&0x02)!=0x00);
        {
        }
         k1=ADRESH;
         m1=ADRESL;
         k1=k1<<8;
         m1=k1|m1;
            
		adc_val1_mv =m1*4.508;
           
 //ch2//
        ADCON0=0x14; //ch2    RE0
        ADCON1=0x05; 
        ADCON0=0x15;
        
        ADCON0=0x17;
  
    	while((ADCON0&0x02)!=0x00);
          {
          }
        k2=ADRESH;
        m2=ADRESL;
        k2=k2<<8;
        m2=k2|m2;
        adc_val2_mv =m2*4.508;
//ch3//

        ADCON0=0x18; // RE1
        ADCON1=0x05; 
        ADCON0=0x19;
        
        ADCON0=0x1B;


	    while((ADCON0&0x02)!=0x00);
       {
          }
       k3=ADRESH;
       m3=ADRESL;
       k3=k3<<8;
       m3=k3|m3;
       adc_val3_mv =m3*4.508;
   
//ch4//
 
       ADCON0=0x50;   //RD0
       ADCON1=0x05; 
       ADCON0=0x51;
        
       ADCON0=0x53;

	   while((ADCON0&0x02)!=0x00);
       {
       }
       k4=ADRESH;
       m4=ADRESL;
       k4=k4<<8;
       m4=k4|m4;
       adc_val4_mv =m4*4.508;

    //ch5//
                
        ADCON0=0x54; //ch5    RD1
        ADCON1=0x05; 
        ADCON0=0x55;
        
        ADCON0=0x57;

        while((ADCON0&0x02)!=0x00);
       {
       }
       k5=ADRESH;
       m5=ADRESL;
       k5=k5<<8;
       m5=k5|m5;
       adc_val5_mv =m5*4.508;


   //ch6//

       ADCON0=0x58; //ch6     RD2
       ADCON1=0x05; 
       ADCON0=0x59;
        
       ADCON0=0x5B;


    	while((ADCON0&0x02)!=0x00);
       {
       }
       k6=ADRESH;
       m6=ADRESL;
       k6=k6<<8;
       m6=k6|m6;
       adc_val6_mv =m6*4.508;

 //ch7//
   
        ADCON0=0x5C; //ch7     RD3
        ADCON1=0x05; 
        ADCON0=0x5D;
       
        ADCON0=0x5F;


		while((ADCON0&0x02)!=0x00);
        {
        }
        k7=ADRESH;
        m7=ADRESL;
        k7=k7<<8;
        m7=k7|m7;
        adc_val7_mv =m7*4.508;


//ch8//
   
       ADCON0=0x60; //ch8     RD4
       ADCON1=0x05; 
       ADCON0=0x61;
        
       ADCON0=0x63;


    	while((ADCON0&0x02)!=0x00);
       {
       }
       k8=ADRESH;
       m8=ADRESL;
       k8=k8<<8;
       m8=k8|m8;
       adc_val8_mv =m8*4.508;

//ch9//
   
       ADCON0=0x64; //ch9     RD5
       ADCON1=0x05; 
       ADCON0=0x65;
        
       ADCON0=0x67;

       while((ADCON0&0x02)!=0x00);
      {
      }
      k9=ADRESH;
      m9=ADRESL;
      k9=k9<<8;
      m9=k9|m9;
      adc_val9_mv =m9*4.508;


		ADCON0=0x40;    //ch13      RC4
        ADCON1=0x05; 
        ADCON0=0x41;
        
        ADCON0=0x43;


	   while((ADCON0&0x02)!=0x00);
       {
       }
       k13=ADRESH;
       m13=ADRESL;
       k13=k13<<8;
       m13=k13|m13;
       adc_val10_mv =m13*4.508;
 adc_avg_mv1= ((adc_val1_mv+adc_val2_mv+adc_val3_mv+adc_val4_mv+adc_val5_mv+adc_val6_mv+adc_val7_mv+adc_val8_mv+adc_val9_mv+adc_val10_mv+adc_val11_mv+adc_val12_mv+adc_val13_mv+adc_val14_mv+adc_val15_mv+adc_val16_mv+adc_val17_mv+adc_val18_mv+adc_val19_mv+adc_val20_mv+adc_val21_mv+adc_val22_mv+adc_val23_mv+adc_val24_mv));
 adc_avg_mv2=adc_avg_mv1*0.04166;
 adc_avg_mv=adc_avg_mv2*0.04166; 
     
#endif

switch(page_index)
			{

			default:
				Page_1();
			break;
			}
			
    low_index = 0;
	high_index = 0;
       for(k=0;k<24;k++)
			{
				
				if(Status_buffer[k] == 1)
				{
					low_index++;
				}
				else if(Status_buffer[k] == 2)
				{
					high_index++;
				}
				else
				{

				}
            }
            
            
			    
		   	if(low_index > high_index)
				{
				
g=0;            
   	          f=2;
r=0;
tube_24_flag=1;
                 }
			else if(low_index < high_index)
		       {
					 
				   
g=0;
	r=2;
f=0;
tube_24_flag=2;
		       }
							
           	else if((low_index == 0) && (high_index == 0))
		      {
					
g=2;
f=0;
r=0;     
tube_24_flag=1;
    
              }
			else if((low_index == high_index)&& (low_index !=0) && (high_index!=0))
				{g=0;
r=2;
f=2;
					
                 
tube_24_flag=2;
                 
			}
              

				else
				{
			 
				}
       

//			}
        }
		 else
		 {

		 }
	 #endif
	        
 }   
        
     
     
 
    
       	

void keypad(void)
{

	
 if((PORTB & 0x0F) != 0x00)
	{
        delay(5);

		if((PORTB & 0x0F) != 0x00)      //0x00 no key press
		{
		    keypress= PORTB & 0x0F;
	
				switch(keypress)
				{

		   case KEY_1:
                    
					if((toggle_mode >= 1) && (toggle_mode <= 48))
					{
						incridigit();
						
					}
          
			        else if(toggle_mode == 0)
					{
						page_index++;
						if(page_index > 3)
						{
							page_index = 1;
						}
					}
					
					else
					{

					}

					break;
              


      case KEY_4:

					if((toggle_mode >= 1) && (toggle_mode <= 48))
					{

						decridigit();
						
					}
					else if(toggle_mode == 0)
					{
						if(page_index <4)
						{
							page_index = 4;
						}
						else
						{
							page_index ++;
						}
						if(page_index >5)
						{
							page_index = 4;
						}


					}
					else
					{

					}

					break;




       case KEY_2:
					if((toggle_mode >= 1) && (toggle_mode <= 48))
					{
				        
						movepasscur();
						
					}

					else
					{

					}

					break;



         case KEY_3:
				toggle_mode =  toggle_mode+1;
					if(toggle_mode == 49)
					{
                        max_range24 = range;
						EEpromWrite(&max_range24 ,MAX_VAL_LOCATION_24, 2);

                        toggle_mode = 0;
					}
                     
					if(toggle_mode == 1)
					{
					    line = 1;
		                range = min_range1;
					    set_min(min_range1,max_range1,1);
                        
					}
                   
					if(toggle_mode ==2)
					{
					    line = 2;
		                min_range1 = range;	 
					    EEpromWrite(&min_range1 ,MIN_VAL_LOCATION_1, 2);

                        range = max_range1;
						set_max(min_range1,max_range1,1);
					}

					if(toggle_mode == 3)
					{
					     line = 1;
						 max_range1 = range;
					   	 EEpromWrite(&max_range1 ,MAX_VAL_LOCATION_1, 2);

		                 range = min_range2;
						 set_min(min_range2,max_range2,2);
					}

					if(toggle_mode == 4)
					{
						 line = 2;
						 min_range2 = range;
						 EEpromWrite(&min_range2 ,MIN_VAL_LOCATION_2, 2);

                         range = max_range2;
						 set_max(min_range2,max_range2,2);
					}

					if(toggle_mode == 5)
					{
					   line = 1;
					   max_range2 = range;
				       EEpromWrite(&max_range2 ,MAX_VAL_LOCATION_2, 2);

		               range = min_range3;
					    set_min(min_range3,max_range3,3);
					}

					if(toggle_mode == 6)
					{
						  line = 2;
						  min_range3 = range;
						  EEpromWrite(&min_range3 ,MIN_VAL_LOCATION_3, 2);

                          range = max_range3;
						  set_max(min_range3,max_range3,3);

					}

					if(toggle_mode == 7)
					{
						 line = 1;
						 max_range3 = range;
						 EEpromWrite(&max_range3 ,MAX_VAL_LOCATION_3, 2);

		                 range = min_range4;						
						 set_min(min_range4,max_range4,4);
					}

					if(toggle_mode == 8)
					{
						line = 2;
						min_range4 = range;
					    EEpromWrite(&min_range4 ,MIN_VAL_LOCATION_4, 2);

                         range = max_range4;
						 set_max(min_range4,max_range4,4);
					}

					if(toggle_mode == 9)
					{
						  line = 1;
					      max_range4 = range;
				       	  EEpromWrite(&max_range4 ,MAX_VAL_LOCATION_4, 2);

		                  range = min_range5;
						  set_min(min_range5,max_range5,5);
					}

					if(toggle_mode == 10)
					{
						  line = 2;
						  min_range5 = range;
					 	  EEpromWrite(&min_range5 ,MIN_VAL_LOCATION_5, 2);

                          range = max_range5;
						  set_max(min_range5,max_range5,5);

					}

					if(toggle_mode == 11)
					{
						 line = 1;
						 max_range5 = range;
					     EEpromWrite(&max_range5 ,MAX_VAL_LOCATION_5, 2);

		                 range = min_range6;
						 set_min(min_range6,max_range6,6);
					}

					if(toggle_mode == 12)
					{
						  line = 2;
						  min_range6 = range;
						  EEpromWrite(&min_range6 ,MIN_VAL_LOCATION_6, 2);

                          range = max_range6;
						  set_max(min_range6,max_range6,6);
					}

		        	if(toggle_mode == 13)
					{
						 line = 1;
						 max_range6 = range;
						 EEpromWrite(&max_range6 ,MAX_VAL_LOCATION_6, 2);

		                 range = min_range7;
						set_min(min_range7,max_range7,7);
					}

					if(toggle_mode == 14)
					{
						line = 2;
						min_range7 = range;
						EEpromWrite(&min_range7 ,MIN_VAL_LOCATION_7, 2);
                        range = max_range7;
						set_max(min_range7,max_range7,7);
					}

					if(toggle_mode == 15)
					{
						 line = 1;
						 max_range7 = range;
						 EEpromWrite(&max_range7 ,MAX_VAL_LOCATION_7, 2);

		                range = min_range8;
						set_min(min_range8,max_range8,8);
					}

					if(toggle_mode == 16)
					{
						 line = 2;
						 min_range8 = range;
						  EEpromWrite(&min_range8 ,MIN_VAL_LOCATION_8, 2);
                          range = max_range8;
						  set_max(min_range8,max_range8,8);
					}

					if(toggle_mode == 17)
					{
						 line = 1;
						 max_range8 = range;
						 EEpromWrite(&max_range8 ,MAX_VAL_LOCATION_8, 2);

		                 range = min_range9;
						 set_min(min_range9,max_range9,9);
					}

					if(toggle_mode == 18)
					{
						line = 2;
						min_range9 = range;
					   	EEpromWrite(&min_range9 ,MIN_VAL_LOCATION_9, 2);
                        range = max_range9;
						set_max(min_range9,max_range9,9);

					}

					if(toggle_mode == 19)
					{
						line = 1;
						max_range9 = range;
						EEpromWrite(&max_range9 ,MAX_VAL_LOCATION_9, 2);

	                	range = min_range10;
						set_min(min_range10,max_range10,10);
						
						
					}

				if(toggle_mode == 20)
					{
						line = 2;
						min_range10 = range;
						EEpromWrite(&min_range10 ,MIN_VAL_LOCATION_10, 2);

                        range = max_range10;
						set_max(min_range10,max_range10,10);
					}

					if(toggle_mode == 21)
					{
						 line = 1;
						 max_range10 = range;
						 EEpromWrite(&max_range10 ,MAX_VAL_LOCATION_10, 2);

		                range = min_range11;
						set_min(min_range11,max_range11,11);
					}

					if(toggle_mode == 22)
					{
						 line = 2;
						 min_range11 = range;
					   	 EEpromWrite(&min_range11 ,MIN_VAL_LOCATION_11, 2);

                        range = max_range11;
						set_max(min_range11,max_range11,11);

					}

					if(toggle_mode == 23)
					{
						 line = 1;
						 max_range11 = range;
						 EEpromWrite(&max_range11 ,MAX_VAL_LOCATION_11, 2);

		                range = min_range12;
						set_min(min_range12,max_range12,12);
					}

					if(toggle_mode == 24)
					{
						  line = 2;
						  min_range12 = range;
						  EEpromWrite(&min_range12 ,MIN_VAL_LOCATION_12, 2);

                         range = max_range12;
						 set_max(min_range12,max_range12,12);
					}

					if(toggle_mode == 25)
					{
						 line = 1;
						 max_range12 = range;
						 EEpromWrite(&max_range12 ,MAX_VAL_LOCATION_12, 2);

	                 	range = min_range13;
						set_min(min_range13,max_range13,13);
					}

					if(toggle_mode == 26)
					{
						  line = 2;
						  min_range13 = range;
					   	  EEpromWrite(&min_range13 ,MIN_VAL_LOCATION_13, 2);

                          range = max_range13;
					      set_max(min_range13,max_range13,13);

					}

					if(toggle_mode == 27)
					{
						 line = 1;
						 max_range13 = range;
						 EEpromWrite(&max_range13 ,MAX_VAL_LOCATION_13, 2);

		                 range = min_range14;
					     set_min(min_range14,max_range14,14);

					}

					if(toggle_mode == 28)
					{
						 line = 2;
						 min_range14 = range;
						 EEpromWrite(&min_range14 ,MIN_VAL_LOCATION_14, 2);

                         range = max_range14;
						 set_max(min_range14,max_range14,14);

					}

					if(toggle_mode == 29)
					{
						 line = 1;
						 max_range14 = range;
						 EEpromWrite(&max_range14 ,MAX_VAL_LOCATION_14, 2);

		                 range = min_range15;
						 set_min(min_range15,max_range15,15);

					}

					if(toggle_mode == 30)
					{
						 line = 2;
						 min_range15 = range;
						 EEpromWrite(&min_range15 ,MIN_VAL_LOCATION_15, 2);

                         range = max_range15;
						 set_max(min_range15,max_range15,15);

					}

					if(toggle_mode == 31)
					{
						 line = 1;
						 max_range15 = range;
						 EEpromWrite(&max_range15 ,MAX_VAL_LOCATION_15, 2);

		                 range = min_range16;
						 set_min(min_range16,max_range16,16);
					}

					if(toggle_mode == 32)
					{
					     line = 2;
						 min_range16 = range;
						 EEpromWrite(&min_range16 ,MIN_VAL_LOCATION_16, 2);

                         range = max_range16;
						 set_max(min_range16,max_range16,16);
					}
		        	if(toggle_mode == 33)
					{ 
							line = 1;
						 max_range16 = range;
						EEpromWrite(&max_range16 ,MAX_VAL_LOCATION_16, 2);

		                 range = min_range17;
						set_min(min_range17,max_range17,17);
					}

					if(toggle_mode == 34)
					{
						line = 2;
						min_range17 = range;
						EEpromWrite(&min_range17 ,MIN_VAL_LOCATION_17, 2);

                        range = max_range17;
						set_max(min_range17,max_range17,17);
					}

					if(toggle_mode == 35)
					{
						 line = 1;
						 max_range17 = range;
						 EEpromWrite(&max_range17 ,MAX_VAL_LOCATION_17, 2);

		                range = min_range18;
						set_min(min_range18,max_range18,18);
					}

					if(toggle_mode == 36)
					{
						 line = 2;
						 min_range18 = range;
						  EEpromWrite(&min_range18 ,MIN_VAL_LOCATION_18, 2);
                          range = max_range18;
						  set_max(min_range18,max_range18,18);
					}

					if(toggle_mode == 37)
					{
						 line = 1;
						 max_range18 = range;
						 EEpromWrite(&max_range18 ,MAX_VAL_LOCATION_18, 2);

		                 range = min_range19;
						 set_min(min_range19,max_range19,19);
					}

					if(toggle_mode == 38)
					{
						line = 2;
						min_range19 = range;
					   	EEpromWrite(&min_range19 ,MIN_VAL_LOCATION_19, 2);
                        range = max_range19;
						set_max(min_range19,max_range19,19);

					}

					if(toggle_mode == 39)
					{
						line = 1;
						max_range19 = range;
						EEpromWrite(&max_range19 ,MAX_VAL_LOCATION_19, 2);

	                	range = min_range20;
						set_min(min_range20,max_range20,20);
						
						
					}

				if(toggle_mode == 40)
					{
						line = 2;
						min_range20 = range;
						EEpromWrite(&min_range20 ,MIN_VAL_LOCATION_20, 2);

                        range = max_range20;
						set_max(min_range20,max_range20,20);
					}

					if(toggle_mode == 41)
					{
						 line = 1;
						 max_range20 = range;
						 EEpromWrite(&max_range20 ,MAX_VAL_LOCATION_20, 2);

		                range = min_range21;
						set_min(min_range21,max_range21,21);
					}

					if(toggle_mode == 42)
					{
						 line = 2;
						 min_range21 = range;
					   	 EEpromWrite(&min_range21 ,MIN_VAL_LOCATION_21, 2);

                        range = max_range21;
						set_max(min_range21,max_range21,21);

					}

					if(toggle_mode == 43)
					{
						 line = 1;
						 max_range21 = range;
						 EEpromWrite(&max_range21 ,MAX_VAL_LOCATION_21, 2);

		                range = min_range22;
						set_min(min_range22,max_range22,22);
					}

					if(toggle_mode == 44)
					{
						  line = 2;
						  min_range22 = range;
						  EEpromWrite(&min_range22 ,MIN_VAL_LOCATION_22, 2);

                         range = max_range22;
						 set_max(min_range22,max_range22,22);
					}

					if(toggle_mode == 45)
					{
						 line = 1;
						 max_range22 = range;
						 EEpromWrite(&max_range22 ,MAX_VAL_LOCATION_22, 2);

	                 	range = min_range23;
						set_min(min_range23,max_range23,23);
					}

					if(toggle_mode == 46)
					{
						  line = 2;
						  min_range23 = range;
					   	  EEpromWrite(&min_range23 ,MIN_VAL_LOCATION_23, 2);

                          range = max_range23;
					      set_max(min_range23,max_range23,23);

					}

					if(toggle_mode == 47)
					{
						 line = 1;
						 max_range23 = range;
						 EEpromWrite(&max_range23 ,MAX_VAL_LOCATION_23, 2);

		                 range = min_range24;
					     set_min(min_range24,max_range24,24);

					}

					if(toggle_mode == 48)
					{
						 line = 2;
						 min_range24 = range;
						 EEpromWrite(&min_range24 ,MIN_VAL_LOCATION_24, 2);

                         range = max_range24;
						 set_max(min_range24,max_range24,24);

                         max_range24 = range;
					 	 EEpromWrite(&max_range24 ,MAX_VAL_LOCATION_24, 2);

					}


					


					break;

				default:
					break;
				}
		}
	}
	else
	{
	
	}



}

//********************FOR TUBE VOLTAGE**************************
void keypad1(void)
{

	
 if((PORTB & 0x0F) != 0x00)
	{
        delay(5);

		if((PORTB & 0x0F) != 0x00)      //0x00 no key press
		{
		    keypress= PORTB & 0x0F;
	
				switch(keypress)
				{

		   case KEY_1:
                    
					if((toggle_mode >= 1) && (toggle_mode <= 48))
					{
						incridigit();
						
					}
          
			        else if(toggle_mode == 0)
					{
						page_index++;
						if(page_index > 3)
						{
							page_index = 1;
						}
					}
					
					else
					{

					}

					break;
              


      case KEY_4:

					if((toggle_mode >= 1) && (toggle_mode <= 48))
					{

						decridigit();
						
					}
					else if(toggle_mode == 0)
					{
						if(page_index <4)
						{
							page_index = 4;
						}
						else
						{
							page_index ++;
						}
						if(page_index >5)
						{
							page_index = 4;
						}


					}
					else
					{

					}

					break;




       case KEY_2:
					if((toggle_mode >= 1) && (toggle_mode <= 48))
					{
				        
						movepasscur();
						
					}

					else
					{

					}

					break;



         case KEY_3:
				toggle_mode =  toggle_mode+1;
					if(toggle_mode == 3)
					{
                        max_range24 = range;
						EEpromWrite(&max_range24 ,MAX_VAL_LOCATION_24, 2);

                        toggle_mode = 0;
					}
                     
					if(toggle_mode == 1)
					{
					    line = 1;
		                range = min_range26;
					    set_min(min_range26,max_range26,1);
                        
					}
                   
					if(toggle_mode ==2)
					{
					    line = 2;
		                min_range26 = range;	 
					    EEpromWrite(&min_range26 ,MIN_VAL_LOCATION_26, 2);

					}

					

					break;

				default:
					break;
				}
		}
	}
	else
	{
	
	}



}




//*********************************
void timepass(unsigned int count)
{
	unsigned int i,j;
	for(i = 0;i<count;i++)
	{
		for(j=0;j<10;j++)
		{
			;
		}
	}

}






void incridigit()
{


	UP_cntr[cnt_digit]++;
	if(UP_cntr[cnt_digit]>9)
	{
		UP_cntr[cnt_digit]=9;
	}


	    lcd_gotoxy(line,8);                  
	range = UP_cntr[0]*1000+UP_cntr[1]*100+UP_cntr[2]*10+UP_cntr[3];

	if(range < 0)
	{
		UP_cntr[cnt_digit]--;
	}
	if(range > 5000)
	{
		UP_cntr[cnt_digit]--;
	}
	range = UP_cntr[0]*1000+UP_cntr[1]*100+UP_cntr[2]*10+UP_cntr[3];
    lcd_num_display(range);
Delay1KTCYx(1000);
}

void decridigit()
{

	// lcdGotoXY(8,1);

	UP_cntr[cnt_digit]--;
	if(UP_cntr[cnt_digit]<0)
	{
		UP_cntr[cnt_digit]=0;
	}

   
	    lcd_gotoxy(line,8); //lcdGotoXY(8,line);
	range = UP_cntr[0]*1000+UP_cntr[1]*100+UP_cntr[2]*10+UP_cntr[3];
	if(range < 0 )
	{
		UP_cntr[cnt_digit]++;
	}
	if(range > 5000)
	{
		UP_cntr[cnt_digit]++;
	}
	range = UP_cntr[0]*1000+UP_cntr[1]*100+UP_cntr[2]*10+UP_cntr[3];
   lcd_num_display(range);
Delay1KTCYx(1000);

}


void movepasscur()
{
 Delay1KTCYx(500);
lcd_gotoxy(line,cnt_digit+8);
    
   cnt_digit++; 
 //	c_wr(0x0E);
	if(cnt_digit > 3)
     cnt_digit = 0;
	
}



void set_min(unsigned int min,unsigned int max,unsigned char ch)
{
	unsigned int temp,temp2,temp3;

                              c_wr(0x01);
Delay10KTCYx(5);
                              c_wr(0x80);
Delay10KTCYx(5);
d_wr('S');d_wr('E');d_wr('T');d_wr(' ');d_wr('M');d_wr('O');d_wr('D');d_wr('E');d_wr(' ');d_wr('C');d_wr('H');

							  
							
		                  if(ch <10)
							  {
							   d_wr(ch+0x30);
							  }
							  else if(ch <20)
							  {
								  temp2 = ch%10;
								   d_wr('1');
								  // temp2 = ch/10;
								    d_wr(temp2+0x30);
							  }	                              //DISPLAY CH number
							else 							  {
								  temp3 = ch%10;
								   d_wr('2');
								  // temp2 = ch/10;
								    d_wr(temp3+0x30);
							  }
							  

							 			  
                              c_wr(0xC0);  
Delay10KTCYx(3);        
           d_wr('M');d_wr('I');d_wr('N');d_wr(' ');d_wr('V');d_wr('A');d_wr('L');d_wr(':');
                               lcd_num_display(min);
                              d_wr('m');
                              d_wr('v');
                              d_wr('<');
                              d_wr('-');
                              c_wr(0x90);
Delay10KTCYx(100);  
           d_wr('M');d_wr('A');d_wr('X');d_wr(' ');d_wr('V');d_wr('A');d_wr('L');d_wr(':');
                              lcd_num_display(max);
                               d_wr('m');
                               d_wr('v');

                              cnt_digit = 0;
                              UP_cntr[0] = min/1000;
                              temp = min%1000;
                              UP_cntr[1] = temp/100;
                              temp = temp%100;
                              UP_cntr[2] = temp/10;
                              UP_cntr[3] = temp%10;
Delay1KTCYx(1000);

}


void set_max(unsigned int min,unsigned int max,unsigned char ch)
{
    	unsigned int temp,temp2, temp3;
	    c_wr(0x01);
Delay10KTCYx(5);
	    c_wr(0x80);
Delay10KTCYx(5);
   d_wr('S');d_wr('E');d_wr('T');d_wr(' ');d_wr('M');d_wr('O');d_wr('D');d_wr('E');d_wr(' ');d_wr('C');d_wr('H');


         
                    if(ch <10)
							  {
							   d_wr(ch+0x30);
							  }
							  else if(ch <20)
							  {
								  temp2 = ch%10;
								   d_wr('1');
								  // temp2 = ch/10;
								    d_wr(temp2+0x30);
							  }	                              //DISPLAY CH number
							else 							  {
								  temp3 = ch%10;
								   d_wr('2');
								  // temp2 = ch/10;
								    d_wr(temp3+0x30);
							  }                        //DISPLAY CH number
							  


                    c_wr(0xC0);  
Delay10KTCYx(5);      
     d_wr('M');d_wr('I');d_wr('N');d_wr(' ');d_wr('V');d_wr('A');d_wr('L');d_wr(':');
	              lcd_num_display(min);
	              d_wr('m');
	              d_wr('v');
               	  c_wr(0x90);
Delay10KTCYx(5);
     d_wr('M');d_wr('A');d_wr('X');d_wr(' ');d_wr('V');d_wr('A');d_wr('L');d_wr(':');
                 lcd_num_display(max);
	             d_wr('m');
	             d_wr('v');
	             d_wr('<');
	             d_wr('-');

	cnt_digit = 0;
	UP_cntr[0] = max/1000;
	temp = max%1000;
	UP_cntr[1] = temp/100;
	temp = temp%100;
	UP_cntr[2] = temp/10;
	UP_cntr[3] = temp%10;
Delay1KTCYx(1000);
}



void keypad_set(void)
{

 if((PORTB & 0x0F) != 0x00)
	{
        delay(1);

		if((PORTB & 0x0F) != 0x00)      //0x00 no key press
		{
		    keypress= PORTB & 0x0F;
	

				switch(keypress)
				{

		   case KEY_1:
                    
					if((set_mode>= 1) || (set_mode <= 3))
					{
						incridigit_set();
						
					}
          
			       					
					else
					{

					}

					break;
              


      case KEY_4:

					if((set_mode >= 1) || (set_mode <= 3))
					{

						decridigit_set();
						
					}
				
					else
					{

					}

					break;




       case KEY_2:
					if((set_mode >= 1) || (set_mode <= 3))
					{
				        
						movepasscur_set();
						
					}

					else
					{

					}

					break;



         case KEY_3:
				set_mode =  set_mode+1;
					if(set_mode >= 4)
					{   
						line = 3;
 						  min_range26 = range_set;
					   	 EEpromWrite(&min_range26 ,MIN_VAL_LOCATION_26, 2);
set_min_count(min_range25,min_range26,2);

					}
                     
					if(set_mode == 1)
					{
					    line = 1;
		                range_set = min_range25;
					    set_max_count(min_range25,min_range26,2);
                        min_range25 = range_set;
					   	 EEpromWrite(&min_range25 ,MIN_VAL_LOCATION_25, 2);
                        
					}
                   
					if(set_mode ==2)
					{
 						min_range25 = range_set;
					   	 EEpromWrite(&min_range25 ,MIN_VAL_LOCATION_25, 2);	
							line = 3;					
		               range_set = min_range26;
					    set_min_count(min_range25,min_range26,2);

                        min_range26 = range_set;
					   	 EEpromWrite(&min_range26 ,MIN_VAL_LOCATION_26, 2);

                     	}
					if(set_mode == 3)
					{
					     line = 3;
						  min_range26 = range_set;
					   	 EEpromWrite(&min_range26 ,MIN_VAL_LOCATION_26, 2);
						set_min_count(min_range25,min_range26,2);
		             }

					break;

				default:
					break;
				}
		}
	}
	else
	{
	
	}



}

void incridigit_set()
{


	UP_cntr[cnt_digit]++;
	if(UP_cntr[cnt_digit]>9)
	{
		UP_cntr[cnt_digit]=9;
	}


	    lcd_gotoxy(line,8);                  
range_set = UP_cntr[0]*1000+UP_cntr[1]*100+UP_cntr[2]*10+UP_cntr[3];

	if(range_set < 0)
	{
		UP_cntr[cnt_digit]--;
	}
	if(range_set > 9999)
	{
		UP_cntr[cnt_digit]--;
	}
	range_set = UP_cntr[0]*1000+UP_cntr[1]*100+UP_cntr[2]*10+UP_cntr[3];
    lcd_num_display(range_set);
Delay1KTCYx(1000);

}

void decridigit_set()
{

	// lcdGotoXY(8,1);

	UP_cntr[cnt_digit]--;
	if(UP_cntr[cnt_digit]<0)
	{
		UP_cntr[cnt_digit]=0;
	}

   
	    lcd_gotoxy(line,8); //lcdGotoXY(8,line);
	range_set = UP_cntr[0]*1000+UP_cntr[1]*100+UP_cntr[2]*10+UP_cntr[3];
	if(range_set < 0 )
	{
		UP_cntr[cnt_digit]++;
	}
	if(range_set > 9999)
	{
		UP_cntr[cnt_digit]++;
	}
	range_set = UP_cntr[0]*1000+UP_cntr[1]*100+UP_cntr[2]*10+UP_cntr[3];
   lcd_num_display(range_set);
Delay1KTCYx(1000);

}


void 	movepasscur_set()
{
 Delay1KTCYx(500);
lcd_gotoxy(line,cnt_digit+8);
    
   cnt_digit++; 
 //	c_wr(0x0E);
	if(cnt_digit > 3)
     cnt_digit = 0;
	
}


void set_max_count(unsigned int min,unsigned int max,unsigned char ch)
{
    	unsigned int temp,temp2;
	    c_wr(0x01);
Delay10KTCYx(5);
	    c_wr(0x80);
Delay10KTCYx(5);
      d_wr('S');d_wr('E');d_wr('T');d_wr('T');d_wr('I');d_wr('N');d_wr('G');d_wr('S');d_wr(':');d_wr(':');


                    c_wr(0xC0); 
Delay10KTCYx(5);  
     d_wr('T');d_wr('A');d_wr('R');d_wr('G');d_wr('E');d_wr('T');d_wr(' ');d_wr(':');
	              lcd_num_display(min_range25);
	                           d_wr('<');
	             d_wr('-');
c_wr(0x94);   
  Delay10KTCYx(5);  
     d_wr('P');d_wr('R');d_wr('E');d_wr('S');d_wr('S');d_wr(' ');d_wr('"');d_wr('M');d_wr('E');d_wr('N');d_wr('U');d_wr('"');//d_wr('');
Delay10KTCYx(5);
               	 c_wr(0xD0);
//lcd_gotoxy(2,0);
Delay10KTCYx(5);
   d_wr('R');d_wr('E');d_wr('S');d_wr('E');d_wr('R');d_wr('V');d_wr('E');d_wr(':');
                lcd_num_display(min_range26);
	           	             d_wr('<');
	             d_wr('-');

	cnt_digit = 0;
	UP_cntr[0] = min/1000;
	temp = min%1000;
	UP_cntr[1] = temp/100;
	temp = temp%100;
	UP_cntr[2] = temp/10;
	UP_cntr[3] = temp%10;
Delay1KTCYx(1000);
}
void set_min_count(unsigned int min,unsigned int max,unsigned char ch)
{
    	unsigned int temp,temp2;
	    c_wr(0x01);
Delay10KTCYx(5);
	    c_wr(0x80);
Delay10KTCYx(5);
      d_wr('S');d_wr('E');d_wr('T');d_wr('T');d_wr('I');d_wr('N');d_wr('G');d_wr('S');d_wr(':');d_wr(':');

                    c_wr(0xC0);   
    
     d_wr('T');d_wr('A');d_wr('R');d_wr('G');d_wr('E');d_wr('T');d_wr(' ');d_wr(':');
	              lcd_num_display(min_range25);
	                             d_wr('<');
	             d_wr('-');

c_wr(0x94);   
  Delay10KTCYx(5);  
     d_wr('P');d_wr('R');d_wr('E');d_wr('S');d_wr('S');d_wr(' ');d_wr('"');d_wr('M');d_wr('E');d_wr('N');d_wr('U');d_wr('"');//d_wr('');
Delay10KTCYx(5);
            	 c_wr(0xD0);
//lcd_gotoxy(2,0);
Delay10KTCYx(5);
    d_wr('1');d_wr('5');d_wr('V');d_wr(' ');d_wr('V');d_wr('A');d_wr('R');d_wr(':');
                lcd_num_display(min_range26);
	             d_wr('<');
	             d_wr('-');

	cnt_digit = 0;
	UP_cntr[0] = max/1000;
	temp = max%1000;
	UP_cntr[1] = temp/100;
	temp = temp%100;
	UP_cntr[2] = temp/10;
	UP_cntr[3] = temp%10;
Delay1KTCYx(1000);
EEpromWrite(&min_range26 ,MIN_VAL_LOCATION_26, 2);
EEPROM_Load();						
}



void delayms(unsigned int b)
{

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

void START()
{ 			
			if(v_sel==1)
			{	
				GREEN=0;
				SW=1;
				if (SW==1)
				{
				c_wr(0x01); 
				Delay_ms(10);
				c_wr(0x80);
				Delay_ms(20);
				d_wr('T'); d_wr('E');d_wr('S'); d_wr('T');	d_wr(' '); d_wr('S'); d_wr('W');d_wr(' '); d_wr('P'); d_wr('R'); d_wr('E'); d_wr('S'); d_wr('S'); d_wr('E'); d_wr('D');
				Delay_ms(100);
				for(power_argument=1;power_argument<11;power_argument++)
					{
						Delay_ms(200);
						SW=0; 
						//CHKST();
						HARREJ =0;
						RED =0;
						Delay_ms(50);


					 if(power_argument==1)
						{
						Delay_ms(200);
						Channel_Read(power_argument);
						Delay_ms(20);
						current_read();
						serial_display_A(x11);
						v12_chk();
						}
				
					else if(power_argument==5)
						{
						Delay_ms(200);
						Channel_Read(1);
						Delay_ms(20);
						Channel_Read(1);
						serial_display_mv(adc_avg_mv2);
						v12_chk();
						}
						
				else if(power_argument==2)
						{
						Delay_ms(200);
						c_wr(0x01);
						Delay_ms(10);
						c_wr(0x80); 
						Delay_ms(100);	
						d_wr(' ');d_wr(' ');  d_wr('D'); d_wr('I'); d_wr('S'); d_wr('-');d_wr('C'); 
						d_wr('N'); d_wr('T'); d_wr(' ');d_wr('T'); d_wr('E'); d_wr('S');d_wr('T');d_wr(' '); d_wr(' ');
						
						EEpromRead(&count2,MAX_VAL_LOCATION_28,2);
						EEpromRead(&min_range28,MIN_VAL_LOCATION_28,2);

//						if(count2==0000)
				//		{
							Channel_Read('A');
							Delay_ms(800);
							if(tube_24_flag==2)
							{	
								voltage_read();
								//serial_display(x);
							//	v_OK_DISP();
								
								
							}
							else
							{
						    v_NGD_DISP();
							delayms(2);
							}

							Channel_Read('B');
							Delay_ms(800);
							if(tube_24_flag==2)
							{
								if(final_cheak_tube<3)
								{
								voltage_read();
								serial_display(x);
								v_OKD_DISP();
								Delay_ms(200);
								}
							}
							else
							{
						    v_NGD_DISP();
							delayms(2);
							}
							Channel_Read('C');
							Delay_ms(800);
							if(tube_24_flag==2)
							{
								if(final_cheak_tube<3)
								{
								voltage_read();
								serial_display(x);
								v_OKD_DISP();
								Delay_ms(200);
								}
							}
							else
							{
						    v_NGD_DISP();
							delayms(2);
							}

							Channel_Read('D');
							Delay_ms(800);
							if(tube_24_flag==2)
							{
								if(final_cheak_tube<3)
								{
								voltage_read();
								serial_display(x);
								v_OKD_DISP();
								Delay_ms(800);
								}
							}
							else
							{
						    v_NGD_DISP();
							delayms(2);
							}


							Channel_Read('E');
							Delay_ms(800);
							if(tube_24_flag==2)
							{
								if(final_cheak_tube<3)
								{
								voltage_read();
								serial_display(x);
								v_OKD_DISP();
								Delay_ms(200);
								}
							}
							else
							{
						    v_NGD_DISP();
							delayms(2);
							}

						Channel_Read('F');
							Delay_ms(800);
							if(tube_24_flag==2)
							{
								if(final_cheak_tube<3)
								{
								voltage_read();
								serial_display(x);
								Delay_ms(200);
								}
							}
							else
							{
								if(final_cheak_tube<2)
								{
								}
								else
								{
								RED=1;
								Delay_ms(200);
								RED=1;
								v_NGD_DISP();
								delayms(2);
								power_argument=11;
								while(START_KEY!=0)
								{
							 		Delay_ms(2);
								}
								FCT=7-final_cheak_tube;
								for(F_FCT=1;F_FCT<FCT;F_FCT++)
								{
										send_charCom2('0');
										send_charCom2('0');
										send_charCom2('0');
										send_charCom2('0');
										send_charCom2('0');
								}
									send_charCom2('J');
									send_charCom2('O');
									send_charCom2('B');
									send_charCom2('N');
									send_charCom2('G');
									serial_display(count);
									final_cheak_tube=0;
									FCT=0;
									F_FCT=0;
								
								}						
							}
						
					//	}
						
//					else
//						{
//						delay(10);
//						c_wr(0x01);
//						Delay_ms(10);
//						c_wr(0x80); 
//						Delay_ms(100);		
//						d_wr('1'); d_wr('5'); d_wr('V');d_wr(' '); d_wr('P'); d_wr('O'); d_wr('W'); d_wr('E'); d_wr('R');d_wr(' '); 
//						d_wr('S'); d_wr('U'); d_wr('P');d_wr('P'); d_wr('L'); d_wr('Y');
//						c_wr(0xc0);
//						d_wr(' '); d_wr('N'); d_wr('O');d_wr('T'); d_wr(' '); d_wr('S'); d_wr('E'); d_wr('T'); d_wr(' ');d_wr('D'); 
//						d_wr('E'); d_wr('F'); d_wr('O');d_wr('U'); d_wr('L'); d_wr('T');
//						c_wr(0x90);
//						d_wr(' '); d_wr('S'); d_wr('E');d_wr('T'); d_wr(' '); d_wr('1'); d_wr('5'); d_wr('.'); d_wr('9');d_wr('V'); 
//						d_wr(' '); d_wr('T'); d_wr('E');d_wr('S'); d_wr('T'); d_wr(' ');
//
//						Channel_Read('F');
//							Delay_ms(200);
//						voltage_read();
//							if(tube_24_flag==2)
//							{
//								if(final_cheak_tube<3)
//								{
//								serial_display(x);
//								final_cheak_tube++;
//								Delay_ms(20);
//								}
//							}
//							else
//							{
//								if(final_cheak_tube<2)
//								{
//								}
//								else
//								{
//								RED=1;
//								Delay_ms(200);
//								RED=1;
//								v_NGD_DISP();
//								delayms(2);
//								power_argument=11;
//								while(START_KEY!=0)
//								{
//							 		Delay_ms(2);
//								}
//
//								}						
//							}
//						}

					}

				else if(power_argument==3)
						{

						Delay_ms(200);
						c_wr(0x01);
						Delay_ms(10);
						c_wr(0x80); 
						Delay_ms(100);	
						 d_wr(' ');d_wr(' '); d_wr('C'); d_wr('O'); d_wr('N'); d_wr('N');d_wr('E'); 
						d_wr('C'); d_wr('T'); d_wr(' ');d_wr('T'); d_wr('E'); d_wr('S');d_wr('T'); d_wr(' '); d_wr(' ');
						
						EEpromRead(&count2,MAX_VAL_LOCATION_28,2);
						EEpromRead(&min_range28,MIN_VAL_LOCATION_28,2);

//					if(count2==0000)
//						{								
						delay(10);
						c_wr(0x01);
						Delay_ms(10);
						c_wr(0x80); 
						Delay_ms(100);		
						d_wr(' ');d_wr(' '); d_wr('C'); d_wr('O'); d_wr('N'); d_wr('N');d_wr('E'); 
						d_wr('C'); d_wr('T'); d_wr(' ');d_wr('T'); d_wr('E'); d_wr('S');d_wr('T'); d_wr(' '); d_wr(' ');
						
							Channel_Read('F');
							Delay_ms(500);
							if(tube_24_flag==2)
							{
								if(final_cheak_tube<4)
								{
									v_OKC_DISP();
									//final_cheak_tube--;
									delayms(2);
								}
							}
							
						Channel_Read('E');
							Delay_ms(500);
							if(tube_24_flag==2)
							{
								if(final_cheak_tube<4)
								{
									v_NGC_DISP();
									//final_cheak_tube--;
									delayms(2);
								}
							}
							else
							{
								if(final_cheak_tube<4)
								{
								final_cheak_tube++;
								voltage_read();
								serial_display(x);
							    v_OKC_DISP();
								Delay_ms(200);
								}
								else{}
							}

						Channel_Read('D');
							Delay_ms(500);
							if(tube_24_flag==2)
							{
								if(final_cheak_tube<4)
								{
									v_NGC_DISP();
									//final_cheak_tube--;
									delayms(2);
								}
							}
							else
							{
								if(final_cheak_tube<4)
								{
								final_cheak_tube++;
								voltage_read();
								serial_display(x);
							    v_OKC_DISP();
								Delay_ms(200);
								}
								else{}
							}
						Channel_Read('C');
							Delay_ms(500);
							if(tube_24_flag==2)
							{
								if(final_cheak_tube<4)
								{
									v_NGC_DISP();
									//final_cheak_tube--;
									delayms(2);
								}
							}
							else
							{
								if(final_cheak_tube<4)
								{
								final_cheak_tube++;
								voltage_read();
								serial_display(x);
							    v_OKC_DISP();
								Delay_ms(200);
								}
								else{}
							}
						Channel_Read('B');
							Delay_ms(500);
						voltage_read();
							if(tube_24_flag==2)
							{
								if(final_cheak_tube<4)
								{
									v_NGC_DISP();
									//final_cheak_tube--;
									delayms(2);
								}
							}
							else
							{
								if(final_cheak_tube<4)
								{
								final_cheak_tube++;
								voltage_read();
								serial_display(x);
							    v_OKC_DISP();
								Delay_ms(200);
								}
								else{}
							}

							Channel_Read('A');
							Delay_ms(500);
							voltage_read();
							
						 if((final_cheak_tube<4)&&(final_cheak_tube!=4))
							{
								final_cheak_tube++;
								voltage_read();
								serial_display(x);
							    v_OKC_DISP();
								Delay_ms(200);
							}
						
							else
								{
								}

					//	}
	 
					}
					
					else if(power_argument==4)
						{
						 v32_ps();
						}
						

						else if(power_argument==6)    
						{
						Delay_ms(200); 
						Channel_Read('R'); 
						delayms(10);
						rev_pol();	
						Delay_ms(20);
						}
						else
						{
						}	
					}
				}	
		}
			if(v_sel==0)     //24v tube check
			{
				GREEN=0;
				SW=1;
				if (SW==1)
				{
				c_wr(0x01); 
				Delay_ms(10);
				c_wr(0x80);
				Delay_ms(20);
				d_wr('T'); d_wr('E');d_wr('S'); d_wr('T');	d_wr(' '); d_wr('S'); d_wr('W');d_wr(' '); d_wr('P'); d_wr('R'); d_wr('E'); d_wr('S'); d_wr('S'); d_wr('E'); d_wr('D');
				Delay_ms(100);
				
				for(power_argument=1;power_argument<7;power_argument++)
					{
						Delay_ms(1000);
						SW=0; 
						RED =0;
						Delay_ms(50);

				
//******************************************************************************************************************
						 if(power_argument==1)    //current for 24v
						{
						Delay_ms(1000);
						Channel_Read(3);   
						Delay_ms(20);
					    current_read24V();
						serial_display_A(x11);
						final_cheak_tube++;
						final_cheak_tube++;
					     v24_ps();
						Delay_ms(1000);
						}
//******************************************************************************************************************
					else if(power_argument==2)    //24v tube dis-connect voltage 32v
						{
						 //RST();
						 
						 Delay_ms(1000);
						Channel_Read('W'); 
						delayms(10);
						voltage_read();
						serial_display(x);
						if(tube_24_flag==2)//HIGH_BEAM_F_B==1 &&
						{
						final_cheak_tube++;
						GREEN=1;
						
						YELLOW=0;
						RED=0;	
						c_wr(0x01);
						Delay_ms(2);	
						c_wr(0x80); 
						Delay_ms(20);		
						 d_wr('O'); d_wr('V');d_wr('P'); d_wr(' '); d_wr('D'); d_wr('I'); d_wr('S'); d_wr('-');d_wr('C'); 
						d_wr('N'); d_wr('T'); d_wr(' ');d_wr('T'); d_wr('E'); d_wr('S');d_wr('T');
						c_wr(0x92); 
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); d_wr('O'); d_wr('K'); 
					
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						Delay_ms(200);
						
						}
						
						else
						{
						if(tube_24_flag!=2)
						{
						RED=0;
						YELLOW=0;
						GREEN=0;
						c_wr(0x01);
						Delay_ms(2);
						c_wr(0x80); 
						Delay_ms(20);		
						 d_wr('O'); d_wr('V');d_wr('P'); d_wr(' '); d_wr('D'); d_wr('I'); d_wr('S'); d_wr('-');d_wr('C'); 
						d_wr('N'); d_wr('T'); d_wr(' ');d_wr('T'); d_wr('E'); d_wr('S');d_wr('T');	
						c_wr(0x92); 
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						power_argument=11;
						while(START_KEY!=0)
							{
							 Delay_ms(2);
							}
						}
						}	
						Delay_ms(20);

						 Delay_ms(100);
						}
//*********************************************************************************************************
					if(power_argument==3)        //24v tube connect voltage 28.5v
						{//24 apllied
						Delay_ms(1000);
						Channel_Read('V'); 
						Delay_ms(400);
						voltage_read();
						serial_display(x);
						final_cheak_tube++;
						final_cheak_tube++;
						//Channel_Read(3); 
						delayms(10);
						//voltage_read();
						//serial_display(x);
						if(tube_24_flag==2)//HIGH_BEAM_F_B==1 &&
						{
						//final_cheak_tube++;
						GREEN=0;
						YELLOW=0;
						RED=0;	
						c_wr(0x01);
						Delay_ms(2);	
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr('O'); d_wr('V'); d_wr('P');d_wr(' '); d_wr('C'); d_wr('O'); d_wr('N'); d_wr('N'); d_wr('E');d_wr('C'); 
						d_wr('T'); d_wr(' '); d_wr('T');d_wr('E'); d_wr('S'); d_wr('T');
						c_wr(0x92); 
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); d_wr('O'); d_wr('K'); 
						//d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						Delay_ms(200);
						}
						
						else
						{
						YELLOW=0;
						RED=0;
						GREEN=1;
						c_wr(0x01);
						Delay_ms(2);
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr('O'); d_wr('V'); d_wr('P');d_wr(' '); d_wr('C'); d_wr('O'); d_wr('N'); d_wr('N'); d_wr('E');d_wr('C'); 
						d_wr('T'); d_wr(' '); d_wr('T');d_wr('E'); d_wr('S'); d_wr('T');
						c_wr(0x92); 
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
					//d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						d_wr(' '); d_wr('O'); d_wr('K'); 
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						
						}	
						Delay_ms(500);
						}
			
//***************************************************************************************************************
				else if(power_argument==4)    //24v tube sustainsion voltage 32v
						{
						 v32_ps();
						 Delay_ms(100);
						}
//***************************************************************************************						
					else if(power_argument==5)
						{
						Delay_ms(1000);
						Channel_Read(3);
						Delay_ms(20);
						Channel_Read(3);
						serial_display_mv(adc_avg_mv2);
						final_cheak_tube++;
						v24_ps();
						Delay_ms(500);
						}
						
//******************************************************************************************************************
					else if(power_argument==6)    
						{
						Delay_ms(1000); 
						Channel_Read('T'); 
						delayms(10);
						rev_pol();	
						Delay_ms(20);
						}
			
			}		//FOR LOOP END	
		 } //SW IF END	
		}	//2ND IF END 	
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
	x=x/2.04;
	x=x*10;
	x=x/1.271;   //X=X/1.261//1.212
//	lcd_num_display(x);
}

void current_read()
{
	TRISCbits.TRISC5=1;
	ANSELCbits.ANSC5=1;
	ADCON2=0xB8;
	ADCON0=0x47;
	ADCON1=0x8E;
	delayms(1);
  	ADCON0bits.GO=1;
	while((ADCON0&0x02)!=0x00);
       {
       }
	x11= (256*ADRESH) + ADRESL;
	x11=x11*1.29;     //X11=X11*1.17//1.4
}

void current_read24V()
{
	TRISCbits.TRISC5=1;
	ANSELCbits.ANSC5=1;
	ADCON2=0xB8;
	ADCON0=0x47;
	ADCON1=0x8E;
	delayms(1);
  	ADCON0bits.GO=1;
	while((ADCON0&0x02)!=0x00);
       {
       }
	x11= (256*ADRESH) + ADRESL;
	x11=x11*0.07;     //X11=X11*1.17
}

void v_NGC_DISP()
{
						YELLOW=0;
						RED=0;
						GREEN=1;
						//	
						c_wr(0x01);
						Delay_ms(10);
						c_wr(0x80); 
						Delay_ms(100);		
						 d_wr('O'); d_wr('V');d_wr('P'); d_wr(' '); d_wr('C'); d_wr('O'); d_wr('N'); d_wr('N');d_wr('E'); 
						d_wr('C'); d_wr('T'); d_wr(' ');d_wr('T'); d_wr('E'); d_wr('S');d_wr('T');
						c_wr(0xc0);
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); d_wr('O'); d_wr('F'); d_wr('F'); 
						//	d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
					//	serial_display(x);
						Delay_ms(2);
}
						
void v_OKC_DISP()					
	{//15reject	
						c_wr(0x01);
						Delay_ms(10);
						c_wr(0x80); 
						Delay_ms(100);		
						 d_wr('O'); d_wr('V');d_wr('P'); d_wr(' '); d_wr('C'); d_wr('O'); d_wr('N'); d_wr('N');d_wr('E'); 
						d_wr('C'); d_wr('T'); d_wr(' ');d_wr('T'); d_wr('E'); d_wr('S');d_wr('T');
						c_wr(0xc0);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); 	d_wr('O'); d_wr('N'); d_wr(' ');d_wr(' ');	d_wr(' '); d_wr(' ');
						//	d_wr(' '); d_wr('O'); d_wr('K'); 
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						Delay_ms(20);	  
}

void v_OKD_DISP()
{
				
						final_cheak_tube++;
						GREEN=1;
						
						YELLOW=0;
						RED=0;
						//	
						c_wr(0x01);
						Delay_ms(10);
						c_wr(0x80); 
						Delay_ms(100);		
						 d_wr('O'); d_wr('V');d_wr('P'); d_wr(' '); d_wr('D'); d_wr('I'); d_wr('S'); d_wr('-');d_wr('C'); 
						d_wr('N'); d_wr('T'); d_wr(' ');d_wr('T'); d_wr('E'); d_wr('S');d_wr('T');
						c_wr(0xc0);
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); d_wr('O'); d_wr('F'); d_wr('F'); 
						//	d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
					//	serial_display(x);
						Delay_ms(2);
}
						
void v_NGD_DISP()					
	{

						c_wr(0x01);
						Delay_ms(10);
						c_wr(0x80); 
						Delay_ms(100);		
						d_wr('O'); d_wr('V');d_wr('P'); d_wr(' '); d_wr('D'); d_wr('I'); d_wr('S'); d_wr('-');d_wr('C'); 
						d_wr('N'); d_wr('T'); d_wr(' ');d_wr('T'); d_wr('E'); d_wr('S');d_wr('T');
						c_wr(0xc0);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); 	d_wr('O'); d_wr('N'); d_wr(' ');d_wr(' ');	d_wr(' '); d_wr(' ');
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						Delay_ms(20);	  
	}


void v32_ps()
{
						Delay_ms(500);
						Channel_Read(4); 
						delayms(10);
						voltage_read();
						serial_display(x);
						if(tube_24_flag==2)//HIGH_BEAM_F_B==1 &&
						{
						final_cheak_tube++;
						GREEN=1;
						
						YELLOW=0;
						RED=0;	
						c_wr(0x01);
						Delay_ms(2);	
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr(' ');d_wr('O'); d_wr('V'); d_wr('P');d_wr(' '); d_wr('S'); d_wr('U'); d_wr('S'); d_wr('T'); d_wr('A');d_wr('I'); 
						d_wr('N'); d_wr('I'); d_wr('N');d_wr('G');  d_wr(' ');
						c_wr(0x92); 
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); d_wr('O'); d_wr('K'); 
					
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						Delay_ms(200);
						
						}
						
						else
						{
						if(tube_24_flag!=2)
						{
						RED=0;
						YELLOW=0;
						GREEN=0;
						c_wr(0x01);
						Delay_ms(2);
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr(' ');d_wr('O'); d_wr('V'); d_wr('P');d_wr(' '); d_wr('S'); d_wr('U'); d_wr('S'); d_wr('T'); d_wr('A');d_wr('I'); 
						d_wr('N'); d_wr('I'); d_wr('N');d_wr('G');  d_wr(' ');	
						c_wr(0x92); 
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						power_argument=11;
						while(START_KEY!=0)
							{
							 Delay_ms(2);
							}
						}
						}	
						Delay_ms(20);
}

void v12_chk()
{
			if(f==2) //LOW_BEAM_F_B==1 &&
						{
						YELLOW=1;
						RED=0;
						GREEN=0;	
						c_wr(0x01);
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr(' ');	d_wr('1'); d_wr('2'); d_wr('V');d_wr(' '); d_wr('P'); d_wr('O'); d_wr('W'); d_wr('E'); d_wr('R');d_wr(' '); 
						d_wr('S'); d_wr('U'); d_wr('P');d_wr('P'); d_wr('L'); d_wr('Y');
						c_wr(0xC0); 
						Delay_ms(2);
						d_wr('*');	d_wr('H'); d_wr('I'); d_wr('G');d_wr('H');d_wr(' ');
						d_wr('I'); 	d_wr('N'); d_wr('T'); d_wr('E');d_wr('N');	d_wr('C'); d_wr('I');d_wr('T'); d_wr('Y');d_wr('*');
						c_wr(0x92); 
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
					
						power_argument=11;
						while(START_KEY!=0)
							{
							 Delay_ms(2);
							}
						}
						
						else
						{
						final_cheak_tube++;
						GREEN=1;
						YELLOW=0;
						RED=0;	
						c_wr(0x01);
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr('1'); d_wr('2'); d_wr('V');d_wr(' '); d_wr('P'); d_wr('O'); d_wr('W'); d_wr('E'); d_wr('R');d_wr(' '); 
						d_wr('S'); d_wr('U'); d_wr('P');d_wr('P'); d_wr('L'); d_wr('Y');
						c_wr(0xC0); 
						d_wr('*');	d_wr('H'); d_wr('I'); d_wr('G');d_wr('H');d_wr(' ');
						d_wr('I'); 	d_wr('N'); d_wr('T'); d_wr('E');d_wr('N');	d_wr('C'); d_wr('I');d_wr('T'); d_wr('Y');d_wr('*');
						c_wr(0x92); 
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); d_wr('O'); d_wr('K'); 
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						Delay_ms(200);
						} 
		
						tmr_delay(2);		 
						Channel_Read(1); 
						{
						  
						if(r==2)//HIGH_BEAM_F_B==1 &&
						{
						YELLOW=0;
						RED=1;
						GREEN=0;	
						c_wr(0x01);
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr('1'); d_wr('2'); d_wr('V');d_wr(' '); d_wr('P'); d_wr('O'); d_wr('W'); d_wr('E'); d_wr('R');d_wr(' '); 
						d_wr('S'); d_wr('U'); d_wr('P');d_wr('P'); d_wr('L'); d_wr('Y');
						c_wr(0xC0); 
						Delay_ms(2);	
						d_wr('*');	d_wr('L'); d_wr('0'); d_wr('W');d_wr(' ');
						d_wr('I'); 	d_wr('N'); d_wr('T'); d_wr('E');d_wr('N');	d_wr('C'); d_wr('I');d_wr('T'); d_wr('Y');d_wr('*');
						c_wr(0x92); 
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						power_argument=11;
						while(START_KEY!=0)
							{
							 Delay_ms(2);
							}
						}
						
						else
						{
						//high ok
						
						final_cheak_tube++;
						GREEN=1;
						
						YELLOW=0;
						RED=0;
						//	
						c_wr(0x01);
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr('1'); d_wr('2'); d_wr('V');d_wr(' '); d_wr('P'); d_wr('O'); d_wr('W'); d_wr('E'); d_wr('R');d_wr(' '); 
						d_wr('S'); d_wr('U'); d_wr('P');d_wr('P'); d_wr('L'); d_wr('Y');
						c_wr(0xC0); 
						d_wr('*');	d_wr('L'); d_wr('0'); d_wr('W');d_wr(' ');
						d_wr('I'); 	d_wr('N'); d_wr('T'); d_wr('E');d_wr('N');	d_wr('C'); d_wr('I');d_wr('T'); d_wr('Y');d_wr('*');
						c_wr(0x92); 
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); d_wr('O'); d_wr('K'); 
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						Delay_ms(200);
						}	
						
						}

}



void rev_pol()
{
	if(tube_24_flag==2)//HIGH_BEAM_F_B==1 &&
						{
						//ok
						final_cheak_tube++;
						GREEN=1;
						
						YELLOW=0;
						RED=0;
						//	
						c_wr(0x01);
						Delay_ms(2);	
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr('R'); d_wr('E'); d_wr('V');d_wr('E'); d_wr('R'); d_wr('S'); d_wr('E'); d_wr(' '); d_wr('P');d_wr('O'); 
						d_wr('L'); d_wr('A'); d_wr('R');d_wr('I'); d_wr('T'); d_wr('Y');
						c_wr(0xC0); 
						Delay_ms(20);	
						d_wr(' ');  d_wr('T'); d_wr('E'); d_wr('S');d_wr('T'); 
						d_wr(' '); d_wr('T'); d_wr('U');d_wr('B'); d_wr('E'); d_wr(' ');d_wr('O');d_wr('F');d_wr('F'); d_wr(' '); d_wr(' ');
						c_wr(0x92); 
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						d_wr(' '); d_wr('O'); d_wr('K'); 
						//	d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						Delay_ms(200);
						
						}
						
						else
						{//reject
						//final_cheak_tube++;
						YELLOW=0;
						RED=1;
						Delay_ms(100);
						GREEN=0;
						//	
						c_wr(0x01);
						Delay_ms(2);
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr('R'); d_wr('E'); d_wr('V');d_wr('E'); d_wr('R'); d_wr('S'); d_wr('E'); d_wr(' '); d_wr('P');d_wr('O'); 
						d_wr('L'); d_wr('A'); d_wr('R');d_wr('I'); d_wr('T'); d_wr('Y');
						c_wr(0xC0); 
						Delay_ms(20);	
						d_wr(' ');  d_wr('T'); d_wr('E'); d_wr('S');d_wr('T'); d_wr(' '); d_wr('T');d_wr('U'); d_wr('B'); d_wr('E');
						d_wr(' '); d_wr('O'); d_wr('N');d_wr('.'); d_wr('.'); d_wr('.');
						c_wr(0x92); 
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E'); 
						d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						//	d_wr(' '); d_wr('O'); d_wr('K'); 
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						
						//				c_wr("0x80");
						//				lcd_string("HIGH BEAM OK");
						power_argument=11;
						while(START_KEY!=0)
							{
							 Delay_ms(2);
							}
						}
}

void v24_ps()
{
						Delay_ms(1000);
						Channel_Read(3); 
						delayms(10);
						//voltage_read();
						//serial_display(x);
						if(tube_24_flag==2)//HIGH_BEAM_F_B==1 &&
						{
						//final_cheak_tube++;
						GREEN=0;
						
						YELLOW=0;
						RED=1;	
						c_wr(0x01);
						Delay_ms(10);	
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr('2'); d_wr('4'); d_wr('V');d_wr(' '); d_wr('P'); d_wr('O'); d_wr('W'); d_wr('E'); d_wr('R');d_wr(' '); 
						d_wr('S'); d_wr('U'); d_wr('P');d_wr('P'); d_wr('L'); d_wr('Y');
						c_wr(0xC0); 
						Delay_ms(2);	
						d_wr('*');	d_wr('L'); d_wr('0'); d_wr('W');d_wr(' ');
						d_wr('I'); 	d_wr('N'); d_wr('T'); d_wr('E');d_wr('N');	d_wr('C'); d_wr('I');d_wr('T'); d_wr('Y');d_wr('*');
						c_wr(0x92);
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
						//d_wr(' '); d_wr('O'); d_wr('K'); 
						d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						while(START_KEY!=0)
							{
							 Delay_ms(2);
							}
						Delay_ms(200);
						if(power_argument<3)
						{
						final_cheak_tube=1;
						}
						else
						{
						final_cheak_tube=6;
						}
						power_argument=11;
						}
						
						else
						{
						YELLOW=0;
						RED=0;
						GREEN=1;
						c_wr(0x01);
						Delay_ms(10);
						c_wr(0x80); 
						Delay_ms(20);	
						d_wr('2'); d_wr('4'); d_wr('V');d_wr(' '); d_wr('P'); d_wr('O'); d_wr('W'); d_wr('E'); d_wr('R');d_wr(' '); 
						d_wr('S'); d_wr('U'); d_wr('P');d_wr('P'); d_wr('L'); d_wr('Y');	
						c_wr(0x92); 
						Delay_ms(2);	
						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
					//d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
						d_wr(' '); d_wr('O'); d_wr('K'); 
						c_wr(0xD0); 
						lcd_num_display(final_cheak_tube);
						
						}	
						Delay_ms(1000);
}
