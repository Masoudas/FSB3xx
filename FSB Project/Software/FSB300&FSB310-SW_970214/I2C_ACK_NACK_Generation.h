/*******************************************************************************
********************************************************************************
*@ File:	I2C_ACK_NACK_Generation.c
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:95/12/25	Previous:95/12/25	Created:95/12/25
*@ Author:	M. Aghamohamadian

*@ Brief:	This header holds the data to be compared against the data received through I2C.

********************************************************************************
*******************************************************************************/
/*----- Include Files --------------------------------------------------------*/
#ifndef I2C_ACK_NACK_GENERATION_h
#define I2C_ACK_NACK_GENERATION_h

/*----- CONSTANT DEFINITIONS -------------------------------------------------*/
//// CRC Check ACK/NACK generation
#define                 CRC_LENGTH              2       // The length of CRC (in byte).
#define                 TWOBYTE_CRC_POLYNOMIAL  0x8005  // The CRC polynomial.

//Outputs of Check_CRC function
#define                 CRC_VALID               1       // The received CRC value equals the computed one.
#define                 CRC_INVALID             0

//I2C data
#define         SERIAL_NO_CTRL_INPUT            0x80   // The case where there is no control signal.
#define         SERIAL_EMR_INPUT                0x81
#define         SERIAL_TRG_INPUT                0x82
#define         SERIAL_OVL_INPUT                0x84
#define         SERIAL_DOB_INPUT                0x88
#define         SERIAL_DIRECTION_UP_INPUT       0x90
#define         SERIAL_DIRECTION_DOWN_INPUT     0xA0

#define         SERIAL_PARK_09_BYTE0            0x10  
#define         SERIAL_PARK_09_BYTE1            0x0C  

#define         SERIAL_PARK_08_BYTE0            0x00   
#define         SERIAL_PARK_08_BYTE1            0x0C   

#define         SERIAL_PARK_07_BYTE0            0x78   
#define         SERIAL_PARK_07_BYTE1            0x0C   

#define         SERIAL_PARK_06_BYTE0            0x02   
#define         SERIAL_PARK_06_BYTE1            0x0C   

#define         SERIAL_PARK_05_BYTE0            0x12   
#define         SERIAL_PARK_05_BYTE1            0x0C   

#define         SERIAL_PARK_04_BYTE0            0x19   
#define         SERIAL_PARK_04_BYTE1            0x0C   

#define         SERIAL_PARK_03_BYTE0            0x30   
#define         SERIAL_PARK_03_BYTE1            0x0C   

#define         SERIAL_PARK_02_BYTE0            0x24   
#define         SERIAL_PARK_02_BYTE1            0x0C   

#define         SERIAL_PARK_01_BYTE0            0x79
#define         SERIAL_PARK_01_BYTE1            0x0C

#define         SERIAL_PARK_BYTE0               0x0C
#define         SERIAL_PARK_BYTE1               0x7F

#define         SERIAL_FLOOR_MINUS_10_BYTE0     0x40   
#define         SERIAL_FLOOR_MINUS_10_BYTE1     0x3F   

#define         SERIAL_FLOOR_MINUS_09_BYTE0     0x10                 
#define         SERIAL_FLOOR_MINUS_09_BYTE1     0x3F                 

#define         SERIAL_FLOOR_MINUS_08_BYTE0     0x00
#define         SERIAL_FLOOR_MINUS_08_BYTE1     0x3F

#define         SERIAL_FLOOR_MINUS_07_BYTE0     0x78                                        
#define         SERIAL_FLOOR_MINUS_07_BYTE1     0x3F                                        

#define         SERIAL_FLOOR_MINUS_06_BYTE0     0x02   
#define         SERIAL_FLOOR_MINUS_06_BYTE1     0x3F   

#define         SERIAL_FLOOR_MINUS_05_BYTE0     0x12                                     
#define         SERIAL_FLOOR_MINUS_05_BYTE1     0x3F                                     

