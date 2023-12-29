#include <Arduino.h>
#include <ICM42670.h>


bool ICM42670::begin(uint8_t addr, TwoWire *theWire) {
    TwoWire *_wire = theWire; 
    uint8_t _addr = addr;
    uint8_t whoAmI = whoami();
    if (whoAmI == ICM42670_WHO_AM_I) {
        return true;
    } else {
        return false;
    }
}

uint8_t ICM42670::whoami() {
    // read WHO_AM_I_REG
    uint8_t buffer[1];
    readRegister(WHO_AM_I_REG, buffer);
    return buffer[0];
}

bool ICM42670::writeToRegister(uint8_t reg, uint8_t value) {
    uint8_t buffer[2] = {reg, value};
    uint8_t length = 2;
    _wire->beginTransmission(_addr);
    if (_wire->write(buffer, length) != length) {
        return false;
    }
    if (_wire->endTransmission(true) != 0) {
        return false;
    }
    return true;
}

bool ICM42670::writeRegister(uint8_t reg) {
    uint8_t buffer[1] = {reg};
    uint8_t length = 1;
    _wire->beginTransmission(_addr);
    if (_wire->write(buffer, length) != length) {
        return false;
    }
    if (_wire->endTransmission(true) != 0) {
        return false;
    }
    return true;
}

bool ICM42670::readRegister(uint8_t reg, uint8_t *buffer) {
    // write the register to read from
    if (!writeRegister(reg)) {
        return false;
    }
    // read from the register
    _wire->requestFrom((int)_addr, (int)1);
    while (_wire->available()) {
        buffer[0] = _wire->read();
    }
    return true;
}
