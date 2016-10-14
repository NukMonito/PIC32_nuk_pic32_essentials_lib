// ****************************************************************************
// File:  Fifo.cpp
// Autor: Lluis
// Descripcio
//      Implemantacio de la clase Fifo
//




// ****************************************************************************
// Espai
//
using namespace std;




// ****************************************************************************
// Includes
//
#include "Fifo.h"




// ****************************************************************************
// Implementacio de la clase Fifo
//

// ----------------------------------------------------------------------------
Fifo::~Fifo() {
	/*
	DESTRUCTOR
		Destructor
	*/

	}


// ----------------------------------------------------------------------------
Fifo::Fifo() {
	/*
	CONSTRUCTOR

	PARMETRES:
		void
	*/
	
	// Inicialitzem el buffer
	pin = 0;
	pout = 0;

	// Init Nuk_pic_essentials
	nuk_pic_essentials();
    
	}


// ----------------------------------------------------------------------------
int
Fifo::get(char* r) {
	/*
	FUNCIO:
		Reb una cadena
		Retorna el contingut pendent de 'buff'

	PARAMETRES:
		char* r
			Punter a la cadena a llegir

	RETORN:
		char* r (en el parametre)
			Cadena emplenada
			Si no hi ha res, retorna la cadena vuida (r[0] = 0)
	 
		int
			Nombre de caracters llegits
	*/

	// Preparem el retorn.
	r[0] = 0;
	int n = 0;

	// Traspasem el buff a la cadena de retorn
	while( (pout!=pin) && (n!=BUFF_SIZE) ) {
		r[n] = buff[pout];
		pout++;
		if( pout==BUFF_SIZE ) pout = 0;
		n++;
		}

	r[n] = 0;

	return n;
	}


// ----------------------------------------------------------------------------
bool
Fifo::get(char* r, int size) {
	/*
	FUNCIO:
		Retorna 'size' bytes del 'buff' de la FIFO desde 'pout'.
		Si no hi son els caracters especificats per 'size',
		retorna 'false' (amb la cadena 'r[0]=0') i deixa 'buff' intacte.

	PARAMETRES:
		char* r
			Punter a la cadena a llegir

		int size
			Caracters a llegir

	RETORN:
		char* r (en el parametre)
			Cadena emplenada
			Si no hi ha res, retorna la cadena vuida (r[0] = 0)
	 
		bool
			==True si s'han llegit tans caracters com els especificats
			en parametre 'size'
	*/

    
	// Preparem el retorn.
	// 'r' Tindra la cadena llegida
	// 'bbytes' sera true si em trobat els bytes esperats
	int n = 0;
	r[0] = 0;
	bool bbytes = false;

	// Traspasem el buff a la cadena de retorn
	if( pout!=pin ) {

		// Memoritzem 'pout' per restaurar-lo en el cas de que no trobem
		// els caracters esperats
		int mpout = pout;
  
		// Llegim el buffer
		do {
			r[n] = buff[mpout];
			mpout++;
			if( mpout==BUFF_SIZE ) mpout = 0;
			} while( (++n<size) && (mpout!=pin) );

		// Si hem llegit tans caractes com 'size',
		// ajustem el punter de lectura 'pout'
		if( n==size ) {
			pout = mpout;
			bbytes = true;
			}

		// Si no em trobat 'size' caracters, descartem la lectura
		else r[0] = 0;
		}

	return bbytes;
	}


// ----------------------------------------------------------------------------
char
Fifo::get_char() {
	/*
	FUNCIO:
		Retorna un caracter de 'Serial.buff' apuntat per 'pout'
		Si 'pout' i 'pin' son iguals, retorna '\0'

	PARAMETRES:
		void

	RETORN:
		char
			caracter rebut
			Si no hi ha, retorna 0
	*/
    
	// Preparem el retorn. Caracter rebut
	char r = 0;

	// Llegim el buffer
	if( pout!=pin ) {
		r = buff[pout];
		pout++;
		if( pout==BUFF_SIZE ) pout = 0;
		}

	return r;
	}


