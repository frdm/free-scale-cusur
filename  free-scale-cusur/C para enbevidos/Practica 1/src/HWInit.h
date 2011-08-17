/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            HWInit.h
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Header file for Hardware initalization                     */
/*============================================================================*/
/* FUNCTION COMMENT : Header file to export functions to other files related  */
/* with hardware initialzations                                               */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 11/ago/2011 |                               | Continental      */
/* Initial version for the Smart Car Race 2010 contest using Freescale        */
/* Bolero micro.                                                              */
/*============================================================================*/
#ifndef HWINIT_H                               /* To avoid double inclusion */
#define HWINIT_H

/* Register definitions for selected microcontroller */
#include "MPC5604B_M27V.h"


extern void Hardware_Init(void);


#endif