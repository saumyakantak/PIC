               
          

#include <p18F46K22.h>
//#include "delays.h"

#define data PORTB   // DATA PIN OF LCD
#define RS PORTAbits.RA1  // LCD RS  PIN 
#define v_sel PORTCbits.RC1 // LCD  RW PIN
#define E PORTAbits.RA5   // LCD E PIN

// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR        0x00
#define LCD_LINE1_DDRAMADDR        0x40
#define LCD_LINE2_DDRAMADDR        0x10
#define LCD_LINE3_DDRAMADDR        0x50


void toggle();                // FOR ENABLE ON AND OFF WE USED TOGGLE 
void init_lcd();              // LCD INITIALISATION 
void c_wr(unsigned int item); // LCD COMMAND WRITE`RT
void d_wr(unsigned int item); // LCD DATA WRITE
void lcd_string(unsigned int *str);
void lcd_gotoxy(unsigned char row,unsigned char column);
void display(unsigned char row,unsigned char col,unsigned char *lcd_string);
void Delay(unsigned int itime);

