// ****************************************************************************
// File:  TimerObject.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase TimerObject
//

// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_TIMEROJBJECT
#define NUK_PIC_ESSENTIALS_TIMEROJBJECT




// ****************************************************************************
// Declaracio de la clase TimerObject
//
class TimerObject : public IrqObject {

	public:

	// Registres
	volatile unsigned int* txcon;
	volatile unsigned int* tmrx;
	volatile unsigned int* prx;
        
	// 'bit'_txcon' Configuracio txcon
	// 'bit_bits' Bits del timer
	// 'div' Llista de divisors posibles
	unsigned int bit_txcon;
	unsigned int bit_bits;
	unsigned int div[8];

	// Dades de configuracio
	// 'divisor' Divisor escullit
	// 'periode' tems en unitats timer
	// 'pmicros' tems en microsegons
	int divisor;
	unsigned long periode;
	unsigned long pmicros;

	// Constructors
	TimerObject(TIMERLIST);

	// Funcions
	bool configure(unsigned long);
	void configure(unsigned long,int);
	virtual void Irq(void)=0;

	};




#endif // NUK_PIC_ESSENTIALS_TIMEROJBJECT


