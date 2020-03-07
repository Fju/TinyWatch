#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "screen.h"
#include "i2c_master.h"
#include "clock.h"

#include <util/delay.h>

int main() {
	// allocate memory for screen
	if (screen_begin()) while(1);

	uint8_t s = 0;
	uint8_t m = 0;
	uint8_t h = 0;
	uint8_t i = 0;

	// set time once
	set_hours(21);
	set_minutes(7);
	set_seconds(0);

	// set all I/O to outputs to save some energy, except the following:
	// INT0 (PD2), INT1 (PD3), SCL (PC5), SDA (PC4)
    DDRB = 0xFF;
    DDRC |= ~((1 << PC5) | (1 << PC4));
    DDRD |= ~((1 << PD2) | (1 << PD3));

	// turn off ADC
	ACSR = 0x80;

	// disable all components except TWI
	PRR |= ~(1 << PRTWI);

	// set interrupt enabled
	sei();

	// main loop
	while(1) {
		// two-wire interface needs to be resetted
		i2c_init();

		// turn on screen
		screen_on();
		// draw loop
		while(i++ < 30) {
			screen_clear();

			s = get_seconds();
			m = get_minutes();
			h = get_hours();
			
			screen_draw_inupiaq(h / 20, 2, 2, true);
			screen_draw_inupiaq(h % 20, 30, 2, true);
			
			screen_draw_inupiaq(m / 20, 58, 2, true);
			screen_draw_inupiaq(m % 20, 86, 2, true);

			screen_draw_inupiaq(s / 20, 40, 44, false);
			screen_draw_inupiaq(s % 20, 59, 44, false);

			//screen_draw_decimal(3, 5, 5);

			screen_display();
			_delay_ms(200);
		}
		// turn off screen
		screen_off();
		i = 0;

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
