// Ultrasonic Library by Ha Tae-Kwon, Oh Seung-Min
// refer to Martin S. Mason's
#define progress 0
#define Celsius 25 // You can change
#define timeDistanceConvert(echoTime, conversionFactor) ((echoTime-350) * (331+0.6*conversionFactor)/20000)

#ifndef UltrasonicBSS_h
#define UltrasonicBSS_h

#include "wirish.h"

volatile static long echoTime;
volatile static long startTime;
volatile static float distance;



class Ultrasonic
{
    public:
        Ultrasonic(byte trigPin, byte echoPin);
        float readDistance();
    private:
        static void timer_start();
        static void timer_stop();
        byte _trigPin;
        byte _echoPin;
       
};

#endif