
#include<p18f46k22.h>
#define input1 PORTAbits.RA0
#define LED_Y PORTCbits.RC3
#define LED_Y1 PORTCbits.RC4
#define LED_Y2 PORTCbits.RC5
#define LED_R PORTCbits.RC6
#define LED_G PORTCbits.RC7
#define stamp PORTDbits.RD1
#define  buzzer PORTDbits.RD2
#define  buzzer1 PORTDbits.RD3
#define data PORTB   // DATA PIN OF LCD
#define RS PORTCbits.RC0  // LCD RS  PIN 
#define RW PORTCbits.RC1 // LCD RW PIN
#define E PORTCbits.RC2   // LCD E PIN
void delay(unsigned int b);
unsigned int sp,sj;

void main()
{
	unsigned char i,a[]="SWITCH TESTER";
	
	unsigned int flag1=0;
	unsigned int flag2=0;
	unsigned int flag3=0;
	unsigned int j,count=0;
	unsigned char off[]="SWITCH OFF";
	unsigned char cval[]="COUNT VALUE:";
	unsigned char stg2f[]="STAGE2 FAIL";
	unsigned char stg1f[]="STAGE1 FAIL";
	unsigned char stg2k[]="STAGE2 OK";
	unsigned char stg1k[]="STAGE1 OK";
	unsigned char rest[]="PRESS RESET";
	unsigned char testk[]="TESTED OK";
	 stamp=0;
	//input1=input2;
	TRISC=0X00;
	TRISD=0X00;
	TRISB=0X00;
	TRISAbits.TRISA0=1;
	TRISAbits.TRISA1=1;
	TRISAbits.TRISA2=1;
	ANSELAbits.ANSA0=0;
	ANSELAbits.ANSA1=0;
	ANSELAbits.ANSA2=0;
	ANSELCbits.ANSC2=0;
	ANSELCbits.ANSC3=0;
	ANSELCbits.ANSC4=0;
	ANSELCbits.ANSC5=0;
	ANSELCbits.ANSC6=0;
	ANSELCbits.ANSC7=0;
	ANSELDbits.ANSD1=0;
	LED_Y =1;
	LED_Y1=1; 
	LED_Y2=1; 
	LED_R=1;
	LED_G=1;    
			
			while(1)
			{	
				LED_Y =1;
				LED_Y1=1; 
				LED_Y2=1; 
				LED_R=1;
				LED_G=1;     
				flag1=0; 
				flag2=0;
							
				for(i=0;i<5;i++)
				 {
				     
			       /* *************************** ************** */ 
					if(input1==0 && flag1==0 && flag2==0)
					{
						flag1=1;
						flag2=0;
				    	LED_Y =0;
						LED_Y1=1; 
						LED_Y2=1; 
						LED_R=1;
						LED_G=1;    
			        	delay(1000);
			  		}      
			  
			       /* *************************** ************** */ 
			       if(input1==1 && flag1==1 && flag2==0)
			        {
			            LED_Y=1;
			            flag1=0;
			            flag2=1;
			            LED_Y1=0;
						LED_Y2=1; 
						LED_R=1;
						LED_G=1; 
			            delay(1000);
			        }    
			           
			       /* *************************** ************** */                                            
			     if(input1==1 && flag2==1 && flag1==0)
			        {
				           flag2=0;
				           count++;
			               buzzer=0;
			               LED_Y1=1;
			               LED_Y2=0;
			               LED_R=1;
						   LED_G=1;
						   LED_Y=1;
			               flag2=0;
			               flag3=1;
			               delay(3000);
			               LED_Y2=1;
			         }
			  
			       /* *************************** ************** */     
			         else
			         {
				  			LED_Y =1;
							LED_Y1=1; 
							LED_Y2=1; 
							LED_R=0;
							LED_G=1;  
					        delay(3000);
			          } 
			          
			       /* *************************** ************** */ 
			         if(i==4 && count==4)                            //for stamping purpose i=1
			         {
						count=0;
						LED_G=0;
					//	buzzer1=1;
						stamp=1;
						delay(700);
						stamp=0;
					//	buzzer1=0;
						delay(1000);
						LED_G=1;
			        }
			    }
			       
		}          
}          



void delay(unsigned int b)
{

for(sp=0;sp<b;sp++)
{
for(sj=0;sj<500;sj++)
{
}
}
}



          


