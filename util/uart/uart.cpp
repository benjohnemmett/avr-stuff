#include "uart.h"

void SetupUart() {
    //Set Baud using UBRR0H_VALUE & UBRR0L_VALUE macros
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    // setbaud.h will define USE_2X if it is needed to get timing tolerance
    #if USE_2X
    UCSR0A |= (1 << U2X0);
    #else
    UCSR0A &= ~(1 << U2X0);
    #endif
}

void EnableUartTransmission() {
    UCSR0B |= (1 << TXEN0);
}

void EnableUartReceive() {
    UCSR0B |= (1 << RXEN0);
}

void SendByteToUart(uint8_t data) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

void SendBytesToUart(uint8_t *bytes, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        SendByteToUart(bytes[i]);
    }
}

void SendStringToUart(char* string) {
    while(string[0]) {
        SendByteToUart(string[0]);
        string++;
    }
}

/*
    Input must be in the range [0 9]
*/
char DecToAscii(uint8_t dec) {
    return (char)(dec + 0x30);
}

void PrintChar(char ch) {
    SendByteToUart(ch);
}

void Print(uint8_t value) {
    uint8_t printZeros = 0;
    if (value > 99) {
        uint8_t hundreds = value / 100;
        value -= 100*hundreds;
        SendByteToUart(DecToAscii(hundreds));
        printZeros = 1;
    }
    if (value > 9) {
        uint8_t tens = value / 10;
        value -= 10*tens;
        SendByteToUart(DecToAscii(tens));
    } else if (printZeros) {
        SendByteToUart(DecToAscii(0));
    }
    SendByteToUart(DecToAscii(value));
}

uint8_t ReceiveByteFromUart() {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}
