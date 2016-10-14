// ****************************************************************************
// File:  Nuk_32MX1.h
// Autor: Lluis
// Descripcio
//      PIC 32MX1xxFxxxB
//




// ****************************************************************************
// Machine scheme
//
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
//    I2C2_SCL  AN05  ----  DB03  07-|   C   |-22  DB11  ----  ----  --USB_Dm
//    VSS ----  ----  ----  ----  08-|       |-21  DB10  ----  EI01  --USB_DM
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


// ****************************************************************************
// Definitions
//
#define _VUI volatile unsigned int&
#define _UI unsigned int




// ****************************************************************************
// Includes
//
#include <xc.h>
#include <sys/attribs.h>




// ****************************************************************************
// Machine configuration
//

// ----------------------------------------------------------------------------
// Interrupt
//
// 1.Name     IRQn
// 2.Register IECx
// 3.Register IFSx
// 4.Register IPCx
// 5.Value    IECx Interrupt enable
// 6.Value    IFSx Interrupt flag
// 7.Value    IPCx Interrupt priority (all fixet to 4-0)
// 8.Value    Interrupt vector
//
//          1    2    3    4          5          6          7   8
//      ----- ---- ---- ---- ---------- ---------- ---------- ---
#define IRQ04 IEC0,IFS0,IPC1,0x00000010,0x00000010,0x00000010,  4
#define IRQ06 IEC0,IFS0,IPC1,0x00000080,0x00000080,0x00100000,  6
#define IRQ07 IEC0,IFS0,IPC1,0x00000100,0x00000100,0x10000000,  7
#define IRQ08 IEC0,IFS0,IPC2,0x00000200,0x00000200,0x00000010,  8
#define IRQ09 IEC0,IFS0,IPC2,0x00000800,0x00000800,0x00001000,  9
#define IRQ11 IEC0,IFS0,IPC2,0x00002000,0x00002000,0x10000000, 11
#define IRQ12 IEC0,IFS0,IPC3,0x00004000,0x00004000,0x00000010, 12
#define IRQ13 IEC0,IFS0,IPC3,0x00010000,0x00010000,0x00001000, 13
#define IRQ15 IEC0,IFS0,IPC3,0x00040000,0x00040000,0x10000000, 15
#define IRQ16 IEC0,IFS0,IPC4,0x00080000,0x00080000,0x00000010, 16
#define IRQ17 IEC0,IFS0,IPC4,0x00200000,0x00200000,0x00001000, 17
#define IRQ19 IEC0,IFS0,IPC4,0x00800000,0x00800000,0x10000000, 19
#define IRQ20 IEC0,IFS0,IPC5,0x01000000,0x01000000,0x00000010, 20
#define IRQ21 IEC0,IFS0,IPC5,0x04000000,0x04000000,0x00001000, 21
#define IRQ31 IEC1,IFS1,IPC7,0x00000020,0x00000020,0x10000000, 31
#define IRQ32 IEC1,IFS1,IPC8,0x00000100,0x00000100,0x00000010, 32
#define IRQ33 IEC1,IFS1,IPC8,0x00000700,0x00000700,0x00001000, 33
#define IRQ34 IEC1,IFS1,IPC8,0x0000E000,0x0000E000,0x00100000, 34
#define IRQ36 IEC1,IFS1,IPC9,0x00080000,0x00080000,0x00000010, 36
#define IRQ37 IEC1,IFS1,IPC9,0x00400000,0x00400000,0x00001000, 37
#define IRQ38 IEC1,IFS1,IPC9,0x02000000,0x02000000,0x00100000, 38

// Mascara de parametres
#define IRQLIST _VUI,_VUI,_VUI,_UI,_UI,_UI,_UI








