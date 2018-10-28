#ifndef GENERAL_h
#define GENERAL_h


#define CLEARBIT(ADDRESS,BIT) (ADDRESS &=~(1<<BIT))
#define SETBIT(ADDRESS,BIT) (ADDRESS |=(1<<BIT))
#define TESTBIT(ADDRESS,BIT) (ADDRESS &(1<<BIT))




#define       MAX_PH_TRACK       43

#define       MAX_ALBUME_NUM     4
#define       BUFFER_SIZE         528





#define  Floor0   0x80
#define  Floor1   0xE4
#define  Floor2   0x50
#define  Floor3   0x60
#define  Floor4   0x24
#define  Floor5   0x28
#define  Floor6   0x08
#define  Floor7   0xE0
#define  Floor8   0x00
#define  Floor9   0x20
#define  Lobby    0x9C
#define  Parking  0x10
#define  Ground   0x88
#define  UGround  0x0C
#define  Resturan 0x5C




//////////////////////////*********enabale states************/////////////
#define     SD_ENABLE               0
#define     SERIAL_enable           1 
///the resistor isnot montage

#define     DOB_enable              0x08
//DOB is active low for active high DOB=0x08  should be exchanged (The Jackass who wrote this software told it wrong)


#define     OVL_enable              0x00
//OVL is active low for active high OVL=0x20  should be exchanged

#define     TRG_enable              0x00
//OVL is active low for active high OVL=0x40  should be exchanged


//#define     EMR_enable              0x80
//OVL is active low for active high OVL=0x40  should be exchanged


#define     KEYS_enable             0x00
#define     KEYS_P_enable           0x02
//ONLY POSITIVE KEY IS ENABLE

#define     KEYS_N_enable           0x01
//ONLY NEGATIVE KEY IS ENABLE

#define     ALB_M_enable            0x00
/// for vol + and -  keys and albume mode led

//#define     MAX_ALB_DELAY           0XF0


#define     EMR_enable              0x01
////for emergancy input

#define     ctrl_inputs_check       0x3E
#define     num_inputs_check        0xFc


/////////////////////********states*********//////////////////////////////////
enum Total_state
{
  EMR,     //step0
  OVL,     //step1
  DOB,     //step2
  DING,    //step3
  MUS,     //step4
  FLOORS,  //step5
  SILENCE, //step6
  CHG_ALBUME,
  WEL,
  
};

enum SD_ERROR_ID
 {
       NO_ERROR,
       SD_READ_ERROR,
       FAT_INIT_ERROR
             
 };


// unsigned char sound_buffer[BUFFER_SIZE];
 
//////////////////////////*********delayes and times *********////////////////
#define       OVL_delay            20
#define       DOB_delay            40
#define       MUS_a_Speach         2000
#define       START_UP_DELAY       1000
#define       DEBOUNCE_DELAY       4
#define       Debounce_num        4





#define         DING_TRACK          36
#define         OVL_TRACK           35
#define         DOB_TRACK           34
#define         EMERG_TRACK         33
#define         WEL_TRACK           37

#define         MUSICA0_TRACK       38
#define         MUSICA1_TRACK       39
#define         MUSICA2_TRACK       40
#define         MUSICA3_TRACK       41
#define         MUSICA4_TRACK       42



#define        lobby_index          30
#define        rest_index           32
#define        gnd_index            0
#define        par_index            31


#define        MAX_VOLUME_LEVEL     4





#endif 


