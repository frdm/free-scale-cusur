/* MINITS.H */
#include "typedefs.h"

// Interface defines
#define NUMBER_OF_LINES		5		// Lines read for each location
#define LINES_OF_RESOLUTION 210		// Number of total lines in picture
#define HORIZ_SYNC_THRES	0x10	// ADC value of horizontal low pulse
#define VERTI_SYNC_THRES	0x68	// ADC value of black threshold level

// Location of useful lines of picture
#define A_c					40
#define B_c					45
#define C_c					55
#define D_c					70
#define E_c					90
#define F_c					115
#define G_c					145
#define H_c					180

// Useful macros
#define ENABLE_ADC_INT(x)	(ADC.CIMR[ADC_PRECISION_CHANNEL].R = x)	//IE for channel x
#define DISABLE_INT			(ENABLE_ADC_INT(0))
#define ENABLE_WDGH_INT		(ADC.WTIMR.B.MSKWDG0H=1)				// IE for high wdg
#define DISABLE_WDGH_INT	(ADC.WTIMR.B.MSKWDG0H=0)				// IE for high wdg
#define ENABLE_WDGL_INT		(ADC.WTIMR.B.MSKWDG0L=1)				// IE for low wdg
#define DISABLE_WDGL_INT	(ADC.WTIMR.B.MSKWDG0L=0)				// IE for low wdg
#define LOW_WDG_FLG			(ADC.WTISR.B.WDG0L)
#define CLEAR_LOW_WDG_FLG	(ADC.WTISR.B.WDG0L=1)
#define CLEAR_HIGH_WDG_FLG	(ADC.WTISR.B.WDG0H=1)
#define ADC_DATA_READY		(ADC.CDR[1].B.VALID)
#define ADC_DATA			(ADC.CDR[1].B.CDATA)

// Function prototypes
uint8_t  	boolGetOnVerticalSync	(void);
uint32_t 	u32GetPixel				(uint8_t line, uint8_t position);
void 		vfnInit_MiniTS 			(void);
void 		readLines				(uint8_t tempwanted);
uint8_t     getLineCounter          (void);
void  		initLineSelector		(void);
uint8_t  	selectLine				(uint8_t line);
uint8_t  	deSelectLine			(uint8_t line);