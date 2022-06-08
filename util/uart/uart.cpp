#include "uart.h"

#ifdef __AVR_ATmega32U4__
    #define UBRRH UBRR1H
    #define UBRRL UBRR1L
    #define UCSRA UCSR1A
    #define UCSRB UCSR1B
    #define UDR UDR1
    #define UDRE UDRE1
    #define RXC RXC1
    #define TXC TXC1
    #define RXEN RXEN1
    #define TXEN TXEN1
    #define U2X U2X1
#else
    #define UBRRH UBRR0H
    #define UBRRL UBRR0L
    #define UCSRA UCSR0A
    #define UCSRB UCSR0B
    #define UDR UDR0
    #define UDRE UDRE0
    #define RXC RXC0
    #define TXC TXC0
    #define RXEN RXEN0
    #define TXEN TXEN0
    #define U2X U2X0
#endif

void SetupUart() {
    //Set Baud using UBRR0H_VALUE & UBRR0L_VALUE macros
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;

    // setbaud.h will define USE_2X if it is needed to get timing tolerance
    #if USE_2X
    UCSRA |= (1 << U2X);
    #else
    UCSRA &= ~(1 << U2X);
    #endif
}

void EnableUartTransmission() {
    UCSRB |= (1 << TXEN);
}

void EnableUartReceive() {
    UCSRB |= (1 << RXEN);
}

void SendByteToUart(uint8_t data) {
    loop_until_bit_is_set(UCSRA, UDRE);
    UDR = data;
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
    loop_until_bit_is_set(UCSRA, RXC);
    return UDR;
}
