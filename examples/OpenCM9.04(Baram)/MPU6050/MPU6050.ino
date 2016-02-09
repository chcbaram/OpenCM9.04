/*
    Example for CupDrone
    Modified by Baram 2015. 8.22
*/

#include "I2Cdev.h"
#include "MPU6050.h"


MPU6050 accelgyro;


int16_t ax, ay, az;
int16_t gx, gy, gz;



#define OUTPUT_READABLE_ACCELGYRO



#define LED_PIN BOARD_LED0_PIN

bool blinkState = false;

void setup() 
{
    HwI2C.begin();
    SerialUSB.begin();

    // initialize device
    SerialUSB.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    SerialUSB.println("Testing device connections...");
    SerialUSB.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
    uint32_t startTime;
    uint32_t processTime;

    startTime = micros();
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    processTime = micros() - startTime;

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);


    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        SerialUSB.print("a/g:\t");
        SerialUSB.print(ax/100); SerialUSB.print("\t");
        SerialUSB.print(ay/100); SerialUSB.print("\t");
        SerialUSB.print(az/100); SerialUSB.print("\t");
        SerialUSB.print(gx); SerialUSB.print("\t");
        SerialUSB.print(gy); SerialUSB.print("\t");
        SerialUSB.print(gz); SerialUSB.print("  "); SerialUSB.println(processTime);
    #endif

    #ifdef OUTPUT_BINARY_ACCELGYRO
        SerialUSB.write((uint8_t)(ax >> 8)); SerialUSB.write((uint8_t)(ax & 0xFF));
        SerialUSB.write((uint8_t)(ay >> 8)); SerialUSB.write((uint8_t)(ay & 0xFF));
        SerialUSB.write((uint8_t)(az >> 8)); SerialUSB.write((uint8_t)(az & 0xFF));
        SerialUSB.write((uint8_t)(gx >> 8)); SerialUSB.write((uint8_t)(gx & 0xFF));
        SerialUSB.write((uint8_t)(gy >> 8)); SerialUSB.write((uint8_t)(gy & 0xFF));
        SerialUSB.write((uint8_t)(gz >> 8)); SerialUSB.write((uint8_t)(gz & 0xFF));
    #endif

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}

