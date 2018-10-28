// DataFlash.h for FSB

#ifndef DATAFLASH_h
#define DATAFLASH_h

//#pragma language=extended




//unsigned char first_byte_page , second_byte_page, start_byte_add; // the address of the flash

void play_data_flash(unsigned long int);
void set_floor_num(char);


// DataFlash chip select port pin (PB 2)
#define DF_CHIP_SELECT 0x04

// buffer 1 
#define BUFFER_1 0x00

// buffer 2
#define BUFFER_2 0x01


// defines for all opcodes
//status register
#define Status_reg_Read 0xD7

//Main memory read
#define Main_Mem_Read 0xD2

//Continues Array read 
#define Cont_Array_Read 0xE8

// buffer 1 write 
#define BUFFER_1_WRITE 0x84

// buffer 2 write 
#define BUFFER_2_WRITE 0x87

// buffer 1 read
#define BUFFER_1_READ 0x54

// buffer 2 read
#define BUFFER_2_READ 0x56

// buffer 1 to main memory page program with built-in erase
#define B1_TO_MM_PAGE_PROG_WITH_ERASE 0x83

// buffer 2 to main memory page program with built-in erase
#define B2_TO_MM_PAGE_PROG_WITH_ERASE 0x86

// buffer 1 to main memory page program without built-in erase
#define B1_TO_MM_PAGE_PROG_WITHOUT_ERASE 0x88

// buffer 2 to main memory page program without built-in erase
#define B2_TO_MM_PAGE_PROG_WITHOUT_ERASE 0x89

// main memory page program through buffer 1
#define MM_PAGE_PROG_THROUGH_B1 0x82
 
// main memory page program through buffer 2
#define MM_PAGE_PROG_THROUGH_B2 0x85
 
// auto page rewrite through buffer 1
#define AUTO_PAGE_REWRITE_THROUGH_B1 0x58
 
// auto page rewrite through buffer 2
#define AUTO_PAGE_REWRITE_THROUGH_B2 0x59
 
// main memory page compare to buffer 1
#define MM_PAGE_TO_B1_COMP 0x60

// main memory page compare to buffer 2
#define MM_PAGE_TO_B2_COMP 0x61
 
// main memory page to buffer 1 transfer
#define MM_PAGE_TO_B1_XFER 0x53

// main memory page to buffer 2 transfer
#define MM_PAGE_TO_B2_XFER 0x55

// DataFlash status register for reading density, compare status, 
// and ready/busy status
#define STATUS_REGISTER 0x57

// main memory page read
#define MAIN_MEMORY_PAGE_READ 0x52

// continuous array read (legay array read)
#define CON_ARRAY_READ 0xE8

// erase a 528 byte page
#define PAGE_ERASE 0x81

// erase 512 pages
#define BLOCK_ERASE 0x50

// Page size byte of flash
#define PAGE_SIZE_BYTE 0x01

// change page size byte 1
#define PAGE_SIZE_BYTE1 0x3D

// change page size byte 2
#define PAGE_SIZE_BYTE2 0x2A

// change page size byte 3
#define PAGE_SIZE_BYTE3 0x80

// change page size byte 4
#define PAGE_SIZE_BYTE4 0xA7







#endif