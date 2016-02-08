/*
http://robotsource.org/bs/bd.php?bt=forum_CM9DeveloperWorld&bt_id=292&sca=&sfl=wr_subject&stx=ultra
noiseless 4cm to 530cm
 
You can change Celsius, at UltrasonicBSS.h.
We will add Celsius option, in sketch.
We will update more exact cm.
If it has noise, maybe a reflected wave.

Made by Ha Tae-Kwon and Oh Seung-Min.
Helped by ROBOTIS Lee Sang-Min and a guidance teacher Kim Min-Kook.
Download : https://docs.google.com/file/d/0B-yhlr8l4d2VOWx2X28yenlBQWs/edit
Question : 97htg@naver.com
Under Koean is more exact.
http://robotsource.org/bs/bd.php?bt=forum_CM9DeveloperWorld&bt_id=292&sca=&sfl=wr_subject&stx=ultra
를 참고 했습니다.
오류값 없이 4cm 에서 530cm 까지 가능 합니다.
UltrasonicBSS.h 에서 온도 값을 바꾸면 보다 정확한 음속으로 계산 가능 합니다.
저희는 스케치에서 바로 온도를 넣을 수 있게 만들것이며
cm 를 보다 정밀하게 측정해서 다시 만들 것입니다.
만약 오류값이 있다면 굴절되어 반사파가 들어올 가능성이 높습니다.
하태권, 오승민이 만들었습니다.
ROBOTIS  이상민 님, 지도 교사 김민국 선생님이 도와줬습니다.
다운로드 : https://docs.google.com/file/d/0B-yhlr8l4d2VOWx2X28yenlBQWs/edit
질문 : 97htg@naver.com
*/

#include <UltrasonicBSS.h>

Ultrasonic sonicSensor(8,7);  //Specify Trig and Echo pins (Trig,Echo)  

void setup() {
  SerialUSB.begin();                             // start the serial port
}

void loop() {
  SerialUSB.print("Distance ");
  SerialUSB.println(sonicSensor.readDistance());  //Read and Display the Distance
  delay(40);
}




