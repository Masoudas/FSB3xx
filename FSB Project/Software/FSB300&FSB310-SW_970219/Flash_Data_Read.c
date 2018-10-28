/*******************************************************************************
********************************************************************************
*@ File:	Flash_Data_Read.h
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:95/10/25	Previous:95/10/20	Created:94/02/27
*@ Author:	M.Aghamohamadian 

*@ Brief:	This module is used for reading data from flash AT45DB321D(or E)
                according the rules of FSB board (see the report).

********************************************************************************
*******************************************************************************/
#include <inavr.h>
#include <ioavr.h>
#include "Flash_Data_Read.h"
#include "General.h"

unsigned char Flash_Data_Read(unsigned char half_page_counter, unsigned int *state_timer, unsigned char current_album, unsigned int *Album1, unsigned int *Album2, unsigned int *Album3)
{
     // Initialization
     half_page_counter++;  // Start reading the second half page.
  
  
     // Main commands
     switch (current_state)
     {
       case (EMR):
                 EMR_current_page += Flash_Page_Read(EMR_current_page,half_page_counter);  // Play the following pages of emergency signal, increase the page index.     
       break;    

       case (TEST_MODE):
                 STOP_STATUS_current_page += Flash_Page_Read(STOP_STATUS_current_page,half_page_counter);     
       break;    
              
       case (MUS):
                 MUS_current_page += Flash_Page_Read(MUS_current_page,half_page_counter);  // Play the following music pages, increase the page index.     
                 MUS_Page_Reset(current_album, Album1, Album2, Album3);  // Restart the MUS_current_page if necessary
       break;
    
       case (DEBOUNCE_NUM_SIGNAL):
                 MUS_current_page += Flash_Page_Read(MUS_current_page,half_page_counter);  // Play the following music pages, increase the page index.     
                 MUS_Page_Reset(current_album, Album1, Album2, Album3);  // Restart the MUS_current_page if necessary
       break;
    
       case (OVL):
                 OVL_current_page += Flash_Page_Read(OVL_current_page,half_page_counter);  // Play the following pages of DOB message, increase the page index.      
       break;
       
       case (DOB):
                 DOB_current_page += Flash_Page_Read(DOB_current_page,half_page_counter);  // Play the following pages of DOB message, increase the page index.
       break;
    
       case (DING):
                 DING_current_page += Flash_Page_Read(DING_current_page,half_page_counter);  // Play the following pages of ding, increase the page index.
       break;
    
       case (DING_DONG):
                 DINGDONG_current_page += Flash_Page_Read(DINGDONG_current_page,half_page_counter);  // Play the following pages of ding-dong, increase the page index.
       break;
    
       case (DECLARE_STOP_STATUS):
                 STOP_STATUS_current_page += Flash_Page_Read(STOP_STATUS_current_page,half_page_counter);  // Declare the stop status, increase the page index.
       break;
    
       case (MUS_1):
                 MUS_current_page += Flash_Page_Read(MUS_current_page,half_page_counter);  // Play the following pages of music after declaring stop status, increase the page index.
                 MUS_Page_Reset(current_album, Album1, Album2, Album3);
       break;

       case (MUS_2):
                 MUS_current_page += Flash_Page_Read(MUS_current_page,half_page_counter);  // Play the following pages of (rather relaxing!) music for emergency state.
       break;
    
       case (MUS_3):
                 MUS_current_page += Flash_Page_Read(MUS_current_page,half_page_counter);  // Play the following pages of the current album.
                 MUS_Page_Reset(current_album, Album1, Album2, Album3);  // Restart the MUS_current_page if necessary                 
       break;
       
       case (SILENCE_1):        // For the states that require no sound play, have no action.
                 half_page_counter = 0;
       break;   
       
       case (SILENCE_2): 
                 half_page_counter = 0;
       break;
    
       case (LEARN_MODE): 
                 half_page_counter = 0;         
       break;
    
       case (SILENCE): 
                 half_page_counter = 0;         
       break;        
  
       case (ALBUM_CHANGE):
                 half_page_counter = 0;         
       break;   
    
       default:
                 half_page_counter = 0;
                 current_state = SILENCE;
                 *state_timer = 0;
       break;
     }
  
  
     // Finalization
     if (half_page_counter >= 2)   // If both half pages have been read, set the variable to zero.
     {
       half_page_counter = 0;
     }

     return(half_page_counter);   // Return one, which means one half page has been read
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


unsigned char Flash_Page_Read(unsigned int page_number, unsigned char half_page_counter)
{
     //// Initialization
     unsigned char        Add_First_Byte;         // MSB of page address.
     unsigned char        Add_Second_Byte;        // LSB of page address plus MSB of byte address.
     unsigned char        Add_Third_Byte;         // LSB of bite address.
     unsigned char        Dont_Care_Byte = 0x00;
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
       page_number = page_number - FINAL_PAGE;    // the page number for memory two is given an offset of 8100 pages so that it starts from zero as well.
     }
     
     
     // Assigning the address bits.
     right_shift = 6; // Right shifts are given to integer 'page' to derive MSB of page address.
     left_shift = 2;  // Left shifts are given to integer 'page' to derive LSB of page address.
     
     Add_First_Byte=((unsigned char)(page_number >> right_shift)); 
     Add_Second_Byte=((unsigned char)(page_number << left_shift)); 
       
     if (half_page_counter == 1)  // If reading the first half of the page, first byte will be byte zero.
     {
       Add_Second_Byte += 0x00;
       Add_Third_Byte = 0x00;
     }
     else if (half_page_counter == 2)     // If reading the second half of the page, set byte address to 0x108 (i.e, byte 264). 
     {
       Add_Second_Byte += 0x01;
       Add_Third_Byte = 0x08;
     }
     
     // Start reading data from the memory.    
     Memory_Selection(memory_number);   // Select the desired memory to initiate SPI.
     SPI_Interface(Main_Mem_Read); // Sending the opcode D2H to initialize continuous reading.
     
     SPI_Interface(Add_First_Byte);   // Sending the page addresses.
     SPI_Interface(Add_Second_Byte);        
     SPI_Interface(Add_Third_Byte); 
     
     for (unsigned char i = 0; i < 4; i++) // Sending four don't care bytes.
     {
         SPI_Interface(Dont_Care_Byte); 
     }  
     
     for (unsigned int write_index = 0; write_index < 264; write_index++) // Reading the page.
     {          
         buffer_data[write_index] = SPI_Interface(0x00);  // Sending a dummy byte address, as reading is continuous.
         Music_Deciphering(write_index);
     }
     
     Memory_Selection(0x00);    // Deselect all memories.
     
  
     //// Finalization 
     if (half_page_counter >= 2)
     {
       return(1);  // If the second half page has been read, return one, which means an entire page has been read.    
     }
     else
     {
       return(0); 
     }

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
   char         music_temp = 0; // A template that keeps the current data;
  
  
   //// Main commands
   music_temp = buffer_data[index];     // Saving a template of the byte.
  
   
   // Redecorating the bytes, in order to become meaningful again!
   buffer_data[index] = (buffer_data[index] >> 4) + ((music_temp & 0x0F) << 4); // Swaping MSB and LSB bits.
   buffer_data[index] = ~(buffer_data[index]);
  
  
  //// Finalization
  
} 

