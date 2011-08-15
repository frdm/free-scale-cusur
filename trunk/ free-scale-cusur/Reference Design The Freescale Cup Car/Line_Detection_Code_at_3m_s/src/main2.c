/* MAIN.C */	
#include "MPC5604B_M27V.h"		// For register definition
#include "Driver_ADC.h"			// ADC driver
#include "Driver_SIU.h"			// SIU driver
#include "Driver_PIT.h"			// PIT driver
#include "Driver_INTC.h"		// Interrupts driver
#include "Driver_MPC5604B.h"	// Useful defines (most for PCR)
#include "driver_velocimeter.h"
#include "Setup.h"				// Principal initialization
#include "MiniTS.h"				// Camera reading scheduler
#include "Algorithm.h"			// Main algorithm 
#include "main.h"				// Main header
#define  NUMBER_OF_CAMERA_LINES 34		// Number of lines to be read

uint8_t line[38];
uint8_t direction=0;
uint8_t rampi=0;
uint8_t baches=0;
uint8_t nbaches=0;
uint8_t prelast=0;
uint8_t curve=0;	// para vuelta izq (1), der (2), S (3)
uint8_t thresh=0;
uint16_t rampa=0;
uint32_t prom,reversecounter;
uint8_t counter;
uint8_t valid,valid2,valid3,curvetype;
uint32_t velocity=300;
uint32_t wait=0;
uint32_t velocimeter=0;
uint32_t veldif=0;
uint16_t  debug=0;	//average of positions
uint32_t  debug2=0;	//average of positions
uint32_t  debug3=0;	//average of positions
uint8_t  averageMin=0;	//average of positions
int32_t  vector=0;	//average of positions
int8_t  first=0;	//average of positions
int8_t  last=0;	//average of positions
uint8_t     camerafunc,receivedChar;
uint8_t     camerafunkgenerator;
uint16_t matrixdebug[55];


uint8_t onceperframe=0,framepostscale=0;
int8_t i,go,dif;			//index

uint16_t u16Get_Pulse_Width(uint8_t u8Channel)			
{
	uint16_t u16widtha,u16widthb,result;
	
	if(EMIOS_0.CH[u8Channel].CSR.B.FLAG==1)													/* Wait for flag activation */
	{	
		u16widtha = EMIOS_0.CH[u8Channel].CADR.B.CADR; 	/* Pulse width by subtracting the value in B1 from A2 */
		u16widthb = EMIOS_0.CH[u8Channel].CBDR.B.CBDR;
		
		if(u16widtha>u16widthb)
		{
			result=u16widtha - u16widthb;
		}
		else
		{
			result=0;
		}
		
		EMIOS_0.CH[u8Channel].CSR.B.FLAG = 1;
		Restart_Modulus_Counter(u8Channel);
		return result;
	}
	else
	{
		return 0;
	}
	
}

void initLINFlex_cuau (void) {
 
  LINFLEX_0.LINCR1.B.INIT = 1;    /* Put LINFlex hardware in init mode */
  LINFLEX_0.LINCR1.R= 0b10001;    /* Configure module as LIN master*/
  LINFLEX_0.UARTCR.R= 0b110000000110011;   /*configure module as UART 1 byte no parity*/
  LINFLEX_0.LINIBRR.B.DIV_M= 416; /* Mantissa baud rate divider 104 component 38400*/
  LINFLEX_0.LINFBRR.B.DIV_F = 11;  /* Fraction baud rate divider 3 comonent 38400*/
  LINFLEX_0.UARTCR.R= 0b110000000110011;   /*configure module as UART 1 byte no parity*/
  LINFLEX_0.LINCR1.B.INIT = 0; 	  /* Put LINFlex hardware in normal mode */
  SIU.PCR[18].R = 0x0400;         /* MPC56xxB: Configure port B2 as LIN0TX */
  SIU.PCR[19].R = 0x0103;         /* MPC56xxB: Configure port B3 as LIN0RX */
}

