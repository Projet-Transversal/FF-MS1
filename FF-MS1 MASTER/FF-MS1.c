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

sbit LED = P1^6;
sbit Button = P3^7;
sbit FREQ_OUT = P0^4;
sbit SLAVE_NSS = P0^5;
int i = 0;
// Prototypes de Fonctions

void Transfert(){
	SLAVE_NSS = 0;
	SPI0DAT = 'E';
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void) {
       
			int i;
	
	  Init_Device();  // Appel des configurations globales
	  
// D�but Insertion Code Configuration des p�riph�riques ***********************
		EA = 1;
		LED = 0;
		SLAVE_NSS = 1;
	
// Fin Code Initialisations ***************************************************
	
// D�but Insertion Code Phase D�marrage ***************************************	
			
			
// Fin Code phase D�marrage	***************************************************
	
	
	while(1)
		{
			for(i = 0; i < 999; i++);
			Transfert();
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
	SLAVE_NSS = 1;
}
