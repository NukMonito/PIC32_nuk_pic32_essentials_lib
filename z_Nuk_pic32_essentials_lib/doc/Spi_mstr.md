![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Clase Spi_mstr (Master)`**








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

Los objetos de la clase **Spi_mstr** gestionan las entradas/salidas 
**SPI** del MCU en modo master. 
  
Se operan con:
* **Constructores**
	* [**Spi_mstr**(SPIn, unsigned int *baud*, [ double *delay*, bool *edge*, bool *polarity* ] ))](#C01)
* **Métodos**
	* [char\* **transmit**(Digital *select*, char* *cadena*, int *size*,	[ unsigned int *freq*, double *delay*, bool *edge*, bool *polarity* ] )](#M01)








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Constructores








------------------------------------------------------------------------------
<A name="C01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Spi_mstr(SPIn,
	unsigned int baud,
	unsigned int p_freq,
	double p_delay,
	bool p_edge,
	bool p_polarity)
```

**Descripción**
> Asocia el objecto a un puerto SPI*n* del MCU

**Parámetros**
>SPI*n*.
>>Donde *n* es el número de puerto **SPI**. 
Para saber qué puertos están disponible en cada MCU, véase 
[Machines](Machines.h.md#Machines)
> 
> unsigned int *baud*
>>Velocidad en baudios del puerto.
> 
>double *delay* 
>>Opcional. Tiempo en microsegundos entre bytes transmitidos.  Por omisión == 0.
>
>bool *edge* 
>>Opcional. Clock Edge Select bit. Por omisión == true. 
> 
>bool *polarity* 
>>Opcional. Clock Polarity Select bit. Por omisión == false.


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
char* transmit(
	Digital& select,
	char* cadena,
	int size,
	unsigned int freq,
	double delay,
	bool edge,
	bool polarity )
```

**Descripción**
>Pone el puerto [Digital](Digital.md) a *off* (lo que selecciona el 
dispositivo periférico asociado) y transmite tantos bytes de la *cadena* 
como los especificados en *size*. La función retorna los bytes recibidos 
en la misma cantidad que los transmitidos. 
 
**Parámetros**
>Digital *select*
>> Puerto [Digital](Digital.md) de selección del dispositivo periférico.
> 
>char* *cadena*
>>bytes a transmitir.
> 
>int *size*
>>Cantidad de caracteres que serán transmitidos y recibidos.
> 
>unsigned int *freq*
>>Opcional. Frecuencia del bus. Por omisión == la dada en el constructor.
> 
>double *delay*
>>Tiempo en microsegundos entre bytes transmitidos. Opcional. 
>>Por omisión: Si se ha especificado la 'freq', == 0. Si no se ha especificado 
>> *freq*, == el dado en el constructor. 
> 
>bool *edge*
>>Clock Edge Select bit. Opcional. Por omisión: Si se ha especificado *freq*, 
>> == true. Si no se ha especificado *freq*, == al dado en el constructor. 
> 
>bool *polarity*
>>Clock Polarity Select bit. Opcional. Por omisión: Si se ha especificado 
>>*freq*, == false . Si no se ha especificado *freq*, == a la dada en el 
>>constructor. 

**Retorno**
>char* *cadena*
>> *Cadena* de bytes recibidos. 

**Ejemplo**
>El siguiente código declara un objeto asociado al puerto SPI2 funcionando a 
7MHz, y otro asociado a un puerto [Digital](Digital.md) DA00, que sirve para 
seleccionar el periférico. En cada iteración de *loop()* se envían y reciben 
cuatro bytes.

```C
//----------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

//----------------------------------------------
Spi_mstr spi(SPI2,7000000);
Digital select(DA00);

//----------------------------------------------
void
loop(void) {

	char recibe[4];

	recibe = spi.transmit(select,"abcd",4);

	//...
	//...

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	select.on();

	while(true) loop();

	return 0;
	}

```








![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)


