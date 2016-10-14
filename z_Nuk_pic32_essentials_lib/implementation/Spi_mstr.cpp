// ****************************************************************************
// File:  Spi_mstr.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase Spi_mstr
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Spi_mstr.h"




// ****************************************************************************
// Implementacio de la clase Spi_class
//

// ----------------------------------------------------------------------------
Spi_mstr::~Spi_mstr() {
	/*
	DESTRUCTOR
		Destructor del objecte. Tambe destruiex l'objecte python
	*/

	// Deshabilitem Spi
	*spixcon = 0;
	}


// ----------------------------------------------------------------------------
Spi_mstr::Spi_mstr(
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

	unsigned int p_freq,
	double p_delay,
	bool p_edge,
	bool p_polarity ) {
	/*
	CONSTRUCTOR
		Contrueix l'objecte SPI

	PARMETRES:
		SPIx
			SPIx
			x = Nombre del SPI

		unsigned int freq
			Frequencia del bus

		double p_delay
			Tems en microsegons entre bytes transmitits

		bool p_edge
			Clock Edge Select bit

		bool p_polarity
			Clock Polarity Select bit

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

	// Port SCK Digital-Out
	p_sck_ansel &= ~((unsigned int)(0b1<<p_sck_num_bit));
	p_sck_tris  &= ~((unsigned int)(0b1<<p_sck_num_bit));

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


	// Default frec
	// Default edge
	// Default polarity
	freq = p_freq;
	delay = p_delay;
	edge = p_edge;
	polarity = p_polarity;

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

	// Configurem SPI2BRG = frequencia
	// Habilitem el bus
	*spixbrg  = ((frequency()*1000000)/(2*freq))-1;
	*spixcon  = bit_msten;
	if( edge ) *spixcon  |= bit_cke;
	if( polarity ) *spixcon  |= bit_ckp;
	*spixcon  |= bit_on;
	}


// ----------------------------------------------------------------------------
char*
Spi_mstr::transmit(
		Digital& port,
		char* cadena,
		int l,
		unsigned int p_freq,
		double p_delay,
		bool p_edge,
		bool p_polarity ) {
	/*
	FUNCIO
		Transmiteix 'l' caracters de la 'cadena'
		Reb tans caracters com s'hagin transmitit
  
	PARAMETRES:
		Digital& port
			Port digital que s'ha posar a 0 per seleccionar el dispositiu SPI

		char* cadena
			Cadena a transmitir
    
		int l
			Longitud de la cadena

		unsigned int p_freq
			Frequencia del bus. Es soposa diferenta a la que s'ha
			donat en el constructor

		double p_delay. Si s'especifica 'freq', 
			Temps en microsegons entre bytes transmitits
			es soposa diferent al que s'ha donat en el constructor

		bool p_edge
			Clock Edge Select bit. Si s'especifica 'freq', 
			es soposa diferent al que s'ha donat en el constructor

		bool p_polarity
			Clock Polarity Select bit. Si s'especifica 'freq', 
			es soposa diferent al que s'ha donat en el constructor

	RETORN:
		char*
			Caracters rebuts
	*/

	// 'n_delay' iteracions necesaries per cubrir'delay' entre bytes transmitits
	unsigned long n_delay;

	// Si la frequencia del bus canvia, tambe canviem delay, edge i polarity
	if( p_freq ) {

		// Reset configuracio SPI
		*spixcon    = 0x00;
		*spixcon2   = 0x00;
		*spixstat   = 0x00;

		// Configurem SPI2BRG = frequencia
		// Habilitem el bus
		*spixbrg  = ((frequency()*1000000)/(2*p_freq))-1;
		*spixcon  = bit_msten;
		if( p_edge ) *spixcon  |= bit_cke;
		if( p_polarity ) *spixcon  |= bit_ckp;
		*spixcon  |= bit_on;

		// Calculem 'n_delay' per el for del delay entre bytes transmitits
		n_delay = p_delay*(DEVCFG3&0xFFFF)/2;
		}

	else {
		// Calculem 'n_delay' per el for del delay entre bytes transmitits
		n_delay = delay*(DEVCFG3&0xFFFF)/2;
		}

	// Reset overflow and clear buffer
	*spixstat &= ~bit_spirov;
	*spixbuf;

	// Select periferal
	port.off();

	// Per cada caracter a transmitir
	for(int i=0;i<l;i++) {

		// Delay
		// 'n_delay' ha estat calculat avans
		for( int i=0;i<n_delay;i++);

		// Transmitim i esperem a que la transmisio finalitzi
		*spixbuf = cadena[i];
		while( (*spixstat&bit_spitbf)!=0 );

		// Esperem a que en el buffer Rx hagi un caracter i el lleguim
		while( (*spixstat&bit_spirbf)==0 );
		buff[i] = *spixbuf;
		}
    
	// Posem a 1 el bit del port de seleccio de dispositiu
	port.on();

	// Si la frequencia ha canviat, deixem les coses com estaven
	if( p_freq ) {

		// Reset configuracio SPI
		*spixcon    = 0x00;
		*spixcon2   = 0x00;
		*spixstat   = 0x00;

		// Configurem SPI2BRG = frequencia
		// Habilitem el bus
		*spixbrg  = (((DEVCFG3&0xFFFF)*1000000)/(2*freq))-1;
		*spixcon  = bit_msten;
		if( edge ) *spixcon  |= bit_cke;
		if( polarity ) *spixcon  |= bit_ckp;
		*spixcon  |= bit_on;
		}

	return buff;
	}


