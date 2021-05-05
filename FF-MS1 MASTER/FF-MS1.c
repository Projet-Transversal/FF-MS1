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

#define Reset_Timer3Overflow TMR3CN &= 0x04
#define Disable_Timer3 TMR3CN = 0x00

sbit LED = P1^6;
sbit Button = P3^7;
sbit SLAVE_NSS = P0^7;
int i = 0;
int SPIcounter = 0;
int SPIlength = 0;
char xdata buffer[10];
// Prototypes de Fonctions

void Transfert(char c){
	for(i=0;i < 125;i++);
	SLAVE_NSS = 0;
	for(i=0;i < 10;i++);
	SPI0DAT = c;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void) {
	
	  Init_Device();  // Appel des configurations globales
	  
// Début Insertion Code Configuration des périphériques ***********************
		EA = 1;
		LED = 0;
		SLAVE_NSS = 1;
	
// Fin Code Initialisations ***************************************************
	
// Début Insertion Code Phase Démarrage ***************************************	
			
			
// Fin Code phase Démarrage	***************************************************
	
	
	while(1)
	{
		buffer[0] = 'B';
		buffer[1] = 'R';
		buffer[2] = 'E';
		buffer[3] = 'A';
		buffer[4] = 'U';
		buffer[5] = 'H';
		SPIlength = 2;
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Fonctions de configuration des divers périphériques
//-----------------------------------------------------------------------------
// Insérez vos fonctions de configuration ici

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Fonctions d'interruptions
//-----------------------------------------------------------------------------
// Insérez vos fonctions d'interruption ici

void ISR_SPI0() interrupt 6{
	SPIF = 0;
	SLAVE_NSS = 1;
}

void ISR_TMR3() interrupt 14{
	Reset_Timer3Overflow;
	if (SPIcounter > SPIlength+3){
		SPIcounter = 0;
	}
	else {
		Transfert(buffer[SPIcounter]);
		SPIcounter++;
	}
}
