#include "p18f46k22.h"
#include "delays.h"
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
unsigned char yy=0;
void Page_Max(void);
void Page_Max2(void);
void Page_Min(void);
void Page_1(void);
void cal_lux();
void cal_lux_value();

void START();
void voltage_read();
void current_read();
void current_read24V();
void MANUL_CHK();
void stop();

unsigned int  target1();

void LHv9_chk();
void LHv12_chk();
void LHv16_chk();
void v24_ps();
void RHv9_chk();
void RHv12_chk();
void RHv16_chk();
unsigned int sp,sj,ch;
 unsigned int  adc_avg_mv2=0;
 unsigned int adc_avg_mv1=0;
unsigned int adc_avg_mv;
//unsigned int count=0;
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
unsigned int i; 
unsigned int f,r,g,l1,f1,r1,g1,l11;
unsigned int tube_24_flag=0,tube_24_flag1=0;
unsigned char SW;  /// SW ASSIGN PORT PIN 
unsigned char line;
unsigned int LH_yellow_flag=0;
unsigned int LH_red_flag=0;
unsigned int RH_yellow_flag=0;
unsigned int RH_red_flag=0;
unsigned int pass_flag=0;
unsigned int LH_FLAG=0;
unsigned int RH_FLAG=0;

extern void timepass(unsigned int );
void keypad_set1(void);

void lcd_num_display(unsigned int );
unsigned char keypress,keyflag,dummy_rtn,byte_1,byte_2,t=0,k=0,o=0,s=0;
unsigned char Status_buffer[8],low_index,high_index;

unsigned int k1,m1,k2,m2,k3,m3,k4,m4,k5,m5,k6,m6,k7,m7,k8,m8;
//unsigned adc_val1,adc_val2,adc_val3,adc_val4,adc_val5,adc_val6,adc_val7,adc_val8;
unsigned int adc_val1_mv,adc_val2_mv,adc_val3_mv,adc_val4_mv,adc_val5_mv,adc_val6_mv,adc_val7_mv,adc_val8_mv;
unsigned int adc_val9_mv,adc_val10_mv,adc_val11_mv,adc_val12_mv,adc_val13_mv;
//unsigned int adc_val21_mv,adc_val22_mv,adc_val23_mv,adc_val24_mv;
unsigned int input_voltade,lamp1_opvoltage,lamp2_opvoltage;


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


extern unsigned int max_range24;
extern unsigned int min_range24;
extern unsigned int max_range25;
extern unsigned int min_range25;
extern unsigned int max_range28;
extern unsigned int min_range28;
extern unsigned int min_range29;
extern unsigned int max_range29;
extern unsigned char page_index;
extern unsigned int initial_cheak;
//unsigned int FCT=0;
//unsigned int F_FCT=0;

void movepasscur();
void incridigit();
void decridigit();

void movepasscur_set();
void decridigit_set();
void incridigit_set() ;    
void keypad_calling();
void menu_button();         

void Channel_Read_LH(unsigned char serial_power_on); 
void Channel_Read_RH(unsigned char serial_power_on);
void Channel_Read_voltage(unsigned char serial_power_on);
unsigned int range;
unsigned int range_set;


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
START_KEY =0; 
RED =0; //LOW_BEAM_F_B =0; HIGH_BEAM_F_B =0;
YELLOW=0;//IND_BEAM_LED =0;
GREEN=0;
BUZZER =0; 
RED_NG=0;
Delay_ms(1);
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
	
d_wr('L'); d_wr('E');d_wr('D'); d_wr(' ');	d_wr('P'); d_wr('C'); d_wr('B'); d_wr(' '); d_wr('T'); d_wr('E'); d_wr('S'); d_wr('T'); d_wr('E'); d_wr('R');
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

				//EEpromRead(&count,MAX_VAL_LOCATION_25,2);			
				YELLOW=0;
				RED=0;
				Delay_ms(500);
				GREEN=0;
				RED_NG=0;
				tube_24_flag=0;
				r=0;
				f=0;
				g=0;
				l1=0;
				tube_24_flag1=0;
				r1=0;
				f1=0;
				g1=0;
				l11=0;
				LH_FLAG=0;
				RH_FLAG=0;
				BUZZER =0; 
				LH_red_flag=0;
				LH_yellow_flag=0; 
				RH_red_flag=0;
				RH_yellow_flag=0; 
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
	
							START();
							c_wr(0x01);
							Delay_ms(20);
							c_wr(0x80);
							delayms(5);
							d_wr('C');d_wr('A');d_wr('L');d_wr('C');d_wr('U');d_wr('L');d_wr('A');d_wr('T'); 
							d_wr('I');d_wr('N');d_wr('G');d_wr(' ');d_wr('L');d_wr('E');d_wr('D');d_wr(' ');
							c_wr(0xC0); 		
							d_wr('L');d_wr('U');d_wr('X');d_wr(' ');d_wr('V');d_wr('A');d_wr('L');d_wr('U'); 
							d_wr('E');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');
							Delay_ms(200);
							cal_lux_value();
							serial_display_mv(adc_avg_mv1);
							Delay_ms(2000);
							Delay_ms(200);
							RCSTA=0x90;
							TXSTA=0x20;
							TXSTAbits.TXEN=1;
							TRISCbits.RC6=0;
							SPBRG=23;
							RCSTAbits.SPEN=1;
							TXREG='*';
							while(PIR1bits.TXIF==0);
							Delay_ms(100);
							TSTOVR();	
//						}
//					}
				GREEN=0;
				EEPROM_Load();
				init_lcd();
				Delay_ms(500);
				NEWHAR();	
		}
   
}     
 
void Page_1(void)                    //  to check which channels are  out of range
{   
EEPROM_Load();

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
	   
}

