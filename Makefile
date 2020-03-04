# default fuses
#FUSE_E = 0xF9
#FUSE_H = 0xDF


# fuse low byte = 1110 0010 = 0xE2
# [ CKDIV8 ][ CKOUT ][ SUT1:0 ][ CKSEL3:0 ]
# CKDIV8 = 1 (unprogrammed)
# CKOUT = 1 (unprogrammed)
# SUT1:0 = 10 -> maximum startup time
# CKSEL3:0 = 0010 -> internal 8 MHz oscillator
FUSE_L = 0xE2

# fuse high byte = 1101 1001 = 0xD9
# [ RSTDISBL ][ DWEN ][ SPIEN ][ WDTON ][ EESAVE ][ BOOTSZ1:0 ][ BOOTRST ]
# RSTDISBL = 1 (unprogrammed) -> reset enabled
# DWEN = 1 (unprogrammed) -> debugWire disabled
# SPIEN = 0 (programmed) -> SPI programming enabled
# WDTON = 1 (unprogrammed) -> watch dog timer disabled
# EESAVE = 1 (unprogrammed) -> EEPROM not reserved
# BOOTSZ1:0 = 11 -> maximum application flash section
# BOOTRST = 1 (unprogrammed) 
FUSE_H = 0xDF 

# fuse extended byte = 1111 1111 = 0xFF
# [ - ][ BODLEVEL2:0 ]
# BODLEVEL2:0 = 111 = brown-out detection disabled
FUSE_E = 0xFF


MCU = atmega168pb
F_CPU = 8000000

DUDEFLAGS = -c avrisp2 -P usb -p $(MCU) -v
CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DDEBUG_LEVEL=0 
OBJECTS = bin/main.o bin/i2c_master.o bin/screen.o


help:
	@echo "Hello World"

test:
	avrdude $(DUDEFLAGS)

fuses:
	avrdude $(DUDEFLAGS) -U lfuse:w:$(FUSE_L):m -U hfuse:w:$(FUSE_H):m -U efuse:w:$(FUSE_E):m

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
