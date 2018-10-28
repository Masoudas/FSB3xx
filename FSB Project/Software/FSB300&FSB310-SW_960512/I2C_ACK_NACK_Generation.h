/* This header defines the function that is used for reading from AT45DB312D */
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


/*----- Variable Definition --------------------------------------------------*/
enum ACK_NACK_Notion
     {
       ACK,
       NACK,
     };

  
/*------ Function Definition -------------------------------------------------*/
ACK_NACK_Notion I2C_ACK_NACK_Generation(unsigned char I2C_data);
/* 
Input:
    I2C_data: Data received via I2C interface.

Output:
    No output

Description:
    By comparing the data received via I2C interface against those defined by
    DATA001, DATA002 and etc, this function generates an ACK or NACK to denote that
    the received data is erroneous or not.
*/

/*******************************************************************************
*******************************************************************************/
#endif