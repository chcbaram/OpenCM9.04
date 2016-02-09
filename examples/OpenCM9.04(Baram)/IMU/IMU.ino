/*
    Example for CupDrone
    Modified by Baram 2015. 8.22
*/
#include "I2Cdev.h"
#include "MPU6050.h"


MPU6050 mpu;


void setup() 
{
	HwI2C.begin();
	SerialUSB.begin();


}


void loop() 
{
	static uint32_t imuTime = micros();

	
	if( (micros() - imuTime) >= 2 )
	{
		mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
		imuTime = micros();
	}
}
