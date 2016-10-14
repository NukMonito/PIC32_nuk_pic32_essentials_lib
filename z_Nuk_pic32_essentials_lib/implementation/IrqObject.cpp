// ****************************************************************************
// File:  IrqObject.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase IrqObject
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "IrqObject.h"




// ****************************************************************************
// Implementacio de la clase IrqObject i de la gestio d'intrrupcions
//

// ----------------------------------------------------------------------------
// Llista de suscriptors d'interrupcions
// 'irqList_obj' Llista d'objectes suscriptors
// 'irqList_int' Llista d'interrupcions dels suscriptors
// 'irqList_last' Element mes alt ocupat en la llista
IrqObject*	irqList_obj[_MAX_INTERRUPTS];
int			irqList_int[_MAX_INTERRUPTS];
int			irqList_last = -1;


// ----------------------------------------------------------------------------
IrqObject::~IrqObject() {
	/*
	DESTRUCTOR
    	Elimina el Objecte
	*/

	// Elimina el Objecte de la llista de suscriptors
	irq_disable();
	
	}


// ----------------------------------------------------------------------------
IrqObject::IrqObject(
	volatile unsigned int& p_iecx,
	volatile unsigned int& p_ifsx,
	volatile unsigned int& p_ipcx,
	unsigned int p_bit_iecx,
	unsigned int p_bit_ifsx,
	unsigned int p_bit_ipcx,
	unsigned int p_interrupt) {
	/*
	CONTSTRUCTOR
		Inicialitza, si cal, la llista de suscriptors
	*/

	// Init Nuk_pic_essentials
	nuk_pic_essentials();

	// Registres d'interrupcio
	iecx = &p_iecx;
	ifsx = &p_ifsx;
	ipcx = &p_ipcx;

	// Memoritzem
	interrupt = p_interrupt;
	bit_iecx  = p_bit_iecx;
	bit_ifsx  = p_bit_ifsx;
	bit_ipcx  = p_bit_ipcx;

	// Assegurem que noltros no hi som a la llista de suscriptors;
	index = -1;
	}


// ---------------------------------------------------------------------------
void
IrqObject::irq_enable(void) {
	/*
	FUNCIO:
		Inclou l'objecte a la llista de suscriptors d'interrupcio
	*/

	// Si la interrupcio no esta ja hablilida
	if( index==-1 ) {

		// Fem la suscripcio
		irqList_last++;
		index = irqList_last;
		irqList_obj[index] = this;
		irqList_int[index] = interrupt;

		// Prioritat interrupcio
		// Clear flag interrupcio
		// Habilitem interrupcio
		*ipcx |=  bit_ipcx;
		*ifsx &= ~bit_ifsx;
		*iecx |=  bit_iecx;
		}

	return;
	}


// ---------------------------------------------------------------------------
void
IrqObject::irq_disable(void) {
	/*
	FUNCIO:
		Esborra el IrqObject de la llista d'interrupcions

	PARAMETRES.
		void

	RETORN:
		void
	*/

	// Variable de proposit general
	int i;

	// Si la interrupcio esta habilida
	if( index!=-1 ) {

		// Col.loquem el darrer element de la llista en el
		// lloc que deixem
		irqList_obj[index] = irqList_obj[irqList_last];
		irqList_int[index] = irqList_int[irqList_last];
		irqList_obj[index]->index = index;
		index = -1;
		irqList_last--;

		// Deshabilitem la interrupcio (provisionalment)
		*iecx &= ~bit_iecx;
		*ifsx &= ~bit_ifsx;

		// Cerquem si hi ha altres subscriptors
		// a la mateixa interrupcio
		for( i=0;i<=irqList_last;i++ ) {
			if( irqList_int[i]==interrupt ) {
				// Hem trobat un altre suscriptor
				// Habilitem la interrupcio
				*iecx |= bit_iecx;
				}
			}
		}

	return;
	}


