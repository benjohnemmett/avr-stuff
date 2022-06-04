F_CPU = 8000000
MCU=atmega328p
CC = avr-gcc

OBJS = ../../../util/uart/uart.o
INC = ../../../util/uart/

bytes.hex: bytes.o $(OBJS)
	$(CC) -mmcu=$(MCU) $(OBJS) bytes.o -o bytes.elf
	avr-objcopy -j .text -j .data -O ihex bytes.elf bytes.hex

%.o: %.cpp
	$(CC) -Os -mmcu=$(MCU) -I$(INC) -c $< -o $@ -DF_CPU=$(F_CPU)

.PHONY: flash
flash:
	avrdude -p $(MCU) -c usbasp -U flash:w:bytes.hex:i

.PHONY: clean
clean:
	rm -f *.o *.elf *.hex
	rm -f $(OBJS)