// ----------------------------------------------------------------------------
// Timer
//
//    1.Name     TIMERn
//    2.Register TxCON
//    3.Register TMRx
//    4.Register PRx
//    5.Bit      TxCON.ON: Configuracio
//    6.Value    TxCON.T32: Timer bits (0==16) o (8==32) (ORed with TxCON.ON)
// 7-14.Value    Posible timer divisors
//   15.Macro    IRQnn
//
//           1      2    3   4      5   6  7  8   9   10  11  12  13   14    15
//      ------ ------ ---- --- ------ --- -- --  -- ---- --- --- --- ---- -----
#define TIMER1  T1CON,TMR1,PR1,0x8000,0x0, 1, 8, 64, 256,  0,  0,  0,   0,IRQ04
#define TIMER2  T2CON,TMR2,PR2,0x8000,0x0, 1, 2,  4,   8, 16, 32, 64, 256,IRQ08
#define TIMER3  T3CON,TMR3,PR3,0x8000,0x0, 1, 2,  4,   8, 16, 32, 64, 256,IRQ12
#define TIMER4  T4CON,TMR4,PR4,0x8000,0x0, 1, 2,  4,   8, 16, 32, 64, 256,IRQ16
#define TIMER5  T5CON,TMR5,PR5,0x8000,0x0, 1, 2,  4,   8, 16, 32, 64, 256,IRQ20
#define TIMER23 T2CON,TMR2,PR2,0x8000,0x8, 1, 2,  4,   8, 16, 32, 64, 256,IRQ12
#define TIMER45 T4CON,TMR4,PR4,0x8000,0x8, 1, 2,  4,   8, 16, 32, 64, 256,IRQ20

// Mascara de parametres
#define TIMERLIST _VUI,_VUI,_VUI,_UI,_UI,_UI,_UI,_UI,_UI,_UI,_UI,_UI,_UI,IRQLIST

// TIMER23 es incompatible amb TIMER2 i TIMER3
// TIMER45 es inconpatible amb TIMER4 i TIMER5








// ----------------------------------------------------------------------------
// Port section
//
// 1.Name     PORTann
// 2.Register PORTa
// 3.Register ANSELa
// 4.Register TRISa
// 5.Value    Bit number
//
//            1     2      3     4   5
//      ------- ----- ------ ----- ---
#define PORTA00 PORTA,ANSELA,TRISA,  0
#define PORTA01 PORTA,ANSELA,TRISA,  1
#define PORTA02 PORTA,ANSELA,TRISA,  2
#define PORTA03 PORTA,ANSELA,TRISA,  3
#define PORTA04 PORTA,ANSELA,TRISA,  4
#define PORTB00 PORTB,ANSELB,TRISB,  0
#define PORTB01 PORTB,ANSELB,TRISB,  1
#define PORTB02 PORTB,ANSELB,TRISB,  2
#define PORTB03 PORTB,ANSELB,TRISB,  3
#define PORTB04 PORTB,ANSELB,TRISB,  4
#define PORTB05 PORTB,ANSELB,TRISB,  5

#define PORTB07 PORTB,ANSELB,TRISB,  7
#define PORTB08 PORTB,ANSELB,TRISB,  8
#define PORTB09 PORTB,ANSELB,TRISB,  9
#define PORTB10 PORTB,ANSELB,TRISB, 10
#define PORTB11 PORTB,ANSELB,TRISB, 11

#define PORTB13 PORTB,ANSELB,TRISB, 13
#define PORTB14 PORTB,ANSELB,TRISB, 14
#define PORTB15 PORTB,ANSELB,TRISB, 15

// Mascara de parametres
#define PORTLIST _VUI,_VUI,_VUI,_UI








