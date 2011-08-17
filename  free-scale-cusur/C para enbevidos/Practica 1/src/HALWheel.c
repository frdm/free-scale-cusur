/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            HALWheel.c
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Source file for Abstraction layer for WHEEL                  */
/*============================================================================*/
/* FUNCTION COMMENT : Describes the functions for Abstraction Layer for WHEEL */
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
#include "MALPWM.h"
#include "HALKnob.h"

void WHEEL_Init(void);
void WHEEL_SetWheelPos(void);


void WHEEL_Init(void)
{
	InitPWM();
}
void WHEEL_SetWheelPos(void)
{
	SetDutyCycle(KNOB_GetKnobValue());
}
