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
    
    //give sensor time to boot
    delay(400);
    
  /* Make sure we have the correct chip ID. This checks
     for correct address and that the IC is properly connected */
  if (read8(BNO055_REGISTER_CHIP_ID) != BNO055_ID)
  {
    return false;
  }

  // Ues a heck of a lot of defaults for now... dont even use the passed modes


  /* set a base mode (normal power mode, fastest/NDOF, manually packed for now) and start! */
    write8(BNO055_REGISTER_PWR_MODE, NORMAL_POWER_MODE);
    write8(BNO055_REGISTER_OPR_MODE, NDOF|FASTEST_MODE);
    
    //give sensor time to change modes
    delay(7);
    
    if (read8(BNO055_REGISTER_SYS_STATUS) != 0x05 )
    {
    return false;
    }


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
    Wire.endTransmission();

  return value;
}

