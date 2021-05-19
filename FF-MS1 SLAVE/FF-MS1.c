//-----------------------------------------------------------------------------
// TP5.c
//-----------------------------------------------------------------------------
// AUTH: Mehdi Slama & Julien Pinard
// DATE: L'aube de l'humanité
//
// Target: C8051F02x
// Tool chain: KEIL Microvision 4
//
//-----------------------------------------------------------------------------
#include <C8051F020.h>
#include "c8051F020_SFR16.h"
#include "FF-MS1_Config.h"
#include <stdlib.h>

sbit LED = P1^6;
char xdata messageBuffer[15];
char xdata recieveBuffer[20];
char* ptr_recieveBuffer;
char i = 0;
char j = 0;
char lMessage = 0;
char nb_char_vide = 0;
bit EOR_flag = 0; //End of Reception flag

// Prototypes de Fonctions

void Decodage(){ //Cette fonction écrit le message reçu dans le messageBuffer
	if (EOR_flag) {
		EOR_flag = 0;
		if (recieveBuffer[1] == 'B' && recieveBuffer[2] == 'R'){
			while (j != lMessage){
				messageBuffer[j] = recieveBuffer[j+3];
				j++;
				}
/////////////// Vérification du message-test			
			if (messageBuffer[0] == 'A' && messageBuffer[1] == 'B' && messageBuffer[2] == 'C'){
				LED = 1;
				}
			}
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void) {
       
	  Init_Device();  // Appel des configurations globales
		SPI0DAT = 'B';
	  
// Début Insertion Code Configuration des périphériques ***********************
		EA = 1;
		LED = 0;
	
// Fin Code Initialisations ***************************************************
	
// Début Insertion Code Phase Démarrage ***************************************	
			
			
// Fin Code phase Démarrage	***************************************************
	
	
	while(1)
	{
		Decodage();
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
	recieveBuffer[i] = SPI0DAT;
	if (recieveBuffer[i] == '~'){
		nb_char_vide++;
	}
	if (recieveBuffer[i] == 'H' && recieveBuffer[i-1] == 'U'){
		lMessage = i-4-nb_char_vide;
		i = 0;
		nb_char_vide = 0;
		EOR_flag = 1;
	}
	if (i == 20){
		i = 0;
	}
	i++;
}