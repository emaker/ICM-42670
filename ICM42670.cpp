#include <ICM42670.h>


bool ICM42670::begin(uint8_t addr, TwoWire *theWire) {
    _wire = theWire; 
    _addr = addr;
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
    readRegister(WHO_AM_I_REG, buffer, (uint8_t) 1);
    return buffer[0];
}

bool ICM42670::write(uint8_t reg, uint8_t *buffer, uint8_t len) {
    _wire->beginTransmission(_addr);
    _wire->write(reg);
    for(uint8_t i = 0; i < len; i++) {
        _wire->write(buffer[i]);
    }
    _wire->endTransmission();
    return true;
}

bool ICM42670::readRegister(uint8_t reg, uint8_t *buffer, uint8_t len) {
    uint16_t rx_bytes = 0;

    _wire->beginTransmission(_addr);
    _wire->write(reg);
    _wire->endTransmission(false);
    rx_bytes = _wire->requestFrom(_addr, len);
    if (len == rx_bytes) {
        for (uint8_t i = 0; i < rx_bytes; i++) {
            buffer[i] = _wire->read();
        }
        return true;
    } else {
        return false;
    }
}
