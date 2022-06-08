#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
                
int main() {
    SetupUart();
    EnableUartTransmission();

    while (1) {

        for (uint8_t i = 0; i < 256; i++) {
            Print(i);
            SendStringToUart((char*)"\r\n");
            _delay_ms(300);
        }
    }
}