// ----------------------------------------------------------------------------
bool
Fifo::get_line(char* r) {
	/*
	FUNCIO:
		Retorna el contingut del 'buffer' de la FIFO desde 'pout' fins
		que troba el caracter EOL. Si no troba EOL, retorna una
		cadena nula i el buffer queda intacte

	PARAMETRES:
		char* r
			Punter a la cadena a llegir

	RETORN:
		char* r (en el parametre)
			Cadena emplenada
			Si no hi ha res, retorna la cadena vuida (r[0] = 0)
	 
		int
			Nombre de caracters llegits
	*/

	// Preparem el retorn.
	// 'r' Tindra la cadena llegida
	// 'bline' sera true si em trobat EOL
	int n = 0;
	r[0] = 0;
	bool bline = false;

	// Traspasem el buff a la cadena de retorn
	if( pout!=pin ) {

		// Memoritzem 'pout' per restaurar-lo en el cas de que no trobem EOL
		int mpout = pout;

		// Llegim el buffer
		n = -1;
		do {
			n++;
			r[n] = buff[mpout];
			mpout++;
			if( mpout==BUFF_SIZE ) mpout = 0;
			} while(
				(mpout!=pin) &&
				(n!=BUFF_SIZE-1) &&
				(r[n]!=EOL) );
            
		// Si hem trobat un final de linia EOL, el marquem com 0x00
		// i ajustem el punter de lectura 'pout'
		if( r[n]==EOL ) {
			r[n] = 0;
			pout = mpout;
			bline = true;
			}
        
		// Si no em trobat un EOL, descartem la lectura
		else {
			r[0] = 0;
			n = 0;
			}
		}

	return bline;
	}


// ----------------------------------------------------------------------------
void
Fifo::insert(char byte) {
	/*
	FUNCIO
		Inserta el caracter a la FIFO

	PARAMETRES
		char byte
			Caracter a insertar
	*/

	//Mentre hagin caracters per llegir
	buff[pin] = byte;
	pin++;
	if( pin==BUFF_SIZE ) pin = 0;
	if( pin==pout ) {
		pin--;
		if( pin<0 ) pin = BUFF_SIZE-1;
		}

	return;
	}


// ----------------------------------------------------------------------------
void
Fifo::insert(const char* cadena) {
	/*
	FUNCIO
		Inserta caracters de la cadena acabada en NULL a la FIFO
		El NULL no s'inserta a la FIFO

	PARAMETRES
		char* cadena
			Cadena a insertar

	NOTA
		El NULL no s'inserta a la FIFO
	*/

	//Mentre hagin caracters per llegir
	int i = 0;
	while( cadena[i]!=0 ) {
		buff[pin] = cadena[i];
		pin++;
		if( pin==BUFF_SIZE ) pin = 0;
		if( pin==pout ) {
			pin--;
			if( pin<0 ) pin = BUFF_SIZE-1;
			}
		i++;
		}

	return;
	}


// ----------------------------------------------------------------------------
void
Fifo::insert(const char* cadena,int len) {
	/*
	FUNCIO
		Inserta 'len' caracters de la 'cadena' a la FIFO

	PARAMETRES
		char* cadena
			Caracters a insertar

		int len
			Nombre de caracters a insernar
	*/

	//Mentre hagin caracters per llegir
	int i = 0;
	while( i<len ) {
		buff[pin] = cadena[i];
		pin++;
		if( pin==BUFF_SIZE ) pin = 0;
		if( pin==pout ) {
			pin--;
			if( pin<0 ) pin = BUFF_SIZE-1;
			}
		i++;
		}

	return;
	}


// ----------------------------------------------------------------------------
void
Fifo::insert_line(const char* cadena) {
	/*
	FUNCIO
		Inserta caracters de la cadena acabada en NULL a la FIFO
		El NULL no s'inserta
		Afegeix un EOL a la FIFO

	PARAMETRES
		char* cadena
			Cadena a insertar
	*/

	insert(cadena);
	insert(EOL);

	return;
	}






