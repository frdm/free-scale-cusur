#include "MiniTS.h"
#include "MPC5604B_M27V.h"

#define NUMBER_OF_SAMPLE_SETS 3

uint8_t *center;
int8_t derivs[NUMBER_OF_SAMPLE_SETS-1];

void vfnObtain_Deriv(void)
{
	uint8_t i;
	for(i=0;i<NUMBER_OF_SAMPLE_SETS-1;i++)
	{
		if((*(center+i)==0) || (*(center+i+1)==0))
		{
			derivs[i]=127;// Invalid deriv
		}
		derivs[i]=(int8_t)(*(center+i))-(int8_t)(*(center+i+1));
	}
}

int8_t i8Average_Deriv(void)
{
	uint8_t i;
	uint8_t correctSets=0;
	int8_t average=0;
	for(i=0;i<NUMBER_OF_SAMPLE_SETS-1;i++)
	{
		if(derivs[i]!=127)// If valid line reading
		{
			correctSets++;
			average+=derivs[i];
		}
	}
	average/=correctSets;
}

void vfnIdentify_Pattern(void)
{
	int8_t average;
	vfnObtain_Deriv();
	average=i8Average_Deriv();
	if(average<-3)
	{
		
	}
	else if(average>3)
	{
		
	}
	else
	{
		
	}
}

void algorithm (uint8_t *localcenter)
{
	center=localcenter;			// Save local variable to global variable
	vfnIdentify_Pattern();		// Recognize turns or straight lines
	//vfnSet_Servo(*(center+1),1,45);
}