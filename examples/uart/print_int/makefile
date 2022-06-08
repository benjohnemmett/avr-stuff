F_CPU = 8000000
MCU=atmega328p
CC = avr-gcc

OBJS = ../../../util/uart/uart.o
INC = ../../../util/uart/

print_int.hex: print_int.o $(OBJS)
	$(CC) -mmcu=$(MCU) $(OBJS) print_int.o -o print_int.elf
	avr-objcopy -j .text -j .data -O ihex print_int.elf print_int.hex

%.o: %.cpp
	$(CC) -Os -mmcu=$(MCU) -I$(INC) -c $< -o $@ -DF_CPU=$(F_CPU)

.PHONY: flash
flash:
	avrdude -p $(MCU) -c usbasp -U flash:w:print_int.hex:i

.PHONY: clean
clean:
	rm -f *.o *.elf *.hex
	rm -f $(OBJS)