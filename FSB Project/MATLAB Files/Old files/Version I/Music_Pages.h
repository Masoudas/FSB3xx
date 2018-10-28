/*******************************************************************************
********************************************************************************
*@ File:	Flash_Data_Read.cpp
****************************************
*@ Company:	Sadr Electronic Dena Co.

*@ Version:	1.0
*@ Update:	Last:95/10/07	Previous:95/10/07	Created:95/10/07
*@ Author:	M. Aghamohamadian 

*@ Brief:	This header contains the page number for each particular sound.

********************************************************************************
*******************************************************************************/

/*----- Include Files --------------------------------------------------------*/
#ifndef SOUND_H
#define SOUND_H


/*----- CONSTANT DEFINITIONS -------------------------------------------------*/
//// Initial and final page for each message
#define    EMR_INITIAL_PAGE                      <param011>   // Emergency message initial page.
#define    EMR_FINAL_PAGE                        <param012>   // Emergency message final page.

#define    DINGDONG_INITIAL_PAGE                 <param021> 
#define    DINGDONG_FINAL_PAGE                   <param022>

#define    DOB_INITIAL_PAGE                      <param031>
#define    DOB_FINAL_PAGE                        <param032>

#define    OVL_INITIAL_PAGE                      <param041>
#define    OVL_FINAL_PAGE                        <param042>

#define    DING_INITIAL_PAGE                     <param051>
#define    DING_FINAL_PAGE                       <param052>

#define    MUSIC_INITIAL_PAGE                    <param061>
#define    MUSIC_FINAL_PAGE                      <param062>

#define    EMR_MUSIC_INITIAL_PAGE                <param071>
#define    EMR_MUSIC_FINAL_PAGE                  <param072>

#define    FLOOR_01_INITIAL_PAGE                 <param081>      // Floor 1 intial page
#define    FLOOR_01_FINAL_PAGE                   <param082>     // Floor 1 final page

#define    FLOOR_02_INITIAL_PAGE                 <param091>
#define    FLOOR_02_FINAL_PAGE                   <param092>

#define    FLOOR_03_INITIAL_PAGE                 <param101>
#define    FLOOR_03_FINAL_PAGE                   <param102>

#define    FLOOR_04_INITIAL_PAGE                 <param111>
#define    FLOOR_04_FINAL_PAGE                   <param112>

#define    FLOOR_05_INITIAL_PAGE                 <param121>
#define    FLOOR_05_FINAL_PAGE                   <param122>

#define    FLOOR_06_INITIAL_PAGE                 <param131>   
#define    FLOOR_06_FINAL_PAGE                   <param132>   

#define    FLOOR_07_INITIAL_PAGE                 <param141>   
#define    FLOOR_07_FINAL_PAGE                   <param142>   

#define    FLOOR_08_INITIAL_PAGE                 <param151>   
#define    FLOOR_08_FINAL_PAGE                   <param152>   

#define    FLOOR_09_INITIAL_PAGE                 <param161>   
#define    FLOOR_09_FINAL_PAGE                   <param162>   

#define    FLOOR_10_INITIAL_PAGE                 <param171>   
#define    FLOOR_10_FINAL_PAGE                   <param172>   

#define    FLOOR_11_INITIAL_PAGE                 <param181>   
#define    FLOOR_11_FINAL_PAGE                   <param182>   

#define    FLOOR_12_INITIAL_PAGE                 <param191>   
#define    FLOOR_12_FINAL_PAGE                   <param192>   

#define    FLOOR_13_INITIAL_PAGE                 <param201>   
#define    FLOOR_13_FINAL_PAGE                   <param202>   

#define    FLOOR_14_INITIAL_PAGE                 <param211>   
#define    FLOOR_14_FINAL_PAGE                   <param212>   

#define    FLOOR_15_INITIAL_PAGE                 <param221>   
#define    FLOOR_15_FINAL_PAGE                   <param222>   

