#include <inavr.h>
#include <ioavr.h>
#include "SD_fun.h"
#include "general.h"
#include "PORTS_init.h"
#include "inputs_check.h"
#include "FAT_fun.h"
#include "dataflash.h"
#include"spifunc.h"


////////////////////////////////////////////////////////////////////////////////

extern unsigned long int floor_num[MAX_PH_TRACK][2];
////////////////////////////////////////////////////////////////////////////////
enum SYSTEM_STate
{
     Ready,
     Busy,
     Wait
}Status_register;

enum Status
{
     OK,
     Fail
};

///////////////////////////////////////////////////////////////////////////////
unsigned int system_time=0;
unsigned int music_delay_flag; 
char Sound_Buffer[BUFFER_SIZE];
char DOB_OVL_F_FLAG=0;// 0 shows that DOB message is finished  1
unsigned char keys_temp=0;
unsigned char DOB_delay_flag=0;// 0-9 when DOB should not be played 10 when it should be played
unsigned char ding_select=0; // if ding_select=0 it is in ding only mode (only play ding)
                             // if ding_selcet=1 it is in normal mode

//unsigned char albume_delay_flag=0;// 

unsigned char welcome_flag=0;
char SD_read=1;
unsigned int buffer_counter=0;
unsigned long int sector, start_sector, stop_sector, music_sector;

///////////////////////// the variable of system state and flags

unsigned char start_up_flag=0; // 0 the start up delay not finished 
//1 after start up delay

unsigned char finished_flag=1;// if 1 the state is finished 
unsigned trg_active_flag=0;   //if 1 the fst activated and the floor speach won't be played yet 
unsigned char current_ALBUME=0;
unsigned char max_sector_num=0;
unsigned char emg_flag=1;
int       flash_page_size =0;        // Denotes the size of flash pages.   
                                          

///////////////////////// the inputs variable
unsigned char control_register=0x00, ctrl_temp=0x00, emg_temp=0x00, ctrl_count=0x00; 
unsigned char numerator_register=0x00, num_temp=0x00, num_count=0x00;


////////////************** General prototype ***********************////////////
/////////////********************************************************///////////
void setup(void);
Total_state GET_STATE(Total_state last_state);
Total_state GET_Floor_STATE( Total_state last_state);
unsigned char ctrl_debounce_check(void);
unsigned char numerator_debounce_check(void);
unsigned char floor_num_find(void);
unsigned char floor_byte_find(void);
void timer_update(void);
unsigned char ALBUME_sector_define(unsigned char);
void Default_set(void);
void change_volume(char key_last_state);
void Flash_Page_Size(void);
void Set_Page_Size(void);        // This function changes the page size of flash to 528bytes if it is 512 bytes.

unsigned char SD_DF_OPT=1;
unsigned albume_mode=0; ///1 is in albume mode 0 isnot in albume mode
/////change 0=data flash
unsigned int read_time_number=500;//, buffer_size=528;
char key_per_state=0x00;
//////////////////////////////////////main
char SD_Flash_count=0;///counter to show the number of reading each devices unsuccesfuly
#define    SD_Flash_COUNT       6


