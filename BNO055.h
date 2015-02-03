/***************************************************
  This is a library for the BNO055
 ****************************************************/
#ifndef __BNO055_H__
#define __BNO055_H__

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

#define BNO055_ADDRESS                (0x28)        // 0x28 com3 low 0x29 com3 high
#define BNO055_POLL_TIMEOUT           (100)         // Maximum number of read attempts
#define BNO055_ID                     (0xA0)        //pg58


class BNO055
{
  public:
    typedef enum
    {                                               // DEFAULT    TYPE
        //page0
      BNO055_REGISTER_CHIP_ID             = 0x00,   // 0x00       r
      BNO055_REGISTER_ACC_ID              = 0x01,   // 0xFB       r
      BNO055_REGISTER_MAG_ID              = 0x02,   // 0x32       r
      BNO055_REGISTER_GYR_ID              = 0x03,   // 0x0F       r
      BNO055_REGISTER_SW_REV_ID_LSB       = 0x04,   //            r        
      BNO055_REGISTER_SW_REV_ID_MSB       = 0x05,   //            r
      BNO055_REGISTER_BL_REV_ID           = 0x06,   //            r
      BNO055_REGISTER_PAGE_ID             = 0x07,   // 0x00       rw
      BNO055_REGISTER_ACC_DATA_X_LSB      = 0x08,   // 0x00       r
      BNO055_REGISTER_ACC_DATA_X_MSB      = 0x09,   // 0x00       r
      BNO055_REGISTER_ACC_DATA_Y_LSB      = 0x0A,   // 0x00       r
      BNO055_REGISTER_ACC_DATA_Y_MSB      = 0x0B,   // 0x00       r
      BNO055_REGISTER_ACC_DATA_Z_LSB      = 0x0C,   // 0x00       r
      BNO055_REGISTER_ACC_DATA_Z_MSB      = 0x0D,   // 0x00       r
      BNO055_REGISTER_MAG_DATA_X_LSB      = 0x0E,   // 0x00       r
      BNO055_REGISTER_MAG_DATA_X_MSB      = 0x0F,   // 0x00       r
      BNO055_REGISTER_MAG_DATA_Y_LSB      = 0x10,   // 0x00       r
      BNO055_REGISTER_MAG_DATA_Y_MSB      = 0x11,   // 0x00       r
      BNO055_REGISTER_MAG_DATA_Z_LSB      = 0x12,   // 0x00       r
      BNO055_REGISTER_MAG_DATA_Z_MSB      = 0x13,   // 0x00       r
      BNO055_REGISTER_GYR_DATA_X_LSB      = 0x14,   // 0x00       r
      BNO055_REGISTER_GYR_DATA_X_MSB      = 0x15,   // 0x00       r
      BNO055_REGISTER_GYR_DATA_Y_LSB      = 0x16,   // 0x00       r
      BNO055_REGISTER_GYR_DATA_Y_MSB      = 0x17,   // 0x00       r
      BNO055_REGISTER_GYR_DATA_Z_LSB      = 0x18,   // 0x00       r
      BNO055_REGISTER_GYR_DATA_Z_MSB      = 0x19,   // 0x00       r
      BNO055_REGISTER_EUL_DATA_X_LSB      = 0x1A,   // 0x00       r
      BNO055_REGISTER_EUL_DATA_X_MSB      = 0x1B,   // 0x00       r
      BNO055_REGISTER_EUL_DATA_Y_LSB      = 0x1C,   // 0x00       r
      BNO055_REGISTER_EUL_DATA_Y_MSB      = 0x1D,   // 0x00       r
      BNO055_REGISTER_EUL_DATA_Z_LSB      = 0x1E,   // 0x00       r
      BNO055_REGISTER_EUL_DATA_Z_MSB      = 0x1F,   // 0x00       r
      BNO055_REGISTER_QUA_DATA_W_LSB      = 0x20,   // 0x00       r
      BNO055_REGISTER_QUA_DATA_W_MSB      = 0x21,   // 0x00       r
      BNO055_REGISTER_QUA_DATA_X_LSB      = 0x22,   // 0x00       r
      BNO055_REGISTER_QUA_DATA_X_MSB      = 0x23,   // 0x00       r
      BNO055_REGISTER_QUA_DATA_Y_LSB      = 0x24,   // 0x00       r
      BNO055_REGISTER_QUA_DATA_Y_MSB      = 0x25,   // 0x00       r
      BNO055_REGISTER_QUA_DATA_Z_LSB      = 0x26,   // 0x00       r
      BNO055_REGISTER_QUA_DATA_Z_MSB      = 0x27,   // 0x00       r
      BNO055_REGISTER_LIA_DATA_X_LSB      = 0x28,   // 0x00       r
      BNO055_REGISTER_LIA_DATA_X_MSB      = 0x29,   // 0x00       r
      BNO055_REGISTER_LIA_DATA_Y_LSB      = 0x2A,   // 0x00       r
      BNO055_REGISTER_LIA_DATA_Y_MSB      = 0x2B,   // 0x00       r
      BNO055_REGISTER_LIA_DATA_Z_LSB      = 0x2C,   // 0x00       r
      BNO055_REGISTER_LIA_DATA_Z_MSB      = 0x2D,   // 0x00       r
      BNO055_REGISTER_GRV_DATA_X_LSB      = 0x2E,   // 0x00       r
      BNO055_REGISTER_GRV_DATA_X_MSB      = 0x2F,   // 0x00       r
      BNO055_REGISTER_GRV_DATA_Y_LSB      = 0x30,   // 0x00       r
      BNO055_REGISTER_GRV_DATA_Y_MSB      = 0x31,   // 0x00       r
      BNO055_REGISTER_GRV_DATA_Z_LSB      = 0x32,   // 0x00       r
      BNO055_REGISTER_GRV_DATA_Z_MSB      = 0x33,   // 0x00       r
      BNO055_REGISTER_TEMP                = 0x34,   // 0x00       r
      BNO055_REGISTER_CALIB_STAT          = 0x35,   // 0x00       r
      BNO055_REGISTER_ST_RESULT           = 0x36,   // xxxx1111   r
      BNO055_REGISTER_INT_STA             = 0x37,   // 000x00xx   r  pg74
      BNO055_REGISTER_SYS_CLK_STATUS      = 0x38,   // 00000000   r  pg74
      BNO055_REGISTER_SYS_STATUS          = 0x39,   // 00000000   r  pg74
      BNO055_REGISTER_SYS_ERR             = 0x3A,   // 00000000   r  pg75
      BNO055_REGISTER_UNIT_SEL            = 0x3B,   // 0xx0x000   rw pg76
      BNO055_REGISTER_OPR_MODE            = 0x3D,   // x???????   rw pg77
      BNO055_REGISTER_PWR_MODE            = 0x3E,   // xxxxxx??   rw pg78
      BNO055_REGISTER_SYS_TRIGGER         = 0x3F,   // 000xxxx0   w  pg78
      BNO055_REGISTER_TEMP_SOURCE         = 0x40,   // xxxxxx??   rw pg78
      BNO055_REGISTER_AXIS_MAP_CONFIG     = 0x41,   // xx??????   rw pg79
      BNO055_REGISTER_AXIS_MAP_SIGN       = 0x42,   // xxxxx???   rw pg79
      BNO055_REGISTER_SIC_MATRIX          = 0x43,   // xxxxxx??   ?? pg80
      BNO055_REGISTER_ACC_OFFSET_X_LSB    = 0x55,   // 0x00       rw
      BNO055_REGISTER_ACC_OFFSET_X_MSB    = 0x56,   // 0x00       rw
      BNO055_REGISTER_ACC_OFFSET_Y_LSB    = 0x57,   // 0x00       rw
      BNO055_REGISTER_ACC_OFFSET_Y_MSB    = 0x58,   // 0x00       rw
      BNO055_REGISTER_ACC_OFFSET_Z_LSB    = 0x59,   // 0x00       rw
      BNO055_REGISTER_ACC_OFFSET_Z_MSB    = 0x5A,   // 0x00       rw
      BNO055_REGISTER_MAG_OFFSET_X_LSB    = 0x5B,   // 0x00       rw
      BNO055_REGISTER_MAG_OFFSET_X_MSB    = 0x5C,   // 0x00       rw
      BNO055_REGISTER_MAG_OFFSET_Y_LSB    = 0x5D,   // 0x00       rw
      BNO055_REGISTER_MAG_OFFSET_Y_MSB    = 0x5E,   // 0x00       rw
      BNO055_REGISTER_MAG_OFFSET_Z_LSB    = 0x5F,   // 0x00       rw
      BNO055_REGISTER_MAG_OFFSET_Z_MSB    = 0x60,   // 0x00       rw
      BNO055_REGISTER_GYR_OFFSET_X_LSB    = 0x61,   // 0x00       rw
      BNO055_REGISTER_GYR_OFFSET_X_MSB    = 0x62,   // 0x00       rw
      BNO055_REGISTER_GYR_OFFSET_Y_LSB    = 0x63,   // 0x00       rw
      BNO055_REGISTER_GYR_OFFSET_Y_MSB    = 0x64,   // 0x00       rw
      BNO055_REGISTER_GYR_OFFSET_Z_LSB    = 0x65,   // 0x00       rw
      BNO055_REGISTER_GYR_OFFSET_Z_MSB    = 0x66,   // 0x00       rw
      BNO055_REGISTER_ACC_RADIUS_LSB      = 0x67,   // 0x00       rw
      BNO055_REGISTER_ACC_RADIUS_MSB      = 0x68,   // 0x00       rw
      BNO055_REGISTER_MAG_RADIUS_LSB      = 0x69,   // 0x00       rw
      BNO055_REGISTER_MAG_RADIUS_MSB      = 0x6A,   // 0x00       rw
        
        
        //page 1
        
    //BNO055_REGISTER_PAGE_ID             = 0x07,   // ??         rw //see page 0
      BNO055_REGISTER_ACC_CONFIG          = 0x08,   // 00001101   rw pg87
      BNO055_REGISTER_MAG_CONFIG          = 0x09,   // 00001011   rw pg87
      BNO055_REGISTER_GYR_CONFIG          = 0x0A,   // 00111000   rw pg88
      BNO055_REGISTER_GYR_CONFIG_1        = 0x0B,   // 00000000   rw pg88
      BNO055_REGISTER_ACC_SLEEP_CONFIG    = 0x0C,   // ????????   rw pg89
      BNO055_REGISTER_GYR_SLEEP_CONFIG    = 0x0D,   // ????????   rw pg90
      BNO055_REGISTER_INT_MSK             = 0x0F,   // 000x00xx   rw pg91
      BNO055_REGISTER_INT_EN              = 0x10,   // 000x00xx   rw pg92
      BNO055_REGISTER_ACC_AM_THRES        = 0x11,   // 00010100   rw pg92
      BNO055_REGISTER_ACC_INT_SETTINGS    = 0x12,   // 00000011   rw pg93
      BNO055_REGISTER_ACC_HG_DURATION     = 0x13,   // 00001111   rw pg93
      BNO055_REGISTER_ACC_HG_THRES        = 0x14,   // 11000000   rw pg93
      BNO055_REGISTER_ACC_NM_THRES        = 0x15,   // 00001010   rw pg93
      BNO055_REGISTER_ACC_NM_SET          = 0x16,   // x0001011   rw pg94
      BNO055_REGISTER_GYR_INT_SETTING     = 0x17,   // 00000000   rw pg95
      BNO055_REGISTER_GYR_HR_X_SET        = 0x18,   // 00000001   rw pg95
      BNO055_REGISTER_GYR_DUR_X           = 0x19,   // 00011001   rw pg96
      BNO055_REGISTER_ACC_HR_Y_SET        = 0x1A,   // 00000001   rw pg96
      BNO055_REGISTER_GYR_DUR_Y           = 0x1B,   // 00011001   rw pg96
      BNO055_REGISTER_ACC_HR_Z_SET        = 0x1C,   // 00000001   rw pg97
      BNO055_REGISTER_GYR_DUR_Z           = 0x1D,   // 00011001   rw pg97
      BNO055_REGISTER_GYR_AM_THRES        = 0x1E,   // 00000100   rw pg97
      BNO055_REGISTER_GYR_AM_SET          = 0x1F,   // 00001010   rw pg98
    } BNO055Registers_t;

    
    typedef enum
    {                                   //HW SENS POWER    SENS SIG         FUSION
                                        //  A   M   G       A   M   G       E   Q   L   G
        CONFIGMODE      = 0b00000000,   //  y   y   y       n   n   n       n   n   n   n
        ACCONLY         = 0b00000001,   //  y   n   n       y   n   n       n   n   n   n
        MAGONLY         = 0b00000010,   //  n   y   n       n   y   n       n   n   n   n
        GYROONLY        = 0b00000011,   //  n   n   y       n   n   y       n   n   n   n
        ACCMAG          = 0b00000100,   //  y   y   n       y   y   n       n   n   n   n
        ACCGYRO         = 0b00000101,   //  y   n   y       y   n   y       n   n   n   n
        MAGGYRO         = 0b00000110,   //  n   y   y       n   y   y       n   n   n   n
        AMG             = 0b00000111,   //  y   y   y       y   y   y       n   n   n   n
        IMU             = 0b00001000,   //  y   n   y       y   n   y       y   y   y   y
        COMPASS         = 0b00001001,   //  y   y   n       y   y   n       y   y   y   y
        M4G             = 0b00001010,   //  y   y   n       y   y   y       y   y   y   y
        NDOF_FMC_OFF    = 0b00001011,   //  y   y   y       y   y   y       y   y   y   y
        NDOF            = 0b00001100,   //  y   y   y       y   y   y       y   y   y   y
    } BNO055Mode_t;
    
    typedef enum
    {
        NORMAL_POWER_MODE     = 0b00000000,
        LOW_POWER_MODE        = 0b00000001,
        SUSPEND_POWER_MODE    = 0b00000010,
    } BNO055PowerModes_t;
    
    typedef enum
    {
        FASTEST_MODE    = 0b00100000,
        GAME_MODE       = 0b01000000,
        UI_MODE         = 0b01100000,
        NORMAL_MODE     = 0b10000000,
    } BNO055DataRateMode_t;

    typedef struct BNO055EulerData_s
    {
      float x;
      float y;
      float z;
    } BNO055EulerData;


    BNO055(void);

    bool begin(BNO055Mode_t md=NDOF, BNO055DataRateMode_t spd=FASTEST_MODE, byte addr=BNO055_ADDRESS);
    
    
    void readEuler(void);

    BNO055EulerData EulerData;    // Last read will be available here

  private:
    void write8(BNO055Registers_t reg, byte value);
    byte read8(BNO055Registers_t reg);
    byte address;
    BNO055DataRateMode_t dataSpeed;
    BNO055Mode_t mode;
    byte message;
};

#endif
