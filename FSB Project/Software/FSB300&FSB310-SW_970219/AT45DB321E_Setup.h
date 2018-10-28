/*******************************************************************************
********************************************************************************
*@ File:	AT45DB321E_Setup.c
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:96/01/14	Previous:96/01/14	Created:96/01/14
*@ Author:	M.Aghamohamadian 

*@ Brief:	This header is used for reseting the page size of AT45DB321E to 
                528 byte per page.

********************************************************************************
*******************************************************************************/
/*----- Include Files --------------------------------------------------------*/
#ifndef AT45DB321E_SETUP_h
#define AT45DB321E_SETUP_h


/*----- CONSTANT DEFINITIONS -------------------------------------------------*/
//status register
#define         Status_reg_Read         0xD7

//Page size byte
#define         PAGE_SIZE_BIT          0x01

// Flash busy bit
#define         FLASH_BUSY_BIT          0x80


//// Flash page size change to 528 opcodes
#define         CHANGE_SIZE_OPCODE1     0x3D
#define         CHANGE_SIZE_OPCODE2     0x2A
#define         CHANGE_SIZE_OPCODE3     0x80
#define         CHANGE_SIZE_OPCODE4     0xA7


//// Flash erase opcodes
#define         ERASE_OPCODE1           0xC7
#define         ERASE_OPCODE2           0x94
#define         ERASE_OPCODE3           0x80
#define         ERASE_OPCODE4           0x9A


/*------ Variable Definition -------------------------------------------------*/


/*------ Function Definition -------------------------------------------------*/
unsigned int Flash_Page_Size(unsigned char memory_number);
/* 
Input:
    No input.
Output:
    Page size of AT45DB321D(E)
Description:
   This function determines the page size of the flash AT45DB321D. For this end,
   it sends the opcode D7H to the flash and reads the LSB of register "Status Register".
   It also sets the global "Flash_Page_Size" to the derived page size.

*/

void Change_Page_Size(unsigned char memory_number);
/* 
Input:
    No input.
Output:
    No output
Description:
   Sets the register of the flash AT45DB321E, so that its page is 528 bytes.     
*/

void Flash_Erase(unsigned char memory_number);
/* 
Input:
    No input.
Output:
    No output
Description:
    This function erases all data in AT45DB321E, which is needed if we require
    the reset the page sizes of this flash.    
*/

unsigned char Count_Memory_Chips(unsigned int page_address[][2]);
/* 
Input:
    No input.
Output:
    No output
Description:
    Checks to see if there are two memories on the board by identifying the possible
    page numbers above 8100 (maxmimum pages of memory).
*/


#endif