unsigned char digit_volume_level=0;
void main()
{  
     
     system_time=START_UP_DELAY; 
     WDTCR=0x1F; ///enable watch dog timer 
     WDTCR=0x1F; ///enable watch dog timer       
     Total_state  per_state=SILENCE, state=SILENCE;   
     char SD_STATUS=0;
     SD_ERROR_ID     flag_error=NO_ERROR;
     char max_alb=0;
     unsigned char music_index=0; 
     unsigned char floor_index=0;
     Status_register=Ready;    
     
     Default_set();
     setup();
   
     SD_STATUS=SD_init();
          while ((!(SD_STATUS))&&(SD_Flash_count<=SD_Flash_COUNT))
          {               
                SD_Flash_count++;
               __watchdog_reset();
               SD_STATUS=SD_init();
          }
          if(SD_Flash_count<=SD_Flash_COUNT)
          {
                SD_DF_OPT=1;
          }
          else
          {
                SD_DF_OPT=0;
          }
          
     
     if(SD_DF_OPT==1)//// if it read from SD
      {
          read_time_number=420; 
          SD_STATUS=SD_init();
          while (!(SD_STATUS))
          {
               __watchdog_reset();
               SD_STATUS=SD_init();
          }
          SD_command(16,512);///define the blocklength of SD it is alwayes 512 
          SD_response(); 
          SD_release();
          
          
          while(! (fat_parameter_init()))
          {           
               __watchdog_reset();
          }      
          max_sector_num=get_floor_sectors();
          SD_release();
          
          /////////////eeprom set for albume change /////////////////
          char alb_defen_ID;
          ///0x10 for keeping the default value situation
          ///0x20 for keeping the number of albume
          __EEGET(alb_defen_ID,0x10);
          if(alb_defen_ID==10)// the albume is  defined by user and should be initial from EEPROM
          {
               __EEGET(current_ALBUME,0x20);
               if(((current_ALBUME==4)&&(max_sector_num<=MUSICA3_TRACK))||((current_ALBUME==3)&&(max_sector_num<=MUSICA2_TRACK))||((current_ALBUME==2)&&(max_sector_num<=MUSICA1_TRACK))||((current_ALBUME==1)&&(max_sector_num<=MUSICA0_TRACK)))
               {
                    current_ALBUME=0;
                    __EEPUT(0x20,0); 
               }
          }
          else
          {
               __EEPUT(0x10,10);
               __EEPUT(0x20,0);
               current_ALBUME=0;
          }
          ALBUME_sector_define(music_index);
          music_sector= start_sector;
          sector=start_sector;
          
          
          SD_read=1;
          finished_flag=1;
     }
     else
     {
          read_time_number=500;
          set_floor_num(ding_select);
          ALBUME_sector_define(music_index);
          music_sector= start_sector;
          sector=start_sector;
     }
     char vol_defen_ID=0;
     
     __EEGET(vol_defen_ID,0x45);
     if(vol_defen_ID==10)// the albume is defined by user and should be initial from EEPROM
     {
          __EEGET(digit_volume_level,0x35);
          if(digit_volume_level>=0 && digit_volume_level<=MAX_VOLUME_LEVEL)
          {
          }
          else
          {
               digit_volume_level=MAX_VOLUME_LEVEL;
          }
          
     }
     else
     {
          __EEPUT(0x45,10);  
          __EEPUT(0x35,MAX_VOLUME_LEVEL); 
          digit_volume_level=MAX_VOLUME_LEVEL;
     }
     while(1)
     {              
          if(SD_DF_OPT==1)//// if it read from SD
          {
               if(flag_error!=NO_ERROR)
               {
                    finished_flag=1;               
                    SD_STATUS=SD_init();
                    SD_command(16,512);
                    SD_response();
                    SD_release();                
                    while(!(fat_parameter_init()))
                    {             
                         SD_STATUS=SD_init();
                         SD_command(16,512);
                         SD_response();
                         SD_release();
                         __watchdog_reset();
                         __EEPUT(0x18,0x0A);                                     
                         
                    }
                    
                    
                    //Default_set();
                    finished_flag=0;
                    //for(;;);
                    
               }
          }
 
          if((start_up_flag))
          {   
               if(SD_read==1)
               { 
                    SD_read=0;           
                    sector++;
                    if (state==MUS)
                    {
                         music_sector++;
                    }
                    if(sector> stop_sector)
                    { 
                         if(state==MUS)
                         {
                              
                              if(max_sector_num > (MUSICA4_TRACK+music_index))
                              {
                                   music_index++;                                                  
                              }
                              else
                              {
                                   music_index=0;
                              } 
                              ALBUME_sector_define(music_index);
                              music_sector= start_sector;
                              sector=start_sector;
                              
                              
                         }
                         else
                         {
                               albume_mode=0;
                              finished_flag=1;  
                              SETBIT(PORTB,2);
                         }
                    } 
                    else
                    {
                         if(SD_DF_OPT==1)//// if it reads from SD
                         {
                              if(SD_readsector(sector,Sound_Buffer))
                              {
                                   flag_error=NO_ERROR;
                              }
                              else
                              {
                                   SD_STATUS=SD_init();
                                   if(SD_STATUS)
                                   {
                                        SD_command(16,512);
                                        SD_response();
                                        SD_release();
                                        flag_error=NO_ERROR;
                                   }
                                   else
                                   {
                                        flag_error=SD_READ_ERROR;
                                   }
                                   
                                   
                                   
                              }
                         }
                         else
                         {
                              play_data_flash(sector);
                              
                         }
                    }
               }  
               
               if(Status_register==Ready)
               { 
                    timer_update();
                    Status_register=Busy;
                    
                    
                    __watchdog_reset();
                    
                    if(system_time<1)
                    {
                         if(ctrl_debounce_check()&& numerator_debounce_check())
                         { 
                              if((state!=SILENCE)&&(state!=CHG_ALBUME)&&(albume_mode==0))
                              {
                                   change_volume(key_per_state);
                              }
                              key_per_state=(ctrl_temp & KEYS_A_n);///FOR DEBOUNCE THE USER SHOULD RELEASE THE KEY AND HOLD IT AGAIN TO WORK
                              
                            /* if((ctrl_input & KEYS_A_n)==KEYS_P_enable)
                             {
                                CLEARBIT(ALB_mode_output,ALB_mode_in);   
                             
                             }
                             else
                             {
                                   SETBIT(ALB_mode_output,ALB_mode_in);
                             }*/
                              ctrl_count=0;// for the next time to get the inputs debounce
                              num_count=0;  
                              
                              
                              per_state=state;                                          
                              state=GET_STATE(per_state);                                         
                              keys_temp=(ctrl_temp & KEYS_A_n);
                              if((state==per_state))
                              {                                    
                                    if((SD_DF_OPT==1)&&(state==CHG_ALBUME))
                                    {
                                          max_alb=(max_sector_num > MUSICA3_TRACK) ? MAX_ALBUME_NUM : (max_sector_num-MUSICA0_TRACK);
                                          if(( keys_temp==KEYS_P_enable)||(keys_temp==KEYS_N_enable))
                                          {
                                                if(( keys_temp==KEYS_P_enable)&&(current_ALBUME<max_alb))
                                                {
                                                      current_ALBUME++;
                                                }
                                                else
                                                {
                                                      if((keys_temp==KEYS_N_enable)&&(current_ALBUME>0))
                                                      {
                                                            current_ALBUME--;
                                                            
                                                      }
                                                }
                                                __EEPUT(0x20,current_ALBUME); 
                                                ALBUME_sector_define(music_index);
                                                music_sector= start_sector;
                                                sector=music_sector;
                                                finished_flag=0;
                                          }
                                          
                                          
                                    }
                              }
                              else  //// this is a new state 
                              {                                           
                                   switch(state)
                                   {
                                        
                                   case EMR: 
                                         //albume_mode=0;
                                        finished_flag=0;
                                        start_sector = floor_num[EMERG_TRACK][0];
                                        stop_sector  = floor_num[EMERG_TRACK][1];
                                        sector=start_sector;
                                        break;                                    
                                        
                                   case DOB:
                                         // albume_mode=0;
                                        finished_flag=0;
                                        DOB_OVL_F_FLAG=1;
                                        start_sector = floor_num[DOB_TRACK][0];
                                        stop_sector  = floor_num[DOB_TRACK][1];                               
                                        sector=start_sector;
                                        break;
                                        
                                   case OVL:
                                         // albume_mode=0;
                                        finished_flag=0;
                                        start_sector = floor_num[OVL_TRACK][0];
                                        stop_sector  = floor_num[OVL_TRACK][1];
                                        sector=start_sector;                                        
                                        break;
                                        
                                   case MUS:  
                                        finished_flag=0;
                                        ALBUME_sector_define(music_index);
                                        sector=music_sector;
                                        
                                        break;
                                        
                                   case DING:
                                         // albume_mode=0;
                                        finished_flag=0;
                                        start_sector = floor_num[DING_TRACK][0];
                                        stop_sector  = floor_num[DING_TRACK][1];
                                        sector=start_sector;
                                        break;
                                        
                                   case FLOORS: 
                                         // albume_mode=0;
                                        finished_flag=0;                                        
                                        floor_index=floor_byte_find();                                  
                                        if((floor_index==lobby_index)||(floor_index==rest_index)||(floor_index==gnd_index)||(floor_index==par_index))
                                        {
                                             welcome_flag=1;
                                        }
                                        else
                                        {
                                             welcome_flag=0;
                                        }
                                        if(floor_index<=35)
                                        {                                             
                                             start_sector = floor_num[floor_index][0];
                                             stop_sector  = floor_num[floor_index][1]; 
                                             sector=start_sector;
                                        }
                                        else
                                        {                                    
                                             state=SILENCE;
                                             trg_active_flag=0; 
                                        }
                                        break;
                                        
                                   case CHG_ALBUME:                                        
                                         CLEARBIT(ALB_mode_output,ALB_mode_in);
                                         
                                        if(SD_DF_OPT)
                                        {                                             
                                             __EEPUT(0x20,current_ALBUME); 
                                             ALBUME_sector_define(music_index);
                                             music_sector= start_sector;
                                             sector=music_sector;
                                             finished_flag=0;
                                        }
                                        break;
                                   case WEL:
                                          //albume_mode=0;
                                        finished_flag=0;
                                        start_sector = floor_num[WEL_TRACK][0];
                                        stop_sector  = floor_num[WEL_TRACK][1];
                                        sector=start_sector;
                                        break;
                                        
                                   case SILENCE:                                                 
                                        finished_flag=1;                                        
                                        break;
                                        
                                   default:
                                        
                                        finished_flag=1;
                                        break;      
                                        
                                   }
                              }
                         }
                         
                    } //system time check finish
                    
                    Status_register=Wait;  
               }///status register check 
               
          }//start up delay 
          else
          {
               if(Status_register==Ready)
               { 
                    Status_register=Wait;
                    timer_update();                  
                    __watchdog_reset();
               }
          }
          
     }
     
}



