// ****************************************************************************
// File:  Nuk_pic_essentials.h
// Autor: Lluis
// Descripcio
//

#ifndef NUK_PIC_ESSENTIALS
#define NUK_PIC_ESSENTIALS




// ****************************************************************************
// Macros
//
#define sleep() asm volatile ( "wait" ); RCONCLR = 0x2
#define frequency() (DEVCFG3&0xFFFF)


// ****************************************************************************
// Includes
//

#include <time.h>

#include "Definitions.h"
#include "Machines.h"
#include "Callable.h"
#include "Caller.h"
#include "Fifo.h"
#include "IrqObject.h"
#include "TimerObject.h"
#include "Timer.h"
#include "Pwm.h"
#include "Analog.h"
#include "Digital.h"
#include "Ei.h"
#include "Serial_Rx.h"
#include "Serial_Tx.h"
#include "Serial.h"
#include "Spi_mstr.h"
#include "Spi_slv.h"
#include "I2c.h"




// ****************************************************************************
// Functions
//
void	nuk_pic_essentials(void);



#endif // NUK_PIC_ESSENTIALS


