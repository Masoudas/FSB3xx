#include"spifunc.h"
#include <inavr.h>
#include <ioavr.h>
#include <iom8.h>


char RD_SPI(unsigned char spi_data)
{
     //char spi_data;  
     SPDR = spi_data;
     while (!(SPSR & 0x80));             // wait for data transfer to be completed
     spi_data=SPDR;
     return SPDR;
     
}