// ----------------------------------------------------------------------------
// Digital section
//
// 1.Name     Dann
// 2.Macro    PORTann
// 3.Register ODCa
// 4.Register CNPUa
// 5.Register CNPDa
// 6.Register CNCONa
// 7.Register CNENa
// 8.Register CNSTATa
// 9.Bit      CNCONa.ON: Change Notice (CN) Control ON
// 9.Macro    IRQn
//
//         1       2    3     4     5      6     7       8      9    10
//      ---- ------- ---- ----- ----- ------ ----- ------- ------ -----
#define DA00 PORTA00,ODCA,CNPUA,CNPDA,CNCONA,CNENA,CNSTATA,0x8000,IRQ34
#define DA01 PORTA01,ODCA,CNPUA,CNPDA,CNCONA,CNENA,CNSTATA,0x8000,IRQ34
#define DA02 PORTA02,ODCA,CNPUA,CNPDA,CNCONA,CNENA,CNSTATA,0x8000,IRQ34
#define DA03 PORTA03,ODCA,CNPUA,CNPDA,CNCONA,CNENA,CNSTATA,0x8000,IRQ34
#define DA04 PORTA04,ODCA,CNPUA,CNPDA,CNCONA,CNENA,CNSTATA,0x8000,IRQ34
#define DB00 PORTB00,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB01 PORTB01,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB02 PORTB02,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB03 PORTB03,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB04 PORTB04,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB05 PORTB05,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB07 PORTB07,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB08 PORTB08,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB09 PORTB09,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB10 PORTB10,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB11 PORTB11,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB13 PORTB13,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB14 PORTB14,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34
#define DB15 PORTB15,ODCB,CNPUB,CNPDB,CNCONB,CNENB,CNSTATB,0x8000,IRQ34

// Mascara de parametres
#define DIGITALLIST PORTLIST,_VUI,_VUI,_VUI,_VUI,_VUI,_VUI,_UI,IRQLIST








// ----------------------------------------------------------------------------
// Analog section
//
// 1.Name     ANn
// 2.Macro    PORTann
// 3.Value    Analogic port number
//
//         1        2   3
//      ----  ------- ---
#define AN00  PORTA00,  0
#define AN01  PORTA01,  1
#define AN02  PORTB00,  2
#define AN03  PORTB01,  3
#define AN04  PORTB02,  4
#define AN05  PORTB03,  5
#define AN09  PORTB15,  9
#define AN10  PORTB14, 10
#define AN11  PORTB13, 11

// Mascara de parametres
#define ANALIST PORTLIST,_UI








// ----------------------------------------------------------------------------
// Pwm section (Output compare)
//
//  1.Name     tPWMTMRn
//  2.Macro    TIMERn
//  3.Bit      OCxCON.OCTSEL: Timer Select (0x00==TIMER2, 0x08==TIMER3)
//  4.Bit      OCxCON.OC32: 32-bit Compare Mode (0==16 bits) (1==32 bits)
//
//              1       2      3      4
//      --------- ------- ------ ------
#define tPWMTMR2  TIMER2 ,0x0000,0x0000
#define tPWMTRM3  TIMER3 ,0x0008,0x0000
#define tPWMTRM23 TIMER23,0x0008,0x0020

//  1.Name		PWMn
//  2.Macro    PORTaxx
//  3.Register RPaxR
//  4.Register OCxCON
//  5.Register OCxR
//  6.Register OcxRS
//  7.Value    RPaxR seleccio del port PPS
//  8.Bit      OCxCON.ON: On
//  9.Bit      OCxCON.OCM: Output_Compare==PWM,Fault_disabled
// 10.Macro    tPWMTRMx Timper posible
//
//         1       2      3     4    5     6      7      8      9       10
//      ---- ------- ------ ----- ---- ----- ------ ------ ------ --------
#define PWM0 PORTA00,RPA0R,OC1CON,OC1R,OC1RS,0x0005,0x8006,0x0006,tPWMTMR2
#define PWM1 PORTA01,RPA1R,OC2CON,OC2R,OC2RS,0x0005,0x8006,0x0006,tPWMTRM3
#define PWM2 PORTA02,RPA2R,OC4CON,OC4R,OC4RS,0x0005,0x8006,0x0006,tPWMTMR2
#define PWM3 PORTA03,RPA3R,OC3CON,OC3R,OC3RS,0x0005,0x8006,0x0006,tPWMTRM3
#define PWM4 PORTA04,RPA4R,OC5CON,OC5R,OC5RS,0x0006,0x8006,0x0006,tPWMTRM23

