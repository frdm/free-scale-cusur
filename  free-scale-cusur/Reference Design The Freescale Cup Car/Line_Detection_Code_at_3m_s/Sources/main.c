/* MAIN.C */

#include "MPC5604B_0M27V_0102.h"
#include "Driver_ADC.h"
#include "Driver_SIU.h"
#include "Driver_PIT.h"
#include "Driver_INTC.h"
#include "Setup.h"
#include "Driver_MPC5604B.h"
#include "MiniTS.h"
#include "main.h"

#define DEBUG				//habilitate this line if debug is necessary


/**
  \brief	returns the minimum average value of the position of
  			the lowest ADC value of the NUMBER_OF_LINES	lines requested
  \param  	set: the number of the set of lines from 0 to 2 (top, middle, low)
  \return	average
*/
uint8_t getMin(uint8_t set)
{
	uint32_t minPixel;		//reading variable
	uint8_t  minPos;		//position of line
	
	uint32_t pixelScan;		//temporary variable
	uint8_t  averageMin=0;	//average of positions
	
	uint8_t a,i;			//indexes
	
	for(a=set*NUMBER_OF_LINES;a<(set+1)*NUMBER_OF_LINES;a++)
	{
		for(i=0;i<50;i++)
		{
			if(pixelScan=u32GetPixel(a,i)>BLACK_LEVEL_THRES)
			{
				if(pixelScan<minPixel)
				{
					minPixel=pixelScan;
					minPos=i;
				}
			}
		}
		averageMin+=minPos;
	}
	averageMin/=NUMBER_OF_LINES;
	
	return averageMin;
}

/** MAIN ... :) */
void main (void) {	

	uint8_t calculate=1;
	uint8_t center[3];
	uint32_t adcval;
		
	#ifdef DEBUG
	uint8_t times;
	#endif
		
	vfnInit_All();  

	vfnInit_Adc_Pad(PCR_ADC_ANP1);
	vfnInit_NormalConversion_Adc(ADC_PRECISION_CHANNEL,ADC_CHANNEL_ANP1);

	vfnInit_Adc_Pad(PCR_ADC_ANP0);
	vfnInit_NormalConversion_Adc(ADC_PRECISION_CHANNEL,ADC_CHANNEL_ANP0);
	vfnInit_Gpio_Out(GPIO_PIN_G0);
	
	//vfnInit_MiniTS ();
	
	vfnInit_Servo(); 		//for servo
	
	/* Aquí va el código de interpretación */
	while(TRUE)
	{
		while(!ADC.CDR[0].B.VALID);
		adcval=ADC.CDR[0].B.CDATA;
		if(adcval<512)
		{
			vfnSet_Gpio(GPIO_PIN_G0,0);			
		}
		else
		{
			vfnSet_Gpio(GPIO_PIN_G0,1);	
		}
			
		if(boolGetOnVerticalSync()&calculate)
		{
			
			#ifdef DEBUG
			times++;
			if(times>5)
			{
			times=0;
			#endif
			
			center[0]=getMin(0);//top
			center[1]=getMin(1);//middle
			center[2]=getMin(2);//botton
			
			vfnSet_Servo(center[1],1,45);
				
			#ifdef DEBUG
			}
			#endif
		}
		else
		{
			calculate=1;
		}
	}
	
}