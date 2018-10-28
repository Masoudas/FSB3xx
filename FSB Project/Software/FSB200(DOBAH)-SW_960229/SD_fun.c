#include "SD_fun.h"
#include <inavr.h>
#include <ioavr.h>
#include "general.h"
#include"spifunc.h"

char SD_init(void)
{
     int i=0xffff;
     unsigned char res=0x00;
     ///enable CS
     CLEARBIT(PORTB,2);
     
     ///send 80 clock while SD power stabilizes
     for(i=0;i<80; i++)
     {
           __watchdog_reset();
          RD_SPI(0xff);
     }
     
     ///send command 0 the crc=95h will send in all situations 
     // the command will start 
     SD_command(0,0);
     
     //wait for response
     res=SD_response();
     if(res!=0x01) ///error accured R1 format(it is different from the code) show the type(R1)          
     {
          //error accured          
          SD_release();
          return 0;
     }
     
     ////in the free code cmd1 also send to the card but we send command 41
     
     i=0xffff;
     SD_command(55,0);
     res=SD_response();     
     SD_command(41,0);
     res=SD_response();
     
     
     while ((res != 0) && (--i))	// wait for it
     {
           __watchdog_reset();
          SD_command(55,0);
          SD_response();     
          SD_command(41,0);
          res=SD_response();	// send CMD1 - activate card init
     }
      __watchdog_reset();
     if(i==0)
          return 0;
     return 1;       
}


void SD_command(char command,long int arguman)
{
     ///// send command | 0100 0000
     
     CLEARBIT(PORTB,2);
     RD_SPI(0xff);// dummy byte
     
     ///// send command | 0100 0000
     char test=command |0x40;
     RD_SPI(test);
     
     
     test=arguman>>24;
     RD_SPI(test); 
     test=arguman>>16;
     RD_SPI(test);
     
     test=arguman>>8;
     RD_SPI(test);
     test=arguman;
     RD_SPI(test); 
     
     
     //// write CRC for cmd0 the CRC should be send for other cmd is ignored
     RD_SPI(0x95);
}

char SD_response(void)
{
     long int i = 0xffff;
     char b = 0xff;
     
     while ((b == 0xff) && (--i)) //the msb should be zero and if others are 1 means an error accured
     {
           __watchdog_reset();
          b = RD_SPI(0xff);
     }
     return b;
     
}


char SD_datatoken(void)
{
     long int i = 0xffff;
     char b = 0xff;
     
     while ((b != 0xfe) && (--i)) //the msb should be zero and if others are 1 means an error accured
     {
           __watchdog_reset();
          b = RD_SPI(0xff);
     }
     return b;
}



char SD_readsector(long int SD_add, char *buf)
{
     unsigned int i;
     unsigned char res;
     // SD_command(16,512);
     // res=SD_response();
     //if(res ==0x00)          
     
     SD_command(17, SD_add<<9);
     res=SD_response();
     
     if(res!=0x00) ///data error accured
     {
          SD_release();
          return 0;          
     }
     res=RD_SPI(0xff);//SD_response();
     
     res=SD_datatoken();
     if(res!=0xfe)
     {          
          SD_release();
          return 0;
     }
     
     for(i=0;i<512; i++)
     {
           __watchdog_reset();
          buf[i]=RD_SPI(0xff);
     }
     RD_SPI(0xff);
     RD_SPI(0xff);
     SD_release();
     return 1;
}

char SD_writesector(long int lba, char *buf)
{
     unsigned int i=0;
     SD_command(24,lba<<9);
     //check the data response 
     if(SD_response())
     {
          SD_release();
          return 0;
     }
     
     
     //// send the data token      
     RD_SPI(0xfe);
     //SETBIT(PORTD,0);
     ////send data to the 
     for(i=0;i<512;i++)
     {
          RD_SPI(*buf++);
     }
     RD_SPI(0xff);
     RD_SPI(0xff);
     i=0xffff;
     while(!SD_response()&&(--i));
     SD_release();
     if(!i)
     {
          return(0);
     }
     else
     {
          SD_command(13,0);
          
          ///the format of response for cmd13 is 16 bit (r2)
          i=RD_SPI(0xff);
          i=i<<8;
          i+=RD_SPI(0xff);          
          
          return(1);
     }
}


void SD_release(void)
{
     for(char i=0;i<0xff;i++)
     {
          __watchdog_reset();
          RD_SPI(0xff);
     }
     SETBIT(PORTB,2);
     
}
