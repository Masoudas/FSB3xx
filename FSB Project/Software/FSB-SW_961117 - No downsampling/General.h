/*******************************************************************************
********************************************************************************
*@ File:	All files
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:95/09/18	Previous:95/09/09	Created:95/09/09
*@ Author:	M. Aghamohamadian 

*@ Brief:	This header contains general parameters (such as states and etc) and 
*               function definitions used commonly in all functions.

********************************************************************************
*******************************************************************************/

/*----- Include Files --------------------------------------------------------*/
#ifndef GENERAL_h
#define GENERAL_h


/*----- CONSTANT DEFINITIONS -------------------------------------------------*/
//// States
enum Total_State  // General states of board.
     {
      TEST_MODE,             // Test mode (in POR)
      LEARN_MODE,            // Learn mode (in POR)
      EMR,                   // Emergency
      OVL,                   // Overload    
      DOB,                   // Door open    
      DING,                  // Ding (elevator ascending)   
      DING_DONG,             // Ding Dong (elevator descending)   
      DEBOUNCE_NUM_SIGNAL,   // Debounce numerator signal after trigger signal is cut off
      DECLARE_STOP_STATUS,   // Stop status declaration
      MUS,                   // Play music while receiving trigger signal   
      MUS_1,                 // Play music after trigger signal is disconnected
      MUS_2,                 // Play emergency music after playing the emergency message
      MUS_3,                 // Play an entire album in album change mode
      SILENCE,               // Silence 
      SILENCE_1,             // Eternal silence after playing emergency music (unless emergency signal disappears)
      SILENCE_2,             // Silence in the test mode
      ALBUM_CHANGE           // Changing the current album of the board
     };


//// Delays and time lengths
#define         START_UP_DELAY            610     // Denotes the start up delay of the board before reading the emergency signal
#define         OVL_DELAY                 610     // Denotes the delay before playing OVL message (OVL_DELAY*program_tick).
#define         DOB_DELAY                 610     // Denotes the delay before playing DOB message (DOB_DELAY*program_tick).
#define         MUSIC_BEFORE_STOP         32      // The length of music played before debouncing the numerator signal (MUSIC_BEFORE_STOP*program_tick).
#define         MUSIC_AFTER_STOP          625     // The length of music played after declaring stop status (MUSIC_AFTER_STOP*program_tick).


//// I/O port
#define         CTRL_PORT_READ            PINC  
#define         CTRL_PORT_DIRECTION       DDRC
#define         CTRL_PORT_WRITE           PORTC
#define         NUM_PORT_READ             PIND  
#define         NUM_PORT_DIRECTION        DDRD
#define         NUM_PORT_WRITE            PORTD
#define         SPI_PORT_READ             PINB  
#define         SPI_PORT_DIRECTION        DDRB
#define         SPI_PORT_WRITE            PORTB


//// Other constants
// Debounce parameters
#define         CTRL_DEBOUNCE_NUMBER             5      // Denotes the number of times a control signal needs to be debounced. 
                                                        // (i.e control signal must remain the same for CTRL_DEBOUNCE_NUMBER*program_tick to be detected).
#define         NUM_DEBOUNCE_NUMBER              5      // Denotes the number of times a numerator signal needs to be debounced (half a second in human terms!). 
#define         VOL_DEBOUNCE_NUMBER              2      // Denotes the number of times the volume signal needs to be debounced.
#define         LEARN_DEBOUNCE_NUMBER            32     // Denotes the number of times an input control singal needs to be debounced in the learn mode.
#define         TEST_DEBOUNCE_NUMBER             3      // Denotes the number of times the input signals need to be debounced in test mode.
#define         BOARD_TYPE_DEBOUNCE_NUMBER       9      // MUST BE AN ODD NUMBER! Denotes the number of times PB0 signal is debounced for determining the board type (i.e, FSB300 or FSB310). 

// EEPROM address where some important data are stored
#define         EEPROM_VOL_ADD                  0x00    // Address for the current level of digital volume.
#define         EEPROM_ERRONEOUS_STATE_ADD      0x01    // Address for saving the current erroneous state (in the sole interrupt of the program).
#define         EEPROM_ALBUM_ADD                0x02    // Address for saving the current album.
#define         EEPROM_DOBTRG_ACTIVE_LEVEL_ADD  0x03    // Address for saving the shape of the trigger signal.
#define         EEPROM_MEMORY_PAGES_ADD         0x04    // Address for saving whether memory pages are changed to 528 bytes.

// Board types
#define         FSB300                          0       // Denotes that the current hardware is that of FSB300.
#define         FSB310                          1       // Denotes that the current hardware is that of FSB310.

// Memory page size modified to 528 
#define         PAGES_MODIFIED_528              0       // Denotes that the page size of memories have been tested to be 528.

// I2C related parameters
#define         I2C_DATA_LENGTH                 4       // The number of bytes to be received via I2C.
#define         I2C_SLAVE_ADDRESS               0x01    // The address to which FSB310 responds.
#define         I2C_BITRATE                     0x00    // The bitrate of I2C.
#define         I2C_FREQUENCY_PRESCALAR         0x00    // The frequency prescalar.

// Albums
#define         NUMBER_OF_ALBUMS                3       // Number of albums.
#define         ALBUM1_FILE_NUMBER              5       // The main album file number (or the row in page_address[][]) corresponding to the first album.
#define         EXTRA_ALBUM1_FILE_NUMBER        79      // The ... the first extra album.
#define         EXTRA_ALBUM2_FILE_NUMBER        80      // The ... the second extra album.

// Miscellaneous
#define         MAX_VOLUME_LEVEL                6       // Maximum defined volume.
#define         MIN_VOLUME_LEVEL                3       // Maximum defined volume.
#define         TOTAL_MEMORY_FILES              90      // Number of files that are loaded in the memory(ies)    
#define         SYNCHRONOUS_LOOP_UNCHECKED      0       // Denotes that the status of synchronous loop has not been checked in the timer/counter interrupt.
#define         SYNCHRONOUS_LOOP_CHECKED        1       // Denotes that the status of synchronous loop has been checked in the timer/counter interrupt.
#define         DONT_CARE_BYTE                  0x00    // Don't care byte used for SPI interface with AT45.

/*------ Global Variable Definition ------------------------------------------*/
//// States
extern           Total_State                    current_state;            // Denotes the current state of FSB (music, silence and etc.)


//// Counters


//// Flags


//// Other globals
extern    unsigned char                buffer_data[528];         // Data read from flash at each call of Flash_Page_Read(). 


/*------ Function Definition -------------------------------------------------*/

#endif 


