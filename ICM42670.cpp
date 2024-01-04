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
    switch (scale)
    {
    case ICM42670_CONFIG_ACCEL_16_G:
        accelCalib = 2048;
        break;
    case ICM42670_CONFIG_ACCEL_8_G:
        accelCalib = 4096;
        break;
    case ICM42670_CONFIG_ACCEL_4_G:
        accelCalib = 8192;
        break;
    case ICM42670_CONFIG_ACCEL_2_G:
        accelCalib = 16384;
        break;
    default:
        break;
    }
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
    switch (rate)
    {
    case ICM42670_CONFIG_GYRO_2k_DPS:
        gyroCalib = 16.4;
        break;
    case ICM42670_CONFIG_GYRO_1k_DPS:
        gyroCalib = 32.8;
        break;
    case ICM42670_CONFIG_GYRO_500_DPS:
        gyroCalib = 65.5;
        break;
    case ICM42670_CONFIG_GYRO_250_DPS:
        gyroCalib = 131;
        break;
    
    default:
        break;
    }
    uint8_t gyroConf = rate | freq;
    // check if theses settings are alreay stored
    uint8_t gyroConfOld;
    if (!readRegister(ICM42670_REG_GYRO_CONFIG0, &gyroConfOld))
        return false;
    if (gyroConfOld == gyroConf)
        return true;
    // write new conf
    bool res = write(ICM42670_REG_GYRO_CONFIG0, &gyroConf, 1);
    // gyro needs a few millis to reconfigure
    delay(20); 
    return res;
}

sensorXYZ ICM42670::getAccel() {
    uint8_t readBuffer[1];
    sensorXYZ sensor = {0,0,0};
    sensorXYZ raw = {0,0,0};
    // read x1 reg
    // shift <<
    // read x0 reg
    if (!readRegister(ICM42670_REG_ACCEL_DATA_X1, readBuffer))
        return sensor;
    raw.x = readBuffer[0] << 8;
    if (!readRegister(ICM42670_REG_ACCEL_DATA_X0, readBuffer))
        return sensor;
    raw.x |= readBuffer[0];
    // read y reg, -''-
    if (!readRegister(ICM42670_REG_ACCEL_DATA_Y1, readBuffer))
        return sensor;
    raw.y = readBuffer[0] << 8;
    if (!readRegister(ICM42670_REG_ACCEL_DATA_Y0, readBuffer))
        return sensor;
    raw.y |= readBuffer[0];
    // read z reg, -''-
    if (!readRegister(ICM42670_REG_ACCEL_DATA_Z1, readBuffer))
        return sensor;
    raw.z = readBuffer[0] << 8;
    if (!readRegister(ICM42670_REG_ACCEL_DATA_Z0, readBuffer))
        return sensor; 
    raw.z |= readBuffer[0];
    // return sensorXYZ
    sensor.x = (raw.x * 1000) / accelCalib;
    sensor.y = (raw.y * 1000) / accelCalib;
    sensor.z = (raw.z * 1000) / accelCalib;
    return sensor;
}

sensorXYZ ICM42670::getGyro() {
    uint8_t readBuffer[1];
    sensorXYZ sensor = {0,0,0};
    sensorXYZ raw = {0,0,0};

    // read x
    if (!readRegister(ICM42670_REG_GYRO_DATA_X1, readBuffer))
        return sensor;
    raw.x = readBuffer[0] << 8;
    if (!readRegister(ICM42670_REG_GYRO_DATA_X0, readBuffer))
        return sensor;
    raw.x |= readBuffer[0];
    
    // read y
    if (!readRegister(ICM42670_REG_GYRO_DATA_Y1, readBuffer))
        return sensor;
    raw.y = readBuffer[0] << 8;
    if (!readRegister(ICM42670_REG_GYRO_DATA_Y0, readBuffer))
        return sensor;
    raw.y |= readBuffer[0];

    // read z
    if (!readRegister(ICM42670_REG_GYRO_DATA_Z1, readBuffer))
        return sensor;
    raw.z = readBuffer[0] << 8;
    if (!readRegister(ICM42670_REG_GYRO_DATA_Z0, readBuffer))
        return sensor;
    raw.z |= readBuffer[0];

    // convert to milli degree
    sensor.x = (raw.x * 1000) / gyroCalib;
    sensor.y = (raw.y * 1000) / gyroCalib;
    sensor.z = (raw.z * 1000) / gyroCalib;
    return sensor;
}

int16_t ICM42670::getTemp() {
    uint8_t readBuffer[1];
    int16_t sensor = 0;
    int16_t raw = 0;
    // read raw
    if (!readRegister(ICM42670_REG_TEMP_DATA1, readBuffer))
        return sensor;
    raw = readBuffer[0] << 8;
    if (!readRegister(ICM42670_REG_TEMP_DATA0, readBuffer))
        return sensor;
    raw |= readBuffer[0];

    // convert to C
    sensor = (raw / 128) + 25;

    return sensor;
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
    for (uint8_t i = 0; i < len; i++) {
        buffer[i] = _wire->read();
    }
    return true;

}
