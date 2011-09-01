/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            MALPWM.h
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Header file for uC Abstraction layer for PWM                 */
/*============================================================================*/
/* FUNCTION COMMENT : Header file uC Abstraction layer for PWM                */
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
#ifndef MALPWM_H                               /* To avoid double inclusion */
#define MALPWM_H

extern void WHEEL_Init(void);
extern void WHEEL_SetWheelPos(void);


#endif