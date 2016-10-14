// ****************************************************************************
// File:  Ports_Ei.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase Ei (External interrupt)
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Ei.h"

Ei::~Ei() {
	/*
	DESTRUCTOR
		Destructor
	*/

	// Deshabilitem interrupcio
	irq_disable();

	}




// ****************************************************************************
// Implementacio de la clase Ei
//

// ----------------------------------------------------------------------------
Ei::Ei(
	volatile unsigned int& p_port,
	volatile unsigned int& p_ansel,
	volatile unsigned int& p_tris,
	unsigned int p_num_bit,

	volatile unsigned int& p_intcon,
	volatile unsigned int& p_intxr,
	unsigned int p_bit_intxr,
	unsigned int p_bit_intnep,

	volatile unsigned int& p_iecx,
	volatile unsigned int& p_ifsx,
	volatile unsigned int& p_ipcx,
	unsigned int p_bit_iecx,
	unsigned int p_bit_ifsx,
	unsigned int p_bit_ipcx,
	unsigned int interrupt ) :

IrqObject(
	p_iecx,
	p_ifsx,
	p_ipcx,

	p_bit_iecx,
	p_bit_ifsx,
	p_bit_ipcx,
	interrupt) {
	/*
	CONSTRUCTOR:
		Configura el pin del port especificat en com a Ei

	PARAMETRES:
	Paxx
		Port del pin que volem que sigui Ei
			a = A,B,....
			xx = nombre del bit

	RETORN:
		void
	 
	NOTA:
		Els pins es coiguren inicialment com a inputs
	*/
 
	// Regitres del port
	port     = &p_port;
	ansel    = &p_ansel;
	tris     = &p_tris;
	intxr    = &p_intxr;
	intcon   = &p_intcon;

	// Memoriritzem el bit del port
	port_bit = ((unsigned int)(0b1)<<p_num_bit);
	bit_intnep = p_bit_intnep;

	// Desbloquegem escritura dels registres PPS
	SYSKEY = 0x00;
	SYSKEY = 0xAA996655;
	SYSKEY = 0x556699AA;

	// Permitim el canvi de PPS
	CFGCON = 0x00;

	// Fem que el port sigui 'Ei'
	*intxr = p_bit_intxr;

	// Bloquejem el canvi PPS
	SYSKEY = 0x00;

	// Estat inicial
	// Digital
	// Input,
	*ansel &= ~port_bit;
	*tris  |=  port_bit;

	return;
	}


// ----------------------------------------------------------------------------
bool
Ei::ison(void) {
	/*
	FUNCIO:
		Retorna 'true' si el pin esta en on

	PARMETRES:
		void

	RETORN:
	'true' si el pin esta en on
	'false' sin e pin esta en off
	*/
	
	return ( (*port&port_bit)!=0 );
	}


// ----------------------------------------------------------------------------
void
Ei::onchange(bool edge,void (*call)(Ei*)) {
	/*
	FUNCIO:
		Estableix/Deshabilita la funcio de callback per interrupcio
		Per canvi de pin.

	PARMETRES:
		int edge
			==true Interrupcio per rising
			==false Iterrupcio per falling

		void (*call)(Ei*)
			Funcio de callback
			Si ==NULL desabilita la interrupcio per canvi de pin

	RETORN:
		void
	*/

	f_callback = call;

	// Si hi ha funcio de callback
	if( f_callback!=NULL ) {

		// Fem que el port sigui input
		*ansel &= ~port_bit;
		*tris |= port_bit;

		// Establim falling/rising
		if( edge ) *intcon |= bit_intnep;
		else *intcon &= ~bit_intnep;

		// Habilitem la interrupcio
		irq_enable();
		}

	// Si no hi ha funcio de callback
	else {

		// Deshabilitem l'interrupcio si es que tampoc hi metode de callback
		if( o_callback==NULL ) irq_disable();
		}

	return;
	}


// ----------------------------------------------------------------------------
void
Ei::onchange(bool edge, Callable* ocall,int hcall) {
	/*
	FUNCIO:
		Estableix/Deshabilita l'objecte  de callback per interrupcio
		Per canvi de pin.

	PARMETRES:
		Callable* call
			Objecte que te funcio de callback

	RETORN:
		void
	*/

	o_callback = ocall;
	h_callback = hcall;

	// Si hi ha objecte Callable
	if( o_callback!=NULL ) {

		// Fem que el port sigui input
		*ansel &= ~port_bit;
		*tris |= port_bit;

		// Establim falling/rising
		if( edge ) *intcon |= bit_intnep;
		else *intcon &= ~bit_intnep;

		// Habilitem la interrupcio
		irq_enable();
		}

	// Si no hi ha funcio de callback
	else {

		// Deshabilitem l'interrupcio si es que tampoc hi metode de callback
		if( f_callback== NULL ) irq_disable();
		}

	return;
	}


// ----------------------------------------------------------------------------
void
Ei::Irq(void) {
	/*
	FUNCIO INTERNA:
		La crida el vector d'interrupcio
	*/

	// Cridem a la funcio d'usuari
	if( f_callback!=NULL ) f_callback(this);
	if( o_callback!=NULL ) o_callback->callback(h_callback);

	return;
	}



