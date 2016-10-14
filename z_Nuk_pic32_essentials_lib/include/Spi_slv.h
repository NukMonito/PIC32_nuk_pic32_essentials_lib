// ****************************************************************************
// File:  Spi_slv.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Spi_slv
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_SPI_SLV
#define NUK_PIC_ESSENTIALS_SPI_SLV




// ****************************************************************************
// Declaracio de la clase Spi
//
class Spi_slv : public Callable {

	public:

	// Atributs

	// Registres
	volatile unsigned int* rpaxr;
	volatile unsigned int* sdixr;
	volatile unsigned int* spixcon;
	volatile unsigned int* spixcon2;
	volatile unsigned int* spixstat;
	volatile unsigned int* spixbrg;
	volatile unsigned int* spixbuf;

	// Configuracio de registres i bits
	unsigned int bit_msten;
	unsigned int bit_cke;
	unsigned int bit_ckp;
	unsigned int bit_on;

	unsigned int bit_spirbf;
	unsigned int bit_spitbf;
	unsigned int bit_spirov;
       
	// 'select' Pin de seleccio
	Digital* select;

	char user_char;

	// Funcio de callback
	void (*f_callback)(Spi_slv*,bool,char&);
   
	// Destructor
	~Spi_slv();

	// Constructors
	Spi_slv(SPILIST,Digital&,void(*)(Spi_slv*,bool,char&));

	// Funcions
	void callback(int);
	};




#endif // NUK_PIC_ESSENTIALS_SPI_SLV


