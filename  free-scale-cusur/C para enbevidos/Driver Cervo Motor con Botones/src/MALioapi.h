/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            sysinit.c
* version:         1.0
* created_by:      Carlos Calvillo
* date_created:    May 17 2010
*=============================================================================*/
/* DESCRIPTION : Source file for basic IO functionality                       */
/*============================================================================*/
/* FUNCTION COMMENT : Provides APIs for basic handling of IOs                 */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/may/2010 |                               | Carlos Calvillo  */
/* Initial version for the Smart Car Race 2010 contest using Freescale        */
/* Bolero micro.                                                              */
/*============================================================================*/
#ifndef MALIOAPI_H                                 /* To avoid double inclusion */
#define MALIOAPI_H
/* Includes */
/* -------- */
#include "stdtypedef.h"


/* PIN PCR values definitions */
#define pin_PA0			    0
#define pin_PA1			    1
#define pin_PA2			    2
#define pin_PA3			    3
#define pin_PA4			    4
#define pin_PA5			    5
#define pin_PA6			    6
#define pin_PA7			    7
#define pin_PA8			    8
#define pin_PA9			    9
#define pin_PA10			10
#define pin_PA11			11
#define pin_PA12			12
#define pin_PA13			13
#define pin_PA14			14
#define pin_PA15			15
#define pin_PB0			    16
#define pin_PB1			    17
#define pin_PB2			    18
#define pin_PB3			    19
#define pin_PB4			    20
#define pin_PB5			    21
#define pin_PB6			    22
#define pin_PB7			    23
#define pin_PB8			    24
#define pin_PB9			    25
#define pin_PB10			26
#define pin_PB11			27
#define pin_PB12			28
#define pin_PB13			29
#define pin_PB14			30
#define pin_PB15			31
#define pin_PC0			    32
#define pin_PC1			    33
#define pin_PC2			    34
#define pin_PC3			    35
#define pin_PC4			    36
#define pin_PC5			    37
#define pin_PC6			    38
#define pin_PC7			    39
#define pin_PC8			    40
#define pin_PC9			    41
#define pin_PC10			42
#define pin_PC11			43
#define pin_PC12			44
#define pin_PC13			45
#define pin_PC14			46
#define pin_PC15			47
#define pin_PD0			    48
#define pin_PD1			    49
#define pin_PD2			    50
#define pin_PD3			    51
#define pin_PD4			    52
#define pin_PD5			    53
#define pin_PD6			    54
#define pin_PD7			    55
#define pin_PD8			    56
#define pin_PD9			    57
#define pin_PD10			58
#define pin_PD11			59
#define pin_PD12			60
#define pin_PD13			61
#define pin_PD14			62
#define pin_PD15			63
#define pin_PE0			    64
#define pin_PE1			    65
#define pin_PE2			    66
#define pin_PE3			    67
#define pin_PE4			    68
#define pin_PE5			    69
#define pin_PE6			    70
#define pin_PE7			    71
#define pin_PE8			    72
#define pin_PE9			    73
#define pin_PE10			74
#define pin_PE11			75
#define pin_PE12			76
#define pin_PE13			77
#define pin_PE14			78
#define pin_PE15			79
#define pin_PF0			    80
#define pin_PF1			    81
#define pin_PF2			    82
#define pin_PF3			    83
#define pin_PF4			    84
#define pin_PF5			    85
#define pin_PF6			    86
#define pin_PF7			    87
#define pin_PF8			    88
#define pin_PF9			    89
#define pin_PF10			90
#define pin_PF11			91
#define pin_PF12			92
#define pin_PF13			93
#define pin_PF14			94
#define pin_PF15			95
#define pin_PG0			    96
#define pin_PG1			    97
#define pin_PG2			    98
#define pin_PG3			    99
#define pin_PG4			    100
#define pin_PG5			    101
#define pin_PG6			    102
#define pin_PG7			    103
#define pin_PG8			    104
#define pin_PG9			    105
#define pin_PG10			106
#define pin_PG11			107
#define pin_PG12			108
#define pin_PG13			109
#define pin_PG14			110
#define pin_PG15			111
#define pin_PH0			    112
#define pin_PH1			    113
#define pin_PH2			    114
#define pin_PH3			    115
#define pin_PH4			    116
#define pin_PH5			    117
#define pin_PH6			    118
#define pin_PH7			    119
#define pin_PH8			    120
#define pin_PH9			    121
#define pin_PH10			122