/////////////********************************************************///////////
////////////********************** functions ***********************////////////
/////////////********************************************************///////////

void change_volume(char key_last_state)
{
      char key_status=ctrl_temp & KEYS_A_n;
      if((key_last_state!=KEYS_N_n)&&(key_status==KEYS_N_enable))// IN LAST STATE THE POSITIVE KEY WAS DISABLE AND IN NEW THE KEY IS ENABLE
      { 
            if(digit_volume_level<MAX_VOLUME_LEVEL)
            {
                  digit_volume_level++;
                  __EEPUT(0x35,digit_volume_level); 
            }
      }
      else
      {
            if((key_last_state!=KEYS_P_n)&&(key_status==KEYS_P_enable))// IN LAST STATE THE POSITIVE KEY WAS DISABLE AND IN NEW THE KEY IS ENABLE
            { 
                  if(digit_volume_level>0)
                  {
                        digit_volume_level--;
                        __EEPUT(0x35,digit_volume_level); 
                  }
            }
      }     
}
//////////////////////control debounce check 
unsigned char ctrl_debounce_check(void)
{
   char ctrl_input_mod=(ctrl_input & 0xFB);
   char ctrl_input_mode2=(EMR_input & EMR_n); //modify
     
     if(ctrl_count < Debounce_num) ///debounce control inputs   
     { 
          if((ctrl_temp==ctrl_input_mod)&&(emg_temp==ctrl_input_mode2))
          {
               ctrl_count++;
               system_time=DEBOUNCE_DELAY;
               ctrl_temp=ctrl_input_mod;
               emg_temp=ctrl_input_mode2;
          }
          else
          {
               ctrl_count=0;              
               ctrl_temp=ctrl_input_mod;
               emg_temp=ctrl_input_mode2;
          } 
          
          return (0);
          
          
     }
     else
     {
          return(1);
     }
}

