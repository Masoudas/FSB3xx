/*******************************************************************************
********************************************************************************
*@ File:	Flash_Data_Read.c
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:96/07/15	Previous:95/10/20	Created:94/02/27
*@ Author:	M.Aghamohamadian 

*@ Brief:	This module is used for reading data from flash AT45DB321D(or E)
                according the rules of FSB board (see the report).

********************************************************************************
*******************************************************************************/
#include <inavr.h>
#include <ioavr.h>
#include "Flash_Data_Read.h"
#include "General.h"


void Flash_Data_Read(unsigned int *state_timer, unsigned char current_album, unsigned int *Album1, unsigned int *Album2, unsigned int *Album3)
{
     // Initialization
  
  
     // Main commands
     switch (current_state)
     {
       case (EMR):
                 Flash_Page_Read(EMR_current_page);  // Play the following pages of emergency signal, increase the page index.     
                 EMR_current_page++;
       break;    

       case (TEST_MODE):
                 Flash_Page_Read(STOP_STATUS_current_page);     
                 STOP_STATUS_current_page++;
       break;    
              
       case (MUS):
                 Flash_Page_Read(MUS_current_page);  // Play the following music pages, increase the page index.     
                 MUS_current_page++;
                 MUS_Page_Reset(current_album, Album1, Album2, Album3);  // Restart the MUS_current_page if necessary
       break;
    
       case (DEBOUNCE_NUM_SIGNAL):
                 Flash_Page_Read(MUS_current_page);  // Play the following music pages, increase the page index.     
                 MUS_current_page++;
                 MUS_Page_Reset(current_album, Album1, Album2, Album3);  // Restart the MUS_current_page if necessary
       break;
    
       case (OVL):
                 Flash_Page_Read(OVL_current_page);  // Play the following pages of DOB message, increase the page index.      
                 OVL_current_page++;
       break;
       
       case (DOB):
                 Flash_Page_Read(DOB_current_page);  // Play the following pages of DOB message, increase the page index.
                 DOB_current_page++;
       break;
    
       case (DING):
                 Flash_Page_Read(DING_current_page);  // Play the following pages of ding, increase the page index.
                 DING_current_page++;
       break;
    
       case (DING_DONG):
                 Flash_Page_Read(DINGDONG_current_page);  // Play the following pages of ding-dong, increase the page index.
                 DINGDONG_current_page++;
       break;
    
       case (DECLARE_STOP_STATUS):
                 Flash_Page_Read(STOP_STATUS_current_page);  // Declare the stop status, increase the page index.
                 STOP_STATUS_current_page++;
       break;
    
       case (MUS_1):
                 Flash_Page_Read(MUS_current_page);  // Play the following pages of music after declaring stop status, increase the page index.
                 MUS_current_page++;
                 MUS_Page_Reset(current_album, Album1, Album2, Album3);
       break;

       case (MUS_2):
                 Flash_Page_Read(MUS_current_page);  // Play the following pages of (rather relaxing!) music for emergency state.
                 MUS_current_page++;
       break;
    
       case (MUS_3):
                 Flash_Page_Read(MUS_current_page);  // Play the following pages of the current album.
                 MUS_current_page++;
                 MUS_Page_Reset(current_album, Album1, Album2, Album3);  // Restart the MUS_current_page if necessary                 
       break;
       
       case (SILENCE_1):        // For the states that require no sound play, have no action.
       break;   
       
       case (SILENCE_2): 
       break;
    
       case (LEARN_MODE): 
       break;
    
       case (SILENCE): 
       break;        
  
       case (ALBUM_CHANGE):
       break;   
    
       default:
                 current_state = SILENCE;
                 *state_timer = 0;
       break;
     }
  
  
     // Finalization
}


void MUS_Page_Reset(unsigned char current_album, unsigned int *Album1, unsigned int *Album2, unsigned int *Album3)
{
    // Initialization
  
  
    // Main commands
    if ((current_album == 1) && (MUS_current_page >= *(Album1+1) || MUS_current_page < *Album1)) // If the entire music of main album has been played.
    {
       MUS_current_page = *Album1;  // Restart from the top, else continue from current page.
    }
    else if ((current_album == 2) && (MUS_current_page >= *(Album2+1) || MUS_current_page < *Album2)) // Else if we are in the extra album 1 and we have exceeded its final page, restart from the top of this album
    {
       MUS_current_page = *Album2;  // Restart from the top of music track, else continue from current page.
    }
    else if ((current_album == 3) && (MUS_current_page >= *(Album3+1) || MUS_current_page < *Album2)) // Same for the second extra album
    {
       MUS_current_page = *Album3;   
    }  
  
    
    // Finalization

}


