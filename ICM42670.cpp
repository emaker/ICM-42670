#include <Arduino.h>
#include <ICM42670.h>

// not sure what this does yet.
ICM42670::~ICM42670() {
    if (i2c_dev) 
        delete i2c_dev;
}


bool ICM42670::begin(uint8_t addr, TwoWire *theWire) {
    if (i2c_dev)
        delete i2c_dev;
    i2c_dev = new Adafruit_I2CDevice(addr, theWire);
    if (!i2c_dev->begin())
        return false;
    
    // /* Check Connection */
    // uint8_t deviceid = getDeviceID();
    // if (deviceid != ICM42670_DEFAULT_DEVICE_ID) {
    //    return false; 
    // }

    return true;
}

uint8_t ICM42670::getDeviceID() {
    return readRegister(WHO_AM_I_REG);
}

void ICM42670::writeRegister(uint8_t reg, uint8_t value) {
    uint8_t buffer[2] = {reg, value};
    i2c_dev->write(buffer, 2);
}

uint8_t ICM42670::readRegister(uint8_t reg) {
    uint8_t buffer[1] = {reg};
    i2c_dev->write_then_read(buffer, 1, buffer, 1);
    return buffer[0];
}

int16_t ICM42670::read16(uint8_t reg) {
    uint8_t buffer[2] = {reg};
    i2c_dev->write_then_read(buffer, 1, buffer, 2);
    return uint16_t(buffer[1]) << 8 | uint16_t(buffer[0]);  
}

bool ICM42670::getEvent(sensors_event_t *event) {
    return false;
}

void ICM42670::getSensor(adafruit_sensor_t *sensor) {
    int i = 1;
}
