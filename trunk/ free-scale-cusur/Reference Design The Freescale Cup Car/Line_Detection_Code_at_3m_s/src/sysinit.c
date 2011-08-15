/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            sysinit.c
* version:         1.0
* created_by:      Carlos Calvillo
* date_created:    May 17 2010
*=============================================================================*/
/* DESCRIPTION : Source file for System Init functionality                    */
/*============================================================================*/
/* FUNCTION COMMENT : Provides code for basic system initializations.         */
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
#include "sysinit.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */



/*==================================================*/ 
/* Definition of constants                 */
/*==================================================*/ 
/* BYTE constants */

/* WORD constants */

/* LONG and STRUCTURE constants */


/*======================================================*/ 
/* Definition of RAM variables                 */
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
void sysinit_ChangeMode(T_ULONG newMode);
void sysinit_disableWatchdog(void);

/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */

/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : sysinit_disableWatchdog
 *  Description          : Disable watchdog
 *  Parameters           :  none.
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void sysinit_disableWatchdog(void) 
{
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}   

/* Exported functions */
/* ------------------ */

/**************************************************************
 *  Name                 : 	sysinit_InitSysClock
 *  Description          : 	Initialize system clock settings.
 *  Parameters           : 	none
 *  Return               : 	none
 *  Critical/explanation : 	Must be called at init phase, It is not intended for
 *							clock changes in normal application operation.
 **************************************************************/
void sysinit_InitSysClock(void)
{
	
	/* Configurations for Output Clock */
	CGM.OC_EN.B.EN = FALSE;
	CGM.OCDS_SC.B.SELDIV = 0;
	CGM.OCDS_SC.B.SELCTL = 0;
	
	/* Configure PLL */
	PLL_SET(0, 2, 64, TRUE);
	
	/* Wait for PLL stabilization */
	while(!CGM.FMPLL_CR.B.S_LOCK){};
	
	/* System Clock Dividers for peripheral groups */
	CGM_CFG_DIV0(TRUE,0);
	CGM_CFG_DIV1(TRUE,0);
	CGM_CFG_DIV2(TRUE,0);
	
	/* Disable watchdog */
	sysinit_disableWatchdog();
}

/**************************************************************
 *  Name                 :  sysinit_InitMode
 *  Description          :  Initialize mode settings and selects RUN0 mode.
 *  Parameters           : 	none
 *  Return               : 	none
 *  Critical/explanation : 	Must be called at init phase, It is not intended for
 *							mode changes in normal application operation.
 **************************************************************/
void sysinit_InitMode(void)
{	
	/* General Mode Configurations */
	/* --------------------------- */
	
	/* Enable desired modes */
	WRITE_ME_ME(ME_RUN0|ME_DRUN|ME_SAFE|ME_RESET);
	/* Mode configurations */
	WRITE_ME_RUN0_MC(MC_PDO_OFF|MC_MVR_ON|MC_DFLA_NORMAL|MC_CFLA_NORMAL|MC_FMPLL_ON|MC_FXOSC_ON|MC_FIRC_ON|MC_SYSCLK_FMPLL);
	
	/* Peripheral mode-related configurations */
	/* -------------------------------------- */
	
	/* Peripheral Configuration 0 */
	WRITE_ME_RUN_PC(0, 0x00000010);
		
	/* Select eMIOS0 to use Peripheral Configuration 0 */
	WRITE_ME_PCTL(PCTL_eMIOS0, 0x0000);
	
	/* Select RUN0 mode */
	sysinit_ChangeMode(MCTL_RUN0);
}

/**************************************************************
 *  Name                 :  sysinit_ChangeMode
 *  Description          :  Changes working mode for the one selected as parameter.
 *  Parameters           :  [Input] lub_newMode -> new mode.
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void sysinit_ChangeMode(T_ULONG lub_newMode)
{
	lub_newMode <<= 28u;
	
	ME.MCTL.R = (lub_newMode | MODE_CHANGE_KEY);
	ME.MCTL.R = (lub_newMode | MODE_CHANGE_INV_KEY);
	
	while (ME.IS.B.I_MTC != 1) {}    /* Wait for mode transition to complete */    
  	ME.IS.B.I_MTC = 1;	              /* Clear Mode Transition Complete flag */	
}

