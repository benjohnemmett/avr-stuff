#ifndef BAUD
#define BAUD 9600
#endif

#include <avr/io.h>
#include <util/setbaud.h>

void SetupUart();
void EnableUartTransmission();
void EnableUartReceive();
void SendByteToUart(uint8_t data);
void SendBytesToUart(uint8_t* bytes, uint8_t length);
void SendStringToUart(char* string);
void Print(uint8_t value);
void Print(uint16_t value);
uint8_t ReceiveByteFromUart();
