// ****************************************************************************
// File:  Pwm.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Pwm (Output compare)
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_PWM
#define NUK_PIC_ESSENTIALS_PWM




// ****************************************************************************
// Declaracio de la clase Pwm (Output compare)
//
class Pwm : public TimerObject {
    
	public:

	// Registres del port
	volatile unsigned int* ansel;
	volatile unsigned int* tris;
	volatile unsigned int* port;

	// Variables de configuracio port
	unsigned int bit_port;

	// Registres del Pwm
	volatile unsigned int* rpaxr;
	volatile unsigned int* ocxcon;
	volatile unsigned int* ocxr;
	volatile unsigned int* ocxrs;

	// Variables de configuracio Pwm
	unsigned int bit_rpaxr;
	unsigned int bit_ocxcon;

	// Dytty en unitats de timer
	unsigned long dutty;

	// Callback function
	void (*f_callback)(Pwm*);

	// Destructor
	~Pwm();

	// Constructors
	Pwm(PWMLIST);

	// Funcions
	bool set(unsigned int,void (*call)(Pwm*)=NULL);
	bool set(unsigned int,Callable*,int);
	void on(unsigned long);
	void off(void);
	void stop(void);

	// Funcions internes
	void Irq(void);

	};




// **
#endif // NUK_PIC_ESSENTIALS_PWM


