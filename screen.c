#include <avr/pgmspace.h>

#include <string.h> // required for `memset`
#include <stdlib.h> // required for `malloc`

#include "screen.h"

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

	uint16_t count = 1024;//BUFFER_SIZE;
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
		i2c_write(0x69);
		++bytesOut;
	}
	i2c_stop();
}

void screen_clear() {
	memset(buffer, 0, BUFFER_SIZE);
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

	return 0;
}

inline void screen_set_pixel(uint8_t x, uint8_t y, bool color) {
	if (color) buffer[x + (y / 8) * SCREEN_WIDTH] |= 1 << (y & 7);
	else buffer[x + (y / 8) * SCREEN_WIDTH] &= ~(1 << (y & 7));
}

void screen_draw_line(uint8_t x0, int8_t y0, uint8_t x1, uint8_t y1) {
	 
	int8_t dx = abs(x1 - x0);
	int8_t sx = (x0 < x1) ? 1 : -1;
	int8_t dy = -abs(y1 - y0);
	int8_t sy = (y0 < y1) ? 1 : -1;

	int16_t err = dx + dy;
	while (1) {		
		screen_set_pixel(x0, y0, true);
		if (x0 == x1 && y0 == y1) break;

		int16_t e2 = 2 * err;
		if (e2 >= dy) {
			err += dy;
			x0 += sx;	
		}
		if (e2 <= dx) {
			err += dx;
			y0 += sy;
		}
	}
}

void screen_draw_inupiaq(uint8_t num, uint8_t offset_x, uint8_t offset_y, bool large) {
	uint8_t lower = num % 5;
	uint8_t upper = num / 5;

	static const uint8_t PROGMEM upper_lines[] = {
		// large character
		0, 14, 24,	9,
		0,	5, 24,	9,
		0,	5, 24,	0,
		// small character
		/*0,	7, 12,	5,
		0,	2, 12,	5,
		0,	2, 12,	0*/
	};

	static const uint8_t PROGMEM lower_lines[] = {
		// large character
		// 1
		0, 14, 24, 38,
		// 2
		0, 14, 12, 38,
		12, 38, 24, 19,
		// 3
		0, 14, 8, 38,
		8, 38, 16, 19,
		16, 19, 24, 38,
		// 4
		0, 14, 6, 38,
		6, 38, 12, 19,
		12, 19, 18, 38,
		18, 38, 24, 19,
		// 0
		2, 28, 12, 38,
		12, 38, 22, 28,
		22, 28, 2, 14,
		2, 28, 22, 14
	};

	uint8_t x0;
	uint8_t x1;
	uint8_t y1;
	uint8_t y0;
	uint8_t i;

	for (i = 0; i < upper; ++i) {
		x0 = pgm_read_byte(upper_lines + (i * 4 + 0)) >> (large ? 0 : 1);
		y0 = pgm_read_byte(upper_lines + (i * 4 + 1)) >> (large ? 0 : 1);
		x1 = pgm_read_byte(upper_lines + (i * 4 + 2)) >> (large ? 0 : 1);
		y1 = pgm_read_byte(upper_lines + (i * 4 + 3)) >> (large ? 0 : 1);
		
		screen_draw_line(offset_x + x0, offset_y + y0, offset_x + x1, offset_y + y1);
	}

	
	uint8_t memoffset = 2 * lower * (lower - 1);
	
	if (lower == 0) {
		if (upper > 0) return;
		
		// hack to display zeros
		memoffset = 40;
		lower = 4;
	}
	for (i = 0; i < lower; ++i) {
		x0 = pgm_read_byte(lower_lines + (i * 4 + 0) + memoffset) >> (large ? 0 : 1);
		y0 = pgm_read_byte(lower_lines + (i * 4 + 1) + memoffset) >> (large ? 0 : 1);
		x1 = pgm_read_byte(lower_lines + (i * 4 + 2) + memoffset) >> (large ? 0 : 1);
		y1 = pgm_read_byte(lower_lines + (i * 4 + 3) + memoffset) >> (large ? 0 : 1);
		
		screen_draw_line(offset_x + x0, offset_y + y0, offset_x + x1, offset_y + y1);
	}
}


