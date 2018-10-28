/*******************************************************************************
********************************************************************************
*@ File:	Learn_Mode.h
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:96/01/14	Previous:96/01/14	Created:96/01/14
*@ Author:	M.Aghamohamadian 

*@ Brief:	This module is used for the learn mode of FSB board.

********************************************************************************
*******************************************************************************/
#include <ioavr.h>
#include <inavr.h>
#include "General.h"
#include "Learn_Mode.h"
#include "IO_Module.h"

void Learn_Mode_Assignments(struct ControlSignal *CTRL_Signal_Params)
{
     // Initialization
     unsigned char          DOB_TRG_active_level;     // The active level for these signals (could be TRGAH_DOBAL and etc.)

     
     // Main commands
     if ((*CTRL_Signal_Params).debounce_counter >= LEARN_DEBOUNCE_NUMBER) // If debounce is done sufficiently,
     {
         (*CTRL_Signal_Params).debounce_counter = 0;     // Restart the debounce counter.
         DOB_TRG_active_level = (*CTRL_Signal_Params).current_input & LEARN_DontC_bits;    
         DOBTRG_Level_Assignment(CTRL_Signal_Params, DOB_TRG_active_level);
         
       // Store the new signal levels in EEPROM.    
       __EEPUT(EEPROM_DOBTRG_ACTIVE_LEVEL_ADD,DOB_TRG_active_level); 
     }
      

     // Finalization
}

void DOBTRG_Level_Assignment(struct ControlSignal *CTRL_Signal_Params, unsigned char DOB_TRG_active_level)
{
    // Initialization
  
  
    // Main commands
    if (DOB_TRG_active_level == DOBAL_TRGAL)    // If after eliminating the don't care bits, DOB is AL and TRG is AL as well,
    {          
      (*CTRL_Signal_Params).PARALLEL_TRG_input = 0x00;    
      (*CTRL_Signal_Params).PARALLEL_OVL_input = 0x20; 
      (*CTRL_Signal_Params).PARALLEL_DOB_input = 0x30;
    }
    else if (DOB_TRG_active_level == DOBAH_TRGAL)   
    {
      (*CTRL_Signal_Params).PARALLEL_TRG_input = 0x00;    
      (*CTRL_Signal_Params).PARALLEL_OVL_input = 0x20; 
      (*CTRL_Signal_Params).PARALLEL_DOB_input = 0x38;
    }
    else if (DOB_TRG_active_level == DOBAL_TRGAH)   
    {
      (*CTRL_Signal_Params).PARALLEL_TRG_input = 0x20;    
      (*CTRL_Signal_Params).PARALLEL_OVL_input = 0x00; 
      (*CTRL_Signal_Params).PARALLEL_DOB_input = 0x10;
    }
    else if (DOB_TRG_active_level == DOBAH_TRGAH)
    {
      (*CTRL_Signal_Params).PARALLEL_TRG_input = 0x20;    
      (*CTRL_Signal_Params).PARALLEL_OVL_input = 0x00; 
      (*CTRL_Signal_Params).PARALLEL_DOB_input = 0x18;
    }  
    else     // In case the value read from the ports is not meaningful, set it to the default DOBAL_TRGAL case.
    {
      (*CTRL_Signal_Params).PARALLEL_TRG_input = 0x00;    
      (*CTRL_Signal_Params).PARALLEL_OVL_input = 0x20; 
      (*CTRL_Signal_Params).PARALLEL_DOB_input = 0x30;      
    }
    
    
    // Finalization
}


