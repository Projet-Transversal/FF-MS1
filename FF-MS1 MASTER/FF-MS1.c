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
bit buffer;
char xdata bigbuffer[7];
sbit FREQ_OUT = P0^4;
sbit SLAVE_NSS = P0^5;
int flag_transfert = 0;
#define Reset_Timer3Overflow TMR3CN &= 0x04
int i = 0;
int cpt = 0;
// Prototypes de Fonctions

void Transfert(){
	SLAVE_NSS = 0;
	SPI0DAT = 'A';
	SLAVE_NSS = 1;
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
			flag_transfert = 0;
			while(flag_transfert);
			Transfert();
			for(i=0;i==10000;i++);
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

void ISR_timer3() interrupt 14{
	Reset_Timer3Overflow;
	if (cpt ==25){
		FREQ_OUT = !FREQ_OUT;
		flag_transfert = 1;
		cpt = 0;
	}
	cpt++;
}
