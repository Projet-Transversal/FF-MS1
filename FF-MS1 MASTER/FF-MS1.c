//-----------------------------------------------------------------------------
// TP5.c
//-----------------------------------------------------------------------------
// AUTH: Mehdi Slama & Julien Pinard
// DATE: Le début des temps
//
// Target: C8051F02x
// Tool chain: KEIL Microvision 4
//
//-----------------------------------------------------------------------------
#include <C8051F020.h>
#include "c8051F020_SFR16.h"
#include "FF-MS1_Config.h"
#include <stdlib.h>
#include <string.h>

#define Reset_Timer3Overflow TMR3CN &= 0x04
#define Disable_Timer3 TMR3CN = 0x00

sbit LED = P1^6;
sbit SLAVE_NSS = P0^7;
char i = 0;
char SPIlength = 0;
char SPIcounter = 0;
char xdata message[15];
char* ptr_message = &message;
char* ogptr_message = &message;
char xdata sendBuffer[19];
char* ptr_sendBuffer = &sendBuffer;
char* ogptr_sendBuffer = &sendBuffer;
char envoi[10];
char* ogptr_envoi = &envoi;
char* ptr_envoi = &envoi;
// Prototypes de Fonctions

void Codage (char SPIlength, char* ptr_sendBuffer, char* ptr_message){
	*ptr_sendBuffer++ = 'B';
	*ptr_sendBuffer++ = 'R';
	while (i < SPIlength){
		*ptr_sendBuffer++ = *ptr_message++;
		i++;
	}
	while (i < (15)){
		*ptr_sendBuffer++ = '~';
		i++;
	}
	*ptr_sendBuffer++ = 'U';
	*ptr_sendBuffer++ = 'H';
	i = 0;
}

void send_SPI(char* ptr_message,char* ptr_envoi,char* ptr_sendBuffer){
	while(*ptr_envoi != '\0'){
		*ptr_message++ = *ptr_envoi++;
		SPIlength++;
	}
	ptr_envoi = ogptr_envoi;
	ptr_message = ogptr_message;
	Codage(SPIlength,ptr_sendBuffer,ptr_message);
	SPIlength=0;
}
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

// Début Code Inistalisations *************************************************

	  Init_Device();  // Appel des configurations globales
	  
		EA = 1;
		LED = 0;
		SLAVE_NSS = 1;
	
// Fin Code Initialisations ***************************************************
	
	//Main loop
	while(1)
	{
		//Mettre le message à envoyer dans un string, qui n'accepte que 15 char max.
		strcpy(envoi,"ABC");
		send_SPI(ptr_message,envoi,ptr_sendBuffer);
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


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
	if (SPIcounter > 18){
		SPIcounter = 0;
		ptr_sendBuffer = ogptr_sendBuffer;
		ptr_message = ogptr_message;
		
	}
	else {
		Transfert(sendBuffer[SPIcounter]);
		SPIcounter++;
	}
}
