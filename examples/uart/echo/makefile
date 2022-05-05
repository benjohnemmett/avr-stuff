F_CPU = 8000000
MCU=atmega328p
CC = avr-gcc

OBJS = ../../../util/uart/uart.o
INC = ../../../util/uart/

echo.hex: echo.o $(OBJS)
	$(CC) -mmcu=$(MCU) $(OBJS) echo.o -o echo.elf
	avr-objcopy -j .text -j .data -O ihex echo.elf echo.hex

%.o: %.cpp
	$(CC) -Os -mmcu=$(MCU) -I$(INC) -c $< -o $@ -DF_CPU=$(F_CPU)

.PHONY: flash
flash: echo.hex
	avrdude -p $(MCU) -c usbasp -U flash:w:echo.hex:i

.PHONY: clean
clean:
	rm -f *.o *.elf *.hex
	rm -f $(OBJS)