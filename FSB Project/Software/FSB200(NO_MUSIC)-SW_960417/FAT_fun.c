#include <ioavr.h>
#include <inavr.h>
#include "SD_fun.h"
#include "FAT_fun.h"
#include "general.h"
extern  char Sound_Buffer[BUFFER_SIZE];


unsigned long int floor_num[MAX_PH_TRACK][2];
unsigned char max_num_floor=1;
unsigned int SecPerClu;
unsigned  int root_directory;
unsigned long int data_sector; 
unsigned long int cluster_num;
//unsigned long int start_sec=0;
//unsigned long int stop_sec=0;
unsigned long int file_size;
      // unsigned int cluster_num;
       
       unsigned int file_number=0;

unsigned char fat_parameter_init(void)
 {
       unsigned long int zero_sector=0;
       unsigned int RootEntCnt;
       unsigned char RsvdSecCnt=0;
       unsigned int FATSz16=0;
       char *boot_sect="MSDOS5.0";
       unsigned char flag;
       unsigned char i=0;
       flag=1;
       
       
       //fat_parameter_init();
       while(flag)///////////finding the boot sector
        {
             __watchdog_reset();
              if(!SD_readsector(zero_sector,Sound_Buffer))
               {
                     return 0;
               }
              
              flag=0;
              for(i=0;i<8;i++)
               {
                     if((Sound_Buffer[i+3])!=(boot_sect[i]))
                      {                    
                            flag=1;                       
                      }
               }      
              if(flag==0)
               {}    
              else
               {
                     zero_sector++; 
               }
              
        }      
       
       SecPerClu=Sound_Buffer[13];
       
       RsvdSecCnt=Sound_Buffer[15];
       RsvdSecCnt=(RsvdSecCnt<<8);
       RsvdSecCnt+=Sound_Buffer[14];////it is little endian
       
       FATSz16=Sound_Buffer[23];
       FATSz16=(FATSz16<<8);
       FATSz16+=Sound_Buffer[22];////it is little endian
       
       ///RootEntCnt
       
       RootEntCnt=Sound_Buffer[18];
       RootEntCnt=(RootEntCnt<<8);
       RootEntCnt+=Sound_Buffer[17];////it is little endian
       
       
       root_directory=zero_sector+RsvdSecCnt+(FATSz16*2);
       
       data_sector=root_directory +(((RootEntCnt*32)+511)/512); 
       return 1;
 } 


void set_default_value(void)
 {
    for(unsigned char i=0;i<MAX_PH_TRACK;i++)
     {
       floor_num[i][0]=0;
       floor_num[i][1]=0;
     }
       
 }
unsigned char get_floor_sectors(void)
 {
       
      
      
      
       unsigned char floor_index=0;
       unsigned char flag=1;
       
       unsigned  int root_dir=root_directory;
       
      // unsigned long int check_value=0;  /// there is no ram for adding the new variable
        set_default_value();
       SD_readsector(root_directory,Sound_Buffer);
       
       while(flag)
        {
              __watchdog_reset();
              if((Sound_Buffer[file_number]<='9')&&(Sound_Buffer[file_number]>='0'))
               {
                   
                     
                     floor_index=(10*(Sound_Buffer[file_number]-'0'))+(Sound_Buffer[1+file_number]-'0');        
                     file_size=Sound_Buffer[31+file_number];
                     file_size=file_size<<8;                
                     file_size+=Sound_Buffer[30+file_number];
                     file_size=file_size<<8;                
                     file_size+=Sound_Buffer[29+file_number];
                     file_size=file_size<<8;                
                     file_size+=Sound_Buffer[28+file_number];
                     file_size/=512;         
                     
                     cluster_num=Sound_Buffer[27+file_number];
                     cluster_num=cluster_num<<8;
                     cluster_num+=Sound_Buffer[26+file_number];
                     if(floor_index<MAX_PH_TRACK)
                      {                          
                           
                           floor_num[floor_index][0]=((cluster_num-2)*SecPerClu)+data_sector+1;
                           floor_num[floor_index][1]=floor_num[floor_index][0]+file_size-5;//start_sector+file_size-5; 
                           
                           if(floor_num[floor_index][0]>floor_num[floor_index][1])                                           
                            {
                                 floor_num[floor_index][0]=0;
                                 floor_num[floor_index][1]=0;
                                 
                            }
                           if(floor_index>max_num_floor)
                                max_num_floor= floor_index;      
                      } 
                     flag=1;                    
                     file_number+=32;   
                     if(file_number>=512)
                      {                                                               
                            root_dir++;
                            SD_readsector(root_dir,Sound_Buffer);
                            file_number=0;
                            
                      }   
               }                                                                    
              else if(Sound_Buffer[file_number]==0)  ///the root directory contain is finished
               {
                     flag=0;
               }   
              /*else if(Sound_Buffer[file_number]=='W')
              {
              welcome_iden=1;
              file_size=Sound_Buffer[31+file_number];
              file_size=file_size<<8;                
              file_size+=Sound_Buffer[30+file_number];
              file_size=file_size<<8;                
              file_size+=Sound_Buffer[29+file_number];
              file_size=file_size<<8;                
              file_size+=Sound_Buffer[28+file_number];
              file_size/=512;         
              
              cluster_num=Sound_Buffer[27+file_number];
              cluster_num=cluster_num<<8;
              cluster_num+=Sound_Buffer[26+file_number]; 
              
              welcome_start_sector=((cluster_num-2)*SecPerClu)+data_sector+1;            
              welcome_stop_sector=welcome_start_sector+file_size-5;//start_sector+file_size-5;
              file_number+=32;
              if(file_number>=512)
              {                                                
              root_dir++;
              SD_readsector(root_dir,Sound_Buffer);  
              file_number=0;
        }
              flag=1;
              
        } */               
              else  ///it is a deleted file or an unsupported format
               {
                     file_number+=32;
                     if(file_number>=512)
                      {                                                
                            root_dir++;
                            SD_readsector(root_dir,Sound_Buffer);  
                            file_number=0;
                      }
                     flag=1;
               } 
        }
       
       return (max_num_floor);
       
       
       
 }
