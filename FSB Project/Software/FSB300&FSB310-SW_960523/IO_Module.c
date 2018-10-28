/*******************************************************************************
********************************************************************************
*@ File:	IO_Module.c
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:96/05/23	Previous:96/01/14	Created:96/01/14
*@ Author:	M.Aghamohamadian 

*@ Brief:	This I/O module of FSB board, used for both FSB300 and FSB310.

********************************************************************************
*******************************************************************************/
#include <inavr.h>
#include <ioavr.h>
#include "General.h"
#include "IO_Module.h"


/////////////********************************************************///////////
////////////********************** Inputs **************************////////////
/////////////********************************************************///////////
void VOL_Signal_Detection(struct VolumeSignal *VOL_Signal_Params)
{
     //// Initialization
  
  
     //// Main commands
     // Debounce check for volume signal
     (*VOL_Signal_Params).current_input = VOL_DontC_bits & CTRL_PORT_READ;  // Extracting the control signals merely related to digital volume.
     if ((*VOL_Signal_Params).previous_input == (*VOL_Signal_Params).current_input) // If the current control signal is equal to 
                                                                                    // the previous one and debounce counter has not overflown,
     {
        (*VOL_Signal_Params).debounce_counter++; // Increase the debounce counter.
     }
     else  // If the current control signal does not match the previous one or it is blank,
     {
        (*VOL_Signal_Params).debounce_counter = 0;       // Restart the counter
     }  
     (*VOL_Signal_Params).previous_input = (*VOL_Signal_Params).current_input;    // Assign the current input to the previous one.
  
  
     // Assigning the current state of the keys
     if ((*VOL_Signal_Params).debounce_counter >= VOL_DEBOUNCE_NUMBER)
     {
        (*VOL_Signal_Params).debounce_counter = 0;
        (*VOL_Signal_Params).keys_previous_state = (*VOL_Signal_Params).keys_current_state; 
        
        // If both keys were pushed in the previous state, no further change in key states is allowed, unless both are let go.
        if ((*VOL_Signal_Params).keys_previous_state != ALBUM_CHANGE_INPUT)
        {
           (*VOL_Signal_Params).keys_current_state = (*VOL_Signal_Params).current_input;
        }
        else if ((*VOL_Signal_Params).keys_previous_state == ALBUM_CHANGE_INPUT && (*VOL_Signal_Params).current_input == VOL_UNPUSHED_INPUT)
        {
           (*VOL_Signal_Params).keys_current_state = (*VOL_Signal_Params).current_input;
        }
                
        // Volume and album change based on the debounced volume signal (more precisely, based on the key states!)
        if (((*VOL_Signal_Params).keys_current_state == VOL_UNPUSHED_INPUT) && ((*VOL_Signal_Params).keys_previous_state == VOL_UP_INPUT))    // If volume-up signal is given as input .
        {
          (*VOL_Signal_Params).digit_volume_level++;  
          (*VOL_Signal_Params).VOL_Signal = VOL_UP_SIGNAL; // Input volume signal is volume up/ test signal. 
        }
        else if (((*VOL_Signal_Params).keys_current_state == VOL_UNPUSHED_INPUT) && ((*VOL_Signal_Params).keys_previous_state == VOL_DOWN_INPUT) && ((*VOL_Signal_Params).digit_volume_level > 0))    // If volume down signal is given as input.
        {
          (*VOL_Signal_Params).digit_volume_level--;        
          (*VOL_Signal_Params).VOL_Signal = VOL_DOWN_SIGNAL; // Input volume signal is volume down/ learn signal. 
        }        
        else if (((*VOL_Signal_Params).keys_current_state == VOL_UNPUSHED_INPUT) && ((*VOL_Signal_Params).keys_previous_state == ALBUM_CHANGE_INPUT))  // If this is not a volume change signal, then it is either and album change signal, or there is no signal at all.
        {
          (*VOL_Signal_Params).VOL_Signal = ALBUM_CHANGE_SIGNAL; // Input volume signal is album change signal. 
        }
        else
        {
          (*VOL_Signal_Params).VOL_Signal = VOL_NO_SIGNAL;
        } 
        
        if ((*VOL_Signal_Params).digit_volume_level > MAX_VOLUME_LEVEL) // Check to see if volume level is not beyond the accepted range.
        {
          (*VOL_Signal_Params).digit_volume_level = MAX_VOLUME_LEVEL;
        }
        __EEPUT(EEPROM_VOL_ADD,(*VOL_Signal_Params).digit_volume_level);        // Save the current volume level.
     }
     else
     {
       (*VOL_Signal_Params).VOL_Signal = VOL_NO_SIGNAL; // In case there is no successful debounce, we conclude that there is no signal.
                                                        // This is important because in case of a previously discovered signal, we may repeatedly declare untill a new debounce occurs.
     }
        
     
     //// Finalization
}


