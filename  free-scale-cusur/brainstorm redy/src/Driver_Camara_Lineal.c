


#include "MPC5604B_M27V.h"
#include "Driver_MPC5604B.h"
#include "Driver_EMIOS.h"


/********************* Definitions **************************/
#define	CHANNEL_CK			7
#define CHANNEL_SI    		9
#define CHANNEL_TRIG   		10
#define CAM_CNT_CHAN   		8
#define CAM_ADC_CHAN   		0
/*************************************************************/


/****************** Global Variables *************************/
uint16_t  	u16PulseWidthMeasure;
uint16_t     u16posicion;
uint16_t  	u16DeltaX ;
uint16_t  	u16PulseWidth ;
uint16_t	u16Pixel[128];
uint16_t 	u16CamCounter;
uint8_t 	u8i;
uint8_t		u8scandone;
uint8_t		killo=0;
uint8_t		pipe=450;

/*************************************************************/






/**************************************************************************************************************/
/*             	FUNCTIONS USING OPWM FROM EMIOS MODULE TO GENERATE CAMERA INPUT SIGNALS                       */
/**************************************************************************************************************/

/** Setup configuration for Camera, Define clock and start pulse **/
void vfnSetup_CamLin(void)
{

	vfnInit_Emios_Output_Pad(PCR_EMIOS_0_7);	/* Path configuration, Emios Output for CK signal */
	vfnInit_Emios_Output_Pad(PCR_EMIOS_0_9);	/* Path configuration, Emios Output for SI signal */
	vfnInit_Emios_Output_Pad(PCR_EMIOS_0_1);
	vfnInit_Gpio_Out(GPIO_PIN_A3);
	vfnInit_Gpio_Out(GPIO_PIN_A5);
	vfnSet_Gpio(GPIO_PIN_A3, 0);
	vfnSet_Gpio(GPIO_PIN_A5, 1);
	
	vfnSetup_Emios_0();                  		/* Main Configuration Register to initialize Emios */
 	vfnInit_Emios_0_Mcb(0,4); 					/* Define Emios Channel as Modulus Counter for CK pulse*/
 	vfnInit_Emios_0_Mcb(8,2000); 				/* Define Emios Channel as Modulus Counter for SI pulse*/
   
	
	vfnInit_Emios_0_Opwm(CHANNEL_CK, 1, 3);		/* Define Emios Channel as Opwm, define A and B parameters as 0 and 2 to generate CK signal for the camera */
	vfnInit_Emios_0_Opwm(CHANNEL_SI, 0, 2);		/* Define Emios Channel as Opwm, define A and B parameters as 1 and 3 to generate SI signal for the camera */
	vfnInit_Emios_0_Opwm(1, 2, 4);
}



/**************************************************************************************************************/
/*             		FUNCTIONS USING IPWM FROM EMIOS MODULE TO READ CAMERA OUTPUT                              */
/**************************************************************************************************************/

/** Set configurations to use Ipwm mode of Emios to read output from the camera **/
void vfnInit_CamLin_Ipwm(void)													
{
	u16PulseWidthMeasure=0;														/* Set i16PulseWidthMeasure to 0*/
	u16DeltaX=0;																/* Set i16DeltaX to 0*/
	u16PulseWidth=0 ;															/* Set i16PulseWidth to 0*/
	

//	vfnInit_Emios_Intput_Pad(PCR_EMIOS_0_tag);									/* Path configuration, Emios Input for camera output processing */

// 	vfnInit_Emios_0_Mcb(); 														/* Define Emios Channel as Modulus Counter */
//	vfnInit_Emios_0_Ipwm();														/* Define Emios Channel as Ipwm */
}

/** Define the value of an average pulse width from many samples **/
void Set_Pulse_Width (uint8_t u8Channel, uint8_t u8Frames)						
{
	uint8_t i=0;																/* Set i to 0*/
	for(i=0; i<u8Frames; i++)													/* Takes as many samples of pulse width measurements as the parameter u8Frames indicates */
	{
		while(EMIOS_0.CH[u8Channel].CSR.B.FLAG==0)								/* Waits for flag activation */
		u16PulseWidthMeasure = u16PulseWidthMeasure + 
		(EMIOS_0.CH[u8Channel].CADR.B.CADR - EMIOS_0.CH[u8Channel].CBDR.B.CBDR);/* Add new pulse width value to previous ones */	
		u16DeltaX = u16DeltaX + (EMIOS_0.CH[u8Channel].CBDR.B.CBDR);			/* Add new delta x value to previous ones */
	}
	u16PulseWidthMeasure = u16PulseWidthMeasure / u8Frames;						/* Divide i16PulseWidthMeasure by number of frames to get average value */
	u16DeltaX = u16DeltaX / u8Frames;											/* Divide i16DeltaX by number of frames to get average value */
}

