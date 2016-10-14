//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Serial serial(UART2,19200);


//----------------------------------------------
void
loop(void) {

	char texto[256];

	serial.put("Introduce un texto: ");
	while( !serial.get_line(texto) );
	serial.put("El texto introducido es ");
	serial.put_line(texto);

	return;
	}

// ---------------------------------------------
int
main(int argc, char** argv) {

	serial.put_line("¡Hola mundo!");

	while(true)	loop();

	return 0;
	}
