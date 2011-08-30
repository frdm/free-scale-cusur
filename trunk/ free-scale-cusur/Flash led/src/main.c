/* Programa: flasheo de leds, con pushbutton de inicio */
/* Explicacion: cuando se presione el pushbutton conectado
a PE[0], se inicia el flasheo de los leds conectados a PE[4],PE[5],PE[6] y PE[7].
NOTA: el programa no se reinicia al presionar de nuevo el pushbutton */
/* Fecha de creación: 05-Ago-2011 */
/* Programador: Cristóbal Christian Ramirez Ruiz */
/* Ayuda: initModesAndClock,initPeriClkGen y disableWatchdog, tomados de "MPC5500 & MPC5600
Simple Cookbook" (Freescale) */

#include "MPC5604B_M27V.h"  
vuint32_t i = 0; /* Dummy idle counter */

void initModesAndClock(void) {
ME.MER.R = 0x0000001D; /* Enable DRUN, RUN0, SAFE, RESET modes */
/* Initialize PLL before turning it on: */
/* Use 1 of the next 2 lines depending on crystal frequency: */
CGM.FMPLL_CR.R = 0x02400100; /* 8 MHz xtal: Set PLL0 to 64 MHz */
/*CGM.FMPLL_R = 0x12400100;*/ /* 40 MHz xtal: Set PLL0 to 64 MHz */
ME.RUN[0].R = 0x001F0074; /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL */
ME.RUNPC[1].R = 0x00000010; /* Peri. Cfg. 1 settings: only run in RUN0 mode */
ME.PCTL[68].R = 0x01; /* MPC56xxB/S SIUL: select ME.RUNPC[1] */
ME.PCTL[72].R = 0x01; /* MPC56xxB/S EMIOS 0: select ME.RUNPC[1] */
/* Mode Transition to enter RUN0 mode: */
ME.MCTL.R = 0x40005AF0; /* Enter RUN0 Mode & Key */
ME.MCTL.R = 0x4000A50F; /* Enter RUN0 Mode & Inverted Key */
while (ME.GS.B.S_MTRANS) {} /* Wait for mode transition to complete */
/* Note: could wait here using timer and/or I_TC IRQ */
while(ME.GS.B.S_CURRENTMODE != 4) {} /* Verify RUN0 is the current mode */
}


void initPeriClkGen(void) {
CGM.SC_DC[2].R = 0x80; /* MPC56xxB: Enable peri set 3 sysclk divided by 1*/
}


void disableWatchdog(void) {
SWT.SR.R = 0x0000c520; /* Write keys to clear soft lock bit */
SWT.SR.R = 0x0000d928;
SWT.CR.R = 0x8000010A; /* Clear watchdog enable (WEN) */
}






void initCONFIG_output(void) { /* set the inputs and outputs */

SIU.PCR[64].R = 0x100; /* set PE[0] as input */
SIU.PCR[65].R = 0x100;
SIU.PCR[64].R = 0x100;
SIU.PCR[66].R = 0x100;
SIU.PCR[67].R = 0x100;

SIU.PCR[68].R = 0x200; /* set PE[4] as output */
SIU.PCR[69].R = 0x200; /* set PE[5] as output */
SIU.PCR[70].R = 0x200; /* set PE[6] as output */
SIU.PCR[71].R = 0x200; /* set PE[7] as output */

}


void init_delay(void)
{
uint32_t i = 0; /* Dummy idle counter */
 
    for(i=0;i<1000000;i++)
	{
	;	
	}
}


void initFLASHING_led(void) { 

int check = 1;

fgh: 
{SIU.GPDO[68].R = 0;SIU.GPDO[69].R = 0;SIU.GPDO[70].R = 0;SIU.GPDO[71].R = 0;}

if(SIU.GPDI[64].R == 0){
		check=0;goto a_el_otro;
		}
		else
			{
				goto fgh;				
			}

if(SIU.GPDI[65].R == 0){
		check=0;goto a_un_lado;
		}
		else
			{
				goto fgh;				
			}

a_un_lado:

init_delay();{SIU.GPDO[68].R = 1;SIU.GPDO[69].R = 1;SIU.GPDO[70].R = 1;SIU.GPDO[71].R = 1;}
init_delay();{SIU.GPDO[68].R = 0;SIU.GPDO[69].R = 1;SIU.GPDO[70].R = 1;SIU.GPDO[71].R = 1;}
init_delay();{SIU.GPDO[68].R = 1;SIU.GPDO[69].R = 0;SIU.GPDO[70].R = 1;SIU.GPDO[71].R = 1;}
init_delay();{SIU.GPDO[68].R = 1;SIU.GPDO[69].R = 1;SIU.GPDO[70].R = 0;SIU.GPDO[71].R = 1;}
init_delay();{SIU.GPDO[68].R = 1;SIU.GPDO[69].R = 1;SIU.GPDO[70].R = 1;SIU.GPDO[71].R = 0;}
goto fgh;

a_el_otro:
init_delay();{SIU.GPDO[68].R = 1;SIU.GPDO[69].R = 1;SIU.GPDO[70].R = 1;SIU.GPDO[71].R = 1;}
init_delay();{SIU.GPDO[68].R = 1;SIU.GPDO[69].R = 1;SIU.GPDO[70].R = 1;SIU.GPDO[71].R = 0;}
init_delay();{SIU.GPDO[68].R = 1;SIU.GPDO[69].R = 1;SIU.GPDO[70].R = 0;SIU.GPDO[71].R = 1;}
init_delay();{SIU.GPDO[68].R = 1;SIU.GPDO[69].R = 0;SIU.GPDO[70].R = 1;SIU.GPDO[71].R = 1;}
init_delay();{SIU.GPDO[68].R = 0;SIU.GPDO[69].R = 1;SIU.GPDO[70].R = 1;SIU.GPDO[71].R = 1;}

goto fgh;

}



void main (void) {

initModesAndClock(); /* Initialize mode entries and system clock */
initPeriClkGen(); /* Initialize peripheral clock generation for DSPIs */
disableWatchdog(); /* Disable watchdog */
initCONFIG_output();
initFLASHING_led(); 

}


