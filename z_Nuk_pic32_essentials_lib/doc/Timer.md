![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Clase Timer`**








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

Los objetos de la clase **Timer** gestionan timers del MCU. 
 
Se operan con:
* **Constructores**
	* [**Timer**(TIMER*n*)](#C01)
* **Métodos**
	* [void **delay**(unsigned int *time*)](#M01)
	* [bool **every**(unsigned int *periode*, void (\**callback*)(Timer\* *object*))](#M02)
	* [bool **every**(unsigned int *periode*, Callable\* *object*, int *handle*)](#M03)
	* [void **on**(void)](#M04)
	* [void **off**(void)](#M05)








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Constructores








------------------------------------------------------------------------------
<A name="C01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Timer(TIMERn)
```

**Descripción**
> Asocia el objecto a un **timer** del MCU.

**Parámetros**
>TIMER*n*.
>>Donde *n* es el número de **timer** a gestionar. Puede ser:
>>
>>* 16 Bits
>>	* TIMER1
>>	* TIMER2
>>	* TIMER3
>>	* TIMER4
>>	* TIMER5
>>* 32 Bits
>>	* TIMER23
>>	* TIMER45
>> 
>> El uso del TIMER23 es incompatible con el uso de TIMER2 y TIMER3
>>
>> El uso del TIMER45 es incompatible don el uso de TIMER4 Y TIMER5
 
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
void delay(unsigned int time)
```
------------------------------------------------------------------------------
**Descripción**
>Detiene el microcontrolador *time* microsegundos.

**Parámetros**
>unsigned int *time*
>> Tiempo en microsegundos
>> El valor máximo programable de *time* es: 
>>	* *max_time* = **2** ^ *bits_del_timer* \* **256** \/ *velocidad_del_procesador_en_MHz*
>>
>> Por ejemplo: Si el MCU funciona a 40MHz, el tiempo máximo programable es de 
>> 419.430 microsegundos.

**Retorno**
>void








------------------------------------------------------------------------------
<A name="M02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
bool every(unsigned int periode, void (*callback)(Timer* object));
```

**Descripción**
>Establece la función de *callback* que se ejecutará cada  vez que expire el 
> *periodo* (expresado en microsegundos).

**Parámetros**
>unsigned int *periode*
>> Periodo en microsegundos
>> El valor máximo programable de *periode* es: 
>>	* *max_periode* = **2** ^ *bits_del_timer* \* **256** \/ *velocidad_del_procesador_en_MHz*

>void (*callback)(void)
>> Función que será llamada cada vez que expire el *periodo*. Deberá tener el 
formato void *mi_funcion_de_callback*(Timer\* *object*).

**Retorno**
>bool
>> **true** El timer se ha configurado correctamente. 
>>
>> **false** El timer no se ha configurado correctamente. El valor de *periode* 
>> es demasiado grande.

**Ejemplo**
>El código siguiente declara el objeto *timer* como global. En *main()* se
establece que la función *on_timer()* se ejecutará cada 250 milisegundos.

```C

//----------------------------------------------
//Includes
//
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"


//----------------------------------------------
// Objetos globales
//
Timer timer(TIMER3);


// ---------------------------------------------
// Código
//
void
on_timer(Timer*) {

	//...
	//...

	return;
	}


// ---------------------------------------------
// Main
//
int
main(int argc, char** argv) {

	timer.every(250000,on_timer);

	while(true) sleep();

	return 0;
	}

```





------------------------------------------------------------------------------
<A name="M03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
bool every(unsigned int periode, Callable* object, int handle)
```

**Descripción**
>Define el valor del parámetro con el que será llamado el método
void **callback**(int) del objeto al que apunta **Callable\*** cada vez que 
expire el *periodo*. El objeto deberá ser derivado la clase 
[Callable](Callable.md) y definir dicho método.

**Parámetros**
>unsigned int *periode*
>> Periodo en microsegundos
>> El valor máximo programable de *periode* es: 
>>	* *max_periode* = **2** ^ *bits_del_timer* \* **256** \/ *velocidad_del_procesador_en_MHz*

>*Callable*\*
>> Puntero a objeto (normalmente **this**) 
> 
>int
>>Entero que será pasado como parámetro a la función void **callback**(int) 
cuando se invoque.
 
**Retorno**
>void


**Ejemplo**
> El siguiente código declara la clase 'mi_clase' derivada de 
[Callable](Callable.md). Tiene como miembros dos objetos de la clase
 **Timer**; uno asociado a 'TIMER3' y otro asociado a 'TIMER4'. 
En su constructor se establecen sendos valores de parámetro con el que se 
llamará al método void **callback**(int) cuando alguno de los *periodos*
expire.
 
```C
// ejemplo.h

//----------------------------------------------
//Includes
//
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"


//----------------------------------------------
class mi_clase : public callable {

	public:

	Timer timer3(TIMER3);
	Timer timer4(TIMER4);

	//------------------------------
	mi_clase() {
		timer3.onchange(100000,this,3);
		timer4.onchange(250000,this,4);
		}

	//------------------------------
	void
	callbakc(int valor) {

		switch(valor) {

			// Ha expiarado el periodo del timer 3
			case 3:
				//...
				//...
				breack;

			// Ha expiarado el periodo del timer 4
			case 4:
				//...
				//...
				breack;

			default:
				breeack
			}
		return;
		}
	}
```

```C
// ejemplo.cpp


//----------------------------------------------
//Includes
//
#include "ejemplo.h"


//----------------------------------------------
// Objetos globales
//
mi_clase mi_objeto;


// ---------------------------------------------
//Código
//
int
main(int argc, char** argv) {

	while(true) sleep();

	return 0;
	}

```








------------------------------------------------------------------------------
<A name="M04"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void on(void)
```

**Descripción**
>Habilita la llamada a la función del *callback*.

**Parámetros**
>void

**Retorno**
>void








------------------------------------------------------------------------------
<A name="M05"></A>
![metode](img/Nuk-metode.jpg)
</A><A href="#TOP">Top</A> | [Index](Index.md)

```C
void off(void)
```

**Descripción**
>Deshabilita la llamada a la función del *callback*. El timer sigue funcionando.

**Parámetros**
>void

**Retorno**
>void









![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)

