/*******************************************************************************
********************************************************************************
*@ File:	Learn_Mode.h
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:96/01/14	Previous:96/01/14	Created:96/01/14
*@ Author:	M.Aghamohamadian 

*@ Brief:	This header is used for the learn mode of FSB board.

********************************************************************************
*******************************************************************************/
/*----- Include Files --------------------------------------------------------*/
#ifndef LEARN_MODE_h
#define LEARN_MODE_h


/*----- CONSTANT DEFINITIONS -------------------------------------------------*/
// Learn mode constants
#define         LEARN_DontC_bits          0x28
#define         DOBAL_TRGAL               0x00
#define         DOBAH_TRGAL               0x08
#define         DOBAH_TRGAH               0x28
#define         DOBAL_TRGAH               0x20

/*------ Variable Definition -------------------------------------------------*/



/*------ Function Definition -------------------------------------------------*/
void Learn_Mode_Assignments(struct ControlSignal *CTRL_Signal_Params);

/*
Input: 
          No input.

Output: 
          No output.

Description:
         Used for debouncing and detecting signal in the learn mode.
*/

void DOBTRG_Level_Assignment(struct ControlSignal *CTRL_Signal_Params, unsigned char DOB_TRG_active_level);
/*
Input: 
          No input.

Output: 
          No output.

Description:
         Assigning the shape of TRG, DOB and OVL signal based on the detected signal
         in debounce mode.
*/

#endif