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
char xdata message[10];
char* ptr_message = &message;
char xdata sendBuffer[14];
char* ptr_sendBuffer = &sendBuffer;
char* ogptr_sendBuffer = &sendBuffer;
char xdata recieveBuffer[14];
char* ptr_recieveBuffer;
char mCounter = 0;
char i = 0;
char j = 0;
char k = 0;
char lMessage = 0;
char nb_char_vide = 0;
char SPIlength;
bit EOR_flag = 0; //End of Reception flag
bit recieve_flag = 0;

// Prototypes de Fonctions

void Codage(char SPIlength, char* ptr_sendBuffer, char* ptr_message){
	k=0;
	if (mCounter == 0){
		*ptr_sendBuffer++ = 'R';
		while (k < SPIlength){
		*ptr_sendBuffer++ = *ptr_message++;
		k++;
		}
		//TODO : Remplir le reste du SendBuffer
		*ptr_sendBuffer++ = 'U';
		*ptr_sendBuffer++ = 'H';
	}
}

void Envoi(char SPIlength, char* ptr_sendBuffer){
	mCounter++;
	if (mCounter == SPIlength + 4){
		SPI0DAT = 'B';
		mCounter = 0;
		ptr_sendBuffer = ogptr_sendBuffer;
	}
	else{
		SPI0DAT = *ptr_sendBuffer++;
	}
}

void Decodage(){ //Cette fonction écrit le message reçu dans le messageBuffer
	if (EOR_flag) {
		EOR_flag = 0;
		if (recieveBuffer[0] == 'B' && recieveBuffer[1] == 'R'){
			while (j != lMessage){
				messageBuffer[j] = recieveBuffer[j+2];
				j++;
				}
// Vérification du message-test			
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
	  
// Début Insertion Code Configuration des périphériques ***********************
		EA = 1;
		LED = 0;
	
// Fin Code Initialisations ***************************************************
	
// Début Insertion Code Phase Démarrage ***************************************	
			
			
// Fin Code phase Démarrage	***************************************************
	
	
	while(1)
	{
//		if (recieve_flag){
//			//On injecte IMMEDIATEMENT une valeur dans le SPI0DAT
//			// Mettez votre message dans le buffer "message", et indiquez sa longueur
//			message[0] = 'C';
//			message[1] = 'J';
//			SPIlength = 2;
//			Codage(SPIlength, ptr_sendBuffer, ptr_message);
//			Envoi(SPIlength,ptr_sendBuffer);
			//La fonction Envoi garde une idée de l'avancement du message avec un compteur global
//		}
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
	recieve_flag = 1;
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