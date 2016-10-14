// ****************************************************************************
// File:  I2c.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase I2C (I2c master)
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_I2C
#define NUK_PIC_ESSENTIALS_I2C




// ****************************************************************************
// Definicions
//

// I2C speed
#define I2C_100K 100000
#define I2C_400K 400000
#define I2C_1M	 1000000




// ****************************************************************************
// Declaracio de la clase I2c
//
class I2c : public IrqObject {

	public:

	// Registres de uart rx
	volatile unsigned int* i2cxcon;
	volatile unsigned int* i2cxstat;
	volatile unsigned int* i2cxbrg;
	volatile unsigned int* i2cxtrn;
	volatile unsigned int* i2cxrcv;
	volatile unsigned int* i2cxadd;

	// Pulse Gobbler Delay
	unsigned int pgd;

	// Control bits
	unsigned int bit_sen;
	unsigned int bit_rsen;
	unsigned int bit_pen;
	unsigned int bit_rcen;
	unsigned int bit_acken;
	unsigned int bit_ackdt;
	unsigned int bit_stren;
	unsigned int bit_disslw;
	unsigned int bit_sclrel;
	unsigned int bit_on;

	// Status bits
	unsigned int bit_rw;
	unsigned int bit_s;
	unsigned int bit_p;
	unsigned int bit_da;
	unsigned int bit_i2cov;
	unsigned int bit_iwcol;
	unsigned int bit_bcl;
	unsigned int bit_trstat;
	unsigned int bit_ackstat;

	// Callback function
	void (*f_callback)(I2c*);

	// Slave Fifos
	Fifo slave_in;
	Fifo slave_out;

	// Constructors
	I2c(I2CLIST,unsigned int,unsigned char = 0,void (*)(I2c*) = NULL);

	// Funcions
	void transmit(char,char*,int,char* = NULL,int = 0);

	int	get(char* c){ slave_in.get(c); }
	bool	get(char* c, int i){ slave_in.get(c,i); }
	char	get_char(){ slave_in.get_char(); }
	bool	get_line(char* c){ slave_in.get_line(c); }

   void	put(char c){ slave_out.insert(c); }
   void	put(const char* c){ slave_out.insert(c); }
   void	put(const char* c,int i){ slave_out.insert(c,i); }
	void	put_line(const char* c){ slave_out.insert_line(c); }

   void Irq(void);
	
	};

    
    

#endif // NUK_PIC_ESSENTIALS_I2C


