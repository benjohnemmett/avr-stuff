#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

#define STARTING_CHAR 97
#define NEW_LINE_CHAR 10
#define CARRIAGE_RETURN_CHAR 13

uint8_t nextChar;

int main() {
    SetupUart();
    EnableUartTransmission();

    while (1) {
        SendByteToUart(STARTING_CHAR + nextChar);
        nextChar++;

        if (nextChar >= 26) {
            SendByteToUart(CARRIAGE_RETURN_CHAR);
            SendByteToUart(NEW_LINE_CHAR);
            nextChar = 0;
        }

        _delay_ms(100);
    }
}