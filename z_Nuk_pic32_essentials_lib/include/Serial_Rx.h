// ****************************************************************************
// File:  Serial_Rx.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Serial
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_SERIAL_RX
#define NUK_PIC_ESSENTIALS_SERIAL_RX




// ****************************************************************************
// Declaracio de la clase Serial
//
class Serial_Rx : public IrqObject, public Fifo {

	public:

	// Registres de uart rx
	volatile unsigned int* rx_uxrxreg;
	volatile unsigned int* rx_uxbrg;
	volatile unsigned int* rx_uxrxr;
	volatile unsigned int* rx_uxmode;
	volatile unsigned int* rx_uxsta;

	// Configuracio registres rx
	unsigned int bit_rx_uxmode;
	unsigned int bit_rx_urxen;
	unsigned int bit_rx_urxda;

	// Callback function
	void (*f_callback)(Serial_Rx*);
	
	// Destructor
	~Serial_Rx();
    
	// Constructors
	Serial_Rx(UARTRXLIST,unsigned int, void (*)(Serial_Rx*)=NULL);

	// Funcions
   void Irq(void);
	};
    
    
 
   
#endif // NUK_PIC_ESSENTIALS_SERIAL