void Parallel_CTRL_Signal_Detection(struct ControlSignal *CTRL_Signal_Params, bool start_up_flag)
{
     //// Initialization
  

     //// Main commands
     // Debounce check for control signals
     (*CTRL_Signal_Params).current_input = CTRL_PORT_READ;      // Read the current control input signal.
     if ((*CTRL_Signal_Params).current_input == (*CTRL_Signal_Params).previous_input)          // If the current control signal is equal to 
                                                                                               // the previous one and debounce counter has not overflown   
     {
       (*CTRL_Signal_Params).debounce_counter++; // Increase the debounce counter.
     }
     else if ((*CTRL_Signal_Params).current_input != (*CTRL_Signal_Params).previous_input)    // If the current control signal does not match the previous one,
     {
       (*CTRL_Signal_Params).debounce_counter = 0;       // Restart the counter
     }
     (*CTRL_Signal_Params).previous_input = (*CTRL_Signal_Params).current_input; // keep the current control signal for the next loop.
     
     // Control input signal derivation based on the debounced control signal
     if (((*CTRL_Signal_Params).debounce_counter >= CTRL_DEBOUNCE_NUMBER) && (current_state != LEARN_MODE) && (current_state != SILENCE_2)) // If debounce is done sufficiently and the board is not in the learn or test mode,
     {                                                                                 // Note: If the board is in learn mode, detection is done using Learn_Mode_Assignments(). In the test mode detection is done in change_state function
         (*CTRL_Signal_Params).debounce_counter = 0;     // Restart debounce counter.
         
         if (((!start_up_flag) || current_state == SILENCE_1) && (((*CTRL_Signal_Params).current_input & EMR_DontC_bits) == PARALLEL_EMR_INPUT))        // If start up time has not elapsed or we are in silence+1 state, and the input is emergency signal.
         {
            (*CTRL_Signal_Params).CTRL_Signal = EMR_SIGNAL;  // Set control signal to emergency signal.
         }
         else if (((*CTRL_Signal_Params).current_input & TRG_DontC_bits) == (*CTRL_Signal_Params).PARALLEL_TRG_input)
         {          
            (*CTRL_Signal_Params).CTRL_Signal = TRG_SIGNAL;
         }
         else if (((*CTRL_Signal_Params).current_input & OVL_DontC_bits) == (*CTRL_Signal_Params).PARALLEL_OVL_input)   // After eliminating the don't care bytes from control signal, if we have an overload signal
         {
            (*CTRL_Signal_Params).CTRL_Signal = OVL_SIGNAL;
         }
         else if (((*CTRL_Signal_Params).current_input & DOB_DontC_bits) == (*CTRL_Signal_Params).PARALLEL_DOB_input)   // Else if we have a door open signal,
         {
            (*CTRL_Signal_Params).CTRL_Signal = DOB_SIGNAL;
         }
         else
         {
            (*CTRL_Signal_Params).CTRL_Signal = NO_SIGNAL;
         }
     }
     
     //// Finalization
}