void Flash_Page_Read(unsigned int page_number)
{
     //// Initialization
     unsigned char        Add_First_Byte;         // MSB of page address.
     unsigned char        Add_Second_Byte;        // LSB of page address plus MSB of byte address.
     unsigned char        Add_Third_Byte;         // LSB of bite address.
     unsigned char        right_shift;            // The number of right shifts given to input page.
     unsigned char        left_shift;             // The number of left shifts given to input page.
     unsigned char        memory_number;          // The memory to be accessed in this read.
     
          
     //// Main Commands 
     // Decide on which memory to access by assessing the page number given to the function.
     if (page_number <= FINAL_PAGE)
     {
       memory_number = 1;
     }
     else
     {
       memory_number = 2;
       page_number = page_number - FINAL_PAGE;    // the page number for memory two is given an offset of 8129 pages so that it starts from zero as well.
     }
     
     
     // Assigning the address bits.
     right_shift = 6; // Right shifts are given to integer 'page' to derive MSB of page address.
     left_shift = 2;  // Left shifts are given to integer 'page' to derive LSB of page address.
     
     Add_First_Byte = ((unsigned char)(page_number >> right_shift)); 
     Add_Second_Byte = ((unsigned char)(page_number << left_shift)); 
     Add_Third_Byte = 0x00;

     
     // Start reading data from the memory.    
     Memory_Selection(memory_number);   // Select the desired memory to initiate SPI.
     SPI_Interface(Main_Mem_Read); // Sending the opcode D2H to initialize continuous reading.
     
     SPI_Interface(Add_First_Byte);   // Sending the page addresses.
     SPI_Interface(Add_Second_Byte);        
     SPI_Interface(Add_Third_Byte); 
     
     for (unsigned char i = 0; i < 4; i++) // Sending four don't care bytes.
     {
         SPI_Interface(DONT_CARE_BYTE); 
     }  
     
     for (unsigned int write_index = 0; write_index < 528; write_index++) // Reading the page.
     {          
         buffer_data[write_index] = SPI_Interface(DONT_CARE_BYTE);  // Sending a dummy byte address, as reading is continuous.
         Music_Deciphering(write_index);
     }
     
     Memory_Selection(DONT_CARE_BYTE);    // Deselect all memories.
     
  
     //// Finalization 

}


unsigned char SPI_Interface(unsigned char spi_data)
{
     SPDR = spi_data;	// The address byte is given to SPDR register.
     while (!(SPSR & 0x80));	// When the MSB of SPSR is one, data transmission is complete.
     return SPDR;	// The data in SPDR register is the data in this address byte.
}


void Memory_Selection(unsigned char memory_number)
{
     if (memory_number == 0)
     {
         // Deselecting both chips by setting the emitter and base of BJT to zero (see the report).
         SPI_PORT_WRITE |= ~ENABLE_CHIP_SELECT; 
         SPI_PORT_WRITE |= ENABLE_PB0; 
     }
     else if (memory_number == 1)
     {    
         SPI_PORT_WRITE &= ~ENABLE_PB0; // Select AT45(1) by setting PB0 to zero.
         SPI_PORT_WRITE &= ENABLE_CHIP_SELECT; // Setting chip-select signal to zero.
     }
     else if (memory_number == 2)
     {
         SPI_PORT_WRITE |= ENABLE_PB0; // Select AT45(2) by setting PB0 to one.
         SPI_PORT_WRITE &= ENABLE_CHIP_SELECT; // Setting chip-select signal to zero.
     }
}

void Music_Deciphering(unsigned int index)
{
   //// Initialization     
  
  
   //// Main commands
   // Redecorating the bytes, in order to become meaningful again!
   buffer_data[index] = (buffer_data[index] >> 4) + ((buffer_data[index] & 0x0F) << 4); // Swaping MSB and LSB bits.
   buffer_data[index] = ~(buffer_data[index]);
  
  
  //// Finalization
  
} 

