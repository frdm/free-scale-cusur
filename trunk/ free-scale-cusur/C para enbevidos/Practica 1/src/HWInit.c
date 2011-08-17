/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            HWInit.c
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Source file for Hardware initalization                     */
/*============================================================================*/
/* FUNCTION COMMENT : Describes the functions for Hardware  initalizations    */
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
#include "HWInit.h"
#include "APPKnob.h"
#include "APPWheel.h"

void Hardware_Init(void);

void Hardware_Init(void)
{

	SM_KNOB(INIT_KNOB);
	SM_WHEEL(INIT_WHEEL);
}