void Parallel_NUM_Signal_Detection(struct NumeratorSignal *NUM_Signal_Params)
{
     //// Initialization
     
     
     //// Main commands
     // Debounce check for numerator signals
     (*NUM_Signal_Params).current_input = NUM_PORT_READ;      // Read the current numerator input signal.
     if (((*NUM_Signal_Params).previous_input == (*NUM_Signal_Params).current_input) && (current_state == DEBOUNCE_NUM_SIGNAL || current_state == SILENCE_2))    // If the current numerator signal is equal to the previous one and we are in the debounce state.
     {
       (*NUM_Signal_Params).debounce_counter++; // Increase the debounce counter.
     }
     else if (((*NUM_Signal_Params).previous_input != (*NUM_Signal_Params).current_input) && (current_state == DEBOUNCE_NUM_SIGNAL || current_state == SILENCE_2))    // If the current numerator signal does not match the previous one,
     {
       (*NUM_Signal_Params).debounce_counter = 0;       // Restart the counter
     }
     else  // In case we are out of debouce numerator signal state, make sure that the debounce counter is zero (so that debouncing would not start from a nonzero number in the next DEBOUNCE_NUM_SIGNAL state)
     {
       (*NUM_Signal_Params).debounce_counter = 0;
     }
     (*NUM_Signal_Params).previous_input = (*NUM_Signal_Params).current_input; // set the previous numerator signal as the current numerator signal for the next loop.

     // Numerator input signal derivation based on the debounced control signal
     if ((*NUM_Signal_Params).debounce_counter >= NUM_DEBOUNCE_NUMBER && current_state == DEBOUNCE_NUM_SIGNAL) // If debounce is done sufficiently
     {
       (*NUM_Signal_Params).debounce_counter = 0;
       (*NUM_Signal_Params).NUM_Signal = (*NUM_Signal_Params).current_input;  // Assign the signal on numerator port to numerator signal.
       (*NUM_Signal_Params).previous_stop = (*NUM_Signal_Params).current_stop;  // current_stop now denotes the stop in the previous state.       
       Parallel_StopStatus_Finder(NUM_Signal_Params);  // Find the current stop status and assign the correct stop status message based on this signal.
     }
    
     
     //// Finalization
}

