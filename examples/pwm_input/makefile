F_CPU=16000000
CC=avr-g++
MCU=atmega32u4

UTIL = ../../util

OBJS = uart.o 
INC = -I$(UTIL)/uart/

.PHONY: all
all: pwm_input.hex

flash: pwm_input.hex
	avrdude -p atmega32u4 -c usbasp -U flash:w:pwm_input.hex:i

pwm_input.hex: pwm_input.o $(OBJS)
	$(CC) -mmcu=$(MCU) $(OBJS) pwm_input.o -o pwm_input.elf
	avr-objcopy -j .text -j .data -O ihex pwm_input.elf pwm_input.hex

uart.o: $(UTIL)/uart/uart.cpp
	$(CC) -Os -mmcu=$(MCU) $(INC) -c $< -o $@ -DF_CPU=$(F_CPU)

%.o: %.cpp
	$(CC) -Os -mmcu=$(MCU) $(INC) -c $< -o $@ -DF_CPU=$(F_CPU)

.PHONY: clean
clean:
	rm -f *.elf *.o *.obj  *.hex
