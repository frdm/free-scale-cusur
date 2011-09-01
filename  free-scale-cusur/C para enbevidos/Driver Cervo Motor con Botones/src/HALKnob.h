/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            HALKnob.h
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Header file for abstraction layer for KNOB                   */
/*============================================================================*/
/* FUNCTION COMMENT : Header file abstraction layer for KNOB                  */
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
#ifndef HALKNOB_H                               /* To avoid double inclusion */
#define HALKNOB_H

/* Register definitions for selected microcontroller */
#include "MPC5604B_M27V.h"
#include "stdtypedef.h"

extern void KNOB_Init(void);
extern void KNOB_SendReadRequest(void);
extern T_UWORD KNOB_GetKnobValue(void);
extern bool KNOB_ReadDone(void);

#endif