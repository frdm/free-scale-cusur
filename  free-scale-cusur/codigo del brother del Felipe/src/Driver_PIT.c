#include "MPC5604B_0M27V_0102.h"
#include "Driver_MPC5604B.h"


/** Initialize PIT */
void vfninit_Pit(uint8_t u8Div) {
  PIT.PITMCR.R = 0x00000001;       /* Enable PIT and configure timers to stop in debug mode */
  PIT.CH[1].LDVAL.R = u8Div;       /* PIT1 timeout = 640000000 sysclks x 1sec/64M sysclks = 1 sec */
  PIT.CH[1].TCTRL.R = 0x000000003; /* Enable PIT1 interrupt and make PIT active to count */ 
}
