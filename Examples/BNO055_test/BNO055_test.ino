/*************************************************** 
  This is an example for the BNO055 
 ****************************************************/

#include <Wire.h> 
#include <BNO055.h>


  BNO055 imu;

void setup() 
{
  Serial.begin(115200);
  
 
   if (!imu.begin(imu.NDOF, imu.NORMAL_MODE )){
    Serial.println("unable to initialize the chip, or it isnt ready. I'll give it a sec and try anyway!");
    delay(30);
  }
 delay(1000);
 imu.getInfo();
 Serial.print("status code: ");Serial.println(imu.SystemStatusCode);
 Serial.print("Selftest results: ");Serial.println(imu.SelfTestStatus);
 Serial.print("System Error code: ");Serial.println(imu.SystemError);
}

void loop() 
{
  imu.readEuler();
  Serial.print("X: "); Serial.print((float)imu.EulerData.x,6);   Serial.print(" ");
  Serial.print("Y: "); Serial.print((float)imu.EulerData.y,6);   Serial.print(" ");
  Serial.print("Z: "); Serial.println((float)imu.EulerData.z,6); Serial.print(" ");
  delay(100);
}
