MCU     = atmega328p
F_CPU   = 16000000UL
PORT    = /dev/ttyUSB0
CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

all: hex flash

hex:
	avr-gcc $(CFLAGS) -o main.bin main.c 
	avr-objcopy -O ihex -R .eeprom main.bin main.hex

flash:
	avrdude -c arduino -p $(MCU) -b 115200 -P $(PORT) -U flash:w:main.hex:i

clean:
	rm -f main.bin main.hex
