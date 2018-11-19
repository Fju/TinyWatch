#ifndef _ATTiny84_SSD1306_H_
#define _ATTiny84_SSD1306_H_


typedef volatile uint8_t  PortReg;
typedef uint8_t           PortMask;

// defintions from https://github.com/adafruit/Adafruit_SSD1306/blob/master/Adafruit_SSD1306.h
#define SSD1306_MEMORYMODE                           0x20
#define SSD1306_COLUMNADDR                           0x21
#define SSD1306_PAGEADDR                             0x22
#define SSD1306_SETCONTRAST                          0x81
#define SSD1306_CHARGEPUMP                           0x8D
#define SSD1306_SEGREMAP                             0xA0
#define SSD1306_DISPLAYALLON_RESUME                  0xA4
#define SSD1306_DISPLAYALLON                         0xA5
#define SSD1306_NORMALDISPLAY                        0xA6
#define SSD1306_INVERTDISPLAY                        0xA7
#define SSD1306_SETMULTIPLEX                         0xA8
#define SSD1306_DISPLAYOFF                           0xAE
#define SSD1306_DISPLAYON                            0xAF
#define SSD1306_COMSCANINC                           0xC0
#define SSD1306_COMSCANDEC                           0xC8
#define SSD1306_SETDISPLAYOFFSET                     0xD3
#define SSD1306_SETDISPLAYCLOCKDIV                   0xD5
#define SSD1306_SETPRECHARGE                         0xD9
#define SSD1306_SETCOMPINS                           0xDA
#define SSD1306_SETVCOMDETECT                        0xDB

#define SSD1306_SETLOWCOLUMN                         0x00
#define SSD1306_SETHIGHCOLUMN                        0x10
#define SSD1306_SETSTARTLINE                         0x40

#define SSD1306_EXTERNALVCC                          0x01
#define SSD1306_SWITCHCAPVCC                         0x02

#define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A
#define SSD1306_DEACTIVATE_SCROLL                    0x2E
#define SSD1306_ACTIVATE_SCROLL                      0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3

#define SSD1306_DISPLAY_WIDTH	128
#define SSD1306_DISPLAY_HEIGHT  64

// ATTiny84 hasn't got enough dynamic memory for storing the whole 128x64 pixels
// so we half the resolution which only takes up 256 bytes instead of 1 KB !
#define DISPLAY_WIDTH	64
#define DISPLAY_HEIGHT	32

// color enumeration
#define COLOR_BLACK		0
#define COLOR_WHITE		1
#define COLOR_INVERT	2

class Tiny_SSD1306 {
public:
	// constructor
	Tiny_SSD1306(int8_t mosi_pin, int8_t sclk_pin, int8_t dc_pin, int8_t cs_pin, int8_t rst_pin);
	//destructor
	~Tiny_SSD1306(void);

	// initialization
	bool		begin(uint8_t switchvcc = SSD1306_SWITCHCAPVCC, uint8_t i2caddr = 0, boolean reset = true);

	// draw functions
	void		clear_display(void);
	void		set_pixel(int16_t x, int16_t y, uint8_t color);
	bool		get_pixel(int16_t x, int16_t y);

	// transmit buffered data to screen
	void		display(void);

private:
	// buffer for storing pixel information as bits
	uint8_t     *buffer;

	// pin indexes
	int8_t       mosiPin, clkPin, dcPin, csPin, rstPin;

	// port variables and pointers
	PortReg     *mosiPort, *clkPort, *dcPort, *csPort;
	PortMask     mosiPinMask, clkPinMask, dcPinMask, csPinMask;

	inline void spi_write(uint8_t data);

	void		send_command(uint8_t c);
	void		send_command_list(const uint8_t *c, uint8_t n);
};