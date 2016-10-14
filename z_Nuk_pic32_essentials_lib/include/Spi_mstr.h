// ****************************************************************************
// File:  Spi_mstr.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Spi_mstr
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_SPI_MSTR
#define NUK_PIC_ESSENTIALS_SPI_MSTR




// ****************************************************************************
// Declaracio de la clase Spi
//
class Spi_mstr {

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

	// Flow registers
	unsigned int bit_spirbf;
	unsigned int bit_spitbf;
	unsigned int bit_spirov;

	// Default frec
	// Default edge
	// Default polarity
	unsigned int freq;
	double delay;
	bool edge;
	bool polarity;
       
	// 'buff'  Buffer del bus Spi
	char buff[BUFF_SIZE];
   
	// Destructor
	~Spi_mstr();

	// Constructors
	Spi_mstr(
			SPILIST,
			unsigned int p_freq,
			double p_delay = 0,
			bool edge = true,
			bool polarity = false );

	// Funcions
	char* transmit(
			Digital&,char*,
			int,unsigned int freq = 0,
			double p_delay = 0,
			bool edge = true,
			bool polarity = false );
	};




#endif // NUK_PIC_ESSENTIALS_SPI_MSTR


