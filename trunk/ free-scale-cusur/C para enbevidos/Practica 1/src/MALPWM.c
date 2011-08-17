/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            MALPWM.c
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Source file for uC Abstraction layer for PWM                 */
/*============================================================================*/
/* FUNCTION COMMENT : Describes the functions for uC Abstraction Layer for PWM*/
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
#include "MALbeMIOS.h"
#include "MALioapi.h"
#include "MALPWM.h"


void InitPWM(void);

void InitPWM(void)
{
	MALbeMIOS_initEMIOS0();
	
	MALbeMIOS_initEMIOS0_ch23();

	IO_SetPinFctn(pin_PE7,PA_AM1);
}

void SetDutyCycle(T_UWORD luw_DC)
{
	if(luw_DC>1000)
	{
		luw_DC=1000;
	}
	EMIOS_0.CH[23].CADR.R=(luw_DC+1000);
}