#include "i2c.h"

bool DeviceIsConnected(uint8_t deviceId) {
    I2CSendStart();
    I2CWaitUntilStartIsSent();
    I2CSendSlaveAddress(deviceId << 1);
    I2CWaitUntilSlaveAddressIsSent();
    return I2CAddressWasAcked();
}

void I2CSendStart() {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
}

void I2CWaitUntilStartIsSent() {
    while (!(TWCR & (1 << TWINT))) {}
}

void I2CSendSlaveAddress(uint8_t address) {
    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);
}

void I2CWaitUntilSlaveAddressIsSent() {
    while (!(TWCR & (1 << TWINT))) {}
}

bool I2CAddressWasAcked() {
    return (TWSR & 0xF8) == TW_MT_SLA_ACK;
}

void I2CSendStop() {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}
