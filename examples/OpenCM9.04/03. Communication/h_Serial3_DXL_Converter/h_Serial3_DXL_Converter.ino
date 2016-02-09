/*SerialUSB_Serial2_Converter
 
 This example is convert from serial2 to USB.
 CM-900, OpenCM9.04 has a port(J9) connected directly to Serial2.
 If some data is coming from Serial2, it is sent to serialUSB.
 On the contrary, all data coming from serialUSB is sent to Serial2.
 
 
 You can connect the below products to J9 Connector in CM-900, OpenCM9.04
 [BT-110A] or [BT-110A Set]
 http://www.robotis-shop-kr.com/goods_detail.php?goodsIdx=875
 [ZIG-110A Set]
 http://www.robotis-shop-kr.com/goods_detail.php?goodsIdx=405
 [LN-101] USART communication and download tool in CM-100
 http://www.robotis-shop-kr.com/goods_detail.php?goodsIdx=348
 
 You can also find all information about ROBOTIS products
 http://support.robotis.com/
 
                   Compatibility
 CM900                  O
 OpenCM9.04             O

 created 16 Nov 2012
 by ROBOTIS CO,.LTD.
 */
  byte SerialBuffer1[256];
  byte SerialBuffer3[256];
  byte SerialBufferWritePointer1 = 0, SerialBufferReadPointer1 = 0;
  byte SerialBufferWritePointer3 = 0, SerialBufferReadPointer3 = 0;
  Dynamixel Dxl(1);
void setup(){
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(1);                              // Initialize DXL bus. 57600bps.
  Serial3.begin(115200);                    // Initialize UART3 (Raspberry Pi 2) as 115200bps.
Serial1.attachInterrupt(serialInterrupt1);  // attach interrrupt function to DXL bus uart channel
Serial3.attachInterrupt(serialInterrupt3);  // attach interrrupt function to UART3 channel
}

void serialInterrupt3(byte buffer){
  SerialBuffer3[SerialBufferWritePointer3++] = buffer;  // save received byte to Raspberry Pi 2 rx buffer
}

void serialInterrupt1(byte buffer){
  SerialBuffer1[SerialBufferWritePointer1++] = buffer;  // save received byte to DXL rx buffer
}

void loop(){
  if(SerialBufferWritePointer3 != SerialBufferReadPointer3)  // if any new data in Raspberry Pi 2 rx buffer, send it to DXL bus.
  {
    Dxl.writeRaw(SerialBuffer3[SerialBufferReadPointer3++]);
  //delay(1);
  }
  if(SerialBufferWritePointer1 != SerialBufferReadPointer1)  // if any new data in DXL rx buffer, send it to Raspberry Pi 2.
  {
    Serial3.print(SerialBuffer1[SerialBufferReadPointer1++],BYTE); 
  //delay(10);
  }
}

