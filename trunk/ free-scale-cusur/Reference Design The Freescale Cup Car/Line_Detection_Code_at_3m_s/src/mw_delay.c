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
/* DESCRIPTION : Timers handling                                              */
/*============================================================================*/
/* FUNCTION COMMENT : Provices APIs to configure and use Timers of PIC micro  */
/*                                                                            */
/*                                                                            */
/*============================================================================*/

//#include "typedefs.h"
#include "stdtypedef.h"
#include "mw_delay.h"

T_UWORD ruw_TimerCounter = 0;
T_UWORD ruw_DelayControl[] = {0, 0, 0, 0, 0};


/* APIs */
/**************************************************************
 *  Name                 : StartDelay
 *  Description          : Initialize Timer 0
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void mw_delay_StartDelay( T_UBYTE lub_DelayNum )
{
    ruw_DelayControl[lub_DelayNum] = ruw_TimerCounter;
}

/**************************************************************
 *  Name                 : StopDelay
 *  Description          : Stop Timer 0
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void mw_delay_StopDelay( T_UBYTE lub_DelayNum )
{
    ruw_DelayControl[lub_DelayNum] = 0;
}


/**************************************************************
 *  Name                 : IsExpiredDelay
 *  Description          : Returns if the delay has expired
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
T_UBYTE mw_delay_IsExpiredDelay( T_UBYTE lub_DelayNum, T_UWORD luw_DelayValue )
{
    T_UWORD luw_tempvalue = 0;
	T_UBYTE lub_returnvalue = 0;

    if ( ruw_DelayControl[lub_DelayNum] > ruw_TimerCounter )
	{
	    luw_tempvalue = (T_UWORD)(0xFFFF - ruw_DelayControl[lub_DelayNum] + ruw_TimerCounter);
	}
	else
	{
	    luw_tempvalue = (T_UWORD)(ruw_TimerCounter - ruw_DelayControl[lub_DelayNum]);
	}

    if (luw_tempvalue > luw_DelayValue) /* Delay value is in 10ms resolution */
	{
	    lub_returnvalue = TRUE;
		ruw_DelayControl[lub_DelayNum] = 0;
	}
	else
	{
	    lub_returnvalue = FALSE;
    }

	return lub_returnvalue;
}

/**************************************************************
 *  Name                 : IsRunningDelay
 *  Description          : Returns if the delay is running
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
T_UBYTE mw_delay_IsRunningDelay( T_UBYTE lub_DelayNum )
{
	T_UBYTE lub_returnvalue = 0;

    if ( ruw_DelayControl[lub_DelayNum] > 0 )
	{
	    lub_returnvalue = TRUE;
	}
	else
	{
	    lub_returnvalue = FALSE;
    }

	return lub_returnvalue;
}


/**************************************************************
 *  Name                 : DelayManager()
 *  Description          : This is the manager of the delay services
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  No
 **************************************************************/
void mw_delay_DelayManager( void )
{
    if ( ruw_TimerCounter == 0xFFFF )
	{
	    ruw_TimerCounter = 1;
	}
	else
	{
	    ruw_TimerCounter++;
	}
}

