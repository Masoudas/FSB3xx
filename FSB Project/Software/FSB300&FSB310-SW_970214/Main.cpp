/*******************************************************************************
********************************************************************************
*@ File:	Main.cpp
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:95/05/07	Previous:95/10/07	Created:95/10/07
*@ Author:	M. Aghamohamadian 

*@ Brief:	This module contains the main program of FSB board.

********************************************************************************
*******************************************************************************/
#include <inavr.h>
#include <ioavr.h>
#include "Learn_Mode.h"
#include "Test_Mode.h"
#include "Flash_Data_Read.h"
#include "AT45DB321E_Setup.h"
#include "General.h"
#include "I2C_Protocol.h"
#include "Main.h"


////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

/////////////********************************************************///////////
/////////********************** Initialization ***********************//////////
/////////////********************************************************///////////
//// Global variable initial assignment
// States
extern          Total_State                      current_state = SILENCE; // Start from the silent state (to check for input signals).
extern          Total_State                      previous_state = SILENCE; // Start from the silent state (to check for input signals).

// Flags

// Counters
extern          unsigned int                     EMR_current_page = 0; 
extern          unsigned int                     MUS_current_page = 0; 
extern          unsigned int                     OVL_current_page = 0;   
extern          unsigned int                     DOB_current_page = 0;   
extern          unsigned int                     DING_current_page = 0;  
extern          unsigned int                     DINGDONG_current_page = 0;
extern          unsigned int                     STOP_STATUS_current_page = 0;  

// Other globals
extern          unsigned char                    buffer_data[264] = {0};


/////////////********************************************************///////////
//////////********************** Main Program ***********************///////////
/////////////********************************************************///////////
void main()
{  
     ///// Initialization
     Initial_Setup();   
     __watchdog_reset();       // Reset watch-dog before entering the main loop.
     
     
     ///// Main commands
     while(1)
     {
        if (board_type == FSB310)       // If the board is FSB310, we need to read signal using I2C protocol.
        {          
          I2C_current_status = I2C_Protocol(&I2C_data[0], I2C_DATA_LENGTH, I2C_SR_MODE, I2C_SLAVE_ADDRESS, IGNORE_CRC, I2C_BITRATE, I2C_FREQUENCY_PRESCALAR, state_timer);
          if (I2C_current_status.output_flag == I2C_PROTOCOL_FINISHED)
          {
            Serial_CTRL_Signal_Detection(&CTRL_Signal_Params, &NUM_Signal_Params, start_up_flag, I2C_data); // Determine the current control signal.
            Serial_NUM_Signal_Detection(&NUM_Signal_Params, I2C_data); // Determine the current numerator signal.
            I2C_data[0] = 0x00;
            I2C_data[1] = 0x00;
            I2C_data[2] = 0x00;
          }         
        }

        if (Status_Register == READY)
        {
               Status_Register = BUSY;  // Set status register to busy (see the report on standard code scripting)
               half_page_counter = Flash_Data_Read(half_page_counter, &state_timer, current_album, &page_address[ALBUM1_FILE_NUMBER][0], &page_address[EXTRA_ALBUM1_FILE_NUMBER][0], &page_address[EXTRA_ALBUM2_FILE_NUMBER][0]);  // Play music, message or remain silent based on the current state.
               timer_update();  // Update system timer
               VOL_Signal_Detection(&VOL_Signal_Params); // Determine the current volume signal.
               Board_Type_Detection();         // Check the board type in every call of synchronous loop, to make sure that noise does not cause abrupt changes in the board type.               
               
               // Detecting the current input signal for FSB300.
               if (board_type == FSB300)
               {
                 Parallel_CTRL_Signal_Detection(&CTRL_Signal_Params, start_up_flag);    
                 Parallel_NUM_Signal_Detection(&NUM_Signal_Params);    
               }
               
               // Check for new state if state_timer has elapsed.
               if (state_timer < 1)  
               {     
                 previous_state = current_state;
                 current_state = Change_State(current_state, previous_state);  // Determine the current state based on the input signal.
                                                               // Furthermore, assign state_timer and perform necessary tasks based on the current state.                          
               }  
               Status_Register = WAIT;
               __watchdog_reset();               
        }
     }
     
     ///// Finalization
}