void Page_Max(void)
{

    c_wr(0x80);
	d_wr('C');d_wr('H');d_wr('A');d_wr('N');d_wr('N');d_wr('E');d_wr('L');d_wr(' ');d_wr('R');d_wr('A');d_wr('N');d_wr('G');d_wr('E');d_wr('S');d_wr(':');d_wr(':');
	
if(SELECT_KEY==1)
	{
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
}

if(SELECT_KEY==0)
	{
	if(max_range5 > min_range5)
	{

		if(adc_val5_mv < min_range5)
		{

				c_wr(0xC0);
		d_wr('5');
        d_wr(' ');
			Status_buffer[4] = 1;

		}
		else if (adc_val5_mv > max_range5)
		{
			Status_buffer[4] = 2;
		c_wr(0xC0);
		d_wr('5');
        d_wr(' ');
		}
		else
		{
			Status_buffer[4] = 0;

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

//	d_wr(' ');
	if(max_range6 > min_range6)
	{
		if(adc_val6_mv < min_range6)
		{

			c_wr(0xC2);
		d_wr('6');
        d_wr(' ');
			Status_buffer[5] = 1;

		}
		else if (adc_val6_mv > max_range6)
		{
			Status_buffer[5] = 2;
					c_wr(0xC2);
		d_wr('6');
        d_wr(' ');
		}
		else
		{
			Status_buffer[5] = 0;

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

//d_wr(' ');
	if(max_range7 > min_range7)
	{
		if(adc_val7_mv < min_range7)
		{

		     c_wr(0xC4);
		d_wr('7');
        d_wr(' ');
			Status_buffer[6] = 1;

		}
		else if (adc_val7_mv > max_range7)
		{
			Status_buffer[6] = 2;
		 c_wr(0xC4);
		d_wr('7');
        d_wr(' ');
		}
		else
		{
			Status_buffer[6] = 0;

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

       //d_wr(' ');
	if(max_range8 > min_range8)
	{
		if(adc_val8_mv < min_range8)
		{

		   c_wr(0xC6);
		d_wr('8');
        d_wr(' ');
			Status_buffer[7] = 1;

		}
		else if (adc_val8_mv > max_range8)
		{
			Status_buffer[7] = 2;
			  c_wr(0xC6);
		d_wr('8');
        d_wr(' ');
		}
		else
		{
			Status_buffer[7] = 0;
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

	}	//lcd_gotoxy(2,0);
		
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
Delay_ms(2);

do {
c_wr(0x80);
Delay_ms(5);
d_wr('L');d_wr('E');d_wr('D');d_wr(' ');d_wr('L');d_wr('U');d_wr('X');d_wr(' ');
d_wr('I');d_wr('N');d_wr(' ');d_wr('m');d_wr('V');d_wr(' ');d_wr(' ');
Delay_ms(20); 
if(SELECT_KEY==1)
{
Channel_Read_LH(3);
Delay_ms(10);
c_wr(0xC0);
lcd_num_display(adc_val1_mv);
c_wr(0xC5);
lcd_num_display(adc_val2_mv);
c_wr(0xCA);
lcd_num_display(adc_val3_mv);	
c_wr(0x90);
lcd_num_display(adc_val4_mv);
Delay_ms(500);
adc_avg_mv1=(((adc_val1_mv+adc_val2_mv+adc_val3_mv+adc_val4_mv)/4)*100);
Delay_ms(10);
}
if(SELECT_KEY==0)
{
Channel_Read_RH(7);
Delay_ms(10);
c_wr(0xC0);
lcd_num_display(adc_val5_mv);
c_wr(0xC5);
lcd_num_display(adc_val6_mv);
c_wr(0xCA);
lcd_num_display(adc_val7_mv);
c_wr(0x90);
lcd_num_display(adc_val8_mv);
Delay_ms(500);
adc_avg_mv1=(((adc_val5_mv+adc_val6_mv+adc_val7_mv+adc_val8_mv)/4)*100);
Delay_ms(10);
}
}while (((PORTB & 0x0A) != 0x0A));

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
Delay_ms(2);
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
	if(SELECT_KEY==0)
	{
	//Channel_Read_RH(7);
	Channel_Read_LH(8);
	Delay_ms(2);
	Page_Max();
	tmr_delay(4);
	}
	else
	{
	//Channel_Read_LH(3);
	Channel_Read_RH(4);
	Delay_ms(2);
	Page_Max();
	tmr_delay(4);
	}
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
unsigned char ok_p=0;
L1:
c_wr(0x01);
Delay_ms(20);
//lcd_num_display(min_range29);
//Delay_ms(5);

c_wr(0x80); 
	Delay_ms(2);	
	d_wr(' '); d_wr('E'); d_wr('N');d_wr('T'); d_wr('E'); d_wr('R'); d_wr(' '); d_wr('P'); 
	d_wr('A');d_wr('S'); d_wr('S'); d_wr('W'); d_wr('O');d_wr('R'); d_wr('D'); d_wr(' ');
	Delay_ms(5);
	Delay_ms(20);
	c_wr(0xC0); 
	Delay_ms(2);
	lcd_num_display(count2);
//while (PORTBbits.RB0 != 1)
//	{	Delay_ms(2);
//	}
do
{
if (PORTBbits.RB0 == 1) 
{ 
	while(PORTBbits.RB0 == 1)
	{	Delay_ms(2);
	}
	 count2 = count2++;  
	 EEpromWrite(&count2,MIN_VAL_LOCATION_29,2);
//	c_wr(0xD0);
	delayms(5);
	c_wr(0x80); 
	Delay_ms(2);	
	d_wr(' '); d_wr('E'); d_wr('N');d_wr('T'); d_wr('E'); d_wr('R'); d_wr(' '); d_wr('P'); 
	d_wr('A');d_wr('S'); d_wr('S'); d_wr('W'); d_wr('O');d_wr('R'); d_wr('D'); d_wr(' ');
	c_wr(0xC0); 
	Delay_ms(2);
	lcd_num_display(count2);
	 if (count2 > min_range29 )
	 {
		 EEpromClear(&count2,MIN_VAL_LOCATION_29,2);
		 count2=0; 
		 
	 }
}

if (((PORTB & 0x08) == 0x08) )
{   
	
	while(((PORTB & 0x08) == 0x08) )
	{	Delay_ms(2);
	}
	count2 = count2--; 
	 EEpromWrite(&count2,MIN_VAL_LOCATION_29,2);
	 c_wr(0xD0);
	delayms(5);
		c_wr(0x80); 
	Delay_ms(2);	
	d_wr(' '); d_wr('E'); d_wr('N');d_wr('T'); d_wr('E'); d_wr('R'); d_wr(' '); d_wr('P'); 
	d_wr('A');d_wr('S'); d_wr('S'); d_wr('W'); d_wr('O');d_wr('R'); d_wr('D'); d_wr(' ');
	c_wr(0xC0); 
	Delay_ms(2);
	lcd_num_display(count2);
	 if (count2 > min_range29 )
	 {
		 EEpromClear(&count2,MIN_VAL_LOCATION_29,2);
		 count2=0; 
		 
	 }
		ok_p=1;
}



}while (((PORTB & 0x04) != 0x04));


if(count2==0001)
{ 
c_wr(0x01);
Delay_ms(20);
c_wr(0x80); 	
d_wr(' '); d_wr('V'); d_wr('A');d_wr('L'); d_wr('I'); d_wr('D'); d_wr(' ');d_wr('P');
d_wr('A');d_wr('S'); d_wr('S'); d_wr('W'); d_wr('O');d_wr('R'); d_wr('D'); d_wr(' ');
Delay_ms(20);
c_wr(0xC0); 	
d_wr(' ');d_wr('F'); d_wr('O'); d_wr('R');d_wr(' ');d_wr('S'); d_wr('E'); d_wr('T');
d_wr(' ');d_wr('C');d_wr('H');d_wr('A');d_wr('N');d_wr('N');d_wr('E');d_wr('L');
Delay_ms(20);
c_wr(0x90); 	
d_wr(' ');d_wr('P');d_wr('R');d_wr('E');d_wr('S');d_wr('S');d_wr(' ');d_wr('"');d_wr('E');d_wr('"');
Delay_ms(20);
do
	{
	keypad();
	}while (((PORTB & 0x0A) != 0x0A));//while (START_KEY!=1);
	c_wr(0x01);		
}
else
{
c_wr(0x01);
Delay_ms(20);
c_wr(0x80); 
d_wr(' '); d_wr('W'); d_wr('R');d_wr('O'); d_wr('N'); d_wr('G'); d_wr(' '); d_wr('P'); 
d_wr('A');d_wr('S'); d_wr('S'); d_wr('W'); d_wr('O');d_wr('R'); d_wr('D'); d_wr(' ');
Delay_ms(20);
goto L1;
}

while (((PORTB & 0x0A) != 0x0A))
Delay_ms(2);

}
//**************************************************
void keypad_set1(void)
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
						incridigit_set();
					break;
              


      case KEY_4:
					decridigit_set();
					break;




       case KEY_2: 
					movepasscur_set();
					break;



         case KEY_3:
					    //line = 1;
		                range_set = min_range29;
					    set_max_count(min_range29,min_range29,2);
                        min_range29 = range_set;
					   	 EEpromWrite(&min_range29 ,MIN_VAL_LOCATION_29, 2);
                        
				
                   
//					if(set_mode == 3)
//					{
//					     line = 3;
//						  min_range26 = range_set;
//					   	 EEpromWrite(&min_range26 ,MIN_VAL_LOCATION_26, 2);
//						set_min_count(min_range25,min_range26,2);
//		             }

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







//**************************************************
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
d_wr('F');d_wr('O');d_wr('R');d_wr(' ');d_wr('L');d_wr('U');d_wr('X');d_wr(' ');
d_wr('O');d_wr('/');d_wr('P');d_wr(':');d_wr(':');d_wr('U');d_wr('&');d_wr('S');
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




void Channel_Read_RH(unsigned char serial_power_on) //void Channel_Read_LH(unsigned char serial_power_on)
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
Delay_ms(2);	    

	#if 1
	if(toggle_mode == 0)
		{
    #if 0

      lcd_gotoxy(0,0); 
      
			
   #endif

   #if 1
   //ch1
for(i=0;i<5;i++)
{
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


}
     
#endif


switch(page_index)
			{
//			case MAIN_PAGE:
//				Page_1();
//			break;
//			case MIN_CH_PAGE:
//	    	  Page_Min();
//			break;
//		   case MAX_CH_PAGE:
//			   Page_Max();
//			break;
//			case VAL_1_PAGE:
//				Page_Val_1();
//			break;
//           case VAL_2_PAGE:
//				Page_Val_2();
//			break;
			default:
				Page_1();
			break;
			}
			
    low_index = 0;
	high_index = 0;
       for(k=0;k<4;k++)
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
l1=0;
tube_24_flag=1;
                 }
			else if(low_index < high_index)
		       {
					 
				   
g=0;
	r=2;
l1=2;
f=0;
tube_24_flag=2;
		       }
							
           	else if((low_index == 0) && (high_index == 0))
		      {
					
g=2;
f=0;
r=0;  
l1=0;   
tube_24_flag=1;
    
              }
			else if((low_index == high_index)&& (low_index !=0) && (high_index!=0))
				{g=0;
r=2;
f=2;
l1=2;					
                 
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
//	 c_wr(0x01);
//c_wr(0x80);
//Delay_ms(20);
//d_wr(' ');d_wr('u');d_wr('c');d_wr(' ');d_wr('i');d_wr('n');d_wr(' ');d_wr('S');d_wr('h');d_wr('O');       
 }   
//******************************************************        
void Channel_Read_LH(unsigned char serial_power_on) //void Channel_Read_RH(unsigned char serial_power_on) 
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

Delay_ms(2);	    

	#if 1
	if(toggle_mode == 0)
		{
    #if 0

      lcd_gotoxy(0,0); 
      
			
   #endif

   #if 1
 for(i=0;i<5;i++)
{  
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
}
 
#endif

switch(page_index)
			{
//			case MAIN_PAGE:
//				Page_1();
//			break;
//			case MIN_CH_PAGE:
//	    	  Page_Min();
//			break;
//		   case MAX_CH_PAGE:
//			   Page_Max();
//			break;
//			case VAL_1_PAGE:
//				Page_Val_1();
//			break;
//           case VAL_2_PAGE:
//				Page_Val_2();
//			break;
			default:
				Page_1();
			break;
			}
			
    low_index = 0;
	high_index = 0;
       for(k=4;k<8;k++)
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
				
g1=0;            
   	          f1=2;
r1=0;
l11=0;
tube_24_flag1=1;
                }
			else if(low_index < high_index)
		       {
					 				   
g1=0;
	r1=2;
l11=2;
f1=0;
tube_24_flag1=2;
		       }
							
           	else if((low_index == 0) && (high_index == 0))
		      {
					
g1=2;
f1=0;
r1=0;  
l11=0;   
tube_24_flag1=1;
    
              }
			else if((low_index == high_index)&& (low_index !=0) && (high_index!=0))
				{g1=0;
r1=2;
f1=2;
l11=2;					
                 
tube_24_flag1=2;
                 
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
//	 c_wr(0x01);
//c_wr(0x80);
//Delay_ms(20);
//d_wr(' ');d_wr('u');d_wr('c');d_wr(' ');d_wr('i');d_wr('n');d_wr(' ');d_wr('S');d_wr('h');d_wr('O');       
 }       
     
//***************************************************** 
void Channel_Read_voltage(unsigned char serial_power_on) 
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
	while(ack<12)	
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
					adc_val9_mv=m+n+o1+p;
					} 
					if(ack==7)
					{
					adc_val10_mv=m+n+o1+p;
					}
					if(ack==11)
					{
					adc_val11_mv=m+n+o1+p;
					}
	    
		}
		else
     	f_array++;

 	c_wr(0x80);
     	ack++;  	
     }ack=0;  

input_voltade=adc_val9_mv*2.99;     //1.33;input_voltade=adc_val9_mv
lamp1_opvoltage=adc_val10_mv*1.48;    //0.54;
lamp2_opvoltage=adc_val11_mv*1.48;       //0.54;
Delay_ms(2);   
  }  	
//*****************************************************
void keypad(void)
{

	
 if((PORTB & 0x0F) != 0x00)
	{
        delay(5);
		pass_flag=1;
		if((PORTB & 0x0F) != 0x00)      //0x00 no key press
		{
		    keypress= PORTB & 0x0F;
	
				switch(keypress)
				{
			
		   case KEY_1:
                    
					if((toggle_mode >= 1) && (toggle_mode <= 17))
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

					if((toggle_mode >= 1) && (toggle_mode <= 17))
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
					if((toggle_mode >= 1) && (toggle_mode <= 17))
					{
				        
						movepasscur();
						
					}

					else
					{

					}

					break;



         case KEY_3:
				toggle_mode =  toggle_mode+1;
					if(toggle_mode == 17)
					{
                        max_range8 = range;
						EEpromWrite(&max_range8 ,MAX_VAL_LOCATION_8, 2);

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


//					}

					


					break;

				default:
					break;
				}

		}
	}
	else
	{
	pass_flag=0;
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
                    
					if((toggle_mode >= 1) && (toggle_mode <= 17))
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

					if((toggle_mode >= 1) && (toggle_mode <= 17))
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
					if((toggle_mode >= 1) && (toggle_mode <= 17))
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
								yy=0;
							  }
							  else if(ch <20)
							  {
								  temp2 = ch%10;
								   d_wr('1');
								  // temp2 = ch/10;
								    d_wr(temp2+0x30);
									yy=0;
							  }	                              //DISPLAY CH number
							else if(ch<25)
								{
								  temp3 = ch%10;
								   d_wr('2');
								  // temp2 = ch/10;
								    d_wr(temp3+0x30);
									yy=0;
								}
								else if (ch==25)
								{
									yy=1;
								}
							  else
								{yy=0;
								}
							  

							 			  
 
if(yy!=1)
{
                              c_wr(0xC0);  
				Delay10KTCYx(3);        
           d_wr('M');d_wr('I');d_wr('N');d_wr(' ');d_wr('V');d_wr('A');d_wr('L');d_wr(':');
                               lcd_num_display(min);
                              d_wr('m');
                              d_wr('v');
                              d_wr('<');
                              d_wr('-');
c_wr(0x90);
Delay10KTCYx(5);
     d_wr('M');d_wr('A');d_wr('X');d_wr(' ');d_wr('V');d_wr('A');d_wr('L');d_wr(':');
                 lcd_num_display(max);
	             d_wr('m');
	             d_wr('v');
	             

}
else
{
                             c_wr(0xC0);  
Delay10KTCYx(3);        
           d_wr('M');d_wr('I');d_wr('N');d_wr(' ');d_wr('V');d_wr('A');d_wr('L');d_wr(':');
                               lcd_num_display(min);
                              d_wr('m');
                              d_wr('v');
                              d_wr('<');
                              d_wr('-');
c_wr(0x90);
Delay10KTCYx(5);
     d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');
     d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');            
}

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
								yy=0;
							  }
							  else if(ch <20)
							  {
								  temp2 = ch%10;
								   d_wr('1');
								  // temp2 = ch/10;
								    d_wr(temp2+0x30);
									yy=0;
							  }	                              //DISPLAY CH number
							else if(ch<25)
								{
								  temp3 = ch%10;
								   d_wr('2');
								  // temp2 = ch/10;
								    d_wr(temp3+0x30);
									yy=0;
								}
								else if (ch==25)
								{
									yy=1;
								}
							  else
								{yy=0;
								} 
							  






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
//	    c_wr(0x01);
//Delay10KTCYx(5);
c_wr(0xC0);
Delay10KTCYx(5);

//Delay10KTCYx(5);
//   d_wr('R');d_wr('E');d_wr('S');d_wr('E');d_wr('R');d_wr('V');d_wr('E');d_wr(':');
//                lcd_num_display(min_range25);
//	           	             d_wr('<');
//	             d_wr('-');

	cnt_digit = 0;
	UP_cntr[0] = min/1000;
	temp = min%1000;
	UP_cntr[1] = temp/100;
	temp = temp%100;
	UP_cntr[2] = temp/10;
	UP_cntr[3] = temp%10;
Delay1KTCYx(1000);
EEpromWrite(&min_range29 ,MIN_VAL_LOCATION_29, 2);
EEPROM_Load();
c_wr(0xC0);
Delay10KTCYx(5);

//Delay10KTCYx(5);
  d_wr('R');
while(START_KEY!=0)
{
Delay_ms(5);
}

}
void set_min_count(unsigned int min,unsigned int max,unsigned char ch)
{
unsigned int temp,temp2;
c_wr(0x01);
Delay10KTCYx(5);

    d_wr('1');d_wr('5');d_wr('V');d_wr(' ');d_wr('V');d_wr('A');d_wr('R');d_wr(':');
               // lcd_num_display(min_range26);
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
				if(SELECT_KEY==1)
				{
				for(power_argument=1;power_argument<5;power_argument++)
					{
						Delay_ms(200);
						SW=0; 
						//CHKST();
						HARREJ =0;
						RED =0;
						Delay_ms(50);

					 if(power_argument==2)   //FOR 9V 
						{
						Delay_ms(200);
						Channel_Read_RH(power_argument);
						Delay_ms(20);
						Channel_Read_RH(power_argument);
						Delay_ms(20);
						c_wr(0x01);
						c_wr(0x80);
						Delay_ms(20);
						//d_wr(' ');d_wr('u');d_wr('c');d_wr(' ');d_wr('i');d_wr('n');d_wr(' ');d_wr('P');d_wr('A');d_wr('1'); 
						//Delay_ms(50);
						RHv9_chk();
						current_read();
						//serial_display_A(x1);
						Delay_ms(50);
						Channel_Read_voltage('R');
						Delay_ms(20);
//						serial_display(input_voltade);
//						Delay_ms(20);
//						serial_display(lamp1_opvoltage);
//						Delay_ms(20);
//						serial_display(lamp2_opvoltage);
//						Delay_ms(20);
//						Delay_ms(2000);
						stop();
						Delay_ms(2000);
						//tmr_delay(1);
						}
					if(power_argument==3)  // FOR 13V
						{
						Delay_ms(200);
						//Channel_Read_LH(power_argument);
						Channel_Read_RH(power_argument);
						Delay_ms(20);
						Channel_Read_RH(power_argument);
						Delay_ms(20);
						c_wr(0x01);
						c_wr(0x80);
						Delay_ms(20);
						//d_wr(' ');d_wr('u');d_wr('c');d_wr(' ');d_wr('i');d_wr('n');d_wr(' ');d_wr('P');d_wr('A');d_wr('1'); 
						//Delay_ms(50);
						//LHv12_chk();
						RHv12_chk();
						current_read();
						serial_display_A(x1);
						Delay_ms(50);
					
						Channel_Read_voltage('R');
						Delay_ms(20);
						serial_display(input_voltade);
						Delay_ms(20);
						serial_display(lamp1_opvoltage);
						Delay_ms(20);
						serial_display(lamp2_opvoltage);
						Delay_ms(20);
						Delay_ms(2000);
						stop();
						Delay_ms(2000);
						}
					if(power_argument==4) //FOR 16V
						{
						Delay_ms(200);
						//Channel_Read_LH(power_argument);
						Channel_Read_RH(power_argument);
						Delay_ms(20);
						Channel_Read_RH(power_argument);
						Delay_ms(20);
						c_wr(0x01);
						c_wr(0x80);
						Delay_ms(20);
						//d_wr(' ');d_wr('u');d_wr('c');d_wr(' ');d_wr('i');d_wr('n');d_wr(' ');d_wr('P');d_wr('A');d_wr('1'); 
						//Delay_ms(50);
						//LHv16_chk();

						RHv16_chk();
						current_read();
						//serial_display_A(x1);
						Delay_ms(50);
						Channel_Read_voltage('R');
						Delay_ms(20);
//						serial_display(input_voltade);
//						Delay_ms(20);
//						serial_display(lamp1_opvoltage);
//						Delay_ms(20);
//						serial_display(lamp2_opvoltage);
//						Delay_ms(20);
//
//						Delay_ms(2000);
						stop();
						Delay_ms(1000);
						}
					}
				}
					

				if(SELECT_KEY==0)
				{
				for(power_argument=5;power_argument<10;power_argument++)
					{


					if(power_argument==6)
						{
						Delay_ms(200);
						//Channel_Read_RH(power_argument);
						Channel_Read_LH(power_argument);
						Delay_ms(20);
						Channel_Read_LH(power_argument);
						Delay_ms(20);
						c_wr(0x01);
						c_wr(0x80);
						Delay_ms(20);
						//d_wr(' ');d_wr('u');d_wr('c');d_wr(' ');d_wr('i');d_wr('n');d_wr(' ');d_wr('P');d_wr('A');d_wr('1'); 
						//Delay_ms(50);
						//RHv9_chk();
						LHv9_chk();
						current_read24V();
						//serial_display_A(x11);
						Delay_ms(50);

						Channel_Read_voltage('R');
						Delay_ms(20);
//						serial_display(input_voltade);
//						Delay_ms(20);
//						serial_display(lamp1_opvoltage);
//						Delay_ms(20);
//						serial_display(lamp2_opvoltage);
//						Delay_ms(20);
//
//						Delay_ms(2000);
						stop();
						Delay_ms(2000);
						}
					if(power_argument==7)
						{
						Delay_ms(200);
						//Channel_Read_RH(power_argument);
						Channel_Read_LH(power_argument);
						Delay_ms(20);
						Channel_Read_LH(power_argument);
						Delay_ms(20);
						c_wr(0x01);
						c_wr(0x80);
						Delay_ms(20);
						//d_wr(' ');d_wr('u');d_wr('c');d_wr(' ');d_wr('i');d_wr('n');d_wr(' ');d_wr('P');d_wr('A');d_wr('1'); 
						//Delay_ms(50);
						//RHv12_chk();
						LHv12_chk();
						current_read();
						serial_display_A(x1);
						Delay_ms(50);
						Delay_ms(2000);
						
						Channel_Read_voltage('R');
						Delay_ms(20);
						serial_display(input_voltade);
						Delay_ms(20);
						serial_display(lamp1_opvoltage);
						Delay_ms(20);
						serial_display(lamp2_opvoltage);
						Delay_ms(20);	
						Delay_ms(2000);
						stop();
						Delay_ms(2000);
						}
					if(power_argument==8)
						{
						Delay_ms(200);
						//Channel_Read_RH(power_argument);
						Channel_Read_LH(power_argument);
						Delay_ms(20);
						Channel_Read_LH(power_argument);
						Delay_ms(20);
						c_wr(0x01);
						c_wr(0x80);
						Delay_ms(20);
						//d_wr(' ');d_wr('u');d_wr('c');d_wr(' ');d_wr('i');d_wr('n');d_wr(' ');d_wr('P');d_wr('A');d_wr('1'); 
						//Delay_ms(50);
						//RHv16_chk();
						LHv16_chk();
						current_read24V();
						//serial_display_A(x11);
						Delay_ms(50);
						Channel_Read_voltage('R');
						Delay_ms(20);
//						serial_display(input_voltade);
//						Delay_ms(20);
//						serial_display(lamp1_opvoltage);
//						Delay_ms(20);
//						serial_display(lamp2_opvoltage);
//						Delay_ms(20);
//
//						Delay_ms(2000);
						stop();
						Delay_ms(1000);
						}

//						else
//						{
//						}
							
					}
				}	
	
			}
}
void stop()
{
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

void LHv9_chk()    //void LHv9_chk()
{

							if(l11==2)
							{
							GREEN=0;	
							YELLOW=1;
							RED=0; 
							Delay_ms(20); 
							LH_red_flag=0;
							LH_yellow_flag=1; 
							Delay_ms(20);    
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('0'); d_wr('9');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
							d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');	
							Delay_ms(1000);
							}
							
							else
							{
							GREEN=1;
							YELLOW=0;
							RED=0;	
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('0'); d_wr('9');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' '); 	
							d_wr('O');d_wr('K');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');	
							
							Delay_ms(1000);
							LH_FLAG++;
							final_cheak_tube++;
							}
							
							//						Channel_Read(1);
							Delay_ms(20);
							
							if(LH_yellow_flag==0)
							{
									if((f1==2)&&(tube_24_flag1!=2)) //LOW_BEAM_F_B==1 &&
									{
									LH_red_flag=1;
									LH_yellow_flag=0;
									RED=1;
									GREEN=0;
									Delay_ms(1);
									YELLOW=0;
									Delay_ms(200);	
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('0'); d_wr('9');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P'); d_wr('C'); d_wr('B'); d_wr(' ');  	
									d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');d_wr(' ');	
									Delay_ms(1000);
									}
									else
									{
									GREEN=1;
									YELLOW=0;
									RED=0;
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('0'); d_wr('9');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('O');d_wr('K');d_wr(' ');
									d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' '); 
									 	
									Delay_ms(1000);
									LH_FLAG++;
									final_cheak_tube++;
									
									}	
							
							}
							else
							{		LH_yellow_flag=0;
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('0'); d_wr('9');
									c_wr(0x90);		
									d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
									d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
									d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');	
									Delay_ms(1000);
							}
}

//********************************************************************************************************************
void LHv12_chk()
{

						if(l11==2)
							{
							GREEN=0;	
							YELLOW=1;
							RED=0; 
							Delay_ms(20); 
							LH_red_flag=0;
							LH_yellow_flag=1;     
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('3');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
							d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');	
							Delay_ms(1000);
							}
							
							else
							{
							GREEN=1;
							YELLOW=0;
							RED=0;	
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('3');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' '); 	
							d_wr('O');d_wr('K');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');	
							
							Delay_ms(1000);
							LH_FLAG++;
							final_cheak_tube++;
							}
							
							//						Channel_Read(1);
												Delay_ms(20);
							
							if(LH_yellow_flag==0)
							{
									if((f1==2)&&(tube_24_flag1!=2)) //LOW_BEAM_F_B==1 &&
									{
									LH_red_flag=1;
									LH_yellow_flag=0;
									RED=1;
									GREEN=0;
									Delay_ms(1);
									YELLOW=0;
									Delay_ms(200);	
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('3');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P'); d_wr('C'); d_wr('B'); d_wr(' ');  	
									d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');d_wr(' ');	
									Delay_ms(1000);
									}
									else
									{
									GREEN=1;
									YELLOW=0;
									RED=0;
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('3');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
									 d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('O');d_wr('K');d_wr(' ');
									d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');
									
									 	
									Delay_ms(1000);
									LH_FLAG++;
									final_cheak_tube++;
									
									}	
							
							}
							else
							{		LH_yellow_flag=0;
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('3');
									c_wr(0x90);		
									d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
									d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
									d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');	
									Delay_ms(1000);
							}
}
//*********************************************************************************************************************

void LHv16_chk()
{

						if(l11==2)
							{
							GREEN=0;	
							YELLOW=1;
							RED=0; 
							Delay_ms(20); 
							LH_red_flag=0;
							LH_yellow_flag=1;     
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('6');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
							d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');	
							Delay_ms(1000);
							}
							
							else
							{
							GREEN=1;
							YELLOW=0;
							RED=0;	
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('6');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' '); 	
							d_wr('O');d_wr('K');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');	
							
							Delay_ms(1000);
							LH_FLAG++;
							final_cheak_tube++;
							}
							
							//						Channel_Read(1);
													Delay_ms(20);
							
							if(LH_yellow_flag==0)
							{
									if((f1==2)&&(tube_24_flag1!=2)) //LOW_BEAM_F_B==1 &&
									{
									LH_red_flag=1;
									LH_yellow_flag=0;
									RED=1;
									GREEN=0;
									Delay_ms(1);
									YELLOW=0;
									Delay_ms(200);	
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('6');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P'); d_wr('C'); d_wr('B'); d_wr(' ');  	
									d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');d_wr(' ');	
									Delay_ms(1000);
									}
									else
									{
									GREEN=1;
									YELLOW=0;
									RED=0;
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('6');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('O');d_wr('K');d_wr(' ');
									d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');
									 
									 	
									Delay_ms(1000);
									LH_FLAG++;
									final_cheak_tube++;
									
									}	
							
							}
							else
							{		LH_yellow_flag=0;
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('L');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('6');
									c_wr(0x90);		
									d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
									d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
									d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');	
									Delay_ms(1000);
							}
}
//-----------------------------------------------------------------------------------------------------------------------
void RHv9_chk()
{

							if(l1==2)  //if(l11==2)
							{
							GREEN=0;	
							YELLOW=1;
							RED=0; 
							Delay_ms(20); 
							RH_red_flag=0;
							RH_yellow_flag=1;     
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('0'); d_wr('9');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
							d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');	
							Delay_ms(1000);
							}
							
							else
							{
							GREEN=1;
							YELLOW=0;
							RED=0;	
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('0'); d_wr('9');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' '); 	
							d_wr('O');d_wr('K');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');	
							
							Delay_ms(1000);
							RH_FLAG++;
							final_cheak_tube++;
							}
							
							//						Channel_Read(1);
													Delay_ms(20);
							
							if(RH_yellow_flag==0)
							{
									if((f==2)&&(tube_24_flag!=2)) //LOW_BEAM_F_B==1 &&   if((f1==2)&&(tube_24_flag1!=2))
									{
									RH_red_flag=1;
									RH_yellow_flag=0;
									RED=1;
									GREEN=0;
									Delay_ms(1);
									YELLOW=0;
									Delay_ms(200);	
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('0'); d_wr('9');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P'); d_wr('C'); d_wr('B'); d_wr(' ');  	
									d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');d_wr(' ');
									Delay_ms(1000);
									}
									else
									{
									GREEN=1;
									YELLOW=0;
									RED=0;
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('0'); d_wr('9');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
									 d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('O');d_wr('K');d_wr(' ');
									d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' '); 	
									
										
									Delay_ms(1000);
									RH_FLAG++;
									final_cheak_tube++;
									
									}	
							
							}
							else
							{
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('0'); d_wr('9');
									c_wr(0x90);		
									d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
									d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
									d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');
									RH_yellow_flag=0;	
									Delay_ms(1000);
							}
}

