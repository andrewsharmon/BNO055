/**************************************************
  This is a library for the BNO055
 **************************************************/

#include <BNO055.h>

/*************************************************************************
 CONSTRUCTOR
 *************************************************************************/


BNO055::BNO055(void) {
  // use i2c
}

bool BNO055::begin(BNO055Mode_t md, BNO055DataRateMode_t spd, byte addr)
{
  Wire.begin();
  mode = md;
  address = addr;
  dataSpeed = spd;
  message= 0x00;
    
     
  /* Make sure we have the correct chip ID. This checks
     for correct address and that the IC is properly connected */
    delay(100);
  if (read8(BNO055_REGISTER_CHIP_ID) != BNO055_ID) //if it is, great it is already booted
  {
      //maybe we are hung up (restart during data transfer)
      
          while((read8(BNO055_REGISTER_CHIP_ID) != BNO055_ID)){  //super hack, but seems to work
              
              digitalWrite(A5,LOW);
              pinMode(A5,OUTPUT);
              delay(1);
              pinMode(A5,INPUT);
              delay(1);
              
          
      }
            if (read8(BNO055_REGISTER_CHIP_ID) != BNO055_ID)//wont get here now, it will just hang above
      {
    return false;
      }
  }
    write8(BNO055_REGISTER_OPR_MODE, CONFIGMODE); //Go to config mode if not there
    delay(25); //mode switch delay
write8(BNO055_REGISTER_SYS_TRIGGER, 0b00100000); //reset the sensor
while (read8(BNO055_REGISTER_CHIP_ID) != BNO055_ID) //wait for boot
{
    delay(10);
}
    delay(50);

  // Ues a heck of a lot of defaults for now... dont even use the passed modes


  /* set a base mode (normal power mode, fastest/NDOF, manually packed for now) and start! */
 
    
    write8(BNO055_REGISTER_PWR_MODE, NORMAL_POWER_MODE);
    delay(1);
    write8(BNO055_REGISTER_OPR_MODE, NDOF|FASTEST_MODE);
    //delay(1);
    //write8(BNO055_REGISTER_UNIT_SEL, 0x10000000); //try android mode
    
    
    //give sensor time to change modes
    delay(50);
    
    //if (read8(BNO055_REGISTER_SYS_STATUS) != 0x00 )
   // {
   // return false;
 // }


  return true;
}

/***************************************************************************
 PUBLIC FUNCTIONS
 ***************************************************************************/
void BNO055::readEuler()
{ 
  uint8_t xhi, xlo, ylo, yhi, zlo, zhi;

  
    Wire.beginTransmission(address);
    // Make sure to set address auto-increment bit
    Wire.write(BNO055_REGISTER_EUL_DATA_X_LSB);
    Wire.endTransmission();
    Wire.requestFrom(address, (byte)6);
    
    // Wait around until enough data is available
    while (Wire.available() < 6);
    
    xlo = Wire.read();
    xhi = Wire.read();
    ylo = Wire.read();
    yhi = Wire.read();
    zlo = Wire.read();
    zhi = Wire.read();

    // Shift values to create properly formed integer (low byte first)
  EulerData.x = (xlo | (xhi << 8));
  EulerData.y = (ylo | (yhi << 8));
  EulerData.z = (zlo | (zhi << 8));
  
        //raw for now, figure scale later
     // data.x *= ??;
     // data.y *= ??;
     // data.z *= ??;
    

}

void BNO055::readLinAcc()
{
    uint8_t xhi, xlo, ylo, yhi, zlo, zhi;
    
    
    Wire.beginTransmission(address);
    // Make sure to set address auto-increment bit
    Wire.write(BNO055_REGISTER_LIA_DATA_X_LSB);
    Wire.endTransmission();
    Wire.requestFrom(address, (byte)6);
    
    // Wait around until enough data is available
    while (Wire.available() < 6);
    
    xlo = Wire.read();
    xhi = Wire.read();
    ylo = Wire.read();
    yhi = Wire.read();
    zlo = Wire.read();
    zhi = Wire.read();
    
    // Shift values to create properly formed integer (low byte first)
    LinAccData.x = (xlo | (xhi << 8));
    LinAccData.y = (ylo | (yhi << 8));
    LinAccData.z = (zlo | (zhi << 8));
    
    //raw for now, figure scale later
    // data.x *= ??;
    // data.y *= ??;
    // data.z *= ??;
    
}

