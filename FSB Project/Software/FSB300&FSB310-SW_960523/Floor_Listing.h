//// FSB310 parameters
// Control signals 
#define         NO_CTRL_INPUT        0x80   // The case where there is no control signal.
#define         EMR_INPUT            0x81
#define         TRG_INPUT            0x82
#define         OVL_INPUT            0x84
#define         DOB_INPUT            0x88
#define         DIRECTION_UP_INPUT   0x90
#define         DIRECTION_DOWN_INPUT 0xA0

// Stop status signals
#define         PARK_09_BYTE1            0x0C   // The first byte of numerator signal for parking 9 (first byte is transmitted first!).
#define         PARK_09_BYTE2            0x10   // The second byte of numerator signal for parking 9 (second byte is transmitted second!).

#define         PARK_08_BYTE1            0x0C  
#define         PARK_08_BYTE2            0x00   

#define         PARK_07_BYTE1            0x0C   
#define         PARK_07_BYTE2            0x78 

#define         PARK_06_BYTE1            0x0C   
#define         PARK_06_BYTE2            0x02 

#define         PARK_05_BYTE1            0x0C
#define         PARK_05_BYTE2            0x12 

#define         PARK_04_BYTE1            0x0C
#define         PARK_04_BYTE2            0x19 

#define         PARK_03_BYTE1            0x0C   
#define         PARK_03_BYTE2            0x30 

#define         PARK_02_BYTE1            0x0C   
#define         PARK_02_BYTE2            0x24   

#define         PARK_01_BYTE1            0x0C
#define         PARK_01_BYTE2            0x79

#define         PARK_00_BYTE1            0x7F
#define         PARK_00_BYTE2            0x0C

#define         FLOOR_MINUS_10_BYTE1     0x3F   
#define         FLOOR_MINUS_10_BYTE2     0x40

#define         FLOOR_MINUS_09_BYTE1     0x3F   
#define         FLOOR_MINUS_09_BYTE2     0x10
                
#define         FLOOR_MINUS_08_BYTE1     0x3F
#define         FLOOR_MINUS_08_BYTE2     0x00
                
#define         FLOOR_MINUS_07_BYTE1     0x3F   
#define         FLOOR_MINUS_07_BYTE2     0x78
                
#define         FLOOR_MINUS_06_BYTE1     0x3F   
#define         FLOOR_MINUS_06_BYTE2     0x02
                
#define         FLOOR_MINUS_05_BYTE1     0x3F
#define         FLOOR_MINUS_05_BYTE2     0x12
                
#define         FLOOR_MINUS_04_BYTE1     0x3F
#define         FLOOR_MINUS_04_BYTE2     0x19
                
#define         FLOOR_MINUS_03_BYTE1     0x3F  
#define         FLOOR_MINUS_03_BYTE2     0x30
                
#define         FLOOR_MINUS_02_BYTE1     0x3F
#define         FLOOR_MINUS_02_BYTE2     0x24
                
#define         FLOOR_MINUS_01_BYTE1     0x3F
#define         FLOOR_MINUS_01_BYTE2     0x79
                
#define         BASEMENT_09_BYTE1        0x03  
#define         BASEMENT_09_BYTE2        0x10

#define         BASEMENT_08_BYTE1        0x03
#define         BASEMENT_08_BYTE2        0x00

#define         BASEMENT_07_BYTE1        0x03   
#define         BASEMENT_07_BYTE2        0x78

#define         BASEMENT_06_BYTE1        0x03
#define         BASEMENT_06_BYTE2        0x02

#define         BASEMENT_05_BYTE1        0x03
#define         BASEMENT_05_BYTE2        0x12

#define         BASEMENT_04_BYTE1        0x03
#define         BASEMENT_04_BYTE2        0x19

#define         BASEMENT_03_BYTE1        0x03  
#define         BASEMENT_03_BYTE2        0x30

#define         BASEMENT_02_BYTE1        0x03
#define         BASEMENT_02_BYTE2        0x24

#define         BASEMENT_01_BYTE1        0x03
#define         BASEMENT_01_BYTE2        0x79

#define         BASEMENT_00_BYTE1        0x7F
#define         BASEMENT_00_BYTE2        0x03

#define         GROUND_BYTE1             0x7F    // Hamkaf (in human terms!)
#define         GROUND_BYTE2             0x42    // Hamkaf (in human terms!)

#define         MANAGEMENT_BYTE1         0x7F
#define         MANAGEMENT_BYTE2         0x25

#define         HYPERSTAR_BYTE1          0x7F
#define         HYPERSTAR_BYTE2          0x0B

#define         HYPERME_BYTE1            0x09
#define         HYPERME_BYTE2            0x06

#define         ARCHIVE_BYTE1            0x7F    // Baygani (again in human terms!)
#define         ARCHIVE_BYTE2            0x20    // Baygani (again in human terms!)

