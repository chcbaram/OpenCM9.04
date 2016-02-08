/* EEPROM Erase 
 
 Demonstrates how to use flash memory as EEPROM in CM900, CM9.04 board.
 
 New bootoader is needed to operate EEPROM library example.
 Because old bootloader always erase after flash address 0x08003000
 So, the data saved will be deleted after downloading new codes to CM900, CM9.04 board
 Please check the bootloader codes in gitHub and robotsource.org
 
                 Compatibility
 CM900                  O
 OpenCM9.04             O

 created 16 Nov 2012
 by ROBOTIS CO,.LTD.
 */

#include "EEPROM.h"
int i;
EEPROM CM_EEPROM;
void setup(){  
  CM_EEPROM.begin();
  //erase page 0, 1
  //instead of eraseAll(), -> CM_EEPROM.erase(0), CM_EEPROM.erase(1)
  CM_EEPROM.eraseAll();
  //CM_EEPROM.erase(0); 
  //CM_EEPROM.erase(1);
}
void loop(){
  //after erasing data
  //just blinking LED.
  toggleLED();
  delay(100);
}

