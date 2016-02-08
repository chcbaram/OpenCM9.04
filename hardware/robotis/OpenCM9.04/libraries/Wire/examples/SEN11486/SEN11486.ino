/*
  Sparkfun SEN11486 a MPU-9150 9 degree of Freedom IMU
  
  Connection:
  SEN11486    CM 904
  Pin
  1 GND      J12 4 GND
  2 VCC      J12 3 3.3V
  3 SDA      J13 12 D16 (PB3)
  4 SDL      J13 11 D17 (PB4)
  5 ESD
  6 ESC
  7 COUT
  8 CIN
  9 AD0
  10 FSYNC
  11 INT
  
  The following reads from a MPU-9150 sensors raw data.
  ax,ay,az stores the Accelrometer axies value
  gx,gy,gz stores the gyroscope axies value
  mx,my,mz stores the magnetometer axies value
  
  The following are an exaction from I2Cdev and MPU6050 from Sparkfun's site.
  Dated 10/3/2011 by Jeff Rowberg

   edited by woeimun 30/4/2014
 
*/
#include <Wire.h>
#include "mpu9150.h"
#define MPU9150_addr  0x68
#define BUFFER_LENGTH 32
#define LED_ON 0
#define LED_OFF 1
// 1000ms default read timeout (modify with "I2Cdev::readTimeout = [ms];")
#define DEFAULT_READ_TIMEOUT     1000

uint8 buffer[20];
int ax, ay, az;
int gx, gy, gz;
int mx, my, mz;
bool blinkState = false;

void setup()
{
  pinMode(BOARD_LED_PIN, OUTPUT);
  digitalWrite(BOARD_LED_PIN, LED_OFF);

  Wire.begin(16,17);    //i2c bus init SDA->16, SCL->17

  SerialUSB.begin();
  SerialUSB.println("Initializing I2C devices");
  //disable sleep
  MPU9150_writeBit(MPU9150_addr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, 0);
  //select reference clock
  MPU9150_writeBits(MPU9150_addr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, MPU6050_CLOCK_PLL_XGYRO);
  //select gyro range
  MPU9150_writeBits(MPU9150_addr, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, MPU6050_GYRO_FS_250);
  //select accelrometer range
  MPU9150_writeBits(MPU9150_addr, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, MPU6050_ACCEL_FS_2);
  //enable I2C bypass for magnetometer
  MPU9150_writeBit(MPU9150_addr, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_I2C_BYPASS_EN_BIT, 1);
  //set rate
  buffer[0]=0xf0;
  MPU9150_write(MPU9150_addr, MPU6050_RA_SMPLRT_DIV, 1, buffer);
  
    // verify connection
    SerialUSB.println("Testing device connections...");
    SerialUSB.println(testConnection(MPU9150_addr) ? "MPU6050 connection successful" : "MPU6050 connection failed");

  delay(100);
}

void loop()
{
  //read accelrometer and gyro 
  MPU9150_read(MPU9150_addr, MPU6050_RA_ACCEL_XOUT_H, 14, buffer,DEFAULT_READ_TIMEOUT);
    ax = (((int16)buffer[0]) << 8) | buffer[1];
    ay = (((int16)buffer[2]) << 8) | buffer[3];
    az = (((int16)buffer[4]) << 8) | buffer[5];
    gx = (((int16)buffer[8]) << 8) | buffer[9];
    gy = (((int16)buffer[10]) << 8) | buffer[11];
    gz = (((int16)buffer[12]) << 8) | buffer[13];
  //read magnetometer
  buffer[0]=0x01;
  MPU9150_write(MPU9150_RA_MAG_ADDRESS, 0x0A, 1, buffer); //enable the magnetometer
  delay(10);
  MPU9150_read(MPU9150_RA_MAG_ADDRESS, MPU9150_RA_MAG_XOUT_L, 6, buffer,DEFAULT_READ_TIMEOUT);
  mx=(((int16)buffer[0]) << 8) | buffer[1];
  my=(((int16)buffer[2]) << 8) | buffer[3];
  mz=(((int16)buffer[4]) << 8) | buffer[5];
  
    SerialUSB.print("a/g/m:\t");
    SerialUSB.print(ax); SerialUSB.print("\t");
    SerialUSB.print(ay); SerialUSB.print("\t");
    SerialUSB.print(az); SerialUSB.print("\t");
    SerialUSB.print(gx); SerialUSB.print("\t");
    SerialUSB.print(gy); SerialUSB.print("\t");
    SerialUSB.print(gz); SerialUSB.print("\t");
    SerialUSB.print(mx); SerialUSB.print("\t");
    SerialUSB.print(my); SerialUSB.print("\t");
    SerialUSB.println(mz);
    SerialUSB.println();

    blinkState = !blinkState;
    digitalWrite(BOARD_LED_PIN, blinkState);

  delay(100);
}

uint8 MPU9150_read(uint8 devAddr,uint8 regAddr, uint8 length, uint8* buf, uint16 timeout)
{
    uint8 count = 0;
    unsigned long t1 = millis();

    for (unsigned char k = 0; k < length; k += min(length, BUFFER_LENGTH))
    {
        Wire.beginTransmission(devAddr);
        Wire.write(regAddr);
        Wire.endTransmission();
        Wire.beginTransmission(devAddr);
        Wire.requestFrom(devAddr, (uint8)min(length - k, BUFFER_LENGTH));
        
        while (Wire.available() && (timeout == 0 || millis() - t1 < timeout))
        {
            buf[count++] = Wire.read();           
        }
    }

    // check for timeout
    if (timeout > 0 && millis() - t1 >= timeout && count < length)
    {
        count = -1; // timeout
    }
    return count;
}

bool MPU9150_write(uint8 devAddr,uint8 regAddr,uint8 length, uint8* data)
{
     uint8 status = 0;

    Wire.beginTransmission(devAddr);
    Wire.write((uint8) regAddr); // send address

    for (uint8 i = 0; i < length; i++)
    {
        Wire.write((uint8) data[i]);
    }

    status = Wire.endTransmission();

}

bool MPU9150_writeBit(uint8 devAddr,uint8 regAddr,uint8 bitNum, uint8 data)
{
    uint8 b;
    MPU9150_read(devAddr, regAddr, 1, &b,DEFAULT_READ_TIMEOUT);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return MPU9150_write(devAddr, regAddr, 1, &b);  
}

bool MPU9150_writeBits(uint8 devAddr, uint8 regAddr, uint8 bitStart, uint8 length, uint8 data)
{
    //      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
    uint8 b;

    if (MPU9150_read(devAddr, regAddr, 1, &b,DEFAULT_READ_TIMEOUT) != 0)
    {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte

        return MPU9150_write(devAddr, regAddr, 1, &b);
    }

    return false;
}

int8 MPU9150_readBits(uint8 devAddr, uint8 regAddr, uint8 bitStart, uint8 length, uint8 *data)
{
    // 01101001 read byte
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    //    010   masked
    //   -> 010 shifted
    uint8 count, b;
    if ((count = MPU9150_read(devAddr, regAddr, 1, &b,DEFAULT_READ_TIMEOUT)) != 0)
    {
        uint8 mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return count;
}

bool testConnection(uint8 devAddr) 
{
  uint8 b[1];
  MPU9150_readBits(devAddr, MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, b);
  return b[0]==0x34 ;
}


