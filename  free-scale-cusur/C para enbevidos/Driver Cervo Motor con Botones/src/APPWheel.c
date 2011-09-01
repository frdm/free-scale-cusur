/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            APPWheel.c
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Source file for Application layer for WHEEL                  */
/*============================================================================*/
/* FUNCTION COMMENT : Describes the functions for Application Layer for WHEEL */
/* Include the state machine for WHEEL                                        */
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
#include "HWInit.h"
#include "HWInit.h"
#include "APPWheel.h"
#include "HALWheel.h"


void SM_WHEEL(E_SM_WHEEL e_sm_wheel);

void SM_WHEEL(E_SM_WHEEL e_sm_wheel)
{
	switch(e_sm_wheel)
	{
		case INIT_WHEEL:
		{
			WHEEL_Init();
			break;
		}
		case UPDATE_WHEEL_POSITION:
		{
			WHEEL_SetWheelPos();
			break;
		}
		default:
			break;
	}
}