/*!
	  \file     Driver_Motor.c
	  \brief    The driver for the main motor of the car, includes a velocimeter
	  			to control speed and regulate it, and also a scan for current 
	  			consumed by the motor.
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
/*
	EMIOS CHANNEL		    |	PORT |	PIN
	--------------------------------------------
	Ch16: MCB			    |	     |
	Ch17:                	|	     |	  
	Ch18: OPWMB Enable	    |	PE2  |	128
	Ch19: SAIC  Velocimeter	|	PE3  |	129
	Ch20: GPIO  IN1		    |	PE4  |	132
	Ch21: GPIO  IN2		    |	PE5  |	133
	Ch22: OPWMB Servo motor	|	PE6  |	139
	Ch23:
	
	PIN LAYOUT
  	  _______________
 	/ 144.....109   |
	|01	    	 108|
	|.  O    	 .  |
	|.	     	 .  |
	|.	     	 .  |
	|36	     	 73 |
	|  37......72   |
 	----------------
 */

#define MOTOR_MCB_CHANNEL	16

#define MOTOR_IN_2_PIN		GPIO_PIN_E4				/* PE4 */

#define MOTOR_IN_1_PIN		GPIO_PIN_E5				/* PE5 */

#define MOTOR_NO2			GPIO_PIN_E7				/* PE7 */

#define MOTOR_EN 			18
#define MOTOR_EN_PCR		PCR_EMIOS_0_18			/* PE2 */

#define MOTOR_SENSE_CH		PCR_ADC_ANP11			/* PD7 */

#define VELOCIMETER			19
#define VELOCIMETER_PCR		PCR_EMIOS_0_19			/* PE3 */

#define MAX_CURRENT			1023
#define MIN_CURRENT			0

#define CIRCLE 				(int32_t)190000000 		/* 2*Pi*R*10^6 */

#define CONTROL				300						/* Kc=1/(CONTROL*DELAY) */
#define DELAY				400


#define MOTORS_MCB_CHANNEL	16
/*************************************************************/



/****************** Global Variables *************************/
int16_t i16Power; 		/* The power (in percentage) of the motor */
int32_t i32Period;		/* The measured period between detections of the wheels */
int16_t i16CntrVel;  	/* The last scan of SAIC */
int16_t i16Overflows;	/* Number of overflows of the MCB */
int16_t i16Cntr1;		/* First counter used for DELAY */
int16_t i16Cntr2;		/* Second counter used for DELAY */
uint16_t u16Last;
uint16_t u16Temp;
/*************************************************************/



/**************************************************************************************************************/
/*           								  	USEFUL FUNCTIONS						                      */
/**************************************************************************************************************/

void vfnSet_Motor_Forward(uint16_t u16Perc)
{
	vfnSet_Gpio(MOTOR_IN_1_PIN, HIGH);
	vfnSet_Gpio(MOTOR_IN_2_PIN, LOW);
	
	vfnSet_Duty_Perc_Opwm(MOTOR_EN,u16Perc,MOTOR_MCB_CHANNEL);	/* Normal Polarity */
	
	i16Power = (int16_t)u16Perc;
}

void vfnSet_Motor_Reverse(uint16_t u16Perc)
{
	vfnSet_Gpio(MOTOR_IN_1_PIN, LOW);
	vfnSet_Gpio(MOTOR_IN_2_PIN, HIGH);
	
	vfnSet_Duty_Perc_Opwm(MOTOR_EN,u16Perc,MOTOR_MCB_CHANNEL);	/* Inverted Polarity */
	
	i16Power = (int16_t)(u16Perc);
}

void vfnSet_Motor_Stop(void)
{
	vfnSet_Duty_Perc_Opwm(MOTOR_EN,0,MOTOR_MCB_CHANNEL);	/* Normal Polarity */
	vfnSet_Gpio(MOTOR_IN_1_PIN, HIGH);
	vfnSet_Gpio(MOTOR_IN_2_PIN, HIGH);							/* Stop motor */
	vfnSet_Duty_Perc_Opwm(MOTOR_EN,100,MOTOR_MCB_CHANNEL);	/* Normal Polarity */
	i16Power = 0;
}

void vfnSet_Motor_NO2(uint8_t state)
{	
	vfnSet_Gpio(MOTOR_NO2, state);
}

uint16_t u16Get_Feedback_Current(void)
{
	uint16_t u16Current;
	u16Current = u16Read_Adc(MOTOR_SENSE_CH,MAX_CURRENT);
	return u16Current;
}

