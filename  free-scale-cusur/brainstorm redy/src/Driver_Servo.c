/*!
	  \file     Driver_Servo.c
	  \brief    The driver for the servo motor, it includes initialization of
	  			counters and channels, and a function that sets the servo motor
	  			at a specified position.
	  \author   Cuauhtli Padilla
	  \author   Rodrigo Mendoza
	  \author   Marco Trujillo
	  \date     July 16 2010	  
*/

#include "MPC5604B_0M27V_0102.h"
#include "Driver_MPC5604B.h"
#include "Driver_EMIOS.h"
#include "Driver_SIU.h"

/****************** Definitions ******************************/
#define SERVO_CTRL			22					
#define SERVO_CTRL_PCR		PCR_EMIOS_0_22		/* PE6 */

#define SERVO_MIN_US		1100				/* Min val in microseconds */
#define SERVO_MAX_US		1880			/* Max val in microseconds */

#define SERVO_MCB_CHANNEL	16
#define MOTOR_MCB_CHANNEL	8
/*************************************************************/


/****************** Global Variables *************************/
int16_t i16Pos;				/* The position of the servo from -100 to 100 */
/*************************************************************/


/****************** Functions ********************************/
void vfnSet_Servo(uint16_t u16Position, uint16_t u16MinVal, uint16_t u16MaxVal)  /* Values are between u16MinVal and u16MaxVal*/
{   
	if(u16Position<u16MinVal || u16Position>u16MaxVal)
	{
		//dont do a thing biatch
	}
	else
	{
		uint16_t u16Duty;      
		u16Duty = (uint16_t)(((u16Position - u16MinVal) * (SERVO_MAX_US - SERVO_MIN_US)) / (u16MaxVal - u16MinVal) + SERVO_MIN_US); 
		
		i16Pos = (int16_t)(((u16Position - u16MinVal) * 200) / (u16MaxVal - u16MinVal)) - (int16_t)(100);
		vfnSet_Duty_Opwm(SERVO_CTRL,u16Duty); 
	}
}

void vfnInit_Servo(void)
{
	vfnSetup_Emios_0();
	vfnInit_Emios_0();   
	  					
  	vfnInit_Emios_0_Mcb(SERVO_MCB_CHANNEL,20000); 							/* Set channel as MCB  */	
  	vfnInit_Emios_0_Mcb(MOTOR_MCB_CHANNEL,5000); 							/* Set channel as MCB  */	
  	
  	vfnInit_Emios_0_Opwm(SERVO_CTRL,0,1000);				/* Set channel as OPWM */
	vfnInit_Emios_Output_Pad(SERVO_CTRL_PCR);				/* Set as output in SIU */
}
/*************************************************************/