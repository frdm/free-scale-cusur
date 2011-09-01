/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            beMIOS.h
* version:         1.0
* created_by:      Carlos Calvillo
* date_created:    May 17 2010
*=============================================================================*/
/* DESCRIPTION : Header file for basic handling of eMIOS peripheral           */
/*============================================================================*/
/* FUNCTION COMMENT : Provides exported functions and symbols for basic       */
/* handling of eMIOS functionalities.                                         */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/may/2010 |                               | Carlos Calvillo  */
/* Initial version for the Smart Car Race 2010 contest using Freescale        */
/* Bolero micro.                                                              */
/*============================================================================*/
#ifndef BEMIOS_H                                 /* To avoid double inclusion */
#define BEMIOS_H

/* Includes */
/* -------- */
#include "stdtypedef.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */

/* typedef */

/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */

/* WORD constants */

/* LONG and STRUCTURE constants */

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */

/* WORD RAM variables */

/* LONG and STRUCTURE RAM variables */

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* ========================================================================== *
 *                               EMIOS defines                                *
 * ========================================================================== */

/* eMIOS Module Configuration Register (EMIOSMCR) */
/* ---------------------------------------------- */

/* MDIS : Module Disable */
#define MDIS_ON            0x04000000l /* 1 = Enter low power mode */
#define MDIS_OFF         0x00000000l /* 0 = Clock is running */
/* GTBE : Global Time Base Enable */
#define GTBE_ON            0x01000000l /* 1 = Global Time Base Enable Out signal asserted */
#define GTBE_OFF         0x00000000l /* 0 = Global Time Base Enable Out signal negated */
/* GPREN : Global Prescaler Enable */
#define GPREN_ON         0x01000000l /* 1 = Prescaler enabled */
#define GPREN_OFF         0x00000000l /* 0 = Prescaler disabled (no clock) and prescaler counter is cleared */
/* GPRE[0:7] : Global Prescaler */
#define GPRE_SET(value)      (T_ULONG)(((value) & 0x0000000fl) << 8)  /* Prescaler value could go from 0 to 
                                                      255 which means clock divider from 1 to 256 */

/* Application specific defines */
typedef enum
{
   PWM_DC_INC,
   PWM_DC_DEC,
   PWM_DC_SET   
}E_PWM_DC_CHM;   /* PWM duty cycle Change mode */


/* ========================================================================== *
 *                               PIT Timers defines                           *
 * ========================================================================== */
 
#define PIT_EnablePITchannel(channel, value)            (PIT.CH[(channel)].TCTRL.B.TEN = (value))
#define PIT_EnablePITinterrupt(channel, value)            (PIT.CH[(channel)].TCTRL.B.TIE = (value))
#define PIT_InterruptAck(channel)                      (PIT.CH[(channel)].TFLG.B.TIF = TRUE)

/* Functions prototypes */
extern void beMIOS_initEMIOS0(void);
extern void beMIOS_initEMIOS0_ch23(void);
extern void beMIOS0_setPWMBdutyCycle(T_UBYTE lub_channel, E_PWM_DC_CHM le_changeMode, T_UWORD luw_steps);
extern void beMIOS0_PITinit(void);
extern void beMIOS0_PITch0_init(void);

#endif