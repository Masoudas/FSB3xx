/*******************************************************************************
********************************************************************************
*@ File:	AT45DB321E_Setup.c
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:96/01/14	Previous:96/01/14	Created:96/01/14
*@ Author:	M.Aghamohamadian 

*@ Brief:	This module contains the functions used for reseting the page
                size of AT45DB321E to 528 byte per page.

********************************************************************************
*******************************************************************************/
#include "General.h"
#include "AT45DB321E_Setup.h"
#include "Flash_Data_Read.h"

unsigned char Count_Memory_Chips(unsigned int page_address[][2])
{
    // Initialization
    unsigned char  number_of_memories;   // The flag which denotes that there are two memories. One means that there are!
  
  
    // Main commands
    for (unsigned char file_index = 0; file_index < TOTAL_MEMORY_FILES; file_index++)
    {
      if (page_address[file_index][1] > FINAL_PAGE) // Check to see if there is any page index above the maximum page size.
      {
        number_of_memories = 2;
      }
    }
  
  
    // Finalization
    return(number_of_memories);
  
}

unsigned int Flash_Page_Size(unsigned char memory_number) 
{
     //// Initialization
     unsigned char       read_count = 0;         // The number of times status register has been read from the flash.
     unsigned char       vote = 0;               // The number of times one is read from the flash (i.e, flash is 528 byte per page).
     unsigned char       status_register = 0;    // The status register of flash AT45DB321E. 
     unsigned char       Dont_Care_Byte = 0x00; 

        
     //// Main commands
     // Read status register eleven times and decide on the page size using majority logic.
     while (read_count < 10)  
     {     
       Memory_Selection(memory_number);    // Send appropriate chip select signal.

       SPI_Interface(Status_reg_Read); // Sending the opcode E8H to initialize continuous reading.     
       status_register = SPI_Interface(Dont_Care_Byte);

       // Deselecting the current chip.
       Memory_Selection(0x00);   

       status_register &= PAGE_SIZE_BIT; // Extract bit zero of status register.
       vote += status_register;   // Increment vote parameter if this bit is one.

       read_count += 1;
     }

     
     //// Finalization     
     // Assigning flash page size based on the votes.
     if (vote >= 5)
     {
       return(512);
     }
     else
     {
       return(528);
     }   
}  


void Flash_Erase(unsigned char memory_number)
{
     // Initialization
     unsigned char Dont_Care_Byte = 0x00;
     unsigned char status_register = 0x00;

     // Main commands   
     Memory_Selection(memory_number);    // Send appropriate chip select signal.

     SPI_Interface(ERASE_OPCODE1); // Send the first byte of opcode to erase the memory.     
     SPI_Interface(ERASE_OPCODE2); // Send the second byte.
     SPI_Interface(ERASE_OPCODE3); // Send the third byte.
     SPI_Interface(ERASE_OPCODE4); // Send the fourth byte.

     Memory_Selection(0x00);    // Deselect the chip.
     
     // Wait for the command to finish.
     Memory_Selection(memory_number);    // Send appropriate chip select signal.
     SPI_Interface(Status_reg_Read); // Sending the opcode to read memory register.     
     status_register = SPI_Interface(Dont_Care_Byte);
     
     while(!(status_register & FLASH_BUSY_BIT))
     {
        status_register = SPI_Interface(Dont_Care_Byte);
     }

     Memory_Selection(0x00);    // Deselect the chip.     
     
     
     // Finalization
}


void Change_Page_Size(unsigned char memory_number)
{
     //// Initialization
     unsigned char Dont_Care_Byte = 0x00;
     unsigned char status_register = 0x00;


     //// Main commands   
     Memory_Selection(memory_number);    // Send appropriate chip select signal.
     
     SPI_Interface(CHANGE_SIZE_OPCODE1); // Send the first byte of opcode to change page size to 528 bytes.     
     SPI_Interface(CHANGE_SIZE_OPCODE2); // Send the second byte.
     SPI_Interface(CHANGE_SIZE_OPCODE3); // Send the third byte.
     SPI_Interface(CHANGE_SIZE_OPCODE4); // Send the fourth byte.

     Memory_Selection(0x00);    // Deselect the chip.     
     
     // Waiting until the above operation is complete.
     Memory_Selection(memory_number);    // Send appropriate chip select signal.

     SPI_Interface(Status_reg_Read); // Sending the opcode to read memory register.     
     status_register = SPI_Interface(Dont_Care_Byte);
     
     while(!(status_register & FLASH_BUSY_BIT))
     {
        status_register = SPI_Interface(Dont_Care_Byte);
     }
     Memory_Selection(0x00);    // Deselect the chip.     
     
     
     //// Finalization
}