void transmitUARTframe4 (uint8_t character,uint8_t character1,uint8_t character2,uint8_t character3) {
  LINFLEX_0.UARTCR.B.TDFL=3;
  LINFLEX_0.BDRL.B.DATA3 = character3;
  LINFLEX_0.BDRL.B.DATA2 = character2;
  LINFLEX_0.BDRL.B.DATA1 = character1;
  LINFLEX_0.BDRL.B.DATA0 = character;
  while(LINFLEX_0.UARTSR.B.DTF == 0)
  LINFLEX_0.UARTSR.B.DTF = 1;
}
void transmitUARTframe3 (uint8_t character,uint8_t character1,uint8_t character2) {
  LINFLEX_0.UARTCR.B.TDFL=2;
  LINFLEX_0.BDRL.B.DATA2 = character2;
  LINFLEX_0.BDRL.B.DATA1 = character1;
  LINFLEX_0.BDRL.B.DATA0 = character;
  while(LINFLEX_0.UARTSR.B.DTF == 0)
  LINFLEX_0.UARTSR.B.DTF = 1;
}
void transmitUARTframe2 (uint8_t character,uint8_t character1) {
  LINFLEX_0.UARTCR.B.TDFL=1;
  LINFLEX_0.BDRL.B.DATA1 = character1;
  LINFLEX_0.BDRL.B.DATA0 = character;
  while(LINFLEX_0.UARTSR.B.DTF == 0)
  
  LINFLEX_0.UARTSR.B.DTF = 1;
}

void transmitUARTframe1 (uint8_t character) {
  LINFLEX_0.UARTCR.B.TDFL=0;
  LINFLEX_0.BDRL.B.DATA0 = character;
  while(LINFLEX_0.UARTSR.B.DTF == 0);
  LINFLEX_0.UARTSR.B.DTF = 1;
}

int8_t receiveUARTframe1 (void) {
  uint8_t receive=0;
  if(LINFLEX_0.UARTSR.B.DRF==1)
  {
  	  receive=LINFLEX_0.BDRM.B.DATA4;
  }
  else
  {
  	  receive=0;
  }
  LINFLEX_0.UARTSR.B.DRF = 1;
  return receive;
}

/**
  \brief	returns the minimum average value of the position of
  			the lowest ADC value of the NUMBER_OF_LINES	lines requested
  \param  	set: the number of the set of lines from 0 to N (top,..,middle,...,low)
  \return	average
*/
uint8_t getMin(uint8_t set)
{
	uint8_t  minPos;		//position of line
	uint32_t derivPos;      //derivative for line detection
	int32_t Deriv;			//deravative
	int32_t maxDeriv=0;		//max deravative
	
	uint32_t pixelScan;		//temporary variable
	uint32_t pixelScan2;		//temporary variable
	
	uint32_t derivPos2;      //derivative for line detection
	int32_t maxDeriv2=0;		//max deravative
	int32_t posDif=0;		//max deravative

	
	uint8_t i;			//index
	
	for(i=5;i<49;i++)
	{
		pixelScan=(u32GetPixel(set,i)-100)<<1;
		pixelScan2=(u32GetPixel(set,i+1)-100)<<1;
		
		
		Deriv=(pixelScan-pixelScan2);
		if(maxDeriv<Deriv)
		{
			maxDeriv=Deriv;
			derivPos=i+1;
		}
		Deriv=(pixelScan2-pixelScan);
		if(maxDeriv2<Deriv)
		{
			maxDeriv2=Deriv;
			derivPos2=i;
		}
		posDif=derivPos2-derivPos;
		if(posDif<0 || posDif>10 || maxDeriv2<45 || maxDeriv<45)//5//60//7/////8//45
		{
			minPos=0;
		}
		else
		{
			minPos=(derivPos2+derivPos)/2;
		}
	}
	if(set==0)
	{
		set=0;
	}
	return minPos;
}
void getImage(void)
{
	for(i=0;i<(NUMBER_OF_CAMERA_LINES+2);i++)
	{
		line[i]=getMin(i);
	}
}
void fixMatrix(void)
{
	/////////////////////Find first valid line//////////////////////
	for(i=NUMBER_OF_CAMERA_LINES;i>17;i--)
	{
		if(line[i]>0 && line[i-1]>0)
		{
			first=i;
			i=0;
		}
		if(first<14)//30 jala chido como antes
		{
			first=0;
		}
	}
	/////////////////////Rebuild Matrix correcting mistakes/////////
	last=0;
	valid3=0;
	for(i=NUMBER_OF_CAMERA_LINES;i>-1;i--)
	{
		if(i>first)
		{
			line[i]=0;
		}
		if(line[i]>0 && line[i-1]>0 && i>0)
		{
			if(line[i]>line[i-1])
			{
				dif=line[i]-line[i-1];
			}
			else
			{
				dif=line[i-1]-line[i];
			}
			if(dif>4)//4
			{
				line[i-1]=0;
				valid3++;
			}						
		}
		if(line[i]>0 && line[i-1]==0 && line[i-2]>0 && i>1)
		{
			if(line[i]>line[i-2])
			{
				dif=line[i]-line[i-2];
			}
			else
			{
				dif=line[i-2]-line[i];
			}
			if(dif>5)//6
			{
				line[i-2]=0;
				valid3++;
			}						
		}
		if(line[i]>0 && line[i-1]==0 && line[i-2]==0 && line[i-3]>0 && i>2)
		{
			if(line[i]>line[i-3])
			{
				dif=line[i]-line[i-3];
			}
			else
			{
				dif=line[i-3]-line[i];
			}
			if(dif>8)//8
			{
				line[i-3]=0;
				valid3++;
			}						
		}
		if(line[i]>0 && line[i-1]==0 && line[i-2]==0 && line[i-3]>0 && i>2)
		{
			dif=line[i]-line[i-3];
			line[i-1]=line[i]-(dif/3);
			line[i-2]=line[i-3]+(dif/3);
			valid3++;
		}
		if(line[i]>0 && line[i-1]==0 && line[i-2]>0 && i>1)
		{
			dif=line[i]-line[i-2];
			line[i-1]=line[i]-(dif/2);
			valid3++;
		}
		if(line[i]==0 && line[i-1]==0 && line[i-2]==0 && i>1 && i<first && last==0)
		{
			last=i-2;
			valid3++;
		}
		if(i<=last)
		{
			line[i]=0;
			valid3++;
		}
	}
	valid=0;
	for(i=NUMBER_OF_CAMERA_LINES;i>-1;i--)
	{
		if(line[i]>0)
		{
			valid=1;
		}
	}
	if(valid==0)
	{
		last=-1;
		first=-1;
	}
}

