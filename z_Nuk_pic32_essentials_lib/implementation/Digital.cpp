// ****************************************************************************
// File:  Ports_Digital.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase Ports_Digital
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Digital.h"




// ****************************************************************************
// Implementacio de la clase Digital
//

// ----------------------------------------------------------------------------
Digital::~Digital() {
	/*
	DESTRUCTOR
        Destructor
	*/

	// Deshabilitem interrupcio
	irq_disable();
	}


// ----------------------------------------------------------------------------
Digital::Digital(
	volatile unsigned int& p_port,
	volatile unsigned int& p_ansel,
	volatile unsigned int& p_tris,

	unsigned int p_num_bit,

	volatile unsigned int& p_odc,
	volatile unsigned int& p_cnpu,
	volatile unsigned int& p_cnpd,
	volatile unsigned int& p_cncon,	
	volatile unsigned int& p_cnen,
	volatile unsigned int& p_cnstat,

	unsigned int p_bit_cn_on,

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
	Configura el pin del port especificat com a digital

	PARAMETRES:
		Paxx
			Port del pin que volem que sigui digital
			a = A,B,....
			xx = nombre del bit

	RETORN:
		void
	 
	NOTA:
		Els pins es configuren inicialment com a inputs
	*/
 
	// Regitres del port
	port     = &p_port;
	ansel    = &p_ansel;
	tris     = &p_tris;
	odc      = &p_odc;
	cnpu     = &p_cnpu;
	cnpd     = &p_cnpd;
	cncon    = &p_cncon;
	cnen     = &p_cnen;
	cnstat   = &p_cnstat;

	// Memoriritzem el bit del port
	// Change Notice (CN) Control ON bit
	port_bit = ((unsigned int)(0b1)<<p_num_bit);
	bit_cn_on = p_bit_cn_on;

	// Estat inicial
	// Digital
	// Input
	*ansel &= ~port_bit;
	*tris  |=  port_bit;

	return;
	}


// ----------------------------------------------------------------------------
void
Digital::input(void) {
	/*
	FUNCIO:
		Converteix el pin en input. Si ja ho es, no fa res.

	PARAMETRES:
		void

	RETORN:
		void
	*/
	
	// Digital
	// Input
	*ansel &= ~port_bit;
	*tris  |=  port_bit;
	*port;

	return;
	}


// ----------------------------------------------------------------------------
void
Digital::on(void) {
	/*
	FUNCIO:
		Posa a 1 el pin del port en mode pull up

	PARAMETRES:
		void

	RETORN:
		void
	*/
	
	// Digital
	// Out
	// Pull up
	// Pin on
	*ansel &= ~port_bit;
	*tris  &= ~port_bit;
	*odc   &= ~port_bit;
	*port  |=  port_bit;

	return;
	}


// ----------------------------------------------------------------------------
void
Digital::open(void) {
	/*
	FUNCIO:
		Posa a 1 el pin del port en mode open drain
		Es a dir, desconecta de masa el pin del port

	PARAMETRES:
		void

	RETORN:
		void
	*/
	
	// Digital
	// Out
	// Open drain
	// Pin on
	*ansel &= ~port_bit;
	*tris  &= ~port_bit;
	*odc   |=  port_bit;
	*port  |=  port_bit;

	return;
	}


// ----------------------------------------------------------------------------
void
Digital::off(void) {
	/*
	FUNCIO:
	Posa a 0 el pin del port en mode pull up

	PARAMETRES:
		void

	RETORN:
		void
	*/

	// Digital
	// Out
	// Pull up
	// Pin off	
	*ansel &= ~port_bit;
	*tris  &= ~port_bit;
	*odc   &= ~port_bit;
	*port  &= ~port_bit;

	return;
	}


// ----------------------------------------------------------------------------
void
Digital::close(void) {
	/*
	FUNCIO:
		Posa a 0 el pin del port en mode open drain
		Es a dir, conecta a masa el pin del port

	PARAMETRES:
		void

	RETORN:
		void
	*/

	// Digital
	// Out
	// Open drain
	// Pin off	
	*ansel &= ~port_bit;
	*tris  &= ~port_bit;
	*odc   |=  port_bit;
	*port  &= ~port_bit;

	return;
	}


