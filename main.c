#include <avr/io.h>
#include "screen.h"
#include "i2c_master.h"

#include <util/delay.h>

int main() {
	i2c_set_clock(true);

	if (screen_begin()) while(1);

	while(1) {

		_delay_ms(200);
		screen_display();
	}
}
