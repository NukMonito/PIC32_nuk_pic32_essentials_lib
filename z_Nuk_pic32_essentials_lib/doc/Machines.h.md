![Nuk](img/Nuk-pic-essentials-lib.jpg)
------------------------------------------------------------------------------




------------------------------------------------------------------------------
### **`Machines.h`**




------------------------------------------------------------------------------
![separa](img/Nuk-separa.jpg)
### Descripción




------------------------------------------------------------------------------
![metode](img/Nuk-metode.jpg)
</A><A href="#TOP">Top</A> | [Index](Index.md)

Este fichero y los **Machine_32MXxxxFxxx.h**, en la carpeta *includes/Machines/*, 
describen mediante macros la configuración física de los posibles MCUs 
que se pueden manejar con esta librería.

El primero (**Machines.h**) determina qué fichero de los segundos 
(**Machine_32MXnFx.h**) se debe incluir en función de la directiva *-mprocessor* 
en el momento de la compilación del proyecto.

Los segundos contienen varias secciones; una por cada tipo de periférco a 
manejar y, en ellas, la declaración de macros que los describen. Estas 
macros pueden modificarse, eliminarse o añadirse con el fin de cambiar algunos 
aspectos del comportamiento de los MCUs.

<A name="Machines"></A>
La librería se distribuye con los ficheros que corresponden a los MCUs 
que son accesibles al público en general por su construcción física. Estos 
sirven de base y ejemplo para editar todos los demás.

* [PIC32MX1xxFxxxB](#P01)
* [PIC32MX2xxFxxxB](#P02)


Las secciones en cada fichero son:

* [Interrupt](#S01)
* [Timer](#S02)
* [Port](#S03)
* [Digital](#S04)
* [Analog](#S05)
* [Pwm](#S06)
* [EI (External interrupt)](#S07)
* [Serial_RX](#S08)
* [Serial_TX](#S09)
* [Serial](#S10)
* [Spi](#S11)
* [I2c](#S12)
* [Watchdog section](#S13)







------------------------------------------------------------------------------
<A name="P01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

**PIC32MX1xxFxxxB**
```
// PIC32MX110F016B
// PIC32MX120F032B
// PIC32MX130F064B
// PIC32MX130F256B
// PIC32MX150F128B
// PIC32MX170F256B
//                                    _______
//    ~MCLR---  ----  ----  ----  01-|.      |-28  ----  ----  ----  --- AVDD
//    --------  AN00  PWM0  DA00  02-|       |-27  ----  ----  ----  --- AVSS
//    --------  AN01  PWM1  DA01  03-|   O   |-26  DB15  ----  AN09  SPI2_SCK
//    PGED1---  AN02  ----  DB00  04-|       |-25  DB14  ----  AN10  --------
//    PGEC1---  AN03  ----  DB01  05-|   P   |-24  DB13  ----  AN11  SPI2_SDI
//    I2C2_SDA  AN04  ----  DB02  06-|   I   |-23  DB12  ----  AN12  --------
//    I2C2_SCL  AN05  ----  DB03  07-|   C   |-22  DB11  ----  ----  SPI2_SDO
//    VSS ----  ----  ----  ----  08-|       |-21  DB10  ----  EI01  --------
//    UART1_RX  ----  PWM2  DA02  09-|   3   |-20  ----  ----  ----  --- VCAP
//    --------  ----  PWM3  DA03  10-|   2   |-19  ----  ----  ----  ---- VSS
//    --------  EI04  ----  DB04  11-|       |-18  DB09  ----  ----  UART2_TX
//    --------  ----  PWM4  DA04  12-|   O   |-17  DB08  ----  ----  UART2_RX
//    VDD ----  ----  ----  ----  13-|       |-16  DB07  ----  ----  UART1-TX
//    --------  EI03  ----  DB05  14-|_______|-15  DB06  ----  EI02  --------
//
// Dann  Digital (donde a puede ser A, B)
// ANnn  Analógico
// PWMn  Pulse Width Modulation
// EInn  EI (external interrupt)
//
// I2Cn  I2C
// SPIn  SPI
// UARTn Serial
//
// Numeración de pines para los encapsulados SOIC, SPDIP, SSOP.
// Para otros encapsulados deberá hacerse una corrección de numeración de pines
```



------------------------------------------------------------------------------
<A name="P02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

**PIC32MX2xxFxxxB**
```
// PIC32MX210F016B
// PIC32MX220F032B
// PIC32MX230F064B
// PIC32MX230F256B
// PIC32MX250F128B
// PIC32MX270F256B

//                                    _______
//    ~MCLR---  ----  ----  ----  01-|.      |-28  ----  ----  ----  --- AVDD
//    --------  AN00  PWM0  DA00  02-|       |-27  ----  ----  ----  --- AVSS
//    --------  AN01  PWM1  DA01  03-|   O   |-26  DB15  ----  AN09  SPI2_SCK
//    PGED1---  AN02  ----  DB00  04-|       |-25  DB14  ----  AN10  --------
//    PGEC1---  AN03  ----  DB01  05-|   P   |-24  PB13  ----  AN11  SPI2_SDI
//    I2C2_SDA  AN04  ----  DB02  06-|   I   |-23  ----  ----  ----  V USB3V3
//    I2C2_SCL  AN05  ----  DB03  07-|   C   |-22  DB11  ----  ----  - USB_DM
//    VSS ----  ----  ----  ----  08-|       |-21  DB10  ----  EI01  - USB_DP
//    UART1_RX  ----  PWM2  DA02  09-|   3   |-20  ----  ----  ----  --- VCAP
//    --------  ----  PWM3  DA03  10-|   2   |-19  ----  ----  ----  ---- VSS
//    --------  EI04  ----  DB04  11-|       |-18  DB09  ----  ----  UART2_TX
//    SPI2_SDO  ----  PWM4  DA04  12-|   O   |-17  DB08  ----  ----  UART2_RX
//    VDD ----  ----  ----  ----  13-|       |-16  DB07  ----  ----  UART1_TX
//    USBID --  EI03  ----  DB05  14-|_______|-15  ----  ----  ----  -- V BUS
//
// Dann  Digital (donde a puede ser A, B)
// ANn   Analógico
// PWMn  Pulse Width Modulation
// EInn  EI (external interrupt)
//
// I2Cn  I2C
// SPIn  SPI
// UARTn Serial
//
// Numeración de pines para los encapsulados SOIC, SPDIP, SSOP.
// Para otros encapsulados deberá hacerse una corrección de numeración de pines

```








------------------------------------------------------------------------------
<A name="S01"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Interrupt section
```

**Descripción**
> Establece el comportamiento de las interrupciones.

**Parámetros**
>1 Name     IRQx
>> Donde *n* es el número de interrupción. Nombre de la macro con el que otras 
podrán hacer referencia a ella.
> 
>2 Register IECx
>> Donde *x* es el número de interrupción. Registro dónde se establecen los 
bits que la habilitan.
> 
>3 Register IFSx
>>Donde *x* es el número de interrupción. Registro dónde se indica los 
bits a revisar en el caso de que la interrupción se active.
> 
>4 Register IPCx
>>Donde *x* es el número de interrupción. Registro donde se establece la 
prioridad de la interrupción (siempre 4).
> 
>5 Value    IECx Interrupt enable
>>Donde *x* es el número de interrupción. Bits que habilitan la interrupción.
> 
>6 Value    IFSx Interrupt flag
>>Donde *x* es el número de interrupción. Bits que a revisar en caso de que la 
interrupción se active.
> 
>7 Value    IPCx Interrupt priority.
>>Donde *x* es el número de interrupción. Siempre 4.
> 
>8 Value    Interrupt vector.
>>Donde *x* es el número de interrupción. Vector de interrupción.


**Nota**
> Los valores de estas macros no deben modificarse, ya que establecen el 
>comportamiento de las clases estándar de esta librería. Sin embargo, sí es 
>posible añadir más para cubrir las necesidades de una clase nueva que requiera 
>el uso de alguna interrupción, en el supuesto de que ésta coincida con el vector 
>pero no con los bits de activación. En cualquier caso, obviamente, el nombre de 
>interrupción deberá ser distinto a los existentes.








------------------------------------------------------------------------------
<A name="S02"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Timer section
```

**Descripción**
> Establece el comportamiento de las Timers.

**Parámetros**
>1 Name     TIMERn
>>Donde *n* es el número de timer.  Nombre de la macro con el que otras 
>>podrán hacer referencia a ella.
> 
>2 Register TxCON
>>Donde *x* es el número de timer. Registro de control del timer.
> 
>3 Register TMRx
>>Donde *x* es el número de timer. Registro configuración de tics del periodo en 
>>tics de reloj / divisor.
> 
>4 Register PRx
>>Donde *x* es el número de timer. Registro contador de tics de reloj/divisor.
> 
>5 Bit      TxCON.ON
>>Donde *x* es el número de timer. Bit de activación del timer en el registro 
>>TxCON.
> 
>6 Value    TxCON.T32
>>Donde *x* es el número de timer. Bits del timer. Puede tomar los valores: 
>>* 0x0 para 16 bits
>>* 0x8 para 32 bits
> 
>7-14 Value    Posible timer divisors
>>Divisores posibles del timer. Deben completarse de izquierda a derecha y de 
>>menor a mayor.
> 
>15 Macro    IRQn
>>Donde *n* es el número de interrupción. Alguna de las macros enumeradas en 
[Interrupt section](S01)

**Nota**
>En principio, no debe modificarse nada en esta sección.








------------------------------------------------------------------------------
<A name="S03"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Port section
```

**Descripción**
>Describe los puertos. Enumera los registros y bits con los que se gestiona 
>cada uno.

**Parámetros**
>1 Name     PORTann
>>Donde *a* es el nombre del registro y *nn* es el número de puerto. 
>>Nombre de la macro con el que otras podrán hacer referencia a ella.
> 
>2 Register PORTa
>>Donde *a* completa el nombre del registro. Pude ser A, B o C
> 
>3 Register ANSELa
>>Donde *a* completa el nombre del registro. Pude ser A, B o C 
> 
>4 Register TRISa
>>Donde *a* completa el nombre del registro. Pude ser A, B o C 
> 
>5 Value    Bit number
>>Número de bit en el registro que lo gestiona.
**Nota**
>En principio, no debe modificarse nada en esta sección.







------------------------------------------------------------------------------
<A name="S04"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Digital section
```

**Descripción**
>Enumera los registros y bits con los que se gestionan los pines digitales.

**Parámetros**
>1 Name     Dann
>>Donde *a* es el registro y *nn* el bit del registro que representa al pin del 
>>puerto. 
>>Nombre de la macro con el que otras o el código podrán hacer referencia a ella. 
> 
>2 Macro    PORTann
>>Debe se una de las macros relacionadas en [Port seccion](#S03). 
> 
>3 Register ODCa
> 
>4 Register CNPUa
> 
>5 Register CNPDa
> 
>6 Register CNCONa
> 
>7 Register CNENa
> 
>8 Register CNSTATa 
>>Donde *a* completa el nombre del registro. 
>>Registros de gestión que rigen el comportamiento del puerto. 
> 
>9 Bit      CNCONa.ON:
>>Change Notice (CN) Control ON. 
>>Bit con el que se activa la interrupción por cambio de estado del pin 
>>gestionado. 
> 
>9 Macro    IRQn
>>Debe ser una de las macros relacionadas en [Interrupt section](#S01).

**Nota**
>En principio, no debe modificarse nada en esta sección.








------------------------------------------------------------------------------
<A name="S05"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Analog section
```

**Descripción**
>Enumera los registros y bits con los que se gestionan los pines analógicos.

**Parámetros**
>1 Name     ANn
>>Donde *a* es el registro y *nn* el bit del registro que representa al pin del 
>>puerto. 
>>Nombre de la macro con el que otras o el código podrán hacer referencia a ella. 
> 
>2 Register PORTann
>>Debe ser una de las macros relacionadas en [Port seccion](#S03). 
> 
>3 Value    Analogic port number
>>Número del pin analógico.

**Nota**
>En principio, no debe modificarse nada en esta sección.








------------------------------------------------------------------------------
<A name="S06"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Pwm section (Output compare)
```

**Descripción**
>Enumera los registros y sus bits con los que se gestionan los pines 
>configurables como PWM (Pulse Width Modulation). 

**Parámetros**
>Los parámetros que describen este tipo de puerto viene dividida en dos 
>apartados:
>* **Timers posibles** 
>* **Registros, valores, macros y bits propios de PWM** 

> 
>**Timers posibles** 
>> 1 Name     tPWMTMRn 
>>>Dónde *n* es el timer posible. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella. 
>> 
>> 2 Macro    TIMERn 
>>>Alguna de las macros definidas en [Timer secction](S02) 
>> 
>> 3 Bit      OCxCON.OCTSEL: 
>>>Donde x es el número de timer. Bit de selección de timer. Timer Select: 
>>>* 0x00==TIMER2 
>>>* 0x08==TIMER3 
>> 
>> 4 Bit      OCxCON.OC32:
>>>Donde x es el número de timer. Bits del timer: 
>>>* 0==16 bits
>>>* 1==32 bits.
> 
>**Registros, valores, macros y bits propios de PWM**
>>1 Name     PWMn 
>>>Dónde *n* es el número de PWM disponible. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella.
>> 
>>2 Macro    PORTaxx 
>>>Alguna de las macros enumeradas en [Port secction](S03)
>> 
>>3 Register RPaxxR 
>>>Registro RPaxxR. Donde a y xx deben coincidir con las de la macro PORTaxx. 
>>
>>4 Register OCxCON 
>> 
>>5 Register OCxR 
>> 
>>6 Register OcxRS 
>> 
>>>Donde x es el número de PWM. 
>>>Registros de gestión que rigen el comportamiento de los puertos PWM. 
>> 
>>7 Value    RPaxxR 
>>>Valor que debe tomar el registro RPaxxR para hacer que este sea, 
>>>efectivamente, un puerto gestionado por el módulo output compare del MCU. 
>>>Véase la documentación del fabricante. 
>> 
>>8 Bit      OCxCON.ON 
>>>Donde x es el número de PWM. 
>>>Bit que habilita/deshabilita el puerto como output compare. 
>> 
>>9 Bit      OCxCON.OCM 
>>>Donde x es el número de PWM. 
>>>Bit para configurar el módulo Output_Compare en modo *PWM, Fault_disabled*. 
>> 
>>10 Macro tPWMTRMx 
>>>Una de las macros del apartado **Timers posibles** de esta misma sección. 

**Nota**
> Potencialmente, los ítems que se pueden cambiar en esta sección son:
>> **3 Register RPaxxR y 7 Value RPaxxR** en consonancia con  **1 Macro PORTaxx**
>>
>> **10 Macro tPWMTRMx**






------------------------------------------------------------------------------
<A name="S07"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)
```C
EI section (External interrupt)
```

**Descripción**
>Enumera los registros y bits con los que se gestionan los pines EI.

**Parámetros**
>1 Name     EInn
>>Dónde *n* es el número de EI. Nombre de la macro con el que otras 
>>o el código podrán hacer referencia a ella.
> 
>2 Macro    PORTann
>>Alguna de las macros enumeradas en [Port secction](S03)
> 
>4 Register INTCON 
> 
>3 Register INTxR
>>Registros que rigen el comportamiento del módulo. 
> 
>5 Bit      INTCON.INTnEP
>>Bit de control de la polaridad (Edge Polarity Control bit) con la que se 
>>displarará la interrupción. 
> 
>6 Value    INTxR 
>>Valor que debe tomar el registro INTxR para que, efectivamente pueda 
>>gestionarse la interrupción. Véase la documentación del fabricante. 
> 
>7 Macro    IRQnn
>>Alguna de las macros enumeradas en [Intrrupt secction](S01)

**Nota**
>En principio, no debe modificarse nada en esta sección.








------------------------------------------------------------------------------
<A name="S08"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)
```C
Serial_RX section
```

**Descripción**
>Enumera los registros y bits con los que se gestionan puertos UART en modo RX.

**Parámetros**
>Los parámetros que describen este tipo de puerto viene dividida en tres 
>apartados:
>* **Registros** 
>* **Valores y bits** 
>* **Configuración**

> 
>**Registros** 
>>1 Name     rUARTx_RX
>>>Dónde *x* es el número de UART_RX. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella. 
>> 
>>2 Register UxRXREG 
>> 
>>3 Register UxBGR 
>> 
>>4 Register UxRXR 
>> 
>>5 Register UxMODE 
>> 
>>6 Register UxSTA 
>>>Donde *x* es el número de UART_RX. 
>>>Conjunto de registros que rigen el comportamiento del módulo UART_RX
> 
>**Valores y bits** 
>>1 Name     cUARTx_RX 
>>>Dónde *x* es el número de UART_RX. Nombre de la macro con el que otras 
o el código podrán hacer referencia a ella. 
>> 
>>2 Value    UxRXR 
>>>Dónde *x* es el número de UART_RX. Valor que toma el registro UxRXR para 
>>>seleccionar el pin (Port Rx PPS selecction). Véase la documentación del 
>>>fabricante. 
>> 
>>3 Value    UxMODE 
>>>Dónde *x* es el número de UART_RX. Configuración del puerto serie. Por 
>>>omisión 8/1/N. Véase la documentación del fabricante si se desea cambiar 
>>>esta configuración. 
>> 
>>4 Bit      UxSTA.URXEN 
>>>Dónde *x* es el número de UART_RX. Bit del registro UxSTA que habilita la 
recepción del puerto serie (Rx Enable). 
>> 
>>5 Bit      UxSTA.URXDA 
>>>Dónde *x* es el número de UART_RX. Bit del registro UxSTA que informa de la 
disponibilidad de un byte de entrada (Receive Buffer Data Available). 
> 
>**Configuración** 
>>1 Name      UARTn_RX 
>>>Dónde *x* es el número de UART_RX. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella. 
>> 
>>2 Macro     PORTaxx 
>>>Una de las macros de [Port section](#S03) 
>> 
>>3 Macro     rUARTx_RX 
>>>Una de las macros del apartado *Registros* de esta sección. 
>> 
>>4 Macro     cUARTx_RX 
>>>Una de las macros del apartado *Valores y bits* de esta sección. 
>> 
>>5 Macro     IRQnn 
>>>Una de las macros del [Iterrupt section](#S01). 

**Notas** 
> Potencialmente, los items que se pueden cambiar en esta sección son:
>>**2 Value UxRXR** en consonancia con **2 PORTaxx**
>>
>>**3 Value UxMODE**







------------------------------------------------------------------------------
<A name="S09"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)
```C
Serial_TX section
```

**Descripción**
>Enumera los registros y bits con los que se gestionan puertos UART en modo TX.

**Parámetros**
>Los parámetros que describen este tipo de puerto viene dividida en tres 
>apartados:
>* **Registros** 
>* **Valores y bits** 
>* **Configuración**

> 
>**Registros** 
>>1 Name     rUARTx_TX
>>>Dónde *x* es el número de UART_TX. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella. 
>> 
>>2 Register UxTXREG 
>> 
>>3 Register UxBGR 
>> 
>>4 Register RPaxR
>> 
>>5 Register UxMODE 
>> 
>>6 Register UxSTA 
>>>Donde *x* es el número de UART_RX. 
>>>Conjunto de registros que rigen el comportamiento del módulo UART_TX
> 
>**Valores y bits** 
>>1 Name     cUARTx_TX 
>>>Dónde *x* es el número de UART_TX. Nombre de la macro con el que otras 
o el código podrán hacer referencia a ella. 
>> 
>>2 Value    RPaxR
>>>Donde *a* y *x* coinciden respectivamente con *a* y *x* de alguno de las 
>>>macros PORTax. Valor que toma el registro UxRXR para seleccionar el pin 
>>>(PPS TX port Select). Véase la documentación del fabricante. 
>> 
>>3 Value    UxMODE 
>>>Dónde *x* es el número de UART_TX. Configuración del puerto serie. Por 
>>>omisión 8/1/N. Véase la documentación del fabricante si se desea cambiar 
>>>esta configuración. 
>> 
>>4 Bit      UxSTA.URXEN 
>>>Dónde *x* es el número de UART_TX. Bit del registro UxSTA que habilita la 
recepción del puerto serie (Rx Enable). 
>> 
>>5 Bit      UxSTA.URXBF 
>>>Dónde *x* es el número de UART_TX. Bit del registro UxSTA que informa del 
estado del buffer de salida (Transmit Buffer Full Status). 
> 
>**Configuración** 
>>1 Name      UARTn_TX 
>>>Dónde *x* es el número de UART_TX. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella. 
>> 
>>2 Macro     PORTaxx 
>>>Una de las macros de [Port section](#S03) 
>> 
>>3 Macro     rUARTx_RX 
>>>Una de las macros del apartado *Registros* de esta sección. 
>> 
>>4 Macro     cUARTx_RX 
>>>Una de las macros del apartado *Valores y bits* de esta sección. 

**Notas** 
> Potencialmente, los items que se pueden cambiar en esta sección son:
>>**2 Value RPaxR** en consonancia con **2 PORTaxx**
>>
>>**3 Value UxMODE**








------------------------------------------------------------------------------
<A name="S10"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)
```C
Serial section
```

**Descripción**
>El cometido de esta sección no es más que ofrecer azúcar sintáctico a los 
objectos de las clases [Serial](Serial.md) 

**Parámetros**
>1 Name     UARTn
>>Dónde *n* es el número de UART. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella. 
> 
>2 Macro    UARTn_RX
>>Una de las macros del apartado *Configuración* de [Serial_RX section](#S08). 
> 
>3 Macro    UARTn_TX
>>Una de las macros del apartado *Configuración* de [Serial_TX section](#S09). 








------------------------------------------------------------------------------
<A name="S11"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)
```C
Spi section
```

**Descripción**
>Enumera los registros y bits con los que se gestionan puertos SPI. 

**Parámetros**
>Los parámetros que describen este tipo de puerto viene dividida en cuatro 
>apartados:
>* **Registros** 
>* **Bits de control** 
>* **Bits de status**
>* **Configuración**
 
>**Registros** 
>>R Name rSPIx
>>>Dónde *x* es el número de puerto SPI. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella. 
>>
>>1 Register RPaxR
>>
>>2 Register SDIxR
>>
>>3 Register SPIxCON
>>
>>4 Register SPIxCON2
>>
>>5 Register SPIxSTAT
>>
>>6 Register SPIxBRG
>>
>>7 Register SPIxBUFF
>>>Donde *x* es el número de puerto SPI. 
>>>Conjunto de registros que rigen el comportamiento del módulo SPI. 
> 
>**Bits de control** 
>>C Name  cSPIx (control bits)
>>>Dónde *x* es el número de puerto SPI. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella. 
>>
>>1 Value RPaxR
>>>Dónde *x* es el número de puerto SPI. Selección del puerto SDO
>>
>>2 Value SDIxR
>>>Dónde *x* es el número de puerto SPI. Selección del puerto SDI
>>
>>3 Bit SPIxCON.MSTEN
>>>Dónde *x* es el número de puerto SPI. Modo: 1 == Master, 0 == Slave.
>>
>>4 Bit SPIxCON.CKE
>>>Dónde *x* es el número de puerto SPI. Clock Edge Select bit.
>>
>>5 Bit SPIxCON.CKP
>>>Dónde *x* es el número de puerto SPI. Clock Polarity Select bit.
>>
>>6 Bit SPIxCON.ON
>>>Dónde *x* es el número de puerto SPI. Spi On.
> 
>**Bits de status**
>>S Name  sSPIx (status bits)
>>
>>1 Bit SPIRBF
>>>Receive Buffer Full Status bit
>>
>>2 Bit SPITBF
>>>Transmit Buffer Full Status bit
>>
>>3 Bit SPIROV
>>>Receive Overflow Flag bit
> 
>**Configuración**
>>1 Name SPIn
>>>Dónde *x* es el número de puerto SPI. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella. 
>>
>>2 Macro PORTaxx
>>>Puerto para SDO. Alguna de las macros definidas en [Port section](#S03). 
>>>Debe ser coherente con *1 Value RPaxR* del apartado *Bits de control* de 
>>>esta sección. 
>>
>>3 Macro PORTaxx
>>>Puerto para SDI. Alguna de las macros definidas en [Port section](#S03). 
>>>Debe ser coherente con *2 Value SDIxR* del apartado *Bits de control* de 
>>>esta sección. 
>>
>>4 Macro PORTaxx
>>>Puerto SCK. Alguna de las macros definidas en [Port section](#S03). 
>>>Debe ser coherente con el puerto SPI elegido. 
>>
>>5 Macro rSPIx
>>>Alguna de las macros definidas en el apartado *Registros* de esta sección. 
>>
>>6 Macro cSPIx
>>>Alguna de las macros definidas en el apartado *Bits de control* de esta 
>>>sección. 
>>
>>7 Macro sSPIx
>>>Alguna de las macros definidas en el apartado *Bits de status* de esta 
>>>sección. 


**Notas**
> Potencialmente, los ítems que se pueden cambiar en esta sección son:
>>**1 Value RPaxR** en consonancia con **4 Macro PORTaxx** para puerto para SDO
>>
>>**2 Value SDIxR** en consonancia con **4 Macro PORTaxx** para puerto para SDI





------------------------------------------------------------------------------
<A name="S12"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)
```C
I2c section
```

**Descripción**
>Enumera los registros y bits con los que se gestionan puertos I2C. 

**Parámetros**
>Los parámetros que describen este tipo de puerto viene dividida en cuatro 
>apartados:
>* **Registros** 
>* **Bits de control** 
>* **Bits de status**
>* **Configuración**
> 
>**Registros** 
>>R Name rI2Cx
>>>Dónde *x* es el número de puerto I2C. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella.
>>
>>1 Register I2CxCON
>>
>>2 Register I2CxSTAT
>>
>>3 Register I2CxBRG
>>
>>4 Register I2CxTRN
>>
>>5 Register I2CxRCV
>>
>>6 Register I2CxADD
>>>Donde *x* es el número de puerto I2C. 
>>>Conjunto de registros que rigen el comportamiento del módulo I2C.
>>
>>7 Value PGD
>>>Pulse Gobbler Delay
>
>**Bits de control** 
>>C Name cI2Cx
>>>Dónde *x* es el número de puerto I2C. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella.
>>
>>0 Bit SEN
>>>Start Condition Enable bit
>>
>>1 Bit RSEN
>>>Repeated Start Condition Enable bit
>>
>>2 Bit PEN
>>>Stop Condition Enable bit
>>
>>3 Bit RCEN
>>>Receive Enable bit
>>
>>4 Bit ACKEN
>>>Acknowledge Sequence Enable bit
>>
>>5 Bit ACKDT
>>>Acknowledge Data bit (0==ACK) (1==NACK)
>>
>>6 Bit STREN
>>>SCLx Clock Stretch Enable
>>
>>9 Bit DISSLW
>>>Slew Rate Control Disable bit
>>
>>10 Bit SCLREL
>>>SCL Release
>>
>>11 Bit ON
>>>I2C Enable bit
> 
>**Bits de status**
>>S Name sI2Cx
>>>Dónde *x* es el número de puerto I2C. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella.
>>
>>2 Bit RW
>>>Read/Write Information
>>
>>3 Bit S
>>>Start bit
>>
>>4 Bit P
>>>Stop bit
>>
>>5 Bit DA
>>>Data/Address
>>
>>6.Bit I2COV
>>>Receive Overflow Flag bit
>>
>>7 Bit IWCOL
>>>Write Collision Detect bit
>>
>>10 Bit BCL
>>>Master Bus Collision Detect bit
>>
>>11 Bit TRSTAT
>>>Transmit Status bit
>>
>>12 Bit ACKSTAT
>>>Acknowledge Status bit
> 
>**Configuración**
>>N Name I2Cn
>>>Dónde *x* es el número de puerto I2C. Nombre de la macro con el que otras 
>>>o el código podrán hacer referencia a ella.
>>
>>1 Macro PORTaxx
>>>Puerto para SDA. Alguna de las macros definidas en [Port section](#S03). 
>>>Debe ser coherente con el puerto I2C elegido. 
>>
>>2 Macro PORTaxx
>>>Puerto para SCL. Alguna de las macros definidas en [Port section](#S03). 
>>>Debe ser coherente con el puerto I2C elegido. 
>>
>>3 Macro rI2Cx
>>>Alguna de las macros definidas en el apartado *Registros* de esta sección.
>>
>>4 Macro cI2Cx
>>>Alguna de las macros definidas en el apartado *Bits de control* de esta 
>>>sección.
>>
>>5 Macro sI2Cx
>>>Alguna de las macros definidas en el apartado *Bist de status* de esta 
>>>sección.
>>
>>6 Macro IRQnn
>>>Alguna de las macros definidas en [Interrupt](#S01).







------------------------------------------------------------------------------
<A name="S13"></A>
![metode](img/Nuk-metode.jpg)
[Top](#TOP) | [Index](Index.md)

```C
Watchdog section
```

**Descripción**
>Informa del registro y bits con los que se gestiona del módulo Watchdog.
>

**Parámetros**
>0 Name     WATCHDOG
>>Nombre de la macro con el que otras o el código podrán hacer referencia a ella.
> 
>1 Register WDTCON
>> Registro de Watchdog.
> 
>2 Value    WDTCON.WDTCLRKEY
>> Puede tomar los valores 0x00000000 ó 0x57430000
> 
>3 Bit      WDTCON.ON
>> Watchdog enable.
> 
>4 Bit      WDTCON.WDTCLR
>> Puede tomar los valores 0x0000 ó 0x0001

**Nota**
>La librería no utiliza esta macro. Está disponible con el fin de facilitar al 
desarrollador los registros y valores de forma portable. Es responsabilidad del 
desarrollador, por tanto, declarar la directiva **\#pragma WDTPS=PSn**.
Véase la documentación del fabricante del MCU para conocer los detalles de 
operación del módulo Watchdog.

**Ejemplo**
>Puede definirse una función cuyos parámetros recojan los valores de 
la macro.

```C
void
my_watchdog(
	volatile unsigned int& wdtcon,
	unsigned int wdtclrkey,
	unsigned int on
	unsigned int wdtclr ) {

	//...
	//...

	return;
	}

```

>La función puede invocarse con:
```C
	my_watchdog(WATCHDOG);
```





![separa](img/Nuk-separa.jpg)
[Top](#TOP) | [Index](Index.md)


