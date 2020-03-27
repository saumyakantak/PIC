 
 #ifndef __DATATYPES_H
 #define __DATATYPES_H
 
 typedef unsigned char UINT;
 typedef signed char INT;
 typedef char CHAR;
 typedef unsigned short UWORD;
 typedef signed char BYTE;
 typedef signed char UBYTE;
 typedef signed short WORD;
 typedef unsigned long UDWORD;
 typedef signed long DWORD; 
 typedef float  FLOAT; 
 
 typedef union {
 	UWORD data ;
 	struct {
 		BYTE low;
 		BYTE high;
 	};
 } UWORDbytes;
 
 
 typedef union {
 	UDWORD data ;
 	struct {
 		BYTE byte0;
 		BYTE byte1;
 		BYTE byte2;
 		BYTE byte3;
 	};
 	struct {
 		UWORD word0;
 		UWORD word1;
 	};
 } UDWORDbytes;
 
 
 typedef union {
 	UBYTE byte;
 	struct {
 		unsigned bit0:1;
 		unsigned bit1:1;
 		unsigned bit2:1;
 		unsigned bit3:1;
 		unsigned bit4:1;
 		unsigned bit5:1;
 		unsigned bit6:1;
 		unsigned bit7:1;
 	};
 } UBYTEbits;
 
 #define MAX_UDWORD 0xFFFFFFFF
 
 #endif //__DATATYPES_H
 