/////////////////////numerator debounce check
unsigned char numerator_debounce_check(void)
{
     
     
     if(num_count<Debounce_num) ///debounce control inputs   
     { 
          if(num_temp==Numr_input)
          {
               num_count++;
               system_time=DEBOUNCE_DELAY;
               num_temp=Numr_input;
          }
          else
          {
               num_count=0;
               num_temp=Numr_input;
          } 
          return (0);
          
     }
     else
     {
          return(1);
     }
}

void Default_set(void)
{
     trg_active_flag=0;
     welcome_flag=0;
     //start_up_flag=0; 
     finished_flag=1;// if 1 the state is finished  trg_active_flag=0;   //if 1 the fst activated and the floor speach won't be played yet 
     current_ALBUME=0;
     max_sector_num=0;
     emg_flag=1;
     ///////////////////////// the inputs variable
     control_register=0x00;
     ctrl_temp=0x00;
     ctrl_count=0x00; 
     numerator_register=0x00;
     num_temp=0x00;
     num_count=0x00; 
     digit_volume_level=0;
     
}

Total_state GET_STATE(Total_state last_state)
{     
     Total_state prior_state=SILENCE;    
     if((emg_temp&EMR_n)==EMR_enable)// if(control_register>=0x80) ///EMR is active high
     {
          albume_mode=0;
          prior_state=EMR;              
          if((last_state==EMR)&&(finished_flag==1))
          {
               
          }
         
     }
     else 
     {
          if(((((ctrl_temp&DOB_n)==DOB_enable))&&(DOB_delay_flag>=DOB_delay))||(DOB_OVL_F_FLAG==1))
          {  
                
               emg_flag=0;
               albume_mode=0;
               
               if((last_state==DOB)&&(finished_flag==1))
               {
                    DOB_delay_flag=0;
                    DOB_OVL_F_FLAG=0;
                    
               }
                
               if(DOB_delay_flag<DOB_delay)
               {
                    DOB_delay_flag++;
                    if(last_state==SILENCE)
                         
                    {
                          prior_state=MUS;
                    }
                    else
                         prior_state=last_state;
               }
               else
               {
                    //trg_active_flag=0;
                    prior_state=DOB;  
               }
          }
          else 
          {
               if(((ctrl_temp&OVL_n)==OVL_enable)&&(DOB_delay_flag>=OVL_delay))
               {
                     albume_mode=0;
                    emg_flag=0;
                  
                    
                    if((last_state==OVL)&&(finished_flag==1))
                         {
                              DOB_delay_flag=0;
                         }
                   if(DOB_delay_flag<OVL_delay)
                    {
                         DOB_delay_flag++;
                         if(last_state==SILENCE)
                         {
                               prior_state=MUS;
                              // music_delay_flag=MUS_a_Speach;
                         }
                         else
                              prior_state=last_state;
                              
                    }   
                    else
                    {
                        // trg_active_flag=0;
                         prior_state=OVL;  
                    }
                    
                    
               } 
               
               else 
               {
                    /* if(((ctrl_temp&OVL_n)!=OVL_enable)&&((ctrl_temp&DOB_n)!=DOB_enable))
                     {
                           DOB_delay_flag=0;
                     }*/
                     
                    if((((ctrl_temp&OVL_n)==OVL_enable)||((ctrl_temp&DOB_n)==DOB_enable)))
                    {
                         DOB_delay_flag++;
                         DOB_OVL_F_FLAG=2;
                    }
                    if((ctrl_temp&TRG_n)==TRG_enable)
                    { 
                          albume_mode=0;
                         //DOB_delay_flag=0;
                         prior_state=MUS;
                         trg_active_flag=1;
                         
                    }       
                    else {
                         if(trg_active_flag)
                         {
                              albume_mode=0;
                              //DOB_delay_flag=0;
                              prior_state=GET_Floor_STATE(last_state);                
                         }
                         else
                         {  
                              if(music_delay_flag)
                              {
                                    albume_mode=0;
                                   prior_state=MUS;
                              }
                              else
                              {
                                   if((((ctrl_temp&OVL_n)==OVL_enable)||((ctrl_temp&DOB_n)==DOB_enable)))
                                   {
                                         albume_mode=0;
                                        prior_state=MUS;
                                   }
                                   else   
                                   {
                                        if(((KEYS_input & KEYS_A_n)==KEYS_enable))
                                        { 
                                              if(albume_mode==0)
                                              {
                                                    emg_flag=0;
                                                    albume_mode=1;
                                                    prior_state=CHG_ALBUME;
                                              }
                                              else
                                              {
                                                    SETBIT(ALB_mode_output,ALB_mode_in);
                                                    albume_mode=0;
                                                    prior_state=SILENCE; 
                                              }
                                              
                                        }
                                        else
                                        {
                                             if(albume_mode==1)
                                              {
                                                  
                                                   prior_state=CHG_ALBUME;
                                              }
                                              else
                                              {
                                                   if((DOB_delay_flag<=DOB_delay)&&(DOB_OVL_F_FLAG==2))
                                                   {
                                                         CLEARBIT(ALB_mode_output,ALB_mode_in);
                                                         prior_state=MUS;
                                                         DOB_delay_flag++;
                                                         if(DOB_delay_flag>=DOB_delay)
                                                         {
                                                               DOB_delay_flag=0;
                                                               DOB_OVL_F_FLAG=0;
                                                               //SETBIT(ALB_mode_output,ALB_mode_in);
                                                         }
                                                   }
                                                   
                                                   else  
                                                   {
                                                         prior_state=SILENCE;
                                                   }
                                              }
 
                                        }
                                   }
                              }
                              
                         }
                    }
               }
          }
     }
     if(albume_mode==0)
     {
           SETBIT(ALB_mode_output,ALB_mode_in);
           //prior_state=SILENCE;
     }
     return(prior_state);
}

