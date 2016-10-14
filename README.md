![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------

# Descripción


**Nuk pic32 essentials lib** es una libreria de objetos escrita en C++ que 
facilita enórmemente las tareas de desarrollo de proyectos para la gama de 
microcontroladores PIC de 32 bits, ya que enmascara (pero no impide) las 
configuraciones y operaciones mediante registros.

**Nuk pic32 essentials lib es fácil de aprender**, ya que, con apenas diez 
clases de objetos, pueden manejarse los MCUs con toda la potencia que éstos 
ofrecen. De forma muy intuitiva, se pueden gestionar:

* Los puertos de entrada/salida
	* Digital
	* Analog
	* Pwm
	* Ei (External interrupt)
* Las interfaces de comunicaciones
	* Serial, Serial_Tx y Serial_Rx
	* Spi master y eslave
	* I2c
* Y los módulos lógicos
	* Timer
	* Fifo

**Nuk pic32 essentials lib es versátil**. Para programadores avanzados, la 
librería incluye dos clases derivables muy útiles con las que se puede ampliar 
o modificar su funcionalidad, o desarrollar otras clases que cubran cuaquier 
propósito.

* Clases derivables
	* Callable
	* IrqObject

**Nuk pic32 essentials lib es abierta**. Inicialmente, la librería viene 
configurada para operar con las disposiciones de los MCU 32MX relacionadas más 
abajo. Corresponden a los que son accesibles al público en general por su 
construcción física y sirven de base y ejemplo para editar la de todos los 
demás. Estas disposiciones se pueden cambiar (dentro de las limitaciones que 
impone el diseño físico de los microcontroladores) modifiando las constantes 
que contienen los archivos de configuración:

* Machines
	* PIC32MX1xxFxxxB
	* PIC32MX2xxFxxxB




[Pincha aquí para acceder a toda la documentación.](z_Nuk_pic32_essentials_lib/doc/Index.md)