#define         SERIAL_FLOOR_MINUS_04_BYTE0     0x19                                     
#define         SERIAL_FLOOR_MINUS_04_BYTE1     0x3F                                     

#define         SERIAL_FLOOR_MINUS_03_BYTE0     0x30  
#define         SERIAL_FLOOR_MINUS_03_BYTE1     0x3F  

#define         SERIAL_FLOOR_MINUS_02_BYTE0     0x24                                     
#define         SERIAL_FLOOR_MINUS_02_BYTE1     0x3F                                     

#define         SERIAL_FLOOR_MINUS_01_BYTE0     0x79
#define         SERIAL_FLOOR_MINUS_01_BYTE1     0x3F

#define         SERIAL_BASEMENT_09_BYTE0        0x10  
#define         SERIAL_BASEMENT_09_BYTE1        0x03  

#define         SERIAL_BASEMENT_08_BYTE0        0x00   
#define         SERIAL_BASEMENT_08_BYTE1        0x03   

#define         SERIAL_BASEMENT_07_BYTE0        0x78   
#define         SERIAL_BASEMENT_07_BYTE1        0x03   

#define         SERIAL_BASEMENT_06_BYTE0        0x02   
#define         SERIAL_BASEMENT_06_BYTE1        0x03   

#define         SERIAL_BASEMENT_05_BYTE0        0x12
#define         SERIAL_BASEMENT_05_BYTE1        0x03

#define         SERIAL_BASEMENT_04_BYTE0        0x19
#define         SERIAL_BASEMENT_04_BYTE1        0x03

#define         SERIAL_BASEMENT_03_BYTE0        0x30  
#define         SERIAL_BASEMENT_03_BYTE1        0x03  

#define         SERIAL_BASEMENT_02_BYTE0        0x24
#define         SERIAL_BASEMENT_02_BYTE1        0x03

#define         SERIAL_BASEMENT_01_BYTE0        0x79
#define         SERIAL_BASEMENT_01_BYTE1        0x03

#define         SERIAL_BASEMENT_BYTE0           0x03  
#define         SERIAL_BASEMENT_BYTE1           0x7F  

#define         SERIAL_GROUND_BYTE0             0x42    // Hamkaf (in human terms!)
#define         SERIAL_GROUND_BYTE1             0x7F    // Hamkaf (in human terms!)

#define         SERIAL_MANAGEMENT_BYTE0         0x25
#define         SERIAL_MANAGEMENT_BYTE1         0x7F

#define         SERIAL_HYPERSTAR_BYTE0          0x0B
#define         SERIAL_HYPERSTAR_BYTE1          0x7F

#define         SERIAL_HYPERME_BYTE0            0x06
#define         SERIAL_HYPERME_BYTE1            0x09

#define         SERIAL_ARCHIVE_BYTE0            0x20    // Baygani (again in human terms!)
#define         SERIAL_ARCHIVE_BYTE1            0x7F    // Baygani (again in human terms!)

#define         SERIAL_ROOFGARDEN_BYTE0         0x42    
#define         SERIAL_ROOFGARDEN_BYTE1         0x0F    

#define         SERIAL_FOODCOURT_BYTE0          0x46    
#define         SERIAL_FOODCOURT_BYTE1          0x0E    

#define         SERIAL_PLAYGROUND_BYTE0         0x42    
#define         SERIAL_PLAYGROUND_BYTE1         0x0C    

#define         SERIAL_PENTHOUSE_BYTE0          0x09   
#define         SERIAL_PENTHOUSE_BYTE1          0x0C   

#define         SERIAL_RESTAURANT_BYTE0         0x0F
#define         SERIAL_RESTAURANT_BYTE1         0x7F

#define         SERIAL_LOBBY_BYTE0              0x47
#define         SERIAL_LOBBY_BYTE1              0x7F

#define         SERIAL_POOL_BYTE0               0x47
#define         SERIAL_POOL_BYTE1               0x0C

#define         SERIAL_ROOFTOP_BYTE0            0x09      
#define         SERIAL_ROOFTOP_BYTE1            0x09      