// ----------------------------------------------------------------------------
void
Digital::inv(void) {
	/*
	FUNCIO:
		Canvia de polaritat el pin del port
		Si es un input, el converteix en output i el posa a on

	PARAMETRES:
		void

	RETORN:
		void
	*/
	
	*ansel &= ~port_bit;
	
	// Si el port es un input, el convertim en output i el posem a on
	if( *tris&port_bit ) {
		*tris &= ~port_bit;
		*port  |=  port_bit;
		}
	
	// Si no es un input, canviem la polaritat
	else {
		if( *port&port_bit ) *port &= ~port_bit;
		else *port |= port_bit;
		}
	
	return;
	}


// ----------------------------------------------------------------------------
bool
Digital::ison(void) {
	/*
	FUNCIO:
		Retorna 'true' si el pin esta en on

	PARAMETRES:
		void

	RETORN:
		bool
			'true' si el pin esta en on
			'false' sin e pin esta en off
	*/
	
	return( (*port&port_bit)!=0 );
	}


// ----------------------------------------------------------------------------
bool
Digital::ispullup(void) {
	/*
	FUNCIO:
		Retorna true si el pin esta configurat com a pull_up

	PARAMETRES:
		void

	RETORN:
		void
	*/

	return( (*odc&port_bit)==0 );
	}

// ----------------------------------------------------------------------------
void
Digital::onchange(void (*call)(Digital*)) {
	/*
	FUNCIO:
		Estableix/Deshabilita la funcio de callback per interrupcio
		Per canvi de valor pin.

	PARAMETRES:
		void (*call)(Digital*)
			Funcio de callback
			Si ==NULL desabilita la interrupcio per canvi de pin

	RETORN:
		void
	*/

	// Memoritzem funcio de callback
	o_callback = NULL;
	f_callback = call;

	// Si hi ha funcio de callback
	if( f_callback!=NULL ) {

		// Fem que el port sigui input
		*ansel &= ~port_bit;
		*tris |= port_bit;

		// Habilitem la interrupcio
		*port;
		*cncon |= bit_cn_on;
		*cnen |= port_bit;
		irq_enable();
		}

	// Si no hi ha funcio de callback
	else {
		*port;
		*cnen &= ~port_bit;
		*cncon &= ~bit_cn_on;
		irq_disable();
		}

	return;
	}


// ----------------------------------------------------------------------------
void
Digital::onchange(Callable* ocall,int hcall) {
	/*
	FUNCIO:
		Estableix/Deshabilita l'objecte  de callback per interrupcio
		Per canvi de pin.

	PARAMETRES:
		Callable* ocall
			Objecte que te funcio de callback

		int hcall
			Hadle del objecte 'ocall'. Valor del parametre amb el que
			sera cridada la funcio de callback del objecte.

	RETORN:
		void
	*/

	// Memoritzem funcio de callback
	f_callback = NULL;
	o_callback = ocall;
	h_callback = hcall;

	// Si hi ha objecte Callable
	if( o_callback!=NULL ) {

		// Fem que el port sigui input
		*ansel &= ~port_bit;
		*tris |= port_bit;

		// Habilitem la interrupcio
		*port;
		*cncon |= bit_cn_on;
		*cnen |= port_bit;
		irq_enable();
		}

	// Si no hi ha funcio de callback
	else {
		*port;
		*cnen &= ~port_bit;
		*cncon &= ~bit_cn_on;
		irq_disable();
		}

	return;
	}


// ----------------------------------------------------------------------------
void
Digital::Irq(void) {
	/*
	FUNCIO INTERNA:
		La cridada interrupcio
		Canvi d'estat del pin
	*/

	// Cridem a la funcio d'usuari
	if( *cnen&port_bit ) {
		if( f_callback!=NULL ) f_callback(this);
		if( o_callback!=NULL ) o_callback->callback(h_callback);
		}
		
	return;
	}