#define    FLOOR_16_INITIAL_PAGE                 <param231>   
#define    FLOOR_16_FINAL_PAGE                   <param232>   

#define    FLOOR_17_INITIAL_PAGE                 <param241>   
#define    FLOOR_17_FINAL_PAGE                   <param242>   

#define    FLOOR_18_INITIAL_PAGE                 <param251>   
#define    FLOOR_18_FINAL_PAGE                   <param252>   

#define    FLOOR_19_INITIAL_PAGE                 <param261>   
#define    FLOOR_19_FINAL_PAGE                   <param262>   

#define    FLOOR_20_INITIAL_PAGE                 0   
#define    FLOOR_20_FINAL_PAGE                   0  

#define    FLOOR_21_INITIAL_PAGE                 0   
#define    FLOOR_21_FINAL_PAGE                   0  

#define    FLOOR_22_INITIAL_PAGE                 0   
#define    FLOOR_22_FINAL_PAGE                   0  

#define    FLOOR_23_INITIAL_PAGE                 0   
#define    FLOOR_23_FINAL_PAGE                   0  

#define    FLOOR_24_INITIAL_PAGE                 0   
#define    FLOOR_24_FINAL_PAGE                   0  

#define    FLOOR_25_INITIAL_PAGE                 0   
#define    FLOOR_25_FINAL_PAGE                   0  

#define    FLOOR_26_INITIAL_PAGE                 0   
#define    FLOOR_26_FINAL_PAGE                   0  

#define    FLOOR_27_INITIAL_PAGE                 0   
#define    FLOOR_27_FINAL_PAGE                   0  

#define    FLOOR_28_INITIAL_PAGE                 0   
#define    FLOOR_28_FINAL_PAGE                   0  

#define    FLOOR_29_INITIAL_PAGE                 0   
#define    FLOOR_29_FINAL_PAGE                   0  

#define    PARKING_INITIAL_PAGE                  <param271>    
#define    PARKING_FINAL_PAGE                    <param272>  

#define    PARKING_01_INITIAL_PAGE               <param281> 
#define    PARKING_01_FINAL_PAGE                 <param282>   

#define    PARKING_02_INITIAL_PAGE               <param291>   
#define    PARKING_02_FINAL_PAGE                 <param292>   

#define    PARKING_03_INITIAL_PAGE               <param301>  
#define    PARKING_03_FINAL_PAGE                 <param302>   

#define    PARKING_04_INITIAL_PAGE               <param311>    
#define    PARKING_04_FINAL_PAGE                 <param312>    

#define    PARKING_05_INITIAL_PAGE               <param321>  
#define    PARKING_05_FINAL_PAGE                 <param322>  

#define    PARKING_06_INITIAL_PAGE               <param331>   
#define    PARKING_06_FINAL_PAGE                 <param332>    

#define    PARKING_07_INITIAL_PAGE               <param341>   
#define    PARKING_07_FINAL_PAGE                 <param342>  

#define    PARKING_08_INITIAL_PAGE               <param351>   
#define    PARKING_08_FINAL_PAGE                 <param352>   

#define    PARKING_09_INITIAL_PAGE               0   
#define    PARKING_09_FINAL_PAGE                 0  

#define    BASEMENT_INITIAL_PAGE                 <param361>
#define    BASEMENT_FINAL_PAGE                   <param362>

#define    LOBBY_INITIAL_PAGE                    <param371>
#define    LOBBY_FINAL_PAGE                      <param372>

#define    GROUND_INITIAL_PAGE                   <param381>
#define    GROUND_FINAL_PAGE                     <param382>

#define    EXTR_ALBM1_INITIAL_PAGE               <param391>
#define    EXTR_ALBM1_FINAL_PAGE                 <param392>

#define    EXTR_ALBM2_INITIAL_PAGE               <param401>
#define    EXTR_ALBM2_FINAL_PAGE                 <param402>


/*------ Global Variable Definition ------------------------------------------*/


/*------ Function Definition -------------------------------------------------*/

#endif 

  