//********************************************************************************************************************
void RHv12_chk()
{

						if(l1==2)
							{
							GREEN=0;	
							YELLOW=1;
							RED=0; 
							Delay_ms(20); 
							RH_red_flag=0;
							RH_yellow_flag=1;     
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('3');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
							d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');	
							Delay_ms(1000);
							}
							
							else
							{
							GREEN=1;
							YELLOW=0;
							RED=0;	
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('3');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' '); 	
							d_wr('O');d_wr('K');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');	
							
							Delay_ms(1000);
							RH_FLAG++;
							final_cheak_tube++;
							}
							
							//						Channel_Read(1);
													Delay_ms(20);
							
							if(RH_yellow_flag==0)
							{
									if((f==2)&&(tube_24_flag!=2)) //LOW_BEAM_F_B==1 &&
									{
									RH_red_flag=1;
									RH_yellow_flag=0;
									RED=1;
									GREEN=0;
									Delay_ms(1);
									YELLOW=0;
									Delay_ms(200);	
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('3');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
									 d_wr(' ');d_wr('P'); d_wr('C'); d_wr('B'); d_wr(' ');  	
									d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');d_wr(' '); 	
									Delay_ms(1000);
									}
									else
									{
									GREEN=1;
									YELLOW=0;
									RED=0;
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('3');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('O');d_wr('K');d_wr(' ');
									d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');
									
									
									Delay_ms(1000);
									RH_FLAG++;
									final_cheak_tube++;
									
									}	
							
							}
							else
							{
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('3');
									c_wr(0x90);		
									d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
									d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
									d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');
									RH_yellow_flag=0;	
									Delay_ms(1000);
							}
}
//*********************************************************************************************************************

