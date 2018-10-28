/*******************************************************************************
********************************************************************************
*@ File:	I2C_ACK_NACK_Generation.c
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:95/12/25	Previous:95/12/25	Created:95/12/25
*@ Author:	M. Aghamohamadian

*@ Brief:	This module is for generating both CRC and ACK/NACK for I2C.

********************************************************************************
*******************************************************************************/
#include "I2C_ACK_NACK_Generation.h"

extern          unsigned char            generated_CRC_bytes[CRC_LENGTH] = {0xF0, 0x0F};
extern          unsigned char            received_CRC_bytes[2] = {0};   

ACK_NACK_Notion I2C_ACK_NACK_Generation(unsigned char *I2C_data_pointer, unsigned char I2C_data_counter, unsigned char I2C_data)
{
  /*
  if (((*I2C_data_pointer) == SERIAL_EMR_INPUT) | ((*I2C_data_pointer) == SERIAL_DOB_INPUT) | ((*I2C_data_pointer) == SERIAL_NO_CTRL_INPUT))    // If the control signal is either one of these, send an ACK regardless.
     return (ACK)
  
  
  return (Secondary_Check(I2C_data));
  */
  
  return(ACK);
}


ACK_NACK_Notion Secondary_Check(unsigned char I2C_data)
{
	switch (I2C_data)    // Note that the commneted cases are repeated in the case.
        {
          // Control signal data
          case (SERIAL_NO_CTRL_INPUT):
              break;

          case (SERIAL_EMR_INPUT):
	      break;
        
          case (SERIAL_TRG_INPUT):
              break;
               
          case (SERIAL_OVL_INPUT):
              break;

          case (SERIAL_DOB_INPUT):
              break;
        
          case (SERIAL_DIRECTION_UP_INPUT):
              break;
        
          case (SERIAL_DIRECTION_DOWN_INPUT):
              break;
        
          // Numerator signal related data (First bytes).
          case (SERIAL_FLOOR01_BYTE0):
              break;
       
          case (SERIAL_FLOOR02_BYTE0):
              break;
       
          case (SERIAL_FLOOR03_BYTE0):
              break;
       
          case (SERIAL_FLOOR04_BYTE0):
              break;
       
          case (SERIAL_FLOOR05_BYTE0):
              break;
       
          case (SERIAL_FLOOR06_BYTE0):
              break;
       
          case (SERIAL_FLOOR07_BYTE0):
              break;
       
          case (SERIAL_FLOOR08_BYTE0):
              break;
       
          case (SERIAL_FLOOR09_BYTE0):
              break;
       
          case (SERIAL_FLOOR10_BYTE0):
              break;

          case (SERIAL_PARK_BYTE0):
              break;    

          case (SERIAL_BASEMENT_BYTE0):
              break;    
       
          case (SERIAL_GROUND_BYTE0): 
              break;             
       
          case (SERIAL_HYPERSTAR_BYTE0): 
              break; 
       
          case (SERIAL_HYPERME_BYTE0): 
              break; 
       
          case (SERIAL_RESTAURANT_BYTE0): 
              break;             
       
          case (SERIAL_LOBBY_BYTE0):
              break; 
       
          case (SERIAL_MANAGEMENT_BYTE0): 
              break;

          case (SERIAL_ARCHIVE_BYTE0): 
              break;             
       
          case (SERIAL_FOODCOURT_BYTE0): 
              break;             

          case (SERIAL_PENTHOUSE_BYTE0): 
              break;             

          case (SERIAL_EUROLOGIST_BYTE0): 
              break;     

           // Numerator signal related data (Second bytes).
          case (SERIAL_FLOOR01_BYTE1):
              break;
       
          case (SERIAL_FLOOR_MINUS_10_BYTE1):
              break;    
             
          case (SERIAL_FOODCOURT_BYTE1): 
              break;             

          default:
              return(NACK);
              break;       
        }
   
      return (ACK);
}

void Generate_CRC_Bytes(unsigned char *I2C_data_pointer, unsigned char I2C_data_length)
{
#if GENERATE_CRC_CHECK == 1
  //// Initialization
  unsigned char         counter;
  unsigned int          crc_register = 0;
  unsigned char         shift_register;
  unsigned char         data_bit;
  unsigned char         crc_bit;

  
  //// Main commands    
  for (counter = 0; counter < I2C_data_length; counter++)
  {
    
    for (shift_register = 0x01; shift_register > 0x00; shift_register <<= 1) 
    {
      
      data_bit = (*(I2C_data_pointer+counter) & shift_register) ? 1 : 0;
      crc_bit = crc_register >> 15;
      crc_register <<= 1;
      if (data_bit != crc_bit)
      {
        crc_register ^= TWOBYTE_CRC_POLYNOMIAL;
      }
    }
  }
   
  
  //// Finalization
  generated_CRC_bytes[1] = (unsigned char) (crc_register & 0x00FF);     // Mask the remaining bytes and return a single byte.
  generated_CRC_bytes[0] = (unsigned char) (crc_register >> 8);      
#endif
}


bool Check_CRC(char CRC_length, unsigned char *I2C_data_pointer, unsigned char I2C_data_length)
{
  // Initialization
  char          vote = 0x00;    // Denotes the number of times received and generated CRC bytes are equal.

#if GENERATE_MR_MODE == 1 || GENERATE_SR_MODE == 1 
  // Main commands
  for (char byte_counter = 0; byte_counter < CRC_length; byte_counter++)        // Compare received CRC with generated CRC.
  {
    if (generated_CRC_bytes[byte_counter] == received_CRC_bytes[byte_counter]);
    {
      vote++;
    }
  }
#endif
  
  // Finalization
  if (vote != CRC_length)       // Vote does not equal the length.
  {
    return (CRC_INVALID);       // CRC was invalid
  }
  else
  {    
    return (CRC_VALID);
  }

}