/** Captures the value from the edge to the line, as well as the line width depending on the filter done by TolWidth and TolDelta (percentage) */
uint8_t u8Capture_Line_Values(uint8_t u8Channel, uint8_t u8TolDelta, uint8_t u8TolWidth)			
{
	uint16_t u16delta;
	uint16_t u16width;
	
	if(EMIOS_0.CH[u8Channel].CSR.B.FLAG==1)													/* Wait for flag activation */
	{	
		u16width = EMIOS_0.CH[u8Channel].CADR.B.CADR - EMIOS_0.CH[u8Channel].CBDR.B.CBDR;	/* Pulse width by subtracting the value in B1 from A2 */
		u16delta = (EMIOS_0.CH[u8Channel].CBDR.B.CBDR);										/* Delta x that correspond to the value in A2 */
		
		if ((u16width*100)<u16PulseWidthMeasure*(100-u8TolWidth) && (u16width*100)>u16PulseWidthMeasure*(100+u8TolWidth) && (u16delta*100)>u16DeltaX*(100+u8TolWidth) && (u16delta*100)<u16DeltaX*(100-u8TolWidth))
		{																					/* Apply filter of image stablished by tolerances of pulse width and delta x */
			u16PulseWidth = u16width;														/* Assign acceptable value of i16width to i16PulseWidth */
			u16DeltaX = u16delta;															/* Assign acceptable value of i16delta to i16DeltaX */
			EMIOS_0.CH[u8Channel].CSR.B.FLAG = 1;											/* Clear Flag */	
			return 1;																		/* Succesful line recognition */
		}
		else
		{
			return 0;																		/* Unsuccesful line recognition caused by image filtering */	
		}																	
	}
	else
	{
		return 0;																			/* Unsuccesful line recognition caused by flag unactivation */	
	}	
}

/** Return the last value of i16PulseWidth **/
uint16_t u16Pulse_Width(void)													
{
	return u16PulseWidth;														/* Return the last value of i16PulseWidth */
}

/** Return the last value of i16Delta_X **/
uint16_t u16Delta_X(void)														
{
	return u16DeltaX;															/* Return the last value of i16Delta_X */
}
		
		
			
/**************************************************************************************************************/
/*          		   		FUNCTIONS USING ADC MODULE TO READ CAMERA OUTPUT   		                          */
/**************************************************************************************************************/
						
