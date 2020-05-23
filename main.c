#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "screen.h"
#include "i2c_master.h"
#include "fonts.h"
#include "clock.h"

#include <util/delay.h>

enum state_t {
	S_TIME,			// display time
	S_MENU_TIME,	// set time (hours and minutes)
	S_MENU_DATE,	// set date (day and month)
	S_MENU_YEAR		// set year
};

int main() {
	// set all I/O to outputs to save some energy, except the following:
	// INT0 (PD2), INT1 (PD3), SCL (PC5), SDA (PC4)
    DDRB = 0xFF;
    DDRC |= ~((1 << PC5) | (1 << PC4));
    DDRD |= ~((1 << PD2) | (1 << PD3));

	// active pull-up 
	PORTD |= (1 << PD2) | (1 << PD3);

	// turn off ADC
	ACSR = 0x80;

	// disable all components except TWI
	PRR |= ~(1 << PRTWI);

	// allocate memory for screen
	if (screen_begin()) while(1);

	// set interrupt enabled
	sei();


	enum state_t state;


	uint8_t btn1_state = 0;
	uint8_t btn2_state = 0;

	uint8_t hours = 0;
	uint8_t minutes = 0;
	uint8_t day = 0;
	uint8_t month = 0;
	uint8_t year = 0;

	uint8_t digit_selection = 0;

	uint8_t timeout = 0;

	// wake up/sleep loop
	while(1) {
		// two-wire interface needs to be resetted
		i2c_init();

		// turn on screen
		screen_on();

		state = S_TIME;
		timeout = 0;

		// display loop
		while (1) {
			// update state of button 1
			if (PIND & (1 << PD2)) {
				btn1_state = 0;
			} else if (btn1_state < 32) {
			   	++btn1_state;
			}
			
			// update state of button 2 
			if (PIND & (1 << PD3)) {
				btn2_state = 0;
			} else if (btn2_state < 32) {
				++btn2_state;
			}

			switch (state) {
				case S_TIME:
					// obtain time from RTC
					minutes = get_minutes();
					hours = get_hours();

					// display time
					screen_draw_character(numbers_bitmap, hours / 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 4, 15, 0);
					screen_draw_character(numbers_bitmap, hours % 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 28, 15, 0);
					screen_draw_character(numbers_bitmap, 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 52, 15, 0);
					screen_draw_character(numbers_bitmap, minutes / 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 78, 15, 0);
					screen_draw_character(numbers_bitmap, minutes % 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 102, 15, 0);

					++timeout;

					// detect long press
					if (btn1_state > 20) {
						// switch state
						state = S_MENU_TIME;
						screen_clear();
						// don't timeout when not in state S_TIME
						timeout = 0;
						// get day, month and year once
						day = get_date();
						month = get_month();
						year = get_year();
					}
					break;
				case S_MENU_TIME:
					// draw header ("hh:mm")
					screen_draw_character(character_bitmap, 4, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 24, 1, 0);
					screen_draw_character(character_bitmap, 4, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 40, 1, 0);
					screen_draw_character(character_bitmap, 5, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 56, 1, 0);
					screen_draw_character(character_bitmap, 3, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 72, 1, 0);
					screen_draw_character(character_bitmap, 3, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 88, 1, 0);

					screen_draw_character(numbers_bitmap, hours / 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 4, 30, digit_selection == 0 ? 0xFF : 0);
					screen_draw_character(numbers_bitmap, hours % 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 28, 30, digit_selection == 1 ? 0xFF : 0);
					screen_draw_character(numbers_bitmap, 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 52, 30, 0);
					screen_draw_character(numbers_bitmap, minutes / 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 78, 30, digit_selection == 2 ? 0xFF : 0);
					screen_draw_character(numbers_bitmap, minutes % 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 102, 30, digit_selection == 3 ? 0xFF : 0);

					if (btn1_state == 1) {
						++digit_selection;

						if (digit_selection == 4) {
							// update time
							set_hours(hours);
							set_minutes(minutes);

							// switch state
							state = S_MENU_DATE;
							screen_clear();
							digit_selection = 0;
						}
					}

					if (btn2_state == 1) {
						if (digit_selection == 0) hours += 10;
						else if (digit_selection == 1) hours += 1;
						else if (digit_selection == 2) minutes += 10;
						else if (digit_selection == 3) minutes += 1;

						if (hours > 23) hours = 0;
						if (minutes > 59) minutes = 0;
					}
					break;
				case S_MENU_DATE:
					// draw header ("DD MM")
					screen_draw_character(character_bitmap, 1, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 24, 1, 0);
					screen_draw_character(character_bitmap, 1, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 40, 1, 0);
					screen_draw_character(character_bitmap, 2, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 72, 1, 0);
					screen_draw_character(character_bitmap, 2, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 88, 1, 0);

					screen_draw_character(numbers_bitmap, day / 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 4, 30, digit_selection == 0 ? 0xFF : 0);
					screen_draw_character(numbers_bitmap, day % 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 28, 30, digit_selection == 1 ? 0xFF : 0);

					screen_draw_character(numbers_bitmap, month / 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 78, 30, digit_selection == 2 ? 0xFF : 0);
					screen_draw_character(numbers_bitmap, month % 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 102, 30, digit_selection == 3 ? 0xFF : 0);

					if (btn1_state == 1) {
						++digit_selection;

						if (digit_selection == 4) {
							// update date
							set_date(day);
							set_month(month);

							// switch state
							state = S_MENU_YEAR;
							screen_clear();
							digit_selection = 0;
						}
					}

					if (btn2_state == 1) {
						if (digit_selection == 0) day += 10;
						else if (digit_selection == 1) day += 1;
						else if (digit_selection == 2) month += 10;
						else if (digit_selection == 3) month += 1;

						if (day > 31) day = 1;
						if (month > 12) month = 1;
					}
					break;
				case S_MENU_YEAR:
					// draw header ("YYYY")
					screen_draw_character(character_bitmap, 0, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 32, 1, 0);
					screen_draw_character(character_bitmap, 0, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 48, 1, 0);
					screen_draw_character(character_bitmap, 0, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 64, 1, 0);
					screen_draw_character(character_bitmap, 0, TEXT_CHAR_HEIGHT, TEXT_CHAR_WIDTH, 80, 1, 0);
					
					// draw digits of year
					screen_draw_character(numbers_bitmap, 2, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 16, 30, 0);
					screen_draw_character(numbers_bitmap, 0, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 40, 30, 0);
					screen_draw_character(numbers_bitmap, year / 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 64, 30, digit_selection == 0 ? 0xFF : 0);
					screen_draw_character(numbers_bitmap, year % 10, NUMBERS_CHAR_HEIGHT, NUMBERS_CHAR_WIDTH, 86, 30, digit_selection == 1 ? 0xFF : 0);
					
					if (btn1_state == 1) {
						++digit_selection;

						if (digit_selection == 2) {
							// update year
							set_year(year);

							// switch state
							state = S_TIME;
							screen_clear();
							digit_selection = 0;
						}
					}
				
					if (btn2_state == 1) {
						if (digit_selection == 0) year += 10;
						else if (digit_selection == 1) year += 1;

						if (year > 99) year = 0;
					}
					break;
			}

			// refresh screen
			screen_display();
			_delay_ms(60);

			if (timeout > 50) {
				// leave loop, go to sleep
				break;
			}
		}	

		// turn off screen
		screen_off();

		// enable INT0 and INT1
		EIMSK |= (1 << INT1) | (1 << INT0);

		// sleep in power down mode
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_mode();

		// wake up here, disable interrupts
		EIMSK &= ~((1 << INT1) | (1 << INT0));
	}
}

// these interrupt routines MUST exists but can be empty
ISR(INT0_vect) {
}

ISR(INT1_vect) {
}
