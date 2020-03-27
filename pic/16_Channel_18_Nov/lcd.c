#include "p18f46k22.h"
//#include "delays.h"
#include "config.h"


void delay(int a);
void Delay_us(unsigned int us);
void Delay_ms(unsigned int ms);

void lcd_string(unsigned int *str)
{
int i=0;
while(str[i]!='\0')
{
d_wr(str[i]);
i++;
  Delay1KTCYx(5);
}
return ;
}




void lcd_gotoxy(unsigned char row,unsigned char column)
{   
    if(row==0)
   {
     c_wr(0x80+column);
   }
    else if(row==1)
    {  
     c_wr(0xC0+column);
    }
    else if(row==2)
    {
     c_wr(0x90+column);
    }
    else if(row==3)
    {
     c_wr(0xD0+column);
    }
}


void display(unsigned char row,unsigned char col,unsigned char *lcd_string)
    {
       lcd_gotoxy(row,col);
        while(*lcd_string)
           {
             d_wr(*lcd_string++);
           }
    }



           
	void init_lcd()
  {
	Delay_ms(30);
    c_wr(0x03);
	Delay_ms(30);
    c_wr(0x03);
	Delay_ms(30);
    c_wr(0x03);
	Delay_ms(30);
    c_wr(0x02);
 	Delay_ms(30);
    c_wr(0x28);
 	Delay_ms(30);
    c_wr(0x01);
 	Delay_ms(30);
    c_wr(0x06);
 	Delay_ms(30);
    c_wr(0x0C);
	Delay_ms(30);
   data=0x00;
}


void c_wr(unsigned int item)
  {
   unsigned int ch;
    ch=item;
    item=item&0xF0;
    data=item;
    RS=0;
  //  RW=0;
    toggle();
    ch=ch&0x0F;
    ch=ch<<4;
    data=ch;
    RS=0;
  //  RW=0;
    toggle();
  }   
    

void d_wr(unsigned int item)
  {
    unsigned int ch;
    ch=item;
    item=item&0xF0;
    data=item;
    RS=1;
 //   RW=0;
    toggle();
    ch=ch&0x0F;
    ch=ch<<4;
    data=ch;
    RS=1;
 //   RW=0;
    toggle();
  }  
  
 void toggle()
{
 delay(1);

  E=0;
  delay(1);

  E=1;
  delay(1);

  E=0;
}


void delay(int a)
{
  int j;
int i;
for(i=0;i<a;i++)
{
for(j=0;j<10;j++)
{
}
}
}



void Delay_ms(unsigned int ms)	
{
	unsigned int delay_cont,delay_cont1;
	
	for(delay_cont = 0; delay_cont < ms; delay_cont ++)
		for(delay_cont1 = 0; delay_cont1 < 113; delay_cont1 ++); 
		
}	


void Delay_us(unsigned int us)
{
	unsigned int i;
	for(i = 0; i < us; i++)
	{
		i=i;
	}
}		  
