#include <Arduino.h>
#include <ICM42670.h>

// not sure what this does yet.
ICM42670::~ICM42670() {
    if (i2c_dev) 
        delete i2c_dev;
}

void ICM42670::writeRegister(uint8_t reg, uint8_t value) {
    uint8_t buffer[2] = {reg, value};
    i2c_dev->write(buffer, 2);
}

uint8_t ICM42670::readRegister(uint8_t reg) {
    uint8_t buffer[1] = {reg};
    i2c_dev->write(buffer, 1);
    i2c_dev->write(buffer, 1);
    return buffer[0];
}

uint16_t read16(uint8_t reg) {
    uint8_t buffer[2] = {reg};
    i2c_dev->write(buffer, 1);
    i2c_dev->read(buffer, 2);
    return uint16_t(buffer[1]) << 8 | uint16_t(buffer[0]);  
}


