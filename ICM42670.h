#ifndef ICM42670_H

#define ICM42670_H

#include <Arduino.h>
#include <Wire.h>

// I2C Address
#define ICM42670_DEFAULT_ADDRESS    (0x68)
#define ICM42670_WHO_AM_I  (0x67)
// Registers
// Data
#define ICM42670_REG_TEMP_DATA1     (0x09)
#define ICM42670_REG_TEMP_DATA0     (0x0A)
#define ICM42670_REG_ACCEL_DATA_X1  (0x0B)
#define ICM42670_REG_ACCEL_DATA_X0  (0x0C)
#define ICM42670_REG_ACCEL_DATA_Y1  (0x0D)
#define ICM42670_REG_ACCEL_DATA_Y0  (0x0E)
#define ICM42670_REG_ACCEL_DATA_Z1  (0x0F)
#define ICM42670_REG_ACCEL_DATA_Z0  (0x10)
#define ICM42670_REG_GYRO_DATA_X1   (0x11)
#define ICM42670_REG_GYRO_DATA_X0   (0x12)
#define ICM42670_REG_GYRO_DATA_Y1   (0x13)
#define ICM42670_REG_GYRO_DATA_Y0   (0x14)
#define ICM42670_REG_GYRO_DATA_Z1   (0x15)
#define ICM42670_REG_GYRO_DATA_Z0   (0x16)
//Config
#define ICM42670_REG_DRIVE_CONFIG2  (0x04)
#define ICM42670_REG_GYRO_CONFIG0   (0x20)
#define ICM42670_REG_GYRO_CONFIG1   (0x23)
#define ICM42670_REG_ACCEL_CONFIG0  (0x21)
#define ICM42670_REG_ACCEL_CONFIG1  (0x24)
#define ICM42670_REG_TEMP_CONFIG0   (0x22)
#define WHO_AM_I_REG                (0x75)

// Calibration

// Class

class ICM42670 {
    public:
        bool begin(uint8_t addr = ICM42670_DEFAULT_ADDRESS, TwoWire *theWire = &Wire);
        uint8_t whoami();
        bool startAccel(uint16_t odr, uint16_t fsr);
    private:
        TwoWire *_wire;
        uint8_t _addr;
        bool write(uint8_t reg, uint8_t *buffer, uint8_t len);
        bool readRegister(uint8_t reg, uint8_t *buffer, uint8_t len);
        // uint16_t read2Reg(uint8_t reg); 
};

#endif