#include "dataflash.h"
#include "general.h"
#include <inavr.h>
#include <ioavr.h>
#include <iom8.h>
#include "sound.h"
#include "spifunc.h"


extern  char Sound_Buffer[BUFFER_SIZE];
extern unsigned long int floor_num[MAX_PH_TRACK][2];



//void play_data_flash(char MUS_State)
void play_data_flash(unsigned long int the_byte)

{
      //
     char first_byte_page, second_byte_page, start_byte_add;
     first_byte_page =((char)(the_byte >> 6)); //| 0x80; //6
     second_byte_page=((char)(the_byte << 2));// & 0xfc; //2
     start_byte_add=0x00;
     
    
     PORTB &= ~DF_CHIP_SELECT;
     
     RD_SPI(Main_Mem_Read); 
     
     RD_SPI(first_byte_page);   // transfer page addres with 2 byte A_23 - A_10      
     RD_SPI(second_byte_page);        
     RD_SPI(start_byte_add);  
     
     
     
     //write_SPI(0x00);
     RD_SPI(0x00); 
     RD_SPI(0x00); 
     RD_SPI(0x00); 
     RD_SPI(0x00);
     
     
     for(unsigned int write_index=0; write_index<BUFFER_SIZE; write_index++)
     {          
          Sound_Buffer[write_index]=RD_SPI(0x00); //write the transfer data to the internal buffer
     }
     
      PORTB |= DF_CHIP_SELECT; 
}

void set_floor_num(char ding_select)
{
      if(ding_select==1)
      {
            for(char index1=0; index1<=42; index1++ )
            {
                  floor_num[index1][0]=0;
                  floor_num[index1][1]=0;
            }
            floor_num[36][0]=DING_START_BYTE;
            floor_num[36][1]=DING_STOP_BYTE;            
      }
      else
      {
            floor_num[0][0]=FLOOR_GROUND_START_BYTE;
            floor_num[0][1]=FLOOR_GROUND_STOP_BYTE;
            floor_num[1][0]=FLOOR_01_START_BYTE;
            floor_num[1][1]=FLOOR_01_STOP_BYTE;
            floor_num[2][0]=FLOOR_02_START_BYTE;
            floor_num[2][1]=FLOOR_02_STOP_BYTE;
            floor_num[3][0]=FLOOR_03_START_BYTE;
            floor_num[3][1]=FLOOR_03_STOP_BYTE;
            floor_num[4][0]=FLOOR_04_START_BYTE;
            floor_num[4][1]=FLOOR_04_STOP_BYTE;
            floor_num[5][0]=FLOOR_05_START_BYTE;
            floor_num[5][1]=FLOOR_05_STOP_BYTE;
            floor_num[6][0]=FLOOR_06_START_BYTE;
            floor_num[6][1]=FLOOR_06_STOP_BYTE;
            floor_num[7][0]=FLOOR_07_START_BYTE;
            floor_num[7][1]=FLOOR_07_STOP_BYTE;   
            floor_num[8][0]=FLOOR_08_START_BYTE;
            floor_num[8][1]=FLOOR_08_STOP_BYTE;
            floor_num[9][0]=FLOOR_09_START_BYTE;
            floor_num[9][1]=FLOOR_09_STOP_BYTE;
            floor_num[10][0]=FLOOR_10_START_BYTE;
            floor_num[10][1]=FLOOR_10_STOP_BYTE;
            floor_num[11][0]=FLOOR_11_START_BYTE;
            floor_num[11][1]=FLOOR_11_STOP_BYTE;
            floor_num[12][0]=FLOOR_12_START_BYTE;
            floor_num[12][1]=FLOOR_12_STOP_BYTE;
            floor_num[13][0]=FLOOR_13_START_BYTE;
            floor_num[13][1]=FLOOR_13_STOP_BYTE;
            floor_num[14][0]=FLOOR_14_START_BYTE;
            floor_num[14][1]=FLOOR_14_STOP_BYTE;
            floor_num[15][0]=FLOOR_15_START_BYTE;
            floor_num[15][1]=FLOOR_15_STOP_BYTE;
            floor_num[16][0]=FLOOR_16_START_BYTE;
            floor_num[16][1]=FLOOR_16_STOP_BYTE;
            floor_num[17][0]=FLOOR_17_START_BYTE;
            floor_num[17][1]=FLOOR_17_STOP_BYTE;
            floor_num[18][0]=FLOOR_18_START_BYTE;
            floor_num[18][1]=FLOOR_18_STOP_BYTE;
            floor_num[19][0]=FLOOR_19_START_BYTE;
            floor_num[19][1]=FLOOR_19_STOP_BYTE;
            floor_num[20][0]=FLOOR__1_START_BYTE;
            floor_num[20][1]=FLOOR__1_STOP_BYTE;
            floor_num[21][0]=FLOOR__2_START_BYTE;
            floor_num[21][1]=FLOOR__2_STOP_BYTE;
            floor_num[22][0]=FLOOR__3_START_BYTE;
            floor_num[22][1]=FLOOR__3_STOP_BYTE;
            floor_num[23][0]=FLOOR__4_START_BYTE;
            floor_num[23][1]=FLOOR__4_STOP_BYTE;
            floor_num[24][0]=FLOOR__5_START_BYTE;
            floor_num[24][1]=FLOOR__5_STOP_BYTE;
            floor_num[25][0]=FLOOR__6_START_BYTE;
            floor_num[25][1]=FLOOR__6_STOP_BYTE;
            floor_num[26][0]=FLOOR__7_START_BYTE;
            floor_num[26][1]=FLOOR__7_STOP_BYTE;
            floor_num[27][0]=FLOOR__8_START_BYTE;
            floor_num[27][1]=FLOOR__8_STOP_BYTE;
            floor_num[28][0]=FLOOR__9_START_BYTE;
            floor_num[28][1]=FLOOR__9_STOP_BYTE;
            floor_num[29][0]=FLOOR_UNDERGROUNFD_START_BYTE;
            floor_num[29][1]=FLOOR_UNDERGROUNFD_STOP_BYTE;
            floor_num[30][0]=FLOOR_LOBBY_START_BYTE;
            floor_num[30][1]=FLOOR_LOBBY_STOP_BYTE;
            floor_num[31][0]=FLOOR_PARKING_START_BYTE;
            floor_num[31][1]=FLOOR_PARKING_STOP_BYTE;
            floor_num[32][0]=0;
            floor_num[32][1]=0;
            floor_num[33][0]=EMERGENCY_RESCUE_START_BYTE;
            floor_num[33][1]=EMERGENCY_RESCUE_STOP_BYTE;
            floor_num[34][0]=DOOR_OPEN_START_BYTE;
            floor_num[34][1]=DOOR_OPEN_STOP_BYTE;
            floor_num[35][0]=OVER_LOAD_START_BYTE;
            floor_num[35][1]=OVER_LOAD_STOP_BYTE;
            floor_num[36][0]=DING_START_BYTE;
            floor_num[36][1]=DING_STOP_BYTE;
            floor_num[37][0]=0;
            floor_num[37][1]=0;
            floor_num[38][0]=MUSIC_START_BYTE;
            floor_num[38][1]=MUSIC_STOP_BYTE;
            floor_num[39][0]=0;
            floor_num[39][1]=0;
            floor_num[40][0]=0;
            floor_num[40][1]=0;
            floor_num[41][0]=0;
            floor_num[41][1]=0;
            floor_num[42][0]=0;
            floor_num[42][1]=0;
      }
      
}