void vfnSet_Motor_Velocity(int32_t i32RegulatedVel)
{
	int32_t i32Velocity=CIRCLE/i32Period;
	
	if( (i32RegulatedVel==0) || (i32RegulatedVel>CIRCLE) )  /* Too slow or too fast */
	{
		vfnSet_Motor_Stop();
	}
	else
	{
	/*
		Circumference of wheel (length)
		--------------------------------- =  Measured Velocity (speed)
		    Measured Period (time)
		    
		The units for CIRCLE are nanometers, and the units for i32Period
		are microseconds, so the units for i32Velocity (measured) are
		milimeters/second.
	*/	
	


		if(i32RegulatedVel > i32Velocity)
		{
		 	/* The power must be increased by a small factor:
				the difference of the  desired velocity and the measured velocity
				multiplied by a factor (CONTROL).
				The 16Cntr1 makes this code execute until the DELAY-th time
				to let the power be reduced by the difference multiplied by 
				the factor. So the factor is 1/(DELAY*CONTROL).  */
			if(i16Cntr2>DELAY)
			{
				//i16Power+=1;
				i16Power+=(i32RegulatedVel-i32Velocity)/CONTROL;
				i16Cntr2=0;	
			}
			i16Cntr2++;
			
			/* The power cannot exceed 100% */
			if(i16Power>100)
			{
				i16Power=100;
			}
		}
		else
		{
			/* The power must be reduced by a small factor:
			   the difference of the measured velocity and the desired velocity
			   multiplied by a factor (CONTROL).
			   The 16Cntr1 makes this code execute until the DELAY-th time
			   to let the power be reduced by the difference multiplied by 
			   the factor. So the factor is 1/(DELAY*CONTROL).  */
			if(i16Cntr1>DELAY)
			{
				//i16Power-=1;
				i16Power-=(i32Velocity-i32RegulatedVel)/CONTROL;
				i16Cntr1=0;	
			}
			i16Cntr1++;
			
			/* Desired velocity must be greater than 0
			   so the power for the motor cannot be 0  */
			if(i16Power<1)
			{
				i16Power=1;
			}
		}
		
		/* Set motor forward acording to the power established */
		vfnSet_Motor_Forward(i16Power);
	}
}

void vfnRead_Period(void)
{
	int16_t i16Scan=0;

	
	/* Get the value of the counter when the egde is rised (if not return 0) */
	i16Scan=u16Read_Saic(VELOCIMETER,0,20001);	
	if(i16Scan > 0)
  	{
  		/* The period is the time elapsed in the last scan plus the time
  		   elapsed in between of overflowed up-counters
  		   minus the last scan
  		*/
		i32Period 		=  (int32_t)(i16Scan);
		i32Period		+= (int32_t)(u16Get_Period_Mcb(MOTOR_MCB_CHANNEL) * i16Overflows);
		i32Period		-= (int32_t)(i16CntrVel);
		i16CntrVel		= i16Scan;	/* The actual scan becomes the last scan */
		i16Overflows 	= 0;		/* Reset the number of overflows*/
  	}
  	/* If the number of overflows are too many, then the velocity is practically
  	   zero (which is done by making the period a large number) */
  	if(i16Overflows>10)
  	{
  		i32Period=0x00FFFFFF;
  	}
	
	/* Code for overflows */
	u16Temp=u16Get_Counter(MOTORS_MCB_CHANNEL); 			/* Get counter from channel 16 */
  	if(u16Temp<u16Last)
  	{
  		i16Overflows++;
  	}
  	u16Last=u16Temp;
}

void vfnInit_Motor(void)
{
  	vfnInit_Gpio_Out(MOTOR_IN_1_PIN);						/* Set channel as GPIO */
  	vfnInit_Gpio_Out(MOTOR_IN_2_PIN);						/* Set channel as GPIO */
  	vfnInit_Gpio_Out(MOTOR_NO2);						/* Set channel as GPIO */
  	
  	vfnInit_Emios_0_Opwm(MOTOR_EN,0,1000);					/* Set channel as OPWM */
	vfnInit_Emios_Output_Pad(MOTOR_EN_PCR);					/* Set as output in SIU */
	
  	i32Period=0x00FFFFFF;
  	i16Power = 0;
  	i16Overflows  = 0;
  	u16Last = 0;
	u16Temp = 0;
}
/*************************************************************/