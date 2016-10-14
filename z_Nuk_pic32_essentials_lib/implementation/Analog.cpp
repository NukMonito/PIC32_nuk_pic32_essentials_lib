// ****************************************************************************
// File:  Analog.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase Analog
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Analog.h"




// ****************************************************************************
// Implementacio de la clase Analog
//

// ----------------------------------------------------------------------------
Analog::~Analog() {
	/*
	DESTRUCTOR
        Destructor del IrqObject.
	*/
	
	}


// ----------------------------------------------------------------------------
Analog::Analog(
	volatile unsigned int& p_port,
	volatile unsigned int& p_ansel,
	volatile unsigned int& p_tris,
	unsigned int p_port_num,
	unsigned int p_ana_num ) {
	/*
	CONSTRUCTOR:
		Port analogic

	PARAMETRES:
		ANAx
			Port analogic

	RETORN:
		void
	*/

	// Regitres del port
	ansel     = &p_ansel;
	tris      = &p_tris;

	// Nombre del dispositiu analogic
	// Bit del port
	ana_num = p_ana_num;
	port_bit = ((unsigned int)(0b1)<<p_port_num);

	}


// ----------------------------------------------------------------------------
unsigned int
Analog::get(void) {
	/*
	FUNCIO:
		Captura el valor digital de la entrada analogica

	PARAMETRES:
		void

	RETORN:
		int
			Valor capturat
	*/

	// Preparem el retorn
	unsigned int r;

	// Init Nuk_pic_essentials
	nuk_pic_essentials();

	// Analog, Input
	*tris  |= port_bit;
	*ansel |= port_bit;

	// Seleccionem el pin analogic;
	// Internal counter ends sampling and starts conversion
	// Integer 32-bit
	// Tpa = 2
	AD1CHS = ana_num<<16;
	AD1CON1 = 0x04E0;
	AD1CON2 = 0;
	AD1CON3 = 0x0F02;
	AD1CSSL = 0;

	// Activem el conversor AD1CON1<15>=1
	// Iniciem mostra AD1CON1<1>=1
	// Esperem a que acabi la conversio ADC
	// LLegim ADC1BUF0
	// Desactivem ADC
	// Deseleccionem el bit del port
	AD1CON1 |= 0x8000;
	asm("NOP");
	AD1CON1 |= 0x0002;
	while( (AD1CON1&0x0001)==0 );
	r = ADC1BUF0;
	AD1CON1 = 0;

	return r;
	}