/////////////********************************************************///////////
////////////********************** functions ***********************////////////
/////////////********************************************************///////////
Total_State Change_State(Total_State current_state, Total_State previous_state)
{     
  // Initialization
  Total_State next_state; // Denotes the next state of FSB board.
    
  // Main Commands
  switch (current_state)
  {
    case (EMR): // If it is emergency after POR (only time emergency state may occur).
      next_state = MUS_2;     // Next state would be MUS_2.
      state_timer = UPSAMPLE_FACTOR*(page_address[6][1] - page_address[6][0]);  // Play the entire music designated to emergency state.
      MUS_current_page = page_address[6][0];   // Set music page counter to the beginning of emergency music.
    break;
    
    case (MUS_2):
      next_state = SILENCE_1; // After playing emergency music go to silence plus one mode.
      state_timer = 0; 
      Empty_Flash_Buffer();
    break;
    
    case (SILENCE_1):
      if (CTRL_Signal_Params.CTRL_Signal == EMR_SIGNAL)
      {
        next_state = SILENCE_1;
        state_timer = 0; 
      }
      else
      {
        next_state = SILENCE;   // If there is no emergency signal present anymore, simply start the normal functions of the board.
        state_timer = 0; 
      }
    break;   
    
    case (TEST_MODE):
        next_state = SILENCE_2;
        state_timer = 0;
    break;
    
    case (SILENCE_2): // Check to see if any input test signals are given; if not, the board enters silence mode.
      test_input_number = Test_Input_Detection(&CTRL_Signal_Params, &NUM_Signal_Params);       // Check to see if either control or numerator pins have been excited.     

      if (((CTRL_Signal_Params.debounce_counter >= TEST_DEBOUNCE_NUMBER) || (NUM_Signal_Params.debounce_counter >= TEST_DEBOUNCE_NUMBER)) && (test_input_number <= TOTAL_NO_PINS))       
      {       
        next_state = TEST_MODE;
        state_timer = UPSAMPLE_FACTOR*(page_address[test_input_number+6][1]-page_address[test_input_number+6][0]);    
        STOP_STATUS_current_page = page_address[test_input_number+6][0];       // Play a stop status message based on the input excited in the test mode.
      }
      else if (VOL_Signal_Params.VOL_Signal == ALBUM_CHANGE_SIGNAL)
      {
        next_state = SILENCE;
        state_timer = 50; // Must wait enough so that no unintential album change occures!
      }
      else
      {
        next_state = SILENCE_2;
        state_timer = 0; 
      }   
      Empty_Flash_Buffer();     // Empty the music buffer so that no noise like sound is played.
    break;
    
    case (LEARN_MODE): 
      Learn_Mode_Assignments(&CTRL_Signal_Params);     // Call the learn mode function to read the input control signal and decide on the inputs based on the debounced signals.
      next_state = SILENCE;
      state_timer = 0; 
    break;
    
    case (SILENCE): // If current state is silence.
      if (CTRL_Signal_Params.CTRL_Signal == EMR_SIGNAL) // If the control signal is emergency.
      {
        next_state = EMR; // next state (and just for once after POR) is emergency.
        state_timer = UPSAMPLE_FACTOR*(page_address[0][1] - page_address[0][0]); // Play the entire EMR message,
                                                                                 // for which we need to repeat the loop as many times as given by this formula.
        EMR_current_page = page_address[0][0];  // Set its page counter to the top of the message.
      }
      else if ((VOL_Signal_Params.keys_current_state == VOL_UP_INPUT) && (start_up_flag == 0) && (board_type == FSB300)) // If test key is pressed during POR in FSB300
      {
        next_state = SILENCE_2; // next state (and just for once after POR) is silence 2.
        state_timer = 0;         
      }
      else if ((VOL_Signal_Params.keys_current_state == VOL_DOWN_INPUT) && (start_up_flag == 0) && (board_type == FSB300)) // If learn key is pressed during POR in FSB300 
      {
        next_state = LEARN_MODE; // next state (and only during POR) is LEARN MODE.
        state_timer = 2*LEARN_DEBOUNCE_NUMBER-2; // Stay in learn mode twice the number of needed debounces minus two, to ensure that debounce happens only once.
      }
      else if (VOL_Signal_Params.VOL_Signal == ALBUM_CHANGE_SIGNAL)
      {
        next_state = ALBUM_CHANGE;
        state_timer = 0;  
      }
      else if (CTRL_Signal_Params.CTRL_Signal == TRG_SIGNAL)
      {
        OVL_Delay_Counter = 0;  // Ensure all delays are zero.
        DOB_Delay_Counter = 0;  
        next_state = MUS; // Play music.
        state_timer = 4;
      }
      else if ((CTRL_Signal_Params.CTRL_Signal == OVL_SIGNAL) && (OVL_Delay_Counter <= OVL_DELAY)) // If overload signal is received and its delay has not overflown.
      {
        OVL_Delay_Counter++;  // Increase the delay counter
        DOB_Delay_Counter = 0; // Ensure that DOB delay is zero.
        next_state = SILENCE; // Play silence!
        state_timer = 0;
      }
      else if ((CTRL_Signal_Params.CTRL_Signal == OVL_SIGNAL) && (OVL_Delay_Counter > OVL_DELAY)) // If overload signal is received and its delay has overflown.
      {
        OVL_Delay_Counter = 0;  // Set delay counter to zero.
        next_state = OVL; // Play OVL message.
        state_timer = UPSAMPLE_FACTOR*(page_address[3][1] - page_address[3][0]); // Play the entire OVL message,
        OVL_current_page = page_address[3][0];  // Set its page counter to the top of the message.
      }
      else if ((CTRL_Signal_Params.CTRL_Signal == DOB_SIGNAL) && (DOB_Delay_Counter <= DOB_DELAY))
      {
        DOB_Delay_Counter++;  
        OVL_Delay_Counter = 0; // Ensure that OVL delay is zero.
        next_state = SILENCE;
        state_timer = 0;
      }
      else if ((CTRL_Signal_Params.CTRL_Signal == DOB_SIGNAL) && (DOB_Delay_Counter > DOB_DELAY))
      {
        DOB_Delay_Counter = 0;  
        next_state = DOB; // Play DOB message.
        state_timer = UPSAMPLE_FACTOR*(page_address[2][1] - page_address[2][0]);   // Play the entire DOB message,
        DOB_current_page = page_address[2][0];  // Set its page counter to the top of the message.
      }
      else
      {
        OVL_Delay_Counter = 0;  // Ensure all delays are zero.
        DOB_Delay_Counter = 0;  
        next_state = SILENCE; // Stay in silence mode.
        state_timer = 0;
        if (previous_state != SILENCE)
        {
          EEPROMRead EEPROM_Read;
          EEPROM_Read = EEPROM_Secure_Read(EEPROM_VOL_ADD);                // Set the digital volume to the last value stored in EEPROM.   
          VOL_Signal_Params.digit_volume_level = EEPROM_Read.data;
          if (VOL_Signal_Params.digit_volume_level > MAX_VOLUME_LEVEL || EEPROM_Read.flag == CURROPTED_DATA)   // In case the volume level stored in EEPROM is not meaningful, set it to an intermediate level.
          {
            VOL_Signal_Params.digit_volume_level = 4;
          }
        }
      }
      break;
    
    case (OVL):
      if (CTRL_Signal_Params.CTRL_Signal == OVL_SIGNAL) 
      {
        OVL_Delay_Counter++;  // Re-increase the delay counter
        next_state = SILENCE;
        state_timer = 0;
      }
      else if (CTRL_Signal_Params.CTRL_Signal == DOB_SIGNAL)
      {
        DOB_Delay_Counter++;  
        next_state = SILENCE;
        state_timer = 0;
      }
      else if (CTRL_Signal_Params.CTRL_Signal == TRG_SIGNAL)
      {
        next_state = MUS;
        state_timer = 4;
      }
      else 
      {
        next_state = SILENCE; 
        state_timer = 0;
      }
    break;

    case (DOB): 
      if (CTRL_Signal_Params.CTRL_Signal == DOB_SIGNAL) 
      {
        DOB_Delay_Counter++;  // Re-increase the delay counter
        next_state = SILENCE;
        state_timer = 0;
      }
      else if (CTRL_Signal_Params.CTRL_Signal == OVL_SIGNAL)
      {
        OVL_Delay_Counter++;  
        next_state = SILENCE;
        state_timer = 0;
      }
      else if (CTRL_Signal_Params.CTRL_Signal == TRG_SIGNAL)
      {
        next_state = MUS;
        state_timer = 4;
      }
      else
      {
        next_state = SILENCE; 
        state_timer = 0;
      }  
      Empty_Flash_Buffer();     // Empty the music buffer so that no noise like sound is played.
    break;

    case (MUS):
      if (VOL_Signal_Params.VOL_Signal == ALBUM_CHANGE_SIGNAL)
      {
        next_state = ALBUM_CHANGE;
        state_timer = 0;
      }
      else if (CTRL_Signal_Params.CTRL_Signal == TRG_SIGNAL)
      {
        next_state = MUS;
        state_timer = 8;        // Check for input signal every 4 program ticks while playing music.
                                // Two program ticks ensure that a slight dip in trigger signal would not cause a change of state here.                              
      }
      else
      {
        next_state = MUS_1;
        new_stop_arrival_flag = 1;
        state_timer = MUSIC_BEFORE_STOP;  // Play a short music
      }
    break;
    
    case (MUS_1):
      if (new_stop_arrival_flag == 1)
      {
        new_stop_arrival_flag = 0;
        next_state = DEBOUNCE_NUM_SIGNAL;
        state_timer = 2*NUM_DEBOUNCE_NUMBER-2; // Timer is set according to the debounce number of numerator signal,
                                               // to ensure that only one debounce of numerator signal occurs in this state.
                                               // Note: There is no debouncing in FSB310. However, this wait does not cause
                                               // any issue for that board, given that the numerator signal is updated once there is
                                               // a change in stop number.   

      }
      else // It is after debouncing the numerator signal. 
      {
        next_state = SILENCE; // After playing music because of reaching a new stop, go to silence.
        state_timer = 0;
        Empty_Flash_Buffer();
      }
    break;  
       
    case (DEBOUNCE_NUM_SIGNAL):
      if (NUM_Signal_Params.current_stop > NUM_Signal_Params.previous_stop)  // If stop number has elevated.
      {
        next_state = DING; 
        state_timer = UPSAMPLE_FACTOR*(page_address[4][1] - page_address[4][0]); // Timer is set according to ding length
        DING_current_page = page_address[4][0];  // Set ding page counter to the top. 
      }
      else if (NUM_Signal_Params.current_stop < NUM_Signal_Params.previous_stop)  // If stop number has lowered.
      {
        next_state = DING_DONG; 
        state_timer = UPSAMPLE_FACTOR*(page_address[1][1] - page_address[1][0]); // Timer is set to ding-dong length.
        DINGDONG_current_page = page_address[1][0];  // Set ding-dong page counter to the top.
      }
      else
      {
        next_state = MUS_1;
        state_timer = MUSIC_AFTER_STOP;
      }
    break;

    case (DING):
      next_state = DECLARE_STOP_STATUS; // After ding, play the stop status message.
      state_timer = UPSAMPLE_FACTOR*(page_address[NUM_Signal_Params.stop_track_index][1] - page_address[NUM_Signal_Params.stop_track_index][0]); // Stop status message for FSB310 corresponds to stop_track_index.
      STOP_STATUS_current_page = page_address[NUM_Signal_Params.stop_track_index][0];
    break;
    
    case (DING_DONG):
      next_state = DECLARE_STOP_STATUS; // After ding, play the stop status message.
      state_timer = UPSAMPLE_FACTOR*(page_address[NUM_Signal_Params.stop_track_index][1] - page_address[NUM_Signal_Params.stop_track_index][0]); // Stop status message for FSB310 corresponds to stop_track_index.
      STOP_STATUS_current_page = page_address[NUM_Signal_Params.stop_track_index][0];
    break;

    case (DECLARE_STOP_STATUS):
      next_state = MUS_1; // After playing the stop status messsage, play music for a couple of seconds.
      state_timer = MUSIC_AFTER_STOP;
    break;  
    
    case (MUS_3):
      if (VOL_Signal_Params.VOL_Signal == VOL_UP_SIGNAL)        // If volume up key is pushed.
      {
        current_album++;              // Increasing the album number.
        VOL_Signal_Params.digit_volume_level--;     // Reset the volume level.         
        next_state = ALBUM_CHANGE;
        state_timer = 0;            
      }
      else if (VOL_Signal_Params.VOL_Signal == VOL_DOWN_SIGNAL) // If volume down key is pushed.
      {
        current_album--;        // Decrease the album number.
        VOL_Signal_Params.digit_volume_level++;     // Reset the volume level.         
        next_state = ALBUM_CHANGE;
        state_timer = 0;                
      }      
      else if (VOL_Signal_Params.VOL_Signal == ALBUM_CHANGE_SIGNAL)
      {
        next_state = SILENCE;
        state_timer = 0;      
        Empty_Flash_Buffer();        
      }     
      else
      {
         next_state = MUS_3;   
         state_timer = 0;
      }
    break;
    
    case (ALBUM_CHANGE):
      // Assign next state
      __EEPUT(EEPROM_VOL_ADD,VOL_Signal_Params.digit_volume_level);    
      next_state = MUS_3;
      state_timer = 2;              
      
      // Adjust album number.
      if (current_album > NUMBER_OF_ALBUMS)     // Reset the album number if it is out of bound.
      {
        current_album = 3;
      }
      else if (current_album <= 1)
      {
        current_album = 1;
      }
      __EEPUT(EEPROM_ALBUM_ADD,current_album);

      // Setting the music page to the beginning of the current album
      if (current_album == 1) 
      {
        MUS_current_page = page_address[ALBUM1_FILE_NUMBER][0];
      }
      else if (current_album == 2) 
      {
        MUS_current_page = page_address[EXTRA_ALBUM1_FILE_NUMBER][0];
      }
      else if (current_album == 3) 
      {
        MUS_current_page = page_address[EXTRA_ALBUM2_FILE_NUMBER][0];
      }
      else
      {
        MUS_current_page = page_address[ALBUM1_FILE_NUMBER][0];
      }
    break;   
    
    default:
      next_state = SILENCE;     // If this is an unknown state, go to silence mode.
      state_timer = 0;
    break;
   }
 

    // Finalization
    return (next_state);      
}


