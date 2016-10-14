//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Analog potenciometro(AN00);

Digital led_1(DA01);
Digital led_2(DB00);
Digital led_3(DB01);
Digital led_4(DB02);

Timer reloj(TIMER1);

//----------------------------------------------
void
on_timer(Timer*) {

	led_1.inv();

	int valor_pot = potenciometro.get();

	if( valor_pot<256 ) led_2.off();
	else led_2.on();

	if( valor_pot<512 ) led_3.off();
	else led_3.on();

	if( valor_pot<768 ) led_4.off();
	else led_4.on();

	return;
	}

// ---------------------------------------------
int
main(int argc, char** argv) {

	reloj.every(100000,on_timer);

	while( true ) sleep();

	return 0;
	}
