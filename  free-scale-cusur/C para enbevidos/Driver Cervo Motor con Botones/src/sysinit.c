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
void System_Init(void);
void initModesAndClock(void);
void disableWatchdog(void);
void initPeriClkGen(void);

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
/**************************************************************
 *  Name                 :  System_Init
 *  Description          :  This function initialize all the system(Mode and Clock)
 *  Parameters           :  None
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void System_Init(void)
{
	/* Mode initializations */
	sysinit_InitMode();
	/* -------------------- */
	
	
	/* Clock initializations */
	sysinit_InitSysClock();
	/* --------------------- */
	  initModesAndClock();    /* Initialize mode entries and system clock */
  disableWatchdog();      /* Disable watchdog */
  initPeriClkGen();       /* Initialize peripheral clock generation for DSPIs */
}
void initModesAndClock(void) {
  ME.MER.R = 0x0000001D;          /* Enable DRUN, RUN0, SAFE, RESET modes */
                                  /* Initialize PLL before turning it on: */
  CGM.FMPLL_CR.R = 0x02400100;    /* 8 MHz xtal: Set PLL0 to 64 MHz */   
  ME.RUN[0].R = 0x001F0074;       /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
  ME.RUNPC[1].R = 0x00000010;      /* Peri. Cfg. 1 settings: only run in RUN0 mode */
  ME.PCTL[32].R = 0x01;          /* MPC56xxB/P/S ADC 0: select ME.RUNPC[1] */   
  ME.PCTL[68].R = 0x01;          /* MPC56xxB/S SIU: select ME.RUNPC[1] */   
                                  /* Mode Transition to enter RUN0 mode: */
  ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
  ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  
  while (ME.GS.B.S_MTRANS) {}     /* Wait for mode transition to complete */    
                                  /* Note: could wait here using timer and/or I_TC IRQ */
  while(ME.GS.B.S_CURRENTMODE != 4) {} /* Verify RUN0 is the current mode */
}
void disableWatchdog(void) {
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}        

void initPeriClkGen(void) {
/* Use the following code as required for MPC56xxB or MPC56xxS:*/
  CGM.SC_DC[2].R = 0x80;   /* MPC56xxB/S: Enable peri set 3 sysclk divided by 1 */
}