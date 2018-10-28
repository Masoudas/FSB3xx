/*******************************************************************************
********************************************************************************
*@ File:	Test_Mode.c
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:96/01/19	Previous:96/01/19	Created:96/01/19
*@ Author:	M.Aghamohamadian 

*@ Brief:	This module contains the functions for test mode.

********************************************************************************
*******************************************************************************/
#include <inavr.h>
#include <ioavr.h>
#include "General.h"
#include "Test_Mode.h"
#include "IO_Module.h"


unsigned char Test_Input_Detection(struct ControlSignal *CTRL_Signal_Params, struct NumeratorSignal *NUM_Signal_Params)
{
     //// Initialization
     unsigned int        current_test_input;     // The signal value present at the inputs in test mode altogether in the form PORTD-PORTC. See the report.
     unsigned char       test_input_number;      // Denotes which control input have been excited in the test mode.   
     
     
     //// Main commands
     current_test_input = ((unsigned int)((*NUM_Signal_Params).current_input) << 8) + (unsigned int)((*CTRL_Signal_Params).current_input & CTRL_Test_DontC_bits);     // Define an integer number that contains both the numerator and control signals
                                                                                                                                                // in order to see which input has been excited in this mode.                                    
     
     // Decide on the input pin excited in this mode.
     switch(current_test_input)
     {
       case (DOB_TEST_INPUT):
          test_input_number = 1;
       break;
       
       case (OVL_TEST_INPUT):
          test_input_number = 2;
       break;
       
       case (TRG_TEST_INPUT):
          test_input_number = 3;
       break;
       
       case (NUM_B2_TEST_INPUT):
          test_input_number = 4;
       break;
       
       case (NUM_A2_TEST_INPUT):
          test_input_number = 5;
       break;

       case (NUM_A1_TEST_INPUT):
          test_input_number = 6;
       break;

       case (NUM_B1_TEST_INPUT):
          test_input_number = 7;
       break;

       case (NUM_C1_TEST_INPUT):
          test_input_number = 8;
       break;

       case (NUM_E1_TEST_INPUT):          
          test_input_number = 9;
       break;
         
       case (NUM_F1_TEST_INPUT):          
          test_input_number = 10;
       break;

       case (NUM_G1_TEST_INPUT):
          test_input_number = 11;
       break;
       
       case (EMR_TEST_INPUT):          
          test_input_number = 12;
       break;    
       
       default: // No control pin has been excited, return a number greater than the total number of pins.
          test_input_number = NO_PIN_EXCITED;        // Don't panic! Just making sure that test_input_number is bogus when no input is excited!
       break;
     }


     //// Finalization
     return (test_input_number);
}