/** Set configurations to use Adc to read output from the camera **/
void vfnInit_CamLin_Adc(void)													
{
	u16DeltaX=0;															/* Set i16DeltaX to 0*/
	u16PulseWidth=0 ;														/* Set i16PulseWidth to 0*/
	u8scandone=0;															/* Set u8scandone to 0*/
	u8i=0;																	/* Set u8i to 0*/


	vfnInit_Adc_Pad(PCR_ADC_ANP0);											/* Path configuration, Analog Input for camera output processing */
	vfnInit_Emios_Input_Pad(PCR_EMIOS_0_10);								/* Path configuration, Emios Input for CTU purpose */
	
	vfnInit_Adc_Ctu(ADC_PRECISION_CHANNEL, ADC_CHANNEL_ANP0);				/* Set an ANP0 as normal conversion channel for camera output processing (pin B4) */
	
	vfnTrigger_Emios_Adc(CHANNEL_TRIG,CTU_CHANNEL_ANP0);					/* Configure Ctu to trigger Emios channel 9 with ANP0 Adc channel */

	vfnInit_Emios_0_Saic_Ctu(CHANNEL_TRIG,FALLING_EDGE);					/* Define Emios Channel 9 as Saic for Ctu purpose */

	vfnInit_Emios_0();                  		/* Main Configuration Register to initialize Emios */

}

 
uint8_t u8Capture_Pixel_Values(void)
{

	
	u16CamCounter=EMIOS_0.CH[CAM_CNT_CHAN].CCNTR.B.CCNTR;		
	
	if	(u16CamCounter <= 1996 && u16CamCounter > pipe)
	{
		vfnSet_Duty_Opwm(CHANNEL_CK,1);
	
			vfnSet_Duty_Opwm(1,2);
	}
	else
	{
		vfnSet_Duty_Opwm(CHANNEL_CK,3);
			vfnSet_Duty_Opwm(1,4);
		u8i=0;
		u8scandone=0;
	}
	
	while (u8i<128)
	{
		uint16_t	u16cont3;
	
	/* agruegar un if para cuando la bandera del saic se active en el ultimo pixel entonces apagar el opwm y funcionara :)*/
//		if(u8i==127)
/*		{
			while (EMIOS_0.CH[CHANNEL_TRIG].CSR.B.FLAG ==0) {}
			vfnSet_Duty_Opwm(CHANNEL_CK,1);
		}
		u16Pixel[u8i] = u16Read_Adc(CAM_ADC_CHAN, 1023);
		u8i++;	
		}*/
		u16cont3= u16Read_Adc(CAM_ADC_CHAN, 1023);
		if (u16cont3 != 1024)
		{
			u16Pixel[u8i]=u16cont3;
			u8i++;	
			
			u16CamCounter=EMIOS_0.CH[CAM_CNT_CHAN].CCNTR.B.CCNTR;		
			if	(u16CamCounter <= 1996 && u16CamCounter > pipe)
			{
//				vfnSet_Duty_Opwm(CHANNEL_CK,1);
			}
			else
			{
				vfnSet_Duty_Opwm(CHANNEL_CK,3);
			}
		}


	}
	
	if(u8i==128)
	{
		killo++;
		if(killo>1000)
		{
			pipe++;
		}
		if(pipe>1000)
		{
			pipe=10;
		}
	}
	
	u16CamCounter=EMIOS_0.CH[CAM_CNT_CHAN].CCNTR.B.CCNTR;

	if(u16CamCounter>1996)
	{
		vfnSet_Duty_Opwm(CHANNEL_CK,3);
			vfnSet_Duty_Opwm(1,4);
		u8i=0;
		u8scandone=0;
	}

	if (u8scandone==0)
	{
	uint16_t	u16cont=2;
	uint16_t	u16minval=1023;
	uint16_t	u16minpos=0;
	uint16_t	u16treshold;
	uint16_t	u16corner1;
	uint16_t	u16corner2;
	
		while(u16cont<126)
		{
			if(u16minval>u16Pixel[u16cont])
			{
				u16minval=u16Pixel[u16cont];
				u16minpos=u16cont;	
			}
		u16cont++;	
		}
		
	  	if(u16minval>45)
		{
			u16treshold=15;
		}
		else
		{
			u16treshold=3;
		}
		
		u16corner1=u16minpos;
		u16corner2=u16minpos;
	  	while(((u16Pixel[u16corner1])<(u16minval+u16treshold)) && (u16corner1<128))
		{
			u16corner1--;	
		}
		while(((u16Pixel[u16corner2])<(u16minval+u16treshold)) && (u16corner2>0))
		{
			u16corner2++;	
		}
		u8scandone=1;
		u16PulseWidth = u16corner2 - u16corner1;
		u16DeltaX = (u16corner2 + u16corner1)/2;
		
		u16posicion=	u16minpos;
		return 1;
		
		

	}
	else


	{
		return 0;	
	}
	
	

}

void control(void)
{
		 //CENTRO
		 // nuevo rango para linea en centrto de 49 a 89 anterior de 64 a 94
	if((u16posicion>=55)&&(u16posicion<=74)) /* 94 34*/{
 		EMIOS_0.CH[23].CADR.R = 160; /*165*/
 	}
 //ir izq
	else if((u16posicion>=0)&&(u16posicion<=14)) /*34 18*/
	{
 		EMIOS_0.CH[23].CADR.R = 125; //optimo 130
	}
	
	else if((u16posicion>=15)&&(u16posicion<=34)) /*34 18*/
	{
 		EMIOS_0.CH[23].CADR.R = 136; //optimo 130
	}
	
	else if((u16posicion>=35)&&(u16posicion<=54)) /*34 18*/
	{
 		EMIOS_0.CH[23].CADR.R = 148; //optimo 130
	}
	/*
	else if((u16posicion>=55)&&(u16posicion<=74)) /*34 18*/
	/*{
 		EMIOS_0.CH[23].CADR.R = 160; //optimo 130
	}*/
	
	else if((u16posicion>=75)&&(u16posicion<=94)) /*34 18*/
	{
 		EMIOS_0.CH[23].CADR.R = 171; //optimo 130
	}
	
	else if((u16posicion>=95)&&(u16posicion<=114)) /*34 18*/
	{
 		EMIOS_0.CH[23].CADR.R = 183; //optimo 130
	}
	 
 //curva a der
	else if((u16posicion>=115)&&(u16posicion<=128)) /*94 110*/{
		EMIOS_0.CH[23].CADR.R = 195; //optimo 190
 	}
 

}
  			