/////////////////////////////
Total_state GET_Floor_STATE(Total_state last_state)
{
     Total_state new_state=last_state;
     switch(last_state)
     {
     case MUS:
          new_state=DING;         
          break;
     case DING:           
          if((finished_flag)&&(last_state==DING))
          {
               new_state= FLOORS; 
               trg_active_flag=1;                     
          }
          else
          {
               new_state=DING;
          }
          break;
     case FLOORS:                          
          if((finished_flag)&&(last_state==FLOORS))
          {
               if( welcome_flag)
               {
                    new_state=WEL;
                    trg_active_flag=1;               
                    
               }
               else
               {
                    new_state=MUS;
                    music_delay_flag=MUS_a_Speach;                  
                    trg_active_flag=0;
               }
               
          }
          else
          {
               new_state=FLOORS;
          }
          break;  
     case WEL:
          if((finished_flag)&&(last_state==WEL))
          {
               new_state=MUS;
               music_delay_flag=MUS_a_Speach;                  
               trg_active_flag=0;
          }
          else
          {
               new_state=WEL;  
          }
          break;
     default:
          break;
     }
     return (new_state);
}     








/////////////********************************************************///////////
////////////********************** functions ***********************////////////
/////////////********************************************************///////////


void setup(void)
{  //// port initial ***********************************************************************************************
     SFIOR &=0xFB;
     SD_PWM_port =0x00; 
     SD_PWM_direct=0x2E;                                      
                              
     
     DDRD = 0x00;                            // define port D as input
     PORTD = 0x00;
     //Numr_direct= 0x00; 
     //Numr_port=0x00;
     
     // DDRC=0xFe;
     // PORTC=0x01;
     
     ctrl_direct=0x04;       
     ctrl_port=0x07;      
     
     //// SPI initial **************************************************************************************************
     SPCR=0x50;  ///50 the clock is focs/4
     SPSR=0x01;
     
     //// TIMER1(PWM)  initial *****************************************************************************************
     TCCR1A=0x82;
     TCCR1B=0x19;
     TCNT1H=0x00;
     TCNT1L=0x00;
     ICR1H=0x00;
     ICR1L=0xF5;
     OCR1AH=0x00;
     OCR1AL=0x00;
     OCR1BH=0x00;
     OCR1BL=0x00;
     
     
     //// TIMER0 (delay)  initial ***************************************************************************************
     TCCR0=0x02;   
     TCCR2=0x06;   //every 1 ms an interrupt will be happened
     //// TIMER interrupt initial **************************************************************************************   
     TIMSK=0x45;  // Enable compare match interrupt timer1 and ovl interrupt timer 2
     
     
     //////////////****************************************************************************************************
     __enable_interrupt();                   // enable interrupts
     
     
     ////////////// Change page size to 528 bytes if necessary *********************************************************
     //// Determining the Flash Page Size
     Flash_Page_Size();        // Determine flash page size based on majority vote.      
     if (flash_page_size == 512)        // Assign page size based on the flag.
     {
        Set_Page_Size();
     }
}
/////////////////////////////


