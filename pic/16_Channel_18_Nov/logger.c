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
unsigned int max_range9;
unsigned int min_range9;
unsigned int max_range10;
unsigned int min_range10;
unsigned int max_range11;
unsigned int min_range11;
unsigned int max_range12;
unsigned int min_range12;
unsigned int max_range13;
unsigned int min_range13;
unsigned int max_range14;
unsigned int min_range14;
unsigned int max_range15;
unsigned int min_range15;
unsigned int max_range16;
unsigned int min_range16;
unsigned int max_range17;
unsigned int min_range17;
unsigned int max_range18;
unsigned int min_range18;
unsigned int max_range19;
unsigned int min_range19;
unsigned int max_range20;
unsigned int min_range20;
unsigned int max_range21;
unsigned int min_range21;
unsigned int max_range22;
unsigned int min_range22;
unsigned int max_range23;
unsigned int min_range23;
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
	if(v_sel==1)
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

	EEpromRead(&min_range9, MIN_VAL_LOCATION_9, 2);
	EEpromRead(&max_range9, MAX_VAL_LOCATION_9, 2);

	
	EEpromRead(&min_range10, MIN_VAL_LOCATION_10, 2);
	EEpromRead(&max_range10, MAX_VAL_LOCATION_10, 2);

	EEpromRead(&min_range11, MIN_VAL_LOCATION_11, 2);
	EEpromRead(&max_range11, MAX_VAL_LOCATION_11, 2);

	EEpromRead(&min_range12, MIN_VAL_LOCATION_12, 2);
	EEpromRead(&max_range12, MAX_VAL_LOCATION_12, 2);

	EEpromRead(&min_range13, MIN_VAL_LOCATION_13, 2);
	EEpromRead(&max_range13, MAX_VAL_LOCATION_13, 2);

	EEpromRead(&min_range14, MIN_VAL_LOCATION_14, 2);
	EEpromRead(&max_range14, MAX_VAL_LOCATION_14, 2);

	EEpromRead(&min_range15, MIN_VAL_LOCATION_15, 2);
	EEpromRead(&max_range15, MAX_VAL_LOCATION_15, 2);

	EEpromRead(&min_range16, MIN_VAL_LOCATION_16, 2);
	EEpromRead(&max_range16, MAX_VAL_LOCATION_16, 2); 

	EEpromRead(&min_range17, MIN_VAL_LOCATION_17, 2);
	EEpromRead(&max_range17, MAX_VAL_LOCATION_17, 2);

	EEpromRead(&min_range18, MIN_VAL_LOCATION_18, 2);
	EEpromRead(&max_range18, MAX_VAL_LOCATION_18, 2);

	EEpromRead(&min_range19, MIN_VAL_LOCATION_19, 2);
	EEpromRead(&max_range19, MAX_VAL_LOCATION_19, 2);

	
	EEpromRead(&min_range20, MIN_VAL_LOCATION_20, 2);
	EEpromRead(&max_range20, MAX_VAL_LOCATION_20, 2);

	EEpromRead(&min_range21, MIN_VAL_LOCATION_21, 2);
	EEpromRead(&max_range21, MAX_VAL_LOCATION_21, 2);

	EEpromRead(&min_range22, MIN_VAL_LOCATION_22, 2);
	EEpromRead(&max_range22, MAX_VAL_LOCATION_22, 2);

	EEpromRead(&min_range23, MIN_VAL_LOCATION_23, 2);
	EEpromRead(&max_range23, MAX_VAL_LOCATION_23, 2);

	EEpromRead(&min_range24, MIN_VAL_LOCATION_24, 2);
	EEpromRead(&max_range24, MAX_VAL_LOCATION_24, 2);

	EEpromRead(&min_range25, MIN_VAL_LOCATION_25, 2);
	EEpromRead(&max_range25, MAX_VAL_LOCATION_25, 2);

EEpromRead(&min_range26, MIN_VAL_LOCATION_26, 2);
EEpromRead(&min_range27, MIN_VAL_LOCATION_27, 2);	

