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
char xdata messageBuffer[10];
char xdata recieveBuffer[14];
char* ptr_recieveBuffer;
char mCounter = 0;
char i = 0;
char j = 0;
char lMessage = 0;
char nb_char_vide = 0;
bit EOR_flag = 0; //End of Reception flag

// Prototypes de Fonctions

void Decodage(){ //Cette fonction �crit le message re�u dans le messageBuffer
	if (EOR_flag) {
		EOR_flag = 0;
		if (recieveBuffer[0] == 'B' && recieveBuffer[1] == 'R'){
			while (j != lMessage){
				messageBuffer[j] = recieveBuffer[j+2];
				j++;
				}
/////////////// V�rification du message-test			
//			if (messageBuffer[0] == 'E' && messageBuffer[1] == 'A'){
//				LED = 1;
//				}
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
	  
// D�but Insertion Code Configuration des p�riph�riques ***********************
		EA = 1;
		LED = 0;
	
// Fin Code Initialisations ***************************************************
	
// D�but Insertion Code Phase D�marrage ***************************************	
			
			
// Fin Code phase D�marrage	***************************************************
	
	
	while(1)
	{
		Decodage();
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
	recieveBuffer[i] = SPI0DAT;
	if (recieveBuffer[i] == '&'){
		nb_char_vide++;
	}
	if (recieveBuffer[i] == 'H' && recieveBuffer[i-1] == 'U'){
		lMessage = i-3-nb_char_vide;
		i = 0;
		nb_char_vide = 0;
		EOR_flag = 1;
	}
	if (i == 19){
		i = 0;
	}
	i++;
}