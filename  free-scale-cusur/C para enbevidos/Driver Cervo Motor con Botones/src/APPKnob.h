/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            APPKnob.h
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Header file for application layer for KNOB                   */
/*============================================================================*/
/* FUNCTION COMMENT : Header file application layer for KNOB                  */
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
#ifndef APPKNOB_H                               /* To avoid double inclusion */
#define APPKNOB_H

/* Register definitions for selected microcontroller */
#include "MPC5604B_M27V.h"

typedef enum
{
	INIT_KNOB,
	READ_REQUEST,
	GET_KNOB_VALUE	
}E_SM_KNOB;	/* States for KNOB State Machine */

extern void SM_KNOB(E_SM_KNOB e_sm_knob);

#endif