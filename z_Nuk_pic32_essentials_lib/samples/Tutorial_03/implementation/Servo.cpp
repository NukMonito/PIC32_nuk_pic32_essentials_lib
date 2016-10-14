//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Analog potenciometro(AN00);

Pwm servo(PWM1);

//----------------------------------------------
void
on_servo(Pwm*) {

	static int valor_ant = 0;

	int valor = potenciometro.get();

	if( valor>valor_ant+15 || valor<valor_ant-15) {
		valor_ant = valor;
		servo.on(750+valor*1.5);
		}
	
	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	servo.set(20000,on_servo);

	while(true) sleep();

	return 0;
	}
