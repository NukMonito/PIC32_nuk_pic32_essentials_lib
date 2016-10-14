<A name="TOP"></A>
![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Clase Digital`**




------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

Los objetos de la clase **Digital** gestionan las entradas/salidas digitales 
del MCU.
 
Se operan con:
 
* **Constructores**
	* [**Digital**(Daxx)](#C01)
* **Métodos**
	* [void **input**(void)](#M01)
	* [void **on**(void)](#M02)
	* [void **open**(void)](#M03)
	* [void **off**(void)](#M04)
	* [void **close**(void)](#M05)
	* [void **inv**(void)](#M06)
	* [bool **ison**(void)](#M07)
	* [bool **ispullup**(void)](#M08)
	* [void **onchange**(void (\**callback*)(Digital* *object*))](#M09)
	* [void **onchange**(Callable\* *ocall*,int *hcall*)](#M10)








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Constructores








------------------------------------------------------------------------------
<A name="C01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Digital(Daxx)
```

**Descripción**
> Asocia el objecto a un puerto digital del MCU
 
**Parámetros**
>D*axx*.
>>Donde *a* es el registro del puerto (A,B y C)
>>Y *xx* es el número de puerto digital a gestionar.
>>Para saber qué puertos están disponible en cada MCU, véase 
[Machines](Machines.h.md#Machines)
 
**Retorno**
>void








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Métodos









------------------------------------------------------------------------------
<A name="M01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void input(void)
```

**Descripción**
>Convierte el pin en entrada digital.
 
**Parámetros** 
>void
 
**Retorno**
>void
 
**Ejemplo**
> El siguiente código declara un objeto asociado al puerto digital 'DA00'.
En *main*() convertimos el puerto en entrada digital.
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"


//----------------------------------------------
Digital digital(DA00);



//----------------------------------------------
void
loop(void) {

	//...
	//...

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	digital.input();

	while(true) loop();

	return 0;
	}

```








------------------------------------------------------------------------------
<A name="M02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void on(void)
```

**Descripción**
>Pone a 1 el puerto en modo salida pull up.
 
**Parámetros**
>void
 
**Retorno**
>void
 
**Ejemplo**
> El siguiente código declara un  objeto asociado al puerto digital 'DA00'.
En *loop*() encendemos el puerto.
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Digital digital(DA00);

//----------------------------------------------
void
loop(void) {

	digital.on();
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
void open(void)
```

**Descripción**
>Pone a 1 el puerto en modo salida open drain. Es decir desconecta el puerto de 
masa.
 
**Parámetros**
>void
 
**Retorno**
>void
 
**Ejemplo**
> El siguiente código declara un objeto asociado al puerto digital 'DA00'.
En *loop*() desconectamos el puerto de masa.
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"


//----------------------------------------------
Digital digital(DA00);

//----------------------------------------------
void
loop(void) {

	digital.open();
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
<A name="M04"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void off(void)
```

**Descripción**
>Pone a 0 el puerto en modo salida pull up.
 
**Parámetros**
>void
 
**Retorno**
>void
 
**Ejemplo**
> El siguiente código declara un objeto asociado al puerto digital 'DA00'.
En *loop*() apagamos el puerto.
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Digital digital(DA00);

//----------------------------------------------
void
loop(void) {

	digital.off();
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
<A name="M05"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void close(void)
```

**Descripción**
>Pone a 0 el puerto en modo salida open drain. Es decir conecta el puerto 
a masa.
 
**Parámetros**
>void
 
**Retorno**
>void
 
**Ejemplo**
> El siguiente código declara un objeto asociado al puerto digital 'DA00'. 
En *loop*() conectamos el puerto a masa.
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Digital digital(DA00);

//----------------------------------------------
void
loop(void) {

	digital.close();
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
<A name="M06"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void inv(void)
```

**Descripción**
>Cambia la polaridad del puerto. Si el puerto no era digital, lo convierte a
digital en modo salida pull up y lo pone a on.
 
**Parámetros**
>void
 
**Retorno**
>void
 
**Ejemplo**
> El siguiente código declara un objeto asociado al puerto digital 'DA00'.
En cada iteración de *loop*() el puerto cambará de polaridad.
 
```C
//----------------------------------------------
Digital digital(DA00);

//----------------------------------------------
void
loop(void) {

	digital.inv();
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
<A name="M07"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
bool ison(void)
```

**Descripción**
>Informa del estado del puerto.
 
**Parámetros**
>void
 
**Retorno**
>**true** si el pin está en on
> 
>**false** si el pin está en off
 
**Ejemplo**
> El siguiente código declara un objeto asociado al puerto digital 'DA00'.
En cada iteración de *loop*() se comprueba su estado.
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Digital digital(DA00);


//----------------------------------------------
void
loop(void) {

	if( digital.ison() ) {
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
<A name="M08"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
bool ispullup(void)
```

**Descripción**
>Informa de la configuración del puerto.
 
**Parámetros**
>void
 
**Retorno**
>**true** si el pin está configurado como pull up
> 
>**false** si el pin está configurado como open drain








------------------------------------------------------------------------------
<A name="M09"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void onchange(void (*callback)(Digital* object))
```

**Descripción**
>Define una funcion de usuario que será llamada cuando el puerto cambie
de estado.
 
**Parámetros**
>void (\**callback*)(Digital\* *object*))
>> Función a llamar cuando el puerto cambie de estado. Tiene la forma 
void *funcion_de_callback*(Digital\* *object*).
 
**Retorno**
>void
 
**Ejemplo**
> El siguiente código declara dos objetos asociados a los puertos digitales 
'DA00' y 'DA01'.
En *main*() definimos la función que será llamada cuando algún puerto cambie 
de estado.
Por supuesto, podría definirse una función distinta para cada 
objeto.
 
```C
//----------------------------------------------
//Includes
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"


//----------------------------------------------
//Declaracion de funciones de callback
void on_digital(Digital*);

//----------------------------------------------
//Objetos globales
Digital digital0(DA00);
Digital digital1(DA01);

//----------------------------------------------
//Codigo

//----------------------------------------------
void
on_digital(Digital* dig) {

	if( dig==&digital0 ) {
		//...
		//...
		}
	else {
		//...
		//...
		}

	retrun();
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	digital0.onchange(on_digital);
	digital1.onchange(on_digital);

	while(true) sleep();

	return 0;
	}

```








------------------------------------------------------------------------------
<A name="M10"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void onchange(Callable*,int)
```

**Descripción**
>Define el valor del parámetro con el que será llamado el método
void **callback**(int) del objeto al que apunta **Callable\***, que deberá ser 
derivado la clase [Callable](Callable.md) e implementar dicho método.
 
**Parámetros**
>*Callable*\*
>> Puntero a objeto (normalmente **this**) 
> 
>int
>>Entero que será pasado como parámetro a la función void **callback**(int) 
cuando se invoque debido al cambio de valor del puerto digital.
 
**Retorno**
>void


**Ejemplo**
> El siguiente código declara la clase *mi_clase* derivada de 
[Callable](Callable.md). Tiene como miembros dos objetos de la clase
 **Digital**; uno asociado al puerto 'DA00' y otro asociado al puerto 'DA01'. 
En su constructor se establecen sendos valores de parámetro con el que se 
llamará al método void **callback**(int) en caso de que alguno de los puertos 
cambie de valor. Nótese que en *main*() lo único que hace es dormir.
 
```C
// ejemplo.h

//----------------------------------------------
//Includes
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"


//----------------------------------------------
class mi_clase : public callable {

	public:

	Digital digi_00(DA00);
	Digital digi_01(DA01);

	//------------------------------
	mi_clase() {
		digi_00.onchange(this,10);
		digi_01.onchange(this,20);
		}

	//------------------------------
	void
	callbakc(int valor) {

		switch(valor) {

			// Ha cambiado el puerto DA00
			case 10:
				//...
				//...
				brack;

			// Ha cambiado el puerto DA01
			case 20:
				//...
				//...
				brack;

			default:
				breack
			}
		return;
		}
	}
```

```C
// ejemplo.cpp

//----------------------------------------------
//Includes
#include "ejemplo.h"

//----------------------------------------------
// Objetos globales
mi_calse mi_objeto;

//----------------------------------------------
int
main(int argc, char** argv) {

	while (true) sleep();

	return 0;
	}

```







------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)



