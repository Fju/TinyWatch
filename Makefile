F_CPU   = 8000000

#FUSE_L  = 0xE1
#FUSE_H  = 0xDD

DUDEFLAGS = -c avrisp2 -P usb -p atmega328 -v
CFLAGS  = -Wall -Os -mmcu=atmega328 -DF_CPU=$(F_CPU) -DDEBUG_LEVEL=0 
OBJECTS = bin/main.o bin/i2c_master.o


help:
	@echo "Hello World"


compile:
	avr-gcc $(CFLAGS) -c i2c_master.c -o bin/i2c_master.o
	avr-gcc $(CFLAGS) -c main.c -o bin/main.o
	avr-gcc $(CFLAGS) $(OBJECTS) -o bin/main.elf
	avr-objcopy -O ihex bin/main.elf bin/main.hex
	make clean

clean:
	rm $(OBJECTS) bin/main.elf

program:
	avrdude -c avrisp2 -p attiny45 -P usb -U flash:w:bin/main.hex

erase:
	avrdude -c avrisp2 -p attiny45 -P usb -e
