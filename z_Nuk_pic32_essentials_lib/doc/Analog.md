![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Clase Analog`**




------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

Los objetos de la clase **Analog** gestionan las entradas analógicas del MCU. 
 
Se operan con:
* **Constructores**
	* [**Analog**(ANxx)](#C01)

* **Métodos**
	* [unsigned int **get**(void)](#M01)








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
> Asocia el objecto a un puerto analógico del MCU

**Parámetros**
>AN*xx*.
>>Donde *xx* es el número de puerto analógico a gestionar. 
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
unsigned int get(void)
```
------------------------------------------------------------------------------
**Descripción**
>Obtiene el valor del puerto analógico.

**Parámetros**
>void

**Retorno**
>unsigned int
>>Valor en el rango (0..1023) capturado del puerto en el instante de la
llamada al método. Este valor es proporcional al rango de voltaje (0..Vdd),
donde Vdd es la tensión que alimenta al MCU (típicamente 3,3V).

**Ejemplo**
>El siguiente código declara dos objetos asociados a los puertos analógicos
'AN00' y 'AN01'. En cada iteración de *loop()* leemos los valores de cada uno.

```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Analog analogico0(AN00);
Analog analogico1(AN01);

//----------------------------------------------
void
loop(void) {

	int valor0;
	int valor1;

	valor0 = analogico0.get();
	valor1 = analogico1.get();

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



