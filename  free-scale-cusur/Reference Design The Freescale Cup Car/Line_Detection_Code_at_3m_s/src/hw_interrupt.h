#ifndef HW_INTERRUPTS_H
#define HW_INTERRUPTS_H
/*============================================================================*/
/*       UNIVERSIDAD DE GUADALAJARA - CONTINENTAL AUTOMOTIVE SYSTEMS          */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* %name:            %
* %version:         %
* %created_by:      %
* %date_created:    %
*=============================================================================*/
/* DESCRIPTION : Interrupts handlers                                          */
/*============================================================================*/
/* FUNCTION COMMENT : Provices APIs to configure and use Timers of PIC micro  */
/*                                                                            */
/*                                                                            */
/*============================================================================*/

/******************************************************************************
*   Include Files
******************************************************************************/ 
#include "IntcInterrupts.h"

/******************************************************************************
*   Macro Definitions  
******************************************************************************/

/*****************************************************************************
 *  Local Macro Definitions
 *****************************************************************************/

/******************************************************************************
*   Type Definitions
******************************************************************************/

/******************************************************************************
*   External Variables
******************************************************************************/

extern IVOR4Handler();
extern uint32_t __IVPR_VALUE; /* Interrupt Vector Prefix value from link file*/

//uint32_t Pit1Ctr = 0;   /* Counter for PIT 1 interrupts */
//uint32_t SWirq4Ctr = 0;/* Counter for software interrupt 4 */

/* Private functions prototypes */
/* ---------------------------- */

/******************************************************************************
*   Global Function Prototypes  
******************************************************************************/

/* Exported prototypes */
extern void hw_interrupt_interrupt_initCfg();
extern void hw_interrupt_Enable_Interrupts();
extern void hw_interrupt_Disable_Interrupts();
extern void hw_interrupt_Tick_Interrupt();

/* prototypes */
void hw_interrupt_interrupt_initCfg();
void hw_interrupt_Enable_Interrupts();
void hw_interrupt_Disable_Interrupts();
void hw_interrupt_Tick_Interrupt( void );

#endif