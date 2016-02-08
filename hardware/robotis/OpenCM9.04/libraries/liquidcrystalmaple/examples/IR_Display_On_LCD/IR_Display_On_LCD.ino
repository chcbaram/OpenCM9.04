/*
 Display IR Sensor Data on LCD
 
 
 Created by ROBOTIS,.CO LTD. 14 Jan 2014
 */

#include <LiquidCrystal.h>
#include <OLLO.h>
OLLO myOLLO;

LiquidCrystal lcd(16, 17, 18, 19, 20, 21);

void setup() {
  lcd.begin(16, 2);
  lcd.print("OpenCM9.04");
  myOLLO.begin(1, IR_SENSOR);
}
void loop() {
  lcd.setCursor(0, 1);
  lcd.print(myOLLO.read(1, IR_SENSOR),DEC);
  lcd.print("   ");
  delay(300);
}









