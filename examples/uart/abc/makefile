F_CPU = 8000000
MCU=atmega328p
CC = avr-gcc

OBJS = ../../../util/uart/uart.o
INC = ../../../util/uart/

abc.hex: abc.o $(OBJS)
	$(CC) -mmcu=$(MCU) $(OBJS) abc.o -o abc.elf
	avr-objcopy -j .text -j .data -O ihex abc.elf abc.hex

%.o: %.cpp
	$(CC) -Os -mmcu=$(MCU) -I$(INC) -c $< -o $@ -DF_CPU=$(F_CPU)

.PHONY: flash
flash:
	avrdude -p $(MCU) -c usbasp -U flash:w:abc.hex:i

.PHONY: clean
clean:
	rm -f *.o *.elf *.hex
	rm -f $(OBJS)