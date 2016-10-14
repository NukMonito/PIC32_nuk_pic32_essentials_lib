// ****************************************************************************
// File:  Serial.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Serial
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"
 
#ifndef NUK_PIC_ESSENTIALS_SERIAL
#define NUK_PIC_ESSENTIALS_SERIAL




// ****************************************************************************
// Declaracio de la clase Serial
//
class Serial : public Serial_Rx, public Serial_Tx {

	public:

	// Constructors
	Serial(UARTLIST,unsigned int, void (*)(Serial_Rx*)=NULL);

	};

    
    
  
#endif // NUK_PIC_ESSENTIALS_SERIAL


