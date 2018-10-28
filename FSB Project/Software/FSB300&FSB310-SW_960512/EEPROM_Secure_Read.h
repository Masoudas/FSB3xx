/*******************************************************************************
********************************************************************************
*@ File:	EEPROM_Secure_read.c
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:96/01/14	Previous:96/01/14	Created:96/01/14
*@ Author:	M.Aghamohamadian 

*@ Brief:	This header is used for reading data securely (or repeatedly for confirmation) from EEPROM.

********************************************************************************
*******************************************************************************/
/*----- Include Files --------------------------------------------------------*/

#ifndef EEPROM_SECURE_READ_h
#define EEPROM_SECURE_READ_h


/*----- CONSTANT DEFINITIONS -------------------------------------------------*/
// EEPROM read related constants
#define             CURROPTED_DATA           0x01    // Means the data read from EEPROM is curropted.
#define             TRUSTED_DATA             0x00    // Means the data read from EEPROM is trusted.
#define             EEWE                     0x01    // The EEWE bit of EEPROM control register.
#define             EERE                     0x00    // The EERE bit of EEPROM control register.

// Number of read trials
#define             EEPROM_REPEAT_READ       10      // Denotes the number of times a parameter is read from EEPROM for verification.

/*------ Variable Definition -------------------------------------------------*/
// Read from EEPROM structure
struct EEPROMRead{
       unsigned char     flag;      // Denotes whether the data read from EEPROM is "CORRUPTED" or "TRUSTED".
       unsigned char     data;      // Data read from EEPROM.
       };


/*------ Function Definition -------------------------------------------------*/
struct EEPROMRead EEPROM_Secure_Read(unsigned int EEPROM_byte_address);
/*
Input: 
          EEPROM_BYTE_ADDRESS: The byte to be read from EEPROM

Output: 
          The data structure for read from EEPROM.

Description:
         This function help secure reading from EEPROM in the sense that it 
         repeats reading from this memory untill to reads are equal.
*/

unsigned charEEPROM_read(unsigned int uiAddress);
/*
Input: 
          uiAddress: The address of the character to be read from EEPROM

Output: 
          The data read from EEPROM.

Description:
         This function reads a data from EEPROM.
*/

#endif