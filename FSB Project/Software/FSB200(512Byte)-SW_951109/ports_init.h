#ifndef PORTS_INIT_h
#define PORTS_INIT_h


//****************************board inputs**********************//
//num
#define          NUM_A_in           2
#define          NUM_B_in           3
#define          NUM_C_in           4
#define          NUM_E_in           2
#define          NUM_F_in           6
#define          NUM_G_in           7


////ctrl
#define          NUM___in           1
#define          TEN_in             0

//num
#define          NUM_A_n              0x04
#define          NUM_B_n              0x08
#define          NUM_C_n              0x10
#define          NUM_E_n              0x20
#define          NUM_F_n              0x40
#define          NUM_G_n              0x80


///ctrl
#define          NUM___n              0x02
#define          TEN_n                0x01


//ctrl
#define          TRIG_in            5
#define          OVL_in             4
#define          DOB_in             3

//ctrl
#define          TRG_n              0x20
#define          OVL_n              0x10
#define          DOB_n              0x08

#define          KEYS_A_n              0x03
#define          KEYS_P_n              0x01
#define          KEYS_N_n              0x02
#define          ALB_mode_n            0x04
#define          ALB_mode_in           2

//#define          CHG_ALB_n           0x01


#define          EMR_n               0x01
#define          EMR_in              0


#define          EMR_input         PINB
#define          EMR_port          PORTB
#define          EMR_direct        DDRB



#define          KEYS_input                PINC
//#define          CHG_ALB_p_input           PINC
//#define          CHG_ALB_n_input           PINC
#define          ALB_mode_output            PORTC

//PINB.0  ///


#define          Numr_input         PIND
#define          Numr_port          PORTD
#define          Numr_direct        DDRD

#define          ctrl_input         PINC
#define          ctrl_direct        DDRC
#define          ctrl_port          PORTC






///--------------------------------------------------------------//

//***************************SD interface**********************//
#define     SD_EN_PORT              2
#define     SD_MOSI_PORT            3
#define     SD_MISO_PORT            4
#define     SD_SCK_PORT             5


#define     SD_EN_n                   0x04
#define     SD_MOSI_n                 0x08
#define     SD_MISO_n                 0x10
#define     SD_SCK_n                  0x20

///--------------------------------------------------------------//


//***************************PWM OUTPUTS**********************//
#define     PWM_OUT       PORTB.1
#define     PWM_DIR       DDRB.1
///--------------------------------------------------------------//
        
#define          SD_PWM_inputs        PINB
#define          SD_PWM_port          PORTB
#define          SD_PWM_direct        DDRB



#endif 