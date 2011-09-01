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

#include "beMIOS.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */


/* Defines for the PWM duty cycle handling */
/* --------------------------------------- */

/* Maximum configured value for the UChannel B register used for the PWM. */
#define PWM_DC_MAX_PERIOD_VAL		(0xFFFF)

/* Maximum allowed Duty Cycle in percentage */
#define PWM_DC_MAX_PERCENTAGE		100u	/* 100 means 100% */

/* Inidicates the number of counts that corresponds to a 1% of the duty cycle for the
 * defined PWM_DC_MAX_PERIOD_VAL */
#define PWM_DC_STEPS_VAL			655u 	/* This symbol should be approximately equal to (PWM_DC_MAX_PERIOD_VAL/PWM_DC_MAX_PERCENTAGE) */

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
void beMIOS0_PITch0_installISR(void);
extern void beMIOS0_PITch0_ISR(void);

/* Exported functions */
/* ------------------ */

/**************************************************************
 *  Name                 : beMIOS_initEMIOS0
 *  Description          : Initialize eMIOS0.
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void beMIOS_initEMIOS0(void)
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
 *  Name                 : beMIOS_initEMIOS0_ch23
 *  Description          : Initialize eMIOS0 channel 23.
 *  Parameters           :  none.
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void beMIOS_initEMIOS0_ch23(void)
{
	/* Ensure that Channel is Enabled */
	EMIOS_0.UCDIS.B.CHDIS23 = FALSE;
	
	/* Configure Channel 23 Paramenters */
	/* -------------------------------- */ 
		/* Set Registers A and B for this channel */
	EMIOS_0.CH[23].CADR.R = 0x7FFF;      /* Initial duty cycle is equal to 50% */
  	EMIOS_0.CH[23].CBDR.R = 0xFFFF;      /* Register B is set at its maximum value in order to 
  	                                      * control PWM duty cycle just with register A */                             	
	/* Set eMIOS0 Channel 23 prescaler (clock division is equal to the UCPRE value + 1) */
	EMIOS_0.CH[23].CCR.B.UCPRE = 0;	/* Clock prescaler of 11 for this channel */
	/* Enable clock prescaler for this channel */
	EMIOS_0.CH[23].CCR.B.UCPEN = TRUE;
	/* Select Internal Counter */
	EMIOS_0.CH[23].CCR.B.BSL = 0x0; 
	/* Select Channel mode */
	EMIOS_0.CH[23].CCR.B.MODE = 0x60;	
}

/**************************************************************
 *  Name                 :  beMIOS0_setPWMBdutyCycle
 *  Description          :  If eMIOS0 channel passed as parameter is configured as a 
 *							OPWMB (Buffered Output Pulse Width Modulation), register B of
 *							the channel its set at its maximum value and Duty Cycle is just 
 *							controlled by register A value. Then this function changes the
 *							duty cycle of the PWM.
 *  Parameters           :  [Input] lub_channel -> working eMIOS0 channel. Allowed values are 0-27.
 *							[Input] luw_steps -> Amount of percentage to change the Duty Cycle (D.C.).
 *									Allowed values are: 0-100.
 *							[Input] le_changeMode -> Way to change the Duty Cycle (D.C:), 
 *									Allowed values are:
 *							   	  	  PWM_DC_INC: D.C. is incremented in the percentage specified by parameter luw_steps.
 *							   	  		      For example if current D.C. is at 50% and luw_steps is 11, new duty cycle will
 *								   	  		      be 61%.
 *									  PWM_DC_DEC: D.C. is decremented in the percentage specified by parameter luw_steps.
 *									  			  For example if current D.C. is at 50% and luw_steps is 11, new duty cycle will
 * 								   	  		      be 39%.
 *									  PWM_DC_SET: D.C. is directly set to the percentage specified by parameter luw_steps.
 *									  			  For example if current D.C. is at 50% and luw_steps is 11, new duty cycle will
 * 								   	  		      be 11%.
 *  Return               :  none
 *  Critical/explanation :  Channel specified by parameter lub_channel must be already initialized and it must be configured 
 *							as a OPWMB and register B must be set at its maximum value.
 **************************************************************/
void beMIOS0_setPWMBdutyCycle(T_UBYTE lub_channel, E_PWM_DC_CHM le_changeMode, T_UWORD luw_steps)
{
	T_UWORD luw_currRegAvalue;
	T_UWORD luw_tempIntCalc;

    if(luw_steps <= PWM_DC_MAX_PERCENTAGE)
	{
		if(le_changeMode == PWM_DC_SET)
		{
			/* Set directly the duty cycle to the selected percentage */
			if(luw_steps == PWM_DC_MAX_PERCENTAGE)
			{
				EMIOS_0.CH[lub_channel].CADR.R = PWM_DC_MAX_PERIOD_VAL;	
			}
			else if(luw_steps == 0)
			{
				EMIOS_0.CH[lub_channel].CADR.R = 0;	
			}
			else
			{
				EMIOS_0.CH[lub_channel].CADR.R = (luw_steps * PWM_DC_STEPS_VAL);	
			}
			
				
		}
		else if(le_changeMode == PWM_DC_INC)
		{
			/* Increase current duty cycle percentage in the amount of steps indicated.
			 * If steps to be incremented are greather than 100% duty cycle will be set as 100%. */
			luw_currRegAvalue = EMIOS_0.CH[lub_channel].CADR.R;
			
			luw_tempIntCalc = (luw_steps * PWM_DC_STEPS_VAL);
			
			if((T_ULONG)((T_ULONG)luw_currRegAvalue + (T_ULONG)luw_tempIntCalc) > (T_ULONG)PWM_DC_MAX_PERIOD_VAL)
			{
				/* Select maximum slot */
				EMIOS_0.CH[lub_channel].CADR.R = PWM_DC_MAX_PERIOD_VAL;
			}
			else
			{
				EMIOS_0.CH[lub_channel].CADR.R += luw_tempIntCalc;	
			}	
		}
		else if(le_changeMode == PWM_DC_DEC)
		{
			/* Decrease current duty cycle percentage in the amount of steps indicated.
			 * If steps to be decremented are less than 0% duty cycle will be set as 0%. */
			luw_currRegAvalue = EMIOS_0.CH[lub_channel].CADR.R;
			
			luw_tempIntCalc = (luw_steps * PWM_DC_STEPS_VAL);
			
			if(luw_tempIntCalc >= luw_currRegAvalue)
			{
				/* Select minimum slot */
				EMIOS_0.CH[lub_channel].CADR.R = 0;
			}
			else
			{
				/*  */
				EMIOS_0.CH[lub_channel].CADR.R -= luw_tempIntCalc;	
			}	
		}
		else
		{
			/* Incorrect le_changeMode argument */	
		}	
	}	
}

