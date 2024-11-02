/* 
 * File:   RS-232.c
 * Author: Familia CS
 *
 * Created on 27 de febrero de 2024, 19:21
 */
#include <string.h>
#include <stdio.h>
#include "CFG_RS232.h"
#include "CFG_16F628A.h"

//------------------------------------------------------------------------------
void Uart_Init(int baudios)                                                     // Funcion para configurar el puerto UART.
{
    if(baudios == 9600)
        {
        INTCONbits.GIE = 1;                                                     // Habilta interrupciones enmascaradas todas 
        INTCONbits.PEIE = 1;                                                    // Habilita todas las interrupciones    
        PIE1bits.RCIE = 1;                                                      // Habilta interrupciones por recibimiento de datos UART.
        TRISBbits.TRISB1 = 1;                                                   // Pin RX como una entrada digital
        TRISBbits.TRISB2 = 0;                                                   // Pin TX como una salida digital
        TXSTAbits.TXEN = 1;                                                     // Habilitar transmision
        TXSTAbits.BRGH = 1;                                                     // Habilitar transmision de alta velocidad
        RCSTAbits.SPEN = 1;                                                     // Habilitar puerto serial en PORTB
        RCSTAbits.CREN = 1;                                                     // Habilitar recepcion continua
        SPBRG = 25;                                                             // Para 9600 Baudios
        }
}
//******************************************************************************
void Uart_Send_Char(char INFO)                                                // Funcion para transmitir caracteres
{
    while(TXSTAbits.TRMT == 0);                                                 // Verifico si TRMT esta lleno
    TXREG = INFO;                                                             // Lo que hay en TXDATA se transmite
}
//******************************************************************************
void Uart_Send_String(char *INFO)                                               // Funcion para transmitir una cadena de caracteres
{
    char W;                                                                     // Declaro variable tipo char W
    for (W = 0; INFO[W]!='\0'; W++)                                             // Funcion FOR transmitir cadena
    {
        Uart_Send_Char(INFO[W]);                                                // Funcion para transmitir uno a uno la cadena   
    }
}
//******************************************************************************
char Uart_Read(void)                                                            // Funcion para recibir caracteres
{
    while(PIR1bits.RCIF == 0);                                                  // Verifico bandera de interrupcion por RX
    if(RCSTAbits.OERR == 1)                                                     // Verifico desbordamiento de pila FIFO RCREG
    {
        RCSTAbits.CREN = 0;                                                     // Des-habilito recepcion
        RCSTAbits.CREN = 1;                                                     // Habilito recepcion    
    }
    PIR1bits.RCIF = 0;                                                          // Borro bandera de interrupcion
    return RCREG;                                                               // Retorno con dato recibido
}
//******************************************************************************
void Uart_Read_String(char* Buf, unsigned int s_buf)                            // Funcion para recibir cadenas de caracteres
{
    unsigned int cont_buf = 0;                                                  // Creo variable tipo entero sin signo cont_buf
    char c;                                                                     // Creo variable tipo char C
    do                                                                          // Funcion do while
    {
        c = Uart_Read();                                                        // El dato recibido lo paso a variable char "C"
        Buf[cont_buf++] = c;                                                    // Lo que est en C lo paso a "CADENA" uno a uno
        if(cont_buf >= s_buf) break;                                            // si cont_buf es igual o mayor a el size buf retire
    }while(c != '\n');                                                          // Rompe el lazo si C (dato recibido) es distinto a caracter nulo
    Buf[cont_buf-2] = '\0';
    cont_buf = 0;
}
//******************************************************************************
/*
void Uart_Read_Substring(char* cp, char* vc, int inc, int fn)                   // Funcion para descomponer cadenas de caracteres
{
    int pt = 0;
    for(int lt=inc; lt<=fn; lt++)
    {
        vc[pt] = cp[lt];
        pt++;
    }
    vc[pt] = '\0';
    pt = 0;
}                                                                                
void Uart_Read_StringUntil(char stop_c, char* buf, unsigned int st_size)        // Funcion para descomponer cadenas de caracteres, bit stop
{
    unsigned int rx_cont = 0;
    while(*(buf-1) != stop_c)
    {
        rx_cont++;
        *buf++ = Uart_Read();
        if(rx_cont >= st_size) break;
    }
    *--buf = 0;
}
*/ 