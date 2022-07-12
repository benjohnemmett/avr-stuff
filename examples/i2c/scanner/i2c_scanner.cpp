#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "uart.h"

/*
    This program scans for connected I2C devices. When a device is found, it's ID is written to the UART.
    An LED can also be connected to PB0. Fast blink while scanning, slow blink indicates that a device was found. 
*/

int main() {
    DDRB |= (1 << PB0);
    SetupUart();
    EnableUartTransmission();
    
    while (1) {
        SendStringToUart((char*)"Starting Scan\r\n");
        for (uint8_t id = 0; id < 128; id++) {
            PORTB &= ~(1 << PB0);
            _delay_ms(30);

            PORTB |= (1 << PB0);
            if (DeviceIsConnected(id)) {
                Print(id);
                SendStringToUart((char*)"\r\n");
                for (uint8_t i = 0; i < 3; i++) {
                    _delay_ms(200);
                    PORTB &= ~(1 << PB0);
                    _delay_ms(200);
                    PORTB |= (1 << PB0);
                }
            }

            PORTB |= (1 << PB0);
            _delay_ms(30);
        }
    }
}