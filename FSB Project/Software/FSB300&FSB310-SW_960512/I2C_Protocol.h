/* This header defines the function that is used for reading from AT45DB312D */
/*******************************************************************************
********************************************************************************
*@ File:	ReadDataFlash.c
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:95/09/18	Previous:95/09/09	Created:95/09/09
*@ Author:	M. Aghamohamadian

*@ Brief:	This header is used for defining the general parameters of I2C protocol.
Note:           MT: Master Tranmission mode
                MR: Master Receive mode
                ST: Slave Transmission mode
                SR: Slave Receive mode

********************************************************************************
*******************************************************************************/
/*----- Include Files --------------------------------------------------------*/
#ifndef I2C_PROTOCOL_h
#define I2C_PROTOCOL_h

/*----- CONSTANT DEFINITIONS -------------------------------------------------*/
//// I2C timer related paramters
#define           I2C_MAX_BUSY_TIME                    3


//// Registers of I2C
#define           I2C_ADDRESS_REGISTER             TWAR     
#define           I2C_BITRATE_REGISTER             TWBR                             
#define           I2C_CONTROL_REGISTER             TWCR                             
#define           I2C_DATA_REGISTER                TWDR                             
#define           I2C_STATUS_REGISTER              TWSR                             


//// Bits of TWCR register
#define           TWIE                             0    // The interrupt enable bit
#define           TWEN                             2    // Enable I2C bit
#define           TWWC                             3    // Write collision bit
#define           TWSTO                            4    // Generatee stop signal bit
#define           TWSTA                            5    // Generate start singal bit
#define           TWEA                             6    // Enable acknowledge bit
#define           TWINT                            7    // Start TWI transaction/  TWI completed its current task


//// Output flags of I2C_Protocol() definition
#define           I2C_PROTOCOL_BUSY                0
#define           I2C_PROTOCOL_FINISHED            1


//// I2C states
// General
#define           I2C_READY                        0x01                 // I2C is ready (used to denote that I2C is called in a slave mode)
#define           I2C_START                        0x08                 // I2C started in MT mode
#define           I2C_REPEATED_START               0x10                 // I2C started in MT mode      
#define           I2C_BUSY                         0x02


// Master Transmit mode
#define           I2C_MT_MODE                      0x21                 // I2C to be initiated in MT mode
#define           I2C_MT_ADDRESS_ACK               0x18                 // I2C started in MT mode      
#define           I2C_MT_ADDRESS_NACK              0x20                 // I2C started in MT mode      
#define           I2C_MT_DATA_ACK                  0x28                 // I2C started in MT mode      
#define           I2C_MT_DATA_NACK                 0x30                 // I2C started in MT mode      

// Master Receive mode
#define           I2C_MR_MODE                      0x31
#define           I2C_MR_ADDRESS_ACK               0x40                 // I2C started in MT mode      
#define           I2C_MR_ADDRESS_NACK              0x48                 // I2C started in MT mode      
#define           I2C_MR_DATA_RECEIVE_ACK          0x50                 // I2C started in MT mode      
#define           I2C_MR_DATA_RECEIVE_NACK         0x58                 // I2C started in MT mode      

// Slave Receive mode
#define           I2C_SR_MODE                      0x31
#define           I2C_SR_START                     0x60
#define           I2C_SR_DATA_ACK                  0x80
#define           I2C_SR_DATA_NACK                 0x88

// Slave Transmit mode
#define           I2C_ST_MODE                      0x41
#define           I2C_ST_START                     0xA8
#define           I2C_ST_STOP                      0xC8
#define           I2C_ST_DATA_ACK                  0xB8
#define           I2C_ST_DATA_NACK                 0xC0


//// I2C Commands
// Master mode general commands
#define           I2C_START_SIGNAL                      (1<<TWINT)|(0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)                 
                  // I2C is busy (sending data or command) 

#define           I2C_REPEATED_START_SIGNAL             (1<<TWINT)|(0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)
                  // I2C is busy (sending data or command)

#define           I2C_STOP_SIGNAL                       (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(1<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)
                  // I2C is busy (sending data or command)

#define           I2C_TRANSMIT_ADDRESS_SIGNAL           (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)
                  // I2C is busy (sending data or command)     

#define           I2C_DISABLE_SIGNAL                       (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(1<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)
                  // I2C is busy (sending data or command)


// Slave mode general commands
#define           I2C_SLAVE_MODE_ENABLE_SIGNAL      (0<<TWINT)|(1<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)
                  // I2C is allowed to recognize own address in slave modes.

#define           I2C_SLAVE_MODE_DISABLE_SIGNAL     (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)
                  // I2C is allowed to recognize own address in slave modes.

// Master transmit mode commands
#define           I2C_MT_TRANSMIT_DATA_SIGNAL           (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)
                  // I2C is busy (sending data or command)

// Master receive mode commands
#define           I2C_MR_RECEIVE_DATA_SENDACK_SIGNAL    (1<<TWINT)|(1<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)                 
                  // I2C is busy (sending data or command)   

#define           I2C_MR_RECEIVE_DATA_SENDNACK_SIGNAL   (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)                 
                  // I2C is busy (sending data or command)   

// Slave receive mode commands
#define           I2C_SL_RECEIVE_DATA_SENDACK_SIGNAL    (1<<TWINT)|(1<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)
                  // I2C is busy (sending data or command)     

#define           I2C_SL_RECEIVE_DATA_SENDNACK_SIGNAL   (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)
                  // I2C is busy (sending data or command)     

// Slave transmit mode commands
#define           I2C_ST_TRANSMIT_DATA_SENDACK_SIGNAL   (1<<TWINT)|(1<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)
                  // I2C is busy (sending data or command)     

#define           I2C_ST_TRANSMIT_DATA_SENDNACK_SIGNAL  (1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)|(1<<TWEN)|(0<<TWIE)
                  // Allow recognition of own slave address in a NACK state for REPEATED START.

//// Other constants
#define           I2C_STATUS_REGISTER_PRESCALAR_MASK    0xF8            // 

// Read/write command to be sent to slave in the LSB of I2C_DATA_REGISTER 
#define           I2C_WRITE_TO_SLAVE                    0x00
#define           I2C_READ_FROM_SLAVE                   0x01


/*------ Global Variable Definition ------------------------------------------*/
extern           unsigned int               I2C_data_counter;     // Index of the current I2C data being transmitted.
extern           unsigned int               previous_system_time; // Previous system time.
extern           unsigned char              I2C_state_timer;      // I2C state timer.
extern           unsigned char              I2C_Status;           // Denotes the current status of I2C protocol.
                                                         // For every use (including the very first use, it is set to I2C_READY).


/*------ Function Definition -------------------------------------------------*/
bool I2C_Protocol(unsigned char *I2C_data_pointer, unsigned int I2C_data_length, unsigned char I2C_initiation_mode, unsigned char I2C_slave_address, unsigned char I2C_bitrate, unsigned char I2C_frequency_prescalar, unsigned int current_system_time);
void I2C_ERROR(void);
/* 
Input:
    spi_data: I

Output:
    No output

Description:
    This function sends an instruction to the flash memory on SPCR register, 
    then waits while the fourth bit in SPSR register is one (which means that
    the transaction is complete), then reads the content of SPCR again (which is
    the data sent back from the flash).
*/

#endif