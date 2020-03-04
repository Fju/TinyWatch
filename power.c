#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>

void init_power() {
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
}

