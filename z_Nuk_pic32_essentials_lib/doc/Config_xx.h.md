![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Config_xx.h`**




------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción




------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

En los ficheros *Config_xx.h* se encuentran las directivas de compilador que 
establecen el régimen de funcionamiento del MCU. La distribución de la librería 
viene con cuatro ficheros que permiten establecer la velocidad de reloj en 
8MHz, 10MHz, 20MHz y 40MHz. Respectivamente:
* Config_08.h
* Config_10.h
* Config_20.h
* Config_40.h

Deberá incluirse en el proyecto uno de estos ficheros una sola vez.

El desarrollador es libre de cambiar los valores que afectan a la velocidad de 
reloj, o de crear otros ficheros, conforme se adapten mejor a las necesidades 
de su proyecto, siempre que se configure la directiva **USERID** con el valor 
de la frecuencia a la que funcionará el MCU.

**Notas**
>Cambiar el valor de otras directivas, o suprimirlas, puede conducir a un 
comportamiento impredecible de los objetos de la librería.
> 
>Para saber más acerca de qué valores pueden tomar las directivas consúltense 
los manuales del fabricante del MCU.

**Ejemplo**

Tomemos como base el fichero *Config_40.h*.

```C
// Debug i reconfiguracio
#pragma config DEBUG    = OFF // Debug off
#pragma config IOL1WAY  = OFF // Peripheral Pin Select Configuration bit off
#pragma config PMDL1WAY = OFF // Peripheral Module Disable Configuration bit off

// SYSCLK = 40Mhz
#pragma config FNOSC    = FRCPLL    // Fast RC Osc with PLL
#pragma config FPLLIDIV = DIV_2     // 8Mhz / 2   =   4Mhz
#pragma config FPLLMUL  = MUL_20    // 4Mhz * 20  =  80Mhz
#pragma config FPLLODIV = DIV_2     // 80Mhz / 2  =  40Mhz
#pragma config FPBDIV   = DIV_1     // 40Mhz / 1  =  40Mhz
#pragma config USERID   = 40        // Frequencia en DEVCFG3<15:0>
```

Deseamos que nuestro MCU funcione a 5MHz. Para ello bastará cambiar la 
directiva 

```C
#pragma config FPBDIV   = DIV_1
``` 

por 

```C
#pragma config FPBDIV   = DIV_8
``` 

y la directiva 

```C
#pragma config USERID   = 40
``` 

por

```C
#pragma config USERID   = 5
```








![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)

