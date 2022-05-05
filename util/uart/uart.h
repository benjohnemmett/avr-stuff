#ifndef BAUD
#define BAUD 9600
#endif

#include <avr/io.h>
#include <util/setbaud.h>

void SetupUart();
void EnableUartTransmission();
void EnableUartReceive();
void SendByteToUart(uint8_t data);
uint8_t ReceiveByteFromUart();
