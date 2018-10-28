#include "General.h"
#include <inavr.h>
#include <ioavr.h>
#include "EEPROM_Secure_Read.h"


struct EEPROMRead EEPROM_Secure_Read(unsigned int EEPROM_Byte_Address)
{
     // Initialization   
     unsigned char       EEPROM_read_counter = 0;         // Keeps the number of times data is read from EEPROM.
     unsigned char       EEPROM_first_read;           // The primary read from EEPROM.
     unsigned char       EEPROM_second_read;          // The secondary read from EEPROM.
     struct              EEPROMRead      EEPROM_Read;
       
     
     // Main commands  
     EEPROM_first_read = charEEPROM_read(EEPROM_Byte_Address);  // First read from EEPROM
     EEPROM_second_read = charEEPROM_read(EEPROM_Byte_Address); // Second read from EEPROM
     
     
     while (EEPROM_first_read != EEPROM_second_read && EEPROM_read_counter < EEPROM_REPEAT_READ)  // While the two consecutives reads of EEPROM are unequal, 
                                                                                                  // repeat reading.
     {
       EEPROM_first_read = EEPROM_second_read;
       EEPROM_read_counter++;
       EEPROM_second_read = charEEPROM_read(EEPROM_Byte_Address);
     }   
     
     if (EEPROM_read_counter >= EEPROM_REPEAT_READ)     // If the number of reads have exceeded from the permitted value,
     {  
       EEPROM_Read.flag = CURROPTED_DATA;       // Data is corrupted.
     }
     else
     {
       EEPROM_Read.flag = TRUSTED_DATA;
     }

     // Finalization
     EEPROM_Read.data = EEPROM_second_read;     // Save the last data read from EEPROM.
     return (EEPROM_Read);
}

unsigned charEEPROM_read(unsigned int EEPROM_Byte_Address)
{
     while (EECR & (1<<EEWE));   // Wait for completion of previous write
     EEAR = EEPROM_Byte_Address;       // Set up address register
     EECR |= (1<<EERE);      // Start eeprom read by writing EERE
     return EEDR;       // Return data from data register 
}

