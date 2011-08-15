/*============================================================================*/
/*                             Smart Car Race                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* %name:            %
* %version:         %
* %created_by:      %
* %date_created:    %
*=============================================================================*/
/* DESCRIPTION : Ports handling                                               */
/*============================================================================*/
/* FUNCTION COMMENT : Provices APIs to configure and use cpu of PIC micro     */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  |                               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "stdtypedef.h"
#include "mw_delay.h"
#include "app_ports.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 


/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */

/* Private functions prototypes */
/* ---------------------------- */

/* Exported functions prototypes */
/* ----------------------------- */
void app_ports_init(T_UBYTE lub_Port);
void app_port1();
void app_port2();
void app_port3();

/**************************************************************
 *  Name                 : app_initports
 *  Description          : 
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void app_ports_init(T_UBYTE lub_Port)
{
   SIU.PCR[lub_Port].B.SME = 1;
/* SMC Safe Mode Control
   This bit supports the overriding of the automatic deactivation of the output buffer of the associated
   pad upon entering SAFE mode of the device.
   1: In SAFE mode, the output buffer remains functional.
   0: In SAFE mode, the output buffer of the pad is disabled. */

   SIU.PCR[lub_Port].B.APC = 0;
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

   SIU.PCR[lub_Port].B.OBE = 1;
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

   SIU.GPDO[lub_Port].B.PDO = 0;
}

/**************************************************************
 *  Name                 : app_port1
 *  Description          : 
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void app_port1()
{

   SIU.GPDO[PE4].B.PDO ^= 1;
/* PDO[x] Pad Data Out
   This bit stores the data to be driven out on the external GPIO pad controlled by this register.
   1: Logic high value is driven on the corresponding GPIO pad when the pad is configured as an
   output
   0: Logic low value is driven on the corresponding GPIO pad when the pad is configured as an
   output */

}

/**************************************************************
 *  Name                 : app_port2
 *  Description          : 
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void app_port2()
{
   SIU.GPDO[PE5].B.PDO ^= 1;
/* PDO[x] Pad Data Out
   This bit stores the data to be driven out on the external GPIO pad controlled by this register.
   1: Logic high value is driven on the corresponding GPIO pad when the pad is configured as an
   output
   0: Logic low value is driven on the corresponding GPIO pad when the pad is configured as an
   output */

}

/**************************************************************
 *  Name                 : app_port3
 *  Description          : 
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void app_port3()
{
    SIU.GPDO[PE6].B.PDO ^= 1;
    /* PDO[x] Pad Data Out
   This bit stores the data to be driven out on the external GPIO pad controlled by this register.
   1: Logic high value is driven on the corresponding GPIO pad when the pad is configured as an
   output
   0: Logic low value is driven on the corresponding GPIO pad when the pad is configured as an
   output */

}