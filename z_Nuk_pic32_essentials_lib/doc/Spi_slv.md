![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Clase Spi_slv (Slave)`**








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

Los objetos de la clase **Spi_slv** gestionan las entradas/salidas **SPI** 
del MCU en modo slave. 
  
Se operan con:
* **Constructores**
	* [**Spi_slv**(SPIn, Digital *select*, void (\**callback*)(Spi_slv\* *object*, bool *status*, char& *user_char*))](#C01)
* **Funciones**
	* [void **mi_funcion_de_callback**(Spi_slv\* *object*, bool *status*, char& *user_char*)](#F01)








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Constructores








------------------------------------------------------------------------------
<A name="C01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Spi_mstr(SPIn, Digital select, int(*callback)(Spi_slv* object,bool status, char& user_char))
```

**Descripción**
> Asocia el objecto a un puerto SPI*n* del MCU. 
Para saber qué puertos están disponible en cada MCU, véase 
[Machines](Machines.h.md#Machines)


**Parámetros**
>SPI*n*.
>>Donde *n* es el número de puerto **SPI** a gestionar
>
>Digital *select*
>>Puerto digital por el que se seleccionará el puerto **SPI**
>
>void(\**callback*)(Spi_slv\* *object*, bool *status*, char& *user_char*)
>>Función de <A href="#F01">callback</A>. El objeto la invocará cuando un 
dispositivo **master** periférico seleccione el puerto **SPI**, y por cada 
operación de entrada/salida. 
Deberá tener el formato void *función_de_callback*(Spi_slv\* *object*, bool *status*, char& *user_char*).

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
void funcion_de_callback(Spi_slv* object, bool status, char& user_char)
```

**Descripción**

Esta función, que puede tomar el nombre que el desarrollador prefiera, Deberá 
definirse en el constructor del objeto **Spi_slv**, que la invocará cuando:
* Un dispositivo **master** periférico selecciona el puerto **SPI**
* Sucesivamente, por cada pareja de bytes de entrada/salida.

**Cronológicamente**

1. El objeto **Spi_slv** esperará a que un dispositivo **master** periférico 
seleccione el puerto.
 
2. El objeto **Spi_slv** invoca a la función de *callback* con
	* *status* == **true**
	* *user_char* == **irrelevante**
 
3. La función de *callback* debe implementar la variable:
	* *user_char* = un **byte** (suele tener algún significado acerca del 
estado de nuestro MCU escclavo)
 
4. Por el puerto **SPI** podrá recibirse, o no, un byte:
	* Si no se recibe el proceso continuará desde el punto **1.**
	*	Si se recibe, también será transmitido el último byte suministrado por la 
función de *callback*.

5. El objeto **Spi_slv** invoca a la función de *callback* con:
	* *status* == **false**
	* *user_char* == **byte recibido**
 
6. La función de *callback* trata el byte *user_char*, y puede, o no, 
implementar de nuevo la variable:
	* *user_char* = un **byte**
 
7. El proceso se repite desde el punto **4.**
 
**Notas**
>Si el dispositivo **master** periférico deselecciona el puerto **SPI**, el 
proceso se interrumpeirá.
>
>Conocer cuántos bytes se requerieren en cada transmisión forma parte del 
diseño correcto de los protocolos o de la correcta interpretación de los 
diseñados por los fabricantes de dispositivos con interfaz **SPI**.
> 
>Debemos tener en cuenta que trabajar con el puerto **SPI** en modo **slave** 
requiere hacerlo a contrareloj. Esto implica que las especificaciones que se 
den para los desarrolladores de dispositivos **master** clientes de nuestro 
**slave** deberán ser precisas en cuanto a los tiempos de respuesta requeridos.

**Ejemplo**
>Las dos piezas de código corresponden, una, a un módulo **master** y, otra, a 
un módulo **slave**.
>La función del módulo **slave** es convertir en mayúsculas todo lo que le 
envíe el módulo **master**.

```C
// master.cpp

// ------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

// ------------------------------------------
Serial serial(UART2,500000);

Digital csn(PB14);
Spi_mstr spi(SPI2,1000000);

// ------------------------------------------
void
loop() {

	char tr[255];
	char* rc;
	int l;

	// Entrada por el puerto serie
	serial.put("Que ");
	while( !serial.get_line(tr) );
	l = strlen(tr);
	
	// Transmitimos por SPI (incluimos el 0 final)
	rc = spi.transmit(csn,tr,l+1);

	// Hemos recibido un byte de mas
	// (el estado del dispositivo slave)
	rc[l+1] = 0;

	// Salida por el puerto serie
	serial.put("Recibido de slave: ");
	serial.put_line(rc);

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	while(true) loop();

	return 0;
	}
```

```C
// slave.h

// ------------------------------------------
#include "Config_40.h"
#include "Nuk_pic32_essentials.h"

// ------------------------------------------
void on_spi(Spi_slv*,bool,char&);

```

```C
// slave.cpp

// ------------------------------------------
#include "slave.h"

Digital spi_sel(PB14);
Spi_slv spi(SPI2,spi_sel,on_spi);

// ------------------------------------------
void
on_spi(Spi_slv* object_slv, bool status, char& ccc) {

	if( status ) {
		ccc = 'S';
		}

	else {
		if( (ccc>96) && (ccc<123) ) ccc -= 32;
		}

	return;
	}

//----------------------------------------------
int
main(int argc, char** argv) {

	while(true) sleep();

	return 0;
	}
```








![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)