void timer_update(void)
{
     if(system_time > 0)
     {
          system_time--;
     }
     else
     {
          system_time=0;
          start_up_flag=1;
          
     }
     if(music_delay_flag > 0)
     {
          music_delay_flag--;
     }
     else
     {
          music_delay_flag=0;  
     }
     
}



unsigned char floor_byte_find(void)
{
     unsigned char temp=0x00;
     unsigned char temp2=0x00;
     if(((num_temp & NUM___n)==NUM___n) && ((num_temp & TEN_n)==TEN_n) ) //neg and ten are disable
     {
          temp=0x00;        
     }
     else if(((num_temp & NUM___n)==NUM___n) && ((num_temp & TEN_n)==0x00))//neg is disable 
     {
          temp=10;
     }
     else if(((num_temp & NUM___n)==0x00) && ((num_temp & TEN_n)==TEN_n) )// ten is disable
     {
          temp=19;
     }
     else
     {
          temp=40;
          return(40);
     }
     temp2=floor_num_find();
     if((temp==19)&&(temp2==0)) //it is ground
          return 0;
     temp +=temp2;
     /*if(temp>25 && temp<29)
     temp=40;*/
     return(temp);
}


unsigned char floor_num_find(void)
{
     
     unsigned char temp=0;
     unsigned char in_check=(Numr_input & num_inputs_check);
     
     switch (in_check)
     {
     case Floor0:
          temp=0;            
          break;
     case Floor1:
          temp=1;
          break;
     case Floor2:
          temp=2;
          break;
     case Floor3:
          temp=3;
          break;    
     case Floor4:
          temp=4;
          break;
     case Floor5:
          temp=5;
          break;
     case Floor6:
          temp=6;
          break;    
     case Floor7:
          temp=7;
          break;
     case Floor8:
          temp=8;
          break;
     case Floor9:
          temp=9;
          break;
     case Lobby:
          temp=30;
          break;
     case Parking:
          temp=31;
          break;
     case Ground:
          temp=0;
          break;
     case UGround:
          temp=29;
          break;
     case Resturan:
          temp=32;
          break;
     default:
          temp=40; 
          break;
          
     }
     return(temp);
}



