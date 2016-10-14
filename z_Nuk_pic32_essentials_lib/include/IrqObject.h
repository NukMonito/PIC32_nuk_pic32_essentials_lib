// ****************************************************************************
// File:  IrqObject.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase IrqObject
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_IRQOBJECT
#define NUK_PIC_ESSENTIALS_IRQOBJECT




// ****************************************************************************
// Definicions
//
#define _MAX_INTERRUPTS 40




// ****************************************************************************
// Declaracio de la clase IrqObject
//
class IrqObject : public Caller {
    
	public:

	// Registres de tractament d'interrupcions
	volatile unsigned int* iecx;
	volatile unsigned int* ifsx;
	volatile unsigned int* ipcx;

	// Configuracio de la interrupcio
	int interrupt;
	unsigned int bit_iecx;
	unsigned int bit_ifsx;
	unsigned int bit_ipcx;

	// Element en la Llista de suscriptors de interrupcions
	// Mira la implementacio per veure els detalls
	int index;

	// Destructor
	~IrqObject();

	// Constructors
	IrqObject(IRQLIST);

	// Funcions
	void irq_enable(void);
	void irq_disable(void);

	void irq_clear(void);
	virtual void Irq(void)=0;

	};




#endif // NUK_PIC_ESSENTIALS_IRQOBJECT


