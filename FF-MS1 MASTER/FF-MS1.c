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

#define Reset_Timer3Overflow TMR3CN &= 0x04
#define Disable_Timer3 TMR3CN = 0x00

sbit LED = P1^6;
sbit Button = P3^7;
sbit SLAVE_NSS = P0^7;
char i = 0;
char mCounter = 0;
char SPIcounter = 0;
char SPIlength = 0;
char xdata message[10];
char* ptr_message = &message;
char xdata sendBuffer[14];
char* ptr_sendBuffer = &sendBuffer;
char xdata recieveBuffer[14];
char* ptr_recieveBuffer;
// Prototypes de Fonctions

void Transfert(char c){
	for(i=0;i < 125;i++);
	SLAVE_NSS = 0;
	for(i=0;i < 10;i++);
	SPI0DAT = c;
}

void Codage (char SPIlength, char* ptr_sendBuffer, char* ptr_message){
	*ptr_sendBuffer++ = 'B';
	*ptr_sendBuffer++ = 'R';
	while (i < SPIlength){
		*ptr_sendBuffer++ = *ptr_message++;
		i++;
	}
	while (i < (10)){
		*ptr_sendBuffer++ = '&';
		i++;
	}
	//TODO : Ajout des caractères vides pour remplir
	*ptr_sendBuffer++ = 'U';
	*ptr_sendBuffer++ = 'H';
	i = 0;
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
		//Mettre le message à envoyer dans le buffer message, qui n'accepte que 10 char max.
		message[0] = 'E';
		message[1] = 'A';
		SPIlength = 2; //Spécifiez la longueur du message
		Codage(SPIlength,ptr_sendBuffer,ptr_message);
		/*
		
		if (recieve_flag) {
			recieve_flag = 0;
			if (recieveBuffer[1] == 'B' && recieveBuffer[2] == 'R'){
				while (j != lMessage){
					messageBuffer[j] = recieveBuffer[j+3];
					j++;
					}						
				if (messageBuffer[0] == 'E' && messageBuffer[1] == 'A'){
					LED = 1;
					}
				}
		}
		
		*/
		
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
	if (SPIcounter > 13){
		SPIcounter = 0;
	}
	else {
		Transfert(sendBuffer[SPIcounter]);
		SPIcounter++;
	}
	
	/*
	//Attente de 2 SCK, pour laisse le temps au Slave d'envoyer son message en retour
	
	*ptr_recieveBuffer++ = SPI0DAT;
	mCounter++;
	if (*ptr_recieveBuffer == 'H' && *ptr_recieveBuffer == 'U'){
		lMessage = mCounter-4;
		mCounter = 0;
		recieve_flag = 1;
	}
	if (i == 10){
		i = 0;
	}
	
	
	*/
}
