/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            MALADC.h
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Header file for uC Abstraction layer for ADC                 */
/*============================================================================*/
/* FUNCTION COMMENT : Header file uC Abstraction layer for ADC                */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 11/ago/2011 |                               | Continental      */
/* Initial version for the Smart Car Race 2010 contest using Freescale        */
/* Bolero micro.                                                              */
/*==========================================================================*/
#ifndef MALADC_H                               /* To avoid double inclusion */
#define MALADC_H

/* Register definitions for selected microcontroller */
#include "MPC5604B_M27V.h"

#define LEFT	0
#define RIGHT	1

#define ONE_SHOOT	0
#define SCAN		1

#define _32_MHz		0x00008606

#define ANS_0	32
#define ANS_1	33
#define ANS_2	34
#define ANS_3	35
#define ANS_4	36
#define ANS_5	37
#define ANS_6	38
#define ANS_7	39
#define ANS_8	40
#define ANS_9	41
#define ANS_10	42
#define ANS_11	43
#define ANS_12	44
#define ANS_13	45
#define ANS_14	46
#define ANS_15	47

extern void ConfigPinAs_ADC_Channel(T_UBYTE lub_Port);
extern void Config_ADC_Mode(T_UBYTE lub_mode);
extern void JustifiedADCread(T_UBYTE lub_justified);
extern void SetAmountOfChannels(T_ULONG luw_channels0,T_ULONG luw_channels1,T_ULONG luw_channels2);
extern void SetConvertionTime(T_ULONG lul_channels0,T_ULONG lul_channels1,T_ULONG lul_channels2);
extern void ADCStartConvertion(void);
extern bool	ADCConvertionComplete(void);
extern T_UWORD	ADCReadValue(T_UBYTE lub_pin);

#endif