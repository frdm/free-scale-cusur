/* MINITS.C */

#include "MPC5604B_0M27V_0102.h"
#include "Driver_ADC.h"
#include "Driver_SIU.h"
#include "Driver_PIT.h"
#include "Driver_INTC.h"
#include "Setup.h"
#include "Driver_MPC5604B.h"
#include "MiniTS.h"

// Global Variables
uint16_t	horizLines[50][55];//9+1wtf
uint8_t	ihorizLines;
uint8_t 	iwantedLines;
uint8_t 	pixel;
uint8_t		boolOnVerticalSync;
uint8_t		boolOnHighThresWdg;
uint8_t 	temp;
uint8_t     lineSelect[248];
uint8_t     lineInitializer;

void  initLineSelector(void)
{
	for(lineInitializer=0;lineInitializer<248;lineInitializer++)
	{
		lineSelect[lineInitializer]=0;
	}
}
uint8_t  selectLine(uint8_t line)
{
	lineSelect[line]=TRUE;
}
uint8_t  deSelectLine(uint8_t line)
{
	lineSelect[line]=FALSE;
}
uint8_t  getLineCounter(void)
{
	return ihorizLines;
}
uint8_t  boolGetOnVerticalSync(void)
{
	return boolOnVerticalSync;
}

uint32_t u32GetPixel(uint8_t line, uint8_t position)
{
	return horizLines[line][position];
}

void vfnInit_MiniTS (void)
{		
	ihorizLines=0;
	iwantedLines=0;
	boolOnVerticalSync=TRUE;
}

void readLines(uint8_t tempwanted)
{
	pixel=0;
	
	iwantedLines=tempwanted;
	
	while (!ADC_DATA_READY);			
	horizLines[iwantedLines][pixel]=ADC_DATA;
	
	while((horizLines[iwantedLines][pixel]>HORIZ_SYNC_THRES || pixel<3) && pixel<55)
	{
		pixel++;
		while (!ADC_DATA_READY);			
		horizLines[iwantedLines][pixel]=ADC_DATA;
	}
	//horizLines[iwantedLines][54]=ihorizLines;
	iwantedLines++;
	if(iwantedLines>50)
	{
		iwantedLines=0;
	}
}

void AdcWDGISR(void)
{
	if(boolOnHighThresWdg)
	{	//on high thres
		ihorizLines++;
		if(boolOnVerticalSync)
		{
			vfnInit_Adc_WatchdogH(0,1,HORIZ_SYNC_THRES);
			boolOnVerticalSync=FALSE;
			ihorizLines=0;	
			iwantedLines=0;
		}
		if(	lineSelect[ihorizLines] == TRUE)
		{
			readLines(iwantedLines);
			if(pixel<30)
			{
				boolOnVerticalSync=TRUE;
				vfnInit_Adc_WatchdogH(0,1,VERTI_SYNC_THRES);
			}
			CLEAR_HIGH_WDG_FLG;
		}
		if(ihorizLines>240)
		{
			readLines(8);
			if(pixel<30)
			{
				if(temp>2)
				{
					temp=0;   //for debug
				}
				temp++;
				boolOnVerticalSync=TRUE;
				vfnInit_Adc_WatchdogH(0,1,VERTI_SYNC_THRES);
			}
			CLEAR_HIGH_WDG_FLG;
		}
		else
		{
			boolOnHighThresWdg=0;
			DISABLE_WDGH_INT;
			ENABLE_WDGL_INT;
			CLEAR_LOW_WDG_FLG;
		}
	}
	else
	{	//on low thres
		boolOnHighThresWdg=1;
		ENABLE_WDGH_INT;
		DISABLE_WDGL_INT;
		CLEAR_HIGH_WDG_FLG;
	}
}