// this library is used for reading and writing from PROGMEM
#include <avr/pgmspace.h>

// include header
#include "Tiny_SSD1306.h"

// port register defintions
#define SSD1306_SELECT			*csPort &= ~csPinMask;
#define SSD1306_DESELECT		*csPort |=  csPinMask;
#define SSD1306_MODE_COMMAND	*dcPort &= ~dcPinMask;
#define SSD1306_MODE_DATA		*dcPort |=  dcPinMask;



// double all bits of a 4-bit vector, e. g.: 0b1010 becomes 0b11001100
#define DOUBLE_BITS(s) ((uint8_t)((s & 0x08) << 4 | (s & 0x08) << 3 | (s & 0x04) << 3 | (s & 0x04) << 2 | (s & 0x02) << 2 | (s & 0x02) << 1 | (s & 0x01) << 1 | (s & 0x01)))


Tiny_SSD1306::Tiny_SSD1306(int8_t mosi_pin, int8_t sclk_pin, int8_t dc_pin, int8_t rst_pin, int8_t cs_pin) {
	// class constructor, store pin indexes
	mosiPin = mosi_pin;
	clkPin = sclk_pin;
	dcPin = dc_pin;
	csPin = cs_pin;
	rstPin = rst_pin;
}

Tiny_SSD1306::~Tiny_SSD1306(void) {
	if (buffer) {
		free(buffer);
		buffer = NULL;
	}
}

inline void Tiny_SSD1306::spi_write(uint8_t data) {
	uint8_t bit;
	for (bit = 0x80; bit; bit >>= 1) {
		if (d & bit) {
			*mosiPort |= mosiPinMask;
		} else {
			*mosiPort &= ~mosiPinMask;
		}
		*clkPort |= clkPinMask; // Clock high
		*clkPort &= ~clkPinMask; // Clock low
	}
}

void Tiny_SSD1306::send_command(uint8_t c) {
	SSD1306_MODE_COMMAND
	spi_write(c);
}

void Tiny_SSD1306::send_command_list(const uint8_t *c, uint8_t n) {
	SSD1306_MODE_COMMAND
	while (n--) spi_write(pgm_read_byte(c++));
}

bool Tiny_SSD1306::begin(uint8_t vcs, uint8_t addr, boolean reset) {
	// allocate memory for pixel buffer
	buffer = (uint8_t *)malloc(DISPLAY_WIDTH * DISPLAY_HEIGHT / 8);
	// unable to allocate memory, return 
	if (!buffer) return false;

	// internal or external vcc TODO: find out what means what !
	vccstate = vcs;


	// setup output ports (data/command, chip select)
	dcPort = (PortReg *)portOutputRegister(digitalPinToPort(dcPin));
	dcPinMask = digitalPinToBitMask(dcPin);
	csPort = (PortReg *)portOutputRegister(digitalPinToPort(csPin));
	csPinMask = digitalPinToBitMask(csPin);

	SSD1306_DESELECT

	mosiPort = (PortReg *)portOutputRegister(digitalPinToPort(mosiPin));
	mosiPinMask = digitalPinToBitMask(mosiPin);
	clkPort = (PortReg *)portOutputRegister(digitalPinToPort(clkPin));
	clkPinMask = digitalPinToBitMask(clkPin);
	// clock low
	*clkPort &= ~clkPinMask;
	

	// reset SSD1306 if requested and reset pin specified in constructor
	if (reset && (rstPin >= 0)) {
		pinMode(rstPin, OUTPUT);
		digitalWrite(rstPin, HIGH);
		delay(1);                   // VDD goes high at start, pause for 1 ms
		digitalWrite(rstPin, LOW);  // Bring reset low
		delay(10);                  // Wait 10 ms
		digitalWrite(rstPin, HIGH); // Bring out of reset
	}
	
	// start transmission for initialization sequences
	SSD1306_SELECT

	// Initiliazation sequences
	static const uint8_t PROGMEM init1[] = {
		SSD1306_DISPLAYOFF,             // 0xAE
		SSD1306_SETDISPLAYCLOCKDIV,     // 0xD5
		0x80,                           // the suggested ratio 0x80
		SSD1306_SETMULTIPLEX			// 0xA8
	};               
	ssd1306_commandList(init1, sizeof(init1));
	ssd1306_command1(HEIGHT - 1);

	static const uint8_t PROGMEM init2[] = {
		SSD1306_SETDISPLAYOFFSET,             // 0xD3
		0x0,                                  // no offset
		SSD1306_SETSTARTLINE | 0x0,           // line #0
		SSD1306_CHARGEPUMP };                 // 0x8D
	ssd1306_commandList(init2, sizeof(init2));

	ssd1306_command1((vccstate == SSD1306_EXTERNALVCC) ? 0x10 : 0x14);

	static const uint8_t PROGMEM init3[] = {
		SSD1306_MEMORYMODE,                   // 0x20
		0x00,                                 // 0x0 act like ks0108
		SSD1306_SEGREMAP | 0x1,
		SSD1306_COMSCANDEC };
	ssd1306_commandList(init3, sizeof(init3));

	static const uint8_t PROGMEM init4b[] = {
			SSD1306_SETCOMPINS,                 // 0xDA
			0x12,
			SSD1306_SETCONTRAST };              // 0x81
		ssd1306_commandList(init4b, sizeof(init4b));
		ssd1306_command1((vccstate == SSD1306_EXTERNALVCC) ? 0x9F : 0xCF);
	
	ssd1306_command1(SSD1306_SETPRECHARGE); // 0xd9
	ssd1306_command1((vccstate == SSD1306_EXTERNALVCC) ? 0x22 : 0xF1);
	static const uint8_t PROGMEM init5[] = {
		SSD1306_SETVCOMDETECT,               // 0xDB
		0x40,
		SSD1306_DISPLAYALLON_RESUME,         // 0xA4
		SSD1306_NORMALDISPLAY,               // 0xA6
		SSD1306_DEACTIVATE_SCROLL,
		SSD1306_DISPLAYON };                 // Main screen turn on
	ssd1306_commandList(init5, sizeof(init5));

	// end transmission
	SSD1306_DESELECT
	// return success
	return true;
}