void BNO055::readQua()
{
    uint8_t whi,wlo,xhi, xlo, ylo, yhi, zlo, zhi;
    
    
    Wire.beginTransmission(address);
    // Make sure to set address auto-increment bit
    Wire.write(BNO055_REGISTER_QUA_DATA_W_LSB);
    Wire.endTransmission();
    Wire.requestFrom(address, (byte)8);
    
    // Wait around until enough data is available
    while (Wire.available() < 8);
    
    wlo = Wire.read();
    whi = Wire.read();
    xlo = Wire.read();
    xhi = Wire.read();
    ylo = Wire.read();
    yhi = Wire.read();
    zlo = Wire.read();
    zhi = Wire.read();
    
    // Shift values to create properly formed integer (low byte first) then scale (1qua=2^14lsb)
    QuaData.w = (wlo | (whi << 8))/16384.0;
    QuaData.x = (xlo | (xhi << 8))/16384.0;
    QuaData.y = (ylo | (yhi << 8))/16384.0;
    QuaData.z = (zlo | (zhi << 8))/16384.0;

    
}

void BNO055::calcAbsLinAcc()  //uses last loaded QuaData and LinAccData.  ie, make sure reads for those have been called...
{
    float a1,b1,c1, d1, a2, b2, c2, d2, ra,rb,rc,rd,den; //RAM waste, but helps make it look cleaner
    
    //stuff my quaternions and acceleration vectors into some variables to operate on them
    //specifically calc q^-1.  Note, sensor seems to send the inverse.
    den=  pow(QuaData.w,2)+pow(QuaData.x,2)+pow(QuaData.y,2)+pow(QuaData.z,2); // the passed quaternion 'should' be good, but just in case check
    
    if (den<1.01 && den>.99)  //close enough lets save some processing 
    {
        a1=QuaData.w;
        b1=QuaData.x;   //not negative because of how sensor sends the values
        c1=QuaData.y;   //not negative because of how sensor sends the values
        d1=QuaData.z;   //not negative because of how sensor sends the values
       
    }else{ //oh well, time to divide some floats
        a1=QuaData.w/den;
        b1=QuaData.x/den;   //not negative because of how sensor sends the values
        c1=QuaData.y/den;   //not negative because of how sensor sends the values
        d1=QuaData.z/den;   //not negative because of how sensor sends the values
    }
    //load accel vector V
    a2=0;
    b2=LinAccData.x;
    c2=LinAccData.y;
    d2=LinAccData.z;
    
    // time to Hamilton it up! (q^-1 * V)
    ra=a1*a2-b1*b2-c1*c2-d1*d2;
    rb=a1*b2 + b1*a2 + c1*d2 - d1*c2;
    rc=a1*c2 - b1*d2 + c1*a2 + d1*b2;
    rd=a1*d2 + b1*c2 - c1*b2 + d1*a2;
    
    //swap some vars
    //first invert q
    a2=a1;
    b2=-b1;
    c2=-c1;
    d2=-d1;
    //now move the result
    a1=ra;
    b1=rb;
    c1=rc;
    d1=rd;
    
    
    //Hamilton it up again! (result*q)
    ra=a1*a2-b1*b2-c1*c2-d1*d2;
    rb=a1*b2 + b1*a2 + c1*d2 - d1*c2;
    rc=a1*c2 - b1*d2 + c1*a2 + d1*b2;
    rd=a1*d2 + b1*c2 - c1*b2 + d1*a2;
    
    
 //finally (probably many clock cycles later) set the final values
    AbsLinAccData.x = rb;
    AbsLinAccData.y = rc;
    AbsLinAccData.z = rd;
    
    
}




void BNO055::getInfo()
{
    SystemStatusCode = read8(BNO055_REGISTER_SYS_STATUS);
   SelfTestStatus = read8(BNO055_REGISTER_ST_RESULT);
   SystemError = read8(BNO055_REGISTER_SYS_ERR);
}

/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/
void BNO055::write8(BNO055Registers_t reg, byte value)
{
    // use i2c
    Wire.beginTransmission(address);
    Wire.write((byte)reg);
    Wire.write(value);
    Wire.endTransmission();
  }

byte BNO055::read8(BNO055Registers_t reg)
{
  byte value;

  
    // use i2c
    Wire.beginTransmission(address);
    Wire.write((byte)reg);
    Wire.endTransmission();
    Wire.requestFrom(address, (byte)1);
    value = Wire.read();
    Wire.endTransmission(false);

  return value;
}



