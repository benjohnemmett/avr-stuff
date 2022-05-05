F_CPU = 8000000
MCU=atmega328p
CC = avr-gcc

blink.hex: blink.o
	$(CC) -mmcu=$(MCU) blink.o -o blink.elf
	avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex

%.o: %.cpp
	$(CC) -Os -mmcu=$(MCU) -c $< -o $@ -DF_CPU=$(F_CPU)

.PHONY: flash
flash: blink.hex
	avrdude -p $(MCU) -c usbasp -U flash:w:blink.hex:i

.PHONY: clean
clean:
	rm -f *.o *.elf *.hex