#ifndef _EE24XX1025
#define _EE24XX1025

#include <stdint.h>

#define EE24XX1025_100MHZ         100000
#define EE24XX1025_400MHZ         400000

#define EE24XX1025_WRITE          0b00000000
#define EE24XX1025_READ           0b00000001
#define EE24XX1025_A0             0b00000010
#define EE24XX1025_A1             0b00000100
#define EE24XX1025_BLOCK0         0b00000000
#define EE24XX1025_BLOCK1         0b00001000
#define EE24XX1025_CONTROLCODE    0b10100000

#define _XTAL_FREQ                24000000

uint16_t currentaddress = 0x0000;

void ee24xx1025_open(uint32_t frequency);
void ee24xx1025_close();

uint16_t ee24xx1025_currentaddress();

uint8_t ee24xx1025_next(uint8_t i2caddress, uint8_t block);
uint8_t ee24xx1025_read(uint8_t i2caddress, uint8_t block, uint16_t address);
void ee24xx1025_readseq(uint8_t i2caddress, uint8_t block, uint16_t address, uint8_t* out, uint16_t length);

void ee24xx1025_write(uint8_t i2caddress, uint8_t block, uint16_t address, uint8_t data);
void ee24xx1025_writepage(uint8_t i2caddress, uint8_t block, uint16_t address, uint8_t* data, uint8_t length);


#endif
    