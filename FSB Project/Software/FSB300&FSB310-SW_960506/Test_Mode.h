/*******************************************************************************
********************************************************************************
*@ File:	Test_Mode.c
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:96/01/19	Previous:96/01/19	Created:96/01/19
*@ Author:	M.Aghamohamadian 

*@ Brief:	This header is used for the test mode of FSB board.

********************************************************************************
*******************************************************************************/
/*----- Include Files --------------------------------------------------------*/
#ifndef TEST_MODE_h
#define TEST_MODE_h


/*----- CONSTANT DEFINITIONS -------------------------------------------------*/
// Control signal test inputs & don't care bits (used only in test mode)
#define         CTRL_Test_DontC_bits      0x3C	// The bits corresponding to the volume keys are eliminated
#define         EMR_TEST_INPUT            0xFF34	// Shape of the signal when testing emrgency pin
#define         OVL_TEST_INPUT            0xFF20
#define         DOB_TEST_INPUT            0xFF38
#define         TRG_TEST_INPUT            0xFF10

// Volume signal test inputs (used only in test mode)
#define         NUM_B2_TEST_INPUT         0xFE30  // Shape of the signal when testing B2 pin 
#define         NUM_A2_TEST_INPUT         0xFD30
#define         NUM_A1_TEST_INPUT         0xFB30
#define         NUM_B1_TEST_INPUT         0xF730
#define         NUM_C1_TEST_INPUT         0xEF30
#define         NUM_E1_TEST_INPUT         0xDF30
#define         NUM_F1_TEST_INPUT         0xBF30
#define         NUM_G1_TEST_INPUT         0x7F30

// Other constants
#define         TOTAL_NO_PINS             12
#define         NO_PIN_EXCITED            TOTAL_NO_PINS + 3
/*------ Variable Definition -------------------------------------------------*/



/*------ Function Definition -------------------------------------------------*/
unsigned char Test_Input_Detection(struct ControlSignal *CTRL_Signal_Params, struct NumeratorSignal *NUM_Signal_Params);

/*
Input: 
          CTRL_Signal_Params: The pointer to the structure that holds all parameters related to control signal.
          NUM_Signal_Params: The pointer to the structure that holds the current and previous stop number along with numerator signal value.

Output: 
          The control input pin which has been excited.

Description:
          Used for determining which input pin has been excited.
*/

#endif