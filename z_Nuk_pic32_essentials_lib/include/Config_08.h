// ****************************************************************************
// File:  Config_08.h
// Autor: Lluis
// Descripcio
// 	Pragmas 8 Mhz
//




// ****************************************************************************
// Pragmas
//

// Debug i reconfiguracio
#pragma config DEBUG    = OFF // Debug off
#pragma config IOL1WAY  = OFF // Peripheral Pin Select Configuration bit off
#pragma config PMDL1WAY = OFF // Peripheral Module Disable Configuration bit off

// SYSCLK = 8Mhz
#pragma config FNOSC    = FRC       // Fast RC Osc
#pragma config FPBDIV   = DIV_1     // 8Mhz / 1 =  8Mhz
#pragma config USERID   = 8         // Frequencia en DEVCFG3<15:0>


