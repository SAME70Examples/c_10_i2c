#ifndef _I2C_SAME70_H
#define _I2C_SAME70_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void i2c0_init(void);
void i2c0_write(uint8_t address_7b, uint8_t *pData, int data_length);
void i2c0_write_at(uint8_t address_7b, uint8_t internal_address, uint8_t *pData, int data_length);
void i2c0_read_at(uint8_t address_7b, uint8_t internal_address, uint8_t *pData, int data_length);

#ifdef __cplusplus
}
#endif

#endif /*_I2C_SAME70_H */
