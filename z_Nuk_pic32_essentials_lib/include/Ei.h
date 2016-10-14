// ****************************************************************************
// File:  Ei.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Ei (External interrupt)
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_EI
#define NUK_PIC_ESSENTIALS_EI




// ****************************************************************************
// Declaracio de la clase Ei (External Interrupt)
//
class Ei : public IrqObject {

	public:

	// Registres del port
	volatile unsigned int* port;
	volatile unsigned int* ansel;
	volatile unsigned int* tris;
	volatile unsigned int* intcon;
	volatile unsigned int* intxr;
    
	// Mascara del bit del en el registre del port
	unsigned int port_bit;
	unsigned int bit_intnep;

	// Callback function
	void (*f_callback)(Ei*);

	// Destructor
	~Ei();

	// Constructors
	Ei(EILIST);

	// Funcions
	bool ison(void);
	void onchange(bool,void (*)(Ei*));
	void onchange(bool,Callable*,int);
	void Irq(void);
	};




#endif // NUK_PIC_ESSENTIALS_EI


