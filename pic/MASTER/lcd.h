#include "p18f46k22.h"
#include "delays.h"
#include "config.h"

void delay(int a);
void Delay_us(unsigned int us);
void Delay_ms(unsigned int ms);
void lcd_string(unsigned int *str);
void lcd_gotoxy(unsigned char row,unsigned char column);
void display(unsigned char row,unsigned char col,unsigned char *lcd_string);
void init_lcd();
void c_wr(unsigned int item);
void d_wr(unsigned int item);

