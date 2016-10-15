![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### `Introducción`




------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción




------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

**Nuk pic32 essentials lib** es una librería de objetos escrita en C++ que 
facilita enormemente las tareas de desarrollo de proyectos para la gama de 
microcontroladores PIC de 32 bits, ya que enmascara (pero no impide) las 
configuraciones y operaciones mediante registros.

**Nuk pic32 essentials lib** es **fácil** de aprender, ya que, con apenas diez 
clases de objetos, pueden manejarse los MCUs con toda la potencia que éstos 
ofrecen. 
De forma muy intuitiva, se pueden gestionar:
  
* Los puertos de entrada/salida
	* [Digital](Digital.md)
	* [Analog](Analog.md)
	* [Pwm](Pwm.md)
	* [Ei \(External interrupt\)](Ei.md)
* Las interfaces de comunicaciones
	* [Serial, Serial_Tx y Serial_Rx](Serial.md)
	* [Spi master](Spi_mstr.md) y [eslave](Spi_slv.md)
	* [I2c](I2c.md)
* Y los módulos lógicos
	* [Timer](Timer.md)
	* [Fifo](Fifo.md)

**Nuk pic32 essentials lib** es **versátil**. 
Para programadores avanzados, la librería incluye dos clases derivables muy 
útiles con las que se puede ampliar o modificar su funcionalidad, o desarrollar 
otras clases que cubran cualquier propósito.
* Clases derivables
	* [Callable](Callable.md)
	* [IrqObject](IrqObject.md)
  
**Nuk pic32 essentials lib** es **abierta**. 
Inicialmente, la librería viene configurada para operar con las disposiciones 
de los MCU 32MX descritas más abajo. 
Corresponden a los que son accesibles al público en general por su 
construcción física y sirven de base y ejemplo para editar la de todos los demás. 
Estas disposiciones se pueden cambiar (dentro de las limitaciones que impone el 
diseño físico de los microcontroladores) modificando las constantes que 
contienen los archivos de configuración:

* Machines
	* [PIC32MX1xxFxxxB](Machines.h.md#P01)
	* [PIC32MX2xxFxxxB](Machines.h.md#P02)





 ![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)


