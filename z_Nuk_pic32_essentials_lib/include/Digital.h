// ****************************************************************************
// File:  Digital.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Digital
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_DIGITAL
#define NUK_PIC_ESSENTIALS_DIGITAL




// ****************************************************************************
// Declaracio de la clase Digital
//
class Digital : public IrqObject {
    
	public:
        
	// Registres del port
	volatile unsigned int* port;
	volatile unsigned int* ansel;
	volatile unsigned int* tris;
	volatile unsigned int* odc;
	volatile unsigned int* cnpu;
	volatile unsigned int* cnpd;
	volatile unsigned int* cncon;
	volatile unsigned int* cnen;
	volatile unsigned int* cnstat;
    
	// Mascara del bit del en el registre del port
	// Change Notice (CN) Control ON bit
	unsigned int port_bit;
	unsigned int bit_cn_on;

	// Callback function
	void (*f_callback)(Digital*);

	// Destructor
	~Digital();
    
	// Constructors
	Digital(DIGITALLIST);
    
	// Funcions
	void input(void);
	void on(void);
	void off(void);
	void open(void);
	void close(void);
	void inv(void);
	bool ison(void);
	bool ispullup(void);
	void onchange(void(*)(Digital*));
	void onchange(Callable*,int);

	// Funcions internes
	void Irq(void);
	};




#endif // NUK_PIC_ESSENTIALS_DIGITAL


