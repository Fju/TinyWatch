#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include <stdint.h>


#define I2C_READ 0x01
#define I2C_WRITE 0x00

void i2c_init();
void i2c_set_clock(uint8_t fast);
uint8_t i2c_start(uint8_t address);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read_ack();
uint8_t i2c_read_nack();
uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
void i2c_stop();

#endif // I2C_MASTER_H