// Mascara de parametres
#define PWMTMRLIST TIMERLIST,_UI,_UI
#define PWMLIST PORTLIST,_VUI,_VUI,_VUI,_VUI,_UI,_UI,_UI,PWMTMRLIST

// Per construccio del microcontrolador, els PWM nomes poden utilitzar
// els timers TIMER2 i TIMER3
//
// PWM0,PWM2 i PWM4 Tenen el mateix timer; per tant, la variacio dels
//	parametres del timer d'un d'ells afectara als altres
//
// PWM1,PWM3 i PWM4 Tenen el mateix timer, per tant, la variacio dels
//	parametres del timer d'un d'ells afectara als altres.
//
// PWM3 Es inconpatibles amb els demes, ja que empra els timers
//	TIMER2 i TIMER3 com un de sol de 32 bits








// ----------------------------------------------------------------------------
// EI section (External interrupt)
//
// 1.Name     EInn
// 2.Macro    PORTann
// 4.Register INTCON
// 3.Register INTxR
// 5.Bit      INTCON.INTnEP: Edge Polarity Control bit
// 6.Valor    INTxR
// 7.Macro    IRQnn
//
//         1       2     3      4    5    6     7
//      ---- ------- -----  ----- ---- ---- -----
#define EI01 PORTB10,INTCON,INT1R,0x02,0x03,IRQ07
#define EI03 PORTB05,INTCON,INT3R,0x08,0x01,IRQ15
#define EI04 PORTB04,INTCON,INT4R,0x10,0x02,IRQ19

// Mascara de parametres
#define EILIST PORTLIST,_VUI,_VUI,_UI,_UI,IRQLIST









// ----------------------------------------------------------------------------
// Serial_RX section
//
// 1.Name     rUARTx_RX (registers)
// 2.Register UxRXREG
// 3.Register UxBGR
// 4.Register UxRXR
// 5.Register UxMODE
// 6.Register UxSTA
//
//              1       2     3     4      5     6
//      --------- ------- ----- ----- ------ -----
#define rUART1_RX U1RXREG,U1BRG,U1RXR,U1MODE,U1STA
#define rUART2_RX U2RXREG,U2BRG,U2RXR,U2MODE,U2STA

// 1.Name     cUARTx_RX (control bits)
// 2.Value    UxRXR: PPS Rx Port Select
// 3.Value    UxMODE: 8/1/N
// 4.Bit      UxSTA.URXEN: Rx enable
// 5.Bit      UxSTA.URXDA: Receive Buffer Data Available
//
//              1    2      3      4    5
//      --------- ---- ------ ------ ----
#define cUART1_RX 0x00,0x8000,0x1000,0x01
#define cUART2_RX 0x04,0x8000,0x1000,0x01

// 1.Name      UARTn_RX
// 2.Macro     PORTaxx
// 3.Macro     rUARTx_RX
// 4.Macro     cUARTx_RX
// 5.Macro     IRQnn
//
//             1       2         3         4     5
//      -------- ------- --------- --------- -----
#define UART1_RX PORTA02,rUART1_RX,cUART1_RX,IRQ32
#define UART2_RX PORTB08,rUART2_RX,cUART2_RX,IRQ37

// Mascares de parametres
#define rUARTRXLIST _VUI,_VUI,_VUI,_VUI,_VUI
#define cUARTRXLIST _UI,_UI,_UI,_UI
#define UARTRXLIST PORTLIST,rUARTRXLIST,cUARTRXLIST,IRQLIST








// ----------------------------------------------------------------------------
// Serial_TX section
//
// 1.Name     rUARTn_TX (registres)
// 2.Register UxTXREG
// 3.Register UxBGR
// 4.Register RPaxR
// 5.Register UxMODE
// 6.Register UxSTA
//              1       2     3     4      5     6
//      --------- ------- ----- ----- ------ -----
#define rUART1_TX U1TXREG,U1BRG,RPB7R,U1MODE,U1STA
#define rUART2_TX U2TXREG,U2BRG,RPB9R,U2MODE,U2STA