unsigned char ALBUME_sector_define(unsigned char index)
{
     if(current_ALBUME==0)
     {
          start_sector= floor_num[MUSICA0_TRACK][0];
          stop_sector = floor_num[MUSICA0_TRACK][1];
          return(  MUSICA0_TRACK);
          
     }
     else if(current_ALBUME==1)
     {                     
          start_sector= floor_num[MUSICA1_TRACK][0];
          stop_sector = floor_num[MUSICA1_TRACK][1];
          return(   MUSICA1_TRACK);
     }
     else if(current_ALBUME==2)
     {             
          start_sector= floor_num[MUSICA2_TRACK][0];
          stop_sector =floor_num[MUSICA2_TRACK][1];
          return(MUSICA2_TRACK);
     }
     else if(current_ALBUME==3)
     {                     
          start_sector= floor_num[MUSICA3_TRACK][0];
          stop_sector = floor_num[MUSICA3_TRACK][1];          
          return(MUSICA3_TRACK);
          
     }
     else 
     {
          if((MUSICA4_TRACK+index)>max_sector_num)
          {
               index=0;
          }
          start_sector= floor_num[MUSICA4_TRACK+index][0];
          stop_sector = floor_num[MUSICA4_TRACK+index][1];
          
          return(MUSICA4_TRACK+index);
     }     
     
}