#define         ROOFGARDEN_BYTE1         0x0F    
#define         ROOFGARDEN_BYTE2         0x42    

#define         FOODCOURT_BYTE1          0x0E    
#define         FOODCOURT_BYTE2          0x46    

#define         PLAYGROUND_BYTE1         0x0C    
#define         PLAYGROUND_BYTE2         0x42    

#define         PENTHOUSE_BYTE1          0x0C
#define         PENTHOUSE_BYTE2          0x09   

#define         RESTAURANT_BYTE1         0x7F
#define         RESTAURANT_BYTE2         0x0F

#define         LOBBY_BYTE1              0x7F
#define         LOBBY_BYTE2              0x47

#define         POOL_BYTE1               0x0C
#define         POOL_BYTE2               0x47

#define         FLOOR01_BYTE1            0x7F
#define         FLOOR01_BYTE2            0x79

#define         FLOOR02_BYTE1            0x7F
#define         FLOOR02_BYTE2            0x24

#define         FLOOR03_BYTE1            0x7F
#define         FLOOR03_BYTE2            0x30

#define         FLOOR04_BYTE1            0x7F
#define         FLOOR04_BYTE2            0x19

#define         FLOOR05_BYTE1            0x7F
#define         FLOOR05_BYTE2            0x12

#define         FLOOR06_BYTE1            0x7F
#define         FLOOR06_BYTE2            0x02

#define         FLOOR07_BYTE1            0x7F
#define         FLOOR07_BYTE2            0x78

#define         FLOOR08_BYTE1            0x7F
#define         FLOOR08_BYTE2            0x00

#define         FLOOR09_BYTE1            0x7F
#define         FLOOR09_BYTE2            0x10

#define         FLOOR10_BYTE1            0x79
#define         FLOOR10_BYTE2            0x20

#define         FLOOR11_BYTE1            0x79
#define         FLOOR11_BYTE2            0x79

#define         FLOOR12_BYTE1            0x79
#define         FLOOR12_BYTE2            0x24

#define         FLOOR13_BYTE1            0x79
#define         FLOOR13_BYTE2            0x30

#define         FLOOR14_BYTE1            0x79
#define         FLOOR14_BYTE2            0x19

#define         FLOOR15_BYTE1            0x79
#define         FLOOR15_BYTE2            0x12

#define         FLOOR16_BYTE1            0x79
#define         FLOOR16_BYTE2            0x02

#define         FLOOR17_BYTE1            0x79
#define         FLOOR17_BYTE2            0x78

#define         FLOOR18_BYTE1            0x79
#define         FLOOR18_BYTE2            0x00

#define         FLOOR19_BYTE1            0x79
#define         FLOOR19_BYTE2            0x10

#define         FLOOR20_BYTE1            0x24
#define         FLOOR20_BYTE2            0x20

#define         FLOOR21_BYTE1            0x24
#define         FLOOR21_BYTE2            0x79

#define         FLOOR22_BYTE1            0x24
#define         FLOOR22_BYTE2            0x24

#define         FLOOR23_BYTE1            0x24
#define         FLOOR23_BYTE2            0x30

#define         FLOOR24_BYTE1            0x24
#define         FLOOR24_BYTE2            0x19

#define         FLOOR25_BYTE1            0x24
#define         FLOOR25_BYTE2            0x12

#define         FLOOR26_BYTE1            0x24
#define         FLOOR26_BYTE2            0x02

#define         FLOOR27_BYTE1            0x24
#define         FLOOR27_BYTE2            0x78

#define         FLOOR28_BYTE1            0x24
#define         FLOOR28_BYTE2            0x00

#define         FLOOR29_BYTE1            0x24
#define         FLOOR29_BYTE2            0x10

#define         FLOOR30_BYTE1            0x30
#define         FLOOR30_BYTE2            0x20

#define         FLOOR31_BYTE1            0x30
#define         FLOOR31_BYTE2            0x79

#define         FLOOR32_BYTE1            0x30
#define         FLOOR32_BYTE2            0x24

#define         FLOOR33_BYTE1            0x30
#define         FLOOR33_BYTE2            0x30

#define         FLOOR34_BYTE1            0x30
#define         FLOOR34_BYTE2            0x19

#define         FLOOR35_BYTE1            0x30
#define         FLOOR35_BYTE2            0x12

#define         FLOOR36_BYTE1            0x30
#define         FLOOR36_BYTE2            0x02

#define         FLOOR37_BYTE1            0x30
#define         FLOOR37_BYTE2            0x78

#define         FLOOR38_BYTE1            0x30
#define         FLOOR38_BYTE2            0x00

#define         FLOOR39_BYTE1            0x30
#define         FLOOR39_BYTE2            0x10

#define         FLOOR40_BYTE1            0x19
#define         FLOOR40_BYTE2            0x40