// 1.Name     cUARTx_TX (control bits)
// 2.Value    RPaxR: PPS TX port Select
// 3.Value    UxMODE: 8/1/N
// 4.Bit      UxSTA.UTXEN: Tx enable
// 5.Bit      UxSTA.UTXBF: Transmit Buffer Full Status
//              1    2      3      4      5
//      --------- ---- ------ ------ ------
#define cUART1_TX 0x01,0x8000,0x0400,0x0200
#define cUART2_TX 0x02,0x8000,0x0400,0x0200

// 1.Name      UARTn_TX
// 2.Macro     PORTaxx
// 3.Macro     rUARTx_TX
// 4.Macro     cUARTx_TX
//
//             1       2         3         4
//      -------- ------- --------- ---------
#define UART1_TX PORTB07,rUART1_TX,cUART1_TX
#define UART2_TX PORTB09,rUART2_TX,cUART2_TX

// Mascares de parametres
#define rUARTTXLIST _VUI,_VUI,_VUI,_VUI,_VUI
#define cUARTTXLIST _UI,_UI,_UI,_UI
#define UARTTXLIST PORTLIST,rUARTTXLIST,cUARTTXLIST








// ----------------------------------------------------------------------------
// Serial section
//
// 1.Name     UARTn
// 2.Macro    UART RX
// 3.Macro    UART TX
//
//          1        2        3
//      ----- -------- --------
#define UART1 UART1_RX,UART1_TX
#define UART2 UART2_RX,UART2_TX

// Mascares de parametres
#define UARTLIST UARTRXLIST,UARTTXLIST








// ----------------------------------------------------------------------------
// Spi section
//
// R.Name     rSPIx (registres)
// 1.Register RPaxR
// 2.Register SDIxR
// 3.Register SPIxCON
// 4.Register SPIxCON2
// 5.Register SPIxSTAT
// 6.Register SPIxBRG
// 7.Register SPIxBUFF
//
//          R     1     2       3        4        5       6       7
//      ----- ----- ----- ------- -------- -------- ------- -------
#define rSPI2 RPA4R,SDI2R,SPI2CON,SPI2CON2,SPI2STAT,SPI2BRG,SPI2BUF

// C.Name  cSPIx (control bits)
// 1.Value RPaxR: Seleccio port SDO
// 2.Value SDIxR: Seleccio port SDI
// 3 Bit   SPIxCON.MSTEN: 1 == Master mode. 0 == Slave
// 4.Bit   SPIxCON.CKE: Clock Edge Select bit
// 5.Bit   SPIxCON.CKP: Clock Polarity Select bit
//	6.Bit	  SPIxCON.ON: Spi On
//
//          C    1    2      3      4      5      6
//      ----- ---- ---- ------ ------ ------ ------
#define cSPI2 0x04,0x03,0x0020,0x0100,0x0040,0x8000

// S.Name  sSPIx (status bits)
// 1.Bit   SPIRBF: Receive Buffer Full Status bit
// 2.Bit   SPITBF: Transmit Buffer Full Status bit
// 3.Bit   SPIROV: Receive Overflow Flag bit
//
//          S    1    2    3
//      ----- ---- ---- ----
#define sSPI2 0x01,0x02,0x40

//
// 1.Name     SPIn
// 2.Macro PORTaxx SDO
// 3.Macro PORTaxx SDI
// 4.Macro PORTaxx SCK
// 5.Macro rSPIx
// 6.Macro cSPIx
// 7.Macro sSPIx
//
//         1       2       3       4     5     6     7
//      ---- ------- ------- ------- ----- ----- -----
#define SPI2 PORTA04,PORTB13,PORTB15,rSPI2,cSPI2,sSPI2

// Mascara de parametres
#define rSPILIST _VUI,_VUI,_VUI,_VUI,_VUI,_VUI,_VUI
#define cSPILIST _UI,_UI,_UI,_UI,_UI,_UI
#define sSPILIST _UI,_UI,_UI
#define SPILIST PORTLIST,PORTLIST,PORTLIST,rSPILIST,cSPILIST,sSPILIST








