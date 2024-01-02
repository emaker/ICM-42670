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
    // set gyro low nois
    // set accel low nois
    uint8_t sensorConf = 0b00001111;
    if (!write(ICM42670_REG_PWR_MGMT0, &sensorConf, 1))
        return false;
    return true;
}

uint8_t ICM42670::whoami() {
    uint8_t buffer[1];
    readRegister(WHO_AM_I_REG, buffer, (uint8_t) 1);
    return buffer[0];
}

bool ICM42670::startAccel(uint8_t scale, uint8_t freq) {
    uint8_t accelConf = scale | freq;
    // check if these settings are already stored
    uint8_t accelConfOld;
    if (!readRegister(ICM42670_REG_ACCEL_CONFIG0, &accelConfOld, 1))
        return false;
    if (accelConfOld == accelConf) 
        return true;
    // write new conf
    if (!write(ICM42670_REG_ACCEL_CONFIG0, &accelConf, 1))
        return false;
    return true;    
}

bool ICM42670::startGyro(uint8_t rate, uint8_t freq) {
    uint8_t gyroConf = rate | freq;
    // check if theses settings are alreay stored
    uint8_t gyroConfOld;
    if (!readRegister(ICM42670_REG_GYRO_CONFIG0, &gyroConfOld, 1))
        return false;
    if (gyroConfOld == gyroConf)
        return true;
    // write new conf
    return write(ICM42670_REG_GYRO_CONFIG0, &gyroConf, 1);
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
