//-----------------------------------------------------------------------------
// TP5.c
//-----------------------------------------------------------------------------
// AUTH: 
// DATE: 
//
// Target: C8051F02x
// Tool chain: KEIL Microvision 4
//
//-----------------------------------------------------------------------------
#include <C8051F020.h>
#include "c8051F020_SFR16.h"
#include "FF-MS1_Config.h"
#include "FF-MS1_Divers.h"
#include <stdlib.h>
#include <string.h>

sbit LED = P1^6;
sbit Button = P3^7;
char xdata buffer[10];
char xdata mBuffer[10];
int i = 0;
int j = 0;
int lMessage = 0;
bit recieve_flag = 0;

// Prototypes de Fonctions

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void) {
       
	  Init_Device();  // Appel des configurations globales
	  
// D�but Insertion Code Configuration des p�riph�riques ***********************
		EA = 1;
		LED = 0;
	
// Fin Code Initialisations ***************************************************
	
// D�but Insertion Code Phase D�marrage ***************************************	
			
			
// Fin Code phase D�marrage	***************************************************
	
	
	while(1)
	{
		if (recieve_flag) {
			recieve_flag = 0;
			if (buffer[1] == 'B' && buffer[2] == 'R'){
				while (j != lMessage){
					mBuffer[j] = buffer[j+3];
					j++;
					}						
				if (mBuffer[0] == 'E' && mBuffer[1] == 'A'){
					LED = 1;
					}
				}
			}
		}
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Fonctions de configuration des divers p�riph�riques
//-----------------------------------------------------------------------------
// Ins�rez vos fonctions de configuration ici

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Fonctions d'interruptions
//-----------------------------------------------------------------------------
// Ins�rez vos fonctions d'interruption ici

void ISR_SPI0() interrupt 6{
	SPIF = 0;
	buffer[i] = SPI0DAT;
	i++;
	if (buffer[i] == 'H' && buffer[i-1] == 'U'){
		lMessage = i-4;
		i = 0;
		recieve_flag = 1;
	}
	if (i == 10){
		i = 0;
	}
}