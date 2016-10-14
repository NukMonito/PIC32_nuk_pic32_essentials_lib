// ****************************************************************************
// File:  Caller.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Caller
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_CALLER
#define NUK_PIC_ESSENTIALS_CALLER




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Declaracio de la clase Caller
//
class Caller {

	public:

	// Objecte de callback d'usuari per interrupcio
	// Handle del objecte del callback
	Callable* o_callback;
	int h_callback;

	};




#endif // NUK_PIC_ESSENTIALS_CALLER