void Flash_Page_Size(void) 
{
     //// Initialization
     char       read_count = 0;         // The number of times status register has been read from the flash.
     char       vote = 0;               // The number of times one is read from the flash (i.e, flash is 528 byte per page).
     char       Status_Register = 0;    // The status register of flash AT45DB321D(E). 
     char       Dont_Care_Byte = 0x00; 
    
     
     //// Main commands
     // Read status register eleven times and decide on the page size using majority logic.
     while (read_count < 10)  
     {
     PORTB &= ~DF_CHIP_SELECT; // Sending the chip select signal to initialize memory reading.
     
     RD_SPI(Status_reg_Read); // Sending the opcode E8H to initialize continuous reading.     
     Status_Register = RD_SPI(Dont_Care_Byte);
     
     PORTB |= DF_CHIP_SELECT; // The chip is deselected here.

     Status_Register &= PAGE_SIZE_BYTE; // Extract bit zero of status register.
     vote += Status_Register;   // Increment vote parameter if this bit is one.

     read_count += 1;
     }
     
     
     //// Finalization     
     // Assigning flash page size based on the votes
     if (vote >= 5)
     {
       flash_page_size = 512;
     }
     else if (vote < 5)
     {
       flash_page_size = 528;
     }    
}



void Set_Page_Size(void)
{
     char Dont_Care_Byte = 0x00;
     char status_register = 0x00;       // Denotes the current status register of flash.
     PORTB &= ~DF_CHIP_SELECT; // Sending the chip select signal to initialize memory reading.
     
     RD_SPI(PAGE_SIZE_BYTE1); // Send the first byte of opcode to change page size to 528 bytes.     
     RD_SPI(PAGE_SIZE_BYTE2); // Send the second byte.
     RD_SPI(PAGE_SIZE_BYTE3); // Send the third byte.
     RD_SPI(PAGE_SIZE_BYTE4); // Send the fourth byte.

     PORTB |= DF_CHIP_SELECT; // The chip is deselected here.
     
     PORTB &= ~DF_CHIP_SELECT; // Sending the chip select signal to initialize memory reading.
     
     RD_SPI(Status_reg_Read); // Send opcode to read status register of memory.
     status_register = RD_SPI(Dont_Care_Byte);  // Read status register of memoryy.
     
     while(!(status_register & 0x80))   // Until flash is busy, wait here.
     {
      status_register = RD_SPI(Dont_Care_Byte);
     }
       

     PORTB |= DF_CHIP_SELECT; // The chip is deselected here.
    

     
}


/////////----------------  interupts -----------------------////////// 



#pragma vector = TIMER1_OVF_vect

__interrupt void out_now(void)
{
     //char digit_volume_level2=0;
     if(buffer_counter == read_time_number)
     {
          SD_read = 1;
     }      
     
     if(finished_flag == 0)
     { 
          OCR1AH=0x00;
          OCR1AL=(Sound_Buffer[buffer_counter]>>digit_volume_level);
     } 
     
     
     buffer_counter++;
     if((read_time_number==420)&&(buffer_counter > 511))//(buffer_size-1))
     {
          buffer_counter = 0;
     }
     else
     {
          if((read_time_number==500)&&(buffer_counter > 511))
          {
               buffer_counter = 0;   
          }
     }
     
     if (buffer_counter > 500)
          {
                 if (Status_register== Wait)
                   {              
                    Status_register=Ready;
                   }
                 else  if(Status_register== Busy)
                  {              
                    __EEPUT(0x06,10);   
                    Status_register=Ready;
                  }
                 else
                  {
                         Status_register=Ready;
                 }
          }
     
     
}


