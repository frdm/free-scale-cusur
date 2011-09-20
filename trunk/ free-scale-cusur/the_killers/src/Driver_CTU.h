/* Function Prototypes */

/**
  \brief	Enable trigger events in the selected Emios channel and config event on the Emios channel to trig 
  			a selected Adc channel
  \param  	u8EmiCha: Wanted Emios channel to produce the trig.
  			u8CtuCha: Adc channel to be trigged defined in Driver_MPC5604B.h as CTU_CHANNEL_tag.
  \return	nule.
*/
void vfnTrigger_Emios_Adc(uint8_t u8EmiCha,uint8_t u8CtuCha);


