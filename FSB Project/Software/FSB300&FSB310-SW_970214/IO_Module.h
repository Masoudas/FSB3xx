/*******************************************************************************
********************************************************************************
*@ File:	IO_Module.c
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:96/01/14	Previous:96/01/14	Created:96/01/14
*@ Author:	M.Aghamohamadian 

*@ Brief:	This header is used for I/O definitions of FSB board.

********************************************************************************
*******************************************************************************/
/*----- Include Files --------------------------------------------------------*/

#ifndef IO_MODULE_h
#define IO_MODULE_h
#include "General.h"


/*----- CONSTANT DEFINITIONS -------------------------------------------------*/
//// FSB300 parameters
// Control signal don't care bits
#define         EMR_DontC_bits            0x04     // Zeros denote the don't care bits for checking the emergency signal
#define         TRG_DontC_bits            0x20     
#define         OVL_DontC_bits            0x30     
#define         DOB_DontC_bits            0x38     // ...
#define         VOL_DontC_bits            0x03    

// Control signal shapes (besides those set in the learn mode)
#define         VOL_UP_INPUT              0x02    
#define         VOL_DOWN_INPUT            0x01    
#define         ALBUM_CHANGE_INPUT        0x00     // Denotes the shape of the volume signals when both keys are pushed.
#define         VOL_UNPUSHED_INPUT        0x03     // Denotes the shape of the volume signals when neither key is pushed.
#define         PARALLEL_EMR_INPUT        0x04     // The shape of emeregency control signal. See the report.

// Stop status signal shapes in parallel mode (i.e, FSB300)
#define         PARALLEL_PARK_09          0x21     // The shape of numerator input signal for parking 9. See the report.
#define         PARALLEL_PARK_08          0x01   
#define         PARALLEL_PARK_07          0xE1   
#define         PARALLEL_PARK_06          0x09   
#define         PARALLEL_PARK_05          0x29   
#define         PARALLEL_PARK_04          0x25   
#define         PARALLEL_PARK_03          0x61   
#define         PARALLEL_PARK_02          0x51   
#define         PARALLEL_PARK_01          0xE5   
#define         PARALLEL_PARK_00          0x13   
#define         PARALLEL_BASEMENT         0x0F   
#define         PARALLEL_GROUND           0x8B
#define         PARALLEL_GROUND0          0x83
#define         PARALLEL_LOBBY            0x9F  
#define         PARALLEL_FLOOR01          0xE7
#define         PARALLEL_FLOOR02          0x53
#define         PARALLEL_FLOOR03          0x63
#define         PARALLEL_FLOOR04          0x27
#define         PARALLEL_FLOOR05          0x2B
#define         PARALLEL_FLOOR06          0x0B
#define         PARALLEL_FLOOR07          0xE3
#define         PARALLEL_FLOOR08          0x03
#define         PARALLEL_FLOOR09          0x23
#define         PARALLEL_FLOOR10          0x82
#define         PARALLEL_FLOOR11          0xE6
#define         PARALLEL_FLOOR12          0x52
#define         PARALLEL_FLOOR13          0x62
#define         PARALLEL_FLOOR14          0x26
#define         PARALLEL_FLOOR15          0x2A
#define         PARALLEL_FLOOR16          0x0A
#define         PARALLEL_FLOOR17          0xE2
#define         PARALLEL_FLOOR18          0x02
#define         PARALLEL_FLOOR19          0x22
#define         PARALLEL_FLOOR20          0x80
#define         PARALLEL_FLOOR21          0xCC
#define         PARALLEL_FLOOR22          0xA4
#define         PARALLEL_FLOOR23          0xC4
#define         PARALLEL_FLOOR24          0x24
#define         PARALLEL_FLOOR25          0x28
#define         PARALLEL_FLOOR26          0x0C
#define         PARALLEL_FLOOR27          0xE0
#define         PARALLEL_FLOOR28          0x00
#define         PARALLEL_FLOOR29          0x20


//// FSB310 parameters
// Control signal shapes in serial mode (i.e FSB310)
#define         SERIAL_NO_CTRL_INPUT        0x80   // The case where there is no control signal.
#define         SERIAL_EMR_INPUT            0x81
#define         SERIAL_TRG_INPUT            0x82
#define         SERIAL_OVL_INPUT            0x84
#define         SERIAL_DOB_INPUT            0x88
#define         SERIAL_DIRECTION_UP_INPUT   0x90
#define         SERIAL_DIRECTION_DOWN_INPUT 0xA0

