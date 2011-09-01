/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            HALWheel.h
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Header file for abstraction layer for WHEEL                  */
/*============================================================================*/
/* FUNCTION COMMENT : Header file abstraction layer for WHEEL                 */
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
#ifndef HALWHEEL_H                               /* To avoid double inclusion */
#define HALWHEEL_H

/* Register definitions for selected microcontroller */
#include "MPC5604B_M27V.h"
#include "stdtypedef.h"

extern void WHEEL_Init(void);
extern void WHEEL_SetWheelPos(void);

#endif