// ----------------------------------------------------------------------------
// I2c section
//
// R.Name     rI2Cx (Registers)
// 1.Register I2CxCON
// 2.Register I2CxSTAT
// 3.Register I2CxBRG
// 4.Register I2CxTRN
// 5.Register I2CxRCV
// 6.Register I2CxADD
// 7.Value    PGD: (Pulse Gobbler Delay)
//
//          R       1        2       3       4       5       6   7  
//      ----- ------- -------- ------- ------- ------- ------- ---
#define rI2C2 I2C2CON,I2C2STAT,I2C2BRG,I2C2TRN,I2C2RCV,I2C2ADD,104

//  C.Name  cI2Cx (Control bits)
//  0.Bit   SEN: Start Condition Enable bit
//	 1.Bit   RSEN: Repeated Start Condition Enable bit
//  2.Bit   PEN: Stop Condition Enable bit
//  3.Bit   RCEN: Receive Enable bit
//  4.Bit   ACKEN: Acknowledge Sequence Enable bit
//  5.Bit   ACKDT: Acknowledge Data bit (0==ACK) (1==NACK)
//  6.Bit   STREN: SCLx Clock Stretch Enable
//  9.Bit   DISSLW: Slew Rate Control Disable bit
//	10.Bit   SCLREL: SCLx Release
// 11.Bit   ON: I2C Enable bit
//
//          C    0    1    2    3    4    5    6      9     10     11
//      ----- ---- ---- ---- ---- ---- ---- ---- ------ ------ ------
#define cI2C2 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x0200,0x1000,0x8000

//  S.Name  sI2Cx (Status bits)
//  2.Bit   RW:Read/Write Information
//  3.Bit   S: Start bit
//  4.Bit   P: Stop bit
//  5.Bit   DA: Data/Address
//  6.Bit   I2COV: Receive Overflow Flag bit
//  7.Bit   IWCOL: Write Collision Detect bit
// 10.Bit   BCL: Master Bus Collision Detect bit
// 11.Bit   TRSTAT: Transmit Status bit
// 12.Bit   ACKSTAT:Acknowledge Status bit
//
//          S      2      3      4      5      6      7     10     11     12
//      ----- ------ ------ ------ ------ ------ ------ ------ ------ ------
#define sI2C2 0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,0x0400,0x4000,0x8000

//	N.Name     I2Cn
// 1.Macro    PORTaxx SDA
// 2.Macro    PORTaxx SCL
// 3.Macro    rI2Cx
// 4.Macro    cI2Cx
//	5.Macro    sI2Cx
// 6.Macro    IRQxx
//
//         N       1       2     3     4     5     6
//      ---- ------- ------- ----- ----- ----- -----
#define I2C2 PORTB02,PORTB03,rI2C2,cI2C2,sI2C2,IRQ38

// Mascara de parametres
#define rI2CLIST _VUI,_VUI,_VUI,_VUI,_VUI,_VUI,_UI
#define cI2CLIST _UI,_UI,_UI,_UI,_UI,_UI,_UI,_UI,_UI,_UI
#define sI2CLIST _UI,_UI,_UI,_UI,_UI,_UI,_UI,_UI,_UI
#define I2CLIST PORTLIST,PORTLIST,rI2CLIST,cI2CLIST,sI2CLIST,IRQLIST




// ----------------------------------------------------------------------------
// Watchdog section
//
// 0.Name	  WATCHDOG
// 1.Register WDTCON
// 2.Value    WDTCON.WDTCLRKEY (Alternate value 0x57430000)
// 3.Bit      WDTCON.ON          
// 4.Bit      WDTCON.WDTCLR (Alternate value 0x0000)
//
//             0      1          2      3      4
//      -------- ------ ---------- ------ ------
#define WATCHDOG WDTCON,0x00000000,0x8000,0x0001

// Mascara de parametres
#define WATCHDOGLIST _VUI,_UI,_UI,_UI


