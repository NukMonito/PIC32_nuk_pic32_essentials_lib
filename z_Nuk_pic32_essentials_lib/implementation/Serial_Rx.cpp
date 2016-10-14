// ****************************************************************************
// File:  Serial_Rx.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase Serial_Rx
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Serial_Rx.h"




// ****************************************************************************
// Implementacio de la clase Rf_class
//

// ----------------------------------------------------------------------------
Serial_Rx::~Serial_Rx() {
	/*
	DESTRUCTOR
		Destructor
	*/

	// Deshabilitem tx
	*rx_uxmode &= ~bit_rx_uxmode;
	*rx_uxsta  &= ~bit_rx_urxen;

	// Deshabilitem interrupcio
	irq_disable();

	}


// ----------------------------------------------------------------------------
Serial_Rx::Serial_Rx(

	volatile unsigned int& p_rx_port,
	volatile unsigned int& p_rx_ansel,
	volatile unsigned int& p_rx_tris,
	unsigned int p_rx_num_bit,

	volatile unsigned int& p_rx_uxrxreg,
	volatile unsigned int& p_rx_uxbrg,
	volatile unsigned int& p_rx_uxrxr,
	volatile unsigned int& p_rx_uxmode,
	volatile unsigned int& p_rx_uxsta,
	unsigned int p_bit_rx_uxrxr,
	unsigned int p_bit_rx_uxmode,
	unsigned int p_bit_rx_urxen,
	unsigned int p_bit_rx_urxda,

	volatile unsigned int& p_iecx,
	volatile unsigned int& p_ifsx,
	volatile unsigned int& p_ipcx,
	unsigned int bit_iecx,
	unsigned int bit_ifsx,
	unsigned int bit_ipcx,
	unsigned int interrupt,

	unsigned int baud,
	void (*call)(Serial_Rx*) ) :

IrqObject(
	p_iecx,
	p_ifsx,
	p_ipcx,
	bit_iecx,
	bit_ifsx,
	bit_ipcx,
	interrupt),

Fifo() {
	/*
	CONSTRUCTOR
		Contrueix l'IrqObject Serial
		Configura
		UARTx Rx
		baud
		8/1/N

	PARMETRES:
		UARTx
			UARTx
			x = Nombre de UART

		int baud
			Baudios

		void (*call)(Serial_Rx*)
			Punter a la funcio de callback per interrucio de recepcio
	*/

	// Port Digital-In
	p_rx_ansel &= ~((unsigned int)(0b1<<p_rx_num_bit));
	
	// Registres de uart rx
	rx_uxrxreg  = &p_rx_uxrxreg;
	rx_uxbrg    = &p_rx_uxbrg;
	rx_uxrxr    = &p_rx_uxrxr;
	rx_uxmode   = &p_rx_uxmode;
	rx_uxsta    = &p_rx_uxsta;

	// Configuracio registres rx
	bit_rx_uxmode = p_bit_rx_uxmode;
	bit_rx_urxen = p_bit_rx_urxen;
	bit_rx_urxda = p_bit_rx_urxda;

	// Desbloquegem escritura dels registres PPS
	SYSKEY = 0x00;
	SYSKEY = 0xAA996655;
	SYSKEY = 0x556699AA;

	// Permitim el canvi de PPS
	CFGCON = 0x00;
    
	// Configurem PPS per UART Rx
	*rx_uxrxr = p_bit_rx_uxrxr;

	// Bloquejem el canvi PPS
	SYSKEY = 0x00;

	// baud
	// Habilitem mode 8/1/N
	// Habilitem Rx
	*rx_uxbrg  = ((frequency()*1000000)/(16*baud))-1;
	*rx_uxmode |= bit_rx_uxmode;
	*rx_uxsta  |= bit_rx_urxen;

	// Punter a la funcio de callback
	f_callback = call;

	// Habilitem la interrupcio
	irq_enable();
	}


// ----------------------------------------------------------------------------
void
Serial_Rx::Irq(void) {
	/*
	FUNCIO INTERNA:
		Recepcio serie UARTx
		Emplena el buffer de la Fifo
		Si 'buff' queda ple, matxaca el darrer caracter llegit
	*/

	// NOTA:
	//
	//		Podriem fer:
	//
	//		do {
	//			insert(*rx_uxrxreg);
	//			} while( (*rx_uxsta&bit_rx_urxda) );
	//
	//		pero es mes rapit ...

	//Mentre hagin caracters per llegir
	do {
		buff[pin] = *rx_uxrxreg;
		pin++;
		if( pin==BUFF_SIZE ) pin = 0;
		if( pin==pout ) {
			pin--;
			if( pin<0 ) pin = BUFF_SIZE-1;
			}
		} while( *rx_uxsta&bit_rx_urxda );

	// Cridem a la funicio de callback
	if( f_callback!=NULL ) f_callback(this);

	return;
	}



