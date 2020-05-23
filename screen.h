#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define BUFFER_SIZE 1024
#define SCREEN_ADDR 0x7A // 0x3D << 1

#define SCREEN_MEMORYMODE          0x20 ///< See datasheet
#define SCREEN_COLUMNADDR          0x21 ///< See datasheet
#define SCREEN_PAGEADDR            0x22 ///< See datasheet
#define SCREEN_DEACTIVATE_SCROLL   0x2E

#define SCREEN_SETLOWCOLUMN        0x00 ///< Not currently used
#define SCREEN_SETHIGHCOLUMN       0x10 ///< Not currently used
#define SCREEN_SETSTARTLINE        0x40 ///< See datasheet

#define SCREEN_SETCONTRAST         0x81 ///< See datasheet
#define SCREEN_CHARGEPUMP          0x8D ///< See datasheet
#define SCREEN_SEGREMAP            0xA0 ///< See datasheet
#define SCREEN_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SCREEN_DISPLAYALLON        0xA5 ///< Not currently used
#define SCREEN_NORMALDISPLAY       0xA6 ///< See datasheet
#define SCREEN_INVERTDISPLAY       0xA7 ///< See datasheet
#define SCREEN_SETMULTIPLEX        0xA8 ///< See datasheet
#define SCREEN_DISPLAYOFF          0xAE ///< See datasheet
#define SCREEN_DISPLAYON           0xAF ///< See datasheet
#define SCREEN_COMSCANINC          0xC0 ///< Not currently used
#define SCREEN_COMSCANDEC          0xC8 ///< See datasheet
#define SCREEN_SETDISPLAYOFFSET    0xD3 ///< See datasheet
#define SCREEN_SETDISPLAYCLOCKDIV  0xD5 ///< See datasheet
#define SCREEN_SETPRECHARGE        0xD9 ///< See datasheet
#define SCREEN_SETCOMPINS          0xDA ///< See datasheet
#define SCREEN_SETVCOMDETECT       0xDB ///< See datasheet

#define WIRE_MAX 32

uint8_t *buffer;

void screen_display();
void screen_clear();
uint8_t screen_begin();
void screen_off();
void screen_on();

void screen_draw_character(const uint8_t *bitmap, uint8_t num, const uint8_t height, const uint8_t width, uint8_t offset_x, uint8_t offset_y, uint8_t invert);
//void screen_draw_decimal(uint8_t num, uint8_t offset_x, uint8_t offset_y);

#endif // DISPLAY_H
