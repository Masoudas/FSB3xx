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
#include "IO_Module.h"

extern          unsigned char            generated_CRC_bytes[CRC_LENGTH] = {0xF0, 0x0F};
extern          unsigned char            received_CRC_bytes[2] = {0};   

ACK_NACK_Notion I2C_ACK_NACK_Generation(unsigned char I2C_data)
{
   // Initialization
   ACK_NACK_Notion       Acknowledged_value;      // Denotes the acknowledgement state after receiving signal 
                                                  // through the I2C protocol.

  
   // Main commands
   switch (I2C_data)
   {
        // Control signal data
        case (SERIAL_NO_CTRL_INPUT):
          Acknowledged_value = ACK;
          break;

        case (SERIAL_EMR_INPUT):
          Acknowledged_value = ACK;
          break;
        
        case (SERIAL_TRG_INPUT):
          Acknowledged_value = ACK;
          break;
               
        case (SERIAL_OVL_INPUT):
          Acknowledged_value = ACK;
          break;

        case (SERIAL_DOB_INPUT):
          Acknowledged_value = ACK;
          break;
        
        case (SERIAL_DIRECTION_UP_INPUT):
          Acknowledged_value = ACK;
          break;
        
        case (SERIAL_DIRECTION_DOWN_INPUT):
          Acknowledged_value = ACK;
          break;
        
        // Numerator signal related data.
        case (SERIAL_FLOOR01):
          Acknowledged_value = ACK;
          break;
       
        case (SERIAL_FLOOR02):
          Acknowledged_value = ACK;
          break;
       
        case (SERIAL_FLOOR03):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR04):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR05):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR06):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR07):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR08):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR09):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR10):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR11):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR12):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR13):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR14):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR15):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR16):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR17):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR18):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR19):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR20):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR21):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR22):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR23):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR24):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR25):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR26):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR27):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR28):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR29):
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_FLOOR30):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR31):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR32):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR33):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR34):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR35):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR36):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR37):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR38):
          Acknowledged_value = ACK;
          break;

       case (SERIAL_FLOOR39):
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_FLOOR40):
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_PARK_09):
          Acknowledged_value = ACK;
          break;  
       
       case (SERIAL_PARK_08):
          Acknowledged_value = ACK;
          break;   
       
       case (SERIAL_PARK_07):
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_PARK_06):
          Acknowledged_value = ACK;
          break;     
       
       case (SERIAL_PARK_05):
          Acknowledged_value = ACK;
          break;      
       
       case (SERIAL_PARK_04):
          Acknowledged_value = ACK;
          break;      
       
       case (SERIAL_PARK_03):
          Acknowledged_value = ACK;
          break;      
       
       case (SERIAL_PARK_02):
          Acknowledged_value = ACK;
          break;    
       
       case (SERIAL_PARK_01):
          Acknowledged_value = ACK;
          break;    
       
       case (SERIAL_PARK):
          Acknowledged_value = ACK;
          break;    
       
       case (SERIAL_BASEMENT_09):
          Acknowledged_value = ACK;
          break;  
       
       case (SERIAL_BASEMENT_08):
          Acknowledged_value = ACK;
          break;   
       
       case (SERIAL_BASEMENT_07):
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_BASEMENT_06):
          Acknowledged_value = ACK;
          break;     
       
       case (SERIAL_BASEMENT_05):
          Acknowledged_value = ACK;
          break;      
       
       case (SERIAL_BASEMENT_04):
          Acknowledged_value = ACK;
          break;      
       
       case (SERIAL_BASEMENT_03):
          Acknowledged_value = ACK;
          break;      
       
       case (SERIAL_BASEMENT_02):
          Acknowledged_value = ACK;
          break;    
       
       case (SERIAL_BASEMENT_01):
          Acknowledged_value = ACK;
          break;    
       
       case (SERIAL_BASEMENT):
          Acknowledged_value = ACK;
          break;    
       
       case (SERIAL_FLOOR_MINUS_10):
          Acknowledged_value = ACK;
          break;    
       
       case (SERIAL_FLOOR_MINUS_09):
          Acknowledged_value = ACK;
          break;    

       case (SERIAL_FLOOR_MINUS_08):
          Acknowledged_value = ACK;
          break;    
       
       case (SERIAL_FLOOR_MINUS_07):
          Acknowledged_value = ACK;
          break;    

       case (SERIAL_FLOOR_MINUS_06):
          Acknowledged_value = ACK;
          break;    

       case (SERIAL_FLOOR_MINUS_05):
          Acknowledged_value = ACK;
          break;    

       case (SERIAL_FLOOR_MINUS_04):
          Acknowledged_value = ACK;
          break;    

       case (SERIAL_FLOOR_MINUS_03):
          Acknowledged_value = ACK;
          break;    
       
       case (SERIAL_FLOOR_MINUS_02):
          Acknowledged_value = ACK;
          break;    
       
       case (SERIAL_FLOOR_MINUS_01):
          Acknowledged_value = ACK;
          break;    
       
       case (SERIAL_GROUND): 
          Acknowledged_value = ACK;
          break;             
       
       case (SERIAL_HYPERSTAR): 
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_HYPERME): 
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_RESTAURANT): 
          Acknowledged_value = ACK;
          break;             
       
        case (SERIAL_LOBBY):
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_MANAGEMENT): 
          Acknowledged_value = ACK;
          break;

       case (SERIAL_ARCHIVE): 
          Acknowledged_value = ACK;
          break;             

       case (SERIAL_ROOFGARDEN): 
          Acknowledged_value = ACK;
          break;             
       
       case (SERIAL_FOODCOURT): 
          Acknowledged_value = ACK;
          break;             

       case (SERIAL_PLAYGROUND): 
          Acknowledged_value = ACK;
          break;             
       
       case (SERIAL_PENTHOUSE): 
          Acknowledged_value = ACK;
          break;             
       
       case (SERIAL_POOL): 
          Acknowledged_value = ACK;
          break;          

       case (SERIAL_ROOFTOP): 
          Acknowledged_value = ACK;
          break;        
       
       case (SERIAL_PEDIATRICIAN): 
          Acknowledged_value = ACK;
          break;        

       case (SERIAL_EUROLOGIST): 
          Acknowledged_value = ACK;
          break;     
       
       case (SERIAL_GYNECOLOGIST): 
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_DENTIST): 
          Acknowledged_value = ACK;
          break;        
       
       case (SERIAL_PROJECT_ONE): 
          Acknowledged_value = ACK;
          break;        

       case (SERIAL_EXITWAY): 
          Acknowledged_value = ACK;
          break;          

       default:
          Acknowledged_value = NACK;
       break;        
   }
  
  
   // Finalization
   return (Acknowledged_value);
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