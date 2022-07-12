#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include "uart.h"

/*
Target platform: ATMega32u4.

This program captures the duration of high PWM pulses on INT0 (PD0) pin.
Recorded pulse duration values are output over UART.
*/

#define BLINK_DDR DDRB
#define BLINK_DDB_PIN DDB5
#define BLINK_PORT PORTB
#define BLINK_PIN PB5

#define PWM_IN_INT_VECT INT0_vect
#define PWM_IN_PIN_REG PIND
#define PWM_IN_PIN PD0
#define PWM_IN_TCNT TCNT1

#define PWM_IN2_INT_VECT INT1_vect
#define PWM_IN2_PIN_REG PIND
#define PWM_IN2_PIN PD1
#define PWM_IN2_TCNT TCNT3

#define PWM_OUT_PORT PORTD
#define PWM_OUT_PIN PD4
#define PWM_OUT_DDR DDRD
#define PWM_OUT_DD_PIN DDD4

volatile uint16_t pwm_in_1_value = 0;
volatile uint8_t pwm_in_1_updated = 0;
volatile uint16_t pwm_in_2_value = 0;
volatile uint8_t pwm_in_2_updated = 0;

ISR(PWM_IN_INT_VECT) {
  if (PWM_IN_PIN_REG & (1 << PWM_IN_PIN)) {
    PWM_IN_TCNT = 0; // Reset PWM in timer
  } else {
    pwm_in_1_value = PWM_IN_TCNT;
    pwm_in_1_updated = 1;
  }
}

ISR(PWM_IN2_INT_VECT) {
  if (PWM_IN2_PIN_REG & (1 << PWM_IN2_PIN)) {
    PWM_IN2_TCNT = 0; // Reset PWM in timer
  } else {
    pwm_in_2_value = PWM_IN2_TCNT;
    pwm_in_2_updated = 1;
  }
}

void StartTimers() {
  TCCR1B |= (1 << CS10); // Enable timer 1 with no prescaler
  TCCR3B |= (1 << CS30); // Enable timer 3 with no prescaler
}

void SetupInterrupts() {
  EICRA |= (1 << ISC00); // Select interrupts on any edge for INT0
  EIMSK |= (1 << INT0); // Enable Interrupts for INT0

  EICRA |= (1 << ISC10); // Select interrupts on any edge for INT1
  EIMSK |= (1 << INT1); // Enable Interrupts for INT1

  sei();
}

int main(void) {
  SetupUart();
  EnableUartTransmission();
  SendStringToUart((char*)"Starting up...\r\n");
  
  StartTimers();
  SetupInterrupts();

  BLINK_DDR |= (1 << BLINK_DDB_PIN);

  while (1) {
    BLINK_PORT |= (1 << BLINK_PIN);
    _delay_us(1234);

    BLINK_PORT &= ~(1 << BLINK_PIN);
    _delay_us(18500);

    if (pwm_in_1_updated) {
      Print((pwm_in_1_value - 34) >> 4);
      SendStringToUart((char*)" us\r\n");
      pwm_in_1_updated = 0;
    }
    if (pwm_in_2_updated) {
      Print((pwm_in_2_value - 34) >> 4);
      SendStringToUart((char*)" us\r\n");
      pwm_in_2_updated = 0;
    }
  }
}