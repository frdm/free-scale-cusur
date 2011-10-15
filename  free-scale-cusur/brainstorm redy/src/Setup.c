#include "MPC5604B_0M27V_0102.h"
#include "Driver_MPC5604B.h"

/** Disables Watchdog */
void vfnDisable_Watchdog(void) 		
{
  SWT.SR.R = 0x0000c520;     			/* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;   				/* Clear watchdog enable (WEN) */
}        

/** Initializes the peripheral clock */
void vfnInit_Peri_Clk_Gen(void) 
{
  CGM.SC_DC[2].R = 0x80;   				/* MPC56xxB/S: Enable peri set 3 sysclk divided by 1 */
}

/** Initializes the general modes (ADC, SIU, EMIOS, etc) and clock (PLL, etc) */
void vfnInit_Modes_And_Clock(void) 
{
  ME.MER.R = 0x0000001D;          		/* Enable DRUN, RUN0, SAFE, RESET modes */
                                  		/* Initialize PLL before turning it on: */
  CGM.FMPLL_CR.R = 0x02400100;    		/* 8 MHz xtal: Set PLL0 to 64 MHz */   
  ME.RUN[0].R = 0x001F0074;       		/* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
  ME.RUNPC[1].R = 0x00000010; 	  		/* Peri. Cfg. 1 settings: only run in RUN0 mode */
  ME.PCTL[32].R = 0x01; 	      		/* MPC56xxB/P/S ADC 0: select ME.RUNPC[1] */	
  ME.PCTL[57].R = 0x01; 	      		/* MPC56xxB CTUL: select ME.RUNPC[1] */
  ME.PCTL[68].R = 0x01; 	      		/* MPC56xxB/S SIU: select ME.RUNPC[1] */
  ME.PCTL[72].R = 0x01;           		/* MPC56xxB/S EMIOS 0:  select ME.RUNPC[0] */
  ME.PCTL[73].R = 0x01;  
  ME.PCTL[92].R = 0x01;           		/* PIT, RTI: select ME_RUN_PC[1] */	
                                  		/* Mode Transition to enter RUN0 mode: */
  ME.MCTL.R = 0x40005AF0;         		/* Enter RUN0 Mode & Key */
  ME.MCTL.R = 0x4000A50F;         		/* Enter RUN0 Mode & Inverted Key */  
  while (ME.GS.B.S_MTRANS) {}     		/* Wait for mode transition to complete */    
                                  		/* Note: could wait here using timer and/or I_TC IRQ */
  while(ME.GS.B.S_CURRENTMODE != 4) {} 	/* Verify RUN0 is the current mode */
}

/** Calls the initialization functions */
void vfnInit_All(void)
{
  vfnInit_Modes_And_Clock();    		/* Initialize mode entries and system clock */
  vfnDisable_Watchdog();      			/* Disable watchdog */
  vfnInit_Peri_Clk_Gen();       		/* Initialize peripheral clock generation for DSPIs */
}




