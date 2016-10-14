![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Clase Ei`** (External Interrupt)








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

Los objetos de la clase **Ei** gestionan las entradas digitales del 
MCU.
 
Se operan con:

* **Constructores**
	* [**Ei**(EIxx)](#C01)

* **Métodos**
	* [bool **ison**(void)](#M01)
	* [void **onchange**(void (\***call**)(Ei\*))](#M02)
	* [void **onchange**(Callable\* **ocall**,int **hcall**)](#M03)








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Constructores









------------------------------------------------------------------------------
<A name="C01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Ei(EIxx)
```

**Descripción**
> Asocia el objecto a un puerto digital del MCU.

**Parámetros**
>EI*xx*.
>>Donde *xx* es el número de puerto EI a gestionar. 
Para saber qué puertos están disponible en cada MCU, véase 
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
bool ison(void)
```

**Descripción**
>Informa del estado del puerto.

**Parámetros**
>void

**Retorno**
>'true' si el puerto está en on
>'false' sin e puerto está en off

**Ejemplo**
> El siguiente código declara un objeto asociado al puerto Ei 'EI01'.
En cada iteración de *loop*(), comprueba su estado.

```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Ei ei(EI00);

//----------------------------------------------
void
loop(void) {

	if( ei.ison() ) {
		...
		...
		...
		}

	...
	...
	...

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
void onchange(void(*callback)(Ei*))
```

**Descripción**
>Define una funcion de usuario que será llamada cuando el puerto cambie
de estado. Debe tener el formato **void *mi_funcion*(Ei\*)**

**Parámetros**
>void (\***callback**)(Ei\*))
>> Función a llamar cuando el puerto cambie de estado.

**Retorno**
>void


**Ejemplo**
> El siguiente código declara el objeto asociado al puerto digital 'EI01'.
En *main*() definimos la función que será llamada cuando el puerto cambie 
de estado.

```C
//----------------------------------------------
//Includes
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Ei ei(EI01);

//----------------------------------------------
void
on_ei(Ei* obj_ei) {

	//...
	//...

	return;
	}
//----------------------------------------------
int
main(int argc, char** argv) {

	ei.onchange(on_ei);

	while( true ) sleep();

	return 0;
	}

```








------------------------------------------------------------------------------
<A name="M03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void onchange(Callable* objeto, int handle)
```

**Descripción**
>Define el valor del parámetro con el que será llamado el método
void **callback**(int) del objeto al que apunta **Callable\***, que deberá ser 
derivado la clase [Callable](Callable.md) y definir dicho método.

**Parámetros**
>Callable* *objeto*
>> Puntero a *objeto* de la clase (o derivado de) [Callable](Callable.md) (normalmente **this**) 
> 
>int *hadle*
>>Entero que será pasado como parámetro al método **callback**(int) cuando 
se invoque debido al cambio de valor del puerto EI.


**Retorno**
>void


**Ejemplo**
> El siguiente código (divido en los archivos .h y .cpp) declara la clase 
*mi_clase* derivada de [Callable](Callable.md). 
Tiene como miembros dos objetos de la clase **Ei**; uno asociado al puerto 
EI01 y otro asociado al puerto EI02. 
En su constructor se establecen sendos valores de parámetro con el que se 
llamará al método void **callback**(int) en caso de que alguno de los puertos 
cambie de valor.

```C
// ejemplo.h

//----------------------------------------------
//Includes
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"


//----------------------------------------------
class mi_clase : public callable {

	public:

	Ei ei_01(EI01);
	Ei ei_02(EI02);

	//------------------------------
	mi_clase() {
		ei_01.onchange(this,10);
		ei_02.onchange(this,20);
		}

	//------------------------------
	void
	callbakc(int valor) {

		switch(valor) {

			// Ha cambiado el puerto EI01
			case 10:
				//...
				//...
				brack;

			// Ha cambiado el puerto EI02
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
//Código

//----------------------------------------------
void
Loop(void) {

	sleep();

	return;
	}


//----------------------------------------------
void
Setup(void) {

	return;
	}

```







![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)


