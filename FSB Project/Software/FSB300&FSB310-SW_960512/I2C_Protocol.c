#include "I2C_Protocol.h"
#include "I2C_ACK_NACK_Generation.h"
#include <inavr.h>
#include <ioavr.h>

extern      unsigned char           I2C_Status = I2C_READY;
extern      unsigned char           I2C_state_timer = 0;         
extern      unsigned int            I2C_data_counter = 0;
extern      unsigned int            previous_system_time = 0;

bool I2C_Protocol(unsigned char *I2C_data_pointer, unsigned int I2C_data_length, unsigned char I2C_initiation_mode, unsigned char I2C_slave_address, unsigned char I2C_bitrate, unsigned char I2C_frequency_prescalar, unsigned int current_system_time)
{
     //// Initialization
     ACK_NACK_Notion       Acknowledge_value = ACK;     // Denotes whether ack or nack has been produced for the current data in I2C data register.
     bool                  I2C_finished_flag = I2C_PROTOCOL_BUSY; // Denotes that whether or not I2C has finished sending/receiving data.
     
     // Desginating an address in the slave mode   
     I2C_ADDRESS_REGISTER = I2C_slave_address << 1;      // The seven bits of slave address are filled with the slave number 
                                                         // LSB of I2c_ADDRESS_REGISTER is saved for general call.
     
      // Setting the I2C timer based on the system time
     if (current_system_time != previous_system_time)
     {
       I2C_state_timer++;
       previous_system_time = current_system_time;
     }
      
     
     //// Main Commands
     switch (I2C_Status)    // Set I2C status based on the registers
     {     
       // Common cases for all modes
       case (I2C_READY):        // Initiation case
          I2C_state_timer = 0;
          if (I2C_initiation_mode == I2C_MT_MODE)
          {
            I2C_Status = I2C_BUSY;
            I2C_data_counter = 0;
            I2C_BITRATE_REGISTER = I2C_bitrate;
            I2C_STATUS_REGISTER |= I2C_frequency_prescalar;
            I2C_CONTROL_REGISTER = I2C_START_SIGNAL;
          }
          else if (I2C_initiation_mode == I2C_MR_MODE)
          {
            I2C_Status = I2C_BUSY;
            I2C_data_counter = 0;
            I2C_BITRATE_REGISTER = I2C_bitrate;
            I2C_STATUS_REGISTER |= I2C_frequency_prescalar;
            I2C_CONTROL_REGISTER = I2C_START_SIGNAL;
          }
          else if (I2C_initiation_mode == I2C_SR_MODE)
          {
            I2C_Status = I2C_BUSY;
            I2C_data_counter = 0;
            I2C_CONTROL_REGISTER = I2C_SLAVE_MODE_ENABLE_SIGNAL;
          }
          else if (I2C_initiation_mode == I2C_ST_MODE)
          {
            I2C_Status = I2C_BUSY;
            I2C_data_counter = 0;
            I2C_CONTROL_REGISTER = I2C_SLAVE_MODE_ENABLE_SIGNAL; 
          }
          else
          {
            I2C_Status = I2C_READY;                
          }
       break;       
       
       case (I2C_BUSY):
         I2C_state_timer++;
         if ((I2C_CONTROL_REGISTER & (1 << TWINT)) == (0 << TWINT))     // If TWI has not changed
         {
           if (I2C_state_timer > I2C_MAX_BUSY_TIME)
           {
             I2C_state_timer = 0;
             I2C_ERROR();
           }
           else
           {
             I2C_Status = I2C_BUSY;
             I2C_state_timer++;
           }
         }
         else
         {
           I2C_Status = I2C_STATUS_REGISTER & I2C_STATUS_REGISTER_PRESCALAR_MASK;
           I2C_state_timer = 0;
         }
       break;
       
       default:        // Facing an unknown state        
         I2C_state_timer = 0;
         I2C_Status = I2C_READY;
         I2C_CONTROL_REGISTER = I2C_DISABLE_SIGNAL;     // If an unknown state happens, temporarily diable the protocol.
       break;
       
       // Common cases for master modes
       case (I2C_START):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         if (I2C_initiation_mode == I2C_MT_MODE)
         {     
            I2C_DATA_REGISTER = (I2C_slave_address << 1) + I2C_WRITE_TO_SLAVE;  // Slave would be in SR mode
         }
         else if (I2C_initiation_mode == I2C_MR_MODE)
         {
            I2C_DATA_REGISTER = (I2C_slave_address << 1) + I2C_READ_FROM_SLAVE; // Slave would be in ST mode
         }

         I2C_CONTROL_REGISTER = I2C_TRANSMIT_ADDRESS_SIGNAL;           
       break;
    
       case (I2C_REPEATED_START):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         if (I2C_initiation_mode == I2C_MT_MODE)
         {     
            I2C_DATA_REGISTER = (I2C_slave_address << 1) + I2C_WRITE_TO_SLAVE;  // Slave would be in SR mode
         }
         else if (I2C_initiation_mode == I2C_MR_MODE)
         {
            I2C_DATA_REGISTER = (I2C_slave_address << 1) + I2C_READ_FROM_SLAVE; // Slave would be in ST mode
         }

         I2C_CONTROL_REGISTER = I2C_TRANSMIT_ADDRESS_SIGNAL;           
       break;

       
       // Cases related to MT mode         
       case (I2C_MT_ADDRESS_ACK):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         I2C_DATA_REGISTER = *I2C_data_pointer;  // The first byte of the data vector is sent out here.
         I2C_CONTROL_REGISTER = I2C_MT_TRANSMIT_DATA_SIGNAL;
       break;

       case (I2C_MT_ADDRESS_NACK):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         I2C_CONTROL_REGISTER = I2C_REPEATED_START_SIGNAL;
       break;
       
       case (I2C_MT_DATA_ACK):
         I2C_state_timer = 0;
         I2C_data_counter++;
         I2C_data_pointer += I2C_data_counter;
         if (I2C_data_counter < I2C_data_length)
         {
           I2C_Status = I2C_BUSY;
           I2C_DATA_REGISTER = *I2C_data_pointer; 
           I2C_CONTROL_REGISTER = I2C_MT_TRANSMIT_DATA_SIGNAL;
         }
         else if (I2C_data_counter >= I2C_data_length)
         {
           I2C_Status = I2C_READY;
           I2C_finished_flag = I2C_PROTOCOL_FINISHED;
           I2C_CONTROL_REGISTER = I2C_STOP_SIGNAL;
         }
       break;
       
       case (I2C_MT_DATA_NACK):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         I2C_CONTROL_REGISTER = I2C_REPEATED_START_SIGNAL;
       break;


     // Cases related to MR mode             
       case (I2C_MR_ADDRESS_ACK):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         I2C_CONTROL_REGISTER = I2C_MR_RECEIVE_DATA_SENDACK_SIGNAL;
       break;
       
       case (I2C_MR_ADDRESS_NACK):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         I2C_CONTROL_REGISTER = I2C_REPEATED_START_SIGNAL;
       break;
       
       case (I2C_MR_DATA_RECEIVE_ACK):   // An ack is sent in the previous state and now a data is received (again)
         I2C_state_timer = 0;
         Acknowledge_value = I2C_ACK_NACK_Generation(I2C_DATA_REGISTER);         
         if ((Acknowledge_value == ACK) && (I2C_data_counter < (I2C_data_length-1)))
         {        
           I2C_data_pointer += I2C_data_counter;           
           *I2C_data_pointer = I2C_DATA_REGISTER;
           I2C_data_counter++; 
           I2C_Status = I2C_BUSY; 
           I2C_CONTROL_REGISTER = I2C_MR_RECEIVE_DATA_SENDACK_SIGNAL;                     
         }
         else if ((Acknowledge_value == ACK) && (I2C_data_counter >= (I2C_data_length-1)))
         {
           I2C_data_pointer += I2C_data_counter;           
           *I2C_data_pointer = I2C_DATA_REGISTER;
           I2C_Status = I2C_READY;          
           I2C_finished_flag = I2C_PROTOCOL_FINISHED;
           I2C_CONTROL_REGISTER = I2C_STOP_SIGNAL;
         }  
         else if (Acknowledge_value == NACK)
         {
           I2C_Status = I2C_BUSY;
           I2C_CONTROL_REGISTER = I2C_SL_RECEIVE_DATA_SENDNACK_SIGNAL;
         }
       break;
       
       case (I2C_MR_DATA_RECEIVE_NACK):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         I2C_CONTROL_REGISTER = I2C_REPEATED_START_SIGNAL;
       break;
       

       // Cases related to SR mode 
       case (I2C_SR_START):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         I2C_CONTROL_REGISTER = I2C_SL_RECEIVE_DATA_SENDACK_SIGNAL;
       break;
       
       case (I2C_SR_DATA_ACK):
         I2C_state_timer = 0;
         Acknowledge_value = I2C_ACK_NACK_Generation(I2C_DATA_REGISTER);  
         if ((Acknowledge_value == ACK) && (I2C_data_counter < (I2C_data_length-1)))
         {        
           I2C_data_pointer += I2C_data_counter;           
           *I2C_data_pointer = I2C_DATA_REGISTER;
           I2C_data_counter++; 
           I2C_Status = I2C_BUSY; 
           I2C_CONTROL_REGISTER = I2C_SL_RECEIVE_DATA_SENDACK_SIGNAL; 
         }
         else if ((Acknowledge_value == ACK) && (I2C_data_counter >= (I2C_data_length-1)))
         {
           I2C_data_pointer += I2C_data_counter;           
           *I2C_data_pointer = I2C_DATA_REGISTER;
           I2C_Status = I2C_READY;          
           I2C_finished_flag = I2C_PROTOCOL_FINISHED;
           I2C_CONTROL_REGISTER = I2C_SLAVE_MODE_DISABLE_SIGNAL;
         }  
         else if (Acknowledge_value == NACK)
         {
           I2C_Status = I2C_BUSY;
           I2C_CONTROL_REGISTER = I2C_SL_RECEIVE_DATA_SENDNACK_SIGNAL;
         }
       break;
       
       case (I2C_SR_DATA_NACK):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         I2C_CONTROL_REGISTER = I2C_SLAVE_MODE_ENABLE_SIGNAL;
       break;
       
       
       // Cases related to ST mode 
       case (I2C_ST_START):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         I2C_DATA_REGISTER = *I2C_data_pointer;  // The first byte of the data vector is sent out here.
         if (I2C_data_counter >= (I2C_data_length-1))   // If this is also the last byte to be sent out
         {
           I2C_CONTROL_REGISTER = I2C_ST_TRANSMIT_DATA_SENDNACK_SIGNAL; // set TWEN = 0, discontinue the ST mode 
         }
         else   // This is not the last byte to be sent out
         {
           I2C_CONTROL_REGISTER = I2C_ST_TRANSMIT_DATA_SENDACK_SIGNAL;  // set TWEN = 1, allow the continuation of the ST mode.
         }
       break;
       
       case (I2C_ST_DATA_ACK):
         I2C_state_timer = 0;
         I2C_data_counter++; 
         I2C_data_pointer += I2C_data_counter;           
         I2C_DATA_REGISTER = *I2C_data_pointer;
         I2C_Status = I2C_BUSY;
         if (I2C_data_counter >= (I2C_data_length-1))   // If this is also the last byte to be sent out
         {
           I2C_CONTROL_REGISTER = I2C_ST_TRANSMIT_DATA_SENDNACK_SIGNAL; // set TWEN = 0, discontinue the ST mode 
         }
         else   // This is not the last byte to be sent out
         {
           I2C_CONTROL_REGISTER = I2C_ST_TRANSMIT_DATA_SENDACK_SIGNAL;  // set TWEN = 1, allow the continuation of the ST mode.
         }
       break;
             
       case (I2C_ST_DATA_NACK):
         I2C_state_timer = 0;
         I2C_Status = I2C_BUSY;
         I2C_CONTROL_REGISTER = I2C_SLAVE_MODE_ENABLE_SIGNAL;
       break;
       
       case (I2C_ST_STOP):
         I2C_state_timer = 0;
         I2C_Status = I2C_READY;
         I2C_finished_flag = I2C_PROTOCOL_FINISHED;
         I2C_CONTROL_REGISTER = I2C_SLAVE_MODE_DISABLE_SIGNAL;
       break;    
     }
    
     // Finalization
     return (I2C_finished_flag);     
}


void I2C_ERROR(void)
{
  I2C_Status = I2C_READY;
  I2C_CONTROL_REGISTER = I2C_DISABLE_SIGNAL;
}


