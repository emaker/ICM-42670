#include <ICM42670.h>


bool ICM42670::begin(uint8_t addr, TwoWire *theWire) {
    _wire = theWire; 
    _addr = addr;
    uint8_t whoAmI = whoami();
    Serial.println(whoAmI);
    if (whoAmI == ICM42670_WHO_AM_I) {
        return true;
    } else {
        return false;
    }
}

uint8_t ICM42670::whoami() {
    uint8_t buffer[1];
    if (readRegister(WHO_AM_I_REG, buffer)) {
        return buffer[0];
    } 
    return -1;
}

bool ICM42670::sensorConf() {
    uint8_t sensorConf = 0b00001111;
    return write(ICM42670_REG_PWR_MGMT0, &sensorConf, 1);
}

bool ICM42670::startAccel(uint8_t scale, uint8_t freq) {
    uint8_t accelConf = scale | freq;
    // check if these settings are already stored
    uint8_t accelConfOld;
    if (!readRegister(ICM42670_REG_ACCEL_CONFIG0, &accelConfOld))
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
    if (!readRegister(ICM42670_REG_GYRO_CONFIG0, &gyroConfOld))
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
    uint8_t rx_bytes = 0;

    _wire->beginTransmission(_addr);
    _wire->write(reg);
    uint8_t err = _wire->endTransmission();
    if (err!= 0) {
        Serial.println(err);   
        return false;
    }
    rx_bytes = _wire->requestFrom(_addr, len);
    if (rx_bytes != len) {
        Serial.println("No data");
        return false;
    }    
    Serial.println("Here?!"); 
    for (uint8_t i = 0; i < len; i++) {
        Serial.println("Here?");    
        buffer[i] = _wire->read();
    }
    Serial.println("Here!");
    return true;

}
