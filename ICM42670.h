#ifndef ICM42670_H

#define ICM42670_H

// Includes
#include <Adafruit_I2CDevice.h>
#include <Adafruit_Sensor.h>

// I2C Address
#define ICM42670_DEFAULT_ADDRESS    (0x68)
#define ICM42670_DEFAULT_DEVICE_ID  (0x67)
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

// Calibration

// Class
class ICM42670 : public Adafruit_Sensor {
    public:
        ~ICM42670();

        bool begin(uint8_t addr = ICM42670_DEFAULT_ADDRESS, TwoWire *theWire);
        uint8_t getDeviceID(void);
        bool getEvent(sensors_event_t*);
        void getSensor(adafruit_sensor_t);

        // register r/w
        uint8_t readRegister(uint8_t reg);
        int16_t read16(uint8_t reg);
        void writeRegister(uint8_t reg, uint8_t value);
    private:
        Adafruit_I2CDevice *i2c_dev = NULL;
};
#endif