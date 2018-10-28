#include <inavr.h>
#include <ioavr.h>
#include <iom8.h>
#include "general.h"
#include "PORTS_init.h"
#include "inputs_check.h"


unsigned char GET_ctrl_inputs(void)
{
    unsigned char temp=0x00;
    unsigned char control_reg=0x00;
    if(TESTBIT(srial_input,SERIAL_sel_in)==SERIAL_enable)
    {
          return(control_reg);
          ////for serial interface  
    }
    else
    {
     // SETBIT(PORTD,0);
          //ctrl_inputs=0 0 0 0 FST OVL DOB emg 
          temp=ctrl_input & 0x0e;            
          //temp=temp<<3;          
          control_reg=temp;                  
          /*temp=EMR_inputs;          
          temp=temp<<7;
          temp= temp&0x80;
          control_reg |=temp;*/
          /*if((PINC & 0x0e)==0x0e)
              SETBIT(PORTD,0);*/
          
          return(control_reg);
    }
    
}
unsigned char GET_num_inputs(void)
{
  unsigned char numerator_register=0x00;
  unsigned char temp=0x00;
    
  if(TESTBIT(srial_input,SERIAL_sel_in)==SERIAL_enable)
    {
          return(numerator_register);
          ////for serial interface  
    }
    else
    {           
           numerator_register= Numr_input>>2;
           numerator_register &=0x3F;
           temp=ctrl_input<<3;
           temp &=0xC0;
           numerator_register += temp;
           return(numerator_register);
    }
    
}
 