// ****************************************************************************
// File:  Config_40.h
// Autor: Lluis
// Descripcio
// 	Pragmas 40 Mhz
//




// ****************************************************************************
// Pragmas
//

// Debug i reconfiguracio
#pragma config DEBUG    = OFF // Debug off
#pragma config IOL1WAY  = OFF // Peripheral Pin Select Configuration bit off
#pragma config PMDL1WAY = OFF // Peripheral Module Disable Configuration bit off

// SYSCLK = 40Mhz
#pragma config FNOSC    = FRCPLL    // Fast RC Osc with PLL
#pragma config FPLLIDIV = DIV_2     // 8Mhz / 2   =   4Mhz
#pragma config FPLLMUL  = MUL_20    // 4Mhz * 20  =  80Mhz
#pragma config FPLLODIV = DIV_2     // 80Mhz / 2  =  40Mhz
#pragma config FPBDIV   = DIV_1     // 40Mhz / 1  =  40Mhz
#pragma config USERID   = 40        // Frequencia en DEVCFG3<15:0>