#define         SERIAL_PEDIATRICIAN_BYTE0       0x12
#define         SERIAL_PEDIATRICIAN_BYTE1       0x46

#define         SERIAL_EUROLOGIST_BYTE0         0x41
#define         SERIAL_EUROLOGIST_BYTE1         0x06

#define         SERIAL_GYNECOLOGIST_BYTE0       0x06
#define         SERIAL_GYNECOLOGIST_BYTE1       0x42

#define         SERIAL_DENTIST_BYTE0            0x12
#define         SERIAL_DENTIST_BYTE1            0x40

#define         SERIAL_PROJECT_ONE_BYTE0        0x0C
#define         SERIAL_PROJECT_ONE_BYTE1        0x79

#define         SERIAL_EXITWAY_BYTE0            0x06
#define         SERIAL_EXITWAY_BYTE1            0x40

#define         SERIAL_FLOOR01_BYTE0            0x79
#define         SERIAL_FLOOR01_BYTE1            0x7F

#define         SERIAL_FLOOR02_BYTE0            0x24
#define         SERIAL_FLOOR02_BYTE1            0x7F

#define         SERIAL_FLOOR03_BYTE0            0x30
#define         SERIAL_FLOOR03_BYTE1            0x7F

#define         SERIAL_FLOOR04_BYTE0            0x19
#define         SERIAL_FLOOR04_BYTE1            0x7F

#define         SERIAL_FLOOR05_BYTE0            0x12
#define         SERIAL_FLOOR05_BYTE1            0x7F

#define         SERIAL_FLOOR06_BYTE0            0x02
#define         SERIAL_FLOOR06_BYTE1            0x7F

#define         SERIAL_FLOOR07_BYTE0            0x78
#define         SERIAL_FLOOR07_BYTE1            0x7F

#define         SERIAL_FLOOR08_BYTE0            0x00
#define         SERIAL_FLOOR08_BYTE1            0x7F

#define         SERIAL_FLOOR09_BYTE0            0x10
#define         SERIAL_FLOOR09_BYTE1            0x7F

#define         SERIAL_FLOOR10_BYTE0            0x40
#define         SERIAL_FLOOR10_BYTE1            0x79

#define         SERIAL_FLOOR11_BYTE0            0x79
#define         SERIAL_FLOOR11_BYTE1            0x79

#define         SERIAL_FLOOR12_BYTE0            0x24
#define         SERIAL_FLOOR12_BYTE1            0x79

#define         SERIAL_FLOOR13_BYTE0            0x30
#define         SERIAL_FLOOR13_BYTE1            0x79

#define         SERIAL_FLOOR14_BYTE0            0x19
#define         SERIAL_FLOOR14_BYTE1            0x79

#define         SERIAL_FLOOR15_BYTE0            0x12
#define         SERIAL_FLOOR15_BYTE1            0x79

#define         SERIAL_FLOOR16_BYTE0            0x02
#define         SERIAL_FLOOR16_BYTE1            0x79

#define         SERIAL_FLOOR17_BYTE0            0x78
#define         SERIAL_FLOOR17_BYTE1            0x79

#define         SERIAL_FLOOR18_BYTE0            0x00
#define         SERIAL_FLOOR18_BYTE1            0x79

#define         SERIAL_FLOOR19_BYTE0            0x10
#define         SERIAL_FLOOR19_BYTE1            0x79

#define         SERIAL_FLOOR20_BYTE0            0x40
#define         SERIAL_FLOOR20_BYTE1            0x24

#define         SERIAL_FLOOR21_BYTE0            0x79
#define         SERIAL_FLOOR21_BYTE1            0x24

#define         SERIAL_FLOOR22_BYTE0            0x24
#define         SERIAL_FLOOR22_BYTE1            0x24

#define         SERIAL_FLOOR23_BYTE0            0x30
#define         SERIAL_FLOOR23_BYTE1            0x24

