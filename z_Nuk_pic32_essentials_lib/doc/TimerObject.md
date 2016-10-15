![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Clase TimerObject`**




------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

**TimerObject** Es una clase derivada de 
[IrqObject](IrqObject.md), derivable y no instanciable, ya que tiene el método 
virtual puro *Irq()*.

Esta clase gestiona los mecanismos de interrupción propios de los timers del 
MCU de forma tal que varios objetos puedan compartir la misma interrupción del 
timer sin interferirse unos a otros. 
Dada una interrupción que afecte a uno o varios objectos derivados de 
**TimerObject**, está se encargará de invocar al método *irq()* de cada uno de 
ellos.

siempre que hayan invocado previamente alguta de las formas del método 
*configure()*.
 
Se operan con:
* **Constructores**
	* [**TimerObject**(TIMERLIST)](#C01)

* **Métodos**
	* [bool **configure**(unsigned long)](#M01)
	* [void **configure**(unsigned long,int)](M02)
	* [virtual void **Irq**(void)=0](M03)








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Constructores








------------------------------------------------------------------------------
<A name="C01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Analog(ANxx)
```
------------------------------------------------------------------------------
**Descripción**
> Asocia el objecto a una interrupción del MCU. El constructor de la clase
derivada deberá invocar al constructor de la clase TimerObject con los parámetros 
apropiados.

**Parámetros**
>TIMERLIST
>>La lista de parámetros
>>>volatile unsigned int& txcon
>>>>Registro TxCON
>>>
>>>volatile unsigned int& tmrx
>>>>Registro TMRx
>>>
>>>volatile unsigned int& prx,
>>>>Registro PRx
>>>
>>>unsigned int bit_txcon,
>>>>Bits a on de TxCON cuando el timer se active
>>>
>>>unsigned int bit_bits,
>>>>Bist del timer
>>>
>>>unsigned int div0
>>>>Divisor del timer 0
>>>
>>>unsigned int p_div1,
>>>>Divisor del timer 1
>>>
>>>unsigned int div2
>>>>Divisor del timer 2
>>>
>>>unsigned int p_div3,
>>>>Divisor del timer 3
>>>
>>>unsigned int div4
>>>>Divisor del timer 4
>>>
>>>unsigned int div5
>>>>Divisor del timer 5
>>>
>>>unsigned int div6
>>>>Divisor del timer 6
>>>
>>>unsigned int div7,
>>>>Divisor del timer 7
>>>
>>>volatile unsigned int& iecx
>>>>Registro IECx
>>> 
>>>volatile unsigned int& ifsx,
>>>>Registro IFSx
>>> 
>>>volatile unsigned int& ipcx,
>>>>Registro IPCx
>>> 
>>>unsigned int bit_iecx,
>>>>Bits que habilitan la interrupción
>>> 
>>>unsigned int bit_ifsx,
>>>>Bits causantes de la interrupción
>>> 
>>>unsigned int bit_ipcx,
>>>>Prioridad de la interrupción
>>> 
>>>unsigned int interrupt) 
>>>>Vector de interrupción

**Retorno**
>El retorno deberá ser vold










------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Métodos








------------------------------------------------------------------------------
<A name="M01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
bool configure(unsigned long)
```
------------------------------------------------------------------------------
**Descripción**
>Suscribe el objeto derivado de **TimerObject** a la llamada del su método 
*irq()* cuando se active la interrupción definida en su constructor.

**Parámetros**
>void

**Retorno**
>void








------------------------------------------------------------------------------
<A name="M02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void irq_disable(void)
```
------------------------------------------------------------------------------
**Descripción**
>Revierte la suscripción realizada por el método [void **irq_enable**(void)](#M01) 

**Parámetros**
>void

**Retorno**
>void








------------------------------------------------------------------------------
<A name="M03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void irq(void)
```
------------------------------------------------------------------------------
**Descripción**
>Método virtual de la clase **TimerObject** a implementar por la clase derivada.

**Parámetros**
>void

**Retorno**
>void








![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)



