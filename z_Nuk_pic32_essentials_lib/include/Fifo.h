// ****************************************************************************
// File:  Fifo.h
// Autor: Lluis
// Descripcio
//      Declaracio de la clase Fifo
//




// ****************************************************************************
// Includes
//
#include "Nuk_pic32_essentials.h"

#ifndef NUK_PIC_ESSENTIALS_FIFO
#define NUK_PIC_ESSENTIALS_FIFO




// ****************************************************************************
// Declaracio de la clase Fifo
//
class Fifo {

	public:

    // buffer
    char buff[BUFF_SIZE];
    
    // Proxim caracter a intertar
    int pin;
    
    // Proxim caracter a treure si != a pout
    int pout;

	// Destructor
	~Fifo();
    
	// Constructors
	Fifo();

	// Funcions
	int	get(char*);
	bool	get(char*,int);
	char	get_char();
	bool	get_line(char*);
   void	insert(char);
   void	insert(const char*);
   void	insert(const char*,int);
	void	insert_line(const char*);
	};
    
    

   
#endif // NUK_PIC_ESSENTIALS_FIFO