#define         SERIAL_FLOOR24_BYTE0            0x19
#define         SERIAL_FLOOR24_BYTE1            0x24

#define         SERIAL_FLOOR25_BYTE0            0x12
#define         SERIAL_FLOOR25_BYTE1            0x24

#define         SERIAL_FLOOR26_BYTE0            0x02
#define         SERIAL_FLOOR26_BYTE1            0x24

#define         SERIAL_FLOOR27_BYTE0            0x78
#define         SERIAL_FLOOR27_BYTE1            0x24

#define         SERIAL_FLOOR28_BYTE0            0x00
#define         SERIAL_FLOOR28_BYTE1            0x24

#define         SERIAL_FLOOR29_BYTE0            0x10
#define         SERIAL_FLOOR29_BYTE1            0x24

#define         SERIAL_FLOOR30_BYTE0            0x40
#define         SERIAL_FLOOR30_BYTE1            0x30

#define         SERIAL_FLOOR31_BYTE0            0x79
#define         SERIAL_FLOOR31_BYTE1            0x30

#define         SERIAL_FLOOR32_BYTE0            0x24
#define         SERIAL_FLOOR32_BYTE1            0x30

#define         SERIAL_FLOOR33_BYTE0            0x30
#define         SERIAL_FLOOR33_BYTE1            0x30

#define         SERIAL_FLOOR34_BYTE0            0x19
#define         SERIAL_FLOOR34_BYTE1            0x30

#define         SERIAL_FLOOR35_BYTE0            0x12
#define         SERIAL_FLOOR35_BYTE1            0x30

#define         SERIAL_FLOOR36_BYTE0            0x02
#define         SERIAL_FLOOR36_BYTE1            0x30

#define         SERIAL_FLOOR37_BYTE0            0x78
#define         SERIAL_FLOOR37_BYTE1            0x30

#define         SERIAL_FLOOR38_BYTE0            0x00
#define         SERIAL_FLOOR38_BYTE1            0x30

#define         SERIAL_FLOOR39_BYTE0            0x10
#define         SERIAL_FLOOR39_BYTE1            0x30

#define         SERIAL_FLOOR40_BYTE0            0x40
#define         SERIAL_FLOOR40_BYTE1            0x19


/*----- Global Variables ---------------------------------------------------- */
extern                  unsigned char            generated_CRC_bytes[2];  // The CRC data bytes.
extern                  unsigned char            received_CRC_bytes[2];   // Received CRC bytes.


/*----- Variable Definition --------------------------------------------------*/
enum ACK_NACK_Notion    // An enumeration which denotes software ACK and NACK for I2C.
     {
       ACK,
       NACK,
     };

  
/*------ Function Definition -------------------------------------------------*/
ACK_NACK_Notion I2C_ACK_NACK_Generation(unsigned char *I2C_data_pointer, unsigned char I2C_data_counter, unsigned char I2C_data);
/* 
Input:
    

Output:
    No output.

Description:
    By comparing the data received via I2C interface against those defined by
    DATA001, DATA002 and etc, this function generates an ACK or NACK to denote that
    the received data is erroneous or not.
*/

void Generate_CRC_Bytes(unsigned char *I2C_data_pointer, unsigned char I2C_data_length);
/* 
Input:
    I2C_data_pointer: The pointer to the I2C data.
    I2C_data_length: The length of I2C data.   

Output:
    No output.

Description:
    This function computes the CRC bytes and returns it in a two byte array..
*/

bool Check_CRC(char CRC_length, unsigned char *I2C_data_pointer, unsigned char I2C_data_length);
/* 
Input:
    CRC_length: The length of CRC bytes.

Output:
    No output.

Description:
    This function compares the received with computed CRC bytes and generates a flag
    to denote if they were equal.    
*/

ACK_NACK_Notion Primary_Check(unsigned char *I2C_data_pointer, unsigned char I2C_data_counter, unsigned char I2C_data);      // It's not like anybody gives a shit what this function does.
ACK_NACK_Notion Secondary_Check(unsigned char I2C_data);
#endif