void Initial_Setup(void)
{    
     //// Determining the board type (i.e, FSB300 or FSB310)
     board_type = Board_Type_Detection();       
     
     //// Timer registers 
     // Timer global registers
     TIMSK = 0x04;  // Enable compare match interrupt for timer 1.
     __enable_interrupt();    // enable interrupts

     // Timer1 (PWM for playing music, fast PWM mode, TOP value is equal to register ICR1) 
     TCCR1A = 0x82;      
     TCCR1B = 0x19;       
     ICR1H = 0x00;        // ICR is set at 0x00FF. In other words, TOP value of fast PWM is 0xFF.
     ICR1L = 0xF0;
     OCR1AH = 0x00;       // Comparison value is set at zero (changes in the interrput).
     OCR1AL = 0x00;

     // Watch dog timer
     WDTCR = 0x1C; // Enable watch dog timer (happens every 60ms at Vcc = 5V)
     WDTCR = 0x1C; // Ensure enabling WD.
   
     // SPI registers
     SPCR = 0x50;  // SPI clock is set at f_clk/2.
     SPSR = 0x01;
     
     
     //// Port I/O
     if (board_type == FSB310)
     {
       NUM_PORT_DIRECTION = 0xFF;   // Numerator port (port D) is defined as output to avoid any confusion with FSB300.
       CTRL_PORT_DIRECTION = 0xFC;  // Control port (port C) except for PC0 & PC1 are as output to avoid any confusion with FSB300.
                                    // PC0 & PC1 are input ports for volume signal.
     }
     else       // Board is FSB300
     {
       NUM_PORT_DIRECTION = 0x00; 
       CTRL_PORT_DIRECTION = 0x00;  
     }
   
     // SPI port (port B) direction
     SPI_PORT_DIRECTION = 0x2F; // Refer to the report for this register.

     
     //// Extract page number corresponding to the messages and etc.
     Page_Extraction();
     
         
     //// Variables of Main.cpp initial setup
     Parameter_Initial_Setup();

     
     //// Set flash page size to 528 bytes (if necessary)
     unsigned char       number_of_memories = 1; // Denotes the total number of memories available in the board.
     struct              EEPROMRead              EEPROM_Read;           // The structure for data to be read securely from EEPROM.

     EEPROM_Read = EEPROM_Secure_Read(EEPROM_MEMORY_PAGES_ADD); // Read from EEPROM whether the pages have been set up to 528 previously.    
     if (EEPROM_Read.data != PAGES_MODIFIED_528 || EEPROM_Read.flag == CURROPTED_DATA)   // Check to see if modification is needed based on the data read from EEPROM.
     {
       number_of_memories = Count_Memory_Chips(page_address);  // Check to see if there are two memories on the board.
       for (unsigned char memory_number = 1; memory_number <= number_of_memories; memory_number++)
       {
         if (Flash_Page_Size(memory_number) == 512)        // If the page size for this memory is 512.
         {
            Flash_Erase(memory_number);  // Erase all data in the flash (necessary to make the adjustment)
            Change_Page_Size(memory_number);   // Change the register of the flash, so that page size would be 528 bytes.
         }
       }
       __EEPUT(EEPROM_MEMORY_PAGES_ADD,PAGES_MODIFIED_528); // Save in EEPROM that the pages have been modified to 528.
     }
         
     
     //// Set the volume level & album number & DOB and TRG signal levels
     // Get the stored volume level in EEPROM
     EEPROM_Read = EEPROM_Secure_Read(EEPROM_VOL_ADD);                // Set the digital volume to the last value stored in EEPROM.   
     VOL_Signal_Params.digit_volume_level = EEPROM_Read.data;
     if (VOL_Signal_Params.digit_volume_level > MAX_VOLUME_LEVEL || EEPROM_Read.flag == CURROPTED_DATA)   // In case the volume level stored in EEPROM is not meaningful, set it to an intermediate level.
     {
        VOL_Signal_Params.digit_volume_level = 3;
     }
     
     // Get the stored album number in EEPROM
     EEPROM_Read = EEPROM_Secure_Read(EEPROM_ALBUM_ADD);           // Set the album number to the last value stored in EEPROM.
     current_album = EEPROM_Read.data;
     if (current_album > NUMBER_OF_ALBUMS || current_album < 1 || EEPROM_Read.flag == CURROPTED_DATA)  // In case the album number stored in EEPROM is not meaningful, set it to one.
     {
        current_album = 1;
     } 
     
     // Assign first page of the current stored album
     if (current_album == 1) 
     {
       MUS_current_page = page_address[ALBUM1_FILE_NUMBER][0];
     }
     else if (current_album == 2) 
     {
       MUS_current_page = page_address[EXTRA_ALBUM1_FILE_NUMBER][0];
     }
     else if (current_album == 3) 
     {
       MUS_current_page = page_address[EXTRA_ALBUM2_FILE_NUMBER][0];
     }
     
     
     //// Setting up the default control signal levels
     EEPROM_Read = EEPROM_Secure_Read(EEPROM_DOBTRG_ACTIVE_LEVEL_ADD);
     if (EEPROM_Read.flag == TRUSTED_DATA && board_type == FSB300)  // If the data read from EEPROM is trusted and the board is FSB300
     {
       DOBTRG_Level_Assignment(&CTRL_Signal_Params, EEPROM_Read.data);
     }
     else       // This is not a trusted data, so assume the default case.
     {
        CTRL_Signal_Params.PARALLEL_TRG_input = 0x00;    
        CTRL_Signal_Params.PARALLEL_OVL_input = 0x20; 
        CTRL_Signal_Params.PARALLEL_DOB_input = 0x30;
     }
}

