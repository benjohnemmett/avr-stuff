#include <avr/io.h>
#include <util/twi.h>

bool DeviceIsConnected(uint8_t deviceId);
void I2CSendStart();
void I2CWaitUntilStartIsSent();
void I2CSendSlaveAddress(uint8_t address);
void I2CWaitUntilSlaveAddressIsSent();
bool I2CAddressWasAcked();
void I2CSendStop();
