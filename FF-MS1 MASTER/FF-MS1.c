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
char xdata buffer[7];
// Prototypes de Fonctions
void Exe(){
	if (buffer == 'L'){
		LED = 1;
	}
}
void Bouton() {
	if (Button == 0){
		SPI0DAT = 'L';
	}
	
}

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
			if (SPIF == 1){
				*buffer = SPI0DAT;
				SPIF = 0;
			}		
		Exe();
		Bouton();
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
