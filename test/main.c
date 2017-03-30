#include <xc.h>

#include "../inc/24xx1025.h"

void main(void) {
  // init i2c communication with eeprom
  ee24xx1025_open(EE24XX1025_400MHZ);
  
  // write value at 0xFF
  ee24xx1025_write(EE24XX1025_A0 | EE24XX1025_A1, EE24XX1025_BLOCK0, 0xFF, 0xAA);
  // sequentially write 5 values at 0x100
  uint8_t values[5] = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  ee24xx1025_writepage(EE24XX1025_A0 | EE24XX1025_A1, EE24XX1025_BLOCK0, 0x100, values, 5);
  
  // read value at address 0xFF
  uint8_t valFF = ee24xx1025_read(EE24XX1025_A0 | EE24XX1025_A1, EE24XX1025_BLOCK0, 0x00FF);
  // read value at next address (0x100 because last address = 0xFF)
  uint8_t val100 = ee24xx1025_next(EE24XX1025_A0 | EE24XX1025_A1, EE24XX1025_BLOCK0);
  // read 100 values at 0x100
  uint8_t data[100] = {0};
  ee24xx1025_readseq(EE24XX1025_A0 | EE24XX1025_A1, EE24XX1025_BLOCK0, 0x100, data, 100);
  
  // close i2c communication
  ee24xx1025_close();
  
  // program loop
  while(1); 
}
