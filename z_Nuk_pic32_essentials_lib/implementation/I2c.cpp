// ****************************************************************************
// File:  I2c.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase I2CM (I2c master)
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "I2c.h"


// ****************************************************************************
// Implementacio de la clase Rf_class
//

// ----------------------------------------------------------------------------
I2c::I2c(
	volatile unsigned int& p_sda_port,
	volatile unsigned int& p_sda_ansel,
	volatile unsigned int& p_sda_tris,
	unsigned int p_sda_num_bit,

	volatile unsigned int& p_scl_port,
	volatile unsigned int& p_scl_ansel,
	volatile unsigned int& p_scl_tris,
	unsigned int p_scl_num_bit,

	volatile unsigned int& p_i2cxcon,
	volatile unsigned int& p_i2cxstat,
	volatile unsigned int& p_i2cxbrg,
	volatile unsigned int& p_i2cxtrn,
	volatile unsigned int& p_i2cxrcv,
	volatile unsigned int& p_i2cxadd,

	// Pulse Gobbler Delay
	unsigned int p_pgd,

	// Control bits
	unsigned int p_bit_sen,
	unsigned int p_bit_rsen,
	unsigned int p_bit_pen,
	unsigned int p_bit_rcen,
	unsigned int p_bit_acken,
	unsigned int p_bit_ackdt,
	unsigned int p_bit_stren,
	unsigned int p_bit_disslw,
	unsigned int p_bit_sclrel,
	unsigned int p_bit_on,

	// Status bits
	unsigned int p_bit_rw,
	unsigned int p_bit_s,
	unsigned int p_bit_p,
	unsigned int p_bit_da,
	unsigned int p_bit_i2cov,
	unsigned int p_bit_iwcol,
	unsigned int p_bit_bcl,
	unsigned int p_bit_trstat,
	unsigned int p_bit_ackstat,

	// Interrupt
	volatile unsigned int& p_iecx,
	volatile unsigned int& p_ifsx,
	volatile unsigned int& p_ipcx,
	unsigned int bit_iecx,
	unsigned int bit_ifsx,
	unsigned int bit_ipcx,
	unsigned int interrupt,

	// Frequency
	// Slave address
	// Callback function
	unsigned int freq,
	unsigned char slave_addr,
	void (*call)(I2c*) ) :

IrqObject(
	p_iecx,
	p_ifsx,
	p_ipcx,
	bit_iecx,
	bit_ifsx,
	bit_ipcx,
	interrupt) {

	/*
	CONSTRUCTOR
		Construeix I2c
		Configura
		baud
		Multimaster

	PARAMETERS:
		I2Cx
			Port I2C on x = I2C port

		int freq
			Frequency. One of these:
				I2C_100K
				I2C_400K
				I2C_1M

		char slave_addr
			Slave address
			Optional parameter. Required when acts as slave

		void (*call)(I2c*) )
			Function to call when a slave write are demanded.
			Optional parameter. Required when acts as slave
		
	*/

	// Port SDA Digital
	// Port SDL Digital
	p_sda_ansel &= ~((unsigned int)(0b1<<p_sda_num_bit));
	p_scl_ansel &= ~((unsigned int)(0b1<<p_scl_num_bit));
	
	// Registers of I2C
	i2cxcon  = &p_i2cxcon;
	i2cxstat = &p_i2cxstat;
	i2cxbrg  = &p_i2cxbrg;
	i2cxtrn  = &p_i2cxtrn;
	i2cxrcv  = &p_i2cxrcv;
	i2cxadd  = &p_i2cxadd;

	// Control bits
	bit_sen = p_bit_sen;
	bit_rsen = p_bit_rsen;
	bit_pen = p_bit_pen;
	bit_rcen = p_bit_rcen;
	bit_acken = p_bit_acken;
	bit_ackdt = p_bit_ackdt;
	bit_stren = p_bit_stren;
	bit_disslw = p_bit_disslw;
	bit_sclrel = p_bit_sclrel;
	bit_on = p_bit_on;

	// Status bits
	bit_rw = p_bit_rw;
	bit_s = p_bit_s;
	bit_s = p_bit_p;
	bit_da = p_bit_da;
	bit_i2cov = p_bit_i2cov;
	bit_iwcol = p_bit_iwcol;
	bit_bcl = p_bit_bcl;
	bit_trstat = p_bit_trstat;
	bit_ackstat = p_bit_ackstat;

	// Pulse Gobbler Delay
	// Frequencia
	pgd = p_pgd;
	//*i2cxbrg = 0x02C;

	*i2cxbrg = ((1/((double)freq*2))-((double)p_pgd/1000000000))*(double)frequency()*1000000-2;

	if( freq!=I2C_400K ) *i2cxcon |= bit_disslw;

	// Slave address
	*i2cxadd = slave_addr>>1;

	// Callback pointer function
	f_callback = call;
	if( f_callback!=NULL ) *i2cxcon |= bit_stren;

	// Enable module
	// Enable interrupt
	*i2cxcon |= bit_on;
	irq_enable();
	}


