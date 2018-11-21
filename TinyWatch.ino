#include "src/Tiny_SSD1306.h";


#define PIN_MOSI 5
#define PIN_CLK 4
#define PIN_DC 3
#define PIN_CS 2
#define PIN_RST 1

Tiny_SSD1306 screen(PIN_MOSI, PIN_CLK, PIN_DC, PIN_CS, PIN_RST);

void setup() {
  // put your setup code here, to run once:
  screen.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
