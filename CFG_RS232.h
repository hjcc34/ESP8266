/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
 
#ifndef CFG_RS232_H
#define	CFG_RS232_H

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdio.h>
#include <string.h>
#include "CFG_16F628A.h"

#define _XTAL_FREQ  4000000

#define SALTOL      0x0A
#define RETORNOC    0x0D
#define CNULL       0x00

char cadena[20];
//------------------------------------------------------------------------------
void Uart_Init(int baudios);
void Uart_Send_Char(char INFO);
void Uart_Send_String(char *INFO);
char Uart_Read(void);
void Uart_Read_String(char* Buf, unsigned int s_buf);
/*
void Uart_Read_Substring(char* cp, char* vc, int inc, int fn);
void Uart_Read_StringUntil(char stop_c, char* buf, unsigned int st_size);
*/ 

#endif	/* CFG_RS232_H */