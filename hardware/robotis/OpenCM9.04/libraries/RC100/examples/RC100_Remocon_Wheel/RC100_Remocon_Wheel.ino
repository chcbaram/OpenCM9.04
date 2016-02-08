/* Dynamixel wheel mode using RC-100
 
  Demonstrates communication the OpenCM9.04 and RC100 with  init as BT-210/BT-110A/Zigbee-110A mode
  RC100 is a remote controller with built-in IR module
  IR Receiver can be connected to 4 pin communication port and controlled by RC-100
  You can buy it the link below.(Korea only)
  [RC-100] Controller like joystick
  
                   Compatibility
 CM900                  O
 OpenCM9.04             O
 
           Dynamixel Compatibility
               Ax    MX      Rx    XL-320    Pro
 CM900          O      O      O        O      X
 OpenCM9.04     O      O      O        O      X
 **** OpenCM9.04 MX-Series and Pro-Series in order to drive should be OpenCM 485EXP board ****
 
 created 16 Nov 2012
 by ROBOTIS CO,.LTD.
 */

#include <RC100.h>
RC100 Controller;

#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP

#define ID_NUM_1 1
#define ID_NUM_2 2

Dynamixel Dxl(DXL_BUS_SERIAL1);

void setup() {
  // Dynamixel 2.0 Protocol -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps  
  Dxl.begin(3);  
  
  pinMode(BOARD_LED_PIN, OUTPUT);
  Controller.begin(1); // RC100 init as BT-210/BT-110A/Zigbee-110A mode
  Dxl.wheelMode(1);
  Dxl.wheelMode(2);
}
int RcvData =0;

void loop() {

  if(Controller.available()){
    RcvData = Controller.readData();
    SerialUSB.print("RcvData = ");
    SerialUSB.println(RcvData);

    if(RcvData & RC100_BTN_U){
      Dxl.goalSpeed(ID_NUM_1, 500);        //Dynamixel 1 -> Left motor
      Dxl.goalSpeed(ID_NUM_2, 500+1023);   //Dynamixel 2 -> Right motor
    }
    else if(RcvData & RC100_BTN_D){
      Dxl.goalSpeed(ID_NUM_1, 500+1023);   //Dynamixel 1 -> Left motor
      Dxl.goalSpeed(ID_NUM_2, 500);        //Dynamixel 2 -> Right motor
    }
    else if(RcvData & RC100_BTN_L){
      Dxl.goalSpeed(ID_NUM_1, 500+1023);   //Dynamixel 1 -> Left motor
      Dxl.goalSpeed(ID_NUM_2, 500+1023);   //Dynamixel 2 -> Right motor
    }      
    else if(RcvData & RC100_BTN_R){
      Dxl.goalSpeed(ID_NUM_1, 500);        //Dynamixel 1 -> Left motor
      Dxl.goalSpeed(ID_NUM_2, 500);        //Dynamixel 2 -> Right motor
    } 
    else{
      Dxl.goalSpeed(ID_NUM_1, 0);          //Dynamixel 1 -> Left motor
      Dxl.goalSpeed(ID_NUM_2, 0);          //Dynamixel 2 -> Right motor
    }    
  }
}
/* defines for RC100 in the RC100.h
 Controller.begin(1);  ----> Bluetooth Mode
 Controller.begin(2);  ----> IR Mode
 
 #define RC100_BTN_U		(1)
 #define RC100_BTN_D		(2)
 #define RC100_BTN_L		(4)
 #define RC100_BTN_R		(8)
 #define RC100_BTN_1		(16)
 #define RC100_BTN_2		(32)
 #define RC100_BTN_3		(64)
 #define RC100_BTN_4		(128)
 #define RC100_BTN_5		(256)
 #define RC100_BTN_6		(512)
 */



