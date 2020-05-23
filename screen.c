#include <avr/pgmspace.h>
#include <util/delay.h>

#include <string.h> // required for `memset`
#include <stdlib.h> // required for `malloc`

#include "screen.h"
#include "i2c_master.h"

void screen_command(uint8_t cmd) {
	i2c_start(SCREEN_ADDR);
	i2c_write(0x00);
	i2c_write(cmd);
	i2c_stop();
}

void screen_command_list(const uint8_t *c, uint8_t n) {
	i2c_start(SCREEN_ADDR);
	i2c_write(0x00);

	uint8_t bytesOut = 1;
	while (n--) {
		if (bytesOut >= WIRE_MAX) {
			// flow control, end transmission and start a new one
			i2c_stop();
			i2c_start(SCREEN_ADDR);
			i2c_write(0x00);
			// reset counter
			bytesOut = 1;
		}
		// send byte from command list
		i2c_write(pgm_read_byte(c++));
		++bytesOut;
	}
	// end transmission
	i2c_stop();
}

void screen_display() {
	static const uint8_t PROGMEM dlist1[] = {
		0x22,
		0,		// Page start address
		0xFF,	// Page end (not really, but works here)
		0x21,
		0 
	}; // Column start address
	screen_command_list(dlist1, sizeof(dlist1));
	screen_command(SCREEN_WIDTH - 1);

	uint16_t count = BUFFER_SIZE;
	uint8_t *ptr = buffer;


	i2c_start(SCREEN_ADDR);
	i2c_write(0x40);
	uint8_t bytesOut = 1;
	while(count--) {
		if(bytesOut >= WIRE_MAX) {
			i2c_stop();
			i2c_start(SCREEN_ADDR);
			i2c_write(0x40);
			bytesOut = 1;
		}
		i2c_write(*ptr++);
		++bytesOut;
	}
	i2c_stop();
}

void screen_clear() {
	memset(buffer, 0, BUFFER_SIZE);
}

void screen_off() {
	screen_command(SCREEN_DISPLAYOFF);
}

uint8_t screen_begin() {
	if (!buffer) {
		// allocate memory
		buffer = (uint8_t *) malloc(BUFFER_SIZE);
	}
	// allocation failed
	if (!buffer) return 1;

	// clear buffer
	screen_clear();
	return 0;
}

void screen_on() {
	// display reset high
	PORTD |= 1 << PD0;
	_delay_ms(1);
	// display reset low	
	PORTD &= ~(1 << PD0);
	_delay_ms(10);
	// reset back to high
	PORTD |= 1 << PD0;

	static const uint8_t PROGMEM init1[] = {
		SCREEN_DISPLAYOFF,									 // 0xAE
		SCREEN_SETDISPLAYCLOCKDIV,					 // 0xD5
		0x80,																 // the suggested ratio 0x80
		SCREEN_SETMULTIPLEX };							 // 0xA8
	screen_command_list(init1, sizeof(init1));
	screen_command(SCREEN_HEIGHT - 1);

	static const uint8_t PROGMEM init2[] = {
		SCREEN_SETDISPLAYOFFSET,						 // 0xD3
		0x0,																	// no offset
		SCREEN_SETSTARTLINE | 0x0,					 // line #0
		SCREEN_CHARGEPUMP };								 // 0x8D
	screen_command_list(init2, sizeof(init2));

	screen_command(0x14);

	static const uint8_t PROGMEM init3[] = {
		SCREEN_MEMORYMODE,									 // 0x20
		0x00,																 // 0x0 act like ks0108
		SCREEN_SEGREMAP | 0x1,
		SCREEN_COMSCANDEC };
	screen_command_list(init3, sizeof(init3));

	screen_command(SCREEN_SETCOMPINS);
	screen_command(0x12);
	screen_command(SCREEN_SETCONTRAST);
	screen_command(0xCF);

	screen_command(SCREEN_SETPRECHARGE); // 0xd9
	screen_command(0xF1);
	
	static const uint8_t PROGMEM init5[] = {
		SCREEN_SETVCOMDETECT,							 // 0xDB
		0x40,
		SCREEN_DISPLAYALLON_RESUME,				 // 0xA4
		SCREEN_NORMALDISPLAY,							 // 0xA6
		SCREEN_DEACTIVATE_SCROLL,
		SCREEN_DISPLAYON
	};								 // Main screen turn on
	screen_command_list(init5, sizeof(init5));
}

inline void screen_set_pixel(uint8_t x, uint8_t y, uint8_t mode) {
	if (mode) {
		// set pixel white
		buffer[x + (y / 8) * SCREEN_WIDTH] |= 1 << (y & 7);
	} else {
		// set pixel black
		buffer[x + (y / 8) * SCREEN_WIDTH] &= ~(1 << (y & 7));
	}
}

void screen_draw_character(const uint8_t *bitmap, uint8_t num, const uint8_t height, const uint8_t width, uint8_t offset_x, uint8_t offset_y, uint8_t invert) {
	uint8_t byte = 0;
	uint16_t memoffset = num * (height * width / 8);
	for (uint8_t y = 0; y < height; ++y) {
		for (uint8_t x = 0; x < width; ++x) {
			if (x % 8 == 0) {
				// load new byte
				byte = pgm_read_byte(bitmap + memoffset);
				byte ^= invert;
				++memoffset;
			}
			
			screen_set_pixel(offset_x + x, offset_y + y, (byte & (1 << (7 - x % 8))));
		}
	}
}

