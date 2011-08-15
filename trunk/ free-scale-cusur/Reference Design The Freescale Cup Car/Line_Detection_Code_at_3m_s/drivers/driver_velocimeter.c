#include "driver_velocimeter.h"
#include "SROM.h"

uint16_t RecDataMaster;           /* Data recieved on master SPI */

void initDSPI_0(void) {
  DSPI_0.MCR.R = 0x80010001;     /* Configure DSPI_0 as master */
  DSPI_0.CTAR[0].B.DBR=0;		//no double baud
  DSPI_0.CTAR[0].B.FMSZ=0b0111;	//8 bits
  DSPI_0.CTAR[0].B.CPOL=1;		//pol
  DSPI_0.CTAR[0].B.CPHA=1;		//clock phase
  DSPI_0.CTAR[0].B.LSBFE=0;		//msb first
  
  DSPI_0.CTAR[0].B.PDT=0b01;	//3*  |
  DSPI_0.CTAR[0].B.DT=0b1011;	//4096|=12288->12288/64MHz=192us
  
  DSPI_0.CTAR[0].B.PBR=0b00;	//2*|
  DSPI_0.CTAR[0].B.BR=0b0101;	//32|=64->64MHz/64=1MHz freq
    
  DSPI_0.CTAR[0].B.PCSSCK=0b00;	//1*  |
  DSPI_0.CTAR[0].B.CSSCK=0b1011;//4096|=4096->4096/64MHz=64us b4
   
  DSPI_0.CTAR[0].B.PASC=0b00;	//1*  |
  DSPI_0.CTAR[0].B.ASC=0b1011;	//4096|=4096->4096/64MHz=64us afta
  
  DSPI_0.MCR.B.HALT = 0x0;	     /* Exit HALT mode: go from STOPPED to RUNNING state*/
  SIU.PCR[13].R = 0x0604;        /* //pin44 PA13//MPC56xxB: Config pad as DSPI_0 SOUT output */
  SIU.PCR[12].R = 0x0103;        /* //pin45 PA12//MPC56xxB: Config pad as DSPI_0 SIN input */
  SIU.PCR[14].R = 0x0604;        /* //pin42 PA14//MPC56xxB: Config pad as DSPI_0 SCK output */
  SIU.PCR[15].R = 0x0604;        /* //pin40 Pa15//MPC56xxB: Config pad as DSPI_0 PCS0 output */	
}

void ReadDataDSPI_0(void) {
  while (DSPI_0.SR.B.RFDF != 1){}  /* Wait for Receive FIFO Drain Flag = 1 */
  RecDataMaster = DSPI_0.POPR.R;   /* Read data received by master SPI */
  DSPI_0.SR.R = 0x90020000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */
}

void delay(uint32_t times)
{
	uint32_t ind;
	for(ind=0;ind<times*100;ind++);
}

void write_spi(uint8_t address,uint8_t txdata)
{
	SEND_SPI_CS(0x80+address);
    ReadDataDSPI_0();
	SEND_SPI(txdata);
    ReadDataDSPI_0();
}

void read_spi(uint8_t address)
{
	SEND_SPI_CS(address);
    ReadDataDSPI_0();
    SEND_SPI(0);
    ReadDataDSPI_0();
}

void srom_download(void)
{
	uint16_t ind;
	
	SEND_SPI_CS(0xE2);
    ReadDataDSPI_0();
    
    for(ind=0;ind<3069;ind++)
    {
        SEND_SPI_CS(SROM[ind]);
    	ReadDataDSPI_0();	
    }
    SEND_SPI(SROM[3069]);
    ReadDataDSPI_0();
}
void init_velocimeter(void)
{
	//init registers
	initDSPI_0();           // Initialize DSPI_0 as master SPI and init CTAR0

	//powerup
	read_spi(0x00);  		//dummy read to reset port
	write_spi(0x3A,0x5A);	//write to power up reset
	delay(10000);			//wait at least 50ms
	read_spi(0x02);			//read registers 0x02 to 0x06
	read_spi(0x03);
	read_spi(0x04);
	read_spi(0x05);
	read_spi(0x06);
	write_spi(0x39,0x02);	//write 0x02 to config 4 (select 3k SROM)
	write_spi(0x13,0x1D);	//write 0x1d to initialize srom
	delay(100);				//wait for one frame
	write_spi(0x13,0x18);	//write 0x18 to start srom download
	srom_download();		//download srom
	delay(100);
	write_spi(0x20,0x80);	//clear last bit from laser nen

	write_spi(0x02,0x00);	//clear motion register
}

uint32_t dist_velocimeter(void)
{
	int16_t x,y;
	uint32_t d2=0;
	read_spi(0x02);		//read motion register
	if(RecDataMaster&0x80)//if motion ocurred
	{
		read_spi(0x03);	//read delta X L
		x=RecDataMaster;
		read_spi(0x04);	//read delta X H
		x+=RecDataMaster<<8;
		read_spi(0x05);	//read delta Y L
		y=RecDataMaster;
		read_spi(0x06);	//read delta Y H
		y+=RecDataMaster<<8;
		
		d2=((int32_t)x*(int32_t)x)+((int32_t)y*(int32_t)y);
		
		write_spi(0x02,0x00);//clear motion register
	}
	return d2;
}

uint32_t vel_velocimeter(void)
{
	int16_t x,y;
	uint32_t d2=0;
	write_spi(0x02,0x00);//clear motion register
	delay(1000);
	read_spi(0x02);		//read motion register
	if(RecDataMaster&0x80)//if motion ocurred
	{
		read_spi(0x03);	//read delta X L
		x=RecDataMaster;
		read_spi(0x04);	//read delta X H
		x+=RecDataMaster<<8;
		read_spi(0x05);	//read delta Y L
		y=RecDataMaster;
		read_spi(0x06);	//read delta Y H
		y+=RecDataMaster<<8;
		
		d2=((int32_t)x*(int32_t)x)+((int32_t)y*(int32_t)y);
		
		write_spi(0x02,0x00);//clear motion register
	}
	return d2*2;
}