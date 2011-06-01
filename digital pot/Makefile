# MPLAB IDE generated this makefile for use with GNU make.
# Project: digital pot.mcp
# Date: Mon May 30 21:09:17 2011

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

digital\ pot.cof : main.o
	$(LD) /l"C:\MCC18\lib" "C:\MCC18\bin\LKR\18f4455_g.lkr" "main.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"digital pot.cof" /M"digital pot.map" /W

main.o : main.c C:/MCC18/h/spi.h C:/MCC18/h/stdio.h main.c C:/MCC18/h/p18cxxx.h C:/MCC18/h/p18f4455.h C:/MCC18/h/pconfig.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h
	$(CC) -p=18F4455 "main.c" -fo="main.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "main.o" "digital pot.cof" "digital pot.hex"

