![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Clases Serial, Serial_Tx y Serial_Rx`**








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

Los objetos de las clases **Serial**, **Serial_Tx** y **Serial_Rx** gestionan 
las entradas/salidas UART del MCU. 
  
La clase **Serial** es derivada de las clases **Serial_Rx** y **Serial_Tx**, y 
hereda de ellas todos sus métodos.
  
Se operan con:
 
* **Constructores**
	* [**Serial**(UARTx,unsigned int *baud* [, void (\**callback*)(Serial_Rx\*) ] )](#C01)
	* [**Serial_Tx**(UARTx,unsigned int *baud*)](#C02)
	* [**Serial_Rx**(UARTx,unsigned int *baud* [, void (\**callback*)(Serial_Rx\*) ] )](#C03)
* **Métodos**
	* **Serial** y **Serial_Tx**
		* [void **put**(const char* *cadena*)](#M01)
		* [void **put**(char* *cadena*, unsigned int *size*)](#M02)
		* [void **put_char**(char *byte*)](#M03)
		* [void **put_line**(const char* *cadena*)](#M04)
		* [void **put_hex**(const char* *cadena* ,int *size*)](#M05)
	* **Serial** y **Serial_Rx**
		* [int **get**(char* *cadena*)](#G01)
		* [bool **get**(char* *cadena* ,int *size*)](#G02)
		* [char **get_char**()](#G03)
		* [bool **get_line**(char* *cadena*)](#G04)









------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Constructores








------------------------------------------------------------------------------
<A name="C01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Serial(UARTx,unsigned int baud [, void (*callback)(Serial_Rx*) ] )
```

**Descripción**
>Asocia el objecto a un puerto **Serial** del MCU para ser utilizado en 
transmisión y recepción.
 
**Parámetros**
>UARTn ó UARTn_RX,UARTn_TX
>>Donde *n* es el número de puerto **Serial** a gestionar. 
Para saber qué puertos están disponible en cada MCU, véase 
[Machines](Machines.h.md#Machines)

> 
>unsigned int *baud*
>> Velocidad de recepción/transmisión en baudios del puerto.
> 
> void (\**callbak*)(Serial_Rx\*)
>> Opcional. 
Si se define, el objeto llamará a esta función en cuanto esté 
disponible un bytes en la [Fifo](Fifo.md) de la entrada serie (RX).
La función deberá tener la forma **void *mi_funcion* (Serial_Rx\*)**.
 
**Retorno**
>void
 
**Notas**
> Objsérvese que no es posible configurar los parámetros de paridad, bits 
de parada y tramaño del byte, que son, por omisión 1/par/8 respectivamente; 
valores estandar de facto. No obstante, es posible cambiar esta configuración 
a bajo nivel modificando los archivos de la capeta [Machines](Machines.md)
 
**Ejemplo**
> El siguiente código declara un objeto asociado al puerto UART1. La función 
*mi_funcion* será llamada por el objeto *serial* en cuanto se reciba algún 
byte por el puerto.


```C
//Ejemplo.h

//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
void mi_funcion(Serial_Rx*);

```
 
```C
//Ejemplo.cpp

//----------------------------------------------
#include "Ejemplo.h"

//----------------------------------------------
Serial_Tx serial(UART1_TX,500000,mi_funcion);

//----------------------------------------------
void mi_funcion(Serial_Rx*) {

	//...
	//...

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	while(true) sleep();

	return 0;
	}

```








------------------------------------------------------------------------------
<A name="C02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Serial_Tx(UARTTXx,unsigned int baud)
```

**Descripción**
> Asocia el objecto a un puerto **Serial** del MCU para ser utilizado 
solamente en transmisión.
En este caso, sólo estarán disponibles los métodos propios de Tx.
 
**Parámetros**
>UARTn_TX
>>Donde *n* es el número de puerto **Serial** a gestionar. 
Para saber qué puertos están disponible en cada MCU, véase 
[Machines](Machines.h.md#Machines)

> 
>unsigned int *baud*
>> Velocidad de transmisión en baudios del puerto.

**Retorno**
>void








------------------------------------------------------------------------------
<A name="C03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Serial_Rx(UARTRXn,unsigned int baud [, void (*callback)(Serial_Rx\*) ] )
```

**Descripción**
> Asocia el objecto a un puerto **Serial** del MCU para ser utilizado 
solamente en recepción.
En este caso, sólo estarán disponibles los métodos propios de Rx.

**Parámetros**
>UARTn_RX
>>Donde *n* es el número de puerto **Serial** a gestionar. 
Para saber qué puertos están disponible en cada MCU, véase 
[Machines](Machines.h.md#Machines)

> 
>unsigned int *baud*
>> Velocidad de recepción en baudios del puerto.
> 
>  void (\**callback*)(Serial_Rx\*)
>> Opcional. 
Si se define, el objeto llamará a esta función en cuanto se reciba un 
byte por el puerto de entrada serie. 
La función deberá tener la forma **void *mi_funcion* (Serial_Rx\*)**.

**Retorno**
>void







------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Métodos de las clases Serial y Serial_Tx








------------------------------------------------------------------------------
<A name="M01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void put(const char* cadena)
```

**Descripción**
>Transmite la cadena terminada en *NULL* pasada en el parámetro.
 
**Parámetros**
>const char* *cadena*
>> Cadena de bytes terminada en *NULL*.
 
**Retorno**
>void

**Ejemplo 1**
> El siguiente código declara un objeto asociado al puerto UART2_TX.
En cada iteración de *loop()* transmite el mesaje *¡¡¡ Hola mundo !!!*
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"


//----------------------------------------------
Serial_Tx serial(UART2_TX,500000);


//----------------------------------------------
void
loop(void) {

	serial.put(" ¡¡¡ Hola mundo !!! ");

	//...
	//...

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	while(true) loop();

	return 0;
	}

```
 
**Ejemplo 2**
> El siguiente código es el mismo que el del ejemplo anterior; pero utilizando 
los puertos Tx y Rx de UART1
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Serial serial(UART1,500000);

//----------------------------------------------
void
Loop(void) {

	serial.put(" ¡¡¡ Hola mundo !!! ");

	//...
	//...

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	while(true) loop();

	return 0;
	}

```

**Ejemplo 3**
> Lo mismo que en los ejemplos anteriores; pero utilizando los puertos Rx y Tx 
de UART1_RX y UART2_TX respectivamente
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Serial serial(UART1_RX,UART2_TX,500000);

//----------------------------------------------
void
Loop(void) {

	serial.put(" ¡¡¡ Hola mundo !!! ");

	//...
	//...

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	while(true) loop();

	return 0;
	}

```








------------------------------------------------------------------------------
<A name="M02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void put(char* cadena,unsigned int size)
```

**Descripción**
>Transmite el número de byte especificado en *size* de la *cadena*.
 
**Parámetros**
>const char* *cadena*
>> Cadena de bytes.
> 
>unsigned int *size*
>> Número de bytes a transmitir
 
**Retorno**
>void

**Ejemplo 1**
> El siguiente código declara un objeto asociado al puerto UART2_TX. 
En cada iteración de *loop()* transmite el mesaje *¡¡¡ Hola !!!*

```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"


//----------------------------------------------
Serial_Tx serial(UART2_TX,500000);


//----------------------------------------------
void
Loop(void) {

	serial.put(" ¡¡¡ Hola mundo !!! ",9);
	serial.put((char*)(" ¡¡¡ Hola mundo !!! ")+15,5);

	//...
	//...

	return;
	}


//----------------------------------------------
int
main(int argc, char** argv) {

	while(true) loop();

	return 0;
	}

```








------------------------------------------------------------------------------
<A name="M03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void put_char(char byte)
```

**Descripción**
>Transmite el *byte* especificado.

**Parámetros**
>const char *byte*
>> *byte* a trnasmitir.

**Retorno**
>void








------------------------------------------------------------------------------
<A name="M04"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void put_line(const char* cadena)
```

**Descripción**
>Transmite la cadena terminada en cero pasada en el parámetro, y añade a la 
transmisión un byte de fin de linea (EOL).

**Parámetros**
>const char* *cadena*
>> Cadena de byte terminada en 0 (cero).

**Retorno**
>void

**Nota**
> Por omisión el byte *EOL* es 0x0A; sin embargo, puede cambiarse 
modificando la constante definida en el fichero 
[Definitions.h](Definitions.h.md)








------------------------------------------------------------------------------
<A name="M05"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void put_hex(const char* cadena, int size)
```

**Descripción**
>Transmite en formato hexadecimal, tantos bytes como se indique en 
*size*, de la cadena pasada en el parámetro, y añade a la transmisión un 
byte de fin de linea (EOL).

**Parámetros**
>const char* *cadena*
>> Cadena de bytes.
> 
>int size
>> Número de bytes a transmitir.

**Retorno**
>void

**Nota**
> Por omisión el byte de fin de línea es 0x0A. Sin embargo puede cambiarse 
modificando la constante definida en el fichero 
[Definitions.h](Definitions.h.md)








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Métodos de las clases Serial y Serial_RX








------------------------------------------------------------------------------
<A name="G01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
int get(const char* cadena)
```

**Descripción**
>Lee de todos los bytes pendientes.

**Parámetros**
>const char* *cadena*
>> *Cadena* donde se depositarán los bytes leídos, más un byte *NULL*.

**Retorno**
>int size
>> Cantidad de bytes leídos de la **Fifo**.

**Nota**
>Es resposabilidad del programador que la *cadena* disponga del tamaño 
suficiente para albergar los bytes recibidos. 

**Ejemplo**
> El siguiente código declara un objeto asociado al puerto UART2. 
En cada iteración de *loop*()se leen los bytes recibidos por el puerto.

```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

----------------------------------------------
Serial_Tx serial(UART2,500000);

//----------------------------------------------
void
loop(void) {

	char* entrada[BUFF_SIZE];
	int leidos;

	if( (leidos = serial.get(entrada)) ){
			{
			//...
			//...
			}

	//...
	//...

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	while(true) loop();

	return 0;
	}

```








------------------------------------------------------------------------------
<A name="G02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
bool get(const char* cadena, int size)
```

**Descripción**
>Si se han recibido, lee tantos bytes como los especificados en *size*.

**Parámetros**
>const char* *cadena*
>> Puntero a la *cadena* que deberá tener, como mínimo, *size* bytes de espacio.

> int *size*
>> Cantidad de bytes a extraer.

**Retorno**
>bool
>> **true** Habian suficientes bytes. La cadena ha sido completada.
>>
>> **false** No hay suficientes bytes. El contenido de la cadena es invalido.

>**Ejemplo**
>> El siguiente código declara un objeto asociado al puerto UART2. 
En cada iteración de *loop*() se leen tres bytes recibidos por el puerto.

```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Serial_Tx serial(UART1,500000);

//----------------------------------------------
void
poop(void) {

	char* entrada[4];

	// Leemos tres bytes, si los hay
	if( serial.get(entrada,3) ){
			{
			//...
			//...
			}

	//...
	//...

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	while(true) loop();

	return 0;
	}

```








-------------------------------------------------------------------------------
<A name="G03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
char get_char()
```

>**Descripción**
>>Si se ha recibido, lee un byte.

>**Parámetros**
>>void

>**Retorno**
>>char
>>> Si lo hay, el byte leido.
>>> Si no lo hay 0 (cero).

>**Ejemplo**
>> El siguiente código declara un objeto asociado al puerto UART2. 
En cada iteración de *loop*() se lee un byte recibido por el puerto.

```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Serial_Tx serial(UART1,500000);

//----------------------------------------------
void
loop(void) {

	char entrada;

	// Esperamos a recibir 1 byte
	while( !(entrada = serial.get_char()) );

	//...
	//...

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	while(true) loop();

	return 0;
	}
```








------------------------------------------------------------------------------
<A name="G04"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
bool get_line(char* cadena)
```

**Descripción**
>Lee los bytes pendientes hasta encontrar un final de linea (*EOL*). 
Si entre los bytes recibidos no aparace *EOL*, la función devuelve
**false** y el contenido de la *cadena* será invalido.

**Parámetros**
>char* cadena
>>Cadena receptora de los bytes. En la cadena, *EOL* será sustituido por 
*NULL*.

**Retorno**
>bool
>> **true** si se ha leído algún byte.
>>
>> **false** en caso contrario.

**Nota**
> Observa que, aun cuando pudieran haber bytes pendientes, 
estos no serán devueltos por el método si no se ha encontrado un *EOL*.

**Ejemplo**
> El siguiente código declara un objeto asociado al puerto UART1. 
En cada iteración se lee una línea recibida por el puerto.

```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"


//----------------------------------------------
Serial_Tx serial(UART1,500000);


//----------------------------------------------
void
loop(void) {

	char* entrada[BUFF_SIZE];

	while( !serial.get_line(entrada) );

	//...
	//...

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	while(true) loop();

	return 0;
	}

```





![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)

