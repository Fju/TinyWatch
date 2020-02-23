F_CPU   = 8000000

# default fuses
#FUSE_E = 0xF9
#FUSE_L = 0x62
#FUSE_H = 0xDF

MCU = atmega168pb
DUDEFLAGS = -c avrisp2 -P usb -p $(MCU) -v
CFLAGS  = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DDEBUG_LEVEL=0 
OBJECTS = bin/main.o bin/i2c_master.o bin/screen.o


help:
	@echo "Hello World"

test:
	avrdude $(DUDEFLAGS)

fuses:
	avrdude $(DUDEFLAGS) -U lfuse:w:0xE2:m
compile:
	avr-gcc $(CFLAGS) -c i2c_master.c -o bin/i2c_master.o
	avr-gcc $(CFLAGS) -c screen.c -o bin/screen.o
	avr-gcc $(CFLAGS) -c main.c -o bin/main.o
	avr-gcc $(CFLAGS) $(OBJECTS) -o bin/main.elf
	avr-objcopy -O ihex bin/main.elf bin/main.hex
	make clean

clean:
	rm $(OBJECTS) bin/main.elf

program:
	avrdude $(DUDEFLAGS) -U flash:w:bin/main.hex

erase:
	avrdude $(DUDEFLAGS) -e