void RHv16_chk()
{

						if(l1==2)
							{
							GREEN=0;	
							YELLOW=1;
							RED=0; 
							Delay_ms(20); 
							RH_red_flag=0;
							RH_yellow_flag=1;     
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('6');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
							d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');	
							Delay_ms(1000);
							}
							
							else
							{
							GREEN=1;
							YELLOW=0;
							RED=0;	
							c_wr(0x01);
							Delay_ms(1);
							c_wr(0x80);
							Delay_ms(5);  
							d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
							c_wr(0xC0);  
							d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
							d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('6');
							c_wr(0x90);		
							d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
							d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
							c_wr(0xD0);
							d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' '); 	
							d_wr('O');d_wr('K');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');	
							Delay_ms(1000);
							RH_FLAG++;
							final_cheak_tube++;
							}
							
							//						Channel_Read(1);
													Delay_ms(20);
							
							if(RH_yellow_flag==0)
							{
									if((f==2)&&(tube_24_flag!=2)) //LOW_BEAM_F_B==1 &&
									{
									RH_red_flag=1;
									RH_yellow_flag=0;
									RED=1;
									GREEN=0;
									Delay_ms(1);
									YELLOW=0;
									Delay_ms(200);	
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('6');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
								 		d_wr(' ');d_wr('P'); d_wr('C'); d_wr('B'); d_wr(' ');  	
									d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');d_wr(' ');
									Delay_ms(1000);
									}
									else
									{
									GREEN=1;
									YELLOW=0;
									RED=0;
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('6');
									c_wr(0x90);		
									d_wr(' ');d_wr('H');d_wr('I');d_wr('G');d_wr('H');d_wr(' ');d_wr('I');d_wr('N');
									d_wr('T');d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('O');d_wr('K');d_wr(' ');
									d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' ');d_wr(' '); 
									
										
									Delay_ms(1000);
									RH_FLAG++;
									final_cheak_tube++;
									
									}	
							
							}
							else
							{
									c_wr(0x01);
									Delay_ms(1);
									c_wr(0x80);
									Delay_ms(5);  
									d_wr(' ');d_wr('R');d_wr('H');d_wr(' ');d_wr('P'); d_wr('C');d_wr('B'); 
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr('I');d_wr('N'); d_wr('G');
									c_wr(0xC0);  
									d_wr(' ');d_wr('T');d_wr('E');d_wr('S');d_wr('T');d_wr(' '); d_wr('V');d_wr('O'); 
									d_wr('L');d_wr('T');d_wr('A');d_wr('G');d_wr('E');d_wr(':');d_wr('1'); d_wr('6');
									c_wr(0x90);		
									d_wr(' ');d_wr('L');d_wr('0');d_wr('W');d_wr(' ');d_wr('I');d_wr('N');d_wr('T');
									d_wr('E');d_wr('N');d_wr('S');d_wr('I');d_wr('T');d_wr('Y');d_wr(' ');d_wr(' ');
									c_wr(0xD0);
									d_wr(' ');d_wr('P');d_wr('C');d_wr('B');d_wr(' ');d_wr('R'); 
									d_wr('E');d_wr('J');d_wr('E');d_wr('C');d_wr('T');d_wr(' ');
									RH_yellow_flag=0;	
									Delay_ms(1000);
							}
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

