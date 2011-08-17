/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            MALADC.c
* version:         1.0
* created_by:      Continental
* date_created:    Ago 11 2011
*=============================================================================*/
/* DESCRIPTION : Source file for uC Abstraction layer for ADC                 */
/*============================================================================*/
/* FUNCTION COMMENT : Describes the functions for uC Abstraction Layer for ADC*/
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
#include "MALADC.h"

void ConfigPinAs_ADC_Channel(T_UBYTE lub_Port);
void Config_ADC_Mode(T_UBYTE lub_mode);
void JustifiedADCread(T_UBYTE lub_justified);
void SetAmountOfChannels(T_ULONG lul_channels0,T_ULONG lul_channels1,T_ULONG lul_channels2);
void SetConvertionTime(T_ULONG lul_channels0,T_ULONG lul_channels1,T_ULONG lul_channels2);
void ADCStartConvertion(void);
bool ADCConvertionComplete(void);
T_UWORD	ADCReadValue(T_UBYTE lub_pin);

void ConfigPinAs_ADC_Channel(T_UBYTE lub_Port)
{
	SIU.PCR[lub_Port].B.SME = 0;
/* SMC Safe Mode Control
   This bit supports the overriding of the automatic deactivation of the output buffer of the associated
   pad upon entering SAFE mode of the device.
   1: In SAFE mode, the output buffer remains functional.
   0: In SAFE mode, the output buffer of the pad is disabled. */

   SIU.PCR[lub_Port].B.APC = 1;
/* APC Analog Pad Control
   This bit enables the usage of the pad as analog input.
   1: Analog input path switch can be enabled by the ADC
   0: Analog input path from the pad is gated and cannot be used */

   SIU.PCR[lub_Port].B.PA = 0x00;
/* PA[1:0] Pad Output Assignment
   This field is used to select the function that is allowed to drive the output of a multiplexed pad.
   00: Alternative Mode 0 — GPIO
   01: Alternative Mode 1 — See the signal description chapter
   10: Alternative Mode 2 — See the signal description chapter
   11: Alternative Mode 3 — See the signal description chapter */

   SIU.PCR[lub_Port].B.OBE = 0;
/* OBE Output Buffer Enable
   This bit enables the output buffer of the pad in case the pad is in GPIO mode.
   1: Output buffer of the pad is enabled when PA[1:0] = 00
   0: Output buffer of the pad is disabled when PA[1:0] = 00 */

   SIU.PCR[lub_Port].B.IBE = 0;
/* IBE Input Buffer Enable
   This bit enables the input buffer of the pad.
   1: Input buffer of the pad is enabled
   0: Input buffer of the pad is disabled */

   SIU.PCR[lub_Port].B.ODE = 0;
/* ODE Open Drain Output Enable
   This bit controls output driver configuration for the pads connected to this signal. Either open drain
   or push/pull driver configurations can be selected. This feature applies to output pads only.
   1: Open drain enable signal is asserted for the pad
   0: Open drain enable signal is negated for the pad */

   SIU.PCR[lub_Port].B.SRC = 0;
/* SRC Slew Rate Control
   This field controls the slew rate of the associated pad when it is slew rate selectable. Its usage is
   the following:
   0: (default) Pad configured as slow
   1: Pad is configured as medium or fast (depending on the pad) */

   SIU.PCR[lub_Port].B.WPE = 0;
/* WPE Weak Pull Up/Down Enable
   This bit controls whether the weak pull up/down devices are enabled/disabled for the pad
   connected to this signal.
   1: Weak pull device enable signal is asserted for the pad
   0: Weak pull device enable signal is negated for the pad */

   SIU.PCR[lub_Port].B.WPS = 0;
/* WPS Weak Pull Up/Down Select
   This bit controls whether weak pull up or weak pull down devices are used for the pads connected
   to this signal when weak pull up/down devices are enabled.
   1: Pull up is selected
   0: Pull down is selected */
}
void Config_ADC_Mode(T_UBYTE lub_mode)
{
	ADC.MCR.R = 0x00000000;
	if(lub_mode==ONE_SHOOT)
	{
		ADC.MCR.B.MODE=0;
	}
	else if(lub_mode==SCAN)
	{
		ADC.MCR.B.MODE=1;
	}
	else
	{
		
	}
}
void JustifiedADCread(T_UBYTE lub_justified)
{
	if(lub_justified==LEFT)
	{
		ADC.MCR.B.WLSIDE=1;
	}
	else if(lub_justified==RIGHT)
	{
		ADC.MCR.B.WLSIDE=0;
	}
	else
	{
		
	}
}
void SetAmountOfChannels(T_ULONG lul_channels0,T_ULONG lul_channels1,T_ULONG lul_channels2)
{
	ADC.NCMR[0].R=lul_channels0;
	ADC.NCMR[1].R=lul_channels1;
	ADC.NCMR[2].R=lul_channels2;
}
void SetConvertionTime(T_ULONG lul_channels0,T_ULONG lul_channels1,T_ULONG lul_channels2)
{
	ADC.CTR[0].R=lul_channels0;
	ADC.CTR[1].R=lul_channels1;
	ADC.CTR[2].R=lul_channels2;
}
void ADCStartConvertion(void)
{
	ADC.MCR.B.NSTART=1;
}
bool ADCConvertionComplete(void)
{

	if(ADC.CDR[32].B.VALID==1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
T_UWORD	ADCReadValue(T_UBYTE lub_pin)
{
	return ADC.CDR[lub_pin].B.CDATA;
}