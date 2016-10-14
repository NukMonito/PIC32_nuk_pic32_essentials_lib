// ****************************************************************************
// File:  Serial.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase Serial
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Serial.h"




// ****************************************************************************
// Implementacio de la clase Rf_class
//

// ----------------------------------------------------------------------------
Serial::Serial(
	volatile unsigned int& p_rx_port,
	volatile unsigned int& p_rx_ansel,
	volatile unsigned int& p_rx_tris,
	unsigned int p_rx_num_bit,

	volatile unsigned int& p_rx_uxrxreg,
	volatile unsigned int& p_rx_uxbrg,
	volatile unsigned int& p_rx_uxrxr,
	volatile unsigned int& p_rx_uxmode,
	volatile unsigned int& p_rx_uxsta,
	unsigned int bit_rx_uxrxr,
	unsigned int bit_rx_uxmode,
	unsigned int bit_rx_urxen,
	unsigned int bit_rx_urxda,

	volatile unsigned int& p_iecx,
	volatile unsigned int& p_ifsx,
	volatile unsigned int& p_ipcx,
	unsigned int bit_iecx,
	unsigned int bit_ifsx,
	unsigned int bit_ipcx,
	unsigned int interrupt,

	volatile unsigned int& p_tx_port,
	volatile unsigned int& p_tx_ansel,
	volatile unsigned int& p_tx_tris,
	unsigned int p_tx_num_bit,

	volatile unsigned int& p_tx_uxtxreg,
	volatile unsigned int& p_tx_uxbrg,
	volatile unsigned int& p_tx_rpaxr,
	volatile unsigned int& p_tx_uxmode,
	volatile unsigned int& p_tx_uxsta,
	unsigned int bit_tx_rpaxr,
	unsigned int bit_tx_uxmode,
	unsigned int bit_tx_utxen,
	unsigned int bit_tx_utxbf,

	unsigned int baud,
	void (*call)(Serial_Rx*) ) :

Serial_Rx(
	p_rx_port,
	p_rx_ansel,
	p_rx_tris,
	p_rx_num_bit,	
	p_rx_uxrxreg,
	p_rx_uxbrg,
	p_rx_uxrxr,
	p_rx_uxmode,
	p_rx_uxsta,
	bit_rx_uxrxr,
	bit_rx_uxmode,
	bit_rx_urxen,
	bit_rx_urxda,
	p_iecx,
	p_ifsx,
	p_ipcx,
	bit_iecx,
	bit_ifsx,
	bit_ipcx,
	interrupt,
	baud,
	call ),

Serial_Tx(
	p_tx_port,
	p_tx_ansel,
	p_tx_tris,
	p_tx_num_bit,
	p_tx_uxtxreg,
	p_tx_uxbrg,
	p_tx_rpaxr,
	p_tx_uxmode,
	p_tx_uxsta,
	bit_tx_rpaxr,
	bit_tx_uxmode,
	bit_tx_utxen,
	bit_tx_utxbf,
	baud ) {

	/*
	CONSTRUCTOR
		Contrueix l'IrqObject Serial
		Configura
		UARTx Rx
		UARTx Tx
		baud
		8/1/N

	PARMETRES:
		UARTx
			x = Nombre de UART

		int baud
			Baudios

		void (*call)(Serial_Rx*)
			Punter a la funcio de callback per interrucio de recepcio
	*/
	
	}

