#include "MPC5604B_M27V.h"
#include "Driver_ADC.h"
#include "Driver_Camara_Lineal.h"
#include "Driver_CTU.h"
#include "Driver_EMIOS.h"
#include "Driver_SIU.h"

int32_t y;

int main(void) {
  volatile int i = 0;
	

/** Calls the initialization functions */


 vfnInit_All();

vfnSetup_CamLin();
vfnSetup_Emios_1();
vfnInit_Emios_0();
vfnInit_Emios_1();
vfnInit_CamLin_Adc();



beMIOS_initEMIOS0_ch23();

vfnInit_Emios_Output_Pad(71);

beMIOS_initEMIOS1_ch23();

vfnInit_Emios1_Output_Pad(96);
vfnInit_Gpio_Out(64);

vfnSet_Gpio(64,0);




  /* Loop forever */
  for (;;) {
  
y=EMIOS_1.CH[23].CCNTR.R;
 u8Capture_Pixel_Values();
 control();
 
 
    i++;
  }
}



