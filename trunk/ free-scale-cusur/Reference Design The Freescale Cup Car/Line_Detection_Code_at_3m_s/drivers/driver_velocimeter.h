#include "MPC5604B_M27V.h"		// For register definition

#define SEND_SPI(x)		DSPI_0.PUSHR.R=0x08010000+(x)
#define SEND_SPI_CS(x)	DSPI_0.PUSHR.R=0x88010000+(x)

void initDSPI_0(void);
void ReadDataDSPI_0(void);
void delay(uint32_t times);
void write_spi(uint8_t address,uint8_t txdata);
void read_spi(uint8_t address);
void srom_download(void);
void init_velocimeter(void);
uint32_t dist_velocimeter(void);
uint32_t vel_velocimeter(void);