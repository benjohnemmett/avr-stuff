#include <avr/io.h>
#include <util/delay.h>

#define PIN_OUT PB2

int main() {
    DDRB |= (1 << PIN_OUT);

    while (1) {
        PORTB |= (1 << PIN_OUT);
        _delay_ms(200);
        PORTB &= ~(1 << PIN_OUT);
        _delay_ms(300);
    }
}