char Parallel_StopStatus_Finder(struct NumeratorSignal *NUM_Signal_Params)     
{
     //// Initialization
                         
     
     //// Main commands
     switch ((*NUM_Signal_Params).NUM_Signal)
     {
       // Parkings
       case (PARALLEL_PARK_09):
          (*NUM_Signal_Params).current_stop = 1;              // Assign the current stop number.
          (*NUM_Signal_Params).stop_track_index = 47;         // The stop status message to be played corresponding to this floor.
          break;  
       
       case (PARALLEL_PARK_08):
          (*NUM_Signal_Params).current_stop = 2;            
          (*NUM_Signal_Params).stop_track_index = 48;
          break;   
       
       case (PARALLEL_PARK_07):
          (*NUM_Signal_Params).current_stop = 3;            
          (*NUM_Signal_Params).stop_track_index = 49;
          break; 
       
       case (PARALLEL_PARK_06):
          (*NUM_Signal_Params).current_stop = 4;            
          (*NUM_Signal_Params).stop_track_index = 50;
          break;     
       
       case (PARALLEL_PARK_05):
          (*NUM_Signal_Params).current_stop = 5;            
          (*NUM_Signal_Params).stop_track_index = 51;
          break;      
       
       case (PARALLEL_PARK_04):
          (*NUM_Signal_Params).current_stop = 6;            
          (*NUM_Signal_Params).stop_track_index = 52;
          break;      
       
       case (PARALLEL_PARK_03):
          (*NUM_Signal_Params).current_stop = 7;            
          (*NUM_Signal_Params).stop_track_index = 53;
          break;      
       
       case (PARALLEL_PARK_02):
          (*NUM_Signal_Params).current_stop = 8;            
          (*NUM_Signal_Params).stop_track_index = 54;
          break;    
       
       case (PARALLEL_PARK_01):
          (*NUM_Signal_Params).current_stop = 9;            
          (*NUM_Signal_Params).stop_track_index = 55;
          break;    
       
       case (PARALLEL_PARK_00):
          (*NUM_Signal_Params).current_stop = 10;           
          (*NUM_Signal_Params).stop_track_index = 56;
          break;    
       
       case (PARALLEL_BASEMENT):
          (*NUM_Signal_Params).current_stop = 11;           
          (*NUM_Signal_Params).stop_track_index = 66;
          break;   
             
       // Ground floors (or something to that effect!)
       case (PARALLEL_GROUND): // This one reads "HAMKAF".
          (*NUM_Signal_Params).current_stop = 12;           
          (*NUM_Signal_Params).stop_track_index = 67;
          break;      
       
       case (PARALLEL_GROUND0): // This one also reads "HAMKAF".
          (*NUM_Signal_Params).current_stop = 12;           
          (*NUM_Signal_Params).stop_track_index = 67;
          break;      

       // Floors above ground (or above lobby if you like!)      
       case (PARALLEL_FLOOR01):
          (*NUM_Signal_Params).current_stop = 13;            
          (*NUM_Signal_Params).stop_track_index = 7;
          break;
       
       case (PARALLEL_FLOOR02):
          (*NUM_Signal_Params).current_stop = 14;            
          (*NUM_Signal_Params).stop_track_index = 8;
          break;
       
       case (PARALLEL_FLOOR03):
          (*NUM_Signal_Params).current_stop = 15;            
          (*NUM_Signal_Params).stop_track_index = 9;
          break;
       
       case (PARALLEL_FLOOR04):
          (*NUM_Signal_Params).current_stop = 16;            
          (*NUM_Signal_Params).stop_track_index = 10;
          break;
       
       case (PARALLEL_FLOOR05):
          (*NUM_Signal_Params).current_stop = 17;            
          (*NUM_Signal_Params).stop_track_index = 11;
          break;
       
       case (PARALLEL_FLOOR06):
          (*NUM_Signal_Params).current_stop = 18;            
          (*NUM_Signal_Params).stop_track_index = 12;
          break;
       
       case (PARALLEL_FLOOR07):
          (*NUM_Signal_Params).current_stop = 19;            
          (*NUM_Signal_Params).stop_track_index = 13;
          break;
       
       case (PARALLEL_FLOOR08):
          (*NUM_Signal_Params).current_stop = 20;            
          (*NUM_Signal_Params).stop_track_index = 14;
          break;
       
       case (PARALLEL_FLOOR09):
          (*NUM_Signal_Params).current_stop = 21;            
          (*NUM_Signal_Params).stop_track_index = 15;
          break;
       
       case (PARALLEL_FLOOR10):
          (*NUM_Signal_Params).current_stop = 22;            
          (*NUM_Signal_Params).stop_track_index = 16;
          break;
       
       case (PARALLEL_FLOOR11):
          (*NUM_Signal_Params).current_stop = 23;            
          (*NUM_Signal_Params).stop_track_index = 17;
          break;
       
       case (PARALLEL_FLOOR12):
          (*NUM_Signal_Params).current_stop = 24;            
          (*NUM_Signal_Params).stop_track_index = 18;
          break;
       
       case (PARALLEL_FLOOR13):
          (*NUM_Signal_Params).current_stop = 25;            
          (*NUM_Signal_Params).stop_track_index = 19;
          break;
       
       case (PARALLEL_FLOOR14):
          (*NUM_Signal_Params).current_stop = 26;            
          (*NUM_Signal_Params).stop_track_index = 20;
          break;
       
       case (PARALLEL_FLOOR15):
          (*NUM_Signal_Params).current_stop = 27;            
          (*NUM_Signal_Params).stop_track_index = 21;
          break;
       
       case (PARALLEL_FLOOR16):
          (*NUM_Signal_Params).current_stop = 28;            
          (*NUM_Signal_Params).stop_track_index = 22;
          break;
       
       case (PARALLEL_FLOOR17):
          (*NUM_Signal_Params).current_stop = 29;            
          (*NUM_Signal_Params).stop_track_index = 23;
          break;
       
       case (PARALLEL_FLOOR18):
          (*NUM_Signal_Params).current_stop = 30;            
          (*NUM_Signal_Params).stop_track_index = 24;
          break;
       
       case (PARALLEL_FLOOR19):
          (*NUM_Signal_Params).current_stop = 31;            
          (*NUM_Signal_Params).stop_track_index = 25;
          break;
       
       case (PARALLEL_LOBBY):
          (*NUM_Signal_Params).current_stop = 12;            
          (*NUM_Signal_Params).stop_track_index = 71;
          break;         
      
       default:
         break;          
     }

     //// Finalization
     return(0);
}


