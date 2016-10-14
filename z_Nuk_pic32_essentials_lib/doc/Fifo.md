![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Clase Fifo`**




------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción








------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

Los objetos de la clase **Fifo**, gestionan colas de bytes. Pueden 
utilizarse como colas de mensajes entre diferentes partes de un proyecto, 
que fluyen de forma que el primero que entra es el primero que sale.

La clase Fifo puede manejarse, también, derivando nuevas clases. Por ejempo: 
algunas de las interfaces de comunicaciones como la clase 
[Serial_Rx](Serial.md) se gestionan mediante estas colas.
 


El tamaño de las colas **Fifo** viene dado por la constante *BUFF_SIZE* 
definida en el archivo [Definitions.h](Definitions.h.md).
 
Se operan con:
* **Constructores**
	* [**Fifo**()](#C01)
* **Métodos**
	* [void **insert**(char *byte*)](#I01)
	* [void **insert**(char* *cadena*)](#I02)
	* [void **insert**(char* *cadena*, int *size*](#I03)
	* [void **insert_line**(char* *cadena*)](#I04)
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
Fifo()
```

**Descripción**
> Crea un objeto **Fifo**.

**Parámetros**
>void

**Retorno**
>void








------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Métodos








------------------------------------------------------------------------------
<A name="I01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void insert(char byte)
```

**Descripción**
>Inserta el *byte* en en la **Fifo**.

**Parámetros**
>char *byte*
>> *byte* a insertar en la **Fifo**

**Retorno**
>void








------------------------------------------------------------------------------
<A name="I02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void insert(char* cadena)
```

**Descripción**
>Inserta en la **Fifo** la *cadena* terminada en *NULL*. El byte *NULL* no se 
insertará en la **Fifo**.

**Parámetros**
>const char* *cadena*
>> *Cadena* de bytes terminada en *NULL*.

**Retorno**
>void








------------------------------------------------------------------------------
<A name="I03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void insert(char* cadena, int size)
```

**Descripción**
>Inserta en la **Fifo** tantos bytes de la *cadena* como los indicados
por el parámetro *size*.

**Parámetros**
>const char* *cadena*
>> *Cadena* de bytes.
 
>int *size*
>> Catidad de bytes de la *cadena* a insertar en la **Fifo**. 

**Retorno**
>void

**Nota**
>Obsérvese que la inserción de bytes se hace en crudo.








------------------------------------------------------------------------------
<A name="I04"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
void insert_line(char* cadena)
```

**Descripción**
>Inserta en la **Fifo** la *cadena* terminada en *NULL*. El la **Fifo**, el 
*NULL* se sustituirá por un *EOL*.

**Parámetros**
>const char* *cadena*
>> *Cadena* de bytes terminada en *NULL*.

**Retorno**
>void

**Nota**
> Por omisión, el byte *EOL* es 0x0A; sin embargo, puede cambiarse 
modificando la constante definida en el fichero [Definitions.h](Definitions.h.md)












------------------------------------------------------------------------------
<A name="G01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
int get(const char* cadena)
```

**Descripción**
>Extrae de la **Fifo** todos los bytes pendientes.

**Parámetros**
>const char* *cadena*
>> *Cadena* donde se depositarán los bytes extraidos, más un byte *NULL*.

**Retorno**
>int size
>> Cantidad de bytes extraídos de la **Fifo**.

**Nota**
>Es resposabilidad del programador que la *cadena* disponga del tamaño 
suficiente para albergar los bytes extraídos. 








------------------------------------------------------------------------------
<A name="G02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
bool get(const char* cadena, int size)
```

**Descripción**
>Si los hay, extrae de la **Fifo** tantos bytes como los especificados en 
*size*.

**Parámetros**
>const char* *cadena*
>> Puntero a la *cadena* que deberá tener, como mínimo, *size* bytes de espacio.

> int *size*
>> Cantidad de bytes a extraer.

**Retorno**
>bool
>> **true** en la **Fifo** habian suficientes bytes. La cadena ha sido 
completada.
>>
>> **false** en la **Fifo** no hay suficientes bytes. El contenido de la 
cadena es invalido.

**Nota**
>Obsérvese que la extacción de bytes se hace en crudo.








-------------------------------------------------------------------------------
<A name="G03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
char get_char()
```

**Descripción**
>Si lo hay, extrae de la **Fifo** un byte.

**Parámetros**
>void

**Retorno**
>char
>> Si lo hay, el byte leido.
>> Si no lo hay 0 (cero).








------------------------------------------------------------------------------
<A name="G04"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
bool get_line(char* cadena)
```

**Descripción**
>Extrae de la **Fifo** los bytes pendientes hasta encontrar un final 
de linea (*EOL*). Si en la **Fifo** no aparace *EOL*, la función devuelve
**false** y el contenido de la *cadena* será invalido.

**Parámetros**
>char* cadena
>>Cadena receptora de los bytes. En la cadena, *EOL* será sustituido por 
*NULL*.

**Retorno**
>bool
>> **true** si se ha extraido algún byte.
>>
>> **false** en caso contrario.

**Nota**
> Obsérvese que, aun cuando pudieran haber bytes pendientes en la **Fifo**, 
estos no serán devueltos por el método si no se ha encontrado un *EOL*.








![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)


