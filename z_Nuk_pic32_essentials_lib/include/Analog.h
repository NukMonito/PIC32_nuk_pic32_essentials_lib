// ****************************************************************************
// File:  Analog.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Analog
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_ANALOG
#define NUK_PIC_ESSENTIALS_ANALOG




// ****************************************************************************
// Declaracio de la clase Analog
//
class Analog {
    
	public:

	// Atributs
        
	// Registres del port
	volatile unsigned int* ansel;
	volatile unsigned int* tris;
    
	// Bit del port
	// Nombre del dispositiu analogic
	unsigned int port_bit;
	unsigned int ana_num;

	// Destructor
	~Analog();

	// Constructors
	Analog(ANALIST);
    
	// Funcions
	unsigned int get(void);
	};




#endif // NUK_PIC_ESSENTIALS_ANALOG


