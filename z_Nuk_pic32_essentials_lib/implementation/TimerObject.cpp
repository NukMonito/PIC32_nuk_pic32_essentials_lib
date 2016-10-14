// ****************************************************************************
// File:  TimerObject.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase TimerObject
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"




// ****************************************************************************
// Implementacio de la clase TimerObject_class
//

// ----------------------------------------------------------------------------
TimerObject::TimerObject(
	volatile unsigned int& p_txcon,
	volatile unsigned int& p_tmrx,
	volatile unsigned int& p_prx,
	unsigned int p_bit_txcon,
	unsigned int p_bit_bits,
	unsigned int p_div0,unsigned int p_div1,
	unsigned int p_div2,unsigned int p_div3,
	unsigned int p_div4,unsigned int p_div5,
	unsigned int p_div6,unsigned int p_div7,

	volatile unsigned int& p_iecx,
	volatile unsigned int& p_ifsx,
	volatile unsigned int& p_ipcx,
	unsigned int p_bit_iecx,
	unsigned int p_bit_ifsx,
	unsigned int p_bit_ipcx,
	unsigned int p_interrupt ) :

IrqObject(
	p_iecx,
	p_ifsx,
	p_ipcx,
	p_bit_iecx,
	p_bit_ifsx,
	p_bit_ipcx,
	p_interrupt) {

	/*
	CONSTRUCTOR:
		Configura TimerObject

	PARMETRES:
		TimerObjectx
			TimerObject x

		int p
			Periode del TimerObject en milisegons

	RETORN:
		void
	*/

	// Registres del Timer
	txcon = &p_txcon;
	tmrx  = &p_tmrx;
	prx   = &p_prx;

	// Variables
	bit_txcon = p_bit_txcon;
	bit_bits  = p_bit_bits;
	div[0] = p_div0;
	div[1] = p_div1;
	div[2] = p_div2;
	div[3] = p_div3;
	div[4] = p_div4;
	div[5] = p_div5;
	div[6] = p_div6;
	div[7] = p_div7;

	// Deshabilitem Timer
	*txcon  = 0x00;
	*prx    = 0x00;
	*tmrx   = 0;

	}


// ----------------------------------------------------------------------------
bool
TimerObject::configure(unsigned long p) {
	/*
	FUNCIO:
		Calcula els tics i un dividor apropiat de timer per a que tingui un
		periode de 't' microsegons. Deixa la configuracio a las variables 
		del objecte 'periode' i 'divisor', i configura els registres del
		timer 'prx' i txcon'

	PARAMETRES:
	int t
		Periode en microsegons

	RETORN:
		bool
			True == El canvi ha prosperat
			False == El canvi ha fallat

		Modifica els atributs 'periode' i 'divisor'
		Modifica els registres del timer 'txcon' i 'prx'
	*/

	// Preparem el retorn
	bool r = false;

	// Aturem el timer
	*txcon = 0x00;

	// Memoritzem el periode
	pmicros = p;

	// Si el periode no es zero, configurem
	if( pmicros ) {

		// 'tc' Cicles de procesador en 't' microsegons
		// Recordem que afrequency() tenim la frequencia del microcontrolador
		// en MHz, per tant ...
		double tc = pmicros*frequency();

		// Triem un divisor dels disponibles
		// 'ideal' Valor del divisor ideal.
		//     'tc'/(2¹16) per timer de 16 bits
		//     'tc'/(2^32) per timer de 32 bits
		// 'divisor' Divisor
		// 'div' Tabla dels valors dels divisors disponibles
		// Si hem trobat un divisor 'r' sera ==true
		unsigned int ideal;
		divisor = 0;
		if( bit_bits!=0 ) ideal = (tc/(0x100000000))+1;
		else ideal = (tc/(0x10000))+1;
		while( (ideal>div[divisor]) && divisor<8 ) divisor++;
		if( divisor<8 ) r = true;

		// Si hem trobat un divisor
		if( r ) {

			// Calculem el periode
			periode = tc/div[divisor];

			// Configurem el timer (queda aturat)
			*txcon |= bit_bits;
			*txcon |= (divisor<<4);
			*prx = periode;
			*tmrx = 0x00;
			}
		}

	return r;
	}


// ----------------------------------------------------------------------------
void
TimerObject::configure(unsigned long p, int d) {
	/*
	FUNCIO:
		Estableix el periode i el divisor del timer

	PARAMETRES:
		unsigend int p
			Periode del timer en tics
		int d
			Divisor del timer

	RETORN:
		void
	*/

	// Parem el timer
	*txcon = 0x00;

	// Memoritzem el periode i el divisor
	periode = p;
	divisor = d;

	// Calculem el periode en microsegons
	double tc = periode*div[divisor];
	pmicros = tc/frequency();

	// Configurem el timer
	*txcon |= *txcon |= bit_bits;
	*txcon |= (d<<4);
	*prx = p;

	return;
	}