void Parameter_Initial_Setup(void)
{
     //// Variables of main.cpp initial assignement
     // States 
     Status_Register = READY;     

     // Flags
     start_up_flag = 0;
     new_stop_arrival_flag = 0;
     I2C_current_status.output_flag = I2C_PROTOCOL_FINISHED;
     check_synchronous_loop = SYNCHRONOUS_LOOP_UNCHECKED;

     // Counters 
     OVL_Delay_Counter = 0;  
     DOB_Delay_Counter = 0; 
     buffer_counter = 0;
     sub_buffer_counter = 0;
     
     //// Structures initialization
     // Numerator signal parameters initialization
     NUM_Signal_Params.current_stop = 0;
     NUM_Signal_Params.previous_stop = 0;
     NUM_Signal_Params.NUM_Signal = PARALLEL_LOBBY;    
     NUM_Signal_Params.previous_input = 0;      
     NUM_Signal_Params.current_input = 0xFF;
     NUM_Signal_Params.debounce_counter = 0;
     NUM_Signal_Params.stop_track_index = 0;
   
     // Control signal parameters initialization     
     CTRL_Signal_Params.PARALLEL_TRG_input = 0x00;    
     CTRL_Signal_Params.PARALLEL_OVL_input = 0x20;
     CTRL_Signal_Params.PARALLEL_DOB_input = 0x30;
     CTRL_Signal_Params.debounce_counter = 0;
     CTRL_Signal_Params.CTRL_Signal = NO_SIGNAL;   
     CTRL_Signal_Params.previous_input = 0;      
     CTRL_Signal_Params.current_input = 0xFF; // Assigned a different initial value from CTRL_previous_input, so that nothing would change automatically.       

     // Volume signal parameters initialization     
     VOL_Signal_Params.VOL_Signal = VOL_NO_SIGNAL;   
     VOL_Signal_Params.previous_input = 0x03;      
     VOL_Signal_Params.current_input = 0x00; 
     VOL_Signal_Params.keys_current_state = VOL_UNPUSHED_INPUT; 
     VOL_Signal_Params.keys_previous_state = VOL_UNPUSHED_INPUT;
     VOL_Signal_Params.debounce_counter = 0;
     
     // I2C data initial assignment (to ensure that board does not start from an incorrect initial state)
     I2C_data[0] = 0x00;   
     I2C_data[1] = 0x00;
     I2C_data[2] = 0x00;   

     
     //// Other variables
     state_timer = START_UP_DELAY;
     VOL_Signal_Params.digit_volume_level = 0;
     current_album = 1;  
     half_page_counter = 0; 
     MUS_current_page = page_address[5][0];
}

