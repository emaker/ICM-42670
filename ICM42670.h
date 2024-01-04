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
#define ICM42670_REG_PWR_MGMT0      (0x1F)

// Calibration
// GYRO
#define ICM42670_CONFIG_GYRO_2k_DPS     (0b00000000)
#define ICM42670_CONFIG_GYRO_1k_DPS     (0b00100000)
#define ICM42670_CONFIG_GYRO_500_DPS    (0b01000000)
#define ICM42670_CONFIG_GYRO_250_DPS    (0b01100000)
// ACCEL
#define ICM42670_CONFIG_ACCEL_16_G      (0b00000000)
#define ICM42670_CONFIG_ACCEL_8_G       (0b00100000)
#define ICM42670_CONFIG_ACCEL_4_G       (0b01000000)
#define ICM42670_CONFIG_ACCEL_2_G       (0b01100000)
// RATE
#define ICM42670_CONFIG_RATE_1p6_kHz    (0b00000101)
#define ICM42670_CONFIG_RATE_800_Hz     (0b00000110)
#define ICM42670_CONFIG_RATE_400_Hz     (0b00000111)
#define ICM42670_CONFIG_RATE_200_Hz     (0b00001000)
#define ICM42670_CONFIG_RATE_100_Hz     (0b00001001)
#define ICM42670_CONFIG_RATE_50_Hz      (0b00001010)
#define ICM42670_CONFIG_RATE_25_Hz      (0b00001011)
#define ICM42670_CONFIG_RATE_12p5_Hz    (0b00001100)

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} sensorXYZ;

typedef struct {
    float x;
    float y;
    float z;
} sensorFloatXYZ;  

// Class

class ICM42670 {
    public:
        bool begin(uint8_t addr = ICM42670_DEFAULT_ADDRESS, TwoWire *theWire = &Wire);
        uint8_t whoami();
        bool sensorConf();
        bool startAccel(uint8_t scale, uint8_t freq);
        bool startGyro(uint8_t rate, uint8_t freq);
        sensorXYZ getAccel();
        sensorFloatXYZ getGyro();
        uint16_t getTemp();
    private:
        TwoWire *_wire;
        uint8_t _addr;
        uint16_t accelCalib = 0;
        float gyroCalib = 0;
        bool write(uint8_t reg, uint8_t *buffer, uint8_t len);
        bool readRegister(uint8_t reg, uint8_t *buffer, uint8_t len = 1);
        // uint16_t read2Reg(uint8_t reg); 
};

#endif