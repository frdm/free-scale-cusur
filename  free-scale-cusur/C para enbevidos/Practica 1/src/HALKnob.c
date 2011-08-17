/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            HALKnob.c
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Source file for Abstraction layer for KNOB                   */
/*============================================================================*/
/* FUNCTION COMMENT : Describes the functions for Abstraction Layer for KNOB  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 11/ago/2011 |                               | Continental      */
/* Initial version for the Smart Car Race 2010 contest using Freescale        */
/* Bolero micro.                                                              */
/*============================================================================*/

#include "stdtypedef.h"
#include "sysinit.h"
#include "MALioapi.h"
#include "MALbeMIOS.h"
#include "MALADC.h"
//#include "MALPWM.h"



void KNOB_Init(void);
void KNOB_SendReadRequest(void);
T_UWORD KNOB_GetKnobValue(void);
bool KNOB_ReadDone(void);


void KNOB_Init(void)
{
	IO_SetPinFctn(pin_PB8,PA_GPIO);	//Configure 
	ConfigPinAs_ADC_Channel(pin_PB8);
	Config_ADC_Mode(SCAN);
	JustifiedADCread(RIGHT);
	SetAmountOfChannels(0,1,0);
	SetConvertionTime(0,_32_MHz,0);	
}

void KNOB_SendReadRequest(void)
{
	ADCStartConvertion();
}

T_UWORD KNOB_GetKnobValue(void)
{
	return ADCReadValue(ANS_0);
}

bool KNOB_ReadDone(void)
{
	return ADCConvertionComplete();
}