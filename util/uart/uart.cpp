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

void EnableUartTransmission(){
    UCSR0B |= (1 << TXEN0);
}

void EnableUartReceive() {
    UCSR0B |= (1 << RXEN0);
}

void SendByteToUart(uint8_t data){
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

uint8_t ReceiveByteFromUart() {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}