// ----------------------------------------------------------------------------
void
I2c::transmit(char addr,char* trm, int sizetrm,char* rcb,int sizercb) {
	/*
	FUNCIO:
		I2C Transaction

	PARAMETRES:
		char* addr
			address of slave

		char* trm
			string to transmit

		int sizetrm
			size of trm

		char* buffer
			string to receibe

		int sizercb
			size of wanted characters to receibe

	RETURN:
		bool
			true == transacction succefull
			false == transacction not succefull
	*/

	// 'i' general pourpose counter;
	int i;

	// Retry until no collision occurs
	do {
		// Reset
		*i2cxstat &= ~bit_i2cov;
		*i2cxstat &= ~bit_iwcol;
		*i2cxcon &= ~bit_on;
		*i2cxcon |= bit_on;

		// Initiate start condition
		*i2cxcon |= bit_sen;
		while( *i2cxcon&bit_sen );

		// Send slave address
		if( (*i2cxstat&bit_bcl)==0 ) {
			*i2cxtrn = addr&0xFE;
			while( *i2cxstat&bit_trstat );
			}

		// Transmit
		i = 0;
		while( (*i2cxstat&bit_bcl)==0 && i<sizetrm ) {
			*i2cxtrn = trm[i];
			while( *i2cxstat&bit_trstat );
			i++;
			}

		// If there are bytes to receibe
		if( (*i2cxstat&bit_bcl)==0 &&  sizercb>0 ) {

			// Initiate restart condition
			*i2cxcon |= bit_rsen;
			while( *i2cxcon&bit_rsen );

			// Send slave address
			if( (*i2cxstat&bit_bcl)==0 ) {
				*i2cxtrn = addr|0x01;
				while( *i2cxstat&bit_trstat );
				}
			}

		// Receibe 'sizercb'-1 bytes (maybe 0)
		i = 0;
		sizercb--;
		while( (*i2cxstat&bit_bcl)==0 && i<sizercb ) {
			*i2cxcon |= bit_rcen;
			while( *i2cxcon&bit_rcen );
			rcb[i] = *i2cxrcv;
			*i2cxcon &= ~bit_ackdt;
			*i2cxcon |= bit_acken;
			while( *i2cxcon&bit_acken );
			i++;
			}

		// Receibe last byte (maybe 0)
		sizercb++;
		if( (*i2cxstat&bit_bcl)==0 && i<sizercb ) {
			*i2cxcon |= bit_rcen;
			while( *i2cxcon&bit_rcen );
			rcb[i] = *i2cxrcv;
			*i2cxcon |= bit_ackdt;
			*i2cxcon |= bit_acken;
			while( *i2cxcon&bit_acken );
			}

		// Initiate stop condition
		if ( (*i2cxstat&bit_bcl)==0 ) {
			*i2cxcon |= bit_pen;
			while( *i2cxcon&bit_pen );
			}

		// Few delay if a collision occurs
		if ( *i2cxstat&bit_bcl ) {
			for(i=0;i<100;i++);
			}

		// Retry until no collision occurs
		} while( *i2cxstat&bit_bcl );

	return;
	}


// ----------------------------------------------------------------------------
void
I2c::Irq(void) {
	/*
	INTERNAL FUNCTION:
		I2Cx start or stop detected
		or
		I2Cx reception/transmision

		In slave mode, if user callback function was defined, this module call it
		when a transmit character are required and no ones are aviable in slave
		FIFO. If callback are not deffined, or the callback function puts nothiing
		in slave FIFO, then NULL bytes will be transmited.

		This function puts in own FIFO all character receibed. Then, the user
		thread can get it at any time.

	*/

	// If start or stop bit detected
	if( (*i2cxstat&bit_s) || (*i2cxstat&bit_p) ) {
		*i2cxcon &= ~bit_on;
		*i2cxcon |= bit_on;
		}

	// Slave
	else {

		// Pull the SCLx low (hold the I2C bus)
		*i2cxcon &= ~bit_sclrel;

		// If slave reception
		if( (*i2cxstat&bit_rw)==0 ) {

			// Receibe a char
			// If it is not an address, insert it in FIFO
			char r;
			r = *i2cxrcv;
			if( (*i2cxstat&bit_da) ) slave_in.insert(r);
			}

		// If slave transmision
		else {

			// If there are not a callback function, transmit a dummy byte
			if( f_callback==NULL ) *i2cxtrn = NULL;

			else {
				// If there are almost one char in slave FIFO, then transmit it
				// Else, call callback function and transmit a char, even no ones
				char rchar[1];
				rchar[0] = NULL;
				if( slave_out.get(rchar,1) ) {
					*i2cxtrn = rchar[0];
					}
				else {
					f_callback(this);
					slave_out.get(rchar,1);
					*i2cxtrn = rchar[0];
					}
				}
			}

		// Release SCLx
		*i2cxcon |= bit_sclrel;
		}

	return;
	}