// Stop status signal shapes in serial mode (i.e, FSB310)
#define         SERIAL_PARK_09            0x0C10  // The shape of numerator input signal for parking 9 in series mode. See the report.
#define         SERIAL_PARK_08            0x0C00   
#define         SERIAL_PARK_07            0x0C78   
#define         SERIAL_PARK_06            0x0C02   
#define         SERIAL_PARK_05            0x0C12   
#define         SERIAL_PARK_04            0x0C19   
#define         SERIAL_PARK_03            0x0C30   
#define         SERIAL_PARK_02            0x0C24   
#define         SERIAL_PARK_01            0x0C79
#define         SERIAL_PARK               0x7F0C
#define         SERIAL_FLOOR_MINUS_10     0x3F40   
#define         SERIAL_FLOOR_MINUS_09     0x3F10                 
#define         SERIAL_FLOOR_MINUS_08     0x3F00
#define         SERIAL_FLOOR_MINUS_07     0x3F78                                        
#define         SERIAL_FLOOR_MINUS_06     0x3F02   
#define         SERIAL_FLOOR_MINUS_05     0x3F12                                     
#define         SERIAL_FLOOR_MINUS_04     0x3F19                                     
#define         SERIAL_FLOOR_MINUS_03     0x3F30  
#define         SERIAL_FLOOR_MINUS_02     0x3F24                                     
#define         SERIAL_FLOOR_MINUS_01     0x3F79
#define         SERIAL_BASEMENT_09        0x0310  
#define         SERIAL_BASEMENT_08        0x0300   
#define         SERIAL_BASEMENT_07        0x0378   
#define         SERIAL_BASEMENT_06        0x0302   
#define         SERIAL_BASEMENT_05        0x0312
#define         SERIAL_BASEMENT_04        0x0319
#define         SERIAL_BASEMENT_03        0x0330  
#define         SERIAL_BASEMENT_02        0x0324
#define         SERIAL_BASEMENT_01        0x0379
#define         SERIAL_BASEMENT           0x7F03  
#define         SERIAL_GROUND             0x7F42    // Hamkaf (in human terms!)
#define         SERIAL_MANAGEMENT         0x7F25
#define         SERIAL_HYPERSTAR          0x7F0B
#define         SERIAL_HYPERME            0x0906
#define         SERIAL_ARCHIVE            0x7F20    // Baygani (again in human terms!)
#define         SERIAL_ROOFGARDEN         0x0F42    
#define         SERIAL_FOODCOURT          0x0E46    
#define         SERIAL_PLAYGROUND         0x0C42    
#define         SERIAL_PENTHOUSE          0x0C09   
#define         SERIAL_RESTAURANT         0x7F0F
#define         SERIAL_LOBBY              0x7F47
#define         SERIAL_POOL               0x0C47
#define         SERIAL_ROOFTOP            0x0909      
#define         SERIAL_PEDIATRICIAN       0x4612
#define         SERIAL_EUROLOGIST         0x0641
#define         SERIAL_GYNECOLOGIST       0x4206
#define         SERIAL_DENTIST            0x4012
#define         SERIAL_PROJECT_ONE        0x790C
#define         SERIAL_EXITWAY            0x4006
#define         SERIAL_FLOOR01            0x7F79
#define         SERIAL_FLOOR02            0x7F24
#define         SERIAL_FLOOR03            0x7F30
#define         SERIAL_FLOOR04            0x7F19
#define         SERIAL_FLOOR05            0x7F12
#define         SERIAL_FLOOR06            0x7F02
#define         SERIAL_FLOOR07            0x7F78
#define         SERIAL_FLOOR08            0x7F00
#define         SERIAL_FLOOR09            0x7F10
#define         SERIAL_FLOOR10            0x7940
#define         SERIAL_FLOOR11            0x7979
#define         SERIAL_FLOOR12            0x7924
#define         SERIAL_FLOOR13            0x7930
#define         SERIAL_FLOOR14            0x7919
#define         SERIAL_FLOOR15            0x7912
#define         SERIAL_FLOOR16            0x7902
#define         SERIAL_FLOOR17            0x7978
#define         SERIAL_FLOOR18            0x7900
#define         SERIAL_FLOOR19            0x7910
#define         SERIAL_FLOOR20            0x2440
#define         SERIAL_FLOOR21            0x2479
#define         SERIAL_FLOOR22            0x2424
#define         SERIAL_FLOOR23            0x2430
#define         SERIAL_FLOOR24            0x2419
#define         SERIAL_FLOOR25            0x2412
#define         SERIAL_FLOOR26            0x2402
#define         SERIAL_FLOOR27            0x2478
#define         SERIAL_FLOOR28            0x2400
#define         SERIAL_FLOOR29            0x2410
#define         SERIAL_FLOOR30            0x3040
#define         SERIAL_FLOOR31            0x3079
#define         SERIAL_FLOOR32            0x3024
#define         SERIAL_FLOOR33            0x3030
#define         SERIAL_FLOOR34            0x3019
#define         SERIAL_FLOOR35            0x3012
#define         SERIAL_FLOOR36            0x3002
#define         SERIAL_FLOOR37            0x3078
#define         SERIAL_FLOOR38            0x3000
#define         SERIAL_FLOOR39            0x3010
#define         SERIAL_FLOOR40            0x1940


