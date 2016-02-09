/* OLLO PIR sensor Read
 
 connect Temperature Sensor Module to port 2. 
 
 You can buy PIR Sensor DYNAMIXEL in ROBOTIS-SHOP
 http://www.robotis-shop-en.com/?act=shop_en.goods_view&GS=2438&GC=GD080304 
 //위 링크 수정
 
 You can also find all information 
 http://support.robotis.com/
 
               Compatibility
 CM900                  X
 OpenCM9.04             O
 
 created 16 Nov 2012
 by ROBOTIS CO,.LTD.
 */

#include <OLLO.h>
OLLO myOLLO;

void setup(){
  myOLLO.begin(2,PIR_SENSOR);//OLLO PIR Module must be connected at port 2.

}
void loop(){
  SerialUSB.print("PIR Read = ");
  SerialUSB.println(myOLLO.read(2, PIR_SENSOR));
  delay(100); 
}





