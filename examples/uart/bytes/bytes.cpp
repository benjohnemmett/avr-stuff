#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

#define STARTING_CHAR 97
#define NEW_LINE_CHAR 10
#define CARRIAGE_RETURN_CHAR 13

uint8_t bytes[] = {0x54, 0x68, 0x65, 0x73, 0x65, 0x20, 0x61, 0x72, 
                    0x65, 0x20, 0x73, 0x6F, 0x6D, 0x65, 0x20, 0x62, 
                    0x79, 0x74, 0x65, 0x73, 0x0A, 0x0D};
uint8_t bytes2[] = {'H', 'e', 'r', 'e', ' ', 'a', 'r', 'e',
                    ' ', 's', 'o', 'm', 'e', ' ', 'm', 'o',
                    'r', 'e', ' ', 'b', 'y', 't', 'e', 's',
                    '\r', '\n'};
char string[] = "This is a null terminated char array.\r\n\0";

uint8_t bytes_length = 22;
uint8_t bytes2_length = 26;
                
int main() {
    SetupUart();
    EnableUartTransmission();

    while (1) {
        SendBytesToUart(bytes, bytes_length);
        _delay_ms(500);
        
        SendBytesToUart(bytes2, bytes2_length);
        _delay_ms(500);

        SendStringToUart(string);
        _delay_ms(500);
    }
}