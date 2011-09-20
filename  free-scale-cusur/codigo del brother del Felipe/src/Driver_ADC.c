#include "MPC5604B_0M27V_0102.h"
#include "Driver_MPC5604B.h"



/** Set an Adc channel as normal conversion channel **/
void vfnInit_NormalConversion_Adc(uint8_t u8ChannelType,uint32_t u32Channel) 
{
	ADC.MCR.R = 0x20000000;        										/* Initialize ADC0 for scan mode and allow cross triggering */
  	ADC.CTR[u8ChannelType].R = 0x00008606;      						/* Conversion times for 32MHz ADClock */
  	//ADC.MCR.B.ADCLKSEL = 0;
  	ADC.NCMR[u8ChannelType].R = ADC.NCMR[u8ChannelType].R | u32Channel;	/* Set channel mask as normal conversion mask */
  	ADC.MCR.B.NSTART=1;             									/* Start Normal Conversion */  	 	
}

/** Set an Adc channel as a conversion channel for cross trigguering **/
void vfnInit_Adc_Ctu(uint8_t u8ChannelType,uint32_t u32Channel)
{
	ADC.MCR.R = 0x20020000;        										/* Initialize ADC0 for scan mode and allow cross triggering */
  	ADC.CTR[u8ChannelType].R = 0x00008606;      						/* Conversion times for 32MHz ADClock */
  	ADC.NCMR[u8ChannelType].R = ADC.NCMR[u8ChannelType].R | u32Channel;	/* Set channel mask as normal conversion  */
  	ADC.NCMR[u8ChannelType].R = ADC.NCMR[u8ChannelType].R - u32Channel;	/* Unset channel from normal conversion mask */
}
/** Adc channel interrupt request **/
void vfnInit_Adc_Interrupt(uint8_t u8ChannelType,uint32_t u32Channel, uint32_t AdcChannel)
{
  ADC.IMR.B.MSKEOC = 1;
  ADC.CIMR[u8ChannelType].R = u32Channel;  
}

/** AdcWatchDog channel interrupt request low**/
void vfnInit_Adc_WatchdogL(uint8_t u8WtdChannel, uint32_t u32AdcChannel, uint32_t u32LowTreshold)
{
	ADC.THRHLR[u8WtdChannel].B.THRL=u32LowTreshold;
	ADC.TRC[u8WtdChannel].B.THRCH=u32AdcChannel;
	ADC.WTIMR.B.MSKWDG0L=1;
	ADC.TRC[u8WtdChannel].B.THREN=1;
}
/** AdcWatchDog channel interrupt request low2**/
void vfnInit_Adc_WatchdogL2(uint8_t u8WtdChannel, uint32_t u32AdcChannel, uint32_t u32LowTreshold)
{
	ADC.THRHLR[u8WtdChannel].B.THRL=u32LowTreshold;
	ADC.TRC[u8WtdChannel].B.THRCH=u32AdcChannel;
	ADC.WTIMR.B.MSKWDG1L=1;
	ADC.TRC[u8WtdChannel].B.THREN=1;
}

/** AdcWatchDog channel interrupt request high**/
void vfnInit_Adc_WatchdogH(uint8_t u8WtdChannel, uint32_t u32AdcChannel, uint32_t u32HighTreshold)
{
	ADC.THRHLR[u8WtdChannel].B.THRH=u32HighTreshold;
	ADC.TRC[u8WtdChannel].B.THRCH=u32AdcChannel;
	ADC.WTIMR.B.MSKWDG0H=1;
	ADC.TRC[u8WtdChannel].B.THREN=1;
}


/** Read Adc channel in scale from 0 to Maximum Value **/

uint16_t u16Read_Adc(uint8_t u8Channel, uint16_t u16MaximumValue)
{
	uint16_t u16Result;
	
	if (ADC.CDR[u8Channel].B.VALID == 1) 							/* Wait for last scan to complete */  
	{
		u16Result = (uint16_t)ADC.CDR[u8Channel].B.CDATA;					/* Assign ADC scan value to u16Result */
		u16Result = (uint16_t)(u16MaximumValue * u16Result / 1023); 		/* Convert to range from 0 to maximum value */
		return u16Result;
	}
	else
	{
		return 1024;
	}
 				       	
}

/*
uint16_t u16Read_Adc(uint8_t u8Channel, uint16_t u16MaximumValue)
{
	uint16_t u16Result;
	
	while (ADC.CDR[u8Channel].B.VALID != 1) {}							  
	u16Result = (uint16_t)ADC.CDR[u8Channel].B.CDATA;					
	u16Result = (uint16_t)(u16MaximumValue * u16Result / 1023); 		
	return u16Result;		       	
}
*/