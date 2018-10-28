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

ACK_NACK_Notion I2C_ACK_NACK_Generation(unsigned char I2C_data)
{
   // Initialization
   ACK_NACK_Notion       Acknowledged_value;      // Denotes the acknowledgement state after receiving signal 
                                                  // through the I2C protocol.

  
   // Main commands
   switch (I2C_data)    // Note that the commneted cases are repeated in the case.
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
        
        // Numerator signal related data (First bytes).
        case (SERIAL_FLOOR01_BYTE0):
          Acknowledged_value = ACK;
          break;
       
        case (SERIAL_FLOOR02_BYTE0):
          Acknowledged_value = ACK;
          break;
       
        case (SERIAL_FLOOR03_BYTE0):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR04_BYTE0):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR05_BYTE0):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR06_BYTE0):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR07_BYTE0):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR08_BYTE0):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR09_BYTE0):
          Acknowledged_value = ACK;
          break;
       
       case (SERIAL_FLOOR10_BYTE0):
          Acknowledged_value = ACK;
          break;
       
//       case (SERIAL_FLOOR11_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR12_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR13_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR14_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR15_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR16_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR17_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR18_BYTE0):
//         Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR19_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR20_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR21_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR22_BYTE0):
//         Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR23_BYTE0):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR24_BYTE0):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR25_BYTE0):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR26_BYTE0):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR27_BYTE0):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR28_BYTE0):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR29_BYTE0):
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_FLOOR30_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR31_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR32_BYTE0):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR33_BYTE0):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR34_BYTE0):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR35_BYTE0):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR36_BYTE0):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR37_BYTE0):
//         Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR38_BYTE0):
//         Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR39_BYTE0):
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_FLOOR40_BYTE0):
//          Acknowledged_value = ACK;
//          break; 
       
//      case (SERIAL_PARK_09_BYTE0):
//          Acknowledged_value = ACK;
//          break;  
       
//       case (SERIAL_PARK_08_BYTE0):
//          Acknowledged_value = ACK;
//          break;   
       
//       case (SERIAL_PARK_07_BYTE0):
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_PARK_06_BYTE0):
//          Acknowledged_value = ACK;
//          break;     
       
//       case (SERIAL_PARK_05_BYTE0):
//          Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_PARK_04_BYTE0):
//          Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_PARK_03_BYTE0):
//          Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_PARK_02_BYTE0):
//          Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_PARK_01_BYTE0):
//          Acknowledged_value = ACK;
//          break;    
       
       case (SERIAL_PARK_BYTE0):
          Acknowledged_value = ACK;
          break;    
       
//       case (SERIAL_BASEMENT_09_BYTE0):
//          Acknowledged_value = ACK;
//          break;  
       
//       case (SERIAL_BASEMENT_08_BYTE0):
//         Acknowledged_value = ACK;
//          break;   
       
//       case (SERIAL_BASEMENT_07_BYTE0):
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_BASEMENT_06_BYTE0):
//          Acknowledged_value = ACK;
//          break;     
       
//       case (SERIAL_BASEMENT_05_BYTE0):
//          Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_BASEMENT_04_BYTE0):
//          Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_BASEMENT_03_BYTE0):
//          Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_BASEMENT_02_BYTE0):
//          Acknowledged_value = ACK;
//          break;    
       
//      case (SERIAL_BASEMENT_01_BYTE0):
//          Acknowledged_value = ACK;
//          break;    
       
       case (SERIAL_BASEMENT_BYTE0):
          Acknowledged_value = ACK;
          break;    
       
//       case (SERIAL_FLOOR_MINUS_10_BYTE0):
//          Acknowledged_value = ACK;
//         break;    
       
//       case (SERIAL_FLOOR_MINUS_09_BYTE0):
//          Acknowledged_value = ACK;
//          break;    

//       case (SERIAL_FLOOR_MINUS_08_BYTE0):
//          Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_FLOOR_MINUS_07_BYTE0):
//          Acknowledged_value = ACK;
//          break;    

//       case (SERIAL_FLOOR_MINUS_06_BYTE0):
//          Acknowledged_value = ACK;
//          break;    

//       case (SERIAL_FLOOR_MINUS_05_BYTE0):
//          Acknowledged_value = ACK;
//          break;    

