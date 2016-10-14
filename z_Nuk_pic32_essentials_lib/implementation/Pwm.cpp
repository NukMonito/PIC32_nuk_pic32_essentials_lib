// ****************************************************************************
// File:  Ports_Pwm.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase Pwm (Outut compare)
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Pwm.h"




// ****************************************************************************
// Implementacio de la clase Pwm (Output compare)
//


Pwm::~Pwm() {
	/*
	DESTRUCTOR
        Destructor
	*/

	// Deshabilitem timer
	// Deshabilitem interrupcio
	*txcon &= ~bit_txcon;
	irq_disable();
	
	}


// ----------------------------------------------------------------------------
Pwm::Pwm(
	volatile unsigned int& p_port,
	volatile unsigned int& p_ansel,
	volatile unsigned int& p_tris,
	unsigned int p_num_bit,

	volatile unsigned int& p_rpaxr,
	volatile unsigned int& p_ocxcon,
	volatile unsigned int& p_ocxr,
	volatile unsigned int& p_ocxrs,

	unsigned int p_bit_rpaxr,
	unsigned int p_bit_ocxcon_on,
	unsigned int p_bit_ocxcon_ocm,

	volatile unsigned int& p_txcon,
	volatile unsigned int& p_tmrx,
	volatile unsigned int& p_prx,
	unsigned int p_bit_txcon,
	unsigned int p_bits,
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
	unsigned int p_interrupt,

	unsigned int p_bit_ocxcon_octsel,
	unsigned int p_bit_ocxcon_oc32 ) :

TimerObject(
	p_txcon,
	p_tmrx,
	p_prx,
	p_bit_txcon,
	p_bits,
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
		Configura el pin del port especificat com a PWM

	PARAMETRES:
		PWMx
			Port PWM

	RETORN:
		void
	*/

	// Registres del port
	port = &p_port;
	ansel = &p_ansel;
	tris = &p_tris;

	// Variables de configuracio del port
	bit_port = ((unsigned int)0x1)<<p_num_bit;

	// Port digital, out, off
	*ansel &= ~bit_port;
	*tris  &= ~bit_port;
	*port  &= ~bit_port;
 
	// Registres del Pwm
	rpaxr  = &p_rpaxr;
	ocxcon = &p_ocxcon;
	ocxr   = &p_ocxr;
	ocxrs  = &p_ocxrs;

	// Variables de configuracio Pwm
	bit_rpaxr = p_bit_rpaxr;
	bit_ocxcon =
		p_bit_ocxcon_on|p_bit_ocxcon_ocm|p_bit_ocxcon_octsel|p_bit_ocxcon_oc32;

	// Desbloquegem escritura dels registres PPS
	SYSKEY = 0x00;
	SYSKEY = 0xAA996655;
	SYSKEY = 0x556699AA;

	// Permitim el canvi de PPS
	CFGCON = 0x00;

	// Fem que el port sigui 'Output compare'
	*rpaxr = p_bit_rpaxr;

	// Bloquejem el canvi PPS
	SYSKEY = 0x00;

	// Deshabilitem Pwm (output compare)
	*ocxcon = 0x00;
	*ocxr   = 0x00;
	*ocxrs  = 0x00;
	*port &= ~bit_port;

	}


// ----------------------------------------------------------------------------
bool
Pwm::set(unsigned int p,void (*call)(Pwm*)) {
	/*
	FUNCIO:
		Estableix periode de funcionament del PWM
		Si el timer ja estava en on, fa un reset del contator.
		Si hi es, activa el callback

	PARAMETRES
	unsigned int p
		Periode en microsegons. Si es zero, el timer queda aturat

		void (*call)(Pwm*)
			Funcio callback quan expira el periode del timer

	RETORN
		True	El timer s'ha configurat adequadament
		False	El timer no s'ha pogut configurar i/o ha quedat aturat

	NOTA 1:
		Els objectes que emprin el mateix timer tambe es veuran
		afectas per aquesta accio; pero mantenen la seva funcio
		de callback

	NOTA 2:
		La rao de que el timer no es pugui configurar es que el
		valor de 'p' es zero o molt gros per que pugui fer-se
		caber en un periode amb el maxim divisor posible
	*/

	// Preparem el retorn
	bool r = false;

	// Memoritzem funcio de callback
	o_callback = NULL;
	f_callback = call;

	// Parem el modul
	*ocxcon &= ~bit_ocxcon;
	*ocxr  = 0;
	*ocxrs  = 0;

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
Pwm::set(unsigned int p,Callable* ocall,int hcall) {
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

	// Parem el modul
	*ocxcon &= ~bit_ocxcon;
	*ocxr  = 0;
	*ocxrs  = 0;

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
Pwm::on(unsigned long d) {
	/*
	FUNCIO:
		Canvia i activa el PWM amb nou dutty
		Si hi es, activa el callback

	PARAMETRES
		unsigned int d
			Dutty en microsegons

	RETORN
		void
	*/

	// Canviem el dutty
	// Si hi ha funcio de callback, habilitem interrupcio
	// Activem el modul
	dutty  = ((double)periode*d)/pmicros;
	*ocxrs = dutty;
	if( (f_callback!=NULL) || (o_callback!=NULL) ) irq_enable();
	*ocxcon |= bit_ocxcon;

	return;
	}


// ----------------------------------------------------------------------------
void
Pwm::off(void) {
	/*
	FUNCIO:
		Atura el dutty del PWM.
		Si hi es, activa el callback
	*/

	if( (f_callback!=NULL) || (o_callback!=NULL) ) irq_enable();
	*ocxrs = 0;

	return;
	}


// ----------------------------------------------------------------------------
void
Pwm::stop(void) {
	/*
	FUNCIO:
		Atura el dutty del PWM.
		Desactiva el callback
	*/

	*ocxrs = 0;
	irq_disable();

	return;
	}


// ----------------------------------------------------------------------------
void
Pwm::Irq(void) {
	/*
	FUNCIO INTERNA:
		El periode ha expirat
		Cridem a la funcio de callback, si hi es
	*/

	// Cridem a la funcio d'usuari per que ens doni nous
	// valors de periode i dutty
	if( f_callback!=NULL ) f_callback(this);
	if( o_callback!=NULL ) o_callback->callback(h_callback);

	return;
	}


