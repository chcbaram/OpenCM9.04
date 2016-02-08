/*
This example shows how to transfer data using i2c interface.
OpenCM9.04 operates as i2c master device, UNO operates as i2c slave.
You can also find sketch code implemented as slave device for Arduino UNO 

Master device : OpenCM9.04
Slave device : Arduino UNO

*/


#include <Wire.h> //I2C library

void setup()
{
  Wire.begin(14,15);                              // init I2C pin
  SerialUSB.begin();                             // USB Serial init 
  SerialUSB.attachInterrupt(userinput);   //USB interrupt
}
// USB interrupt for sending data using i2c
void userinput(byte* databuff, byte datalength)    
{  
  char cc[12];
  char adatalength[12];
  char accint[12];
  char accfra[12];      
  double doublecc=0;  
  
  //make string from input data
  for(unsigned int i=0; i < datalength+1;i++)
  {    
    cc[i] =(char)databuff[i];
    if(i==datalength)
    {
      cc[i] = 0;//null input for the end of chracter array
    }
  }
    delay(10);
  
  //convert to double type for string
  doublecc=atof((char*)databuff);
    
  //separates integer and fractional
  int ccint=(int)doublecc; 
  int ccfra=pow(10,datalength)*(doublecc-(int)doublecc);
  
  SerialUSB.print("Chracter array of Input data is ");
  SerialUSB.println(cc); 
  SerialUSB.print("Double variable of Input data is ");
  SerialUSB.println(doublecc,datalength); 
  SerialUSB.print("Length of data = ");
  SerialUSB.println(datalength); 
  SerialUSB.print("The Integer part is ");
  SerialUSB.println(ccint); 
  SerialUSB.print("For Fragment data ");
  SerialUSB.println(ccfra); 
  SerialUSB.println("");

  //length and integer, the fractional part is converted to a string
  //for I2C data transmission 
  itoa(datalength,adatalength,10);
  itoa(ccint,accint,10);
  itoa(ccfra,accfra,10);

  //i2c transfer data 
  Wire.beginTransmission(4);  // open i2c address 4디바이스주소 4 로의 I2C 통신 열기
  Wire.write(cc); // send string data
  Wire.write(" ");
  Wire.write(adatalength); 
  Wire.write(" ");
  Wire.write(accint); 
  Wire.write(" ");
  Wire.write(accfra); 
  Wire.write(" ");
  Wire.endTransmission(); 
  
}

void loop()
{
  delay(50);
}

/*
//The below codes are i2c slave device for Arduino UNO
//you can use it on UNO boards.
#include <Wire.h> 
int led = 13;
  
void setup()
{
  Wire.begin(4);                 // set up i2c
  Wire.onReceive(receiveEvent);   // attach receive event similar interrupt
  Serial.begin(9600);             // init Serial device
  pinMode(led, OUTPUT);        // init LED port
}

void loop() // LED blinking
{
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)  
  delay(25);
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(25);
}
// i2c receiving event when data coming from master device(OpenCM9.04)
void receiveEvent(int howMany)
{
    while(Wire.available())   // when data is available
   {
   char c = Wire.read();     // read data
   Serial.print(c);           // print to Serial port
   }
   Serial.println("");  
}

*/