// ---------------------------------------------------------------------------
void
IrqObject::irq_clear(void) {
	/*
	FUNCIO:
		Rearma la interrupcio fent clear del flag.

	PARAMETRES.
		void

	RETORN:
		void
	*/

	// Rearmem la interrupcio.
	*ifsx &= ~bit_ifsx;

	return;
	}




// ****************************************************************************
// Tractament d'interrupcions
//

// ----------------------------------------------------------------------------
void irqList_service(int interrupt) {
	/*
	FUNCIO INTERNA:
		Delibera la interrupcio del parametre a cada subscriptor
		Aquesta funcio la crida cada vector d'interrupcio

	PARAMETRES:
		int interrupt
			Nombre del vector d'interrupcio

	RETORN:
		void
	*/

	// Cerquem els suscriptors que tenen la interrupcio 'interrupt'
	// i les cridem
	int i;
	int j = -1;
	for( i=0;i<=irqList_last;i++ ) {
		if(
			(irqList_int[i]==interrupt)  &&
			((*(irqList_obj[i]->ifsx)&irqList_obj[i]->bit_ifsx)!=0)) {
			irqList_obj[i]->Irq();
			j = i;
			}
		}

	// Rearmem interrupcio
	if( j>=0 ) irqList_obj[j]->irq_clear();

	return;
	}


// ----------------------------------------------------------------------------
// Vectors d'interrupcio

#ifdef IRQ00
extern "C" {void __ISR( 0, IPL4SOFT)IrqIrq_00(void){irqList_service( 0);}}
#endif

#ifdef IRQ01
extern "C" {void __ISR( 1, IPL4SOFT)IrqIrq_01(void){irqList_service( 1);}}
#endif

#ifdef IRQ02
extern "C" {void __ISR( 2, IPL4SOFT)IrqIrq_02(void){irqList_service( 2);}}
#endif

#ifdef IRQ03
extern "C" {void __ISR( 3, IPL4SOFT)IrqIrq_03(void){irqList_service( 3);}}
#endif

#ifdef IRQ04
extern "C" {void __ISR( 4, IPL4SOFT)IrqIrq_04(void){irqList_service( 4);}}
#endif

#ifdef IRQ05
extern "C" {void __ISR( 5, IPL4SOFT)IrqIrq_05(void){irqList_service( 5);}}
#endif

#ifdef IRQ06
extern "C" {void __ISR( 6, IPL4SOFT)IrqIrq_06(void){irqList_service( 6);}}
#endif

#ifdef IRQ07
extern "C" {void __ISR( 7, IPL4SOFT)IrqIrq_07(void){irqList_service( 7);}}
#endif

#ifdef IRQ08
extern "C" {void __ISR( 8, IPL4SOFT)IrqIrq_08(void){irqList_service( 8);}}
#endif

#ifdef IRQ09
extern "C" {void __ISR( 9, IPL4SOFT)IrqIrq_09(void){irqList_service( 9);}}
#endif

#ifdef IRQ10
extern "C" {void __ISR(10, IPL4SOFT)IrqIrq_10(void){irqList_service(10);}}
#endif

#ifdef IRQ11
extern "C" {void __ISR(11, IPL4SOFT)IrqIrq_11(void){irqList_service(11);}}
#endif

#ifdef IRQ12
extern "C" {void __ISR(12, IPL4SOFT)IrqIrq_12(void){irqList_service(12);}}
#endif

#ifdef IRQ13
extern "C" {void __ISR(13, IPL4SOFT)IrqIrq_13(void){irqList_service(13);}}
#endif

#ifdef IRQ14
extern "C" {void __ISR(14, IPL4SOFT)IrqIrq_14(void){irqList_service(14);}}
#endif

#ifdef IRQ15
extern "C" {void __ISR(15, IPL4SOFT)IrqIrq_15(void){irqList_service(15);}}
#endif

#ifdef IRQ16
extern "C" {void __ISR(16, IPL4SOFT)IrqIrq_16(void){irqList_service(16);}}
#endif

#ifdef IRQ17
extern "C" {void __ISR(17, IPL4SOFT)IrqIrq_17(void){irqList_service(17);}}
#endif

