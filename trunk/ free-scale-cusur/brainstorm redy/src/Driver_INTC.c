#include "MPC5604B_0M27V_0102.h"
#include "Driver_MPC5604B.h"

extern IVOR4Handler();
extern uint32_t __IVPR_VALUE; /* Interrupt Vector Prefix vaue from link file*/
extern const vuint32_t IntcIsrVectorTable[];

/** Initialize Interrupt Vectors */
asm void vfninit_IrqVectors(void) {
  lis	   r3, __IVPR_VALUE@h   /* IVPR value is passed from link file */
  ori      r3, r3, __IVPR_VALUE@l 
  mtivpr   r3									 
}

/** Initialize Interrupt Controller */
void vfninit_Intc(void) {	
  INTC.MCR.B.HVEN = 0;       /* Single core: initialize for SW vector mode */
  INTC.MCR.B.VTES = 0;       /* Single core: Use default vector table 4B offsets */
  INTC.IACKR.R = (uint32_t) &IntcIsrVectorTable[0];    /* MPC555x: INTC ISR table base */
}

/** Initialize External Interrupts*/
void vfninit_Irq(void) {
  INTC.CPR.B.PRI = 0;          /* Single Core: Lower INTC's current priority */
  asm(" wrteei 1");	    	   /* Enable external interrupts */
}

/** Stablish Vectors Priority*/
void vfninit_Priority(void)
{
  //INTC.PSR[60].R = 1;        /* PIT 1 interrupt vector with priority 1 */
  //INTC.PSR[4].R = 2;		/* Software interrupt 4 IRQ priority = 2 */
  //INTC.PSR[62].R = 3;		/* Adc End Of Converion Interrupt priority = 2 */
  INTC.PSR[64].R = 1;		/* Adc End Of Converion Interrupt priority = 2 */
}

