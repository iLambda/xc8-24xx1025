# xc8-24xx1025
A 24xx1025 I²C EEPROM driver for XC8.

To use in a project, copy 24xx1025.h and 24xx1025.c in your project, and add :
```c
#include "24xx1025.h"
```
**⚠️IMPORTANT⚠️** You MUST redefine \_XTAL\_FREQ in 24xx1025.h for the library to work.

## api

The following methods are available:

#### ee24xx1025_open
```c
void ee24xx1025_open(uint32_t frequency);
```
Initialize the connection with the EEPROM.
* **frequency** : the frequency of the I²C clock, in Hz.

#### ee24xx1025_close
```c
void ee24xx1025_close();
```
Closes the connection with the EEPROM.

#### ee24xx1025_currentaddress
```c
void ee24xx1025_currentaddress();
```
Returns the value of the EEPROM address counter.

#### ee24xx1025_next
```c
uint8_t ee24xx1025_next(uint8_t i2caddress, uint8_t block);
```
Returns the data pointed by the address counter. Once it is called, the address counter is incremented.
If this call read address n, then next call will read address n+1.
* **i2caddress** : the I2C address of the EEPROM. Must be a OR combination of *EE24XX1025_A0* and *EE24XX1025_A1*.
* **block** : the EEPROM block that will be read. Must be *EE24XX1025_BLOCK0* or *EE24XX1025_BLOCK1*.

#### ee24xx1025_read
```c
uint8_t ee24xx1025_read(uint8_t i2caddress, uint8_t block, uint16_t address);
```
Returns the data at the specified address.
* **i2caddress** : the I2C address of the EEPROM. Must be a OR combination of *EE24XX1025_A0* and *EE24XX1025_A1*.
* **block** : the EEPROM block that will be read. Must be *EE24XX1025_BLOCK0* or *EE24XX1025_BLOCK1*.
* **address** : the EEPROM address of the data. Must be inbetween 0000h and FFFFh.

#### ee24xx1025_readseq
```c
void ee24xx1025_readseq(uint8_t i2caddress, uint8_t block, uint16_t address, uint8_t* out, uint16_t length);
```
Sequentially reads a given amount of data from the EEPROM.
* **i2caddress** : the I2C address of the EEPROM. Must be a OR combination of *EE24XX1025_A0* and *EE24XX1025_A1*.
* **block** : the EEPROM block that will be read. Must be *EE24XX1025_BLOCK0* or *EE24XX1025_BLOCK1*.
* **address** : the initial EEPROM address of the data. Must be inbetween 0000h and FFFFh.
* **out** : the pointer that will be filled with EEPROM data.
* **length** : the total length in bytes of the data that will be read.




#### ee24xx1025_write
```c
void ee24xx1025_write(uint8_t i2caddress, uint8_t block, uint16_t address, uint8_t data);
```
Writes the data at the specified address.
* **i2caddress** : the I2C address of the EEPROM. Must be a OR combination of *EE24XX1025_A0* and *EE24XX1025_A1*.
* **block** : the EEPROM block that will be modified. Must be *EE24XX1025_BLOCK0* or *EE24XX1025_BLOCK1*.
* **address** : the EEPROM address of the data. Must be inbetween 0000h and FFFFh.
* **data** : the data that'll be written at **address**.

#### ee24xx1025_writepage
```c
void ee24xx1025_writepage(uint8_t i2caddress, uint8_t block, uint16_t address, uint8_t* data, uint8_t length);
```
Writes up to 127 bytes of data at the same time in the EEPROM.
* **i2caddress** : the I2C address of the EEPROM. Must be a OR combination of *EE24XX1025_A0* and *EE24XX1025_A1*.
* **block** : the EEPROM block that will be modified. Must be *EE24XX1025_BLOCK0* or *EE24XX1025_BLOCK1*.
* **address** : the initial EEPROM address of the data. Must be inbetween 0000h and FFFFh.
* **data** : the array that will be copied into the EEPROM's memory.
* **length** : the total length in bytes of the data that will be written.
