![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Clase IrqObject`**




------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

**IrqObject** Es una clase deribable no instanciable, ya que tiene el método 
virtual puro *Irq()*.

Esta clase gestiona los mecanismos de interrupción de forma tal que varios 
objetos puedan compartir la misma interrupción sin interferirse unos a otros. 
Dada una interrupción que afecte a uno o varios objectos, **IrqObject**, se 
encargará de invocar al método *irq()* de cada uno de ellos, siempre que estos 
hayan invocado previamente al método *irq_enable()*.
Por el contrario, *irq_disalbe()* deshabilitará la llamada a *irq()*.



 
Se operan con:
* **Constructores**
	* [**IrqObject**(IRQLIST)](#C01)

* **Métodos**
	* [void **irq_enable**(void)](#M01)
	* [void **irq_disable**(void)](M02)
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
> Asocia el objecto a una iterrupción del MCU. El constructor de la clase
derivada deberá invocar al constructor de la clase IrqObject con los parámetros 
apropiados.

**Parámetros**
>IRQLIST
>>La lista de parámetros
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
void irq_enable(void)
```
------------------------------------------------------------------------------
**Descripción**
>Suscribe el objeto derivado de **IrqObject** a la llamada del su método 
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
>Método virtual de la clase **IrqObject** a implementar por la clase derivada.

**Parámetros**
>void

**Retorno**
>void








![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)



