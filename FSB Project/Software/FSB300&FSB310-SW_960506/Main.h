/*******************************************************************************
********************************************************************************
*@ File:	Main.cpp
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:95/10/07	Previous:95/10/07	Created:95/10/07
*@ Author:	M. Aghamohamadian 

*@ Brief:	This header contains the parameter and definitions used in main.cpp.

********************************************************************************
*******************************************************************************/

/*----- Include Files --------------------------------------------------------*/
#ifndef MAIN_h
#define MAIN_h
#include "General.h"
#include "IO_Module.h"
#include "EEPROM_Secure_Read.h"

/*----- CONSTANT DEFINITIONS -------------------------------------------------*/
//// States
enum Generic_State // General states in main.cpp (for implementing the main loop) 
     {
      READY,  // Ready to perform state functions/ choose a new state.
      BUSY,   // Busy performing current state functions/ choosing a new state.
      WAIT    // (Choosing)state has finished.
     };


/*------ Variable Definition -------------------------------------------------*/
//// States
Generic_State       Status_Register;        // Denotes the general state of the main (BUSY, READY, WAIT).


//// Counters
unsigned char       half_page_counter;   // Denotes the first or second half the current page of memory
unsigned int        OVL_Delay_Counter;  // The delay before playing OVL message.
unsigned int        DOB_Delay_Counter;  // The delay before playing DOB message.
unsigned int        buffer_counter;   // Denotes the byte number being read at timer1/counter1 interrput.  
unsigned char       sub_buffer_counter; // Denotes the number of times a byte is repeated for upsampling


//// Flags
bool                start_up_flag;   // Denotes whether or not start up time has elapsed.
                                     // Zero means this time has not elapsed and one means otherwise.
bool                new_stop_arrival_flag;   // Denotes whether the elevator has reached a new stop, set upon change of trigger signal after the music state.
                                              // If set to one, means that the elevator has reached a new stop, zero means otherwise.


//// Timers
unsigned int        state_timer;   // Denotes the time needed to perform current state. 
                                   // It is set to start up delay at first when initialized in main.


//// Structures
struct              ControlSignal           CTRL_Signal_Params;    // The structure which entails the control signal parameters.
struct              NumeratorSignal         NUM_Signal_Params;     // The structure which entails the numerator signal parameters.
struct              VolumeSignal            VOL_Signal_Params;     // The structure which entails the volume signal parameters.


//// I2C related parameters
unsigned char       I2C_data[4];              // Denotes the data to be received via I2C.
bool                I2C_output_flag;          // Denotes the status of I2C (finished or busy).


//// Other parameters
unsigned int        page_address[TOTAL_MEMORY_FILES][2];      // Denotes the initial and final page of each message/music.  
unsigned char       current_album;                            // Denotes the current album being played in the board.   
unsigned char       stop_track_index ;                        // Denotes the space in memory where the current stop status message is saved.
unsigned char       test_input_number;                        // In the test mode, denotes to which input pin a test signal is given.
bool                Board_Type;                               // Denotes the current hardware platform (i.e, FSB300 or FSB310).


/*------ Function Definition -------------------------------------------------*/
Total_State Change_State(Total_State current_state);
/* 
Input:
    No input.
Output:
    No output
Description:
    The function for changing the states in the main loop of the program.    

*/

void Initial_Setup(void);
/* 
Input:
    No input.
Output:
    No output
Description:
    This functions assings an initial value to all parameters defined in Main.cpp
*/

void Parameter_Initial_Setup(void);
/* 
Input:
    No input.
Output:
    No output
Description:
    Many variables defined aboved are assigned values by calling this function in Initial_Setup().    
*/

void timer_update(void);
/* 
Input:
    No input.
Output:
    No output
Description:
    Used for updating the timer in Main.cpp.

*/

void Page_Extraction(void);
/* 
Input:
    No input.
Output:
    No output
Description:    
    This function extracts the initial and final page of each message/ music from
    the first page (page zero) of the flash.
*/

void Empty_Flash_Buffer(void);
/*
Input: 
          No input.

Output: 
          No output.

Description:
         Used for deleting data from the buffer which holds the data read from 
         AT45DB321E.
*/

bool Board_Type_Detection();
/*
Input: 
          No input.

Output: 
          A bool variable, where zero denotes that the board is FSB300, and one denotes that it is FSB310.

Description:
         Used for determining the platform (FSB300 or FSB310) by reading PB0.
*/


#endif 


