![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### `Tutorial 01` 
#### `¡Hola mundo!`




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

Empezaremos diseñando un pequeño proyecto al que llamaremos (cómo no) 
**hola_mundo**. Para trabajar necesitaremos:

* Software y Harware del fabricante del microcontrolador .
	* Compilador C++
	* IPE Integrated Programming Environment
	* Microcontrolador
	* Un grabador apropiado del microcontrolador 
* Software adicional
	* Editor de texto plano
	* Emulador de terminal
* Hardware adicional
	* Un adaptador USB a puerto serie. 

Aprenderemos a comunicarnos con el microcontrador a través del 
puerto serie. Algo muy útil, que nos facilitará mucho la vida, si no queremos 
hacer las cosas a ciegas.


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

En la carpeta donde se archivó la librería, en 
*../z_Nuk_pic_essentials_lib/samples*, se encontrarán todos los tutoriales. 
Para trabajar cómodamente, y no perderse en la profundidad de 
muchas subcarpetas, pueden copiarse en otra carpeta más próxima a la raíz 
del disco.

Cada tutorial tiene la estructura básica de carpetas:

* **Tutorial_nn**
	* **bin** Ejecutables de MCU
	* **implementation** Normalmente los ficheros de código con extensión *.c* o *.cpp*
	* **includes** Normalmente los ficheros de código con extensión *.h* o *.hpp*
	* **make** Scripts para compilar el código.

Ésta cubre suficientemente los propósitos del aprendizaje. Por supuesto, es 
posible crear una a tu gusto, con tu estilo, y que se adapte de forma precisa 
a los objetivos de cada uno de tus proyectos.

En este turorial trabajaremos con el contenido de la carpeta **Tutorial_01**







------------------------------------------------------------------------------
<A name="P02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

**Paso 2**

En la carpeta *implementation*, dentro de *Tutorial_01*, encontrarás el fichero 
*Hola_mundo.cpp*, cuyo contenido es el siguiente:

```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Serial serial(UART2,500000);


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

	while( true ) loop();

	return 0;
	}
```

Échale una ojeada. Probablemente, por poca experiencia que tengas en 
POO, captarás rápidamente la idea. Sea o no así, por favor, sigue leyendo.








------------------------------------------------------------------------------
<A name="P03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

**Paso 3**

Abre el explorador de carpetas.

Sitúate en la capeta *Tutorial_01*

Pincha con el `boton_derecho` en un área libre y elige la opción 
`abre un terminal`

Ejecuta el comando:

```
make/compile.sh -p -p -p
```

Aparecerá una ventana en la que debemos elegir un *procesador*.

Seguidamente aparacerá una ventana en la que deberemos elegir la carpeta 
donde se encuentran las librerías (Atención! no la carpeta de la libreria, 
sino la carpeta que la contiene).

Finalmente aparecerá una ventana donde debemos elegir el códgo fuente 
*Hola_Mundo.cpp* que está en *Turorial_01/implementation*

Si todo va bien, se habrá creado en *Turorial_01/bin* el fichero 
*Hola_munto.cpp.hex*, que es el ejecutable a cargar en el microcontrolador.

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
#include "Config_40.h"
```
En esta línea incluimos el fichero de configuración para que la librería y el 
MCU funcionen. En especial determina la velocidad del reloj interno del MCU. 
En este tutorial hemos elegido trabajar a 40MHz

La distrubución viene con los siguientes
* Config_08.h ____ 8MHz
* Config_10.h ____ 10MHz
* Config_20.h ____ 0MHz
* Config_40.h ____ 40MHz

Aunque puden confecionarse otros. Véase [Config_xx.h](Config_xx.h.md)








------------------------------------------------------------------------------
<A name="E02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
#include "Nuk_pic32_essentials.h"
```
Icluimos la librería.







------------------------------------------------------------------------------
<A name="E03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Serial serial(UART2,500000);
```
Con este constructor de la clase [Serial](Serial.md) creamos el objeto *serial*. 
En los parámetros establecemos qué puerto serie y a qué velocidad en baudios 
será manejado por el objeto. En este tutorial hemos elegido el puerto UART2 a 
500 Kbps.

Véanse los constructores disponibles en [Serial](Serial.md)







------------------------------------------------------------------------------
<A name="E04"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
serial.put("Introduce un texto: ");
```
El método **put** del objeto *serial* de la clase [Serial](Serial.md) envía 
el texto por el puerto serie.








------------------------------------------------------------------------------
<A name="E05"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
while( !serial.get_line(texto) );
```
El método **get_line** del objeto *serial* de la clase [Serial](Serial.md) 
recibe información por el puerto serie. La instrucción *while* detendrá el 
curso del programa hasta que se haya completado una línea.






------------------------------------------------------------------------------
<A name="E06"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
serial.put_line(texto);
```
El método **put_line** del objeto *serial* de la clase [Serial](Serial.md) envía 
el texto por el puerto serie y una marca de fin de línea (EOL).







------------------------------------------------------------------------------
<A name="E07"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

El comando:
```C
make/compile.sh -p -p -p
```
Realiza las tareas:
* Compilar las librerias para el procesador elegido.
* Buscar los ficheros para las directivas #include.
* Compilar nuestro código.
* Lincarlo todo.

Su sintaxis es:
```C
# compile.sh mprocessor lib_directori source
#
# where
#
# mprocessor 
#   The name of the processor target ( like 32MX170F226B )
#   if -p dialog apairs
#
# lib_dir
#   The direcctori where you have the libraries
#   if -p dialog apairs
#
# source
#   The name of your C source code
#   if -p dialog apairs
```

Podríamos haber escrito, por ejemplo:
```C
make/compile.sh 32MX170F256B $HOME/my_libs_pic32/Nuk_pic32_libs implementation/Hola_Mundo.cpp
```

**Nota**
>Como habrás observado, el script informa de las opciones que usa para realizar 
el compilado y el lincado. Con esta información y un vistazo al código del 
script, no dudo que sabrás crear uno que cubra mejor tus necesidades.





 ![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)


