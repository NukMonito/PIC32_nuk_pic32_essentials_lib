// ****************************************************************************
// File:  Config_20.h
// Autor: Lluis
// Descripcio
// 	Pragmas 20 Mhz
//




// ****************************************************************************
// Pragmas
//

// Debug i reconfiguracio
#pragma config DEBUG    = OFF // Debug off
#pragma config IOL1WAY  = OFF // Peripheral Pin Select Configuration bit off
#pragma config PMDL1WAY = OFF // Peripheral Module Disable Configuration bit off

// SYSCLK = 20Mhz
#pragma config FNOSC    = FRCPLL    // Fast RC Osc with PLL
#pragma config FPLLIDIV = DIV_2     // 8Mhz / 2   =   4Mhz
#pragma config FPLLMUL  = MUL_20    // 4Mhz * 20  =  80Mhz
#pragma config FPLLODIV = DIV_4     // 80Mhz / 4  =  20Mhz
#pragma config FPBDIV   = DIV_1     // 20Mhz / 1  =  20Mhz
#pragma config USERID   = 20        // Frequencia en DEVCFG3<15:0>


