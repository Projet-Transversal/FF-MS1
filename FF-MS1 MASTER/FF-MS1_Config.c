/*******************************************************************************
; 	FILE NAME  	: FF-MS_Config.c
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Configurations GLOBALES pour le 8051F020
;
; 	REVISION 1.0
;   Ce fichier contient les codes de configuration globale du 8051F020
;     - Configuration de l'horloge système SYSCLK
;     - Configuration des broches du 80851F020
;     - Configuration Reset et watchdog
*/
//******************************************************************************

#include "C8051F020.h"
#include "c8051F020_SFR16.h"

sbit LED = P1^6;

// Peripheral specific initialization functions,
// Called from the Init_Device() function

//-----------------------------------------------------------------------------
// Dévalidation du watchdog
//-----------------------------------------------------------------------------
void Reset_Sources_Init()
{
	 WDTCN = 0xDE;
	 WDTCN = 0XAD;
// Début Insertion Code configuration Reset  **********************************
	
// Fin Insertion Code configuration Reset et **********************************
}

//-----------------------------------------------------------------------------
// Configuration des Ports d'entrée-sorties
//-----------------------------------------------------------------------------

void Port_IO_Init()
{
    // P0.0  -  SCK, Push-Pull, Digital
    // P0.1  -  MISO, Open-Drain, Digital
    // P0.2  -  MOSI, Push-Pull, Digital
    // P0.3  -  NSS,  Open-Drain, Digital, Unused
    // P0.4  -  Unassigned,  Open-Drain, Digital
    // P0.5  -  Unassigned,  Open-Drain, Digital
    // P0.6  -  Unassigned,  Open-Drain, Digital
    // P0.7  -  SLAVE_NSS,  Push-Pull, Digital

    // P1.0  -  Unassigned,  Open-Drain, Digital
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Unassigned,  Open-Drain, Digital
    // P1.3  -  Unassigned,  Open-Drain, Digital
    // P1.4  -  Unassigned,  Open-Drain, Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  LED       ,  Open-Drain, Digital
    // P1.7  -  Unassigned,  Open-Drain, Digital

    // P2.0  -  Unassigned,  Open-Drain, Digital
    // P2.1  -  Unassigned,  Open-Drain, Digital
    // P2.2  -  Unassigned,  Open-Drain, Digital
    // P2.3  -  Unassigned,  Open-Drain, Digital
    // P2.4  -  Unassigned,  Open-Drain, Digital
    // P2.5  -  Unassigned,  Open-Drain, Digital
    // P2.6  -  Unassigned,  Open-Drain, Digital
    // P2.7  -  Unassigned,  Open-Drain, Digital

    // P3.0  -  Unassigned,  Open-Drain, Digital
    // P3.1  -  Unassigned,  Open-Drain, Digital
    // P3.2  -  Unassigned,   Push-Pull, Digital
    // P3.3  -  Unassigned,  Open-Drain, Digital
    // P3.4  -  Unassigned,  Open-Drain, Digital
    // P3.5  -  Unassigned,  Open-Drain, Digital
    // P3.6  -  Unassigned,  Open-Drain, Digital Input INT6
    // P3.7  -  Unassigned,  Open-Drain, Digital Input INT7
		
		// P4.0 to P7.7   Unassigned,  Open-Drain, Digital
		
// Début Insertion Code configuration Crossbar et GPIO ************************

		P0MDOUT   |= 0x3D; // P0.0,P0.2,P0.3,P0.4,P0.5 en Push-Pull P0.1 en Open Drain
		P0 = 0x02; // P0.1 en mode entrée : MISO
		P3 |= 0x80; // P3.7 en mode entrée : Bouton
    XBR0      = 0x02; //Activation du SPI0
    XBR2      = 0x40; //Activation du crossbar
		
     
// Fin Insertion Code configuration Crossbar et GPIO **************************

}

//-----------------------------------------------------------------------------
// Config Interruptions SPI0
//-----------------------------------------------------------------------------
void Config_SPI0()
{
	SPIEN = 1;
	MSTEN = 1;
	EIE1 |= 0x01;
	SPI0CKR = 0x30;
}

//-----------------------------------------------------------------------------
// Config Timer 3 : Générateur de fréquence
//-----------------------------------------------------------------------------
void Config_Timer3(void){
	
	 EIE2 |= 0x01; //Timer 3 interrupt enabled
	 TMR3RL = 0xEDFF;
	 TMR3CN = 0x04; //Timer 3 est enabled
}

//-----------------------------------------------------------------------------
// Config oscillateur - SYSCLK = 22,1184MHz - Oscillateur externe à quartz 
//-----------------------------------------------------------------------------

void Oscillator_Init_Osc_Quartz()
{

	  int i = 0;
    OSCXCN    = 0x67;  // Config de l'horloge externe - Quartz > 6,7 MHz
    for (i = 0; i < 3000; i++);  // attente stabilisation Fosc quartz
    while ((OSCXCN & 0x80) == 0); // validation stabilité du quartz
    OSCICN    = 0x0C;  // Commutation sur oscillateur externe 
	                     // L'oscillateur n'est pas stopp
}

//-----------------------------------------------------------------------------
// Initialisation globale du Microcontrôleur - 
//-----------------------------------------------------------------------------
void Init_Device(void)
{
    Reset_Sources_Init();
    Port_IO_Init();
    Oscillator_Init_Osc_Quartz();
		Config_Timer3();
		Config_SPI0();
}