/* Pad Configuration Registers (PCR0...PCR122) */
/* ------------------------------------------- */

/* PA[1:0] Pad Output Assignment */
#define PA_GPIO			(T_UWORD)(0x0000)		/* 00: Alternative Mode 0: GPIO */
#define PA_AM1			(T_UWORD)(0x0400)		/* 01: Alternative Mode 1 */
#define PA_AM2			(T_UWORD)(0x0800)		/* 10: Alternative Mode 2 */
#define PA_AM3			(T_UWORD)(0x0C00)		/* 11: Alternative Mode 3 */


/* WPS: Weak Pull Up/Down Select */
#define WPS_PULL_UP			1
#define WPS_PULL_DOWN		0

/* ========================================================================== *
 *                                    PIN APIs                                *
 * ========================================================================== */

/* PIN Configuration APIs */
/* ---------------------- */

/* >>>> Pin Function select */
/* Select Pin Function: configure it either as GPIO or an Alternate function */
#define IO_SetPinFctn(pinPcr,function)			( {SIU.PCR[(pinPcr)].R &= 0xF3FF; /* Clear bits. For function values see PA_GPIO, PA_AMx defines */ \
            									   SIU.PCR[(pinPcr)].R |= ((function) & 0x0C00);} )	/* Set bits with new value */

/* >>>> Pin Direction */
/* Set Pin as Input (GPIO) */
#define IO_SetPinAsInput(pinPcr)				( SIU.PCR[(pinPcr)].B.IBE = TRUE )		/* Write bit IBE with 1 */
/* Set Pin as Output (GPIO) */
#define IO_SetPinAsOutput(pinPcr)				( SIU.PCR[(pinPcr)].B.OBE = TRUE )		/* Write bit OBE with 1 */
/* Set Pin as both Input and Output (GPIO) */
#define IO_SetPinAsInOut(pinPcr)				( {SIU.PCR[(pinPcr)].B.IBE = TRUE ); SIU.PCR[(pinPcr)].B.OBE = TRUE;} )		/* Write bits IBE and OBE with 1 */
/* Set port in tristate (Clear IBE and OBE bits) */
#define IO_SetPinDirReset(pinPcr)				( SIU.PCR[(pinPcr)].R &= 0xFCFF )		/* Clear bits IBE and ODE */

/* >>>> Pin Properties */
/* Pin Open Drain Output Enable  */
#define IO_PinOpenDrainEnable(pinPcr, value)	( SIU.PCR[(pinPcr)].B.ODE = (value) )	/* 'value' options are TRUE or FALSE */
/* Pin Weak Pull Up/Down Enable */
#define IO_PinPullUpDownEn(pinPcr, value)		( SIU.PCR[(pinPcr)].B.WPE = (value) )	/* 'value' options are TRUE or FALSE */
/* Weak Pull Up/Down Select */
#define IO_PinPullSelect(pinPcr, value)			( SIU.PCR[(pinPcr)].B.WPE = (value) )	/* See WPS register field defines for 'value' options  */

/* GPIO PIN Access (Read/Write) APIs */
/* --------------------------------- */

/* Read Pin (GPIO) */
#define IO_PinRead(pinPcr)						( SIU.GPDI[(pinPcr)].B.PDI )
/* Write Pin (GPIO) */
#define IO_PinWrite(pinPcr, value)				( SIU.GPDO[(pinPcr)].B.PDO = (value) )

#endif