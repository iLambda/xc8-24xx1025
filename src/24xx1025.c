#include "../inc/24xx1025.h"

#include <xc.h>
#include <i2c.h>

void ee24xx1025_open(uint32_t frequency){
  // set pins as input
  I2C_SCL = 1;
  I2C_SDA = 1;
  // open i2c
  OpenI2C(MASTER, SLEW_ON);
  // the I2C clock frequency is given by:
  //    Fclock = Fosc / (4*(SSPADD + 1))
  //    =>SSPADD = (Fosc / 4*Fclock) - 1
  SSPADD = (((uint32_t)_XTAL_FREQ >> 2) / frequency) - 1;
  // debounce
  __delay_us(250);
}

uint16_t ee24xx1025_currentaddress(){
  return currentaddress;
}

uint8_t ee24xx1025_read(uint8_t i2caddress, uint8_t block, uint16_t address){
  // compute the control byte
  uint8_t ctrl = EE24XX1025_CONTROLCODE
          | (i2caddress & (EE24XX1025_A0 | EE24XX1025_A1))
          | ((!!block) * EE24XX1025_BLOCK1);
  // compute the address high and low byte
  uint8_t hiaddr = address >> 8;
  uint8_t loaddr = address & 0x00FF;

  // procedure to communicate is (','=ACK '.'=STOP and maj is start):
  //  Control byte, hiaddr, loaddr
  StartI2C();
  WriteI2C(ctrl | EE24XX1025_WRITE);
  IdleI2C();//WaitWriteI2C();
  WriteI2C(hiaddr);
  IdleI2C();
  WriteI2C(loaddr);
  IdleI2C();
  RestartI2C();
  WriteI2C(ctrl | EE24XX1025_READ);
  uint8_t value = ReadI2C();
  StopI2C();
  IdleI2C();

  // current address is now this one
  currentaddress = address;
  // return read value
  return value;
}

uint8_t ee24xx1025_next(uint8_t i2caddress, uint8_t block) {
  // compute the control byte
  uint8_t ctrl = EE24XX1025_CONTROLCODE
          | (i2caddress & (EE24XX1025_A0 | EE24XX1025_A1))
          | ((!!block) * EE24XX1025_BLOCK1)
          | EE24XX1025_READ;
  // read
  StartI2C();
  IdleI2C();
  WriteI2C(ctrl);
  IdleI2C();
  uint8_t value = ReadI2C();
  IdleI2C();
  StopI2C();
  IdleI2C();

  // incr adress
  currentaddress++;
  currentaddress &= 0xFFFF;
  // return value
  return value;
}


void ee24xx1025_readseq(uint8_t i2caddress, uint8_t block, uint16_t address, uint8_t* out, uint16_t length) {
  // compute the control byte
  uint8_t ctrl = EE24XX1025_CONTROLCODE
          | (i2caddress & (EE24XX1025_A0 | EE24XX1025_A1))
          | ((!!block) * EE24XX1025_BLOCK1);
  // check ptr
  if (!out) {
    return;
  }
  // compute the address high and low byte
  uint8_t hiaddr = address >> 8;
  uint8_t loaddr = address & 0x00FF;
  uint8_t endaddr = (address + length) & 0xFFFF;

  // procedure to communicate is (','=ACK '.'=STOP and maj is start):
  //  Control byte, hiaddr, loaddr
  StartI2C();
  WriteI2C(ctrl | EE24XX1025_WRITE);
  IdleI2C();
  WriteI2C(hiaddr);
  IdleI2C();
  WriteI2C(loaddr);
  IdleI2C();
  RestartI2C();
  WriteI2C(ctrl | EE24XX1025_READ);
  while (length--) {
    *(out++) = ReadI2C();
    if (length != 0) {
      AckI2C();
    }
  }
  StopI2C();
  IdleI2C();

  // current address is now this one
  currentaddress = endaddr;
}

void ee24xx1025_write(uint8_t i2caddress, uint8_t block, uint16_t address, uint8_t data){
    // compute the control byte
  uint8_t ctrl = EE24XX1025_CONTROLCODE
          | (i2caddress & (EE24XX1025_A0 | EE24XX1025_A1))
          | ((!!block) * EE24XX1025_BLOCK1)
          | EE24XX1025_WRITE;
  // compute the address high and low byte
  uint8_t hiaddr = address >> 8;
  uint8_t loaddr = address & 0x00FF;

  // procedure to communicate is (','=ACK '.'=STOP and maj is start):
  //  Control byte, hiaddr, loaddr
  StartI2C();
  WriteI2C(ctrl);
  IdleI2C();
  WriteI2C(hiaddr);
  IdleI2C();
  WriteI2C(loaddr);
  IdleI2C();
  WriteI2C(data);
  IdleI2C();
  StopI2C();
  IdleI2C();

  // current address is now this one
  currentaddress = address;
}
void ee24xx1025_writepage(uint8_t i2caddress, uint8_t block, uint16_t address, uint8_t* data, uint8_t length) {
  // compute the control byte
  uint8_t ctrl = EE24XX1025_CONTROLCODE
          | (i2caddress & (EE24XX1025_A0 | EE24XX1025_A1))
          | ((!!block) * EE24XX1025_BLOCK1)
          | EE24XX1025_WRITE;
  // compute the address high and low byte
  uint8_t hiaddr = address >> 8;
  uint8_t loaddr = address & 0x00FF;

  // procedure to communicate is (','=ACK '.'=STOP and maj is start):
  //  Control byte, hiaddr, loaddr
  StartI2C();
  WriteI2C(ctrl);
  IdleI2C();
  WriteI2C(hiaddr);
  IdleI2C();
  WriteI2C(loaddr);
  IdleI2C();
  while (length--) {
    WriteI2C(*(data++));
    IdleI2C();
  }
  StopI2C();
  IdleI2C();

  // current address is now this one
  currentaddress = address;
}

void ee24xx1025_close(){
  CloseI2C();
}