void current_read()
{
	TRISCbits.TRISC4=1;
	ANSELCbits.ANSC4=1;
	ADCON2=0xB8;
		ADCON0=0x40;          //RC4
        ADCON1=0x05; 
        ADCON0=0x41;
        
        ADCON0=0x43;

	   while((ADCON0&0x02)!=0x00);
       {
       }
     x= (256*ADRESH) + ADRESL;
	 x1=x*1.2125;   //0.07; 
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

void v24_ps()
{
//						Delay_ms(1000);
//						Channel_Read_LH(3); 
//						delayms(10);
//						//voltage_read();
//						//serial_display(x);
//						if(tube_24_flag==2)//HIGH_BEAM_F_B==1 &&
//						{
//						//final_cheak_tube++;
//						GREEN=0;
//						
//						YELLOW=0;
//						RED=1;	
//						c_wr(0x01);
//						Delay_ms(10);	
//						c_wr(0x80); 
//						Delay_ms(20);	
//						d_wr('2'); d_wr('4'); d_wr('V');d_wr(' '); d_wr('P'); d_wr('O'); d_wr('W'); d_wr('E'); d_wr('R');d_wr(' '); 
//						d_wr('S'); d_wr('U'); d_wr('P');d_wr('P'); d_wr('L'); d_wr('Y');
//						c_wr(0xC0); 
//						Delay_ms(2);	
//						d_wr('*');	d_wr('L'); d_wr('0'); d_wr('W');d_wr(' ');
//						d_wr('I'); 	d_wr('N'); d_wr('T'); d_wr('E');d_wr('N');	d_wr('C'); d_wr('I');d_wr('T'); d_wr('Y');d_wr('*');
//						c_wr(0x92);
//						Delay_ms(2);	
//						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
//						//d_wr(' '); d_wr('O'); d_wr('K'); 
//						d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
//						c_wr(0xD0); 
//						lcd_num_display(final_cheak_tube);
//						while(START_KEY!=0)
//							{
//							 Delay_ms(2);
//							}
//						Delay_ms(200);
//						if(power_argument<3)
//						{
//						final_cheak_tube=1;
//						}
//						else
//						{
//						final_cheak_tube=6;
//						}
//						power_argument=11;
//						}
//						
//						else
//						{
//						YELLOW=0;
//						RED=0;
//						GREEN=1;
//						c_wr(0x01);
//						Delay_ms(10);
//						c_wr(0x80); 
//						Delay_ms(20);	
//						d_wr('2'); d_wr('4'); d_wr('V');d_wr(' '); d_wr('P'); d_wr('O'); d_wr('W'); d_wr('E'); d_wr('R');d_wr(' '); 
//						d_wr('S'); d_wr('U'); d_wr('P');d_wr('P'); d_wr('L'); d_wr('Y');	
//						c_wr(0x92); 
//						Delay_ms(2);	
//						d_wr('T'); d_wr('U'); d_wr('B');d_wr('E');
//					//d_wr(' '); 	d_wr('R'); d_wr('E'); d_wr('J');d_wr('E');	d_wr('C'); d_wr('T');
//						d_wr(' '); d_wr('O'); d_wr('K'); 
//						c_wr(0xD0); 
//						lcd_num_display(final_cheak_tube);
//						}	
//						Delay_ms(1000);
}

void cal_lux_value()
{
if(SELECT_KEY==1)
{
Channel_Read_RH(4);
Delay_ms(10);

Delay_ms(500);
adc_avg_mv1=((adc_val1_mv+adc_val2_mv+adc_val3_mv+adc_val4_mv)/4);
Delay_ms(10);
}
if(SELECT_KEY==0)
{
Channel_Read_LH(8);
Delay_ms(10);
Delay_ms(500);
adc_avg_mv1=((adc_val5_mv+adc_val6_mv+adc_val7_mv+adc_val8_mv)/4);
Delay_ms(10);
}
}