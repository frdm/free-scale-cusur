/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            APPKnob.c
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Source file for Application layer for KNOB                   */
/*============================================================================*/
/* FUNCTION COMMENT : Describes the functions for Application Layer for KNOB  */
/* Include the state machine for KNOB                                         */
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
#include "APPKnob.h"
#include "HALKnob.h"


void SM_KNOB(E_SM_KNOB e_sm_knob);

void SM_KNOB(E_SM_KNOB e_sm_knob)
{
	switch(e_sm_knob)
	{
		case INIT_KNOB:
		{
			KNOB_Init();
			break;
		}
		case READ_REQUEST:
		{
			KNOB_SendReadRequest();			
			break;
		}
		case GET_KNOB_VALUE:
		{
			KNOB_GetKnobValue();
			break;
		}
		default:
			break;
	}
}