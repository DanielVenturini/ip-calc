all:	ipcalc

ipcalc:	libraries
	gcc ipcalc.c -o ipcalc -lm

libraries:
	gcc functions.h