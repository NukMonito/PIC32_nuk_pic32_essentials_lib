// ****************************************************************************
// File:  Callable.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Callable
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_CALLABLE
#define NUK_PIC_ESSENTIALS_CALLABLE




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Declaracio de la clase Callable
//
class Callable {

	public:

	// Funcions
	virtual void callback(int)=0;

	};




#endif // NUK_PIC_ESSENTIALS_CALLABLE


