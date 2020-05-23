#ifndef CLOCK_H
#define CLOCK_H

#include "i2c_master.h"

#define CLOCK_ADDR 0xD0

#define CLOCK_SECONDS_REG 0x00
#define CLOCK_MINUTES_REG 0x01
#define CLOCK_HOURS_REG   0x02
#define CLOCK_DATE_REG    0x04
#define CLOCK_MONTH_REG   0x05
#define CLOCK_YEAR_REG    0x06

uint32_t get_time();

uint8_t get_hours();
void set_hours(uint8_t hours);
uint8_t get_minutes();
void set_minutes(uint8_t minutes);
uint8_t get_seconds();
void set_seconds(uint8_t seconds);

uint8_t get_date();
void set_date(uint8_t date);
uint8_t get_month();
void set_month(uint8_t month);
uint8_t get_year();
void set_year(uint8_t year);

#endif //CLOCK_H