EEpromRead(&min_range28, MIN_VAL_LOCATION_28, 2);
	EEpromRead(&max_range28, MAX_VAL_LOCATION_28, 2);
   
 
    if((min_range1 < 0) || (min_range1 > 5000)||(max_range1 < 0) || (max_range1 > 5000))
	{
		min_range1 = 0010;
		max_range1 = 0500;
initial_cheak++;
	}
	if((min_range2 < 0) || (min_range2 > 5000)||(max_range2 < 0) || (max_range2 > 5000))
	{
		min_range2 = 0010;
		max_range2 = 0500;
initial_cheak++;
	}
	if((min_range3 < 0) || (min_range3 > 5000)||(max_range3 < 0) || (max_range3 > 5000))
	{
		min_range3 = 0010;
		max_range3 = 0500;
initial_cheak++;
	}
	if((min_range4 < 0) || (min_range4 > 5000)||(max_range4 < 0) || (max_range4 > 5000))
	{
		min_range4 = 0010;
		max_range4 = 0500;
initial_cheak++;
	}
	if((min_range5 < 0) || (min_range5 > 5000)||(max_range5 < 0) || (max_range5 > 5000))
	{
		min_range5 = 0010;
		max_range5 = 0500;
initial_cheak++;
	}
	if((min_range6 < 0) || (min_range6 > 5000)||(max_range6 < 0) || (max_range6 > 5000))
	{
		min_range6 = 0010;
		max_range6 = 0500;
initial_cheak++;
	}

    if((min_range7 < 0) || (min_range7 > 5000)||(max_range7 < 0) || (max_range7 > 5000))
	{
		min_range7 = 0010;
		max_range7 = 0500;
initial_cheak++;
	}
	if((min_range8 < 0) || (min_range8 > 5000)||(max_range8 < 0) || (max_range8 > 5000))
	{
		min_range8 = 0010;
		max_range8 = 0500;
initial_cheak++;
	}

	if((min_range9 < 0) || (min_range9 > 5000)||(max_range9 < 0) || (max_range9 > 5000))
	{
		min_range9 = 0010;
		max_range9 = 0500;
initial_cheak++;
	}