void Serial_CTRL_Signal_Detection(struct ControlSignal *CTRL_Signal_Params, struct NumeratorSignal *NUM_Signal_Params, bool start_up_flag, unsigned char I2C_data_frame[])
{
     //// Initialization

  
     //// Main commands
     switch (I2C_data_frame[0])
     {
       case (SERIAL_EMR_INPUT):
         if ((!start_up_flag) || (current_state == SILENCE_1))
         {
           (*CTRL_Signal_Params).CTRL_Signal = EMR_SIGNAL;
         }
         else
         {
           (*CTRL_Signal_Params).CTRL_Signal = NO_SIGNAL;
         }
         break;
       
       case (SERIAL_TRG_INPUT):
         (*CTRL_Signal_Params).CTRL_Signal = TRG_SIGNAL;
         break;
       
       case (SERIAL_OVL_INPUT):
         (*CTRL_Signal_Params).CTRL_Signal = OVL_SIGNAL;
         break;

       case (SERIAL_DOB_INPUT):
         (*CTRL_Signal_Params).CTRL_Signal = DOB_SIGNAL;
         break;
       
       case (SERIAL_DIRECTION_UP_INPUT):        // In case of elevator moving upward, make sure that the current_stop value is higher than that of previous stop.
         (*CTRL_Signal_Params).CTRL_Signal = NO_SIGNAL;          
         (*NUM_Signal_Params).current_stop = 1; 
         (*NUM_Signal_Params).previous_stop = (*NUM_Signal_Params).current_stop - 1;
         break;

       case (SERIAL_DIRECTION_DOWN_INPUT):        // In case of elevator moving downward, make sure that the current_stop value is lower than that of previous stop.
         (*CTRL_Signal_Params).CTRL_Signal = NO_SIGNAL;          
         (*NUM_Signal_Params).current_stop = 0; 
         (*NUM_Signal_Params).previous_stop = (*NUM_Signal_Params).current_stop + 1;
         break;
       
       default:
         (*CTRL_Signal_Params).CTRL_Signal = NO_SIGNAL; 
         (*NUM_Signal_Params).current_stop = (*NUM_Signal_Params).previous_stop;
         break;
     }
  
     //// Finalization
}


