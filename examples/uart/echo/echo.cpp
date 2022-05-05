#include "uart.h"

#define NEW_LINE_CHAR 10
#define CARRIAGE_RETURN_CHAR 13

int main() {
    SetupUart();
    EnableUartTransmission();
    EnableUartReceive();

    while(1) {
        uint8_t received = ReceiveByteFromUart();
        SendByteToUart(received);
        SendByteToUart(CARRIAGE_RETURN_CHAR);
        SendByteToUart(NEW_LINE_CHAR);
    }
}
