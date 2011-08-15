#ifndef MW_DELAY_H
#define MW_DELAY_H
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
/* DESCRIPTION : Timers handling                                              */
/*============================================================================*/
/* FUNCTION COMMENT : Provices APIs to configure and use Timers of PIC micro  */
/*                                                                            */
/*                                                                            */
/*============================================================================*/

/******************************************************************************
*   Include Files
******************************************************************************/ 
#include "stdtypedef.h"

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

/******************************************************************************
*   Global Function Prototypes  
******************************************************************************/

/* Exported prototypes */
extern void mw_delay_StartDelay( T_UBYTE lub_DelayNum );
extern void mw_delay_StopDelay( T_UBYTE lub_DelayNum );
extern T_UBYTE mw_delay_IsExpiredDelay( T_UBYTE lub_DelayNum, T_UWORD luw_DelayValue );
extern T_UBYTE mw_delay_IsRunningDelay( T_UBYTE lub_DelayNum );
extern void mw_delay_DelayManager( void );


/* prototypes */
void mw_delay_StartDelay( T_UBYTE lub_DelayNum );
void mw_delay_StopDelay( T_UBYTE lub_DelayNum );
T_UBYTE mw_delay_IsExpiredDelay( T_UBYTE lub_DelayNum, T_UWORD luw_DelayValue );
T_UBYTE mw_delay_IsRunningDelay( T_UBYTE lub_DelayNum );
void mw_delay_DelayManager( void );


#endif