bool Board_Type_Detection(void)
{
     // Initialization
     static              unsigned char          detection_counter;      // A static which denotes the number of ticks in which the function was called.
     unsigned char       vote = 0;       // Denotes the number of times PB6 is above zero.

     
     // Main commands
     DDRB &= 0xBF;     // Temporarily define PB6 as input.
     PORTB |= 0x40;    // Temporarilty enable the pull-up of this port.

     vote += ((PINB&0x40) >> 2);
     detection_counter++;
     
     if (detection_counter >= BOARD_TYPE_DEBOUNCE_NUMBER)
     {
       if (vote < ((BOARD_TYPE_DEBOUNCE_NUMBER+1)/2))   // Assing board type based on the vote.
       {             
         board_type = FSB300;      
       }
       else
       {        
         board_type = FSB310;
       }
       detection_counter = 0;   // Set the counter to zero to restart detecting the board type.
       vote = 0;        // Set vote to zero as well.
     }
     
     
     // Finalization
     if (vote == 0)
     {             
       return(FSB300);      
     }
     else
     {        
       return(FSB310);
     }
}

void Page_Extraction(void)
{
     //// Initialization
     unsigned char        Add_First_Byte;         // MSB of page address.
     unsigned char        Add_Second_Byte;        // LSB of page address plus MSB of byte address.
     unsigned char        Add_Third_Byte;         // LSB of bite address.
     unsigned char        Dont_Care_Byte = 0x00;
        
    
     //// Main commands
     Add_First_Byte = 0;     // Get ready to read page zero of the memory.
     Add_Second_Byte = 0; 
     Add_Third_Byte = 0x2C;     // The first byte in PAGES_LOCATION_FLASH page, where a page number is stored.
     
     Memory_Selection(1);   // Select memory one to initiate SPI.
     
     SPI_Interface(Main_Mem_Read); // Sending the opcode D2H to initialize continuous reading.     
     SPI_Interface(Add_First_Byte);   // Sending the page addresses.
     SPI_Interface(Add_Second_Byte);        
     SPI_Interface(Add_Third_Byte); 
     
     for (unsigned char i = 0; i < 4; i++) // Sending four don't care bytes.
     {
         SPI_Interface(Dont_Care_Byte); 
     }   
       
     for (unsigned char file_index = 0; file_index < TOTAL_MEMORY_FILES; file_index++)
     {
       // Initial page
       page_address[file_index][0] = 256*((unsigned int)SPI_Interface(Dont_Care_Byte)); // First byte of initial page address is multiplied by 256!
       page_address[file_index][0] += SPI_Interface(Dont_Care_Byte); 
       
       // Final page
       page_address[file_index][1] = 256*((unsigned int)SPI_Interface(Dont_Care_Byte)); // First byte of final page address is multiplied by 256!
       page_address[file_index][1] += SPI_Interface(Dont_Care_Byte); 
     }
     Memory_Selection(0); // Deselect all memories.
}