void Serial_NUM_Signal_Detection(struct NumeratorSignal *NUM_Signal_Params, unsigned char I2C_data_frame[])     
{
     //// Initialization
     unsigned int        I2C_NUM_bytes = 0;       // Denotes the two bytes of I2C signal put together. 
     

     //// Main commands   
     I2C_NUM_bytes = ((unsigned int)(I2C_data_frame[1]) << 8) + (unsigned int)(I2C_data_frame[2]);   // The corresponding codes of the seven segment are combined to form an integer.
     
     switch (I2C_NUM_bytes)     // Decide on the current stop status.
     {
       case (SERIAL_FLOOR01):
          (*NUM_Signal_Params).stop_track_index = 7;            
          break;
       
       case (SERIAL_FLOOR02):
          (*NUM_Signal_Params).stop_track_index = 8;            
          break;
       
       case (SERIAL_FLOOR03):
          (*NUM_Signal_Params).stop_track_index = 9;
          break;
       
       case (SERIAL_FLOOR04):
          (*NUM_Signal_Params).stop_track_index = 10;
          break;
       
       case (SERIAL_FLOOR05):
          (*NUM_Signal_Params).stop_track_index = 11;
          break;
       
       case (SERIAL_FLOOR06):
          (*NUM_Signal_Params).stop_track_index = 12;
          break;
       
       case (SERIAL_FLOOR07):
          (*NUM_Signal_Params).stop_track_index = 13;
          break;
       
       case (SERIAL_FLOOR08):
          (*NUM_Signal_Params).stop_track_index = 14;
          break;
       
       case (SERIAL_FLOOR09):
          (*NUM_Signal_Params).stop_track_index = 15;
          break;
       
       case (SERIAL_FLOOR10):
          (*NUM_Signal_Params).stop_track_index = 16;
          break;
       
       case (SERIAL_FLOOR11):
          (*NUM_Signal_Params).stop_track_index = 17;
          break;
       
       case (SERIAL_FLOOR12):
          (*NUM_Signal_Params).stop_track_index = 18;
          break;
       
       case (SERIAL_FLOOR13):
          (*NUM_Signal_Params).stop_track_index = 19;
          break;
       
       case (SERIAL_FLOOR14):
          (*NUM_Signal_Params).stop_track_index = 20;
          break;
       
       case (SERIAL_FLOOR15):
          (*NUM_Signal_Params).stop_track_index = 21;
          break;
       
       case (SERIAL_FLOOR16):
          (*NUM_Signal_Params).stop_track_index = 22;
          break;
       
       case (SERIAL_FLOOR17):
          (*NUM_Signal_Params).stop_track_index = 23;
          break;
       
       case (SERIAL_FLOOR18):
          (*NUM_Signal_Params).stop_track_index = 24;
          break;
       
       case (SERIAL_FLOOR19):
          (*NUM_Signal_Params).stop_track_index = 25;
          break;
       
       case (SERIAL_FLOOR20):
          (*NUM_Signal_Params).stop_track_index = 26;
          break;
       
       case (SERIAL_FLOOR21):
          (*NUM_Signal_Params).stop_track_index = 27;
          break;
       
       case (SERIAL_FLOOR22):
          (*NUM_Signal_Params).stop_track_index = 28;
          break;
       
       case (SERIAL_FLOOR23):
          (*NUM_Signal_Params).stop_track_index = 29;
          break;

       case (SERIAL_FLOOR24):
          (*NUM_Signal_Params).stop_track_index = 30;
          break;

       case (SERIAL_FLOOR25):
          (*NUM_Signal_Params).stop_track_index = 31;
          break;

       case (SERIAL_FLOOR26):
          (*NUM_Signal_Params).stop_track_index = 32;
          break;

       case (SERIAL_FLOOR27):
          (*NUM_Signal_Params).stop_track_index = 33;
          break;

       case (SERIAL_FLOOR28):
          (*NUM_Signal_Params).stop_track_index = 34;
          break;

       case (SERIAL_FLOOR29):
          (*NUM_Signal_Params).stop_track_index = 35;
          break; 
       
       case (SERIAL_FLOOR30):
          (*NUM_Signal_Params).stop_track_index = 36;
          break;
       
       case (SERIAL_FLOOR31):
          (*NUM_Signal_Params).stop_track_index = 37;
          break;
       
       case (SERIAL_FLOOR32):
          (*NUM_Signal_Params).stop_track_index = 38;
          break;
       
       case (SERIAL_FLOOR33):
          (*NUM_Signal_Params).stop_track_index = 39;
          break;

       case (SERIAL_FLOOR34):
          (*NUM_Signal_Params).stop_track_index = 40;
          break;

       case (SERIAL_FLOOR35):
          (*NUM_Signal_Params).stop_track_index = 41;
          break;

       case (SERIAL_FLOOR36):
          (*NUM_Signal_Params).stop_track_index = 42;
          break;

       case (SERIAL_FLOOR37):
          (*NUM_Signal_Params).stop_track_index = 43;
          break;

       case (SERIAL_FLOOR38):
          (*NUM_Signal_Params).stop_track_index = 44;
          break;

       case (SERIAL_FLOOR39):
          (*NUM_Signal_Params).stop_track_index = 45;
          break; 
       
       case (SERIAL_FLOOR40):
          (*NUM_Signal_Params).stop_track_index = 46;
          break; 

       // Parkings
       case (SERIAL_PARK_09):
           (*NUM_Signal_Params).stop_track_index = 47;
           break;  
       
       case (SERIAL_PARK_08):
           (*NUM_Signal_Params).stop_track_index = 48;
           break;   
       
       case (SERIAL_PARK_07):
           (*NUM_Signal_Params).stop_track_index = 49;
           break; 
       
       case (SERIAL_PARK_06):
           (*NUM_Signal_Params).stop_track_index = 50;
           break;     
       
       case (SERIAL_PARK_05):
           (*NUM_Signal_Params).stop_track_index = 51;
           break;      
       
       case (SERIAL_PARK_04):
           (*NUM_Signal_Params).stop_track_index = 52;
           break;      
       
       case (SERIAL_PARK_03):
           (*NUM_Signal_Params).stop_track_index = 53;
           break;      
       
       case (SERIAL_PARK_02):
           (*NUM_Signal_Params).stop_track_index = 54;
           break;    
       
       case (SERIAL_PARK_01):
           (*NUM_Signal_Params).stop_track_index = 55;
           break;    
       
       case (SERIAL_PARK):
           (*NUM_Signal_Params).stop_track_index = 56;
           break;    
       
       case (SERIAL_BASEMENT_09):
           (*NUM_Signal_Params).stop_track_index = 57;
           break;  
       
       case (SERIAL_BASEMENT_08):
           (*NUM_Signal_Params).stop_track_index = 58;
           break;   
       
       case (SERIAL_BASEMENT_07):
           (*NUM_Signal_Params).stop_track_index = 59;
           break; 
       
       case (SERIAL_BASEMENT_06):
           (*NUM_Signal_Params).stop_track_index = 60;
           break;     
       
       case (SERIAL_BASEMENT_05):
           (*NUM_Signal_Params).stop_track_index = 61;
           break;      
       
       case (SERIAL_BASEMENT_04):
           (*NUM_Signal_Params).stop_track_index = 62;
           break;      
       
       case (SERIAL_BASEMENT_03):
           (*NUM_Signal_Params).stop_track_index = 63;
           break;      
       
       case (SERIAL_BASEMENT_02):
           (*NUM_Signal_Params).stop_track_index = 64;
           break;    
       
       case (SERIAL_BASEMENT_01):
           (*NUM_Signal_Params).stop_track_index = 65;
           break;    
       
       case (SERIAL_BASEMENT):
           (*NUM_Signal_Params).stop_track_index = 66;
           break;    
       
       case (SERIAL_FLOOR_MINUS_09):
           (*NUM_Signal_Params).stop_track_index = 81;
           break;  
       
       case (SERIAL_FLOOR_MINUS_08):
           (*NUM_Signal_Params).stop_track_index = 82;
           break;  
       
       case (SERIAL_FLOOR_MINUS_07):
           (*NUM_Signal_Params).stop_track_index = 83;
           break;  

       case (SERIAL_FLOOR_MINUS_06):
           (*NUM_Signal_Params).stop_track_index = 84;
           break;  

       case (SERIAL_FLOOR_MINUS_05):
           (*NUM_Signal_Params).stop_track_index = 85;
           break;  

       case (SERIAL_FLOOR_MINUS_04):
           (*NUM_Signal_Params).stop_track_index = 86;
           break;  

       case (SERIAL_FLOOR_MINUS_03):
           (*NUM_Signal_Params).stop_track_index = 87;
           break;  
       
       case (SERIAL_FLOOR_MINUS_02):
           (*NUM_Signal_Params).stop_track_index = 88;
           break;  
       
       case (SERIAL_FLOOR_MINUS_01):
           (*NUM_Signal_Params).stop_track_index = 89;
           break;  
              
       case (SERIAL_GROUND): 
           (*NUM_Signal_Params).stop_track_index = 67;
           break;             
       
       case (SERIAL_HYPERSTAR): 
           (*NUM_Signal_Params).stop_track_index = 68;
           break; 
       
       case (SERIAL_HYPERME): 
           (*NUM_Signal_Params).stop_track_index = 69;
           break; 
       
       case (SERIAL_RESTAURANT): 
           (*NUM_Signal_Params).stop_track_index = 70;
           break;             
       
        case (SERIAL_LOBBY):
           (*NUM_Signal_Params).stop_track_index = 71;
           break; 
       
       case (SERIAL_MANAGEMENT): 
           (*NUM_Signal_Params).stop_track_index = 72;
           break;

       case (SERIAL_ARCHIVE): 
           (*NUM_Signal_Params).stop_track_index = 73;
           break;             

       case (SERIAL_ROOFGARDEN): 
           (*NUM_Signal_Params).stop_track_index = 74;
           break;             
       
       case (SERIAL_FOODCOURT): 
           (*NUM_Signal_Params).stop_track_index = 75;
           break;             

       case (SERIAL_PLAYGROUND): 
           (*NUM_Signal_Params).stop_track_index = 76;
           break;             
       
       case (SERIAL_PENTHOUSE): 
           (*NUM_Signal_Params).stop_track_index = 77;
           break;        
       
       case (SERIAL_POOL): 
           (*NUM_Signal_Params).stop_track_index = 78;
           break; 
       
       case (SERIAL_ROOFTOP): 
           (*NUM_Signal_Params).stop_track_index = 90;
           break;        
       
       case (SERIAL_PEDIATRICIAN): 
           (*NUM_Signal_Params).stop_track_index = 91;
           break;        

       case (SERIAL_EUROLOGIST): 
           (*NUM_Signal_Params).stop_track_index = 92;
           break;     
       
       case (SERIAL_GYNECOLOGIST): 
           (*NUM_Signal_Params).stop_track_index = 93;
           break; 
       
       case (SERIAL_DENTIST): 
           (*NUM_Signal_Params).stop_track_index = 94;
           break;        
       
       case (SERIAL_PROJECT_ONE): 
           (*NUM_Signal_Params).stop_track_index = 95;
           break;        

       case (SERIAL_EXITWAY): 
           (*NUM_Signal_Params).stop_track_index = 96;
           break;        
             
       default:
           (*NUM_Signal_Params).previous_stop = (*NUM_Signal_Params).current_stop; // If no meaningful floor status is available, assume that previous and current
                                                                                   // stop numbers are equal. Hence, only music is played after reaching the stop.
           break;          
     }

     //// Finalization
}