if((min_range10 < 0) || (min_range10 > 5000)||(max_range10 < 0) || (max_range10 > 5000))
	{
		min_range10 = 0010;
		max_range10 = 0500;
initial_cheak++;
	}

	if((min_range11 < 0) || (min_range11 > 5000)||(max_range11 < 0) || (max_range11 > 5000))
	{
		min_range11 = 0010;
		max_range11 = 0500;
initial_cheak++;
	}
	if((min_range12 < 0) || (min_range12 > 5000)||(max_range12 < 0) || (max_range12 > 5000))
	{
		min_range12 = 0010;
		max_range12 = 0500;
initial_cheak++;
	}
	if((min_range13 < 0) || (min_range13 > 5000)||(max_range13 < 0) || (max_range13 > 5000))
	{
		min_range13 = 0010;
		max_range13 = 0500;
initial_cheak++;
	}
	if((min_range14 < 0) || (min_range14 > 5000)||(max_range14 < 0) || (max_range14 > 5000))
	{
		min_range14 = 0010;
		max_range14 =0500;
initial_cheak++;
	}
	if((min_range15 < 0) || (min_range15 > 5000)||(max_range15 < 0) || (max_range15 > 5000))
	{
		min_range15 = 0010;
		max_range15 = 0500;
initial_cheak++;
	}
	if((min_range16 < 0) || (min_range16 > 5000)||(max_range16 < 0) || (max_range16 > 5000))
	{
		min_range16 = 0010;
		max_range16 = 0500;
initial_cheak++;
	}
    if((min_range17 < 0) || (min_range17 > 5000)||(max_range17 < 0) || (max_range17 > 5000))
	{
		min_range17 = 0010;
		max_range17 = 0500;
initial_cheak++;
	}
	if((min_range18 < 0) || (min_range18 > 5000)||(max_range18 < 0) || (max_range18 > 5000))
	{
		min_range18 = 0010;
		max_range18 = 0500;
initial_cheak++;
	}

	if((min_range19 < 0) || (min_range19 > 5000)||(max_range19 < 0) || (max_range19 > 5000))
	{
		min_range19 = 0010;
		max_range19 = 0500;
initial_cheak++;
	}

	if((min_range20 < 0) || (min_range20 > 5000)||(max_range20 < 0) || (max_range20 > 5000))
	{
		min_range20 = 0010;
		max_range20 = 0500;
initial_cheak++;
	}

	if((min_range21 < 0) || (min_range21 > 5000)||(max_range21 < 0) || (max_range21 > 5000))
	{
		min_range21 = 0010;
		max_range21 = 0500;
initial_cheak++;
	}
	if((min_range22 < 0) || (min_range22 > 5000)||(max_range22 < 0) || (max_range22 > 5000))
	{
		min_range22 = 0010;
		max_range22 = 0500;
initial_cheak++;
	}
	if((min_range23 < 0) || (min_range23 > 5000)||(max_range23 < 0) || (max_range23 > 5000))
	{
		min_range23 = 0010;
		max_range23 = 0500;
initial_cheak++;
	}
	if((min_range24 < 0) || (min_range24 > 5000)||(max_range24 < 0) || (max_range24 > 5000))
	{
		min_range24 = 0010;
		max_range24 = 0500;
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
if((count2<0)  || (count2 >9999))
	{
		count2 = 0;
//		//max_range10 = 9999;
	}

	if((min_range26 < 0) || (min_range26 > 5000))
	{
		min_range26 = 0;
	}
	if((min_range27 < 0) || (min_range27 > 0012))
	{
		min_range26 = 0000;
	}
	
	
	}
	
	if(v_sel==0)
	{	
	initial_cheak=0;
	EEpromRead(&min_range1, MIN_VAL_LOCATION2_1, 2);
	EEpromRead(&max_range1, MAX_VAL_LOCATION2_1, 2);

	EEpromRead(&min_range2, MIN_VAL_LOCATION2_2, 2);
	EEpromRead(&max_range2, MAX_VAL_LOCATION2_2, 2);

	EEpromRead(&min_range3, MIN_VAL_LOCATION2_3, 2);
	EEpromRead(&max_range3, MAX_VAL_LOCATION2_3, 2);

	EEpromRead(&min_range4, MIN_VAL_LOCATION2_4, 2);
	EEpromRead(&max_range4, MAX_VAL_LOCATION2_4, 2);

	EEpromRead(&min_range5, MIN_VAL_LOCATION2_5, 2);
	EEpromRead(&max_range5, MAX_VAL_LOCATION2_5, 2);

	EEpromRead(&min_range6, MIN_VAL_LOCATION2_6, 2);
	EEpromRead(&max_range6, MAX_VAL_LOCATION2_6, 2);

    EEpromRead(&min_range7, MIN_VAL_LOCATION2_7, 2);
	EEpromRead(&max_range7, MAX_VAL_LOCATION2_7, 2);

	EEpromRead(&min_range8, MIN_VAL_LOCATION2_8, 2);
	EEpromRead(&max_range8, MAX_VAL_LOCATION2_8, 2);

	EEpromRead(&min_range9, MIN_VAL_LOCATION2_9, 2);
	EEpromRead(&max_range9, MAX_VAL_LOCATION2_9, 2);

	
	EEpromRead(&min_range10, MIN_VAL_LOCATION2_10, 2);
	EEpromRead(&max_range10, MAX_VAL_LOCATION2_10, 2);

	EEpromRead(&min_range11, MIN_VAL_LOCATION2_11, 2);
	EEpromRead(&max_range11, MAX_VAL_LOCATION2_11, 2);

	EEpromRead(&min_range12, MIN_VAL_LOCATION2_12, 2);
	EEpromRead(&max_range12, MAX_VAL_LOCATION2_12, 2);

	EEpromRead(&min_range13, MIN_VAL_LOCATION2_13, 2);
	EEpromRead(&max_range13, MAX_VAL_LOCATION2_13, 2);

	EEpromRead(&min_range14, MIN_VAL_LOCATION2_14, 2);
	EEpromRead(&max_range14, MAX_VAL_LOCATION2_14, 2);

	EEpromRead(&min_range15, MIN_VAL_LOCATION2_15, 2);
	EEpromRead(&max_range15, MAX_VAL_LOCATION2_15, 2);

	EEpromRead(&min_range16, MIN_VAL_LOCATION2_16, 2);
	EEpromRead(&max_range16, MAX_VAL_LOCATION2_16, 2); 

	EEpromRead(&min_range17, MIN_VAL_LOCATION2_17, 2);
	EEpromRead(&max_range17, MAX_VAL_LOCATION2_17, 2);

	EEpromRead(&min_range18, MIN_VAL_LOCATION2_18, 2);
	EEpromRead(&max_range18, MAX_VAL_LOCATION2_18, 2);

	EEpromRead(&min_range19, MIN_VAL_LOCATION2_19, 2);
	EEpromRead(&max_range19, MAX_VAL_LOCATION2_19, 2);

	
	EEpromRead(&min_range20, MIN_VAL_LOCATION2_20, 2);
	EEpromRead(&max_range20, MAX_VAL_LOCATION2_20, 2);

	EEpromRead(&min_range21, MIN_VAL_LOCATION2_21, 2);
	EEpromRead(&max_range21, MAX_VAL_LOCATION2_21, 2);

	EEpromRead(&min_range22, MIN_VAL_LOCATION2_22, 2);
	EEpromRead(&max_range22, MAX_VAL_LOCATION2_22, 2);

	EEpromRead(&min_range23, MIN_VAL_LOCATION2_23, 2);
	EEpromRead(&max_range23, MAX_VAL_LOCATION2_23, 2);

	EEpromRead(&min_range24, MIN_VAL_LOCATION2_24, 2);
	EEpromRead(&max_range24, MAX_VAL_LOCATION2_24, 2);

	EEpromRead(&min_range25, MIN_VAL_LOCATION2_25, 2);
	EEpromRead(&max_range25, MAX_VAL_LOCATION2_25, 2);

EEpromRead(&min_range26, MIN_VAL_LOCATION2_26, 2);
EEpromRead(&min_range27, MIN_VAL_LOCATION2_27, 2);	

EEpromRead(&min_range28, MIN_VAL_LOCATION2_28, 2);
	EEpromRead(&max_range28, MAX_VAL_LOCATION2_28, 2);
   
 
    if((min_range1 < 10) || (min_range1 > 5000)||(max_range1 < 10) || (max_range1 > 5000))
	{
		min_range1 = 0010;
		max_range1 = 0400;
initial_cheak++;
	}
	if((min_range2 < 10) || (min_range2 > 5000)||(max_range2 < 10) || (max_range2 > 5000))
	{
		min_range2 = 0010;
		max_range2 = 0400;
initial_cheak++;
	}
	if((min_range3 < 10) || (min_range3 > 5000)||(max_range3 < 10) || (max_range3 > 5000))
	{
		min_range3 = 0010;
		max_range3 = 0400;
initial_cheak++;
	}
	if((min_range4 < 10) || (min_range4 > 5000)||(max_range4 < 10) || (max_range4 > 5000))
	{
		min_range4 = 0010;
		max_range4 = 0400;
initial_cheak++;
	}
	if((min_range5 < 10) || (min_range5 > 5000)||(max_range5 < 10) || (max_range5 > 5000))
	{
		min_range5 = 0010;
		max_range5 = 0400;
initial_cheak++;
	}
	if((min_range6 < 10) || (min_range6 > 5000)||(max_range6 < 10) || (max_range6 > 5000))
	{
		min_range6 = 0010;
		max_range6 = 0400;
initial_cheak++;
	}

    if((min_range7 < 10) || (min_range7 > 5000)||(max_range7 < 10) || (max_range7 > 5000))
	{
		min_range7 = 0010;
		max_range7 = 0400;
initial_cheak++;
	}
	if((min_range8 < 10) || (min_range8 > 5000)||(max_range8 < 10) || (max_range8 > 5000))
	{
		min_range8 = 0010;
		max_range8 = 0400;
initial_cheak++;
	}

	if((min_range9 < 10) || (min_range9 > 5000)||(max_range9 < 10) || (max_range9 > 5000))
	{
		min_range9 = 0010;
		max_range9 = 0400;
initial_cheak++;
	}

if((min_range10 < 10) || (min_range10 > 5000)||(max_range10 < 10) || (max_range10 > 5000))
	{
		min_range10 = 0010;
		max_range10 = 0400;
initial_cheak++;
	}

	if((min_range11 < 10) || (min_range11 > 5000)||(max_range11 < 10) || (max_range11 > 5000))
	{
		min_range11 = 0010;
		max_range11 = 0400;
initial_cheak++;
	}
	if((min_range12 < 10) || (min_range12 > 5000)||(max_range12 < 10) || (max_range12 > 5000))
	{
		min_range12 = 0010;
		max_range12 = 0400;
initial_cheak++;
	}
	if((min_range13 < 10) || (min_range13 > 5000)||(max_range13 < 10) || (max_range13 > 5000))
	{
		min_range13 = 0010;
		max_range13 = 0400;
initial_cheak++;
	}
	if((min_range14 < 10) || (min_range14 > 5000)||(max_range14 < 10) || (max_range14 > 5000))
	{
		min_range14 = 0010;
		max_range14 = 0400;
initial_cheak++;
	}
	if((min_range15 < 10) || (min_range15 > 5000)||(max_range15 < 10) || (max_range15 > 5000))
	{
		min_range15 = 0010;
		max_range15 = 0400;
initial_cheak++;
	}
	if((min_range16 < 10) || (min_range16 > 5000)||(max_range16 < 10) || (max_range16 > 5000))
	{
		min_range16 = 0010;
		max_range16 = 0400;
initial_cheak++;
	}
    if((min_range17 < 10) || (min_range17 > 5000)||(max_range17 < 10) || (max_range17 > 5000))
	{
		min_range17 = 0010;
		max_range17 = 0400;
initial_cheak++;
	}
	if((min_range18 < 10) || (min_range18 > 5000)||(max_range18 < 10) || (max_range18 > 5000))
	{
		min_range18 = 0010;
		max_range18 = 0400;
initial_cheak++;
	}

	if((min_range19 < 10) || (min_range19 > 5000)||(max_range19 < 10) || (max_range19 > 5000))
	{
		min_range19 = 0010;
		max_range19 = 0400;
initial_cheak++;
	}

	if((min_range20 < 10) || (min_range20 > 5000)||(max_range20 < 10) || (max_range20 > 5000))
	{
		min_range20 = 0010;
		max_range20 = 0400;
initial_cheak++;
	}

	if((min_range21 < 10) || (min_range21 > 5000)||(max_range21 < 10) || (max_range21 > 5000))
	{
		min_range21 = 0010;
		max_range21 = 0400;
initial_cheak++;
	}
	if((min_range22 < 10) || (min_range22 > 5000)||(max_range22 < 10) || (max_range22 > 5000))
	{
		min_range22 = 0010;
		max_range22 = 0400;
initial_cheak++;
	}
	if((min_range23 < 10) || (min_range23 > 5000)||(max_range23 < 10) || (max_range23 > 5000))
	{
		min_range23 = 0010;
		max_range23 = 0400;
initial_cheak++;
	}
	if((min_range24 < 10) || (min_range24 > 5000)||(max_range24 < 10) || (max_range24 > 5000))
	{
		min_range24 = 0010;
		max_range24 = 0400;
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
if((count2<0)  || (count2 >9999))
	{
		count2 = 0;
//		//max_range10 = 9999;
	}

	if((min_range26 < 0) || (min_range26 > 5000))
	{
		min_range26 = 0;
	}
	if((min_range27 < 0) || (min_range27 > 0012))
	{
		min_range26 = 0000;
	}
	
	
	}
	
	
}
