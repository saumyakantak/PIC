
#include <p18F46K22.h>
void UART_Init2(void);
void send_str(unsigned char *ptr); 
void send_char(unsigned char x);
void send_strCom2(const rom unsigned char *ptr);
void send_charCom2(unsigned char x);
void serRX2(void);
void serial_display(unsigned int  ans0);
void serial_display_A(unsigned int  ans0);
void serial_display_mv(unsigned int  ans0);
void serial_display_num(unsigned int  ans0);
