#include "clock.h"

uint32_t get_time() {
	// combine all time values to a 32-bit number
	uint32_t time = get_hours() << 12;
	time |= get_minutes() << 6;
	time |= get_seconds();

	return time;
}

uint8_t get_hours() {
	// read from hours register (address = 0x02)
	// bits: [ MSB ][   6   ][     5    ][     4    ][ 3 ][ 2 ][ 1 ][ 0 ]
	//       [  0  ][ 24/12 ][   AM/PM  ][ 10 hours ][       hours      ]
	//                       [ 20 hours ]
	// If Bit 6 is set the hour data is encoded in the 12 mode, which means
	// that Bit 5 indicates AM (not set) or PM (set). In 24 hour mode
	// (Bit 6 not set) Bit 5 śtands for 20 hours (if set).
	uint8_t data;
	i2c_readReg(CLOCK_ADDR, CLOCK_HOURS_REG, &data, 1);

	uint8_t hours = data & 0x0F;

	if (data & 0x10) hours += 10;

	if (data & 0x40) {
		// 12 hour mode
		if (data & 0x20) hours += 12;
	} else {
		// 24 hour mode
		if (data & 0x20) hours += 20;
	}

	return hours;
}

void set_hours(uint8_t hours) {
	uint8_t data = 0;
	if (hours > 12) {
		hours -= 12;
		data = ((hours % 10) & 0x0F) | 0x60;
	} else {
		data = ((hours % 10) & 0x0F) | 0x40;
	}

	if (hours >= 10) data |= 0x10;

	i2c_writeReg(CLOCK_ADDR, CLOCK_HOURS_REG, &data, 1);
}

uint8_t get_minutes() {
	// read from minutes register (address = 0x01)
	// bits: [ MSB ][ 6 ][ 5 ][ 4 ][ 3 ][ 2 ][ 1 ][ LSB ]
	//       [  0  ][ 10 minutes  ][       minutes      ]
	uint8_t data;
	i2c_readReg(CLOCK_ADDR, CLOCK_MINUTES_REG, &data, 1);

	uint8_t minutes = data & 0x0F;
	minutes += ((data & 0x70) >> 4) * 10;

	return minutes;
}

void set_minutes(uint8_t minutes) {
	uint8_t data = 0;
	
	data |= (minutes % 10) & 0x0F;
	data |= ((minutes / 10) << 4) & 0x70;
	i2c_writeReg(CLOCK_ADDR, CLOCK_MINUTES_REG, &data, 1);
}

uint8_t get_seconds() {
	// read from seconds register (address = 0x00)
	// bits: [ MSB ][ 6 ][ 5 ][ 4 ][ 3 ][ 2 ][ 1 ][ LSB ]
	//       [  0  ][ 10 seconds  ][       seconds      ]
	uint8_t data;
	i2c_readReg(CLOCK_ADDR, CLOCK_SECONDS_REG, &data, 1);

	uint8_t seconds = data & 0x0F;
	seconds += ((data & 0x70) >> 4) * 10;

	return seconds;
}

void set_seconds(uint8_t seconds) {
	uint8_t data = 0;

	data |= (seconds % 10) & 0x0F;
	data |= ((seconds / 10) << 4) & 0x70;

	i2c_writeReg(CLOCK_ADDR, CLOCK_SECONDS_REG, &data, 1);
}


void set_date(uint8_t date) {
	// write to date register (address = 0x04)
	// bits: [ MSB ][ 6 ][  5 ][ 4 ][ 3 ][ 2 ][ 1 ][ LSB ]
	//       [  0  ][ 0 ][ 10 date ][        date        ]
	uint8_t data = 0;

	data |= (date % 10) & 0x0F;
	data |= ((date / 10) << 4) & 0x30;

	i2c_writeReg(CLOCK_ADDR, CLOCK_DATE_REG, &data, 1);
}

void set_month(uint8_t month) {
	// write to month register (address = 0x05)
	// bits: [    MSB    ][ 6 ][ 5 ][     4    ][ 3 ][ 2 ][ 1 ][ LSB ]
	//       [  century  ][ 0 ][ 0 ][ 10 month ][       month        ]
	uint8_t data = 0;

	data |= (month % 10) & 0x0F;
	data |= ((month / 10) << 4) & 0x10;

	i2c_writeReg(CLOCK_ADDR, CLOCK_MONTH_REG, &data, 1);
}

void set_year(uint8_t year) {
	// write to year register (address = 0x06)
	// bits: [ MSB ][ 6 ][ 5 ][ 4 ][ 3 ][ 2 ][ 1 ][ LSB ]
	//       [       10 year      ][        year        ]
	uint8_t data = 0;

	data |= (year % 10) & 0x0F;
	data |= ((year / 10) << 4) & 0xF0;

	i2c_writeReg(CLOCK_ADDR, CLOCK_YEAR_REG, &data, 1);
}
