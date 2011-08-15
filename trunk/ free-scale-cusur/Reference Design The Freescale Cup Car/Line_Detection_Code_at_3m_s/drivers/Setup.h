/* Function Prototypes */

/** Disables Watchdog */
void vfnDisable_Watchdog(void);

/** Initializes the peripheral clock */
void vfnInit_Peri_Clk_Gen(void);

/** Initializes the general modes (ADC, SIU, EMIOS, etc) and clock (PLL, etc) */
void vfnInit_Modes_And_Clock(void);

/** Calls the initialization functions */
void vfnInit_All(void);

