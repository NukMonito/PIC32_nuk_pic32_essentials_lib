![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### `Tutorial 02` 
#### `De analógico a digital en poco tiempo`




------------------------------------------------------------------------------
<A name="I00"></A>
![separa](img/Nuk-separa.jpg)
### Indice




------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)


* [Introducción](#I00)
	* Donde se establecen los requerimiento previos y los objetivos.
* [Procedimiento](#P00)
	* Donde de explican los pasos a seguir para que el tutorial, como proyecto,
funcione.
* [Explicación detallada](#E00)
	* Donde se da una explicación detallada de los aspectos en los que se 
quiere hacer hincapié y que son objeto del tutorial.








------------------------------------------------------------------------------
<A name="I00"></A>
![separa](img/Nuk-separa.jpg)
### Introducción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

Para este proyecto es necesario:

* Software y Harware del fabricante del microcontrolador .
	* Compilador C++
	* IPE Integrated Programming Environment
	* Microcontrolador
	* Un grabador apropiado del microcontrolador 
* Software adicional
	* Editor de texto plano
* Hardware adicional
	* Un potenciómetro.
	* 4 leds.
	* 4 resistencias de 150 ohmios.

Aprenderemos el manejo básio de los puertos de entrada/salida 
[Digitales](Digital.md), el de los puertos de entrada [Analógica](Analog.md) y 
del módulo [Timer](Timer.md). Todo ello utilizando las clases de la librería.

**Notas**
>En ningún tutorial se hace la suposición de que el desarrollador utiliza un 
IDE determinado, ya que la elección de uno es un asunto personal (o corporativo). 
Si éste es el caso, se entenderá que se sabrán hacer las correcciones 
necesarias a las explicaciones para adaptarlas a cada preferencias.








------------------------------------------------------------------------------
<A name="P00"></A>
![separa](img/Nuk-separa.jpg)
### Procedimiento







------------------------------------------------------------------------------
<A name="P01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

**Paso 1**

En este turorial trabajaremos con el contenido de la carpeta **Tutorial_02**. 
Si te resulta más práctico, puedes copiarla donde prefieras.

La estructura de la carpeta es la misma que la de todos los tutoriares. Véase el
[Paso 1 del Tutorial_01](Tutorial_01.md#P01)







------------------------------------------------------------------------------
<A name="P02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

**Paso 2**

En la carpeta *implementation*, dentro de *Tutorial_02*, encontrarás el fichero 
*Analogio_Digital.cpp*, cuyo contenido es el siguiente:

```C
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
```

Échale una ojeada. Probablemente, por poca experiencia que tengas en 
POO, captarás rápidamente la idea. Sea o no así, por favor, sigue leyendo.

**Nota**
>El código está escrito para que los leds funcionen con una configuración física 
en modo pull up. Al final del tutorial se da un ejemplo de cómo hacerlo para 
que funcionen con una configuración en modo open drain.






------------------------------------------------------------------------------
<A name="P03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

**Paso 3**

Compilaremos y lincaremos el programa. Es un proceso análogo al descrito en 
el [Paso 3 del Tutorial_01](Tutorial_01.md#P03). Véase también 
[make/compile.sh -p -p -p](Tutorial_01.md#E07) del mismo tutorial.

La asignación de puertos y pines del microcontrolador puede verse en 
[Machines.h](Machines.h.md#P01)








------------------------------------------------------------------------------
<A name="E00"></A>
![separa](img/Nuk-separa.jpg)
### Explicación detallada








------------------------------------------------------------------------------
<A name="E01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
//----------------------------------------------
Analog potenciometro(AN00);

Digital led_1(DA01);
Digital led_2(DB00);
Digital led_3(DB01);
Digital led_4(DB02);

Timer reloj(TIMER1);
```

En esta sección del código declaramos 7 objetos: Un puerto analógico, cuatro 
digitales y un temporizador, cada uno de ellos asociado a un módulo y/o pin 
físico del microcontrolador:

El objeto *potenciometro* va asociado al puerto [Analógio](Analog.md) 
**AN00**. Como se puede comprobar en [Machines.h](Machines.h.md#P01), no es 
el único que podríamos haber elegido.

Los cuatro objetos *led_n* de la clase [Digital](Digital.md) van asociados, 
respectivamente por su número, a los puertos digitales **DA01**, **DB00**, 
**DB01** y **DB02**; esta asociación es arbitraria y en absoluto obligada. 
En [Machines.h](Machines.h.md#P01) pueden verse los puertos que están 
disponibles.

Por último, el objeto *reloj* de la clase [Timer](Timer.md) va asociado al 
módulo **TIMER1** del microcontralador.








------------------------------------------------------------------------------
<A name="E02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
// ---------------------------------------------
int
main(int argc, char** argv) {

	reloj.every(100000,on_timer);

	while( true ) sleep();

	return 0;
	}
```

La sentencia `reloj.every(100000,on_timer);` establece que cada 100 milisegundos 
se ejecutará la función *on_timer()*.

La sentencia `while( true ) sleep();` hará que el microcontrolador duerma y 
espere a que el periodo de 100 milisegundos expire.








------------------------------------------------------------------------------
<A name="E02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)
```C
//----------------------------------------------
void
on_timer(Timer&) {

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
```
Cada vez que se ejecute la función *on_timer()* el *led_1* cambiará de estado. 
el efecto será, por tanto, un parpadeo continuo.

En la sentencia `int valor_pot = potenciometro.get();` se crea la variable 
*valor_pot* que albergará el valor leído del puerto [Analógico](Analog.md), 
es decir, el valor que corresponde a la posición del potenciometro en ese 
instante. Como se desprende de la guía de referencia, los valores que puede 
tomar un puerto [Analógico](Analog.md) están en el rango de enteros 
(0 .. 1024), proporcionales a los valores en voltaje (0V .. 3,3V). En función 
de ese valor,*led_1*, *led_2* y *led_3* se encenderán y apagaran secuencialmente.


**Nota**
>El código está escrito para que los leds funcionen con una configuración 
física en pull up. Podemos reescribirlo para una configuración en 
open drain. Obsérvese que en *main()* se ha inluído la sentencia ` led1.open()`;
de no hacerlo, el puerto quedaría configurado en modo pull up.

```C
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
void
on_timer(Timer&) {

	led_1.inv();

	int valor_pot = potenciometro.get();

	if( valor_pot<256 ) led_2.open();
	else led_2.close();

	if( valor_pot<512 ) led_3.open();
	else led_3.close();

	if( valor_pot<768 ) led_4.open();
	else led_4.close();

	return;
	}

// ---------------------------------------------
int
main(int argc, char** argv) {

	led1.open();

	reloj.every(100000,on_timer);

	while( true ) sleep();

	return 0;
	}
```





 ![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)


