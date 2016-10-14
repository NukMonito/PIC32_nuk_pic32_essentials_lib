// ****************************************************************************
// File:  Serial_Tx.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Serial_Tx
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_SERIAL_TX
#define NUK_PIC_ESSENTIALS_SERIAL_TX




// ****************************************************************************
// Declaracio de la clase Serial
//
class Serial_Tx {

	public:

	// Registres de uart tx
	volatile unsigned int* tx_uxtxreg;
	volatile unsigned int* tx_uxbrg;
	volatile unsigned int* tx_rpaxr;
	volatile unsigned int* tx_uxmode;
	volatile unsigned int* tx_uxsta;

	// Configuracio registres tx
	unsigned int bit_tx_uxmode;
	unsigned int bit_tx_utxen;
	unsigned int bit_tx_utxbf;

	// Destructor
	~Serial_Tx();
    
	// Constructors
	Serial_Tx(UARTTXLIST,unsigned int);

	// Funcions
	void put(const char*);
	void put(const char*,unsigned int);
	void put_char(char);
	void put_line(const char*);
	void put_hex(const char*,int);
	};




#endif // NUK_PIC_ESSENTIALS_SERIAL_TX


