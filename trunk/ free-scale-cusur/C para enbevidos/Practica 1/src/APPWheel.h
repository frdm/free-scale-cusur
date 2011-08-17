/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            APPWheel.h
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Header file for application layer for Wheel                   */
/*============================================================================*/
/* FUNCTION COMMENT : Header file application layer for Wheel                  */
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
#ifndef APPWHEEL_H                               /* To avoid double inclusion */
#define APPWHEEL_H

/* Register definitions for selected microcontroller */
#include "MPC5604B_M27V.h"

typedef enum
{
	INIT_WHEEL,
	UPDATE_WHEEL_POSITION	
}E_SM_WHEEL;	/* States for Wheel State Machine */

extern void SM_WHEEL(E_SM_WHEEL e_sm_wheel);

#endif