void Empty_Flash_Buffer(void)
{
    for (unsigned int i = 0 ; i < 264 ; i++)    // Set zero data in the music buffer.
    {
       buffer_data[i] = 0;
    } 
}

void timer_update(void)
{
     if(state_timer > 0)
     {
        state_timer--;
     }
     else
     {
        state_timer = 0;
        start_up_flag = 1;    // After the start up time elapses. this flag is set to one.
     }
}


/////////////********************************************************///////////
////////////********************* Interrupts ***********************////////////
/////////////********************************************************///////////
#pragma vector = TIMER1_OVF_vect
__interrupt void out_now(void)
{
     //// The routine for DAC.
     // Setting the duty cycle of PWM (see the report)
     OCR1AH = 0x00;     
     OCR1AL = buffer_data[buffer_counter] >> (6-VOL_Signal_Params.digit_volume_level);  
     sub_buffer_counter++;
     
     if (sub_buffer_counter == 2)
     {
       sub_buffer_counter = 0;
       buffer_counter++;
     }
       
     if (buffer_counter > 263)  // If the entire (current) page has been read, restart the counter.
     {
       buffer_counter = 0;
       check_synchronous_loop = SYNCHRONOUS_LOOP_UNCHECKED;
     }

     // Setting the status register for program tick (happens here since the entire page has now been played)
     if (buffer_counter > 250 && check_synchronous_loop == SYNCHRONOUS_LOOP_UNCHECKED)
     {
       check_synchronous_loop = SYNCHRONOUS_LOOP_CHECKED;  
       if (Status_Register == WAIT)
       {              
          Status_Register = READY;
       }
       else if (Status_Register == BUSY)
       {              
          __EEPUT(EEPROM_ERRONEOUS_STATE_ADD,current_state);   
          Status_Register = READY;
       }
       else
       {
          Status_Register = READY;
       }
     }
}