//       case (SERIAL_FLOOR_MINUS_04_BYTE0):
//          Acknowledged_value = ACK;
//          break;    

//       case (SERIAL_FLOOR_MINUS_03_BYTE0):
//         Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_FLOOR_MINUS_02_BYTE0):
//         Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_FLOOR_MINUS_01_BYTE0):
//          Acknowledged_value = ACK;
//          break;    
       
       case (SERIAL_GROUND_BYTE0): 
          Acknowledged_value = ACK;
          break;             
       
       case (SERIAL_HYPERSTAR_BYTE0): 
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_HYPERME_BYTE0): 
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_RESTAURANT_BYTE0): 
          Acknowledged_value = ACK;
          break;             
       
        case (SERIAL_LOBBY_BYTE0):
          Acknowledged_value = ACK;
          break; 
       
       case (SERIAL_MANAGEMENT_BYTE0): 
          Acknowledged_value = ACK;
          break;

       case (SERIAL_ARCHIVE_BYTE0): 
          Acknowledged_value = ACK;
          break;             

//       case (SERIAL_ROOFGARDEN_BYTE0): 
//          Acknowledged_value = ACK;
//          break;             
       
       case (SERIAL_FOODCOURT_BYTE0): 
          Acknowledged_value = ACK;
          break;             

//       case (SERIAL_PLAYGROUND_BYTE0): 
//          Acknowledged_value = ACK;
//          break;             
       
       case (SERIAL_PENTHOUSE_BYTE0): 
          Acknowledged_value = ACK;
          break;             
       
//       case (SERIAL_POOL_BYTE0): 
//         Acknowledged_value = ACK;
//          break;          

//       case (SERIAL_ROOFTOP_BYTE0): 
//          Acknowledged_value = ACK;
//          break;        
       
//       case (SERIAL_PEDIATRICIAN_BYTE0): 
//          Acknowledged_value = ACK;
//          break;        

       case (SERIAL_EUROLOGIST_BYTE0): 
          Acknowledged_value = ACK;
          break;     
       
//       case (SERIAL_GYNECOLOGIST_BYTE0): 
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_DENTIST_BYTE0): 
//          Acknowledged_value = ACK;
//          break;        
       
//       case (SERIAL_PROJECT_ONE_BYTE0): 
//          Acknowledged_value = ACK;
//          break;        

//       case (SERIAL_EXITWAY_BYTE0): 
//          Acknowledged_value = ACK;
//          break;          

        // Numerator signal related data (Second bytes).
        case (SERIAL_FLOOR01_BYTE1):
          Acknowledged_value = ACK;
          break;
       
//        case (SERIAL_FLOOR02_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//        case (SERIAL_FLOOR03_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR04_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//      case (SERIAL_FLOOR05_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR06_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR07_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR08_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR09_BYTE1):
//          Acknowledged_value = ACK;
///          break;
       
//       case (SERIAL_FLOOR10_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR11_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR12_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR13_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR14_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR15_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR16_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR17_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR18_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR19_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR20_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR21_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR22_BYTE1):
//         Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR23_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR24_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR25_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR26_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR27_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR28_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR29_BYTE1):
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_FLOOR30_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR31_BYTE1):
///          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR32_BYTE1):
//          Acknowledged_value = ACK;
//          break;
       
//       case (SERIAL_FLOOR33_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR34_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR35_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR36_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR37_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR38_BYTE1):
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_FLOOR39_BYTE1):
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_FLOOR40_BYTE1):
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_PARK_09_BYTE1):
//          Acknowledged_value = ACK;
//          break;  
       
//       case (SERIAL_PARK_08_BYTE1):
//          Acknowledged_value = ACK;
//          break;   
       
//       case (SERIAL_PARK_07_BYTE1):
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_PARK_06_BYTE1):
//          Acknowledged_value = ACK;
//          break;     
       
//       case (SERIAL_PARK_05_BYTE1):
//          Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_PARK_04_BYTE1):
//          Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_PARK_03_BYTE1):
//          Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_PARK_02_BYTE1):
//          Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_PARK_01_BYTE1):
//          Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_PARK_BYTE1):
//          Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_BASEMENT_09_BYTE1):
//          Acknowledged_value = ACK;
//          break;  
       
