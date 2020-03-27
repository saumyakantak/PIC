
#include "p18f46k22.h"
#include "adc.h"

unsigned int k1,m1,k2,m2,k3,m3,k4,m4,k5,m5,k6,m6;



void adc_init()
{
  

     
        ADCON0=0x00; 
        ADCON1=0x05; 
        ADCON0=0x01;
        delay(50);
        ADCON0=0x03;

}

unsigned short a2dConvert10bit(unsigned char ch)
{
  



       
			while((ADCON0&0x02)!=0x00);
        {
         }
   k1=ADRESH;
   m1=ADRESL;
   k1=k1<<8;
   m1=k1|m1;
}
    