/*------ Variable Definition -------------------------------------------------*/
//// Signal related constants
enum CTRL_Signal_Type // Denotes the type of controller signal received.
    {
     EMR_SIGNAL,
     OVL_SIGNAL,
     DOB_SIGNAL,
     TRG_SIGNAL,
     NO_SIGNAL,
    };

enum VOLUME_Signal_Type // Denotes the type of volume controller signal received.
    {
     VOL_UP_SIGNAL,   
     VOL_DOWN_SIGNAL,
     ALBUM_CHANGE_SIGNAL,
     VOL_NO_SIGNAL,
    };


//// Prototypes for the signal structures
// Control signal prototype
struct ControlSignal{
       CTRL_Signal_Type    CTRL_Signal;         // Denotes the current control signal (after debounce).
       unsigned char       debounce_counter;    // keeps the number of times a control signal has been debounced. 
       unsigned char       current_input;       // The current input control signal.            
       unsigned char       previous_input;      // The previous input control signal.            
       unsigned char       PARALLEL_TRG_input;  // The shape of control signal corresponding to trigger signal.
       unsigned char       PARALLEL_OVL_input;  // The shape of control signal corresponding to overload signal.
       unsigned char       PARALLEL_DOB_input;  // The shape of control signal corresponding to door open signal.
      };

// Numerator signal prototype
struct NumeratorSignal{
       unsigned char                NUM_Signal;               // Denotes the current numerator signal (after debounce).
       unsigned char                debounce_counter;         // keeps the number of times a numerator signal has been debounced. 
       unsigned char                current_input;            // The current input numerator signal.            
       unsigned char                previous_input;           // The previous input numerator signal.            
       unsigned char                stop_track_index;         // Denotes the index of the file corresponding the current stop status.
       unsigned int                 current_stop;             // Denotes the current stop (see the definitions of LCB or CIB board)
       unsigned int                 previous_stop;            // Denotes the previous stop index
      };

// Volume signal prototype
struct VolumeSignal{
       VOLUME_Signal_Type           VOL_Signal;               // Denotes the current volume signal  (after debounce, before key release).
       unsigned char                debounce_counter;         // keeps the number of times the volume control signal has been debounced. 
       unsigned char                keys_current_state;       // The current state of the volume keys.
       unsigned char                keys_previous_state;      // The previous state of the volume keys.
       unsigned char                current_input;            // The current input volume signal.            
       unsigned char                previous_input;           // The previous input volume signal.            
       unsigned char                digit_volume_level;       // The digital volume level (or shifts to left in OCR1 variable).
      };


/*------ Function Definition -------------------------------------------------*/
void Parallel_CTRL_Signal_Detection(struct ControlSignal *CTRL_Signal_Params, bool start_up_flag);

/*
Input: 
          *CTRL_Signal_Params: The pointer to the structure that holds all parameters related to control signal.
          start_up_flag: Denotes whether start-up time has elapsed or not.

Output: 
          No output.

Description:
          This functions is used for debouncing and detecting the control signal in parallel mode (i.e, FSB300).
*/

void Parallel_NUM_Signal_Detection(struct NumeratorSignal *NUM_Signal_Params);

/*
Input: 
          *NUM_Signal_Params: The pointer to the structure that holds the current and previous stop number along with numerator signal value.

Output: 
          No output.

Description:
          This function is used for debouncing the numerator signal in parallel mode (i.e, FSB300).
*/

void VOL_Signal_Detection(struct VolumeSignal *VOL_Signal_Params);

/*
Input: 
          *VOL_Signal_Params: Denotes the pointer to structure that holds the current volume signal parameters.

Output: 
          No output.

Description:
*/

char Parallel_StopStatus_Finder(struct NumeratorSignal *NUM_Signal_Params);

/*
Input: 
          *Num_Signal_Params: The structure that holds the current and previous stop number along with numerator signal value.

Output: 
          No output.

Description:
          This functions determines the current stop status based on the debounced numerator singal.
*/

void Serial_CTRL_Signal_Detection(struct ControlSignal *CTRL_Signal_Params, struct NumeratorSignal *NUM_Signal_Params, bool start_up_flag, unsigned char I2C_CTRL_frame[]);

/*
Input: 
          *CTRL_Signal_Params: The structure that holds all parameters related to control signal.
          *NUM_Signal_Params: The structure that holds the current and previous stop number along with numerator signal value.
          start_up_flag: Denotes whether start-up time has elapsed or not.

Output: 
          No output.

Description:
          This functions is used for detecting the control signal in serial mode (i.e, FSB310).
*/

void Serial_NUM_Signal_Detection(struct NumeratorSignal *NUM_Signal_Params, unsigned char I2C_NUM_frame[]);     

/*
Input: 
          *NUM_Signal_Params: The structure that holds the current and previous stop number along with numerator signal value.

Output: 
          The space in the memory corresponding to the current stop status.

Description:
          This functions is used for detecting the numerator signal in serial mode (i.e, FSB310).
*/

#endif
