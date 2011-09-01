/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            MALbeMIOS.h
* version:         1.0
* created_by:      Carlos Calvillo
* date_created:    May 17 2010
*=============================================================================*/
/* DESCRIPTION : Source file for basic handling of eMIOS peripheral           */
/*============================================================================*/
/* FUNCTION COMMENT : Provides code for basic handling of eMIOS               */
/* functionalities.                                                           */
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

/* Includes */
/* -------- */
#include "stdtypedef.h"

#include "MALbeMIOS.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */


/* Defines for the PWM duty cycle handling */
/* --------------------------------------- */


/*==================================================*/ 
/* Definition of constants                          */
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

/* Private defines */

/* Private functions prototypes */
/* ---------------------------- */

/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */

/* Private functions */
/* ----------------- */
void MALbeMIOS0_PITch0_installISR(void);
extern void MALbeMIOS0_PITch0_ISR(void);

/* Exported functions */
/* ------------------ */

/**************************************************************
 *  Name                 : MALbeMIOS_initEMIOS0
 *  Description          : Initialize eMIOS0.
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void MALbeMIOS_initEMIOS0(void)
{
	/* MCR register */
	/* Ensure that eMIOS0 is not disabled */
	EMIOS_0.MCR.B.MDIS = 0; 
	/* Set eMIOS0 prescaler (clock division is equal to the GPRE value + 1) */
	EMIOS_0.MCR.B.GPRE = 63; /* 63 means a clock division of 64. If System clock is 64 MHz, eMIOS0 clock will be 1 MHz */ 
	/* Enable prescaler for eMIOS0 */
	EMIOS_0.MCR.B.GPREN = TRUE;
	/* */ 
	EMIOS_0.MCR.B.GTBE = TRUE;
	
	EMIOS_0.MCR.B.FRZ = 1;
}

/**************************************************************
 *  Name                 : MALbeMIOS_initEMIOS0_ch23
 *  Description          : Initialize eMIOS0 channel 23.
 *  Parameters           :  none.
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void MALbeMIOS_initEMIOS0_ch23(void)
{
	/* Ensure that Channel is Enabled */
	EMIOS_0.UCDIS.B.CHDIS23 = FALSE;
	
	/* Configure Channel 23 Paramenters */
	/* -------------------------------- */ 
		/* Set Registers A and B for this channel */
	EMIOS_0.CH[23].CADR.R = 0x2710;//This value indicates the value to make the change (Duty cycle)
  	EMIOS_0.CH[23].CBDR.R = 0x4E20;//This Register indicates the Value for period
  								   /* Register B is set at its maximum value in order to 
  	                               /* control PWM duty cycle just with register A */                             	
	/* Set eMIOS0 Channel 23 prescaler (clock division is equal to the UCPRE value + 1) */
	EMIOS_0.CH[23].CCR.B.UCPRE = 0;	/* Clock prescaler of 1 for this channel */
	/* Enable clock prescaler for this channel */
	EMIOS_0.CH[23].CCR.B.UCPEN = TRUE;
	/* Select Internal Counter */
	EMIOS_0.CH[23].CCR.B.BSL = 0x0; 
	/* Select Channel mode */
 	EMIOS_0.CH[23].CCR.B.MODE=0x58;	//Configure as Output Pulse Width and Frequency Modulation Buffered
}


