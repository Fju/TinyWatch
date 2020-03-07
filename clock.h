#ifndef CLOCK_H
#define CLOCK_H

#include "i2c_master.h"

#define CLOCK_ADDR 0xD0

#define CLOCK_SECONDS_REG 0x00
#define CLOCK_MINUTES_REG 0x01
#define CLOCK_HOURS_REG 0x02

uint32_t get_time();

uint8_t get_hours();
void set_hours(uint8_t hours);
uint8_t get_minutes();
void set_minutes(uint8_t minutes);
uint8_t get_seconds();
void set_seconds(uint8_t seconds);

#endif //CLOCK_H
