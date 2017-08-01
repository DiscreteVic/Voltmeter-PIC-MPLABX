
#include <pic16f88.h> 
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define _XTAL_FREQ 4000000


#define segA PORTAbits.RA0
#define segB PORTAbits.RA1
#define segC PORTAbits.RA2
#define segD PORTAbits.RA3
#define segE PORTAbits.RA4
#define segF PORTBbits.RB5
#define segG PORTBbits.RB0

#define dig1 PORTBbits.RB1
#define dig2 PORTBbits.RB2
#define dig3 PORTBbits.RB3

#define comma PORTBbits.RB4

int t_ref = 2;

int convertAD(int config)
{
 //Falta config. el TRISx y quitar las interrupciones si no se van a utilizar.
  int selecAN[7]={0x01,0x02,0x04,0x08,0x10,0x20,0x40};
  int ch;
  ANSEL=0;
  ADCON0 = 0;
  ANSEL = selecAN[config];
  //Realizamos desplazamiento del numero del canal pasado como config,
  //ya que los bits de canal son el bit 5,4,3 del ADCON0.
  ch=(config<<3);
  ADCON0 = (ch|0b11000001);
  //Justificacion a la derecha.(Vref+=Vdd,Vref-=Vss)
  ADCON1=0b10000000;
  __delay_ms(1);         //Esperamos tiempo de adquisición min 20microSeg.
  ADCON0bits.GO = 1;   //Inciamos la conversión.
  while(ADCON0bits.GO_nDONE);  //Esperamos a que finalice la conversión.

  return (((unsigned int)ADRESH)<<8)|(ADRESL);  //Devolvemos resultado.
}

void pos(int digit) {
	switch (digit) {
	case 1:
		dig1 = 1;
		dig2 = 0;
		dig3 = 0;
		break;
	case 2:
		dig1 = 0;
		dig2 = 1;
		dig3 = 0;
		break;
	case 3:
		dig1 = 0;
		dig2 = 0;
		dig3 = 1;
		break;
	}
}
void disp7WriteDig(int digit, int position) {
	pos(position);
	switch (digit) {
	case 0:
		segA = 0;
		segB = 0;
		segC = 0;
		segD = 1;
		segE = 0;
		segF = 0;
		segG = 0;
		break;
	case 1:
		segA = 1;
		segB = 1;
		segC = 0;
		segD = 1;
		segE = 1;
		segF = 0;
		segG = 1;
		break;
	case 2:
		segA = 0;
		segB = 0;
		segC = 1;
		segD = 0;
		segE = 1;
		segF = 0;
		segG = 0;
		break;
	case 3:
		segA = 1;
		segB = 0;
		segC = 0;
		segD = 0;
		segE = 1;
		segF = 0;
		segG = 0;
		break;
	case 4:
		segA = 1;
		segB = 1;
		segC = 0;
		segD = 0;
		segE = 0;
		segF = 0;
		segG = 1;
		break;
	case 5:
		segA = 1;
		segB = 0;
		segC = 0;
		segD = 0;
		segE = 0;
		segF = 1;
		segG = 0;
		break;
	case 6:
		segA = 0;
		segB = 0;
		segC = 0;
		segD = 0;
		segE = 0;
		segF = 1;
		segG = 0;
		break;
	case 7:
		segA = 1;
		segB = 1;
		segC = 0;
		segD = 1;
		segE = 1;
		segF = 0;
		segG = 0;
		break;
	case 8:
		segA = 0;
		segB = 0;
		segC = 0;
		segD = 0;
		segE = 0;
		segF = 0;
		segG = 0;
		break;
	case 9:
		segA = 1;
		segB = 1;
		segC = 0;
		segD = 0;
		segE = 0;
		segF = 0;
		segG = 0;
		break;
	}
	__delay_ms(t_ref);
}
void disp7WriteNum(float  num_f) {
	comma = 1;
	num_f = 2 * num_f;
	int mul = 1;
	int num_i = 0;
	// Transformation of float number, choosing decimals
	if (num_f < 1) mul = 1000;
	if (num_f >= 1 && num_f < 10) mul = 100;
	if (num_f >= 10) mul = 10;

	num_i = (int)(num_f*mul); // Integer number with cipher without comma


	if (num_f >= 1 && num_f < 10)comma = 0;
	else comma = 1;
	disp7WriteDig((num_i / 100), 1); //Write first cipher 

	if (num_f >= 10)comma = 0;
	else comma = 1;
	disp7WriteDig(((num_i - (num_i / 100) * 100) / 10), 2); //Write second cipher

	comma = 1;
	disp7WriteDig(((num_i - (num_i / 100) * 100) - ((num_i - (num_i / 100) * 100) / 10) * 10), 3); //Write third cipher

}

