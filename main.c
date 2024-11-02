/*
 * File:   main.c
 * Author: Familia CS
 *
 * Created on 23 de febrero de 2024, 18:38
 */


#include <xc.h>
#include <pic16f628a.h>
#include <string.h>
#include <stdio.h>
#include "CFG_16F628A.h"
#include "CFG_RS232.h"

//--------------------------------Interrupcion----------------------------------
void __interrupt () RX_DATO (void)
{
    if (PIR1bits.RCIF == 1)
    {
        Uart_Read_String(cadena, 20);                                           // Lee la cadena recibida y la almacena
//******************************************************************************    
            if(!strcmp(cadena, "OK"))                                           // Si la cadena es "BLE_C", ENVIENDE BLE_OK el led
            {
            OK = 1;                                                             // ENCIENDE LED DE BLE_OK
            ERROR = 0;
            }
//******************************************************************************    
            if(!strcmp(cadena, "ERROR"))                                        // Si la cadena es "BLE_C", ENVIENDE BLE_OK el led
            { 
            OK = 0;                                                             // APAGA LED DE BLE_NOK
            ERROR = 1;
            }    
//******************************************************************************
        PIR1bits.RCIF = 0;
    }
}  
//------------------------------------------------------------------------------

void main(void)
{
    TRISA = 0;                                                                  //Puertos A como salidas
    TRISB = 0x12;                                                               //Puertos B como salidas
    PORTA = 0, PORTB = 0;                                                       //Puerto A,B,C,D y E a cero todos los pines
    CMCON = 0x07;                                                               //DESACTIVA LOS COMPARADORES
    OPTION_REGbits.PSA = 0, OPTION_REGbits.PS0 = 0,OPTION_REGbits.PS1 = 0,OPTION_REGbits.PS2 = 0; 
    Uart_Init(9600);
    /*
    Uart_Tx_String("Mensaje de prueba"); 
    Uart_Tx(FIN_TEXTO);
    Uart_Tx(ENTER);
    */
    unsigned char a;
    for (a=0;a<5;a++)
    {
        OK = 1;
        __delay_ms(500);
        OK = 0;
        __delay_ms(500);
        ERROR = 1;
        __delay_ms(500);
        ERROR = 0;
        __delay_ms(500);
    }
    __delay_ms(2000);
//***********************ENVIO COMANDO AT***************************************    
    Uart_Send_String("AT\r\n");    
    __delay_ms(2000);
    OK = 0;
    __delay_ms(2000);
//********************DEFINICION DE MODO WIFI***********************************    
    Uart_Send_String("AT+CWMODE_DEF=1\r\n");  
    __delay_ms(2000);
    OK = 0;
    __delay_ms(2000);    
//************************CONEXION CON AP***************************************
    Uart_Send_String("AT+CWJAP_DEF=");
    Uart_Send_Char('"');
    Uart_Send_String("DIGIFIBRA-6PRN");
    Uart_Send_Char('"');
    Uart_Send_Char(',');
    Uart_Send_Char('"');
    Uart_Send_String("ksH74442ey");
    Uart_Send_Char('"');
    Uart_Send_String("\r\n");
    __delay_ms(2000);
    OK = 0;
    __delay_ms(2000);
//-------------------------------Programa principal-----------------------------    
    while (1)
    {
        OK = 1;
        __delay_ms(100);
        OK = 0;
        __delay_ms(100);
    }
}