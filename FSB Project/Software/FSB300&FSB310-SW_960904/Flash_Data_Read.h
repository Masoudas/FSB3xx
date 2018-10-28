/*******************************************************************************
********************************************************************************
*@ File:	Flash_Data_Read.h
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:95/10/25	Previous:95/10/20	Created:94/02/27
*@ Author:	M.Aghamohamadian 

*@ Brief:	This header is used for reading data from flash AT45DB321D(or E).

********************************************************************************
*******************************************************************************/
/*----- Include Files --------------------------------------------------------*/

#ifndef FLASH_DATA_READ_h
#define FLASH_DATA_READ_h


/*----- CONSTANT DEFINITIONS -------------------------------------------------*/
// SPI port defenition for chip selection (see the FSB report).
#define         ENABLE_CHIP_SELECT         0xFB   // Enabling the chip select pin, which means putting a zero on it (which is PB2).
#define         ENABLE_PB0                 0x01   // Enabling PB0, which means setting it to one (the auxiliry port for selecting between the memories).

// Main memory read
#define         Main_Mem_Read              0xD2

// Continuous array read opcode
#define         CON_ARRAY_READ             0x1B

// Total pages of AT45
#define         FINAL_PAGE                 8192   // The last page on which data exists.

/*------ Global Variable Definition ------------------------------------------*/
extern    unsigned int     EMR_current_page;   // The current page of emergency message being played.
extern    unsigned int     MUS_current_page;   // The current page of music being played.
extern    unsigned int     OVL_current_page;   // The current page of overload message being played.
extern    unsigned int     DOB_current_page;   // The current page of door open message being played.
extern    unsigned int     DING_current_page;  // The current page of ding message being played.
extern    unsigned int     DINGDONG_current_page;  // The current page of ding-dong message being played.
extern    unsigned int     STOP_STATUS_current_page;  // The current page of stop declaration being played.


/*------ Function Definition -------------------------------------------------*/
unsigned char Flash_Data_Read(unsigned char half_page_counter, unsigned int *state_timer, unsigned char current_album, unsigned int *Album1, unsigned int *Album2, unsigned int *Album3);
/*
Input: 
          half_page_counter: Denotes  the current half page being read.

Output: 
          No output.

Description:
          This function works as a chennel between main() and Flash_Page_Read(),
          and determines which pages of flash memory should be read based on the
          current state.
*/

void MUS_Page_Reset(unsigned char current_album, unsigned int *Album1, unsigned int *Album2, unsigned int *Album3);
/*
Input: 
          No input.

Output: 
          No output.

Description:
          Used for resetting the MUS_current_page when it reaches the final
          page of the current album.
*/

unsigned char Flash_Page_Read(unsigned int page, unsigned char half_page_counter);
/* 
Input:
    page: Denotes the current page to be read.
    half_page_counter: The counter which determines which half of current page should be read.

Output:
    The updated half_page_counter.

Description:
    This functions reads data from a desired page of AT45DB321E(or D) flash using SPI 
    protocol. For this end, the address bytes are created, chip select signal 
    is properly set and data is read from the flash assuming either page size
    of 528 or 512. Data read from the flash is written to the array "Sound_Buffer".

*/

unsigned char SPI_Interface(unsigned char spi_data);
/* 
Input:
    spi_data: Instruction to be fed to the memory.

Output:
    No output

Description:
    This function sends an instruction to the flash memory on SPCR register, 
    then waits while the fourth bit in SPSR register is one (which means that
    the transaction is complete), then reads the content of SPCR again (which is
    the data sent back from the flash).
*/

void Memory_Selection(unsigned char memory_number);
/* 
Input:
    memory_number: The memory to be selected (or deselecting all memory by sending 0x00)

Output:
    No output

Description:
    This function assigns appropriate values to PB0 and chip select pin of SPI to select
    a desired memory.
*/

void Music_Deciphering(unsigned int index);
/* 
Input:
    index: The byte number read from AT45.

Output:
    No output

Description:
    This function deciphers the data read from AT45 using the ciphering pattern discussed 
    in the report.    
*/

#endif