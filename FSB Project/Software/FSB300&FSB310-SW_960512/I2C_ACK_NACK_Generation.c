#include "I2C_ACK_NACK_Generation.h"
#include "IO_Module.h"

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
        
        // Stop data
        case (SERIAL_STOP001):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP002):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP003):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP004):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP005):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP006):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP007):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP008):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP009):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP010):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP011):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP012):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP013):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP014):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP015):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP016):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP017):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP018):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP019):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP020):
          Acknowledged_value = ACK;
        break;
        case (SERIAL_STOP021):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP022):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP023):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP024):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP025):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP026):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP027):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP028):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP029):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP030):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP031):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP032):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP033):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP034):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP035):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP036):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP037):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP038):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP039):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP040):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP041):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP042):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP043):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP044):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP045):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP046):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP047):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP048):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP049):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP050):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP051):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP052):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP053):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP054):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP055):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP056):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP057):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP058):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP059):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP060):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP061):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP062):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP063):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP064):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP065):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP066):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP067):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP068):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP069):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP070):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP071):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP072):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP073):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP074):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP075):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP076):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP077):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP078):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP079):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP080):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP081):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP082):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP083):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP084):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP085):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP086):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP087):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP088):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP089):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP090):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP091):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP092):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP093):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP094):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP095):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP096):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP097):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP098):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP099):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP100):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP101):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP102):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP103):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP104):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP105):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP106):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP107):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP108):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP109):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP110):
          Acknowledged_value = ACK;
        break;
              
        case (SERIAL_STOP111):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP112):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP113):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP114):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP115):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP116):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP117):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP118):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP119):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP120):
          Acknowledged_value = ACK;
        break;
        
        case (SERIAL_STOP121):
          Acknowledged_value = ACK;
        break;

        case (SERIAL_STOP122):
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
       
       case (SERIAL_PARK_00):
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
       
       case (SERIAL_BASEMENT_00):
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

       case (SERIAL_ROOF_GARDEN): 
          Acknowledged_value = ACK;
       break;             
       
       case (SERIAL_FOOD_COURT): 
          Acknowledged_value = ACK;
       break;             

       case (SERIAL_PLAY_GROUND): 
          Acknowledged_value = ACK;
       break;             
       
       case (SERIAL_PENT_HOUSE): 
          Acknowledged_value = ACK;
       break;             
       
       case (SERIAL_POOL): 
          Acknowledged_value = ACK;
       break;             

       default:
          Acknowledged_value = NACK;
       break;        
   }
  
  
   // Finalization
   return (Acknowledged_value);
}