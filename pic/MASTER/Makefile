# MPLAB IDE generated this makefile for use with GNU make.
# Project: 16_channel.mcp
# Date: Mon Jul 23 12:10:34 2018

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

16_channel.cof : keypad.o lcd.o logger.o param.o DOT_MARKER.o SERIAL.o
	$(LD) /p18F46K22 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.46\lib" "keypad.o" "lcd.o" "logger.o" "param.o" "DOT_MARKER.o" "SERIAL.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"16_channel.cof" /M"16_channel.map" /W

keypad.o : keypad.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/delays.h config.h param.h config.h DOT_MARKER.h serial.h config.h lcd.h keypad.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18f46k22.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18F46K22.h keypad.h datatypes.h
	$(CC) -p=18F46K22 "keypad.c" -fo="keypad.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

lcd.o : lcd.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/delays.h config.h lcd.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18f46k22.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18F46K22.h
	$(CC) -p=18F46K22 "lcd.c" -fo="lcd.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

logger.o : logger.c param.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/delays.h config.h logger.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18f46k22.h datatypes.h keypad.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18F46K22.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h
	$(CC) -p=18F46K22 "logger.c" -fo="logger.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

param.o : param.c param.h param.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18f46k22.h datatypes.h keypad.h
	$(CC) -p=18F46K22 "param.c" -fo="param.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

DOT_MARKER.o : DOT_MARKER.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/delays.h config.h param.h DOT_MARKER.h serial.h DOT_MARKER.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18f46k22.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18cxxx.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18F46K22.h datatypes.h keypad.h
	$(CC) -p=18F46K22 "DOT_MARKER.c" -fo="DOT_MARKER.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

SERIAL.o : SERIAL.C serial.h SERIAL.C C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18f46k22.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/p18F46K22.h
	$(CC) -p=18F46K22 "SERIAL.C" -fo="SERIAL.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "keypad.o" "lcd.o" "logger.o" "param.o" "DOT_MARKER.o" "SERIAL.o" "16_channel.cof" "16_channel.hex"

