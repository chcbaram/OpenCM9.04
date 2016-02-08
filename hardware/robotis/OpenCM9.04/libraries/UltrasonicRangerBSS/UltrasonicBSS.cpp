/*
Ultrasonic Library by Ha Tae-Kwon, Oh Seung-Min
refer to Martin S. Mason's
*/
#include "wirish.h"
#include "UltrasonicBSS.h"
Ultrasonic::Ultrasonic(byte trigPin, byte echoPin)
{
  attachInterrupt(trigPin,timer_start,FALLING); 
  attachInterrupt(echoPin,timer_stop,FALLING); 
  _trigPin = trigPin;
  _echoPin = echoPin;
}

float Ultrasonic::readDistance()
//Distance in cm between 1 and 530. 
{
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(990);
  delay(39); // total 40ms

  return distance;
}

void Ultrasonic::timer_start()
{
  startTime = micros();
}

void Ultrasonic::timer_stop()
{
  echoTime = micros()-startTime;
  if(echoTime>39000)
  echoTime=39000;
  distance = timeDistanceConvert(echoTime, Celsius);
}