//       case (SERIAL_BASEMENT_08_BYTE1):
//          Acknowledged_value = ACK;
//          break;   
       
//       case (SERIAL_BASEMENT_07_BYTE1):
//          Acknowledged_value = ACK;
//          break; 
       
//      case (SERIAL_BASEMENT_06_BYTE1):
//          Acknowledged_value = ACK;
//          break;     
       
//       case (SERIAL_BASEMENT_05_BYTE1):
//          Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_BASEMENT_04_BYTE1):
//          Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_BASEMENT_03_BYTE1):
//         Acknowledged_value = ACK;
//          break;      
       
//       case (SERIAL_BASEMENT_02_BYTE1):
//          Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_BASEMENT_01_BYTE1):
//          Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_BASEMENT_BYTE1):
//          Acknowledged_value = ACK;
//          break;    
       
       case (SERIAL_FLOOR_MINUS_10_BYTE1):
          Acknowledged_value = ACK;
          break;    
       
//       case (SERIAL_FLOOR_MINUS_09_BYTE1):
//          Acknowledged_value = ACK;
//          break;    

//       case (SERIAL_FLOOR_MINUS_08_BYTE1):
//          Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_FLOOR_MINUS_07_BYTE1):
//          Acknowledged_value = ACK;
//         break;    

//       case (SERIAL_FLOOR_MINUS_06_BYTE1):
//          Acknowledged_value = ACK;
//          break;    

//       case (SERIAL_FLOOR_MINUS_05_BYTE1):
//          Acknowledged_value = ACK;
//          break;    

//       case (SERIAL_FLOOR_MINUS_04_BYTE1):
//          Acknowledged_value = ACK;
//          break;    

//       case (SERIAL_FLOOR_MINUS_03_BYTE1):
//          Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_FLOOR_MINUS_02_BYTE1):
//          Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_FLOOR_MINUS_01_BYTE1):
//          Acknowledged_value = ACK;
//          break;    
       
//       case (SERIAL_GROUND_BYTE1): 
//          Acknowledged_value = ACK;
//          break;             
       
//       case (SERIAL_HYPERSTAR_BYTE1): 
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_HYPERME_BYTE1): 
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_RESTAURANT_BYTE1): 
//          Acknowledged_value = ACK;
//          break;             
       
//        case (SERIAL_LOBBY_BYTE1):
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_MANAGEMENT_BYTE1): 
//          Acknowledged_value = ACK;
//          break;

//       case (SERIAL_ARCHIVE_BYTE1): 
//          Acknowledged_value = ACK;
//          break;             

//       case (SERIAL_ROOFGARDEN_BYTE1): 
//          Acknowledged_value = ACK;
//          break;             
       
       case (SERIAL_FOODCOURT_BYTE1): 
          Acknowledged_value = ACK;
          break;             

//       case (SERIAL_PLAYGROUND_BYTE1): 
//          Acknowledged_value = ACK;
//          break;             
       
//       case (SERIAL_PENTHOUSE_BYTE1): 
//          Acknowledged_value = ACK;
//          break;             
       
//       case (SERIAL_POOL_BYTE1): 
//          Acknowledged_value = ACK;
//          break;          

//       case (SERIAL_ROOFTOP_BYTE1): 
//          Acknowledged_value = ACK;
//          break;        
       
//       case (SERIAL_PEDIATRICIAN_BYTE1): 
//          Acknowledged_value = ACK;
//          break;        

//       case (SERIAL_EUROLOGIST_BYTE1): 
//          Acknowledged_value = ACK;
//          break;     
       
//       case (SERIAL_GYNECOLOGIST_BYTE1): 
//          Acknowledged_value = ACK;
//          break; 
       
//       case (SERIAL_DENTIST_BYTE1): 
//          Acknowledged_value = ACK;
//          break;        
       
//       case (SERIAL_PROJECT_ONE_BYTE1): 
//          Acknowledged_value = ACK;
//          break;        

//       case (SERIAL_EXITWAY_BYTE1): 
//          Acknowledged_value = ACK;
//          break;          
          
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