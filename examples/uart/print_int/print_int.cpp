#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

void PrintUint8Values() {
    for (uint8_t i = 0; i < 255; i += 1) {
        Print(i);
        SendStringToUart((char*)"\r\n");
        _delay_ms(100);
    }
}

void PrintFibonacci() {
    uint16_t j = 1;
    uint16_t k = 1;
    Print(j);
    SendStringToUart((char*)"\r\n");
    Print(k);
    SendStringToUart((char*)"\r\n");
    while (k+j > k) {
        uint16_t k_ = k;
        k = j+k;
        j = k_;

        Print(k);
        SendStringToUart((char*)"\r\n");

        _delay_ms(100);
    }
}   

int main() {
    SetupUart();
    EnableUartTransmission();

    while (1) {
        PrintUint8Values();
        PrintFibonacci();
    }
}