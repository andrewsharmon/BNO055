/*************************************************** 
  This is an example for the BNO055 
 ****************************************************/

#include <Wire.h> 
#include <BNO055.h>


  BNO055 imu;

void setup() 
{
  Serial.begin(9600);
  
 
   if (!imu.begin(imu.NDOF, imu.NORMAL_MODE )){
    Serial.println("unable to initialize the chip, or it isnt ready. I'll give it a sec and try anyway!");
    delay(30);
  }
}

void loop() 
{
  imu.readEuler();
  Serial.print("X: "); Serial.print((float)imu.EulerData.x);   Serial.print(" ");
  Serial.print("Y: "); Serial.print((float)imu.EulerData.y);   Serial.print(" ");
  Serial.print("Z: "); Serial.println((float)imu.EulerData.z); Serial.print(" ");
  delay(100);
}
