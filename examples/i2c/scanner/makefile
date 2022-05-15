F_CPU = 8000000
MCU=atmega328p
CC = avr-gcc

UTIL = ../../../util

OBJS = $(UTIL)/i2c/i2c.o $(UTIL)/uart/uart.o 
INC = -I$(UTIL)/i2c/ -I$(UTIL)/uart/

i2c_scanner.hex: i2c_scanner.o $(OBJS)
	$(CC) -mmcu=$(MCU) $(OBJS) i2c_scanner.o -o i2c_scanner.elf
	avr-objcopy -j .text -j .data -O ihex i2c_scanner.elf i2c_scanner.hex

%.o: %.cpp
	$(CC) -Os -mmcu=$(MCU) $(INC) -c $< -o $@ -DF_CPU=$(F_CPU)

.PHONY: flash
flash:
	avrdude -p $(MCU) -c usbasp -U flash:w:i2c_scanner.hex:i

.PHONY: clean
clean:
	rm -f *.o *.elf *.hex
	rm -f $(OBJS)