#ifdef IRQ18
extern "C" {void __ISR(18, IPL4SOFT)IrqIrq_18(void){irqList_service(18);}}
#endif

#ifdef IRQ19
extern "C" {void __ISR(19, IPL4SOFT)IrqIrq_19(void){irqList_service(19);}}
#endif

#ifdef IRQ20
extern "C" {void __ISR(20, IPL4SOFT)IrqIrq_20(void){irqList_service(20);}}
#endif

#ifdef IRQ21
extern "C" {void __ISR(21, IPL4SOFT)IrqIrq_21(void){irqList_service(21);}}
#endif

#ifdef IRQ22
extern "C" {void __ISR(22, IPL4SOFT)IrqIrq_22(void){irqList_service(22);}}
#endif

#ifdef IRQ23
extern "C" {void __ISR(23, IPL4SOFT)IrqIrq_23(void){irqList_service(23);}}
#endif

#ifdef IRQ24
extern "C" {void __ISR(24, IPL4SOFT)IrqIrq_24(void){irqList_service(24);}}
#endif

#ifdef IRQ25
extern "C" {void __ISR(25, IPL4SOFT)IrqIrq_25(void){irqList_service(25);}}
#endif

#ifdef IRQ26
extern "C" {void __ISR(26, IPL4SOFT)IrqIrq_26(void){irqList_service(26);}}
#endif

#ifdef IRQ27
extern "C" {void __ISR(27, IPL4SOFT)IrqIrq_27(void){irqList_service(27);}}
#endif

#ifdef IRQ28
extern "C" {void __ISR(28, IPL4SOFT)IrqIrq_28(void){irqList_service(28);}}
#endif

#ifdef IRQ29
extern "C" {void __ISR(29, IPL4SOFT)IrqIrq_29(void){irqList_service(29);}}
#endif

#ifdef IRQ30
extern "C" {void __ISR(30, IPL4SOFT)IrqIrq_30(void){irqList_service(30);}}
#endif

#ifdef IRQ31
extern "C" {void __ISR(31, IPL4SOFT)IrqIrq_31(void){irqList_service(31);}}
#endif

#ifdef IRQ32
extern "C" {void __ISR(32, IPL4SOFT)IrqIrq_32(void){irqList_service(32);}}
#endif

#ifdef IRQ33
extern "C" {void __ISR(33, IPL4SOFT)IrqIrq_33(void){irqList_service(33);}}
#endif

#ifdef IRQ34
extern "C" {void __ISR(34, IPL4SOFT)IrqIrq_34(void){irqList_service(34);}}
#endif

#ifdef IRQ35
extern "C" {void __ISR(35, IPL4SOFT)IrqIrq_35(void){irqList_service(35);}}
#endif

#ifdef IRQ36
extern "C" {void __ISR(36, IPL4SOFT)IrqIrq_36(void){irqList_service(36);}}
#endif

#ifdef IRQ37
extern "C" {void __ISR(37, IPL4SOFT)IrqIrq_37(void){irqList_service(37);}}
#endif

#ifdef IRQ38
extern "C" {void __ISR(38, IPL4SOFT)IrqIrq_38(void){irqList_service(38);}}
#endif

#ifdef IRQ39
extern "C" {void __ISR(39, IPL4SOFT)IrqIrq_39(void){irqList_service(39);}}
#endif

#ifdef IRQ40
extern "C" {void __ISR(40, IPL4SOFT)IrqIrq_40(void){irqList_service(40);}}
#endif

#ifdef IRQ41
extern "C" {void __ISR(41, IPL4SOFT)IrqIrq_41(void){irqList_service(41);}}
#endif

#ifdef IRQ42
extern "C" {void __ISR(42, IPL4SOFT)IrqIrq_42(void){irqList_service(42);}}
#endif

#ifdef IRQ43
extern "C" {void __ISR(43, IPL4SOFT)IrqIrq_43(void){irqList_service(43);}}
#endif


