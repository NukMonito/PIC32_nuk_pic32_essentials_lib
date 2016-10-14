// ****************************************************************************
// File:  Serial_Tx.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase Serial_Tx
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Serial_Tx.h"




// ****************************************************************************
// Implementacio de la clase Rf_class
//

// ----------------------------------------------------------------------------
Serial_Tx::~Serial_Tx() {
	/*
	DESTRUCTOR
		Destructor
	*/

	// Deshabilitem tx
	*tx_uxmode &= ~bit_tx_uxmode;
	*tx_uxsta  &= ~bit_tx_utxen;
	}

// ----------------------------------------------------------------------------
Serial_Tx::Serial_Tx(
	volatile unsigned int& p_tx_port,
	volatile unsigned int& p_tx_ansel,
	volatile unsigned int& p_tx_tris,
	unsigned int p_tx_num_bit,
	volatile unsigned int& p_tx_uxtxreg,
	volatile unsigned int& p_tx_uxbrg,
	volatile unsigned int& p_tx_rpaxr,
	volatile unsigned int& p_tx_uxmode,
	volatile unsigned int& p_tx_uxsta,
	unsigned int p_bit_tx_rpaxr,
	unsigned int p_bit_tx_uxmode,
	unsigned int p_bit_tx_utxen,
	unsigned int p_bit_tx_utxbf,
	unsigned int baud ) {
	/*
	CONSTRUCTOR
		Contrueix l'IrqObject Serial_Tx
		Configura
			UARTx Tx
			baud
			8/1/N

	PARMETRES:
		UARTx
			UARTx
			x = Nombre de UART

		int baud
			Baudios

		void (*call)(void)
			Punter a la funcio de callback per interrucio de recepcio
	*/

	// Init Nuk_pic_essentials
	nuk_pic_essentials();

	// Port Digital-Out
	p_tx_ansel &= ~((unsigned int)(0b1<<p_tx_num_bit));

	// Registres de uart tx
	tx_uxtxreg  = &p_tx_uxtxreg;
	tx_uxbrg    = &p_tx_uxbrg;
	tx_rpaxr    = &p_tx_rpaxr;
	tx_uxmode   = &p_tx_uxmode;
	tx_uxsta    = &p_tx_uxsta;

	// Configuracio registres tx
	bit_tx_uxmode = p_bit_tx_uxmode;
	bit_tx_utxen  = p_bit_tx_utxen;
	bit_tx_utxbf  = p_bit_tx_utxbf;

	// Desbloquegem escritura dels registres PPS
	SYSKEY = 0x00;
	SYSKEY = 0xAA996655;
	SYSKEY = 0x556699AA;

	// Permitim el canvi de PPS
	CFGCON = 0x00;

	// Configurem PPS per UART Tx
	*tx_rpaxr = p_bit_tx_rpaxr;

	// Bloquejem el canvi PPS
	SYSKEY = 0x00;

	// baud
	// Habilitem mode 8/1/N
	// Habilitem Tx
	*tx_uxbrg  = (((double)frequency()*1000000)/(16*(double)baud))-1;
	*tx_uxsta  |= bit_tx_utxen;
	*tx_uxmode |= bit_tx_uxmode;
	}


// ----------------------------------------------------------------------------
void
Serial_Tx::put(const char* cadena) {
	/*
	FUNCIO:
		Transmiteix per UARTx una cadena de caracters acabada amb 0x00

	PARAMETRES:
		char* cadena
			Cadena a transmitir

	RETORN:
		void
	*/

	// Transmitim la cadena
	int i = 0;
	while( cadena[i]!=0 ) {
		while( *tx_uxsta&bit_tx_utxbf );
		*tx_uxtxreg = cadena[i];
		i++;
		}

	return;
	}


// ----------------------------------------------------------------------------
void
Serial_Tx::put(const char* cadena,unsigned int size) {
	/*
	FUNCIO:
		Transmiteix per UARTx 'size' caracters de la cadena 'cadena'

	PARAMETRES:
		char* cadena
			Caracters a transmitir

		unsigned int size
			Nombre de caracters a transmitir

	RETORN:
		void
	*/

	int i;

	for(i=0;i<size;i++) {
		while( *tx_uxsta&bit_tx_utxbf );
		*tx_uxtxreg = cadena[i];
		}

	return;
	}


// ----------------------------------------------------------------------------
void
Serial_Tx::put_char(char caracter) {
	/*
	FUNCIO:
		Transmiteix per UARTx un caracter

	PARAMETRES:
		char caracter
		Caracter a transmitir

	RETORN:
		void
	*/

	while( *tx_uxsta&bit_tx_utxbf );
	*tx_uxtxreg = caracter;

	return;
	}


// ----------------------------------------------------------------------------
void
Serial_Tx::put_line(const char* cadena) {
	/*
	FUNCIO:
		Transmiteix per UARTx una cadena de caracters acabada amb 0x00
		Finalment transmeteix un EOL

	PARAMETRES:
		char* cadena
		Cadena a transmitir

	RETORN:
		void
	*/

	put(cadena);
	put_char(EOL);

	return;
	}


// ----------------------------------------------------------------------------
void
Serial_Tx::put_hex(const char* c,int n) {
	/*
	FUNCIO
		Imprimeix el contingut c en fortat hexadecimal

	PARAMETRES
		char* c
			Caracters a imprimir

		int n
			Nombre de caracters en c

	RETORN
		void
	*/
	int i;
	char cc[3];
	char ccc;

	cc[2] = ' ';
	for(i=0;i<n;i++) {
		ccc = c[i];

		cc[1] = ccc&0xF;
		if( cc[1]>9 ) cc[1] += 0x37;
		else cc[1] += 0x30;

		ccc >>= 4;

		cc[0] = ccc&0xF;
		if( cc[0]>9 ) cc[0] += 0x37;
		else cc[0] += 0x30;

		put(cc,3);
		}

	put_line("");
	}



