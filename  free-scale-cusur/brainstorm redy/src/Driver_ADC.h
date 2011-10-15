/* Function Prototypes */

/**
  \brief	Initialize Adc in scan mode, Configure Adc clock to 32 MHz, set an Adc Channel from a channel type 
  			as a Normal Conversion, and start conversions by settin NSTART to 1. 
  \param  	u8ChannelType: defined in Driver_MPC5604B.h as ADC_CHANNEL_TYPE_tag 
  			u32Channel: defined in Driver_MPC5604B.h as ADC_CHANNEL_tag 
  \return	nule
*/
void vfnInit_NormalConversion_Adc(uint8_t u8ChannelType,uint32_t u32Channel);

/**
  \brief	Initialize Adc in scan mode, Configure Adc clock to 32 MHz, set an Adc Channel from a channel type 
  			as a cross triggering Adc Channel, and start conversions by settin NSTART to 1. 
  \param  	u8ChannelType: channel type defined in Driver_MPC5604B.h as ADC_CHANNEL_TYPE_tag 
  			u32Channel: Adc channel value defined in Driver_MPC5604B.h as ADC_CHANNEL_tag 
  \return	nule
*/
void vfnInit_Adc_Ctu(uint8_t u8ChannelType,uint32_t u32Channel);

/**
  \brief	Checks for an Adc conversion to be complete, reads the value of the conversion, scale the read
  			value in a range from 0 to Maximum Value and devolve the scaled value.
  \param  	u8Channel: The channel used for ADC, channels appear in Driver_MPC5604B.h.
  			u8MaximumValue: The maximum possible value for the result. 
  \return	An integer from 0 to u8MaximumValue proportional to the ADC scan
*/
//void uint16_t u16Read_Adc(uint8_t u8Channel, uint16_t u16MaximumValue);

void vfnInit_Adc_Interrupt(uint8_t u8ChannelType,uint32_t u32Channel);

void vfnInit_Adc_WatchdogL(uint8_t u8WtdChannel, uint32_t u32AdcChannel, uint32_t u32LowTreshold);
void vfnInit_Adc_WatchdogH(uint8_t u8WtdChannel, uint32_t u32AdcChannel, uint32_t u32HighTreshold);
void vfnInit_Adc_WatchdogL2(uint8_t u8WtdChannel, uint32_t u32AdcChannel, uint32_t u32LowTreshold);