uint8_t onCurve()
{
	if(curve==0)
	{
		thresh=12;
	}
	else
	{
		thresh=5;
	}
	if(last>thresh && valid==1)					//last debe ser 0
	{
		if(line[last+3]>35)////38
		{
			curve=1;			// vuelta izq
		}
		if(line[last+3]<15)////16
		{
			curve=2;			// vuelta der
		}	
	}
	if(last<5 && valid==1)
	{
		curve=0;					
	}
	if(valid==1)
	{
		switch(curve)
		{
			case 0: direction=0;break;
			case 1: direction=last+18;break;
			case 2: direction=34-last;break;
		}
	}
	if(valid==0)
	{
		if(curve==1)
		{
			direction=48;			// vuelta izq
		}
		if(curve==2)
		{
			direction=5;			// vuelta der
		}
	}
	return 	direction;	
}
/** MAIN ... :) */
void main (void) {	
	


	
	/*************************************************
	*	INITIALIZATION
	**************************************************/
		
	vfnInit_All();  
	vfnInit_MiniTS();
	vfnInit_Adc_Pad(PCR_ADC_ANP2);
	vfnInit_NormalConversion_Adc(ADC_PRECISION_CHANNEL,ADC_CHANNEL_ANP2);
	//while()
	//transmitUARTframe1 ('h');
	
	vfnInit_Adc_Pad(PCR_ADC_ANP1);
	vfnInit_NormalConversion_Adc(ADC_PRECISION_CHANNEL,ADC_CHANNEL_ANP1);
	vfnInit_Adc_WatchdogL(0,1,HORIZ_SYNC_THRES);
	vfnInit_Adc_WatchdogH(0,1,HORIZ_SYNC_THRES);
	vfninit_IrqVectors();
	vfninit_Intc();
	vfninit_Irq();
	vfninit_Priority();
	ENABLE_WDGL_INT;
	ENABLE_WDGH_INT;	
	
	vfnSetup_Emios_0();
	
	vfnInit_Emios_Input_Pad(PCR_EMIOS_0_1);
	
 	vfnInit_Emios_0_Mcb(0,0xFFFF); 														/* Define Emios Channel as Modulus Counter */
	vfnInit_Emios_0_Ipwm(1,1);
	
	vfnInit_Servo(); 				//for servo
	vfnSet_Servo(26,4,49);
	vfnInit_Motor();				// Initialize motor
	init_velocimeter();				// Initialize velocimeter	
	initLINFlex_cuau();         /* Initialize FLEXCAN 0 as master */
	initLineSelector();             //initialize select lines for camera read
	//selectLine(124);				//select lines for read
	vfnSet_Motor_NO2(FALSE);
	camerafunc=20;
	
	
	vfnInit_Emios_0();
	
	
	
///////////////////////// SE VA Y SE CORRE /////////////////////////////////////////

	/* Seleccion de lineas de la RCA a convertir */
	for(i=2;i<(NUMBER_OF_CAMERA_LINES+4);i++)
	{
		selectLine(camerafunc);
		camerafunc+=i/3;
	}
	
	velocity=300;
	reversecounter=0;
	
	/* Aquí va el código de interpretación */
	while(TRUE)
	{
		if(onceperframe==0)
		{
			onceperframe=1;
			debug++;
			
			/*Get line Matrix*/
			getImage();
			fixMatrix();
///////////////////////line following algorithm/////////////////////////
			
			/*clasificacion de curva*/
			direction=onCurve();
			
			if(direction==0)
			{
				///cuando esta en recta
				
				curvetype=0;
				velocity=3000;		//3300
				prom=0;
				for(i=first;i>(last+3);i--)
				{
					prom+=line[i];
				}
				prom= prom/(first-(last+3));
				if(prom<26)
				{
					prom=25-prom;
					prom/=2;
					prom=25-prom;
				}
				else
				{
					prom=prom-26;
					prom/=2;
					prom=26+prom;
				}
				direction=prom;
			}
			else
			{
			/////cuando estas en una curva
				
				curvetype=1;
				velocity=1500;		//1620
				if(velocimeter<(velocity*velocity)+(200*200))
				{
					if(direction<26)
					{
						direction=25-direction;
						direction/=2;
						direction=25-direction-8;
					}
					else
					{
						direction=direction-26;
						direction/=2;				//direction/=2;
						direction=26+direction+8;	//direction=26+direction+9;
					}	
				}
			}
	
			/////// reducir velocidad en curva
			if(last>1 || line[last+3]<11 || line[last+3]>39)//11//8
			{
				velocity=1700;
			}
			
			
			if(first<26)//11//8
			{
				velocity=2200;
			}
			/*if(valid3>15 && (line[last+6]>17 && line[last+6]<33) && velocimeter>(1500*1500))
			{
				vfnSet_Servo(direction,4,49);	
				reversecounter=1;
			}*/
			else
			{
				reversecounter=0;
				vfnSet_Servo(direction,4,49);	
			}
			if(direction<41 && direction>9 && curvetype==1)
			{
				velocity=1700;
			}
			if(direction<39 && direction>11 && curvetype==1)
			{
				velocity=1800;
			}
			if(direction<35 && direction>15 && curvetype==1)
			{
				velocity=1900;
			}
			if(direction<33 && direction>17 && curvetype==1)
			{
				velocity=2200;
			}
			if(direction<31 && direction>19 && curvetype==1)
			{
				velocity=2400;
			}
			if(direction<29 && direction>21 && curvetype==1)
			{
				velocity=3000;
			}
			
			////////Parado a control remoto
			receivedChar=receiveUARTframe1();
			if(receivedChar>0)
			{
				velocity=0;
				vfnSet_Motor_NO2(FALSE);
				vfnSet_Motor_Stop();
				vfnSet_Servo(5,4,49);
				for(wait=0;wait<30000000;wait++);
				//velocity=300;
				//vfnSet_Motor_Forward(100);
			}
			else
			{
				receivedChar=0;
				//vfnSet_Motor_Forward(0);
			}
			
			
			/////// Deteccion de rampa
			rampa = u16Get_Pulse_Width(1);
		
			if(rampa!=0)
			{				
				if(rampa<3200)
				{
					rampi++;
				}
				else
				{
					rampi=0;
					reversecounter=0;
				}
				if(rampi>0)	//velocimeter>(100*100)
				{
					if(baches >5)
					{
						reversecounter=1;
						vfnSet_Servo(25,4,49);	
					}
					else
					{
						vfnSet_Servo(25,4,49);
						reversecounter=1;
						vfnSet_Motor_Reverse(100);
					}							
				}
			}
			/*if(last>1 && last<4)
			{
				vfnSet_Motor_Reverse(100);
				reversecounter=1;
			}
			else
			{
				reversecounter=0;
			}*/
				
		}	
		
		
		if(boolGetOnVerticalSync())
		{
			velocimeter=vel_velocimeter();
			//transmitUARTframe3(velocimeter);
			
			if((velocimeter<(velocity*velocity)) && reversecounter==0)
			{
				vfnSet_Motor_Forward(100);	
			}
			if((velocimeter>(velocity*velocity)) && reversecounter==0)
			{
				veldif=velocimeter-(velocity*velocity);
				if(veldif>200000)//entre menor sea el valor mayor es el freno
				{
					vfnSet_Motor_Reverse(100);
				}
				else
				{
					vfnSet_Motor_Forward(0);
				}
				
			}
			
			/////// deteccion de baches o topes
			if(velocimeter<(200*200) && reversecounter==0)
			{
				baches++;
				nbaches=0;
				vfnSet_Motor_Forward(60);
			}
			else
			{
				nbaches++;
				if(nbaches>30)
				{
					baches=0;
				}
			}
			//transmitUARTframe1 ('h');
			onceperframe=0;
			/*if(debug>15)
			{
			
				for(i=0;i<55;i++)
				{
					matrixdebug[i]=(u32GetPixel(0,i)-100)<<1;//*(u32GetPixel(2,i)-100);
				}
				
				debug=0;
			}*/
		}
	}	
}
