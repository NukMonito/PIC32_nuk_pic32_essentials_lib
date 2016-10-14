// ****************************************************************************
// File:  Timer.h
// Autor: Lluis
// Descripcio
//		Declaracio de la clase Timer
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_TIMER
#define NUK_PIC_ESSENTIALS_TIMER




// ****************************************************************************
// Declaracio de la clase Timer
//
class Timer : public TimerObject {

	public:

	// Callback function
	void (*f_callback)(Timer*);

	// Destructor
	~Timer();

	// Constructors
	Timer(TIMERLIST);

	// Funcions
	void delay(unsigned int);
	bool every(unsigned int,void (*)(Timer*));
	bool every(unsigned int,Callable*,int);
	void on(void);
	void off(void);
	void Irq(void);

	};




#endif // NUK_PIC_ESSENTIALS_TIMER


