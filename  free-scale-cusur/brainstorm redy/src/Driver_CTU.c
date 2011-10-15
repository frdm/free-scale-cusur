#include "MPC5604B_0M27V_0102.h"
#include "Driver_MPC5604B.h"

/** Config event on Emios Channel to trig CTU_CHANNEL_adc */
void vfnTrigger_Emios_Adc(uint8_t u8EmiCha,uint8_t u8CtuCha)
{
	CTU.EVTCFGR[u8EmiCha].B.TM=1;					/* Trigger Mask Enabled for selected Emios Channel */
	CTU.EVTCFGR[u8EmiCha].B.CHANNELVALUE=u8CtuCha;	/* Config event on Emios Channel to trig CTU_CHANNEL_adc */
}