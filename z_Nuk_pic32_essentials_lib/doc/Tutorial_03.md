![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### `Tutorial 03` 
#### `Servo`




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
	* Un servo


Aprenderemos el manejo básico de los puertos de salida [Pwm](Pwm.md) utilizando 
las clases de la librería.

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

En este turorial trabajaremos con el contenido de la carpeta **Tutorial_03**. 
Si te resulta más práctico, puedes copiarla donde prefieras.

La estructura de la carpeta es la misma que la de todos los tutoriales. Véase el
[Paso 1 del Tutorial_01](Tutorial_01.md#P01)







------------------------------------------------------------------------------
<A name="P02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

**Paso 2**

En la carpeta *implementation*, dentro de *Tutorial_03*, encontrarás el fichero 
*Servo.cpp*, cuyo contenido es el siguiente:

```C
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
```

Échale una ojeada. Probablemente, por poca experiencia que tengas en 
POO, captarás rápidamente la idea. Sea o no así, por favor, sigue leyendo.

**Nota**
>Se hace la suposición de que el servo funciona con un periodo de 
20 milisegundos y una variación de pulso que va de 0.75 a 2.25 milisegundos.






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

Pwm servo(PWM1);

```

En esta sección del código declaramos 2 objetos: Un puerto analógico y una 
salida Pwm, cada uno de ellos asociado a un pin físico del microcontrolador:

El objeto *potenciometro* va asociado al puerto [Analógio](Analog.md) 
**AN00**. Como se puede comprobar en [Machines.h](Machines.h.md#P01), no es 
el único que podríamos haber elegido.

El objeto *servo* va asociado al puerto [Pwm](Pwm.md) **PWM1**.








------------------------------------------------------------------------------
<A name="E02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
///----------------------------------------------
int
main(int argc, char** argv) {

	servo.set(20000,on_servo);

	while(true) sleep();

	return 0;
	}
```

La sentencia `pwm.set(20000,on_servo)` establece que cada 20 milisegundos 
se ejecutará la función *on_servo()*. También es el ciclo del servo.

La sentencia `while( true ) sleep();` hará que el microcontrolador duerma y 
espere a que el periodo de 20 milisegundos expire.








------------------------------------------------------------------------------
<A name="E02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)
```C
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

```
En la sentencia `int valor_pot = potenciometro.get();` se crea la variable 
*valor* que albergará el valor leído del puerto [Analógico](Analog.md), 
es decir, el valor que corresponde a la posición del potenciometro en ese 
instante. Como se desprende de la guía de referencia, los valores que puede 
tomar un puerto [Analógico](Analog.md) están en el rango de enteros 
(0 .. 1024), proporcionales a los valores en voltaje (0V .. 3,3V).


Si el valor leío varia +-15 puntos con relación al valor leído en la útima
llamada a *on_servo()*, la sentencia *servo.on(750+valor*1.5)* modificará el 
tiempo del pulso, lo que a su vez hará que la posición del servo varíe.


**Nota**
>Se hace la suposición de que el servo funciona con un periodo de 
20 milisegundos y una variación de pulso que va de 0.75 a 2.25 milisegundos.








 ![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)


