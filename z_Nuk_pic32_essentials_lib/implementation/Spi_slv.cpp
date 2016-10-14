// ****************************************************************************
// File:  Spi_slv.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase Spi_slv
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Spi_slv.h"




// ****************************************************************************
// Implementacio de la clase Spi_class
//

// ----------------------------------------------------------------------------
Spi_slv::~Spi_slv() {
	/*
	DESTRUCTOR
		Destructor del objecte. Tambe destruiex l'objecte python
	*/

	// Deshabilitem Spi
	*spixcon &= 0;
	}


// ----------------------------------------------------------------------------
Spi_slv::Spi_slv(
	volatile unsigned int& p_sdo_port,
	volatile unsigned int& p_sdo_ansel,
	volatile unsigned int& p_sdo_tris,
	unsigned int p_sdo_num_bit,

	volatile unsigned int& p_sdi_port,
	volatile unsigned int& p_sdi_ansel,
	volatile unsigned int& p_sdi_tris,
	unsigned int p_sdi_num_bit,

	volatile unsigned int& p_sck_port,
	volatile unsigned int& p_sck_ansel,
	volatile unsigned int& p_sck_tris,
	unsigned int p_sck_num_bit,

	volatile unsigned int& p_rpaxr,
	volatile unsigned int& p_sdixr,
	volatile unsigned int& p_spixcon,
	volatile unsigned int& p_spixcon2,
	volatile unsigned int& p_spixstat,
	volatile unsigned int& p_spixbrg,
	volatile unsigned int& p_spixbuf,

	unsigned int p_bit_rpaxr,
	unsigned int p_bit_sdixr,

	unsigned int p_bit_msten,
	unsigned int p_bit_cke,
	unsigned int p_bit_ckp,
	unsigned int p_bit_on,

	unsigned int p_bit_spirbf,
	unsigned int p_bit_spitbf,
	unsigned int p_bit_spirov,

	Digital& p_select,
	void (*p_callback)(Spi_slv*,bool,char&) ) {
	/*
	CONSTRUCTOR
		Contrueix l'objecte SPI

	PARMETRES:
		SPIx
			SPIx
			x = Nombre del SPI

		unsigned int freq
			Frequencia del bus

	RETORN:
		void
	*/

	// Init Nuk_pic_essentials
	nuk_pic_essentials();

	// Port SDO Digital-Out
	p_sdo_ansel &= ~((unsigned int)(0b1<<p_sdo_num_bit));
	p_sdo_tris  &= ~((unsigned int)(0b1<<p_sdo_num_bit));

	// Port SDI Digital-In
	p_sdi_ansel &= ~((unsigned int)(0b1<<p_sdi_num_bit));
	p_sdi_tris  |=  ((unsigned int)(0b1<<p_sdi_num_bit));

	// Port SCK Digital-In
	p_sck_ansel &= ~((unsigned int)(0b1<<p_sck_num_bit));
	p_sck_tris  |=  ((unsigned int)(0b1<<p_sck_num_bit));

	// Registres del port
	rpaxr    = &p_rpaxr,
	sdixr    = &p_sdixr,
	spixcon  = &p_spixcon,
	spixcon2 = &p_spixcon2,
	spixstat = &p_spixstat,
	spixbrg  = &p_spixbrg,
	spixbuf  = &p_spixbuf,

	// Configuracio registres i bits
	bit_msten = p_bit_msten;
	bit_cke = p_bit_cke;
	bit_ckp = p_bit_ckp;
	bit_on = p_bit_on;
	bit_spirbf  = p_bit_spirbf;
	bit_spitbf  = p_bit_spitbf;
	bit_spirov  = p_bit_spirov;

	// Desbloquegem escritura dels registres PPS
	SYSKEY = 0x00;
	SYSKEY = 0xAA996655;
	SYSKEY = 0x556699AA;

	// Permitim el canvi de PPS
	CFGCON = 0x00;

	// configurat per SDOx
	// configurat per SDIx
	// El pin de clock, quedara configurat quan activem SPI
	*rpaxr = p_bit_rpaxr;
	*sdixr = p_bit_sdixr;

	// Bloquejem el canvi PPS
	SYSKEY = 0x00;

	// Clear configuracio, estat i buffer intern SPI
	*spixcon    = 0x00;
	*spixcon2   = 0x00;
	*spixbuf;
	*spixstat   = 0x00;

	// Funcio de callback
	f_callback = p_callback;

	// Memoritzem el Port digital
	// Enable interrupt per fall de seleccio
	select = &p_select;
	select->onchange(this,0);

	// Habilitem el bus
	*spixcon = bit_cke;
	*spixcon |= bit_on;
	
	}


// ----------------------------------------------------------------------------
void
Spi_slv::callback(int) {
	/*
	FUNCIO:
		Pull down del pin de seleccio del Spi

		Crida a la funcio de 'callback' que te la forma:
			void callback(bool& status, char& user_char);

		Cronologicament

		callback

			01.	L'objecte demana a la funcio de callback un caracter.
					Amb 'status'==true indica que ha estat seleccionat
					amb el port digital 'select'. Aqui, el valor de
					'user_char'	es irrelevant.

			02.	La funcio callback ha de suministrar un caracter emplenant
					la variable 'user_char'.

					Aixo fa que:

		El objecte

			03.	Envia per SPI el caracter i a l'hora reb  un altre.

					Aixo produiex una:

		Irq

			04.	L'objecte suministra a la funcio de 'callback' el caracter
					rebut. Amb 'status'==false indica que ha arribat un byte

			05.	La funcio de callback recull el caracter 'user_char'.
					i prepara el seguent, si cal.

	PARAMETRES:
		int
			Sempre 0 (cero)

	RETORN:
		void
	*/

	// Si es falling
	// Demanem un byte de status a callback
	// Reset input
	//	Enviem el byte
	if( !select->ison() ) {

		// Reconfiguracio, estat i buffer intern SPI
		*spixcon    = 0x00;
		*spixcon2   = 0x00;
		*spixbuf;
		*spixstat   = 0x00;

		// Habilitem el bus
		*spixcon = bit_cke;
		*spixcon |= bit_on;

		// Funcio de callback
		f_callback(this,true,user_char);
		*spixstat &= ~bit_spirov;
		*spixbuf = user_char;
		}

	do {
		while( !(*spixstat&bit_spirbf) && !(*(select->port)&select->port_bit) );
		if( *spixstat&bit_spirbf	) {
			user_char = *spixbuf;
			f_callback(this,false,user_char);
			*spixbuf = user_char;
			}
		}while( !(*(select->port)&select->port_bit) );

	return;
	}


