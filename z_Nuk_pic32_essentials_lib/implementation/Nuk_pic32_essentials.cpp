// ****************************************************************************
// File:  Nuk_pic_essentials.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la llibreria Nuk_pic_essentials

// ----------------------------------------------------------------------------
using namespace std;


// ----------------------------------------------------------------------------
#include "Nuk_pic32_essentials.h"




// ----------------------------------------------------------------------------
void
nuk_pic_essentials(void) {
	/*
	FUNCTION:
		Init Nuk_pic_essentials
		Enable multivector interruptions
		Idle mode for sleeping

	PARAMETERS:
		void

	RETURN:
		void
	*/

	static bool done = false;

	// Only once
	if( !done ) {
		done = true;

		// Dissable interrupts
		asm("di");

		// Enable  multivector interrupts
		INTCONSET = 0x1000;

		WDTCONSET = 0x8000;

		// Unlock protected write registers
		SYSKEY = 0x0;
		SYSKEY = 0xAA996655;
		SYSKEY = 0x556699AA;

		// Select idle mode for sleep
		OSCCONCLR = 0x10;

		// ** TO DO ** (or not)
		// RTCC Value registers can be written to by the user
		// Time 00:00:00
		// Date Saturday 2000-01-01
		// RTCC On bit
		// RTCCONSET = 0x00000008;
		// RTCTIME   = 0x00000000;
		// RTCDATE   = 0x00010106;
		// RTCCONSET = 0x00008000;

		// Lock protected write registers
		SYSKEY = 0x0;

		// Enable interrupts
		asm("ei");
		}

	return;
	}


