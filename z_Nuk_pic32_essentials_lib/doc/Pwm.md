![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Clase Pwm`**




------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg) 
[Top](#TOP) | [Index](Index.md)

Los objetos de la clase **Pwm** gestionan las salidas digitales por pulsos del 
MCU. Se opera con:
* **Constructores**
	* [**Pwm**(PWMx)](#C01)
* **Métodos**
	* [bool **set**(unsigned int *periodo* [, void (**\*callback**)(Pwm\* *object*) ] )](#M1)
	* [bool **set**(unsigned int *periodo*, Callable\* *object*, int *handle*)](#M12)
	* [void **on**(unsigned long *dutty*)](#M02)
	* [void **off**(void)](#M3)
	* [void **stop**(void)](#M4)
* **Funciones**
	* [void **funcion_de_callback**(Pwm\* *object*)](#F01)








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Constructores








------------------------------------------------------------------------------
<A name="C01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Pwm(PWMx)
```
------------------------------------------------------------------------------
**Descripción**
> Asocia el objecto a un puerto PWM del MCU
 
**Parámetros**
>PWM*x*.
>>Donde *x* es el número de puerto PWM a gestionar. 
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
bool set(unsigned int periodo [, void (*callback)(Pwm* object) ] )
```

**Descripción**
>Establece el *periodo* del puerto **PWM**. Opcionalmente puede establecerse una 
función de *callback* que será invocada cada vez que el *periodo* expire. 
*set()* puede invocarse tantas veces como sea necesario cambiar el periodo.
Para poner en marcha el pulso se deberá invocar, además, al método 
<A href="#M02">on()</A>.
 
**Parámetros**
>unsigned int *periodo*
>> Duración del *periodo* en microsegundos. Si es cero, el PWM queda 
completamente parado.
> 
>void (*\*callback*)(Pwm*)
>> Opcional.
Puntero a la función de <A href="#F01">callback</A> que será llamada cada vez 
que expire el *periodo*. La función deberá tener el formato 
void *mi_funcion*(Pwm\* objeto).
> 
**Retorno**
>bool
>> **true** si el puerto se ha podido configurar correctamente.
>> **false** en caso contrario.
 
**Notas**
>Debe tenerse en cuenta que, por construcción del MCU, la clase **Pwm** sólo 
puede utilizar los timers **2** y **3**. Esto implica que, dados dos puertos 
**PWM** que utilizan el mismo timer, el cambio de *periodo* en uno de ellos 
supone el cambio de *periodo* en el otro.
Por omisión, la librería asigna el timer 2 de 16 bits a los puertos pares, el 
timer 3 de 16 bits a los impares no divisibles por tres, y el timer 23 de 32 
bits a los puertos cuyo número es divisible por 3. 
El uso de los puertos con timer de 32 bits es incompatible con el uso de los 
demás. 
> 
>También debe ternerse en cuenta que el *periodo* máximo programable es: 
>	* *microsegundos* = **2** ^ *bits_del_timer* \* **256** \/ *velocidad_del_procesador_en_MHz*
> 
>Para saber más véase [Timer](Timer.md), [Config_xx.h](Config_xx.md) y 
[Machines.h](Machines.md).

**Ejemplo 1**
>El siguiente código declara un objeto asociado al puerto PWM0. Inicalmente,
se establece un periodo de 40 milisegundos y un pulso de 1 milisegundo. 
En cada llamada a la funcion de <A href="#F01">callback</A> *on_pwm*, el 
valor del pulso varia hasta llegar a 40 milisegundos; después disminuye hasta 
llegar a 1 milisegundo; este proceso se repite indefinidademte.
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Pwm pwm(PWM0);

//----------------------------------------------
void
on_pwm(Pwm*) {

	static unsigned long dutty = 1000;
	static bool bmas = true;

	if( bmas ) {
		dutty += 1000;
		if( dutty>39000 ) bmas = false;
		}

	else	{
		dutty -= 1000;
		if( dutty<2000 ) bmas = true;
		}
	
	pwm.on(dutty);

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	pwm.set(40000,on_pwm);
	pwm.on(1000);

	while(true) sleep();

	return 0;
	}
```

**Ejemplo 2**
>Este ejemplo es parecido al anterior; pero, esta vez, variamos el periodo.
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Pwm pwm(PWM0);

//----------------------------------------------
void
on_pwm(Pwm*) {

	static unsigned long periodo = 41000;
	static bool bmas = false;

	if( bmas ) {
		periodo += 1000;
		if( periodo>39000 ) bmas = false;
		}

	else	{
		periodo -= 1000;
		if( periodo<2000 ) bmas = true;
		}
	
	pwm.set(periodo,on_pwm);
	pwm.on(1000);

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	on_pwm(&pwm);

	while(true) sleep();

	return 0;
	}

```








------------------------------------------------------------------------------
<A name="M012"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
bool set(unsigned int periodo, Callable* object, int handle)
```

**Descripción**

Establece el *periodo* del puerto **PWM** y define el valor del parámetro con 
el que será llamado el método void callback(int) del objeto al que apunta 
Callable*, que deberá ser derivado la clase Callable e implementar dicho método.
La llamada se realizará cada vez que el *periodo* expire. 
*set()* puede invocarse tantas veces como sea necesario cambiar el periodo.
Para poner en marcha el pulso se deberá invocar, además, al método 
<A href="#M02">on()</A>.
 
**Parámetros**
>unsigned int *periodo*
>> Duración del *periodo* en microsegundos. Si es cero, el PWM queda 
completamente parado.
> 
>Callable\* *object*
>> Puntero a objeto (normalmente **this**).
> 
>int *handle*
>>Entero que será pasado como parámetro a la función void callback(int) cuando 
se invoque al expirar el *periodo*
 
**Retorno**
>bool
>> **true** si el puerto se ha podido configurar correctamente.
>> **false** en caso contrario.
 
**Notas**
>Debe tenerse en cuenta que, por construcción del MCU, la clase **Pwm** sólo 
puede utilizar los timers **2** y **3**. Esto implica que, dados dos puertos 
**PWM** que utilizan el mismo timer, el cambio de *periodo* en uno de ellos 
supone el cambio de *periodo* en el otro.
Por omisión, la librería asigna el timer 2 de 16 bits a los puertos pares, el 
timer 3 de 16 bits a los impares no divisibles por tres, y el timer 23 de 32 
bits a los puertos cuyo número es divisible por 3. 
El uso de los puertos con timer de 32 bits es incompatible con el uso de los 
demás. 
> 
> También debe ternerse en cuenta que el *periodo* máximo programable es: 
>	* *microsegundos* = **2** ^ *bits_del_timer* \* **256** \/ *velocidad_del_procesador_en_MHz*
> 
>Para saber más véase [Timer](Timer.md), [Config_xx.h](Config_xx.md) y 
[Machines.h](Machines.md).








------------------------------------------------------------------------------
<A name="M02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void on(unsigned long dutty)
```

**Descripción**
>Establece la duración del pulso del objeto **Pwm** y lo pone en marcha. Este 
método puede invocarse tantas veces como sea necesario cambiar la duración 
del pulso.

**Parámetros**
>unsigned long *dutty*
>> Duración del pulso en microsegundos.

**Retorno**
>void

**Nota**
>Para poder utilizar este método, previamente se debe invocarse el método 
<A href="#M01">*set()*</A>.

**Ejemplos**
> Véanse los ejemplos del método <A href="#M01">*set()*</A> y 
<A href="#M03">*off()*</A>.








------------------------------------------------------------------------------
<A name="M03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void off(void)
```

**Descripción**
>Deshabilita el pulso del objeto **Pwm**. Si se estableció la función de 
*callback*, ésta seguirá invocándose cada vez que expire el *periodo* 
establecido con el método <A href="#M01">*set()*</A>.
 
**Parámetros**
>void
 
**Retorno**
>void
 
**Ejemplo**
> El siguiente código declara un objeto asociado al puerto PWM0. Inicalmente,
se establece un periodo de 40 milisegundos y un pulso de 1 milisegundo. La 
funcion de *callback* alterna la salida a on y off, por lo que el pulso 
aparecerá cada 80 milisegundos.
 
```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Pwm pwm(PWM0);

//----------------------------------------------
void
on_pwm(Pwm*) {

	static bool bon = true;

	if( bon ) pwm.on(1000);
	else pwm.off();
	bon = !bon;

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	pwm.set(40000,on_pwm);

	while(true) sleep();

	return 0;
	}

```








------------------------------------------------------------------------------
<A name="M04"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void stop(void)
```

**Descripción**
>Deshabilita el objeto **Pwm**. Detiene el pulso y la llamada a la función de 
*callback*. Se puede restablecer el funcionamiento con:
> 
>* <A href="#M02">*on()*</A>, si se desea conservar el *periodo* con el que 
estaba configurado en el momento en que fue parado.
>* <A href="#M01">*set()*</A> seguido de <A href="#M02">*on()*</A>, en otro caso.
 
**Parámetros**
>void
 
**Retorno**
>void








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Funciones








------------------------------------------------------------------------------
<A name="F01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void funcion_de_callback(Pwm* objeto)
```

**Descripción**
>Si se define en el método <A href="#M01">set()</A>, esta función, que puede 
tomar el nombre que el desarrollador prefiera, será invocada por el objeto 
**Pwm** cada vez que el *periodo* expire.
>Por lo general, Las taréas de la función son:
>* Cambiar el régimen del periodo con <A href="#M01">set()</A>
>* Cambiar el régimen del pulso con <A href="#M02">on()</A> y <A href="#M03">off()</A>
>* Otras tareas periódicas relacionadas con la naturaleza del proyecto.

**Parámetros**
>Pwm* *objecto*
>>Puntero al objeto **Pwm** que ha generado la llamada a la función de 
*callback*.

**Retorno**
>void


**Notas**
>Obsérvese que pueden existir varias funciones de *callback* para un mismo 
objeto, una única para varios, o varias funciones para varios objetos.
 



![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)


