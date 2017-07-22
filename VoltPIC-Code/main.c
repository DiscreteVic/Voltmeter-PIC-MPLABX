/*
 * File:   LED1.c
 * Author: Usuario
 * Created on diciembre 2015
 */

#include <pic16f88.h> 
#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#include <VoltPicLib.h>
// CONFIG1
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator; port I/O function on both RA6/OSC2/CLKO pin and RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#pragma config DEBUG = OFF
// CONFIG2
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)

#define _XTAL_FREQ 4000000

//PERIFÉRICOS UTILIZADOS EN LA PLACA DE EXPANSIÓN



void main(void) {
    TRISA=0b00000000;    //Port A configuration 
    TRISB=0b01000000;    //Port B configuration A6 INPUT
    OSCCON = 0b01101100; //110 -> 4MHz
    ANSEL = 0b00100000;  //AN6 analogic
    
    OPTION_REGbits.nRBPU = 0; //Pull-up resistor at port B outputs
    
    PORTB=0;
    PORTA=0;
    
    int result;
    float measure;
    
    while(1){
        result = convertAD(5);    
        measure = 0.00488758*result;    
        
        disp7WriteNum(measure);
        
    } 
    return;
}