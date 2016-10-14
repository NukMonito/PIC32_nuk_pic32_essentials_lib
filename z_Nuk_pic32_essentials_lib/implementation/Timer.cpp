// ****************************************************************************
// File:  Timer.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase Timer
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Timer.h"




// ****************************************************************************
// Implementacio de la clase Timer_class
//

// ----------------------------------------------------------------------------
Timer::~Timer() {
	/*
	DESTRUCTOR
        Destructor del IrqObject.
	*/

	// Deshabilitem timer
	// Deshabilitem interrupcio
	*txcon &= ~bit_txcon;
	irq_disable();

	}

// ----------------------------------------------------------------------------
Timer::Timer(
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

TimerObject(p_txcon,
	p_tmrx,
	p_prx,
	p_bit_txcon,
	p_bit_bits,
	p_div0,p_div1,p_div2,p_div3,
	p_div4,p_div5,p_div6,p_div7,

	p_iecx,
	p_ifsx,
	p_ipcx,
	p_bit_iecx,
	p_bit_ifsx,
	p_bit_ipcx,
	p_interrupt ) {

	/*
	CONSTRUCTOR:
		Configura timer

	PARMETRES:
		TIMERx
			Timer x

	RETORN:
		void
	*/

	}


// ----------------------------------------------------------------------------
void
Timer::delay(unsigned int t) {
	/*
	FUNCIO
		Retarda la ejecucio 't' microsegons

	NOTA:
		Tots els objectes que emprin el mateix timer quedaran
		parats; encara que mantenen la seva funcio de callback.
		Es pot reestablir el seu funcionament fent on().
	*/

	// Deshabilitem la interrupcio del timer
	// Calcuem i configurem PRx
	// Habilitem conta de timer
	// Esperem flag
	// Fem clear del flag
	// Deshabilitem timer
	irq_disable();
	configure(t);
	*txcon |= bit_txcon;
	while( !(*ifsx&bit_ifsx) );
	*ifsx &= ~bit_ifsx;
	*txcon = 0x00;

	return;
	}


// ----------------------------------------------------------------------------
bool
Timer::every(unsigned int p,void (*call)(Timer*)) {
	/*
	FUNCIO:
		Crida la funcio de 'f_callbak' cada 'p' microsegons
		Si el timer ja estava en on, fa un reset del contator
		Si 'p' es zero, el timer queda aturat

	PARAMETRES:
		unsigned int p
			Periode en microsegons. Si es zero, el timer queda aturat

		void (*call)(Timer*)
			Funcio de callback

	RETORN
		True	El timer s'ha configurat adequadament
		False	El timer no s'ha pogut configurar i/o ha quedat aturat

	NOTA 1:
		Els objectes que emprin el mateix timer es veuran
		afectas per aquesta accio; pero mantenen la seva funcio
		de callback

	NOTA 2:
		La rao de que el timer no es pugui configurar es que el
		valor de 'p' es zero o molt gros per que pugui ferse
		caber en un periode amb el maxim divisor posible
	*/

	// Preparem el retorn
	bool r = false;

	// Memoritzem funcio de callback
	o_callback = NULL;
	f_callback = call;

	// Configurem i activem Timer
	if( (r = configure(p)) ) {
		// Si hi ha funcio de callback, habilitem interrupcio
		// Activem el timer
		if( f_callback!=NULL ) irq_enable();
		else irq_disable();
		*txcon  |= bit_txcon;
		}
	else irq_disable();

	return r;
	}

// ----------------------------------------------------------------------------
bool
Timer::every(unsigned int p,Callable* ocall,int hcall) {
	/*
	FUNCIO:
		Crida la funcio de 'o_callbak' cada 't' microsegons
		Si el timer ja estava en on, fa un reset del contator
		Si 'p' es zero, el timer queda aturat

	PARAMETRES:
		unsigned int p
			Periode en microsegons. Si es zero, el timer queda aturat

		Callable* call
			Objecte de callback al termini de cada periode

		int hcall

	RETORN
		True	El timer s'ha configurat adequadament
		False	El timer no s'ha pogut configurar i/o ha quedat aturat

	NOTA 1:
		Els objectes que emprin el mateix timer es veuran
		afectas per aquesta accio; pero mantenen la seva funcio
		de callback

	NOTA 2:
		La rao de que el timer no es pugui configurar es que el
		valor de 'p' es zero o molt gros per que pugui ferse
		caber en un periode amb el maxim divisor posible
	*/

	// Preparem el retorn
	bool r = false;

	// Memoritzem funcio de callback
	f_callback = NULL;
	o_callback = ocall;
	h_callback = hcall;

	// Configurem i activem Timer i Pwm (output compare)
	if( (r = configure(p)) ) {
		// Si hi ha funcio de callback, habilitem interrupcio
		// Activem el timer
		if( o_callback!=NULL ) irq_enable();
		else irq_disable();
		*txcon  |= bit_txcon;
		}
	else irq_disable();

	return r;
	}


// ----------------------------------------------------------------------------
void
Timer::on(void) {
	/*
	FUNCIO:
		Habilita la cridada de la funcio de callback configurada
		per la funcio 'every()'

	*/

	// Habilitem timer
	// Reestablim funcio de callback
	*txcon |= bit_txcon;
	irq_enable();

	return;
	}


// ----------------------------------------------------------------------------
void
Timer::off(void) {
	/*
	FUNCIO:
		Deshabilita la cridada de la funcio de callback configurada
		per la funcio 'every()'
	*/

	// Deshabilitem interrupcio del ojecte
	irq_disable();

	return;
	}


// ----------------------------------------------------------------------------
void
Timer::Irq(void) {
	/*
	FUNCIO INTERNA:
		El periode a expirat
		Cridem a la funcio del IrqObject que la ha demanada per
		que canvii, si cal, els valor del periode entre altres
		coses d'interes per el usuari
	*/
	
	// Cridem a la funcio d'usuari
	if( f_callback!=NULL ) f_callback(this);
	if( o_callback!=NULL ) o_callback->callback(h_callback);

	return;
	}