void Tiny_SSD1306::clear_display(void) {
	// set whole buffer to 0 (Black)
	memset(buffer, COLOR_BLACK, DISPLAY_WIDTH * DISPLAY_HEIGHT / 8));
}

void Tiny_SSD1306::set_pixel(int16_t x, int16_t y, uint8_t color) {
	if (x >= 0 && x < DISPLAY_WIDTH && y >= 0 && y < DISPLAY_HEIGHT) {
		// pixel is inside of the display, update pixel buffer
		switch (color) {
			case COLOR_WHITE:	buffer[x + (y / 8) * DISPLAY_WIDTH] |= (1 << (y & 7)); break;
			case COLOR_BLACK:	buffer[x + (y / 8) * DISPLAY_WIDTH] &= ~(1 << (y & 7)); break;
			case COLOR_INVERT:	buffer[x + (y / 8) * DISPLAY_WIDTH] ^= (1 << (y & 7)); break;
		}
	}
}

bool Tiny_SSD1306::get_pixel(int16_t x, int16_t y) {
	if (x >= 0 && x < DISPLAY_WIDTH && y >= 0 && y < DISPLAY_HEIGHT) {
		// pixel is inside of the display, return pixel value
		return buffer[x + (y / 8) * DISPLAY_WIDTH] & (1 << (y & 7));		
	}
	return false;
}

void Tiny_SSD1306::display(void) {
	
	SSD1306_SELECT

	static const uint8_t PROGMEM dlist1[] = {
		SSD1306_PAGEADDR,
		0,                         // Page start address
		0xFF,                      // Page end (not really, but works here)
		SSD1306_COLUMNADDR,
		0 
	};                       // Column start address
	send_command_list(dlist1, sizeof(dlist1));
	send_command(SSD1306_DISPLAY_WIDTH - 1); // Column end address

	uint8_t *ptr = buffer;

	SSD1306_MODE_DATA

	uint8_t x, y = SSD1306_DISPLAY_HEIGHT / 8;
	while (y--) {
		x = SSD1306_DISPLAY_WIDTH;
		while (x--) {
			ptr = x / 2 + y / 2 * DISPLAY_WIDTH;
			spi_write(DOUBLE_BITS(y & 1 ? *ptr : *ptr >> 4);
		}
	}

	SSD1306_DESELECT
}

