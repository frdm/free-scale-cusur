//////////////////////Aplication Layer/////////////////////

void SM_KNOB(E_SM_KNOB e_sm_knob);
void SM_WHEEL(E_SM_WHEEL e_sm_wheel);
void Hardware_Init(void);

void SM_KNOB(E_SM_KNOB e_sm_knob)
{
	switch(e_sm_knob)
	{
		case INIT_KNOB:
		{
			KNOB_Init();
			break;
		}
		case READ_REQUEST:
		{
			KNOB_SendReadRequest();			
			break;
		}
		case GET_KNOB_VALUE:
		{
			KNOB_GetKnobValue();
			break;
		}
		default;
	}
}


void SM_WHEEL(E_SM_WHEEL e_sm_wheel)
{
	switch(e_sm_knob)
	{
		case INIT_WHEEL:
		{
			WHEEL_Init();
			break;
		}
		case UPDATE_WHEEL_POSITION
		{
			WHEEL_SetWheelPos();
			break;
		}
		default;
	}
}


void main (void)
{
	System_Init();
	Hardware_Init();
	
	while(TRUE)
	{
		SM_KNOB(READ_REQUEST);	//Send the request to get the KNOB value
		if(KNOB_ReadDone())
		{
			SM_WHEEL(UPDATE_WHEEL_POSITION);
		}
	}
}
void Hardware_Init(void)
{
	SM_KNOB(INIT_KNOB);
	SM_WHEEL(SM_WHEEL);
}
////////////////Hardware Abstraction Layer/////////////////
void KNOB_Init(void);
void KNOB_SendReadRequest(void);
void KNOB_GetKnobValue(void);
bool KNOB_ReadDone(void);
void WHEEL_Init(void);
void WHEEL_SetWheelPos(void);


void KNOB_Init(void)
{
	//Disable the output buffer in SAFE mode
	//Select the PAD as Analog input
	//Select the PAD Output asigment
}
void KNOB_SendReadRequest(void)
{
	
}
void KNOB_GetKnobValue(void)
{
	
}
bool KNOB_ReadDone(void)
{
	
}
void WHEEL_Init(void)
{
	//Disable the output buffer in SAFE mode
	//Select the PAD as Analog input
	//Select the PAD Output asigment
}
void WHEEL_SetWheelPos(void)
{
	
}
// /* int main(void) 
// {
	// /* ======================================== */
  	// /*              INITIALIZATIONS             */
  	// /* ======================================== */
  	

	
	
	// /* Configure Pins */
	// /* -------------- */
	// /* Pin PE3 will be used as GPIO-input to increment PWM duty cycle */
	// IO_SetPinFctn(pin_PE3,PA_GPIO);
	// IO_SetPinAsInput(pin_PE3);
	// /* Pin PE2 will be used as GPIO-input to decrement PWM duty cycle */
	// IO_SetPinFctn(pin_PE2,PA_GPIO);
	// IO_SetPinAsInput(pin_PE2);
	// /* Pin PE1 will be used as GPIO-input to set PWM duty cycle to 50% */
	// IO_SetPinFctn(pin_PE1,PA_GPIO);
	// IO_SetPinAsInput(pin_PE1);
	
	// /* PWM initialization */
	// /* ------------------ */
	// /* Init eMIOS 0 */	
	// beMIOS_initEMIOS0();
	// /* Init eMIOS 0 channel 23 as a OPWMB */	
	// beMIOS_initEMIOS0_ch23();
	// /* Associate PIN PE7 to the eMIOS 0 channel 23 function */
	// IO_SetPinFctn(pin_PE7,PA_AM1);	
	
	// /* Loop forever */
	
	// for (;;) 
	// {
		// /* INCREASE PWM OUTPUT */
		// /* ------------------- */
		// if(main_chkPinTransition(pin_PE3,raub_BufferPinPE3,1))
		// {
			// /* Increment current Duty Cycle in 5% */
			// beMIOS0_setPWMBdutyCycle(23,PWM_DC_INC,5);	
		// }
		
		// /* DECREASE PWM OUTPUT */
		// /* ------------------- */
		// if(main_chkPinTransition(pin_PE2,raub_BufferPinPE2,1))
		// {
			// /* Decrement current Duty Cycle in 5% */
			// beMIOS0_setPWMBdutyCycle(23,PWM_DC_DEC,5);	
		// }
		
		// /* SET PWM TO 50% */
		// /* -------------- */
		// if(main_chkPinTransition(pin_PE1,raub_BufferPinPE1,1))
		// {
			// /* Set current Duty Cycle to 50% */
			// beMIOS0_setPWMBdutyCycle(23,PWM_DC_SET,50);	
		// }
	// }
// } */