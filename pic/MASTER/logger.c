#include "p18f46k22.h"
#include "param.h"
#include "keypad.h"
#include "config.h"
#include"datatypes.h"
void EEPROM_Load(void);

unsigned char trigger_Sec_timer,trigger_mSec_timer;

extern unsigned adc_val1,adc_val2,adc_val3,adc_val4,adc_val5,adc_val6,adc_val7,adc_val8,adc_val9,adc_val10,adc_val11,adc_val12,adc_val13,adc_val14,adc_val15,adc_val16;
extern unsigned int adc_val1_mv,adc_val2_mv,adc_val3_mv,adc_val4_mv,adc_val5_mv,adc_val6_mv,adc_val7_mv,adc_val8_mv;
extern unsigned int adc_val9_mv,adc_val10_mv,adc_val11_mv,adc_val12_mv,adc_val13_mv,adc_val14_mv,adc_val15_mv,adc_val16_mv;
extern unsigned int k1,m1,k2,m2,k3,m3,k4,m4,k5,m5,k6,m6,k7,m7,k8,m8,k9,m9,k10,m10,k11,m11,k12,m12,k13,m14,k14,m10,k15,m15,k16,m16;

unsigned int max_range1;
unsigned int min_range1;
unsigned int max_range2;
unsigned int min_range2;
unsigned int max_range3;
unsigned int min_range3;
unsigned int max_range4;
unsigned int min_range4;
unsigned int max_range5;
unsigned int min_range5;
unsigned int max_range6;
unsigned int min_range6;
unsigned int max_range7;
unsigned int min_range7;
unsigned int max_range8;
unsigned int min_range8;



unsigned int max_range24;
unsigned int min_range24;
unsigned int max_range25;
unsigned int min_range25;
signed int count ; // location 10
signed int count2 ;// location 10
unsigned int initial_cheak=0;


unsigned int max_range26;
 unsigned int min_range26;
unsigned int min_range27;

unsigned int max_range28;
unsigned int min_range28;

unsigned int max_range29;
unsigned int min_range29;
//signed Target_count;
void Wait();

void lcd_num_display(unsigned int  ans0);







void lcd_num_display(unsigned int  ans0)
{

	unsigned int a,b,c,d,e,f;
	a=(unsigned  int)ans0% 1000;//234
	b=(unsigned  int)ans0/1000;//1
	c=(unsigned  int)a%100;//34
	d=(unsigned  int)a/100;//2
	e=(unsigned  int)c%10;//4
	f=(unsigned  int)c/10;//3

   d_wr(b+0x30);
   d_wr(d+0x30);
   d_wr(f+0x30);
   d_wr(e+0x30);

}


void EEPROM_Load(void)
{
	
	initial_cheak=0;
	EEpromRead(&min_range1, MIN_VAL_LOCATION_1, 2);
	EEpromRead(&max_range1, MAX_VAL_LOCATION_1, 2);

	EEpromRead(&min_range2, MIN_VAL_LOCATION_2, 2);
	EEpromRead(&max_range2, MAX_VAL_LOCATION_2, 2);

	EEpromRead(&min_range3, MIN_VAL_LOCATION_3, 2);
	EEpromRead(&max_range3, MAX_VAL_LOCATION_3, 2);

	EEpromRead(&min_range4, MIN_VAL_LOCATION_4, 2);
	EEpromRead(&max_range4, MAX_VAL_LOCATION_4, 2);

	EEpromRead(&min_range5, MIN_VAL_LOCATION_5, 2);
	EEpromRead(&max_range5, MAX_VAL_LOCATION_5, 2);

	EEpromRead(&min_range6, MIN_VAL_LOCATION_6, 2);
	EEpromRead(&max_range6, MAX_VAL_LOCATION_6, 2);

    EEpromRead(&min_range7, MIN_VAL_LOCATION_7, 2);
	EEpromRead(&max_range7, MAX_VAL_LOCATION_7, 2);

	EEpromRead(&min_range8, MIN_VAL_LOCATION_8, 2);
	EEpromRead(&max_range8, MAX_VAL_LOCATION_8, 2);


	EEpromRead(&min_range25, MIN_VAL_LOCATION_25, 2);
	EEpromRead(&max_range25, MAX_VAL_LOCATION_25, 2);

EEpromRead(&min_range26, MIN_VAL_LOCATION_26, 2);
EEpromRead(&min_range27, MIN_VAL_LOCATION_27, 2);	

EEpromRead(&min_range28, MIN_VAL_LOCATION_28, 2);
	EEpromRead(&max_range28, MAX_VAL_LOCATION_28, 2);

EEpromRead(&min_range29, MIN_VAL_LOCATION_29, 2);
	EEpromRead(&max_range29, MAX_VAL_LOCATION_29, 2);
   
 
    if((min_range1 < 0) || (min_range1 > 5000)||(max_range1 < 0) || (max_range1 > 5000))
	{
		min_range1 = 0;
		max_range1 = 5000;
initial_cheak++;
	}
	if((min_range2 < 0) || (min_range2 > 5000)||(max_range2 < 0) || (max_range2 > 5000))
	{
		min_range2 = 0;
		max_range2 = 5000;
initial_cheak++;
	}
	if((min_range3 < 0) || (min_range3 > 5000)||(max_range3 < 0) || (max_range3 > 5000))
	{
		min_range3 = 0;
		max_range3 = 5000;
initial_cheak++;
	}
	if((min_range4 < 0) || (min_range4 > 5000)||(max_range4 < 0) || (max_range4 > 5000))
	{
		min_range4 = 0;
		max_range4 = 5000;
initial_cheak++;
	}
	if((min_range5 < 0) || (min_range5 > 5000)||(max_range5 < 0) || (max_range5 > 5000))
	{
		min_range5 = 0;
		max_range5 = 5000;
initial_cheak++;
	}
	if((min_range6 < 0) || (min_range6 > 5000)||(max_range6 < 0) || (max_range6 > 5000))
	{
		min_range6 = 0;
		max_range6 = 5000;
initial_cheak++;
	}

    if((min_range7 < 0) || (min_range7 > 5000)||(max_range7 < 0) || (max_range7 > 5000))
	{
		min_range7 = 0;
		max_range7 = 5000;
initial_cheak++;
	}
	if((min_range8 < 0) || (min_range8 > 5000)||(max_range8 < 0) || (max_range8 > 5000))
	{
		min_range8 = 0;
		max_range8 = 5000;
initial_cheak++;
	}


	
if((min_range25 <= 0) || (min_range25 >= 10000))
	{
		min_range25 = 9999;
//		//max_range10 = 9999;
	}
if((count<0)  || (count >9999))
	{
		count = 0;
//		//max_range10 = 9999;
	}

if((min_range28 <= 0) || (min_range28 >= 10000))
	{
		min_range28 = 9999;
//		//max_range10 = 9999;
	}

if((min_range29 < 0) || (min_range29 > 10000))
	{
		min_range29 = 9999;
//		max_range2 = 5000;
//initial_cheak++;
	}

if((count2<0)  || (count2 >9999))
	{
		count2 = 0;
//		//max_range10 = 9999;
	}

	if((min_range26 < 0) || (min_range26 > 5000))
	{
		min_range26 = 0;
	}
	if((min_range27 < 0) || (min_range27 > 5000))
	{
		min_range26 = 0;
	}
	
	
//	}
	
	
}
